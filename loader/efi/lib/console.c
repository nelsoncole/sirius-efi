/**
 *	Copyright (c) 2013 Sirius Corporation
 *	Nelson Sapalo da Siva Cole
 *	Lubango, 4 de Agosto de 2019 - Hora: 23h10
 *	File Name: console.c
 **/

#include <efi.h>


/*
 *
 *
 *
 *
 *
 *  Output Protocol
 *
 *
 *
 *
 */
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
 
EFI_STATUS 
EFIAPI ClearScreen() {
	 return  ST->ConOut->ClearScreen(ST->ConOut);
 }
 
EFI_STATUS 
EFIAPI OutputString(IN CHAR16 *String) {
	return ST->ConOut->OutputString(ST->ConOut,String);
}

EFI_STATUS 
EFIAPI SetAttribute(IN UINTN Foreground,IN UINTN Background) {
	return ST->ConOut->SetAttribute(ST->ConOut,EFI_TEXT_ATTR(Foreground,Background));
}

EFI_STATUS 
EFIAPI EnableCursor(IN BOOLEAN Visible) {
	return ST->ConOut->EnableCursor(ST->ConOut,Visible);
}

EFI_STATUS 
EFIAPI SetCursorPosition(IN UINTN Column,IN UINTN Row) {
	return ST->ConOut->SetCursorPosition(ST->ConOut,Column,Row);
}


static VOID atoi(INTN value, CHAR16* valuestring) {
  INTN min_flag;
  CHAR16 swap, *p;
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

static VOID i2hex(UINTN val, CHAR16* dest, INTN len)
{
	CHAR16* cp;
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
    dest[len+1]='\0';
}


EFI_STATUS 
EFIAPI PrintF(CHAR16 *format,...) {

	EFI_STATUS status = 0;
	CHAR16 CH[2];
	CH[1] = 0;
	

	VOID* ap;
	va_start (ap,format);
	INTN index = 0;	
	INTN d;
	CHAR16 c;
	CHAR16 *s;
	CHAR16 buffer[0xff];


	while ((*(CHAR16*)(format + index))/*format[index]*/)
	{
		switch ((*(CHAR16*)(format + index))/*format[index]*/)
		{
		case '%':
			++index;
			switch ((*(CHAR16*)(format + index))/*format[index]*/)
			{
			
				case 'C':
				case 'c':
				c = (CHAR16) va_arg (ap, INTN);
				CH[0] = c;
				OutputString(CH);
				break;
     
				case 'S':
				case 's':
				s = va_arg (ap, CHAR16*);
				OutputString(s);
				break;

				case 'd':
				case 'i':
				d = va_arg (ap, UINTN);
				atoi(d, buffer);
				status = OutputString(buffer);
				break;

				case 'X':
				case 'x':
				d = va_arg (ap, INTN);
				i2hex(d, buffer,HEX_LEN);
				status = OutputString(buffer);
				break;
			
				default:
				status = OutputString(L"%%");
				break;
				
			}
			break;

		default:
		CH[0] = (*(CHAR16*)(format + index));/*format[index]*/
		status = OutputString(CH);
		break;
		}
		++index;
    }
	
	return status;
}


/*
 *
 *
 *
 *
 *
 *  Input Protocol
 *
 *
 *
 *
 */
 
extern EFI_INPUT_KEY *Key;
 
EFI_STATUS 
EFIAPI Reset(IN BOOLEAN boolean){
	return ST->ConIn->Reset(ST->ConIn,boolean);
}

EFI_STATUS 
EFIAPI ReadKeyStroke(OUT EFI_INPUT_KEY *_Key) {
	return ST->ConIn->ReadKeyStroke(ST->ConIn,_Key);
}


EFI_STATUS 
EFIAPI Scan(OUT CHAR16 *buffer,IN UINTN limit) {
	EFI_STATUS status;
	UINTN index = 0;
	
	while(TRUE){
			
			while(TRUE) {
			status = ReadKeyStroke(Key) &0x7fffffff;
			if ( (status != EFI_NOT_READY) || (status == EFI_DEVICE_ERROR) )
				break;
		}
			PrintF(L"%C",Key->UnicodeChar);
			
			if(Key->UnicodeChar == L'\r')
				break;
			
			
			if(Key->UnicodeChar == 0x0008) /*BackSpace */{
				
				if (index > 0)
				index--;
			
				(*(CHAR16*)(buffer + index)) = 0;
				
			
			} else {
			
				(*(CHAR16*)(buffer + index)) = Key->UnicodeChar;
				
				if (index < limit)
				index++;
				
			}
			
		}
		
		(*(CHAR16*)(buffer + index)) = 0;
		
		return (index);
	
	
}


UINTN GetChar()
{
	
	EFI_STATUS rc;
	while(TRUE) {
			rc = ReadKeyStroke(Key) &0x7fffffff;
			if ( (rc != EFI_NOT_READY) || (rc == EFI_DEVICE_ERROR) )
				break;
		}
		
	return Key->UnicodeChar;
}























