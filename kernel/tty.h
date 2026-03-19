#ifndef FONT_H
#define FONT_H
#include"memory.h"
//vars
extern char font[128][8];
//funcs
void draw_char(char c, int x, int y, unsigned int color, BootInfo* bootinfo, unsigned int* buffer);
void draw_string(char* c, unsigned int x, unsigned int y,unsigned int color, BootInfo* bootinfo, void* buffer);
void clear_screen(unsigned int color, BootInfo* bootinfo, unsigned int* buffer);
void draw_hex(unsigned long long n, unsigned int x, unsigned int y, unsigned int color, BootInfo* bootinfo, void* buffer);

#endif