/**
 *	Copyright (c) 2013 Sirius Corporation
 *	Nelson Sapalo da Siva Cole
 *	Lubango, 21 de Setembro de 2019 - Hora: 15h38
 *	File Name: console.c
 **/

#include <os.h>
#include "stdarg.h"

#if defined(__x86_64__) || defined(__aarch64__)
	#define	INT_MAX 0x7fffffffffffffff // -------	// max value of an "int"
	#define HEX_LEN 16
	
#elif defined(__i386__) || defined(__arm__)
	#define	INT_MAX	0x7fffffff // 2147483647	// max value of an "int"
	#define HEX_LEN 8

#else
#error YOUR ARCH HERE
#endif
 
UINTN 
ClearScreen() {
	 return  0;
 }
 

UINTN 
SetAttribute(IN UINTN Foreground,IN UINTN Background) {
	return 0;

}

UINTN  
EnableCursor(IN BOOLEAN Visible) {
	return 0;
}

UINTN  
SetCursorPosition(IN UINTN Column,IN UINTN Row) {
	return 0;
}


static VOID atoi(INTN value, CHAR8* valuestring) {
  INTN min_flag;
  CHAR8 swap, *p;
  min_flag = 0;

  if (0 > value)
  {
    *valuestring++ = '-';
    value = -INT_MAX> value ? min_flag = INT_MAX : -value;
  }

  p = valuestring;

  do
  {
    *p++ = (CHAR8)(value % 10) + '0';
    value /= 10;
  } while (value);

  if (min_flag != 0)
  {
    ++*valuestring;
  }
  *p-- = '\0';

  while (p > valuestring)
  {
    swap = *valuestring;
    *valuestring++ = *p;
    *p-- = swap;
  }
}

static VOID i2hex(UINTN val, CHAR8* dest, INTN len)
{
	CHAR8* cp;
	char x;
	UINTN n;
	n = val;
	cp = &dest[len];
	while (cp > dest)
	{
		x = n & 0xF;
		n >>= 4;
		*--cp = x + ((x > (HEX_LEN+1)) ? 'A' - 10 : '0');
	}
    dest[len]='\0';
}


UINTN  
print(CONST CHAR8 *format,...) 
{

	UINTN rc = 0;
	

	VOID* ap;
	va_start (ap,format);
	INTN index = 0;	
	INTN d;
	INTN c;
	CHAR8 *s;
	CHAR8 buffer[256];
	
	CHAR8 string[256];
	CHAR8 *p_strig = string;

	setmem(p_strig,256,0);

	while ((*(CHAR8*)(format + index))/*format[index]*/)
	{
		switch ((*(CHAR8*)(format + index))/*format[index]*/)
		{
		case '%':
			++index;
			switch ((*(CHAR8*)(format + index))/*format[index]*/)
			{
			
				case 'C':
				case 'c':
				c = (CHAR8) va_arg (ap, INTN);
				*p_strig++ = c;
				break;
     
				case 'S':
				case 's':
				s = va_arg (ap, CHAR8*);
				while(*s)*p_strig++ = *s++;
				break;

				case 'd':
				case 'i':
				d = va_arg (ap, UINTN);
				atoi(d, buffer);
				s = (CHAR8*)buffer;
				while(*s)*p_strig++ = *s++;
				break;

				case 'X':
				case 'x':
				d = va_arg (ap, INTN);
				i2hex(d, buffer,HEX_LEN);
				s = (CHAR8*)buffer;
				while(*s)*p_strig++ = *s++;
				break;
			
				default:
				*p_strig++ = '%';
				*p_strig++ = '%';
				break;
				
			}
			break;

		default:
		c = (*(CHAR8*)(format + index));/*format[index]*/
		
		*p_strig++ = c;
		
		break;
		}
		++index;
    }
	
	
	outputstring(string);
	return rc;
}














