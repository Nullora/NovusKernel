# NovusKernel
Barely functional kernel. Loaded by my custom bootloader NBL. Debugging this was legit hell on earth.
- dev.to artice [here](https://dev.to/nullora/i-made-my-own-bootloader-at-16-it-was-horrible-it-was-worth-it-2nc1). Go check it out for more info!

<img width="887" height="318" alt="image" src="https://github.com/user-attachments/assets/17b9d958-2302-4620-bb0a-50e9489caa2c" />

# Usage
Use my tool NUB (on my github) to run and test this and modify it comfortably in QeMu.
- After cloning, run **nub clean boot** in /bootloader/ then **nub make boot**.
- Same for /kernel/ but after **nub clean kernel** run **nub kernel kernel**. 
- Then go back to /bootloader/ and run **nub run boot**.
- To flash this onto a USB and boot from it (idk why ud do that) run **sudo nub flash boot** but make sure to check the NUB readme first, all found on my profile.
# Warning
This bootloader and preset kernel work on my real hardware, it has been tested multiple times. 
It is reccomended to not run it on any real machine as it may break unpredictably and crash your computer. I trust my creation, you don't have to.
- This version worked on my real machine.
# Contributions
As this is super early dev, you can easily find simple bugs and fix them. Not only do you get familiar with kernel dev if you're just starting, but you also help me out a ton! kernel code can be found at **/kernel/** in the repo. It is split into multiple files so I dont have one big fat blob of code in kernel.c
# Updates
- free() now actually does something.
- malloc() upgraded to free-list allocator.
- Fixed shitty init_heap() and added double bufferring
- Made draw_char() draw_string() draw_hex() and clear_screen()
- Made malloc() kinda sketchy to run on real hardware, optimized for qemu as of right now.
- Made init_heap()
- Made memset() and changed file organization.
- Made my own memcpy() to quickly copy from backbuffer to screen buffer.
