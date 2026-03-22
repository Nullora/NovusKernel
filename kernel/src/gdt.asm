global load_gdt
global load_idt
global enable_interrupts
load_gdt:
    lgdt [rdi]
    pop rax          ; save return address
    push 0x08        ; CS  (pushed second = higher address)
    push rax         ; RIP (pushed first = lower address)
    retfq            ; pops RIP then CS — correct order now
load_idt:
    lidt [rdi]       ; load idt
    ret
enable_interrupts:   ; this causes a crazy triple fault on QEMU but somehow survives a real machine
    sti
    ret
section .note.GNU-stack noalloc noexec nowrite progbits     ; i have no idea what this does