/**
 *	Copyright (c) 2013 Sirius Corporation
 *	Nelson Sapalo da Siva Cole
 *	Lubango, 28 de Outubro de 2019 - Hora: 20h45
 *	File Name: paging.h
 **/
 
#ifndef __PAGING_H__
#define __PAGING_H__

#define KERNEL_OF_NUM_PAGE_TABLE 8

typedef struct _PAE_PAGE_TABLE
	{
	UINT64 p :1;
	UINT64 rw :1;
	UINT64 us :1;
	UINT64 pwt :1;
	UINT64 pcd :1;
	UINT64 a :1;
	UINT64 d :1;
	UINT64 pat :1;
	UINT64 g :1;
	UINT64 ign2 :3;
	UINT64 frames :40;
	UINT64 rs2 :12;

	}__attribute__((packed)) PAE_PAGE_TABLE;

typedef struct _PAE_PAGE_DIRECTORY
	{
	UINT64 p :1;
	UINT64 rw :1;
	UINT64 us :1;
	UINT64 pwt :1;
	UINT64 pcd :1;
	UINT64 a :1;
	UINT64 ign1 :1;
	UINT64 ps :1;
	UINT64 ign2 :4;
	UINT64 phy_addr_pt :40;
	UINT64 rs2 :12;
	}__attribute__((packed)) PAE_PAGE_DIRECTORY;
	
	
//Page_directory_pointer_table
typedef struct _PAE_PAGE_DIRECTORY_POINTER_TABLE
	{
	UINT64 p :1;
	UINT64 rs0 :2;
	UINT64 pwt :1;
	UINT64 pcd :1;
	UINT64 rs1 :4;
	UINT64 ign :3;
	UINT64 phy_addr_pd :40;
	UINT64 rs2 :12;

	}__attribute__((packed)) PAE_PAGE_DIRECTORY_POINTER_TABLE;
	
typedef struct _PAGE_TABLE
	{
	UINT32 p :1;
	UINT32 rw :1;
	UINT32 us :1;
	UINT32 pwt :1;
	UINT32 pcd :1;
	UINT32 a :1;
	UINT32 d :1;
	UINT32 pat :1;
	UINT32 g :1;
	UINT32 ign :3;
	UINT32 frames :20;

	}__attribute__((packed)) PAGE_TABLE;

typedef struct _PAGE_DIRECTORY
	{
	UINT32 p :1;
	UINT32 rw :1;
	UINT32 us :1;
	UINT32 pwt :1;
	UINT32 pcd :1;
	UINT32 a :1;
	UINT32 ign :1;
	UINT32 ps :1;
	UINT32 ignored :4;
	UINT32 addrpt :20;

	}__attribute__((packed)) PAGE_DIRECTORY;
	
	
VOID page_install();
	




#endif