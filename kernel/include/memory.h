#ifndef MEMORY_H
#define MEMORY_H
#include"boot.h"
//variables
extern unsigned long long heap_base;
extern unsigned long long heap_size;
extern unsigned long long current_heap_pos;

//functions
void* memcpy(void* dest, void* src, unsigned long long n);
void* memset(void* dest, int value, unsigned long long n);
void init_heap(BootInfo* bootinfo);
void* malloc(unsigned long long x);
void free(void* x);
int strcmp(const char* a,const char* b);
int startswith(const char* s,const char* p);


#endif