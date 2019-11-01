/**
 *	Copyright (c) 2013 Sirius Corporation
 *	Nelson Sapalo da Siva Cole
 *	Lubango, 21 de Setembro de 2019 - Hora: 08h45
 *	File Name: typ.h
 **/
 
#ifndef __TYP_H__
#define __TYP_H__

	
// Common UEFI data types
typedef char BOOLEAN;
typedef int INTN;
typedef unsigned UINTN;

typedef char INT8;
typedef unsigned char UINT8;

typedef short INT16;
typedef unsigned short UINT16; 
 
typedef signed long INT32;
typedef unsigned long UINT32;

typedef signed long long INT64;
typedef unsigned long long UINT64;

//typedef signed INT128;
//typedef unsigned UNT128;

typedef char  CHAR8;
typedef short unsigned int CHAR16;

typedef void VOID;

typedef struct {
	UINT16 	cs;
	UINT16 	ds;
	UINT16	es;
	UINT16 	ss;
	UINT16	fs;
	UINT16	gs;
	UINTN 	a;
	UINTN 	b;
	UINTN 	c;
	UINTN 	d;
	
}REG;



#endif