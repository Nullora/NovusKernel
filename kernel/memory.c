#include"memory.h"
#include"boot.h"

unsigned long long heap_base;
unsigned long long heap_size;
unsigned long long current_heap_pos;
MemHeader* heap_start = 0;
void* memcpy(void* dest, void* src, unsigned long long n) {
    __uint128_t* d128 = dest;
    __uint128_t* s128 = src;
    unsigned long long i;
    
    for(i = 0; i < n/16; i++) {
        d128[i] = s128[i];
    }
    unsigned char* d = (unsigned char*)dest + (n/16)*16;
    unsigned char* s = (unsigned char*)src + (n/16)*16;
    for(unsigned long long j = 0; j < n%16; j++) {
        d[j] = s[j];
    }
    return dest;
}
void* memset(void* dest, int value, unsigned long long n){
    unsigned char* d = dest;
    for(unsigned long long i=0;i<n;i++){
        d[i]=value;
    }
    return dest;
}
void init_heap(BootInfo* bootinfo){
    heap_base = 0xDEADBEEF;
    unsigned long long pages=0;
    for(unsigned long long i=0;i<bootinfo->mMapSize/bootinfo->DescriptorSize;i++){
        //this line alone made me lose my mind for 30mins
        EFI_MEMORY_DESCRIPTOR* desc = (EFI_MEMORY_DESCRIPTOR*)((char*)bootinfo->memMap+i*bootinfo->DescriptorSize);
        if(desc->Type==7 && desc->NumberOfPages>pages){
            heap_size = desc->NumberOfPages*4096;
            heap_base = desc->PhysicalStart;
            pages = desc->NumberOfPages;
            }
        }
    current_heap_pos = heap_base;
}

//this was the single worst function i ever wrote in my fucking life
void* malloc(unsigned long long x){
    if(heap_start==0){
        MemHeader* b = (MemHeader*)current_heap_pos;
        b->block_size = x;
        b->usage = 1;
        b->next_header = 0;
        current_heap_pos += sizeof(MemHeader)+x;
        heap_start = b;
        return b+1;
    }
    else{
        MemHeader* b = heap_start;
        MemHeader* last_block = heap_start;
        while(b->next_header!=0){
            if(b->usage==0 && b->block_size>=x){
                current_heap_pos = (unsigned long long)b;
                b->usage=1;
                return b+1;
            }else{
                last_block = b;
                b = b->next_header;
            }
        }
        MemHeader* c = (MemHeader*)current_heap_pos;
        last_block->next_header = c;
        c->block_size = x;
        c->usage = 1;
        c->next_header = 0;
        current_heap_pos += sizeof(MemHeader)+x;
        return c+1;
    }
}
void free(void* x){
    MemHeader* y = (MemHeader*)x-1;
    y->usage = 0;
}