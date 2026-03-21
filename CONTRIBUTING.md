# Contributions
As this is super early dev, you can easily find simple bugs and fix them. Not only do you get familiar with kernel dev if you're just starting, but you also help me out a ton! kernel code can be found at **/kernel/** in the repo. It is split into multiple files. Scroll to **Known issues**, it is split categorized as easy and hard. If you're new, start with the easy, it's a reliable way to learn os dev and working with a team!
# How to setup the project
Setting up the project is extremely simple! Just run these:
```c
make clean // clean existing build files
make // build the kernel and bootloader
make run // to run on qemu
make flash // to flash onto USB incase you wanna try it on real hardware
```
# Where to start
Start by checking out the code itself. Not in kernel.c as thats just a testing playground for now. 
Check the other files like memory.c, tty.c, etc...
# How to contribute
You have to make sure the project builds and runs as intended. Do not open pull requests with code you didn't test.