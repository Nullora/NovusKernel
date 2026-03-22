# Contributing to NovusKernel
Thanks for your interest in contributing! NovusKernel is a 64-bit x86 kernel built from scratch in C with a custom UEFI bootloader. Whether you’re new to OS development or just want to help improve documentation, you’re welcome here. Every contribution counts!

# 1. How to Set Up the Project

Clone the repo and build it:
```shell
git clone https://github.com/Nullora/NovusKernel.git
cd NovusKernel
```
```shell
make clean      # Clean previous build files
make            # Build the kernel and bootloader
make run        # Run it in QEMU
make flash      # Flash onto USB (use with caution)
```
- WARNING: The bootloader and kernel have been tested on real hardware. Running them on your machine may cause problems. QEMU is recommended for testing.

# 2. Where to Start
Look inside the /kernel/ directory.
Do not start in kernel.c, as that’s just a playground for testing.
Good starting points: memory.c, tty.c, gdt.c, etc.

# 3. Good First Issues

If you’re new to os dev, start with small tasks like:

- Adding comments to memory.c or tty.c functions
- Fixing typos in code or README
- Adding small utility functions or helpers

# 4. How to Contribute Code

- Make your changes in small, testable pieces.
- Build and test your changes using QEMU (make run).
- Include proof of testing:
- Screenshots of QEMU output
- Optional: GIFs or video if it’s a visual feature
- Submit a pull request, referencing the issue number (if any).
Wait for review, I respond quickly!

Even small contributions like documentation improvements are appreciated!!

# 5. Roadmap / Future Goals

Some of the upcoming features I plan to work on:

- Keyboard input handling
- Timer interrupts
- Paging / virtual memory
- Simple CLI / shell
- Basic file system support
- Additional TTY / display improvements

Contributors can pick tasks from this list or suggest their own ideas.

# 6. Recognition
All contributors will be added to Contributors.md
Top contributions may be featured on Reddit / DEV.to posts

Your name will be credited, everyone’s help counts!

# 7. Communication

If you need help:

- Comment on GitHub Issues
- Send a message via Reddit (u/nullora0)

I reply quickly and im more than happy to guide new contributors.
