/**
 *	Copyright (c) 2013 Sirius Corporation
 *	Nelson Sapalo da Siva Cole
 *	Lubango, 25 de Agosto de 2019 - Hora: 14h52
 *	File Name: init.c
 **/

#include <efi.h>


// Globais
extern EFI_HANDLE 				IH;
extern EFI_SYSTEM_TABLE 		*ST;
extern EFI_RUNTIME_SERVICES		*RS;
extern EFI_BOOT_SERVICES		*BS;



EFI_STATUS 
EFIAPI InitializeLib(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable){
	
	// EFI Initialize Lib
	IH 	= 	ImageHandle;
	ST 	= 	SystemTable;
	RS 	= 	ST->RuntimeServices;
	BS	=	ST->BootServices;
		
	return EFI_SUCCESS;
}


EFI_STATUS 
EFIAPI LibLocateProtocol(IN EFI_GUID *Protocol,OUT VOID **Interface){
	return BS->LocateProtocol(Protocol,NULL,Interface); 
}



EFI_STATUS 
EFIAPI LibLocateDevicePath(IN EFI_GUID *Protocol,IN OUT EFI_DEVICE_PATH_PROTOCOL **DevicePath,OUT EFI_HANDLE *Device){
	return BS->LocateDevicePath(Protocol,DevicePath,Device); 
}

EFI_STATUS 
EFIAPI LibInstallProtocolInterface(IN OUT EFI_HANDLE *Handle,
	IN EFI_GUID *Protocol,
	IN EFI_INTERFACE_TYPE InterfaceType,
	IN VOID *Interface){
		
	return BS->InstallProtocolInterface(Handle,Protocol,InterfaceType,Interface);
}