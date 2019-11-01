/**
 *	Copyright (c) 2013 Sirius Corporation
 *	Nelson Sapalo da Siva Cole
 *	Lubango, 25 de Agosto de 2019 - Hora: 14h50
 *	File Name: media.c
 **/

#include <efi.h>


/*


	EFI Simple Fyle System Protocol




*/


EFI_GUID SimpleFyleSystemProtocolGuid = EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID;

EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *SimpleFyleSystemProtocol = NULL;



EFI_STATUS 
EFIAPI InitializeSimpleFyleSystemProtocol()
{
	
	//SimpleFyleSystemProtocol = (EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *) Malloc(sizeof(EFI_SIMPLE_FILE_SYSTEM_PROTOCOL));
	
	return LibLocateProtocol(&SimpleFyleSystemProtocolGuid,(VOID **)&SimpleFyleSystemProtocol);
}

EFI_STATUS 
EFIAPI OpenVolume(OUT EFI_FILE_PROTOCOL **Handle){
	return SimpleFyleSystemProtocol->OpenVolume(SimpleFyleSystemProtocol,Handle);
}



EFI_STATUS 
EFIAPI OpenFile(IN EFI_FILE_PROTOCOL *Handle,OUT EFI_FILE_PROTOCOL **NewHandle,
IN CHAR16 *FileName,IN UINT64 OpenMode,IN UINT64 Attributes){
	
	return Handle->Open(Handle,NewHandle,FileName,OpenMode,Attributes);
	
}
EFI_STATUS 
EFIAPI ReadFile(IN EFI_FILE_PROTOCOL *NewHandle,IN OUT UINTN *BufferSize,OUT VOID *Buffer) 
{
	return NewHandle->Read(NewHandle,BufferSize,Buffer);
}

EFI_STATUS 
EFIAPI WriteFile(IN EFI_FILE_PROTOCOL *NewHandle,IN OUT UINTN *BufferSize,IN VOID *Buffer) 
{
	return NewHandle->Write(NewHandle,BufferSize,Buffer);
}

EFI_STATUS 
EFIAPI DeleteFile(IN EFI_FILE_PROTOCOL *NewHandle) 
{
	return NewHandle->Delete(NewHandle);
}

EFI_STATUS 
EFIAPI CloseFile(IN EFI_FILE_PROTOCOL *NewHandle) 
{
	return NewHandle->Close(NewHandle);
}


EFI_STATUS 
EFIAPI FlushFile(IN EFI_FILE_PROTOCOL *NewHandle) 
{
	return NewHandle->Flush(NewHandle);
}

EFI_STATUS 
EFIAPI GetPositionFile(IN EFI_FILE_PROTOCOL *NewHandle,OUT UINT64 *Position)
{
	return NewHandle->GetPosition(NewHandle,Position);
}

EFI_STATUS 
EFIAPI SetPositionFile(IN EFI_FILE_PROTOCOL *NewHandle,IN UINT64 Position)
{
	return NewHandle->SetPosition(NewHandle,Position);
}

EFI_STATUS 
EFIAPI GetInfoFile(IN EFI_FILE_PROTOCOL *NewHandle,IN EFI_GUID *InformationType,IN OUT UINTN *BufferSize,OUT VOID *Buffer)
{
	return NewHandle->GetInfo(NewHandle,InformationType,BufferSize,Buffer);
}

EFI_STATUS 
EFIAPI SetInfoFile(IN EFI_FILE_PROTOCOL *NewHandle,IN EFI_GUID *InformationType,IN UINTN BufferSize,IN VOID *Buffer)
{
	return NewHandle->SetInfo(NewHandle,InformationType,BufferSize,Buffer);
}

/*


	EFI Block I/O Protocol



 */
 

//EFI_GUID BlockIOProtocolGuid = EFI_BLOCK_IO_PROTOCOL_GUID;
