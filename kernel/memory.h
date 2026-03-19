#ifndef MEMORY_H
#define MEMORY_H
#include"boot.h"
//variables
extern unsigned long long heap_base;
extern unsigned long long heap_size;

//functions
void* memcpy(void* dest, void* src, unsigned long long n);
void* memset(void* dest, int value, unsigned long long n);
void init_heap(BootInfo* bootinfo);

#endif