#include"memory.h"
#include"boot.h"
#include"tty.h"

void main(BootInfo* bootinfo) {
    init_heap(bootinfo);
    unsigned int* screenbuffer = bootinfo->FrameBufferBase;
    int textcolor = 0x006400;
    void* backbuffer = malloc(bootinfo->FrameBufferSize);
    clear_screen(0x000000, bootinfo, backbuffer);
    draw_string(">Printed by NovusKernel and loaded from NBL", 50, 50, textcolor, bootinfo, backbuffer);
    draw_string(">Made by @Nullora on GitHub", 50, 70, textcolor, bootinfo, backbuffer);
    draw_string(">Double buffering and heap setup", 50, 90, textcolor, bootinfo, backbuffer);

    memcpy(screenbuffer, backbuffer, bootinfo->FrameBufferSize);
    free(backbuffer);
    for(;;);
}