default rel
global get_total
global get_saving
global add_saving
global load_from_file

section .data
total   dd 0
saving  dd 0

section .text

get_total:
    mov eax, [total]
    ret

get_saving:
    mov eax, [saving]
    ret

add_saving:
    add [saving], ecx
    ret

; --------------------------------------------------
; load_from_file
; C prototype: void load_from_file(int t, int s);
; calling convention (x64): RCX = t, RDX = s
; --------------------------------------------------
load_from_file:
    mov [total], ecx   ; Store first argument (total)
    mov [saving], edx  ; Store second argument (saving)
    ret