#include"memory.h"
#include"boot.h"
unsigned long long heap_base;
unsigned long long heap_size;

void* memcpy(void* dest, void* src, unsigned long long n) {
    __uint128_t* d128 = dest;
    __uint128_t* s128 = src;
    unsigned long long i;
    
    for(i = 0; i < n/16; i++) {
        d128[i] = s128[i];
    }
    unsigned char* d = (unsigned char*)dest + (n/16)*16;
    unsigned char* s = (unsigned char*)src + (n/16)*16;
    for(unsigned long long j = 0; j < n%16; j++) {
        d[j] = s[j];
    }
    return dest;
}
void* memset(void* dest, int value, unsigned long long n){
    unsigned char* d = dest;
    for(unsigned long long i=0;i<n;i++){
        d[i]=value;
    }
    return dest;
}
void init_heap(BootInfo* bootinfo){
    unsigned long long pages=0;
    for(unsigned long long i=0;i<bootinfo->mMapSize/bootinfo->DescriptorSize;i++){
        //this line alone made me lose my mind for 30mins
        EFI_MEMORY_DESCRIPTOR* desc = (EFI_MEMORY_DESCRIPTOR*)((char*)bootinfo->memMap+i*bootinfo->DescriptorSize);
        if(desc->Type==7 && desc->NumberOfPages>pages){
            heap_size = desc->NumberOfPages*4096;
            heap_base = desc->PhysicalStart;
        }
    }
}