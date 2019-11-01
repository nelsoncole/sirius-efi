/**
 *	Copyright (c) 2013 Sirius Corporation
 *	Nelson Sapalo da Siva Cole
 *	Lubango, 21 de Setembro de 2019 - Hora: 08h45
 *	File Name: main.c
 **/
 
#include <os.h> 
 
typedef struct {
	GUI *Graphic;
	
}SYSTEM;


UINTN 
GraphicInitialize(GUI *Graphic)
{
	
	// GUI
	G = (GUI *) Graphic;
	
	//clear screen
	setmem(G->BankBuffer,G->HorizontalResolution * G->VerticalResolution * (G->Bpp/8),0x08);
	RefreshRate();
	
	return 0;
}
 
 
UINTN _main(SYSTEM *System)
{	
	// GUI
	GraphicInitialize(System->Graphic);	
	Box = CreateBox(0,0,G->HorizontalResolution,G->VerticalResolution,0,0);
	
	print("Kernel initialize...\n");
	
	gdt_install();
	idt_install();
	
	// Problemas com a paginação
	// page_install();

	
	apic_initialize();
	apic_timer();
	
	
	
	
	outputstring("Done!\n");
	
	sti(); //Enable eflag interrupt 
	
	
	return (0);
}