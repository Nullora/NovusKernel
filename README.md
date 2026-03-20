# NovusKernel
A 64-bit x86 kernel built from scratch in C with no standard library, loaded by a custom UEFI bootloader. (Debugging was literal hell) (This is made by a 16yr old with 0 formal background in CS, don't expect much!)

<img width="887" height="318" alt="image" src="https://github.com/user-attachments/assets/17b9d958-2302-4620-bb0a-50e9489caa2c" />

# Usage
Use my tool [NUB](https://github.com/Nullora/NUB) to run and test this and modify it comfortably in QeMu.
- After cloning, run **nub clean boot** in /bootloader/ then **nub make boot**.
- Same for /kernel/ but after **nub clean kernel** run **nub kernel kernel**. 
- Then go back to /bootloader/ and run **nub run boot**.
- To flash this onto a USB and boot from it (idk why ud do that) run **sudo nub flash boot** but make sure to check the NUB readme first, all found on my profile.
# Warning
This bootloader and preset kernel work on my real hardware, it has been tested multiple times. 
It is reccomended to not run it on any real machine as it may break unpredictably and crash your computer. I trust my creation, you don't have to.

- This version froze on my real machine. if you do wanna flash it, expect the same result.
# Contributions
As this is super early dev, you can easily find simple bugs and fix them. Not only do you get familiar with kernel dev if you're just starting, but you also help me out a ton! kernel code can be found at **/kernel/** in the repo. It is split into multiple files so I dont have one big fat blob of code in kernel.c
# What works
- Custom UEFI bootloader with ELF64 loader
- Physical memory detection with UEFI memory map
- Free list heap allocator (malloc/free)
- Bitmap TTY (draw_char, draw_string, clear_screen)
- Custom memcpy and memset
