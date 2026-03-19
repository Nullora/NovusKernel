#include"memory.h"
#include"boot.h"
#include"tty.h"

void main(BootInfo* bootinfo) {
    init_heap(bootinfo);
    unsigned int* screenbuffer = bootinfo->FrameBufferBase;
    void* backbuffer = malloc(bootinfo->FrameBufferSize);
    clear_screen(0x000000, bootinfo, backbuffer);

    draw_hex(heap_base, 50, 50, 0xFFFFFF, bootinfo,backbuffer);
    //screenbuffer and backbuffer
    draw_hex((unsigned long long)screenbuffer, 50, 70, 0xFFFFFF, bootinfo,backbuffer);
    draw_hex((unsigned long long)backbuffer, 50, 90, 0xFFFFFF, bootinfo, backbuffer);
    //framebuffer size and descriptor size
    draw_hex((unsigned long long)bootinfo->FrameBufferSize, 50, 110, 0xFFFFFF, bootinfo, backbuffer);
    draw_hex((unsigned long long)bootinfo->DescriptorSize, 50, 130, 0xFFFFFF, bootinfo, backbuffer);
    //memMap size
    draw_hex((unsigned long long)bootinfo->mMapSize, 50, 150, 0xFFFFFF, bootinfo, backbuffer);
    memcpy(screenbuffer, backbuffer, bootinfo->FrameBufferSize);
    for(;;);
}