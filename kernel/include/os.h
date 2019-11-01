/**
 *	Copyright (c) 2013 Sirius Corporation
 *	Nelson Sapalo da Siva Cole
 *	Lubango, 21 de Setembro de 2019 - Hora: 08h47
 *	File Name: os.h
 **/
 
#ifndef __OS_H__
#define __OS_H__


#ifndef IN 	// Prototype argument decoration for EFI parameters to indicate their direction
    #define IN 	// IN - argument is passed into the function
    #define OUT	// OUT - argument (pointer) is returned from the function
    #define OPTIONAL	// OPTIONAL - argument is optional
#endif


#ifndef CONST
   #define CONST const
#endif
#ifndef TRUE
    #define TRUE    ((BOOLEAN) 1)
    #define FALSE   ((BOOLEAN) 0)
#endif

#ifndef NULL
    #define NULL    ((VOID *) 0)
#endif


#define A32_EFER_MSR 0xC0000080


#include "typ.h"
#include "cpuid.h"
#include "paging.h"
#include "gui.h"
#include "dscptor.h"
#include "apic.h"



// Externs
extern GUI *G;
extern GW_HAND	*Box;
//Globais
extern UINT16 font12x16[128*16];

// OS
VOID wait_ns(UINTN count);
VOID cli();
VOID sti();

// System
VOID gdt_install(VOID);
VOID idt_install(VOID);


//  MSR
UINTN 
getmsr(UINT32 msr, UINT32 *low, UINT32 *hight);
UINTN 
setmsr(UINT32 msr, UINT32 low, UINT32 hight);



// String
UINTN strlen(CONST CHAR8 *s);
VOID *copymem(IN VOID *Destination,IN VOID *Source,IN UINTN Length);
VOID *setmem(IN VOID *Buffer,IN UINTN Size,IN UINT8 Value);
CHAR8 *strcpy(CHAR8 *s1, CONST CHAR8 *s2);

VOID *Malloc(UINTN Size);
VOID Free(VOID *Buffer);

// console
UINTN 
SetAttribute(IN UINTN Foreground,IN UINTN Background);

UINTN  
print(CONST CHAR8 *format,...);



#endif