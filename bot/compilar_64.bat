@echo off

set options = "-w -g -nostdlib -nostdinc -MD"
set tcc = "C:\tinyc\tcc64\tcc.exe"
set tiny_impdef = "C:\tinyc\tcc64\tiny_impdef.exe"

rmdir /Q /S obj\
rmdir /Q /S bin\
mkdir obj
mkdir bin

C:\tinyc\tcc64\tiny_impdef.exe %systemroot%\system32\wininet.dll -o C:\tinyc\tcc64\lib\wininet.def
C:\tinyc\tcc64\tiny_impdef.exe %systemroot%\system32\crypt32.dll -o C:\tinyc\tcc64\lib\crypt32.def
C:\tinyc\tcc64\tiny_impdef.exe %systemroot%\system32\advapi32.dll -o C:\tinyc\tcc64\lib\advapi32.def
C:\tinyc\tcc64\tiny_impdef.exe %systemroot%\system32\psapi.dll -o C:\tinyc\tcc64\lib\psapi.def

C:\tinyc\tcc64\tcc.exe %options% -c -o obj\command.o command.c
C:\tinyc\tcc64\tcc.exe %options% -c -o obj\security.o security.c
C:\tinyc\tcc64\tcc.exe %options% -c -o obj\http.o http.c
C:\tinyc\tcc64\tcc.exe %options% -c -o obj\misc.o misc.c
C:\tinyc\tcc64\tcc.exe %options% -c -o obj\base64.o base64.c
C:\tinyc\tcc64\tcc.exe %options% -c -o obj\inject.o inject.c
rem C:\tinyc\tcc\tcc.exe %options% -c -o obj\proc.o proc.c
C:\tinyc\tcc64\tcc.exe %options% -ladvapi32 -lpsapi -lcrypt32 -lwininet -luser32 -o bin\cr1m3_x64.exe main.c obj\inject.o obj\base64.o obj\misc.o obj\http.o obj\security.o obj\command.o

del *.o
echo COMPILED...
dir bin\cr1m3_x64.exe | findstr cr1m3_x64.exe
