#include"memory.h"
#include"boot.h"
#include"tty.h"
#include"gdt.h"

void main(BootInfo* bootinfo) {
    init_gdt();
    init_heap(bootinfo);
    unsigned int* backbuffer = bootinfo->FrameBufferBase;
    int textcolor = 0x006400;
    clear_screen(0x000000, bootinfo, backbuffer);
    draw_string(">Printed by NovusKernel and loaded from NBL", 50, 50, textcolor, bootinfo, backbuffer);
    draw_string(">Made by @Nullora on GitHub", 50, 70, textcolor, bootinfo, backbuffer);
    draw_string(">No longer double buffering and heap setup is bugging out", 50, 90, textcolor, bootinfo, backbuffer);
    
    for(;;);
}