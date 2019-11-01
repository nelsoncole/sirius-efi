/**
 *	Copyright (c) 2013 Sirius Corporation
 *	Nelson Sapalo da Siva Cole
 *	Lubango, 06 de Outubro de 2019 - Hora: 19h39
 *	File Name: cpuid.h
 **/
 
#ifndef __CPUID_H__
#define __CPUID_H__

enum {
	
	// Basic CPUID Information
	CPUID_GET_VENDOR_STRING,
	CPUID_GET_FEATURES,
	CPUID_GET_TLB,
	CPUID_GET_SERIAL,
	// Extended Function CPUID Information
	CPUID_GET_EXTENDED = 0x80000000,
	CPUID_GET_EXTENDED_FEATURES,
	CPUID_GET_BRAND_STRING,
	CPUID_GET_BRAND_STRING_MORE,
	CPUID_GET_BRAND_STRING_END
	
	
	
}CPUID_REQUEST;


UINTN 
cpuid_vendor(OUT CHAR8 *string);
UINTN 
cpuid_processor_brand(OUT CHAR8 *string);


#endif



// Volume 2: Instruction Set Reference, A-Z p471, Volume 3 p2701, Volume 4: Model-Specific Registers p4413