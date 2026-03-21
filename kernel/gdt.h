#ifndef GDT_H
#define GDT_H


//passing gdt table to cpu (gdt entry)
typedef struct __attribute__((packed)){
    unsigned short limit_low;
    unsigned short base_low;
    unsigned char base_mid;
    unsigned char access_byte;
    unsigned char limit_high_flags;
    unsigned char base_high;
} GDT;

typedef struct __attribute__((packed)){
    unsigned short GDT_size;
    unsigned long long GDT_address;
} GDTR;


//idt hell
typedef struct __attribute__((packed)){
    unsigned short offset_low;
    unsigned short selector;
    unsigned char ist;
    unsigned char flags;
    unsigned short offset_mid;
    unsigned int offset_high;
    unsigned int zero;
} IDT;

typedef struct __attribute__((packed)){
    unsigned short IDT_size;
    unsigned long long IDT_address;
} IDTR;


//assembly function
extern void load_gdt(GDTR* gdtr);
extern void load_idt(IDTR* idtr);
extern void enable_interrupts();
void init_gdt();
void init_idt();

//programmable interrupt handler
void outb(unsigned short port, unsigned char value);
unsigned char inb(unsigned short port);
void init_pic();


//actual interrupt functions (finally after all the shit setup)
extern unsigned char scancode;
void keyboard_handler(void* frame) __attribute__((interrupt));

#endif