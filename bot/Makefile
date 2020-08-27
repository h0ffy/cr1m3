CR1M3_HOME=C:\bot
CR1M3_INCS=C:\bot
CR1M3_LIBS=C:\bot
CR1M3_OBJ=$(CR1M3_HOME)

cr1m3build: inject.obj command.obj http.obj misc.obj base64.obj main.obj
	cl /o cr1m3.exe inject.obj command.obj http.obj misc.obj base64.obj main.obj /link 	

inject.obj: inject.c
	cl /c inject.c /TC -I $(CR1M3_INCS) 

command.obj: command.c
        cl /c command.c /TC -I $(CR1M3_INCS)

http.obj: http.c
        cl /c http.c /TC -I $(CR1M3_INCS)

misc.obj: misc.c
        cl /c misc.c /TC -I $(CR1M3_INCS)

base64.obj: base64.c
        cl /c base64.c /TC -I $(CR1M3_INCS)

main.obj: main.c
	cl /c main.c /TC -I $(CR1M3_INCS)



cr1m3build_banner:
	echo "Building cr1m3 trojan horse...."
	
all: cr1m3build_banner cr1m3build

clean:
	del *.obj
	del *.o
	del *.exe
	del obj\*.o
	del obj\*.obj


