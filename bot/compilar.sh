#!/bin/bash
rm -rf bin
rm -rf obj
mkdir obj
mkdir bin
x86_64-w64-mingw32-gcc -c security.c -o obj/security.o
x86_64-w64-mingw32-gcc -c command.c -o obj/command.o
x86_64-w64-mingw32-gcc -c http.c -o obj/http.o
x86_64-w64-mingw32-gcc -c misc.c -o obj/misc.o
x86_64-w64-mingw32-gcc -c base64.c -o obj/base64.o
x86_64-w64-mingw32-gcc -c process.c -o obj/process.o
x86_64-w64-mingw32-gcc -c inject.c -o obj/inject.o
x86_64-w64-mingw32-gcc -crypt32 -luser32 -lwininet main.c obj/process.o obj/inject.o obj/base64.o obj/misc.o obj/command.o obj/security.o obj/http.o -o bin/cr1me.exe

ls bin/cr1m3.exe
