/**
 *	Copyright (c) 2013 Sirius Corporation
 *	Nelson Sapalo da Siva Cole
 *	Lubango, 29 de Julho de 2019 - Hora: 02h37
 *	File Name: efi_main.c
 **/
 
 
#include <efi.h>

#define KERNEL_ADDR 	0x100000  //1MiB
#define BASE_RAM 		0x3fffffff
#define IMAGE_NAME    	L"kernel.bin"

CHAR8 KernelName[] 	= "Sirius Operating System";
CHAR8 RecoveryName[] = "System Recovery";
CHAR8 ResetSystemName[] = "Reset System";
CHAR8 String1[] = "Running kernel ...";
CHAR8 String2[] = "[ Select option and press enter ]";
CHAR8 String3[] = "Kernel not found!";
CHAR8 String4[] = "System Recovery not found!";

extern GUI *G;
typedef struct {
	GUI *Graphic;
	
}SYSTEM_INFO;


SYSTEM_INFO SystemInfo;

extern VOID OS_LoaderI32(UINT32,VOID *);
	

EFI_STATUS 
EFIAPI UEFInitializeGraphics(); 
EFI_STATUS 
EFIAPI WindowMain ();
		
		
EFI_GUID  FileInfoID = EFI_FILE_INFO_ID;

static EFI_STATUS LoadImage(IN CHAR16 *name,OUT EFI_PHYSICAL_ADDRESS *image_address,
			OUT UINT32 *image_size)
{
	
		EFI_STATUS rc;
		EFI_PHYSICAL_ADDRESS phy_address = BASE_RAM;
		EFI_FILE_INFO *file_info = NULL;
		UINTN file_info_size = SIZE_OF_EFI_FILE_INFO + 128;
		EFI_FILE_HANDLE root = NULL;
		EFI_FILE_HANDLE file = NULL;
		UINTN buffer_size = 0;
		UINT8 *buffer;
		
		rc = InitializeSimpleFyleSystemProtocol();
		if(!EFI_ERROR(rc)){
			//Root
			rc = OpenVolume((EFI_FILE_HANDLE *)&root);
			if(!EFI_ERROR(rc )){
		
			rc = OpenFile(root,(EFI_FILE_HANDLE *)&file,name,EFI_FILE_MODE_READ ,EFI_FILE_ARCHIVE); 
			if(!EFI_ERROR(rc)){
			// File Info
			rc = GetInfoFile(file,&FileInfoID,&file_info_size,file_info);
			if(!EFI_ERROR(rc)){
			buffer_size = file_info->FileSize+1;
		
			phy_address = KERNEL_ADDR;
				
			buffer = (UINT8 *)(UINTN) phy_address;
			// File Read
			rc = ReadFile(file,&buffer_size,buffer);
			if(!EFI_ERROR(rc)){
				 
				*image_address = phy_address;
				*image_size = buffer_size;
				rc = CloseFile(file);
				if(EFI_ERROR(rc) ) PrintF(L"UEFI Close File \"%s\" Error,status: %x\n\r",name,rc);
				
			}else PrintF(L"UEFI Read File \"%s\" Error, status: %x\n\r",name,rc);
			}else PrintF(L"UEFI File Info \"%s\" Error, status: %x\n\r",name,rc);	
			}else PrintF(L"UEFI Open File \"%s\" Error, status: %x\n\r",name,rc);
			}else PrintF(L"UEFI Open Volume root Error, status: %x\n\r",rc);
		}else PrintF(L"UEFI Initialize Simple Fyle System Protocol Error, STATUS (%X)\n\r",rc);
		
	
		
		
		return (rc);
				
}


static EFI_STATUS call_loader(SYSTEM_INFO *SystemInfo)
{
	EFI_STATUS rc 										= 0;
	EFI_PHYSICAL_ADDRESS image_addr 					= 0;
	UINT32	image_size 									= 0;
	UINT32  ldr_mem_base 								= KERNEL_ADDR;
	
	UINTN 		MemoryMapSize = 0;
	EFI_MEMORY_DESCRIPTOR MemoryMap;
	UINTN		MapKey;
	UINTN		DescriptorSize;
	UINT32		DescriptorVersion;

	
	
	rc = LoadImage(IMAGE_NAME,&image_addr,&image_size);
		
	/* copy the kernel.bin or mappend kernel.bin into the load time memory */
	//CopyMem((VOID *)(UINTN)ldr_mem_base,(VOID *)(UINTN)image_addr,image_size);
	

	rc = BS->GetMemoryMap(
					&MemoryMapSize,
					&MemoryMap,
					&MapKey,
					&DescriptorSize,
					&DescriptorVersion);
	if(!EFI_ERROR(rc))PrintF(L"GetMemoryMap small %x\n\r",rc);
	else {
					
		rc = BS->ExitBootServices(IH,MapKey);

		if(EFI_ERROR(rc))PrintF(L"ExitBootServices error %x\n\r",rc);
		else {
		OS_LoaderI32(ldr_mem_base + 0x1000/*startkernel*/,SystemInfo/* ebx*/);
		}
	}
	
	for(;;);
	return (rc);
}

