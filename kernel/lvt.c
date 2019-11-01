/**
 *	Copyright (c) 2013 Sirius Corporation
 *	Nelson Sapalo da Siva Cole
 *	Lubango, 26 de Outubro de 2019 - Hora: 18h06
 *	File Name: lvt.c
 **/
 
 
#include <os.h>
extern VOID interrupter(INTN n,UINT32 offset,UINT16 sel,UINT8 dpl );

extern VOID lvt0();

VOID lvt_function(INTN  n){
	
	
	switch(n){
		
		case 32: // APIC Timer
			apic_initial_count_timer(12345);
		break;
		default:
			print("Default LVT n: %d\n",n);
		break;
	}
	
	apic_eoi_register();
	
}


VOID lvt_install()
{
	REG reg;
	reg.cs = 8;
	
    interrupter(0x20,(UINTN)lvt0,reg.cs,0);
}