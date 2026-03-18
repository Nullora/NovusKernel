# NovusKernel
This isn't even a function kernel yet, it's just the bootloader that im proud of! 
- dev.to artice [here](https://dev.to/nullora/i-made-my-own-bootloader-at-16-it-was-horrible-it-was-worth-it-2nc1). Go check it out for more info!
# Usage
Use my tool NUB (on my github) to run and test this and modify it comfortably in QeMu.
- After cloning, run **nub clean boot** in /bootloader/ then **nub make boot**.
- Same for /kernel/ but after **nub clean kernel** run **nub kernel kernel**. 
- Then go back to /bootloader/ and run **nub run boot**.
- To flash this onto a USB and boot from it (idk why ud do that) run **sudo nub flash boot** but make sure to check the NUB readme first, all found on my profile.
# Note
This bootloader and preset kernel works on my real hardware, it has been tested multiple times. 
It is reccomended to not run it on any real machine as it may break unpredictably. I trust my creation, you don't have to.
# Thanks
Thanks to my previous tools Ndeploy and NUB for making this soo much easier, without those this wouldve taken an extra week
# WARNING
If you have tested this on you QeMu and ran into QeMu instantly closing, thats supposed to happen, it's in the kernel code.
It's just me testing if it successfully jumps from bootloader to kernel.