EFI_STATUS EFIAPI efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable)
{
		EFI_STATUS rc;
	
		InitializeLib(ImageHandle,SystemTable);
		

		// Call Clear Screen
		ClearScreen();
		// Call Enable Cursor
		//EnableCursor(TRUE);
		
		// Call Reset Keyboard
		if(EFI_ERROR(Reset(FALSE) )) 
			OutputString(L"UEFI Reset Keyboard Error\n\r");
	
		// Call Console SetAttribute
		if(EFI_ERROR( SetAttribute(EFI_YELLOW,EFI_BLACK) ))
			OutputString(L"UEFI Set Attribute Error\n\r");
		
		
		UEFInitializeGraphics();
		SystemInfo.Graphic = (GUI*) G;
		
		
		
		
		OutputString(L"      Sirius-efi                                      ");
		rc = WindowMain ();
		
		
		/*
		// Testes 
		rc = call_loader(&SystemInfo);
		if(!EFI_ERROR(rc))PrintF(L"err %x\n\r",rc);*/
			
	
		// Wait a key to exit
		OutputString(L"Press a key to exit");
		while(TRUE) {
			rc = ReadKeyStroke(Key) &0x7fffffff;
			if ( (rc != EFI_NOT_READY) || (rc == EFI_DEVICE_ERROR) )
				break;
		}
		
		return (0);
}



EFI_GUID GraphicsOutputProtocolGuid = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;
EFI_GRAPHICS_OUTPUT_PROTOCOL *GraphicsOutputProtocol = (EFI_GRAPHICS_OUTPUT_PROTOCOL *) 0;

GUI GSpace;
EFI_STATUS 
EFIAPI UEFInitializeGraphics(){
	
	EFI_STATUS rc;
	
	G = (GUI*) &GSpace;//Malloc(sizeof(GUI));
	
	
	rc = LibLocateProtocol(&GraphicsOutputProtocolGuid,(VOID **)&GraphicsOutputProtocol);
	if(EFI_ERROR(rc)) PrintF(L"EFI Locate Protocol Error %x\n\r",rc);
	else {
		
		//rc = GraphicsOutputProtocol->SetMode(GraphicsOutputProtocol,ModeNumber);
		
		if(EFI_ERROR(rc)) PrintF(L"EFI Set Mode Error %x\n\r",rc);
		else {
			
			
			// GUI
			G->Pitch 				= 0;
			G->Bpp 					= 32;
			G->Planes				= 0;
			G->HorizontalResolution	= GraphicsOutputProtocol->Mode->Info->HorizontalResolution;  	//	width;
			G->VerticalResolution	= GraphicsOutputProtocol->Mode->Info->VerticalResolution;  		//	hight;
			G->ByteScanLine			= GraphicsOutputProtocol->Mode->Info->PixelsPerScanLine;	
			G->MaxPixelClock		= 0;
			G->FrameBuffer			= (VOID*) GraphicsOutputProtocol->Mode->FrameBufferBase;
			G->FrameBufferSize		= GraphicsOutputProtocol->Mode->FrameBufferSize;
			G->BankBuffer			= (VOID*) Malloc(1024*1024); // 4MB
			
			G->WindowScreen			= 0;
			G->WindowBackground		= 0;
			
			G->Area.HorizontalStart = 0;
			G->Area.VerticalStart 	= 0;
			G->Area.HorizontalEnd 	= G->HorizontalResolution;
			G->Area.VerticalEnd 	= G->VerticalResolution;
			
			
			
			
			
		}
	}
	return (rc);
}

