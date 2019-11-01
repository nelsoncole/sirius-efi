/**
 *	Copyright (c) 2013 Sirius Corporation
 *	Nelson Sapalo da Siva Cole
 *	Lubango, 20 de Setembro de 2019 - Hora: 20h07
 *	File Name: link.ld
 **/
 
OUTPUT_FORMAT("pe-i386")
ENTRY(_start)
SECTIONS
{
	. = 0x101000;
	
	start = .;
	
	.text ALIGN(4K) : AT(ADDR(.text) - 0x100000)
	{
		*(.text .text.*)
	}
	
	.rodata ALIGN(4K) : AT(ADDR(.rodata) - 0x100000)
	{
		*(.rodata .rodata.*)
	}
	
	.data ALIGN(4K) : AT(ADDR(.data) - 0x100000)
	{
		*(.data .data.*)
	}
	
	.bss ALIGN(4K) : AT(ADDR(.bss) - 0x100000)
	{
		*(.bss .bss.*)
		*(COMMON)
	}
	
	end = .;
}