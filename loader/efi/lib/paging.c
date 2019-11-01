/**
 *	Copyright (c) 2013 Sirius Corporation
 *	Nelson Sapalo da Siva Cole
 *	Lubango, 28 de Outubro de 2019 - Hora: 20h43
 *	File Name: paging.c
 **/
 
 
#include <efi.h>

#define io_delay() __asm__ __volatile__("out %%al,$0x80"::)

VOID wait_ns(UINTN count)
{
	count /=100;	 
	while(--count)io_delay();
}

PAGE_DIRECTORY *kernel_page_directory = (PAGE_DIRECTORY*) 0x40000; 
PAGE_TABLE *kernel_page_table = (PAGE_TABLE*) 0x41000; 


VOID load_page_diretory(VOID *phy_addr)
{

	__asm__ __volatile__("movl %k0,%%cr3"::"r"(phy_addr));
	wait_ns(120); // Wait Translation Lookaside Buffer (TLB)
}

VOID page_enable()
{	__asm__ __volatile__("movl %%cr0,%%eax;"
			     "orl $0x80000000,%%eax;"
			     "movl %%eax,%%cr0"::);
}
VOID __native_flush_tlb_single(UINT32 addr)
{
   	__asm__ __volatile__("invlpg (%0)" ::"r" (addr) : "memory");
	wait_ns(120);
}

VOID flush_tlb()
{
    UINT32 addr;
   	__asm__ __volatile__("movl %%cr3,%k0" :"=r" (addr):);
   	__asm__ __volatile__("movl %k0,%%cr3" ::"r" (addr));
	wait_ns(120);
}

VOID page_install()
{	

	INTN i,x;
	UINT32 table_addr = 0;
	UINT32 physical_addr = 0;
	
	PAGE_TABLE *pt = kernel_page_table;
	PAGE_DIRECTORY *pd =kernel_page_directory;

/*	setmem((PAGE_DIRECTORY*)kernel_page_directory,sizeof(PAGE_DIRECTORY)*1024,0);
	setmem((PAGE_TABLE*) kernel_page_table,sizeof(PAGE_TABLE)*KERNEL_OF_NUM_PAGE_TABLE*1024,0);*/
	
	__asm__ __volatile__("cli");

	
	// PTE de identidade
	for(x =0; x < KERNEL_OF_NUM_PAGE_TABLE; x++){
	for(i =0; i < 1024; i++){
		
		kernel_page_table[i*x].p = 1;
		kernel_page_table[i*x].rw= 1;
		kernel_page_table[i*x].frames = ((physical_addr+(i*x*0x1000)) >>12) &0xFFFFF;
	
	}}

	// PDE de identidade
	for(x =0; x < KERNEL_OF_NUM_PAGE_TABLE; x++){
		kernel_page_directory[x].p = 1;
		kernel_page_directory[x].rw= 1;
		table_addr =(UINT32)(kernel_page_table + (1024 *x));
		kernel_page_directory[x].addrpt = (table_addr >>12) &0xFFFFF;
	}
	load_page_diretory((PAGE_DIRECTORY*)kernel_page_directory);
	
	page_enable();

	// Espera o MMU, completar a primeira traducao 
	wait_ns(400);
}