EFI_STATUS 
EFIAPI WindowMain ()
{
	EFI_STATUS rc = 0;
	UINT16 ScanCode = 0;
	UINTN _Key = 0;
	UINTN Select = 0;
	UINTN ok = 0;
	#define MAX_LIST 3
	
	

			CHAR8 Timer[] = {'R','u','n',' ','t','h','e',' ','k','e','r','n','e','l',' ','1','0',' ','.','.','.',0};
			
			SetMem(G->BankBuffer,G->HorizontalResolution * G->VerticalResolution * (G->Bpp/8),0);
			
			GW_HAND *GwHand = CreateWindow("Sirius-efi version 0.01",
						0,
						100,
						100,
						800,
						600, 
						0,
						GW_FLAG_VISIBLE);
						
			GW_HAND *Hand1 =CreateObject(GwHand,
						GW_HANDLE_LIST,
						10,
						10,
						350,
						200, 
						0,
						GW_FLAG_VISIBLE);
						
			GW_HAND *Hand2 = CreateObject(GwHand,
						GW_HANDLE_LABEL,
						800/3 - 60,
						600/2,
						500,
						50, 
						0,
						GW_FLAG_VISIBLE);
						
			GW_HAND *Hand3 = CreateObject(GwHand,
						GW_HANDLE_LABEL,
						10+380,
						10,
						350,
						200, 
						0,
						GW_FLAG_INVISIBLE);
			
			
			
			Send(Hand1,(UINTN)KernelName,0);
			Send(Hand1,(UINTN)RecoveryName,0);
			Send(Hand1,(UINTN)ResetSystemName,0);
			
			Send(Hand2,(UINTN)Timer,0);
			
			ObjectSetFocus(Hand1);
			
			
			while(TRUE){
				
				
				//Update();
				SetMem(G->BankBuffer,G->HorizontalResolution * G->VerticalResolution * (G->Bpp/8),0);
				UpdateWindow(GwHand);
				UpdateObject(GwHand,Hand1);
				UpdateObject(GwHand,Hand2);
				UpdateObject(GwHand,Hand3);
				RefreshRate();
			
				if(!ScanCode) {
			
					if( Timer[15] != '0' || Timer[16] != '0') {
					
						BS->Stall(1000000);
						if(Timer[16] == '0') { 
							Timer[15]--; 
							Timer[16] = '9';
						}else Timer[16]--;
						
					} else  {
						// Call Execut Kernel
						Send(Hand2,(UINTN)String1,0);
						if(ok) {
						Reset(TRUE);
						rc = call_loader(&SystemInfo);
						if(!EFI_ERROR(rc))goto out;
					
						// En caso de erro
						Send(Hand3,(UINTN)String3,0);
						Send(Hand3,GW_FLAG_VISIBLE,GW_SMG_FLAG_BIT);
						}
						ok++;
					
					}
				}
				
				
				if(ScanCode) {
					
					do{
						rc = ReadKeyStroke(Key) &0x7fffffff;
						
					}while(rc == EFI_NOT_READY);
				}
				else {
					rc = ReadKeyStroke(Key) &0x7fffffff;
				}
			
				if (rc != EFI_NOT_READY) {
				
					ScanCode = 1; 
				
					// Alguma tecla foi precionada
					Send(Hand2,(UINTN)String2,0);
					
					if(!Key->UnicodeChar)_Key = Key->ScanCode;
					else _Key = Key->UnicodeChar;
					
					switch(_Key){
						case 0x000D: //Enter
						
							switch(Select) {
								case 0:
									//Call execut kernel
									OutputString(L"Loading System ...");
									rc = call_loader(&SystemInfo);
									if(!EFI_ERROR(rc))goto out;
									
									// En caso de erro
									Send(Hand3,(UINTN)String3,0);
									Send(Hand3,GW_FLAG_VISIBLE,GW_SMG_FLAG_BIT);
									break;
								case 1:
									//Call system recovery
									// En caso de erro
									Send(Hand3,(UINTN)String4,0);
									Send(Hand3,GW_FLAG_VISIBLE,GW_SMG_FLAG_BIT);
									break;
								case 2:
									//Call Reset System
									OutputString(L"Reset System ...");
									RS->ResetSystem(EfiResetCold,0,0,0);
									break;
							}
							break;
						case 0x0001: //Cima
								if(!Select) Select = (MAX_LIST - 1);
								else Select--;
								Send(Hand3,GW_FLAG_INVISIBLE,GW_SMG_FLAG_BIT);
							break;
						case 0x0002: //Baixo
								if(Select >= (MAX_LIST - 1)) Select = 0;
								else Select++; 
								Send(Hand3,GW_FLAG_INVISIBLE,GW_SMG_FLAG_BIT);
							break;
						default:
							break;
					
					}
					
	
				}
		
					// Select LIST
					Send(Hand1,0,Select);
		
			
			}
			
out:
	return (EFI_SUCCESS);
	
}