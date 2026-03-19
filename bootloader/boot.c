#include <efi.h>
#include <efilib.h>
#include<elf.h>
#include <stddef.h>
#include <string.h>

//BootInfo struct so i can pass it to kernel
typedef struct{
    void* FrameBufferBase;
    UINTN FrameBufferSize;
    UINTN Width;
    UINTN Height;
    UINTN PixelsPerScanLine;
    UINTN mMapSize;
    UINTN DescriptorSize;
    EFI_MEMORY_DESCRIPTOR* memMap;
} BootInfo;


EFI_FILE* LoadFile(EFI_FILE* dir, CHAR16* path, EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE* SystemTable){
    EFI_FILE* LoadedFile;
    EFI_LOADED_IMAGE *LoadedImage;
    EFI_SIMPLE_FILE_SYSTEM_PROTOCOL* Filesystem;

    EFI_GUID loaded_image_protocol = LOADED_IMAGE_PROTOCOL;
    EFI_GUID load_file_protocol = SIMPLE_FILE_SYSTEM_PROTOCOL;

    //Load Image
    EFI_STATUS s = uefi_call_wrapper(SystemTable->BootServices->HandleProtocol,
        3,
        ImageHandle,
        &loaded_image_protocol,
        (void **)&LoadedImage);
    Print(L"Image status: %r\n", s);
    Print(L"[1/4]\n");

    //Load FileSystem
    EFI_STATUS s1 = uefi_call_wrapper(SystemTable->BootServices->HandleProtocol,
        3,
        LoadedImage->DeviceHandle,
        &load_file_protocol,
        (void **)&Filesystem);
    Print(L"Filesystem status: %r\n", s1);
    Print(L"[2/4]...\n");


    if(dir==NULL){
        EFI_STATUS so = uefi_call_wrapper(Filesystem->OpenVolume, 2, Filesystem, &dir);
        Print(L"open volume: %r\n", so);
        Print(L"[3/4] NULL\n");
    }else{
        Print(L"[3/4] FULL\n");
    }

    //Open File
    EFI_STATUS s2 = uefi_call_wrapper(dir->Open, 5, dir, &LoadedFile, path, EFI_FILE_MODE_READ, EFI_FILE_READ_ONLY);
    Print(L"open status: %r\n", s2);
    Print(L"[4/4] ");
    if(s2 != EFI_SUCCESS){
        return NULL;
    }
    return LoadedFile;
}
int memcmp(const void* apt, const void* bpt, size_t n){
    const unsigned char* a = apt;
    const unsigned char* b = bpt;
    for(size_t i = 0; i<n; i++){
        if(a[i]<b[i]) return -1;
        else if(a[i]>b[i]) return 1;    
    }
    return 0;
}
  
