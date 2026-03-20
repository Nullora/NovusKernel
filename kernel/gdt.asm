global load_gdt
load_gdt:         
    lgdt [rdi]       ; load gdt
    ret             
section .note.GNU-stack noalloc noexec nowrite progbits     ; i have no idea what this does