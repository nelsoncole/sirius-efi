/**
 *	Copyright (c) 2013 Sirius Corporation
 *	Nelson Sapalo da Siva Cole
 *	Lubango, 06 de Outubro de 2019 - Hora: 17h59
 *	File Name: apic.c
 **/
 
#include <os.h>


UINTN lapicbase = IA32_LOCAL_APIC_BASE_ADDR;

static UINT32 getapicbase()
{
	UINT32 a,d;
	
	getmsr(IA32_APIC_BASE_MSR,&a,&d);
	
	return a;
}

UINTN enableapic(UINT32 apicbase)
{
	UINT32 a = (apicbase &0xfffff000) | IA32_APIC_BASE_MSR_ENABLE;
	UINT32 d = 0;
	
	setmsr(IA32_APIC_BASE_MSR,a,d);
	
	return 0;
	
	
}

VOID 
apic_eoi_register()
{
	*(UINT32*)(lapicbase + APIC_EOI) = 0;
}



UINTN apic_initialize() {
	
	//Task Priority Register (TPR), to inhibit softint delivery
	*(UINT32*)(lapicbase + APIC_TPR) = 0; //0x20;
	
	// Timer interrupt vector, to disable timer interrupts
	*(UINT32*)(lapicbase + APIC_LVT_TIMER) = APIC_CONFIG_DATA_LVT(0,1/*Masked*/,0,0,0,0,0);
	
	// Performance counter interrupt, to disable performance counter interrupts
	*(UINT32*)(lapicbase + APIC_LVT_PERFORMANCE) = APIC_CONFIG_DATA_LVT(0,1/*Masked*/,0,0,0,0,0);
	
	// Local interrupt 0, to enable normal external interrupts, Trigger Mode = Level
	*(UINT32*)(lapicbase + APIC_LVT_LINT0) = APIC_CONFIG_DATA_LVT(0,0/*No Masked*/,NULL,NULL,1,7,0);
	
	// Local interrupt 1, to enable normal NMI processing
	*(UINT32*)(lapicbase + APIC_LVT_LINT1) = APIC_CONFIG_DATA_LVT(0,0/*No Masked*/,NULL,NULL,NULL,4,0);
	
	// Error interrupt, to disable error interrupts
	*(UINT32*)(lapicbase + APIC_LVT_ERROR) = APIC_CONFIG_DATA_LVT(0,1/*Masked*/,0,0,0,0,0);
	
	// Spurious interrupt Vector Register, to enable the APIC and set
	// spurious vector to 15
	*(UINT32*)(lapicbase + APIC_S_INT_VECTOR) = 0x10f;
	
	
	// Global enable
	print("%x\n",getapicbase());
	enableapic(getapicbase());
	print("%x\n",getapicbase());
	
	return 0;
	
}

VOID apic_initial_count_timer(UINTN value)
{
	*(UINT32*)(lapicbase + APIC_INITIAL_COUNT_TIMER ) = value;
}
UINTN apic_timer()
{
	// Timer interrupt vector, to enable timer interrupts
	*(UINT32*)(lapicbase + APIC_LVT_TIMER) = APIC_CONFIG_DATA_LVT(0,0/*Masked*/,NULL,NULL,NULL,NULL,32/*Vetor*/);
	
	//Divide Configuration Register, to divide by 128
	*(UINT32*)(lapicbase + APIC_DIVIDE_TIMER) = 0xA;

	// Initial Count Register
	*(UINT32*)(lapicbase + APIC_INITIAL_COUNT_TIMER) = 12345;
	
	return 0;
	
}













