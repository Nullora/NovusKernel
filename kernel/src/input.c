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
void record_keyboard_to_buffer(char* buffer, char letter, int* i){
    buffer[*i]=letter;
    (*i)++;
    buffer[*i]='\0';
    if(letter == '\n'){
        *i=0;
    }
}