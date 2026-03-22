# NovusKernel
A 64-bit x86 kernel built from scratch in C with no standard library, loaded by a custom UEFI bootloader. (Debugging was literal hell) (This is made by a 16yr old with 0 formal background in CS, don't expect much!)

<img width="887" height="318" alt="image" src="https://github.com/user-attachments/assets/17b9d958-2302-4620-bb0a-50e9489caa2c" />

# Project Overview

NovusKernel is an educational kernel project showcasing low-level OS concepts, including:

- Custom UEFI bootloader with ELF64 loader
- IDT and GDT table setup
- Physical memory detection via UEFI memory map
- Free list heap allocator (malloc/free)
- Bitmap TTY (draw_char, draw_string, clear_screen)
- Custom memcpy and memset

# Usage
```bash
# make sure you are in the root directory (/NovusKernel)
make clean    # clean previous build files
make          # build kernel and bootloader
make r      # run in QEMU
make flash    # flash onto USB (MAKE SURE TO CHANGE VARIABLE <usb> TO YOUR USB NAME)
```
Or if you're using the .nub file (thanks if you're using it!)
```bash
nub c # clean previous build files
nub # build bootloader and kernel
nub r # run in QEMU
nub f # flash onto USB (MAKE SURE TO CHANGE VARIABLE <usb> TO YOUR USB NAME)
nub g # push to github (if youre planning to contribute or you forked the repo)
nub i # install all dependencies. might take a few seconds
```
And if you're not using NUB, you can find it [here!!!](https://github.com/Nullora/NUB)
# Warning
This bootloader and preset kernel work on my real hardware and has been tested multiple times. 
It is reccomended to not run it on any real machine as it may break unpredictably and crash your computer. I trust my creation, you don't have to.

- This version worked on my real machine
# Contributing & how to help
Look at **CONTRIBUTING.md** for more a detailed explanation.