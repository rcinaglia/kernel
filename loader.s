; Multiboot Header Constants
MAGIC_NUMBER equ 0x1BADB002
FLAGS        equ 0x0            ; Nessun FLAG
CHECKSUM     equ -MAGIC_NUMBER  ; Magic + checksum + flags = 0

; Sezione Multiboot
section .multiboot
align 4
    dd MAGIC_NUMBER
    dd FLAGS
    dd CHECKSUM

; Stack per C
KERNEL_STACK_SIZE equ 4096
section .bss
align 16
kernel_stack:
    resb KERNEL_STACK_SIZE


; LOADER (esegue appena carica il Kernel)
section .text
global loader
loader:
    mov esp, kernel_stack + KERNEL_STACK_SIZE   ; Alloca lo Stack
    mov eax, 0x00CA5500

    extern kmain
    call kmain


    .loop:
        jmp .loop
