/**
 *	Copyright (c) 2013 Sirius Corporation
 *	Nelson Sapalo da Siva Cole
 *	Lubango, 22 de Setembro de 2019 - Hora: 20h21
 *	File Name: dscptor.c
 **/
 
 
#include <os.h>

extern VOID gdt_flush();
extern VOID idt_flush();
extern VOID exceptions_install();
extern VOID lvt_install();

GDT gdt[256];
GDTR gdtr[1];

IDT idt[256];
IDTR idtr[1];

static
VOID set_gdt(INTN n,UINT32 limit,UINT32 base,UINT8 type,
UINT8 s,UINT8 dpl,UINT8 p,UINT8 avl,UINT8 l,UINT8 db,UINT8 g)
{


	gdt[n].limit_15_0 = limit &0xFFFF;
	gdt[n].base_15_0 = base &0xFFFF;
	gdt[n].base_23_16 = base >> 16 &0xFF;
	gdt[n].type=type &0xF;
	gdt[n].s=s &0x1;
	gdt[n].dpl =dpl &0x3;
	gdt[n].p=p &0x1;
	gdt[n].limit_19_16= limit >>16 &0xF;
	gdt[n].avl=avl &1;
	gdt[n].l=l &1;
	gdt[n].db=db &1;
	gdt[n].g=g &1;
	gdt[n].base_31_24 = base  >> 24 &0xFF;

}


VOID gdt_install(VOID)
{

	setmem(&gdt,(sizeof(GDT)*256)-1,0);

	//     (n,limit ,base ,type,s,dpl,p,avl,l,db,g)
	set_gdt(0,0,0,0,0,0,0,0,0,0,0);
	set_gdt(1,0xFFFFF,0x00000000,0x2,1,0,1,0,0,1,1); //code dpl 0
	set_gdt(2,0xFFFFF,0x00000000,0xA,1,0,1,0,0,1,1); //data dpl 0
	set_gdt(3,0xFFFFF,0x00000000,0xA,1,3,1,0,0,1,1); //dpl 3
	set_gdt(4,0xFFFFF,0x00000000,0x2,1,3,1,0,0,1,1); //dpl 3
//	set_gdt(5,sizeof(ldt_t)-1,(uint32_t)&ldt,0x2,0,3,1,0,0,1,1); //ldt dpl 3
//	set_gdt(6,sizeof(tss_t)-1,(uint32_t)&tss,0x9,0,3,1,0,0,1,1); //tss dpl 3


    gdtr->limit = (sizeof(GDT)*256)-1;
    gdtr->base = (UINTN)&gdt;
	
	gdt_flush();

  
}

static
VOID set_gate_idt(INTN n,UINT32 offset,UINT16 sel,UINT8 flags,UINT8 dpl,UINT8 p)
{

            idt[n].offset_15_0 = offset &0xFFFF;
            idt[n].sel = sel;
            idt[n].unused = 0;
            idt[n].flags = flags;
            idt[n].dpl = dpl;
            idt[n].p = p;
            idt[n].offset_31_16 = offset >> 16 &0xFFFF;



}


VOID idt_install(VOID)
{

    	setmem(&idt,(sizeof(IDT)*256)-1,0);    
    	exceptions_install();
		lvt_install();
		
    	//irq_install();

		idtr->limit = (sizeof(IDT)*256)-1;
    	idtr->base = (UINTN)idt;
    
    	idt_flush();
	

}

VOID trap(INTN n,UINT32 offset,UINT16 sel,UINT8 dpl )
{
    	set_gate_idt(n,offset,sel,0x8F,dpl,1);

}

VOID interrupter(INTN n,UINT32 offset,UINT16 sel,UINT8 dpl )
{
	set_gate_idt(n,offset,sel,0x8E,dpl,1);

}


