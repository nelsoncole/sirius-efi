/**
 *	Copyright (c) 2013 Sirius Corporation
 *	Nelson Sapalo da Siva Cole
 *	Lubango, 19 de Setembro de 2019 - Hora: 09h30
 *	File Name: memory.c
 **/
 
 
#include <os.h>


UINTN zBUF = 0x02000000;

VOID *Malloc(UINTN Size) 
{
	UINTN addr = zBUF;
	zBUF += Size;
	
	return (VOID*) addr;
	
}


VOID Free(VOID *Buffer)
{
	
	
} 