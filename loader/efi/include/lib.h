/**
 *	Copyright (c) 2013 Sirius Corporation
 *	Nelson Sapalo da Siva Cole
 *	Lubango, 4 de Agosto de 2019 - Hora: 23h25
 *	File Name: lib.h
 **/
 
#ifndef __LIB_H__
#define __LIB_H__

#include "gui.h"
#include "paging.h"

// Globais
extern EFI_HANDLE 				IH;
extern EFI_SYSTEM_TABLE 		*ST;
extern EFI_RUNTIME_SERVICES		*RS;
extern EFI_BOOT_SERVICES		*BS;
extern EFI_INPUT_KEY 			*Key;



/*
 *
 *
 *
 *		Initialize Lib
 *
 *
 *
 */

EFI_STATUS 
EFIAPI InitializeLib(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable);

EFI_STATUS 
EFIAPI LibLocateProtocol(IN EFI_GUID *Protocol,OUT VOID **Interface);

EFI_STATUS 
EFIAPI LibLocateDevicePath(IN EFI_GUID *Protocol,IN OUT EFI_DEVICE_PATH_PROTOCOL **DevicePath,OUT EFI_HANDLE *Device);

EFI_STATUS 
EFIAPI LibInstallProtocolInterface(IN OUT EFI_HANDLE *Handle,
	IN EFI_GUID *Protocol,
	IN EFI_INTERFACE_TYPE InterfaceType,
	IN VOID *Interface);

/*
 *
 *
 *
 *		Console Support
 *
 *
 *
 */
 
 
 // Output

EFI_STATUS 
EFIAPI	ClearScreen();

EFI_STATUS 
EFIAPI OutputString(IN CHAR16 *String);

EFI_STATUS 
EFIAPI SetAttribute(IN UINTN Foreground,IN UINTN Background);

EFI_STATUS 
EFIAPI EnableCursor(IN BOOLEAN Visible);

EFI_STATUS 
EFIAPI SetCursorPosition(IN UINTN Column,IN UINTN Row);

EFI_STATUS 
EFIAPI PrintF(CHAR16 *format,...);

// Input

EFI_STATUS 
EFIAPI Reset(IN BOOLEAN boolean);

EFI_STATUS 
EFIAPI ReadKeyStroke(OUT EFI_INPUT_KEY *_Key);

EFI_STATUS 
EFIAPI Scan(CHAR16 *buffer,UINTN limit);

UINTN GetChar();


/*
	Memory

*/


VOID *Malloc(UINTN Size);
VOID Free(VOID *Buffer);

EFI_STATUS
EFIAPI AllocatePages(	IN EFI_ALLOCATE_TYPE Type,
						IN EFI_MEMORY_TYPE MemoryType,
						IN UINTN Pages,
						IN OUT EFI_PHYSICAL_ADDRESS *Memory);
						
EFI_STATUS
EFIAPI FreePages(	IN EFI_PHYSICAL_ADDRESS Memory,
					IN UINTN  Pages);
					
EFI_STATUS
EFIAPI GetMemoryMap(IN OUT UINTN *MemoryMapSize,
					IN OUT EFI_MEMORY_DESCRIPTOR *MemoryMap,
					OUT UINTN *MapKey,
					OUT UINTN *DescriptorSize,
					OUT UINT32 *DescriptorVersion);
					
EFI_STATUS
EFIAPI AllocatePool (	IN EFI_MEMORY_TYPE PoolType,
						IN UINTN Size,
						OUT VOID **Buffer);

EFI_STATUS
EFIAPI FreePool(VOID *Buffer);

						


/*
 *
 *	Simple File System Protocol
 *
 */
 
typedef EFI_FILE_PROTOCOL *EFI_FILE_HANDLE;
 
EFI_STATUS 
EFIAPI InitializeSimpleFyleSystemProtocol();

EFI_STATUS 
EFIAPI OpenVolume(OUT EFI_FILE_PROTOCOL **Handle);

EFI_STATUS 
EFIAPI OpenFile(IN EFI_FILE_PROTOCOL *Handle,OUT EFI_FILE_PROTOCOL **NewHandle,
IN CHAR16 *FileName,IN UINT64 OpenMode,IN UINT64 Attributes);

EFI_STATUS 
EFIAPI ReadFile(IN EFI_FILE_PROTOCOL *NewHandle,IN OUT UINTN *BufferSize,OUT VOID *Buffer);

EFI_STATUS 
EFIAPI WriteFile(IN EFI_FILE_PROTOCOL *NewHandle,IN OUT UINTN *BufferSize,IN VOID *Buffer);

EFI_STATUS 
EFIAPI DeleteFile(IN EFI_FILE_PROTOCOL *NewHandle);

EFI_STATUS 
EFIAPI CloseFile(IN EFI_FILE_PROTOCOL *NewHandle);

EFI_STATUS 
EFIAPI FlushFile(IN EFI_FILE_PROTOCOL *NewHandle);

EFI_STATUS 
EFIAPI GetPositionFile(IN EFI_FILE_PROTOCOL *NewHandle,OUT UINT64 *Position);

EFI_STATUS 
EFIAPI SetPositionFile(IN EFI_FILE_PROTOCOL *NewHandle,IN UINT64 Position);

EFI_STATUS 
EFIAPI GetInfoFile(IN EFI_FILE_PROTOCOL *NewHandle,IN EFI_GUID *InformationType,IN OUT UINTN *BufferSize,OUT VOID *Buffer);

EFI_STATUS 
EFIAPI SetInfoFile(IN EFI_FILE_PROTOCOL *NewHandle,IN EFI_GUID *InformationType,IN UINTN BufferSize,IN VOID *Buffer);
/*


	Miscellaneous Services 


*/
VOID 
EFIAPI *CopyMem(IN VOID *Destination,IN VOID *Source,IN UINTN Length);

VOID 
EFIAPI *SetMem(	IN VOID *Buffer,IN UINTN Size,IN UINT8 Value);

VOID *memcpy(VOID *dest, CONST VOID *src, UINTN n);

/*

	Graphics Output Protocol  



 */
 







#endif