EFI_STATUS efi_main (EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable) {
    InitializeLib(ImageHandle, SystemTable);
    Print(L"ImageHandle: %lx\n", (UINT64)ImageHandle);
    Print(L"Loading NovusKernel. \n");
    //Load kernel
    EFI_FILE* Kernel = LoadFile(NULL,L"kernel.elf", ImageHandle, SystemTable);
    if(Kernel==NULL){
        Print(L"FATAL: KERNEL FAILED TO LOAD \n");

    }else{
        Print(L"Kernel Loaded into memory Successfully \n");
    }
    Elf64_Ehdr header;
    {
        Print(L"header init...\n");
        UINTN FileInfoSize =0;
        EFI_FILE_INFO* FileInfo;
        uefi_call_wrapper(Kernel->GetInfo, 4, Kernel, &gEfiFileInfoGuid, &FileInfoSize, NULL);
        Print(L"getting header size...\n");
        uefi_call_wrapper(SystemTable->BootServices->AllocatePool, 3,EfiLoaderData, FileInfoSize, (void *)&FileInfo);
        uefi_call_wrapper(Kernel->GetInfo, 4, Kernel, &gEfiFileInfoGuid, &FileInfoSize, (void **)FileInfo);
        UINTN size = sizeof(header);
        Print(L"Reading header...\n");
        uefi_call_wrapper(Kernel->Read, 3, Kernel, &size, &header);
        Print(L"DONE[8/8]\n");

    }
    //check header compatibility
    Print(L"Checking header compatibility\n");
    if(
        //if youre reading this, know this blob was legit hell on fucking earth
        memcmp(&header.e_ident[EI_MAG0], ELFMAG, SELFMAG) != 0 ||
        header.e_ident[EI_CLASS] != ELFCLASS64 ||
        header.e_ident[EI_DATA] != ELFDATA2LSB ||
        header.e_type != ET_EXEC ||
        header.e_machine != EM_X86_64 ||
        header.e_version != EV_CURRENT
    ){
        Print(L"FATAL: Kernel format is bad \n");
    }else{
        Print(L"Kernel header verified successfully \n");
    }
    Elf64_Phdr* phdr;
    {
        uefi_call_wrapper(Kernel->SetPosition, 2,Kernel, header.e_phoff);
        UINTN size = header.e_phnum * header.e_phentsize;
        uefi_call_wrapper(SystemTable->BootServices->AllocatePool, 3,EfiLoaderData, size, (void **)&phdr);
        uefi_call_wrapper(Kernel->Read, 3,Kernel, &size, phdr);
    }
    for(
        Elf64_Phdr* phdrs = phdr;
        (char*)phdrs < (char*)phdr + header.e_phnum * header.e_phentsize;
        phdrs = (Elf64_Phdr*)((char*) phdrs+ header.e_phentsize)
    ){
        switch (phdrs->p_type){
            case PT_LOAD:
                // this blob was hell too
                int pages = (phdrs->p_memsz + 0x1000 - 1) / 0x1000;
                Elf64_Addr segment = phdrs->p_paddr;
                uefi_call_wrapper(SystemTable->BootServices->AllocatePages, 4, AllocateAddress, EfiLoaderData, pages, &segment);
                uefi_call_wrapper(Kernel->SetPosition, 2,Kernel, phdrs->p_offset);
                UINTN size = phdrs->p_filesz;
                uefi_call_wrapper(Kernel->Read, 3, Kernel, &size, (void *) segment);
                break;
        }
    }
    //graphics output protocol setup
    EFI_GUID GopGuid = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;
    EFI_GRAPHICS_OUTPUT_PROTOCOL *gop;
    int status = uefi_call_wrapper(SystemTable->BootServices->LocateProtocol, 3, &GopGuid, NULL, (void **)&gop);
    if(EFI_ERROR(status)) Print(L"Unable to locate GOP \n");
    BootInfo bootinfo;
    bootinfo.FrameBufferBase = (void*)gop->Mode->FrameBufferBase;
    bootinfo.FrameBufferSize = gop->Mode->FrameBufferSize;
    bootinfo.Width = gop->Mode->Info->HorizontalResolution;
    bootinfo.Height = gop->Mode->Info->VerticalResolution;
    bootinfo.PixelsPerScanLine = gop->Mode->Info->PixelsPerScanLine;
    Print(L"NovusKernel Loaded\n");
    Print(L"If you still see this, something is horribly wrong with the kernel...\n");

    //exit boot services
    UINTN mMapSize = 0;
    EFI_MEMORY_DESCRIPTOR* memMap =  NULL;
    UINTN MapKey, DescriptorSize; 
    UINT32 DescriptorVer;
    
    uefi_call_wrapper(SystemTable->BootServices->GetMemoryMap, 5, &mMapSize, memMap, &MapKey, &DescriptorSize, &DescriptorVer);
    uefi_call_wrapper(SystemTable->BootServices->AllocatePool, 3, EfiLoaderData, mMapSize, (void**)&memMap);
    uefi_call_wrapper(SystemTable->BootServices->GetMemoryMap, 5, &mMapSize, memMap, &MapKey, &DescriptorSize, &DescriptorVer);
    //pass memorymap to kernel
    bootinfo.memMap = memMap;
    bootinfo.mMapSize = mMapSize;
    bootinfo.DescriptorSize = DescriptorSize;
    uefi_call_wrapper(SystemTable->BootServices->ExitBootServices, 2, ImageHandle, MapKey);
    //start kernel
    void (*KernelStart)(BootInfo*) = ((__attribute__((sysv_abi)) void (*) (BootInfo*)) header.e_entry);
    KernelStart(&bootinfo);
}