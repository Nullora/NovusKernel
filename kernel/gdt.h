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

//assembly function
extern void load_gdt(GDTR* gdtr);
void init_gdt();



#endif