
section .text
    global _x64Gate
     

_x64Gate:
    pop eax
    jmp 0x33:$+0x07
    dec eax
    sub esp, 0x18
    dec eax
    mov dword [esp+0x10], 0x23
    dec eax
    mov [esp+0x08], eax
    dec eax
    mov [esp+0x00], ebp
    dec eax
    mov ebp, esp
    leave
    dec eax
    retf