/**
 *	Copyright (c) 2013 Sirius Corporation
 *	Nelson Sapalo da Siva Cole
 *	Lubango, 18 de Agosto de 2019 - Hora: 21h20
 *	File Name: string.c
 **/

#include <os.h>

UINTN strlen(CONST CHAR8 *s)
{
	CHAR8 *tmp = (CHAR8*)s;
	while(*tmp != '\0')
	tmp++;
	return (UINTN)(tmp - s);
}



VOID  *copymem(IN VOID *Destination,IN VOID *Source,IN UINTN Length)
{	

	UINTN p    = Length;
	UINTN *p_dest = (UINTN*)Destination;
	UINTN *p_src  = (UINTN*)Source;
	
	p = p/4;
	
	if(Length %4) p++;

	if(Length < 4) {
       		__asm__ __volatile__("cld; rep; movsb;"::"D"(p_dest),\
        	"S"(p_src),"c"(p));
		return p_dest;

	}

       	__asm__ __volatile__("cld; rep; movsd;"::"D"(p_dest),\
        "S"(p_src),"c"(p));
		

	return p_dest;
}


VOID *setmem(IN VOID *Buffer,IN UINTN Size,IN UINT8 Value)
{
	UINT8 *tmp = (UINT8 *)Buffer;
	UINTN count = Size;
    for(; count != 0; count--) *tmp++ = Value;
	return Buffer;
}


CHAR8 *strcpy(CHAR8 *s1, CONST CHAR8 *s2)
{
    CHAR8 *p = (CHAR8*)s1;
    INTN i =0;
    while (s2[i] != '\0'){
    s1[i] = s2[i]; i++;
    }
    return p;
}
