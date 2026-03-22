# dir
KERNEL_DIR   = kernel/src
BOOT_DIR     = bootloader
BUILD        = $(KERNEL_DIR)/build
ESP          = $(BOOT_DIR)/esp/EFI/BOOT

# flags
KFLAGS  = -ffreestanding -fno-stack-protector -fno-pic -mno-red-zone -mno-mmx -mno-sse -mno-sse2 \
		  -I./kernel/include
BFLAGS  = -ffreestanding -fno-stack-protector -fpic -fshort-wchar -mno-red-zone \
          -I/usr/include/efi -I/usr/include/efi/x86_64 -DEFI_FUNCTION_WRAPPER

all: bootloader kernel

# boot
bootloader: $(ESP)/BOOTX64.EFI

$(ESP)/BOOTX64.EFI: $(BOOT_DIR)/boot.efi
	cp $< $@

$(BOOT_DIR)/boot.efi: $(BOOT_DIR)/boot.so
	objcopy \
		-j .text -j .sdata -j .data -j .dynamic \
		-j .dynsym -j .rel -j .rela -j .reloc \
		--target=efi-app-x86_64 $< $@

$(BOOT_DIR)/boot.so: $(BOOT_DIR)/boot.o
	ld -nostdlib -znocombreloc \
		-T /usr/lib/elf_x86_64_efi.lds \
		-shared -Bsymbolic \
		/usr/lib/crt0-efi-x86_64.o $< \
		-o $@ \
		-L/usr/lib -lefi -lgnuefi

$(BOOT_DIR)/boot.o: $(BOOT_DIR)/boot.c
	gcc $(BFLAGS) -c $< -o $@

# kernel
kernel: $(BUILD)/kernel.elf

$(BUILD)/kernel.elf: $(BUILD)/kernel.o $(BUILD)/memory.o $(BUILD)/tty.o $(BUILD)/gdt.o $(BUILD)/gdta.o
	ld -nostdlib -static -e main -Ttext 0x100000 $^ -o $@
	cp $@ $(BOOT_DIR)/esp/

$(BUILD)/kernel.o: $(KERNEL_DIR)/kernel.c
	mkdir -p $(BUILD)
	gcc $(KFLAGS) -c $< -o $@

$(BUILD)/memory.o: $(KERNEL_DIR)/memory.c
	gcc $(KFLAGS) -c $< -o $@

$(BUILD)/tty.o: $(KERNEL_DIR)/tty.c
	gcc $(KFLAGS) -c $< -o $@

$(BUILD)/gdt.o: $(KERNEL_DIR)/gdt.c
	gcc $(KFLAGS) -mgeneral-regs-only -c $< -o $@

$(BUILD)/gdta.o: $(KERNEL_DIR)/gdt.asm
	nasm -f elf64 $< -o $@

# wemu
run: all
	qemu-system-x86_64 \
		-bios /usr/share/ovmf/OVMF.fd \
		-drive format=raw,file=fat:rw:$(BOOT_DIR)/esp \
		-device isa-debug-exit,iobase=0x501,iosize=0x1

# usb flash
flash: all
# change sda1 to your actual usb. find it with lsblk
	sudo mount /dev/sda1 /mnt 	
	sudo mkdir -p /mnt/EFI/BOOT
	sudo cp $(BOOT_DIR)/boot.efi /mnt/EFI/BOOT/BOOTX64.EFI
	sudo cp $(BUILD)/kernel.elf /mnt/kernel.elf
	sudo umount /mnt

# clean
clean:
	rm -rf $(BUILD)
	rm -f $(BOOT_DIR)/boot.o $(BOOT_DIR)/boot.so $(BOOT_DIR)/boot.efi

.PHONY: all bootloader kernel run flash clean