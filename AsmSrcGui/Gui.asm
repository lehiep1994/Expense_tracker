; gui.asm (NASM x86_64, Windows)

default rel
global show_gui

extern MessageBoxA

section .data
    title   db "NASM GUI", 0
    message db "Hello from NASM Assembly!", 0

section .text
show_gui:
    sub rsp, 40                ; shadow space + stack alignment

    xor rcx, rcx               ; HWND = NULL
    lea rdx, [message]         ; LPCSTR lpText
    lea r8,  [title]           ; LPCSTR lpCaption
    mov r9d, 0                 ; MB_OK

    call MessageBoxA

    add rsp, 40
    ret
