/**
 *	Copyright (c) 2013 Sirius Corporation
 *	Nelson Sapalo da Siva Cole
 *	Lubango, 06 de Outubro de 2019 - Hora: 19h40
 *	File Name: cpuid.c
 **/
 
 
#include <os.h>

UINTN
cpuid_vendor(OUT CHAR8 *string)
{
	UINT32 *str_p = (UINT32*) string;
	
	__asm__ __volatile__("cpuid;":"=b"(str_p[0]),"=c"(str_p[2]),"=d"(str_p[1]):"a"(CPUID_GET_VENDOR_STRING));
	
	*(CHAR8*)((CHAR8*)str_p + 12) 	= 0;
	
	return 0;
}


UINTN 
cpuid_processor_brand(OUT CHAR8 *string)
{
	UINT32 *str_p = (UINT32*) string;
	__asm__ __volatile__("cpuid;":\
	"=a"(str_p[0]),"=b"(str_p[1]),"=c"(str_p[2]),"=d"(str_p[3]):\
	"a"(CPUID_GET_BRAND_STRING));
	
	__asm__ __volatile__("cpuid;":\
	"=a"(str_p[4]),"=b"(str_p[5]),"=c"(str_p[6]),"=d"(str_p[7]):\
	"a"(CPUID_GET_BRAND_STRING_MORE));
	
	__asm__ __volatile__("cpuid;":\
	"=a"(str_p[8]),"=b"(str_p[9]),"=c"(str_p[10]),"=d"(str_p[11]):\
	"a"(CPUID_GET_BRAND_STRING_END));
	
	
	return 0;
}

