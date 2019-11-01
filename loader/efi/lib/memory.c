/**
 *	Copyright (c) 2013 Sirius Corporation
 *	Nelson Sapalo da Siva Cole
 *	Lubango, 19 de Setembro de 2019 - Hora: 09h30
 *	File Name: memory.c
 **/
 
 
#include <efi.h>



EFI_STATUS
EFIAPI AllocatePages(	IN EFI_ALLOCATE_TYPE Type,
						IN EFI_MEMORY_TYPE MemoryType,
						IN UINTN Pages,
						IN OUT EFI_PHYSICAL_ADDRESS *Memory)
{
	return BS->AllocatePages(Type,MemoryType,Pages,Memory);
}
EFI_STATUS
EFIAPI FreePages(	IN EFI_PHYSICAL_ADDRESS Memory,
					IN UINTN  Pages)
{
	return BS->FreePages(Memory, Pages);
}

EFI_STATUS
EFIAPI GetMemoryMap(IN OUT UINTN *MemoryMapSize,
					IN OUT EFI_MEMORY_DESCRIPTOR *MemoryMap,
					OUT UINTN *MapKey,
					OUT UINTN *DescriptorSize,
					OUT UINT32 *DescriptorVersion)
{
	
	return BS->GetMemoryMap(MemoryMapSize,MemoryMap,MapKey,DescriptorSize,DescriptorVersion);
}

EFI_STATUS
EFIAPI AllocatePool (	IN EFI_MEMORY_TYPE PoolType,
						IN UINTN Size,
						OUT VOID **Buffer)
{
	return BS->AllocatePool(PoolType,Size,Buffer);
}

EFI_STATUS
EFIAPI FreePool(VOID *Buffer)
{
	return BS->FreePool(Buffer);
	
} 


VOID *Malloc(UINTN Size) 
{
	EFI_STATUS rc;
	
	VOID *Buffer = 0;
	
	rc = BS->AllocatePool(EfiLoaderData,Size,(VOID*)&Buffer);
	if(EFI_ERROR(rc)){
		
		OutputString(L"Allocate Pool error\n\r");
		while(TRUE);
		return 0;
		
	};
	
	return (VOID*) Buffer;
	
}


VOID Free(VOID *Buffer)
{
	EFI_STATUS rc;
	rc = BS->FreePool(Buffer);
	if(EFI_ERROR(rc)){
		
		OutputString(L"Free Pool error\n\r");
		
	};
	
} 