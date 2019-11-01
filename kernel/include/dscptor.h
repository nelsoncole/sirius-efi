/**
 *	Copyright (c) 2013 Sirius Corporation
 *	Nelson Sapalo da Siva Cole
 *	Lubango, 22 de Setembro de 2019 - Hora: 20h27
 *	File Name: dscptor.h
 *
 *
 **/
 
 
 typedef volatile struct {
	UINT64 limit_15_0 :16; 
	UINT64 base_15_0 : 16;
	UINT64 base_23_16 : 8;
	UINT64 type : 4;
	UINT64 s:1;
	UINT64 dpl: 2;
	UINT64 p:1;
	UINT64 limit_19_16: 4;
	UINT64 avl :1;
	UINT64 l:1;
	UINT64 db:1;
	UINT64 g:1; 
	UINT64 base_31_24 : 8;
	 
 }__attribute__((packed)) GDT;
 
 typedef volatile struct {
    UINT16 limit;
	UINT64 base;

}__attribute__((packed)) GDTR;


typedef volatile struct {

    UINT64 offset_15_0 :16; 
	UINT64 sel : 16;
	UINT64 unused :8;
	UINT64 flags : 5;
	UINT64 dpl : 2;
    UINT64 p :1;
	UINT64 offset_31_16 : 16;


}__attribute__ ((packed)) IDT;

typedef volatile struct {
    UINT16 	limit;
	UINT64 	base;

}__attribute__((packed)) IDTR;


