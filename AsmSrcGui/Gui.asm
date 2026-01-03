; gui.asm (NASM x86_64, Windows)

default rel
global show_gui

extern MessageBoxA
extern ExitProcess

section .data
    title       db "NASM GUI", 0
    message     db "Press OK or Cancel", 0

    ok_title    db "Result", 0
    ok_msg      db "You pressed OK", 0

    cancel_msg  db "You pressed Cancel", 0

section .text
show_gui:
    sub rsp, 40                ; shadow space + alignment

    ; MessageBox(hwnd, text, caption, MB_OKCANCEL)
    xor rcx, rcx               ; HWND = NULL
    lea rdx, [message]         ; lpText
    lea r8,  [title]           ; lpCaption
    mov r9d, 1                 ; MB_OKCANCEL
    call MessageBoxA

    ; eax now contains button result
    cmp eax, 1                 ; IDOK?
    je  .pressed_ok

    cmp eax, 2                 ; IDCANCEL?
    je  .pressed_cancel

    jmp .exit

.pressed_ok:
    xor rcx, rcx
    lea rdx, [ok_msg]
    lea r8,  [ok_title]
    mov r9d, 0                 ; MB_OK
    call MessageBoxA
    jmp .exit

.pressed_cancel:
    xor rcx, rcx
    lea rdx, [cancel_msg]
    lea r8,  [ok_title]
    mov r9d, 0
    call MessageBoxA

.exit:
    xor ecx, ecx
    call ExitProcess
