// port 0x501 is QEMU debug exit port
static inline void outb(unsigned short port, unsigned char val) {
    __asm__ volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}

void main() {
    outb(0x501, 0x42); // QEMU will exit with code (0x42 << 1) | 1

    char *vga = (char *)0xB8000;
    vga[0] = 'A';   // character
    vga[1] = 0x0F;  // color: white on black
    for(;;);
}