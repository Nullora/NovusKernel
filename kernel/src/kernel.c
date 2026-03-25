#include"memory.h"
#include"boot.h"
#include"tty.h"
#include"gdt.h"
#include"input.h"

void main(BootInfo* bootinfo) {
    __asm__ volatile ("mov $0x500000, %rsp");
    init_gdt();
    init_idt();
    init_heap(bootinfo); 

    //text
    unsigned char last = 0;
    unsigned long text_y = 70;
    unsigned long text_x = 50;

    unsigned int* screenbuffer = bootinfo->FrameBufferBase;


    unsigned int* backbuffer = malloc(bootinfo->FrameBufferSize); 
    draw_hex((unsigned long long)screenbuffer, 50, 110, 0x006400, bootinfo, backbuffer);
    clear_screen(0x000000, bootinfo, screenbuffer);
    draw_string("Horrible version idk how to implement proper keyboard handling im just polling like a dork now", 50, 30, 0xFFFFFF, bootinfo, screenbuffer);
    memcpy(backbuffer, screenbuffer, bootinfo->FrameBufferSize);
    char* keyboard_buffer = malloc(256);
    int i = 0;
    for(;;){
        if(!(inb(0x64) & 0x01)) continue;
        unsigned char s = inb(0x60);
        if(s & 0x80) continue;
        last = s;
        if(last==0x1c) {
            text_y += 30; 
            text_x = 30;
            memset(keyboard_buffer, 0, 256);
            i=0;
        }
        text_x += 8;
        draw_char(scancode_to_ascii(s), text_x,text_y, 0xFFFFFF, bootinfo, screenbuffer);
        record_keyboard_to_buffer(keyboard_buffer, scancode_to_ascii(s), &i);
        if(strcmp(keyboard_buffer,"help")==1){
            draw_string("> Go to the GitHub read me for more information!! Don't forget to star if you havent", 50,text_y+30, 0xFFFFFF, bootinfo, screenbuffer);
            text_y += 30;
            memset(keyboard_buffer, 0, 256);
        }
        if(strcmp(keyboard_buffer,"nub")==1){
            draw_string("> Not available yet :c", 50,text_y+30, 0xFFFFFF, bootinfo, screenbuffer);
            text_y += 30;
            memset(keyboard_buffer, 0, 256);
        }
        memcpy(backbuffer, screenbuffer, bootinfo->FrameBufferSize);
    }
}
