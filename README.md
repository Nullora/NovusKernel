# NovusKernel
A 64-bit x86 kernel built from scratch in C with no standard library, loaded by a custom UEFI bootloader. (Debugging was literal hell) (This is made by a 16yr old with 0 formal background in CS, don't expect much!)

<img width="887" height="318" alt="image" src="https://github.com/user-attachments/assets/17b9d958-2302-4620-bb0a-50e9489caa2c" />

# Usage
- Run:
```c
// MAKE SURE TO RUN THESE IN THE ROOT DIRECTORY (/NovusKernel)
make // to build the project
make run // to run it on QEMU
make clean // clean build files
make flash // to flash it to an usb. Make sure to go in the makefile and modify the usb name.
```
# Warning
This bootloader and preset kernel work on my real hardware, it has been tested multiple times. 
It is reccomended to not run it on any real machine as it may break unpredictably and crash your computer. I trust my creation, you don't have to.

- This version worked on my real machine
# Contributions
Look at **CONTRIBUTING.md** for more information.
# What works
- IDT table passed to CPU, even closer to keyboard input. (the table is working its just that i was stupid and didnt have a stack)
- GDT table passed to CPU, future interupts. Prepping for keyboard input.
- Custom UEFI bootloader with ELF64 loader
- Physical memory detection with UEFI memory map
- Free list heap allocator (malloc/free)
- Bitmap TTY (draw_char, draw_string, clear_screen)
- Custom memcpy and memset