/*
	Educational purposes only
	GPL LICENSE:  @Cr1m3 / JennyLab
	Win32/cr1m3.tr0jan
*/

#ifndef SYSCALL_H
	unsigned long __syscallstub(int syscall);
	int __sys0x25_NTCreateFile(void	**FileHandle, ACCESS_MASK DesiredAccess, POBJECT_ATTRIBUTES ObjectAttributes, PIO_STATUS_BLOCK   IoStatusBlock, PLARGE_INTEGER AllocationSize, ULONG FileAttributes, ULONG ShareAccess, unsigned long CreateDisposition, unsigned long CreateOptions, void *EaBuffer, unsigned long EaLength);
	

#endif
