#include"memory.h"
#include"boot.h"
#include"tty.h"
#include"gdt.h"

void main(BootInfo* bootinfo) {
    __asm__ volatile ("mov $0x500000, %rsp");
    init_gdt();
    init_idt();
    init_pic();
    init_heap(bootinfo); 

    //text
    unsigned char last = 0;
    unsigned long text_y = 70;

    unsigned int* backbuffer = bootinfo->FrameBufferBase;
    clear_screen(0x000000, bootinfo, backbuffer);
    draw_hex(heap_base, 50, 30, 0x006400, bootinfo, backbuffer);
    draw_hex((unsigned long long)backbuffer, 50, 50, 0x006400, bootinfo, backbuffer);
    draw_hex(heap_size, 50, 70, 0x006400, bootinfo, backbuffer);
    draw_hex(bootinfo->FrameBufferSize, 50, 90, 0x006400, bootinfo, backbuffer);


    unsigned int* screenbufer = malloc(bootinfo->FrameBufferSize); 
    draw_hex((unsigned long long)screenbufer, 50, 110, 0x006400, bootinfo, backbuffer);
    clear_screen(0x240024, bootinfo, screenbufer);
    draw_string("NUB V2.0 WORKS WEL", 50, 30, 0xFFFFFF, bootinfo, screenbufer);
    memcpy(backbuffer, screenbufer, bootinfo->FrameBufferSize);

    for(;;){
        unsigned char s = inb(0x60);
        if(s & 0x80) continue;
        if(s == 0 || s == last) continue;
        last = s;
        draw_hex(s, 50, text_y, 0x006400, bootinfo, screenbufer);
        text_y += 30;
        memcpy(backbuffer, screenbufer, bootinfo->FrameBufferSize);
    }
}