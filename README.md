# NovusKernel
A 64-bit x86 kernel built from scratch in C with no standard library, loaded by a custom UEFI bootloader. (Debugging was literal hell) (This is made by a 16yr old with 0 formal background in CS, don't expect much!)

<img width="887" height="318" alt="image" src="https://github.com/user-attachments/assets/17b9d958-2302-4620-bb0a-50e9489caa2c" />

# Usage
- Run:
```c
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
As this is super early dev, you can easily find simple bugs and fix them. Not only do you get familiar with kernel dev if you're just starting, but you also help me out a ton! kernel code can be found at **/kernel/** in the repo. It is split into multiple files. Scroll to **Known issues**, it is split to easy and hard categories. If you're new, start with the easy, it's a reliable way to learn!
# What works
- IDT table passed to CPU, even closer to keyboard input. (the table is working its just that i was stupid and didnt have a stack)
- GDT table passed to CPU, future interupts. Prepping for keyboard input.
- Custom UEFI bootloader with ELF64 loader
- Physical memory detection with UEFI memory map
- Free list heap allocator (malloc/free)
- Bitmap TTY (draw_char, draw_string, clear_screen)
- Custom memcpy and memset
# Known issues (hard)
No known issues as of right now ;)
# Known issues (easy)
No easy known issues as of right now ;(