void main() {
    __asm__ volatile ("outb %0, %1" : : "a"((unsigned char)0x42), "Nd"((unsigned short)0x501));
    for(;;);
}