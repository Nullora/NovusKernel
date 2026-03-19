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


void main(BootInfo* bootinfo) {
    unsigned int* fb = (unsigned int*)bootinfo->FrameBufferBase;
    for(unsigned long long i = 0; i<bootinfo->FrameBufferSize/4;i++){
        backbuffer[i] = 0x200020;
    }
    memcpy(fb, backbuffer, bootinfo->PixelsPerScanLine*bootinfo->Height*4);
    for(;;);
}