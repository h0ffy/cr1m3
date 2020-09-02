
[BITS 32]


section .text

global _resolve_api_hash


_resolve_api_hash:
	push ebp
	mov ebp, esp
	pusha
	xor eax, eax
	mov edx, [ebp+8]
	mov ecx, [ebp+0x0c]
	cmp ecx, eax
	jnz short resolve_isqual 	
	mov edi, edx

resolve_again:
	scasb
	jnz short resolve_again
	dec edi
	mov ecx, edi
	sub ecx, edx

resolve_isqual:
	not eax

resolve_compute:
	xor al, [edx]
	inc edx
	mov bl, 8
	

resolve_compute_again:
	shr eax, 1
	jnb short resolve_end
	xor eax, 0x0ED888320
	
resolve_end:
	dec bl
	jnz short resolve_compute_again
	loop resolve_compute
	not eax
	mov [esp+0x20+(-4)], eax
	popa
	leave
	retn 8	
