:	Copyright (c) 2013 Sirius Corporation
:	Nelson Sapalo da Siva Cole
:	Lubango, 29 de Julho de 2019 - Hora: 02h40
:	File Name: build.bat

SET NASM=nasm
SET GCC=x86_64-w64-mingw32-gcc
SET CFLAGS= -O0 -Wall -m32 -std=c11 -ffreestanding -fshort-wchar -funroll-loops ^
-fomit-frame-pointer -ffast-math -Wextra -Wno-pointer-to-int-cast -Wno-int-to-pointer-cast ^
-nostdlib -nostdinc -I ./efi/include

:Compile asm
NASM -f win32 efi/crt0/crt032.asm

:Compile c
:efi-app
GCC %CFLAGS% -c efi_main.c

:lib
GCC %CFLAGS% -c efi/lib/data.c
GCC %CFLAGS% -c efi/lib/init.c
GCC %CFLAGS% -c efi/lib/memory.c
GCC %CFLAGS% -c efi/lib/paging.c
GCC %CFLAGS% -c efi/lib/console.c
GCC %CFLAGS% -c efi/lib/media.c
GCC %CFLAGS% -c efi/lib/string.c
GCC %CFLAGS% -c efi/lib/gui/gui.c
GCC %CFLAGS% -c efi/lib/gui/font.c
GCC %CFLAGS% -c efi/lib/gui/font12x16.c


:Moving objects
move efi\crt0\*.obj objs
move *.o objs

:Objects
set MyObjs=objs/crt032.obj ^
objs/data.o ^
objs/init.o ^
objs/memory.o ^
objs/paging.o ^
objs/console.o ^
objs/media.o ^
objs/string.o ^
objs/gui.o ^
objs/font.o ^
objs/font12x16.o ^
objs/efi_main.o

:Linking, create PE+ subsystem = EFI_APPLICATION
GCC -m32 -nostdlib -nostdinc -Wl,--subsystem,10 -e _start -o bootia32.efi %MyObjs% -lgcc
move bootia32.efi ../bin

:removing objects
rm objs/*.o

GOTO :EOF
call :MountVHD


GOTO :EOF

:MountVHD
DiskPart /s build.tmp > build.err
IF EXIT(
		
			
) ELSE (

	
			 )


:EOF


:qemu-system-x86_64 -nic none -vga std -cpu qemu64 -bios share/OVMF.fd -drive file="SIRIUS BLACK.vhd",format=raw