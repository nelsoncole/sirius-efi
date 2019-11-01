/**
 *	Copyright (c) 2013 Sirius Corporation
 *	Nelson Sapalo da Siva Cole
 *	Lubango, 18 de Agosto de 2019 - Hora: 21h20
 *	File Name: string.c
 **/

#include <efi.h>


VOID 
EFIAPI *CopyMem(IN VOID *Destination,IN VOID *Source,IN UINTN Length)
{	
	BS->CopyMem(Destination,Source,Length);
	return Destination;
}


VOID 
EFIAPI *SetMem(	IN VOID *Buffer,IN UINTN Size,IN UINT8 Value)
{
	BS->SetMem(Buffer,Size,Value);
	return Buffer;
}