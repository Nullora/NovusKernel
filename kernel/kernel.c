#include"memory.h"
#include"boot.h"
#include"tty.h"
#include"gdt.h"

void main(BootInfo* bootinfo) {
    init_gdt();
    init_idt();
    init_pic();
    init_heap(bootinfo); 
    unsigned int* backbuffer = bootinfo->FrameBufferBase;
    clear_screen(0x000000, bootinfo, backbuffer);
    draw_hex(heap_base, 50, 30, 0x006400, bootinfo, backbuffer);
    draw_hex(heap_base, 50, 30, 0x006400, bootinfo, backbuffer);
    unsigned int* screenbufer = malloc(bootinfo->FrameBufferSize); 
    clear_screen(0x006400, bootinfo, screenbufer);
    draw_hex(heap_base, 50, 30, 0x0000, bootinfo, screenbufer);
    int textcolor = 0x006400;
    draw_string(">Printed by NovusKernel and loaded from NBL", 50, 50, textcolor, bootinfo, backbuffer);
    draw_string(">Made by @Nullora on GitHub", 50, 70, textcolor, bootinfo, backbuffer);
    draw_string(">No longer double buffering and heap setup is bugging out", 50, 90, textcolor, bootinfo, backbuffer);
    memcpy(backbuffer, screenbufer, bootinfo->FrameBufferSize);
    unsigned char last = 0;
    unsigned long text_y = 90;
    for(;;) {
        if(scancode != last) {
            last = scancode;
            text_y += 30;
            draw_string("key pressed", 50, text_y, textcolor, bootinfo, backbuffer);
        }
    }
}