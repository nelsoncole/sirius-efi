/**
 *	Copyright (c) 2013 Sirius Corporation
 *	Nelson Sapalo da Siva Cole
 *	Lubango, 12 de Outubro de 2019 - Hora: 21h30
 *	File Name: os.c
 **/
 
 
#include <os.h>

#define io_delay() __asm__ __volatile__("out %%al,$0x80"::)

VOID wait_ns(UINTN count)
{
	count /=100;	 
	while(--count)io_delay();
}


//  MSR
UINTN 
getmsr(UINT32 msr, UINT32 *low, UINT32 *hight)
{
	__asm__ __volatile__("rdmsr":"=a"(*low),"=d"(*hight):"c"(msr));
	return 0;
}

UINTN 
setmsr(UINT32 msr, UINT32 low, UINT32 hight)
{
	__asm__ __volatile__("wrmsr": :"a"(low),"d"(hight),"c"(msr));
	return 0;
}

VOID 
cli()
{
	__asm__ __volatile__("cli");
}

VOID 
sti()
{
	__asm__ __volatile__("sti");
}