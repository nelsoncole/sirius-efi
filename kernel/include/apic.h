/**
 *	Copyright (c) 2013 Sirius Corporation
 *	Nelson Sapalo da Siva Cole
 *	Lubango, 06 de Outubro de 2019 - Hora: 18h00
 *	File Name: apic.h
 **/
 
 #ifndef __APIC_H__
 #define __APIC_H__
 
 
#define IA32_APIC_BASE_MSR 0x1B
#define IA32_APIC_BASE_MSR_BSP 0x100
#define IA32_APIC_BASE_MSR_ENABLE 0x800
 
 // Local APIC
 
#define IA32_LOCAL_APIC_BASE_ADDR 0xFEE00000

#define APIC_TPR 					0x80 
#define APIC_EOI					0xb0
#define APIC_S_INT_VECTOR 			0xf0
#define APIC_LVT_TIMER 				0x320
#define APIC_LVT_PERFORMANCE		0x340
#define APIC_LVT_LINT0				0x350
#define APIC_LVT_LINT1				0x360
#define APIC_LVT_ERROR				0x370
#define APIC_INITIAL_COUNT_TIMER 	0x380
#define APIC_CURRENT_COUNT_TIMER	0x390
#define APIC_DIVIDE_TIMER			0x3e0

#define APIC_CONFIG_DATA_LVT(TimerMode,Mask,TriggerMode,Remote,InterruptInput,DeliveryMode,Vector)(\
(((UINT32)(TimerMode) &0x3 ) << 17) |\
(((UINT32)(Mask) &0x1 ) << 16) |\
(((UINT32)(TriggerMode) &0x1 ) << 15) |\
(((UINT32)(Remote) &0x1 ) << 14) |\
(((UINT32)(InterruptInput) &0x1 ) << 13) |\
(((UINT32)(DeliveryMode) &0x7 ) << 8) |\
((UINT32)(Vector) &0xff )\
)


VOID apic_eoi_register();
VOID apic_initial_count_timer(UINTN value);
UINTN apic_timer();
UINTN apic_initialize();
 
 
 #endif