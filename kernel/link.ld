/**
 *	Copyright (c) 2013 Sirius Corporation
 *	Nelson Sapalo da Siva Cole
 *	Lubango, 20 de Setembro de 2019 - Hora: 20h07
 *	File Name: link.ld
 **/
 
OUTPUT_FORMAT(pe-i386)
ENTRY(_start)
SECTIONS
{
	
	.text 0x101000: {
    code = .;
    *(.text)
	. = ALIGN(0x1000);
  }

  .data : {
     data = .;
     *(.data)
	 *(COMMON)
	 . = ALIGN(0x1000);
 
  }
   .rodata : {
     rodata = .;
     *(.rdata)
	 *(.rodata)
	 . = ALIGN(0x1000);
 
  }

  .bss : {
    bss = .;
    *(.bss)
	. = ALIGN(0x1000);
  }

  _end = .;
}