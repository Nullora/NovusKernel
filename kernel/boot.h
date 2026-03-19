#ifndef BOOT_H
#define BOOT_H

//custom EFI_MEMORY_DESCRIPTOR cz i pass it from bootloader
typedef struct{
    unsigned int Type;
    unsigned int Padding;
    unsigned long long PhysicalStart;
    unsigned long long VirtualStart;
    unsigned long long NumberOfPages;
    unsigned long long Attribute;
} EFI_MEMORY_DESCRIPTOR;

//BootInfo so i can grab efi info from bootloader
typedef struct{
    void* FrameBufferBase;
    unsigned long long FrameBufferSize;
    unsigned long long Width;
    unsigned long long Height;
    unsigned long long PixelsPerScanLine;
    unsigned long long mMapSize;
    unsigned long long DescriptorSize;
    EFI_MEMORY_DESCRIPTOR* memMap;
} BootInfo;

#endif