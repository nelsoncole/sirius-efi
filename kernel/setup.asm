;
;	Copyright (c) 2013 Sirius Corporation
;	Nelson Sapalo da Siva Cole
;	Lubango, 20 de Setembro de 2019 - Hora: 20h05
;	File Name: setup.asm
;

bits 32
section .text
extern __main  ;same defined reference in PE+ object
global _start
_start:

	; i386
	push ebx
	call __main
	add esp,4
	
L1:
	hlt
	jmp L1;
	
extern _stack
global _gdt_flush
global _idt_flush

_gdt_flush:
	push ebp
	mov ebp,esp
	
	lgdt [gdtr]
    jmp 0x8:.flush_
.flush_:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
	mov ss, ax
	mov esp,_stack
	
	mov esp,ebp
	pop ebp
	ret

	
_idt_flush:	
	
	push ebp
	mov ebp,esp
	
    lidt [idtr]
	
	mov esp,ebp
	pop ebp
    ret

section .data
gdt_:

;0x0 Entrada Nula, em um GDT a primeira entrada é sempre nula

	dw 0		; Limit
	dw 0		; Base 15:00
	db 0		; Base 23:16
	db 0		; Flags
	db 0		; Flags e Limit 19:16
	db 0		; Base 31:24

; 0x8 CS LIMIT 0xFFFFF, BASE 0x00000000, DPL=0, G=1, S=1 code ou data

	dw 0xFFFF   	; Limit
	dw 0        	; Base 15:00
	db 0        	; Base 23:16
	db 0x9A     	; Flags
	db 0xCF     	; Flags e Limit 19:16
	db 0	    	; Base 31:24
	

; 0x10 DS LIMIT 0xFFFFF, BASE 0x00000000, DPL=0, G=1, S=1 code ou data

	dw 0xFFFF	; Limit
	dw 0		; Base 15:00
	db 0		; Base 23:16
	db 0x92	  	; Flags
	db 0xCF        	; Flags e Limit 19:16
	db 0           	; Base 31:24

;0x18 ;SEGMENTO DE CODIGO (CS 16-BITS) DPL 0, LIMIT 0XFFFF BASE 0X00000000 G 0 1B

	dw 0xFFFF
	dw 0x0
	db 0x0
	db 0x9E
	db 0x0
	db 0x0

;0x20 SEGMENTO DE DADOS (CD 16-BITS)  LIMIT 0XFFFF BASE 0X00000000 G 0 1B

	dw 0xFFFF
	dw 0x0
	db 0x0
	db 0x92
	db 0x0
	db 0x0


gdt_end:
	
extern _gdt
gdtr:
	dw 256*8 -1	; LIMIT
	dd gdt_		; BASE

extern _idt
idtr:
	dw 256*8 - 1
	dd _idt

section .bss
	resq 1024*16 ;128 KB
_stack: