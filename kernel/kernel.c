#include"memory.h"
//BootInfo struct so i can take from bootloader
typedef struct{
    void* FrameBufferBase;
    unsigned long long FrameBufferSize;
    unsigned long long Width;
    unsigned long long Height;
    unsigned long long PixelsPerScanLine;
} BootInfo;

//to get rid of the waterfall effect when filling screen
unsigned int* backbuffer = (unsigned int*)0x1000000;



//writing my own memcpy :c
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

void main(BootInfo* bootinfo) {
    unsigned int* fb = (unsigned int*)bootinfo->FrameBufferBase;
    for(unsigned long long i = 0; i<bootinfo->FrameBufferSize/4;i++){
        backbuffer[i] = 0x200020;
    }
    memcpy(fb, backbuffer, bootinfo->PixelsPerScanLine*bootinfo->Height*4);
    for(;;);
}