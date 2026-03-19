#include"memory.h"


//writing my own memcpy :c
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