     ;==========================================================================================
;
;	Copyright (c) 2013 Sirius Corporation
;	Nelson Sapalo da Siva Cole
;	Lubango, 27 de Outubro de 2019 - Hora: 18h03
;	File Name: vector.asm
;
;========================================================================================

bits 32
section .text
global _isr00,_isr01,_isr02,_isr03,_isr04,_isr05,_isr06,_isr07,_isr08,_isr09
global _isr10,_isr11,_isr12,_isr13,_isr14,_isr15,_isr16,_isr17,_isr18,_isr19
global _isr20,_isr21,_isr22,_isr23,_isr24,_isr25,_isr26,_isr27,_isr28,_isr29
global _isr30,_isr31


extern _fault_exception
isr_jmp:
	pushad
	push ds
	push es
	push fs
	push gs
    push ss
	mov eax,[esp+52]	; pega vector number
	push eax
	mov eax,0x10
	mov ds,ax
	mov es,ax
	mov fs,ax
	mov gs,ax

	call _fault_exception
	pop eax
	
    pop ss
	pop gs
	pop fs
	pop es
	pop ds
	popad	
	add esp,8
	iretd
_isr00:
	push dword 0
	push dword 0
	jmp isr_jmp
_isr01:
	push dword 0
	push dword 1
	jmp isr_jmp
_isr02:
	push dword 0
	push dword 2
	jmp isr_jmp
_isr03:
	push dword 0
	push dword 3
	jmp isr_jmp
_isr04:
	push dword 0
	push dword 4
	jmp isr_jmp
_isr05:
	push dword 0
	push dword 5
	jmp isr_jmp
_isr06:
	push dword 0
	push dword 6
	jmp isr_jmp
_isr07:
	push dword 0
	push dword 7
	jmp isr_jmp
_isr08:
	;error code
	push dword 8
	jmp isr_jmp
_isr09:
	push dword 0
	push dword 9
	jmp isr_jmp
_isr10:
	;error code
	push dword 10
	jmp isr_jmp
_isr11:
	;error code
	push dword 11
	jmp isr_jmp
_isr12:
	;error code
	push dword 12
	jmp isr_jmp
_isr13:
	;error code
	push dword 13
	jmp isr_jmp
_isr14:
	;error code
	push dword 14
	jmp isr_jmp
_isr15:
	push dword 0
	push dword 15
	jmp isr_jmp
_isr16:
	push dword 0
	push dword 16
	jmp isr_jmp
_isr17:
	;error code
	push dword 17
	jmp isr_jmp
_isr18:
	push dword 0
	push dword 18
	jmp isr_jmp
_isr19:
	push dword 0
	push dword 19
	jmp isr_jmp
_isr20:
	push dword 0
	push dword 20
	jmp isr_jmp
_isr21:
	push dword 0
	push dword 21
	jmp isr_jmp
_isr22:
	push dword 0
	push dword 22
	jmp isr_jmp
_isr23:
	push dword 0
	push dword 23
	jmp isr_jmp
_isr24:
	push dword 0
	push dword 24
	jmp isr_jmp
_isr25:
	push dword 0
	push dword 25
	jmp isr_jmp
_isr26:
	push dword 0
	push dword 26
	jmp isr_jmp
_isr27:
	push dword 0
	push dword 27
	jmp isr_jmp
_isr28:
	push dword 0
	push dword 28
	jmp isr_jmp
_isr29:
	push dword 0
	push dword 29
	jmp isr_jmp
_isr30:
	push dword 0
	push dword 30
	jmp isr_jmp
_isr31:
	push dword 0
	push dword 31
	jmp isr_jmp
	




global _lvt0

extern _lvt_function
lvt_jmp:
	pushad
	push ds
	push es
	push fs
	push gs
    push ss
	mov eax,[esp+52]	; pega vector number
	push eax
	mov eax,0x10
	mov ds,ax
	mov es,ax
	mov fs,ax
	mov gs,ax

	call _lvt_function
	
	pop eax
	
    pop ss
	pop gs
	pop fs
	pop es
	pop ds
	popad	
	add esp,8
	iretd

_lvt0:
	push dword 0
	push dword 32
	jmp lvt_jmp
	