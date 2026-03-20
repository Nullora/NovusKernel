#include"gdt.h"
#include"memory.h"

GDT GDT_Table[3];
IDT IDT_Table[256];
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