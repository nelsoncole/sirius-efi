:	Copyright (c) 2013 Sirius Corporation
:	Nelson Sapalo da Siva Cole
:	Lubango, 20 de Setembro de 2019 - Hora: 20h47
:	File Name: build.bat

SET NASM=nasm -O0
SET GCC=gcc
SET CFLAGS= -Wall -O0 -m32 -std=c11 -ffreestanding -fshort-wchar -funroll-loops ^
-fomit-frame-pointer -ffast-math -Wextra -Wno-pointer-to-int-cast -Wno-int-to-pointer-cast ^
-nostdlib -nostdinc -I ./include

:Compile asm
NASM -f win32 setup.asm
NASM -f win32 vector.asm

:Compile c
GCC %CFLAGS% -c main.c
GCC %CFLAGS% -c os.c
GCC %CFLAGS% -c data.c
GCC %CFLAGS% -c dscptor.c
GCC %CFLAGS% -c exceptions.c
GCC %CFLAGS% -c string.c
GCC %CFLAGS% -c memory.c
GCC %CFLAGS% -c console.c
GCC %CFLAGS% -c gui/gui.c
GCC %CFLAGS% -c gui/font12x16.c
GCC %CFLAGS% -c cpuid.c
GCC %CFLAGS% -c apic.c
GCC %CFLAGS% -c lvt.c
GCC %CFLAGS% -c paging.c


:Objects
set MyObjs=setup.obj ^
vector.obj ^
main.o ^
os.o ^
data.o ^
dscptor.o ^
exceptions.o ^
string.o ^
memory.o ^
gui.o ^
font12x16.o ^
console.o ^
cpuid.o ^
apic.o ^
lvt.o ^
paging.o

:Linking
ld -m i386pe -T link.ld -V -o kernel.bin %MyObjs% -Map kernel.map


:remove
rm *.obj
rm *.o