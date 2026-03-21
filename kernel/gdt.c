#include"gdt.h"
#include"memory.h"

GDT GDT_Table[3];
IDT IDT_Table[256];
unsigned char scancode;
void init_gdt(){
    //set gdt_table values
    memset(&GDT_Table[0], 0, sizeof(GDT));
    GDT b;
    b.base_low = 0;
    b.base_mid = 0;
    b.base_high = 0;
    b.limit_low = 0xFFFF;
    b.access_byte = 0x9A;
    b.limit_high_flags = 0xAF;
    GDT_Table[1] = b;
    b.access_byte = 0x92;
    GDT_Table[2] = b;

    GDTR gdtr;
    gdtr.GDT_size = sizeof(GDT_Table)-1;
    gdtr.GDT_address = (unsigned long long)&GDT_Table;
    load_gdt(&gdtr);
}
void init_idt(){
    memset(&IDT_Table[0], 0, sizeof(IDT_Table));
    IDTR idtr;
    idtr.IDT_size = sizeof(IDT_Table)-1;
    idtr.IDT_address = (unsigned long long)&IDT_Table;
    for(unsigned long long i=0;i<47;i++){
        set_idt_entry(i, (void*)dummy_handler);
    }
    set_idt_entry(33, keyboard_handler);
    load_idt(&idtr);
}
void set_idt_entry(int n, void* handler){
    IDT i;
    i.offset_low = (unsigned long long)handler & 0xFFFF;
    i.offset_mid = ((unsigned long long)handler>>16) & 0xFFFF;
    i.offset_high = ((unsigned long long)handler>>32) & 0xFFFFFFFF;
    i.selector = 0x08;
    i.ist = 0;
    i.zero = 0;
    i.flags = 0x8E;
    IDT_Table[n]=i;
}

void outb(unsigned short port, unsigned char value) { //remapping programmable interrupt handler
    __asm__ volatile ("outb %0, %1" : : "a"(value), "Nd"(port));
}
unsigned char inb(unsigned short port) {
    unsigned char result;
    __asm__ volatile ("inb %1, %0" : "=a"(result) : "Nd"(port));
    return result;
}
void init_pic(){
    outb(0x20, 0x11);

    outb(0x80, 0); //dummy cz PIC is old hag

    outb(0xA0, 0x11);

    outb(0x80, 0); //dummy cz PIC is old hag

    outb(0x21, 0x20);

    outb(0x80, 0); //dummy cz PIC is old hag

    outb(0xA1, 0x28);

    outb(0x80, 0); //dummy cz PIC is old hag

    outb(0x21, 0x04);

    outb(0x80, 0); //dummy cz PIC is old hag

    outb(0xA1, 0x02);

    outb(0x80, 0); //dummy cz PIC is old hag

    outb(0x21, 0x01);

    outb(0x80, 0); //dummy cz PIC is old hag

    outb(0xA1, 0x01);

    outb(0x80, 0); //dummy cz PIC is old hag

    outb(0x21, 0x0);

    outb(0x80, 0); //dummy cz PIC is old hag

    outb(0xA1, 0x0);

    outb(0x80, 0); //dummy cz PIC is old hag

}

//keyboard interrupt handler
__attribute__((interrupt)) void keyboard_handler(void* frame){
    scancode = inb(0x60);
    outb(0x20, 0x20);
}
__attribute__((interrupt)) void dummy_handler(void* frame){}