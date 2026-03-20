#include"gdt.h"
#include"memory.h"

GDT GDT_Table[3];
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
