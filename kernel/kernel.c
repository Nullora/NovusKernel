#include"memory.h"
#include"boot.h"
#include"tty.h"

void main(BootInfo* bootinfo) {
    init_heap(bootinfo);
    unsigned int* screenbuffer = bootinfo->FrameBufferBase;
    void* backbuffer = malloc(bootinfo->FrameBufferSize);
    clear_screen(0x301934, bootinfo, screenbuffer);
    
    draw_hex(heap_base, 50, 50, 0xFFFFFF, bootinfo,screenbuffer);
    draw_hex((unsigned long long)screenbuffer, 50, 70, 0xFFFFFF, bootinfo,screenbuffer);
    draw_string("Printed from NovusKernel and loaded by NBL", 50, 90, 0xFFFFFF, bootinfo, screenbuffer);
    draw_string("Made by @Nullora on GitHub", 50, 110, 0xFFFFFF, bootinfo, screenbuffer);
    draw_hex((unsigned long long)backbuffer, 50, 130, 0xFFFFFF, bootinfo, screenbuffer);
    draw_hex((unsigned long long)bootinfo->FrameBufferSize, 50, 150, 0xFFFFFF, bootinfo, screenbuffer);
    draw_hex((unsigned long long)bootinfo->DescriptorSize, 50, 170, 0xFFFFFF, bootinfo, screenbuffer);
    for(;;);
}