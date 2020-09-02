

unsigned int *__find_function(void *hDll, unsigned long ApiHash);
int *__findkern32(void);

int *__findkern32(void) {
	int *a;

	__asm {
		xor ecx, ecx				//; set ecx to 0
		mov esi, fs:[ecx + 0x30]	//; esi = &(PEB) ([FS:0x30])
		mov esi, [esi + 0x0C]		//; esi = PEB->Ldr
		mov esi, [esi + 0x1C]		//; esi = PEB->Ldr.InInitOrder
	next_module:
		//;mov ebp, [esi + 0x08]		//; ebp = InInitOrder[X].base_address - original
		mov eax, [esi + 0x08]		//; ebx = InInitOrder[X].base_address - modified to put in ebx
		mov edi, [esi + 0x20]		//; ebp = InInitOrder[X].module_name (unicode)
		mov esi, [esi]                  
		cmp [edi + 0x18], cx		//; aniway fix for compatibility with win2k modulename[12] == 00 ?
		jne next_module       
		mov a, eax
	}

	return(a);
}

unsigned int *__find_function(void *hDll, unsigned long ApiHash) { //no funciona
	unsigned int *func;
	unsigned long hash = ApiHash;

	__asm {
		mov   eax, hDll
		mov   edx, [eax + 0x78] ; Export table relative offset
		add   edx, eax                
		mov   ecx, [edx + 0x18]       
		mov   ebx, [edx + 0x20]       
		add   ebx, eax     
	find_function_loop:
		jecxz find_function_finished  ; Jump to the end if ecx is 0
		dec   ecx                     
		mov   esi, [eax + ecx * 4]    
		add   esi, eax     	
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
		cmp   edi, ApiHash      
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
		mov func, eax

	}

	return(func);
}