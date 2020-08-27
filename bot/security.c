// funciones antidebugging etc..
#include <windows.h>
#include "security.h"




int __security_anti_debug(void) {

	__asm("mov %fs:(0x30), %rax");
	__asm("movb 2(%rax), %al");
	__asm("test %rax, %rax");
	__asm("je __detected");	
	__asm("mov 0x68(%rax), %rax");
	__asm("and 0x70, %rax");
	__asm("test %rax, %rax");
	__asm("jz __detected");

	return(0);
}

int __detected() {
	ExitProcess(0xFFFFFFFF);
}
 

	/*
// Enter in exception handler
#if defined(_MSC_VER)
        #if _WIN64 || __x86_64__
	__asm {
			pushad
			mov rsi, offset Handler
			push rsi
			push dword ptr fs:[0]
			mov dword ptr fs:[0], rsp
			call 0xC0FE1A7E600DF00D				

		Handler:
			mov rsp, [rsp+8]
			pop dword ptr fs:[0]
			add rsp, 8
			popad
			mov rax, 0xACABACABACABACAB
			mov rax, offset init_yeah2
			jmp rax
	}	
	#else
	__asm {
			pushad
			mov esi, offset Handler
			push esi
			push dword ptr fs:[0]
			mov dowrd ptr fs:[0], esp
			call 0xC0F31A7E
		Handler:
			mov esp, [esp+8]
			pop dword ptr fs:[0]
			add esp, 4
			popad
			mov eax, offset init_yeah
			jmp eax

	}

	#endif
#else
	__asm("nop");	
#endif
*/







/* Return to malware code: */	
/*
#if defined(_MSC_VER)
	#if _WIN64 || __x86_64__
		__asm {
			mov rax, init_yeah
			add rax, 4
			push rax
			ret
		}
	#else
		__asm {
			mov eax, init_yeah
			add eax, 4
			push eax
			ret
		}
	#endif

#else
	#if _WIN64 || __x86_64__
		#if defined(__GNUC__)
			__asm(".att_syntax noprefix");
			__asm("mov $_init_yeah, %rax");
		#else
			__asm("mov $init_yeah, %rax");
		#endif

		__asm("add $4, %rax");
		__asm("push %rax");
		__asm("ret");

	#else
		#if defined(__GNUC__)
                        __asm("mov $_init_yeah, %eax");
                #else
                        __asm("mov $init_yeah, %eax");
                #endif
		
		__asm("add $4, %eax");
		__asm("push %eax");
		__asm("ret");
	#endif

#endif
	*/
