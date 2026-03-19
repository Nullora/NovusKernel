# NovusKernel
This isn't even a functional kernel yet, it's just the bootloader that im proud of! 
- dev.to artice [here](https://dev.to/nullora/i-made-my-own-bootloader-at-16-it-was-horrible-it-was-worth-it-2nc1). Go check it out for more info!

<img width="2880" height="2160" alt="image" src="https://github.com/user-attachments/assets/8a876d4b-30ff-4bd2-bb52-2120ed9fc93b" />

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
# 
- Fixed shitty init_heap() and added double bufferring
- Made draw_char() draw_string() draw_hex() and clear_screen()
- Made malloc() kinda sketchy to run on real hardware, optimized for qemu as of right now.
- Made init_heap()
- Made memset() and changed file organization.
- Made my own memcpy() to quickly copy from backbuffer to screen buffer to reduce waterfall effect which is not fully removed yet.
