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
    draw_hex((unsigned long long)backbuffer, 50, 50, 0x006400, bootinfo, backbuffer);
    draw_hex(heap_size, 50, 70, 0x006400, bootinfo, backbuffer);
    draw_hex(bootinfo->FrameBufferSize, 50, 90, 0x006400, bootinfo, backbuffer);


    unsigned int* screenbufer = malloc(bootinfo->FrameBufferSize); 
    clear_screen(0x006400, bootinfo, screenbufer);
    draw_hex(heap_base, 50, 30, 0x0000, bootinfo, screenbufer);
    memcpy(backbuffer, screenbufer, bootinfo->FrameBufferSize);
    unsigned char last = 0;
    unsigned long text_y = 90;
    for(;;);
}