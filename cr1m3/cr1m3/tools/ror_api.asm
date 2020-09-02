
[BITS 32]


section .text

global _compute_hash


_compute_hash:
	mov esi, eax
        xor   edi, edi
        xor   eax, eax
        cld
compute_hash_again:
        lodsb
        test  al, al
        jz    compute_hash_finished   ; ZF = 0 flag verify
        ror   edi, 0x4a                ; ror crypto key in this case (0x1d)
        add   edi, eax
        jmp   compute_hash_again
compute_hash_finished:
	mov eax, edi
	ret
