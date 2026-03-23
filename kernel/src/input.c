#include"gdt.h"
char scancode_to_ascii(unsigned char sc){
    char map[128] = {
        0,27,'1','2','3','4','5','6','7','8','9','0','-','=',8,
        9,'q','w','e','r','t','y','u','i','o','p','[',']','\n',0,
        'a','s','d','f','g','h','j','k','l',';','\'','`',0,'\\',
        'z','x','c','v','b','n','m',',','.','/',0,'*',0,' '
    };
    if(sc < sizeof(map)) return map[sc];
    return 0;
}
void record_keyboard_to_buffer(char* buffer, unsigned long long size){
    unsigned long long i = 0;
    while(i<size-1){
        unsigned char s = inb(0x60);
        if(!(s & 0x80)){
            buffer[i]=scancode_to_ascii(s);
            i++;
            if(buffer[i-1] == '\n'){ buffer[i-1] = 0; return; }
        }
    }
}