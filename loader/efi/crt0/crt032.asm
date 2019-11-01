;
;	Copyright (c) 2013 Sirius Corporation
;	Nelson Sapalo da Siva Cole
;	Lubango, 29 de Julho de 2019 - Hora: 02h32
;	File Name: crt032.asm
;


;	Inicializar um UEFI_Loader IA32 (i386)
;	Handoff State:
;	ESP + 8 – EFI_SYSTEM_TABLE*
; 	ESP + 4 – EFI_HANDLE
;	ESP - <return address>


bits 32

section .text
global _start
extern _efi_main  ;same defined reference in PE+ object
_start:

	; i386
	mov ebx, [esp+8] 	;EFI_SYSTEM_TABLE*
	mov eax, [esp+4] 	;EFI_HANDLE
	mov ecx,[esp]
	mov dword[_pp],ecx
	
	push ebx
	push eax
	call _efi_main
	add esp,8
	
	ret
	
	
global _OS_LoaderI32
_OS_LoaderI32:
    mov eax,[esp+4]
	mov ebx,[esp+8]
	
	cli
	push ebx
	push ss
	push esp
	pushf
	push cs
    push eax
	iretd



section .reloc

section .data
global _pp
_pp dd 0