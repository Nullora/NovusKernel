global load_gdt
global load_idt
load_gdt:         
    lgdt [rdi]       ; load gdt
    ret
load_idt:
    lidt [rdi]       ; load idt
    ret
section .note.GNU-stack noalloc noexec nowrite progbits     ; i have no idea what this does