/**
 *	Copyright (c) 2013 Sirius Corporation
 *	Nelson Sapalo da Siva Cole
 *	Lubango, 3 de Agosto de 2019 - Hora: 08h40
 *	File Name: efiapi.h
 **/
 
#ifndef __EFI_API_H__
#define __EFI_API_H__


// *** EFI Configuration Table & Properties Table
#define EFI_ACPI_TABLE_GUID \
{0x8868e871,0xe4f1,0x11d3,\
{0xbc,0x22,0x00,0x80,0xc7,0x3c,0x88,0x81}}

#define ACPI_TABLE_GUID \
{0xeb9d2d30,0x2d88,0x11d3,\
{0x9a,0x16,0x00,0x90,0x27,0x3f,0xc1,0x4d}}

#define SAL_SYSTEM_TABLE_GUID \
{0xeb9d2d32,0x2d88,0x11d3,\
{0x9a,0x16,0x00,0x90,0x27,0x3f,0xc1,0x4d}}

#define SMBIOS_TABLE_GUID \
{0xeb9d2d31,0x2d88,0x11d3,\
{0x9a,0x16,0x00,0x90,0x27,0x3f,0xc1,0x4d}}

#define SMBIOS3_TABLE_GUID \
{0xf2fd1544, 0x9794, 0x4a2c,\
{0x99,0x2e,0xe5,0xbb,0xcf,0x20,0xe3,0x94}}

#define MPS_TABLE_GUID \
{0xeb9d2d2f,0x2d88,0x11d3,\
{0x9a,0x16,0x00,0x90,0x27,0x3f,0xc1,0x4d}}
//
// ACPI 2.0 or newer tables should use EFI_ACPI_TABLE_GUID
#define EFI_ACPI_20_TABLE_GUID EFI_ACPI_TABLE_GUID

#define ACPI_TABLE_GUID \
{0xeb9d2d30,0x2d88,0x11d3,\
{0x9a,0x16,0x00,0x90,0x27,0x3f,0xc1,0x4d}}

#define ACPI_10_TABLE_GUID ACPI_TABLE_GUID

#define EFI_PROPERTIES_TABLE_VERSION 0x00010000
// Memory attribute (Not defined bits are reserved)
//
#define EFI_PROPERTIES_RUNTIME_MEMORY_PROTECTION_NON_EXECUTABLE_PE_DATA 0x1 \
// BIT 0 – description – implies the runtime data is separated from the code


typedef struct{
	EFI_GUID 	VendorGuid;
	VOID 	*VendorTable;
} EFI_CONFIGURATION_TABLE;

typedef struct {
	UINT32 Version;
	UINT32 Length;
	UINT64 MemoryProtectionAttribute;
} EFI_PROPERTIES_TABLE;

/*
 *
 *
 *
 *
 *
 *				EFI Table Header
 *
 *
 *
 *
 *
 */
typedef struct _EFI_TABLE_HEADER {
    UINT64                      Signature;
    UINT32                      Revision;
    UINT32                      HeaderSize;
    UINT32                      CRC32;
    UINT32                      Reserved;
} EFI_TABLE_HEADER;

typedef
EFI_STATUS
(EFIAPI *EFI_QUERY_VARIABLE_INFO)(
  IN  UINT32            Attributes,
  OUT UINT64            *MaximumVariableStorageSize,
  OUT UINT64            *RemainingVariableStorageSize,
  OUT UINT64            *MaximumVariableSize
 );


 /*
 *
 *
 *
 *
 *
 *					EFI Boot Services Table
 *
 *
 *
 *
 *
 *
 *
 */
 // *** EFI Task Priority Services

// Task Priority Levels
#define TPL_APPLICATION 4
#define TPL_CALLBACK 8
#define TPL_NOTIFY 16
#define TPL_HIGH_LEVEL 31
typedef
EFI_TPL
(EFIAPI *EFI_RAISE_TPL) (
	IN EFI_TPL NewTpl
);

typedef
VOID
(EFIAPI *EFI_RESTORE_TPL) (
	IN EFI_TPL OldTpl
);

// *** EFI Event, Timer

//*******************************************************
// Event Types
//*******************************************************
// These types can be “ORed” together as needed – for example,
// EVT_TIMER might be “Ored” with EVT_NOTIFY_WAIT or
// EVT_NOTIFY_SIGNAL.
#define EVT_TIMER 0x80000000
#define EVT_RUNTIME 0x40000000
#define EVT_RUNTIME_CONTEXT 0x20000000
#define EVT_NOTIFY_WAIT 0x00000100
#define EVT_NOTIFY_SIGNAL 0x00000200
#define EVT_SIGNAL_EXIT_BOOT_SERVICES 0x00000201
#define EVT_SIGNAL_VIRTUAL_ADDRESS_CHANGE 0x60000202
#define EVT_EFI_SIGNAL_MASK                 0x000000FF
#define EVT_EFI_SIGNAL_MAX                  2


// EFI_EVENT_NOTIFY
//*******************************************************
typedef
VOID
(EFIAPI *EFI_EVENT_NOTIFY) (
	IN EFI_EVENT Event,
	IN VOID *Context
);

typedef
EFI_STATUS
(EFIAPI *EFI_CREATE_EVENT) (
	IN UINT32 Type,
	IN EFI_TPL NotifyTpl,
	IN EFI_EVENT_NOTIFY NotifyFunction, OPTIONAL
	IN VOID *NotifyContext, OPTIONAL
	OUT EFI_EVENT *Event
);


#define EFI_EVENT_GROUP_EXIT_BOOT_SERVICES \
{0x27abf055, 0xb1b8, 0x4c26, 0x80, 0x48, 0x74, 0x8f, 0x37,\
0xba, 0xa2, 0xdf}}
#define EFI_EVENT_GROUP_VIRTUAL_ADDRESS_CHANGE \
{0x13fa7698, 0xc831, 0x49c7, 0x87, 0xea, 0x8f, 0x43, 0xfc,\
0xc2, 0x51, 0x96}
#define EFI_EVENT_GROUP_MEMORY_MAP_CHANGE \
{0x78bee926, 0x692f, 0x48fd, 0x9e, 0xdb, 0x1, 0x42, 0x2e, \
0xf0, 0xd7, 0xab}
#define EFI_EVENT_GROUP_READY_TO_BOOT \
{0x7ce88fb3, 0x4bd7, 0x4679, 0x87, 0xa8, 0xa8, 0xd8, 0xde,\
0xe5,0xd, 0x2b}
#define EFI_EVENT_GROUP_RESET_SYSTEM \
{ 0x62da6a56, 0x13fb, 0x485a, { 0xa8, 0xda, 0xa3, 0xdd, 0x79, 0x12, 0xcb, 0x6b } }

typedef
EFI_STATUS
(EFIAPI *EFI_CREATE_EVENT_EX) ( IN UINT32 Type, IN EFI_TPL NotifyTpl,
	IN EFI_EVENT_NOTIFY NotifyFunction OPTIONAL,
	IN CONST VOID *NotifyContext OPTIONAL,
	IN CONST EFI_GUID *EventGroup OPTIONAL,
	OUT EFI_EVENT *Event
);

typedef
EFI_STATUS
(EFIAPI *EFI_CLOSE_EVENT) (
	IN EFI_EVENT Event
);

typedef
EFI_STATUS
(EFIAPI *EFI_SIGNAL_EVENT) (
	IN EFI_EVENT Event
);

typedef
EFI_STATUS
(EFIAPI *EFI_WAIT_FOR_EVENT) (
	IN UINTN NumberOfEvents,
	IN EFI_EVENT *Event,
	OUT UINTN *Index
);

typedef
EFI_STATUS
(EFIAPI *EFI_CHECK_EVENT) (
	IN EFI_EVENT Event
);

//EFI_TIMER_DELAY
typedef enum {
	TimerCancel,
	TimerPeriodic,
	TimerRelative
} EFI_TIMER_DELAY;
typedef
EFI_STATUS
(EFIAPI *EFI_SET_TIMER) (
	IN EFI_EVENT Event,
	IN EFI_TIMER_DELAY Type,
	IN UINT64 TriggerTime
);


/*
		** EFI Memory Services
	




	
*/

// Memory Attribute Definitions
//*******************************************************
// These types can be “ORed” together as needed.
#define EFI_MEMORY_UC 0x0000000000000001
#define EFI_MEMORY_WC 0x0000000000000002
#define EFI_MEMORY_WT 0x0000000000000004
#define EFI_MEMORY_WB 0x0000000000000008
#define EFI_MEMORY_UCE 0x0000000000000010
#define EFI_MEMORY_WP 0x0000000000001000
#define EFI_MEMORY_RP 0x0000000000002000
#define EFI_MEMORY_XP 0x0000000000004000
#define EFI_MEMORY_NV 0x0000000000008000
#define EFI_MEMORY_MORE_RELIABLE 0x0000000000010000
#define EFI_MEMORY_RO 0x0000000000020000
#define EFI_MEMORY_SP 0x0000000000040000
#define EFI_MEMORY_CPU_CRYPTO 0x0000000000080000
#define EFI_MEMORY_RUNTIME 0x8000000000000000

//*******************************************************
// Memory Descriptor Version Number
//*******************************************************
#define EFI_MEMORY_DESCRIPTOR_VERSION 1

//EFI_ALLOCATE_TYPE
//*******************************************************
// These types are discussed in the “Description” section below.
typedef enum {
	AllocateAnyPages,
	AllocateMaxAddress,
	AllocateAddress,
	MaxAllocateType
} EFI_ALLOCATE_TYPE;
//*******************************************************
//EFI_MEMORY_TYPE
//*******************************************************
// These type values are discussed in Table 29 and Table 30.
typedef enum {
	EfiReservedMemoryType,
	EfiLoaderCode,
	EfiLoaderData,
	EfiBootServicesCode,
	EfiBootServicesData,
	EfiRuntimeServicesCode,
	EfiRuntimeServicesData,
	EfiConventionalMemory,
	EfiUnusableMemory,
	EfiACPIReclaimMemory,
	EfiACPIMemoryNVS,
	EfiMemoryMappedIO,
	EfiMemoryMappedIOPortSpace,
	EfiPalCode,
	EfiPersistentMemory,
	EfiMaxMemoryType
} EFI_MEMORY_TYPE;


typedef
EFI_STATUS
(EFIAPI *EFI_ALLOCATE_PAGES) (
	IN EFI_ALLOCATE_TYPE Type,
	IN EFI_MEMORY_TYPE MemoryType,
	IN UINTN Pages,
	IN OUT EFI_PHYSICAL_ADDRESS *Memory
); 

typedef
EFI_STATUS
(EFIAPI *EFI_FREE_PAGES) (
	IN EFI_PHYSICAL_ADDRESS Memory,
	IN UINTN Pages
);

//EFI_MEMORY_DESCRIPTOR
//*******************************************************
typedef struct {
	UINT32 Type;
	EFI_PHYSICAL_ADDRESS PhysicalStart;
	EFI_VIRTUAL_ADDRESS VirtualStart;
	UINT64 NumberOfPages;
	UINT64 Attribute;
} EFI_MEMORY_DESCRIPTOR;

typedef
EFI_STATUS
(EFIAPI *EFI_GET_MEMORY_MAP) (
	IN OUT UINTN *MemoryMapSize,
	IN OUT EFI_MEMORY_DESCRIPTOR *MemoryMap,
	OUT UINTN *MapKey,
	OUT UINTN *DescriptorSize,
	OUT UINT32 *DescriptorVersion
);

typedef
EFI_STATUS
(EFIAPI *EFI_ALLOCATE_POOL) (
	IN EFI_MEMORY_TYPE PoolType,
	IN UINTN Size,
	OUT VOID **Buffer
);

typedef
EFI_STATUS
(EFIAPI *EFI_FREE_POOL) (
	IN VOID *Buffer
);


typedef 
EFI_STATUS
(EFIAPI *EFI_SET_VIRTUAL_ADDRESS_MAP) (
    IN UINTN                        MemoryMapSize,
    IN UINTN                        DescriptorSize,
    IN UINT32                       DescriptorVersion,
    IN EFI_MEMORY_DESCRIPTOR        *VirtualMap
);


#define EFI_OPTIONAL_PTR            0x00000001
#define EFI_INTERNAL_FNC            0x00000002      // Pointer to internal runtime fnc
#define EFI_INTERNAL_PTR            0x00000004      // Pointer to internal runtime data


typedef 
EFI_STATUS
(EFIAPI *EFI_CONVERT_POINTER) (
    IN UINTN                        DebugDisposition,
    IN OUT VOID                     **Address
);

/*

	** EFI Protocol Handler Services
	
	
	
*/


// *** EFI Device Path Protocol
#define EFI_DEVICE_PATH_PROTOCOL_GUID \
{0x09576e91,0x6d3f,0x11d2,\
{0x8e,0x39,0x00,0xa0,0xc9,0x69,0x72,0x3b}}

// EFI_DEVICE_PATH_PROTOCOL
//*******************************************************
typedef struct _EFI_DEVICE_PATH_PROTOCOL {
	UINT8 Type;
	UINT8 SubType;
	UINT8 Length[2];
	UINT32 m;
} EFI_DEVICE_PATH_PROTOCOL;


//*******************************************************
//EFI_INTERFACE_TYPE
//*******************************************************
typedef enum {
	EFI_NATIVE_INTERFACE
} EFI_INTERFACE_TYPE;

typedef
EFI_STATUS
(EFIAPI *EFI_INSTALL_PROTOCOL_INTERFACE) (
	IN OUT EFI_HANDLE *Handle,
	IN EFI_GUID *Protocol,
	IN EFI_INTERFACE_TYPE InterfaceType,
	IN VOID *Interface
);

typedef
EFI_STATUS
(EFIAPI *EFI_UNINSTALL_PROTOCOL_INTERFACE) (
	IN EFI_HANDLE Handle,
	IN EFI_GUID *Protocol,
	IN VOID *Interface
);

typedef
EFI_STATUS
(EFIAPI *EFI_REINSTALL_PROTOCOL_INTERFACE) (
	IN EFI_HANDLE Handle,
	IN EFI_GUID *Protocol,
	IN VOID *OldInterface,
	IN VOID *NewInterface
);

typedef
EFI_STATUS
(EFIAPI *EFI_REGISTER_PROTOCOL_NOTIFY) (
	IN EFI_GUID *Protocol,
	IN EFI_EVENT Event,
	OUT VOID **Registration
);
// EFI_LOCATE_SEARCH_TYPE
//*******************************************************
typedef enum {
	AllHandles,
	ByRegisterNotify,
	ByProtocol
} EFI_LOCATE_SEARCH_TYPE;

typedef
EFI_STATUS
(EFIAPI *EFI_LOCATE_HANDLE) (
	IN EFI_LOCATE_SEARCH_TYPE SearchType,
	IN EFI_GUID *Protocol OPTIONAL,
	IN VOID *SearchKey OPTIONAL,
	IN OUT UINTN *BufferSize,
	OUT EFI_HANDLE *Buffer
);

typedef
EFI_STATUS
(EFIAPI *EFI_HANDLE_PROTOCOL) (
	IN EFI_HANDLE Handle,
	IN EFI_GUID *Protocol,
	OUT VOID **Interface
);

typedef
EFI_STATUS
(EFIAPI *EFI_LOCATE_DEVICE_PATH) (
	IN EFI_GUID *Protocol,
	IN OUT EFI_DEVICE_PATH_PROTOCOL **DevicePath,
	OUT EFI_HANDLE *Device
);

#define EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL 0x00000001
#define EFI_OPEN_PROTOCOL_GET_PROTOCOL 0x00000002
#define EFI_OPEN_PROTOCOL_TEST_PROTOCOL 0x00000004
#define EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER 0x00000008
#define EFI_OPEN_PROTOCOL_BY_DRIVER 0x00000010
#define EFI_OPEN_PROTOCOL_EXCLUSIVE 0x00000020
typedef
EFI_STATUS
(EFIAPI *EFI_OPEN_PROTOCOL) (
	IN EFI_HANDLE Handle,
	IN EFI_GUID *Protocol,
	OUT VOID **Interface OPTIONAL,
	IN EFI_HANDLE AgentHandle,
	IN EFI_HANDLE ControllerHandle,
	IN UINT32 Attributes
);

typedef
EFI_STATUS
(EFIAPI *EFI_CLOSE_PROTOCOL) (
	IN EFI_HANDLE Handle,
	IN EFI_GUID *Protocol,
	IN EFI_HANDLE AgentHandle,
	IN EFI_HANDLE ControllerHandle
);

typedef struct {
	EFI_HANDLE AgentHandle;
	EFI_HANDLE ControllerHandle;
	UINT32 Attributes;
	UINT32 OpenCount;
} EFI_OPEN_PROTOCOL_INFORMATION_ENTRY;

typedef
EFI_STATUS
(EFIAPI *EFI_OPEN_PROTOCOL_INFORMATION) (
	IN EFI_HANDLE Handle,
	IN EFI_GUID *Protocol,
	OUT EFI_OPEN_PROTOCOL_INFORMATION_ENTRY **EntryBuffer,
	OUT UINTN *EntryCount
);

typedef
EFI_STATUS
(EFIAPI *EFI_CONNECT_CONTROLLER) (
	IN EFI_HANDLE ControllerHandle,
	IN EFI_HANDLE *DriverImageHandle OPTIONAL,
	IN EFI_DEVICE_PATH_PROTOCOL *RemainingDevicePath OPTIONAL,
	IN BOOLEAN Recursive
);

typedef
EFI_STATUS
(EFIAPI *EFI_DISCONNECT_CONTROLLER) (
	IN EFI_HANDLE ControllerHandle,
	IN EFI_HANDLE DriverImageHandle OPTIONAL,
	IN EFI_HANDLE ChildHandle OPTIONAL
);

typedef
EFI_STATUS
(EFIAPI *EFI_PROTOCOLS_PER_HANDLE) (
	IN EFI_HANDLE Handle,
	OUT EFI_GUID ***ProtocolBuffer,
	OUT UINTN *ProtocolBufferCount
);
typedef
EFI_STATUS
(EFIAPI *EFI_LOCATE_HANDLE_BUFFER) (
	IN EFI_LOCATE_SEARCH_TYPE SearchType,
	IN EFI_GUID *Protocol OPTIONAL,
	IN VOID *SearchKey OPTIONAL,
	IN OUT UINTN *NoHandles,
	OUT EFI_HANDLE **Buffer
);

typedef
EFI_STATUS
(EFIAPI *EFI_LOCATE_PROTOCOL) (
	IN EFI_GUID *Protocol,
	IN VOID *Registration OPTIONAL,
	OUT VOID **Interface
);

typedef
EFI_STATUS
(EFIAPI *EFI_INSTALL_MULTIPLE_PROTOCOL_INTERFACES) (
	IN OUT EFI_HANDLE *Handle,
	...
);

typedef
EFI_STATUS
(EFIAPI *EFI_UNINSTALL_MULTIPLE_PROTOCOL_INTERFACES) (
	IN EFI_HANDLE Handle,
	...
);

// *** EFI Image Services
#define EFI_HII_PACKAGE_LIST_PROTOCOL_GUID \
{ 0x6a1ee763, 0xd47a, 0x43b4, \
{ 0xaa, 0xbe, 0xef, 0x1d, 0xe2, 0xab, 0x56, 0xfc } }
// FIXME:  typedef EFI_HII_PACKAGE_LIST_HEADER *EFI_HII_PACKAGE_LIST_PROTOCOL;

typedef
EFI_STATUS
(EFIAPI *EFI_IMAGE_LOAD) (
	IN BOOLEAN BootPolicy,
	IN EFI_HANDLE ParentImageHandle,
	IN EFI_DEVICE_PATH_PROTOCOL *DevicePath,
	IN VOID *SourceBuffer OPTIONAL,
	IN UINTN SourceSize,
	OUT EFI_HANDLE *ImageHandle
); 

typedef
EFI_STATUS
(EFIAPI *EFI_IMAGE_START) (
	IN EFI_HANDLE ImageHandle,
	OUT UINTN *ExitDataSize,
	OUT CHAR16 **ExitData OPTIONAL
);

typedef
EFI_STATUS
(EFIAPI *EFI_IMAGE_UNLOAD) (
	IN EFI_HANDLE ImageHandle
);

typedef
EFI_STATUS
(EFIAPI *EFI_EXIT) (
	IN EFI_HANDLE ImageHandle,
	IN EFI_STATUS ExitStatus,
	IN UINTN ExitDataSize,
	IN CHAR16 *ExitData OPTIONAL
);

typedef
EFI_STATUS
(EFIAPI *EFI_EXIT_BOOT_SERVICES) (
	IN EFI_HANDLE	ImageHandle,
	IN UINTN	MapKey
);


// ***EFI Miscellaneous Services 
typedef
EFI_STATUS
(EFIAPI *EFI_SET_WATCHDOG_TIMER) (
	IN UINTN Timeout,
	IN UINT64 WatchdogCode,
	IN UINTN DataSize,
	IN CHAR16 *WatchdogData OPTIONAL
);

typedef
EFI_STATUS
(EFIAPI *EFI_STALL) (
	IN UINTN Microseconds
);

typedef
VOID
(EFIAPI *EFI_COPY_MEM) (
	IN VOID *Destination,
	IN VOID *Source,
	IN UINTN Length
);

typedef
VOID
(EFIAPI *EFI_SET_MEM) (
	IN VOID *Buffer,
	IN UINTN Size,
	IN UINT8 Value
);

typedef
EFI_STATUS
(EFIAPI *EFI_GET_NEXT_MONOTONIC_COUNT) (
	OUT UINT64 *Count
);

typedef
EFI_STATUS
(EFIAPI *EFI_INSTALL_CONFIGURATION_TABLE) (
	IN EFI_GUID *Guid,
	IN VOID *Table
);

typedef
EFI_STATUS
(EFIAPI *EFI_CALCULATE_CRC32)	(
	IN VOID *Data,
	IN UINTN DataSize,
	OUT UINT32 *Crc32
);

//					EFI Boot Services Table
#define EFI_BOOT_SERVICES_SIGNATURE 0x56524553544f4f42
#define EFI_BOOT_SERVICES_REVISION EFI_SPECIFICATION_VERSION


typedef struct {
	EFI_TABLE_HEADER 					Hdr;
	//
	// Task Priority Services
	//
	EFI_RAISE_TPL 						RaiseTPL; // EFI 1.0+ 
	EFI_RESTORE_TPL 					RestoreTPL; // EFI 1.0+ 
	// 
	// Memory Services 
	// 
	EFI_ALLOCATE_PAGES 					AllocatePages; // EFI 1.0+ 
	EFI_FREE_PAGES 						FreePages; // EFI 1.0+ 
	EFI_GET_MEMORY_MAP 					GetMemoryMap; // EFI 1.0+ 
	EFI_ALLOCATE_POOL 					AllocatePool; // EFI 1.0+ 
	EFI_FREE_POOL 						FreePool; // EFI 1.0+ 
	// 
	// Event & Timer Services 
	// 
	EFI_CREATE_EVENT 					CreateEvent; // EFI 1.0+ 
	EFI_SET_TIMER 						SetTimer; // EFI 1.0+ 
	EFI_WAIT_FOR_EVENT 					WaitForEvent; // EFI 1.0+ 
	EFI_SIGNAL_EVENT 					SignalEvent; // EFI 1.0+ 
	EFI_CLOSE_EVENT 					CloseEvent; // EFI 1.0+ 
	EFI_CHECK_EVENT 					CheckEvent; // EFI 1.0+
	// 
	// Protocol Handler Services 
	// 
	EFI_INSTALL_PROTOCOL_INTERFACE 		InstallProtocolInterface; // EFI 1.0+ 
	EFI_REINSTALL_PROTOCOL_INTERFACE 	ReinstallProtocolInterface; // EFI 1.0+ 
	EFI_UNINSTALL_PROTOCOL_INTERFACE 	UninstallProtocolInterface; // EFI 1.0+ 
	EFI_HANDLE_PROTOCOL 				HandleProtocol; // EFI 1.0+ 
	VOID* 								Reserved; // EFI 1.0+ 
	EFI_REGISTER_PROTOCOL_NOTIFY 		RegisterProtocolNotify; // EFI 1.0+ 
	EFI_LOCATE_HANDLE 					LocateHandle; // EFI 1.0+ 
	EFI_LOCATE_DEVICE_PATH 				LocateDevicePath; // EFI 1.0+
	EFI_INSTALL_CONFIGURATION_TABLE 	InstallConfigurationTable; // EFI 1.0+ 
	// 
	// Image Services 
	// 
	EFI_IMAGE_LOAD 						LoadImage; // EFI 1.0+ 
	EFI_IMAGE_START 					StartImage; // EFI 1.0+
	EFI_EXIT 							Exit; // EFI 1.0+ 
	EFI_IMAGE_UNLOAD 					UnloadImage; // EFI 1.0+ 
	EFI_EXIT_BOOT_SERVICES 				ExitBootServices; // EFI 1.0+ 
	// 
	// Miscellaneous Services 
	// 
	EFI_GET_NEXT_MONOTONIC_COUNT 		GetNextMonotonicCount; // EFI 1.0+ 
	EFI_STALL 							Stall; // EFI 1.0+ 
	EFI_SET_WATCHDOG_TIMER 				SetWatchdogTimer; // EFI 1.0+ 
	// 
	// DriverSupport Services 
	// 
	EFI_CONNECT_CONTROLLER 				ConnectController; // EFI 1.1 
	EFI_DISCONNECT_CONTROLLER 			DisconnectController;// EFI 1.1+ 
	// 
	// Open and Close Protocol Services 
	// 
	EFI_OPEN_PROTOCOL 					OpenProtocol; // EFI 1.1+ 
	EFI_CLOSE_PROTOCOL 					CloseProtocol; // EFI 1.1+
	EFI_OPEN_PROTOCOL_INFORMATION 		OpenProtocolInformation; // EFI 1.1+ 
	// 
	// Library Services 
	// 
	EFI_PROTOCOLS_PER_HANDLE 			ProtocolsPerHandle; // EFI 1.1+ 
	EFI_LOCATE_HANDLE_BUFFER 			LocateHandleBuffer; // EFI 1.1+ 
	EFI_LOCATE_PROTOCOL 				LocateProtocol; // EFI 1.1+ 
	EFI_INSTALL_MULTIPLE_PROTOCOL_INTERFACES	InstallMultipleProtocolInterfaces; // EFI 1.1+ 
	EFI_UNINSTALL_MULTIPLE_PROTOCOL_INTERFACES	UninstallMultipleProtocolInterfaces; // EFI 1.1+
	// 
	// 32-bit CRC Services 
	// 
	EFI_CALCULATE_CRC32 				CalculateCrc32; // EFI 1.1+ 
	// 
	// Miscellaneous Services 
	// 
	EFI_COPY_MEM 						CopyMem; // EFI 1.1+ 
	EFI_SET_MEM 						SetMem; // EFI 1.1+
	EFI_CREATE_EVENT_EX 				CreateEventEx; // UEFI 2.0+ 
	
} EFI_BOOT_SERVICES;


/*
 *
 *
 *
 *
 *
 *					EFI Runtime Services
 *
 *
 *
 *
 *
 *
 *
 */

// *** EFI Time Services 
#define EFI_RT_SUPPORTED_GET_TIME 0x0001
#define EFI_RT_SUPPORTED_SET_TIME 0x0002
#define EFI_RT_SUPPORTED_GET_WAKEUP_TIME 0x0004
#define EFI_RT_SUPPORTED_SET_WAKEUP_TIME 0x0008
#define EFI_RT_SUPPORTED_GET_VARIABLE 0x0010
#define EFI_RT_SUPPORTED_GET_NEXT_VARIABLE_NAME 0x0020
#define EFI_RT_SUPPORTED_SET_VARIABLE 0x0040
#define EFI_RT_SUPPORTED_SET_VIRTUAL_ADDRESS_MAP 0x0080
#define EFI_RT_SUPPORTED_CONVERT_POINTER 0x0100
#define EFI_RT_SUPPORTED_GET_NEXT_HIGH_MONOTONIC_COUNT 0x0200
#define EFI_RT_SUPPORTED_RESET_SYSTEM 0x0400
#define EFI_RT_SUPPORTED_UPDATE_CAPSULE 0x0800
#define EFI_RT_SUPPORTED_QUERY_CAPSULE_CAPABILITIES 0x1000
#define EFI_RT_SUPPORTED_QUERY_VARIABLE_INFO 0x2000


typedef struct {
        UINT32                      Resolution;     // 1e-6 parts per million
        UINT32                      Accuracy;       // hertz
        BOOLEAN                     SetsToZero;     // Set clears sub-second time
} EFI_TIME_CAPABILITIES;


typedef
EFI_STATUS
(EFIAPI *EFI_GET_TIME) (
    OUT EFI_TIME                    *Time,
    OUT EFI_TIME_CAPABILITIES       *Capabilities OPTIONAL
);

typedef
EFI_STATUS
(EFIAPI *EFI_SET_TIME) (
    IN EFI_TIME                     *Time
);

typedef
EFI_STATUS
(EFIAPI *EFI_GET_WAKEUP_TIME) (
    OUT BOOLEAN                     *Enabled,
    OUT BOOLEAN                     *Pending,
    OUT EFI_TIME                    *Time
);

typedef
EFI_STATUS
(EFIAPI *EFI_SET_WAKEUP_TIME) (
    IN BOOLEAN                      Enable,
    IN EFI_TIME                     *Time OPTIONAL
);



//*******************************************************
// Variable Attributes
//*******************************************************
#define EFI_VARIABLE_NON_VOLATILE 0x00000001
#define EFI_VARIABLE_BOOTSERVICE_ACCESS 0x00000002
#define EFI_VARIABLE_RUNTIME_ACCESS 0x00000004
#define EFI_VARIABLE_HARDWARE_ERROR_RECORD 0x00000008 \
//This attribute is identified by the mnemonic 'HR' elsewhere
//in this specification.
#define EFI_VARIABLE_AUTHENTICATED_WRITE_ACCESS 0x00000010
//NOTE: EFI_VARIABLE_AUTHENTICATED_WRITE_ACCESS is deprecated
//and should be considered reserved.
#define EFI_VARIABLE_TIME_BASED_AUTHENTICATED_WRITE_ACCESS \ 0x00000020
#define EFI_VARIABLE_APPEND_WRITE 0x00000040
#define EFI_VARIABLE_ENHANCED_AUTHENTICATED_ACCESS 0x00000080
//This attribute indicates that the variable payload begins
//with an EFI_VARIABLE_AUTHENTICATION_3 structure, and
//potentially more structures as indicated by fields of this
//structure. See definition below and in SetVariable().

//
// EFI_VARIABLE_AUTHENTICATION_3_CERT_ID descriptor
//
// An extensible structure to identify a unique x509 cert
// associated with a given variable
//
#define EFI_VARIABLE_AUTHENTICATION_3_CERT_ID_SHA256 1
typedef struct {
UINT8 Type;
UINT32 IdSize;
// UINT8 Id[IdSize];
} EFI_VARIABLE_AUTHENTICATION_3_CERT_ID;

// EFI platform varibles
//

#define EFI_GLOBAL_VARIABLE     \
    { 0x8BE4DF61, 0x93CA, 0x11d2, {0xAA, 0x0D, 0x00, 0xE0, 0x98, 0x03, 0x2B, 0x8C} }

// Variable attributes
#define EFI_VARIABLE_NON_VOLATILE           0x00000001
#define EFI_VARIABLE_BOOTSERVICE_ACCESS     0x00000002
#define EFI_VARIABLE_RUNTIME_ACCESS         0x00000004

// Variable size limitation
#define EFI_MAXIMUM_VARIABLE_SIZE           1024

typedef
EFI_STATUS
(EFIAPI *EFI_GET_VARIABLE) (
    IN CHAR16                       *VariableName,
    IN EFI_GUID                     *VendorGuid,
    OUT UINT32                      *Attributes OPTIONAL,
    IN OUT UINTN                    *DataSize,
    OUT VOID                        *Data
    );

typedef
EFI_STATUS
(EFIAPI *EFI_GET_NEXT_VARIABLE_NAME) (
    IN OUT UINTN                    *VariableNameSize,
    IN OUT CHAR16                   *VariableName,
    IN OUT EFI_GUID                 *VendorGuid
);


typedef
EFI_STATUS
(EFIAPI *EFI_SET_VARIABLE) (
    IN CHAR16                       *VariableName,
    IN EFI_GUID                     *VendorGuid,
    IN UINT32                       Attributes,
    IN UINTN                        DataSize,
    IN VOID                         *Data
 );



// *** EFI Miscellaneous Services
//*******************************************************
// EFI_RESET_TYPE
//*******************************************************
typedef enum {
	EfiResetCold,
	EfiResetWarm,
	EfiResetShutdown,
	EfiResetPlatformSpecific
} EFI_RESET_TYPE;

typedef
VOID
(EFIAPI *EFI_RESET_SYSTEM) (
	IN EFI_RESET_TYPE ResetType,
	IN EFI_STATUS ResetStatus,
	IN UINTN DataSize,
	IN VOID *ResetData OPTIONAL
);

typedef
EFI_STATUS
(EFIAPI *EFI_GET_NEXT_MONOTONIC_COUNT) (
    OUT UINT64                  *Count
 );

typedef
EFI_STATUS
(EFIAPI *EFI_GET_NEXT_HIGH_MONO_COUNT) (
    OUT UINT32                  *HighCount
);

// *** UEFI 2.0 Capsule Services
typedef struct {
  UINT64                            Length;
  union {
    EFI_PHYSICAL_ADDRESS  DataBlock;
    EFI_PHYSICAL_ADDRESS  ContinuationPointer;
  } Union;
} EFI_CAPSULE_BLOCK_DESCRIPTOR;

typedef struct {
  EFI_GUID          CapsuleGuid;
  UINT32            HeaderSize;
  UINT32            Flags;
  UINT32            CapsuleImageSize;
} EFI_CAPSULE_HEADER;

typedef struct {
  UINT32   CapsuleArrayNumber;
  VOID*    CapsulePtr[1];
} EFI_CAPSULE_TABLE;

#pragma pack(1)
typedef struct {
  UINT16 VariableTotalSize;
  EFI_GUID CapsuleGuid;
  EFI_TIME CapsuleProcessed;
  EFI_STATUS CapsuleStatus;
} EFI_CAPSULE_REPORT_TABLE;
#pragma pack()

#define CAPSULE_FLAGS_PERSIST_ACROSS_RESET          0x00010000
#define CAPSULE_FLAGS_POPULATE_SYSTEM_TABLE         0x00020000
#define CAPSULE_FLAGS_INITIATE_RESET                0x00040000


typedef
EFI_STATUS
(EFIAPI *EFI_UPDATE_CAPSULE)(
  IN EFI_CAPSULE_HEADER     **CapsuleHeaderArray,
  IN UINTN                  CapsuleCount,
  IN EFI_PHYSICAL_ADDRESS   ScatterGatherList   OPTIONAL
 );

typedef
EFI_STATUS
(EFIAPI *EFI_QUERY_CAPSULE_CAPABILITIES)(
  IN  EFI_CAPSULE_HEADER     **CapsuleHeaderArray,
  IN  UINTN                  CapsuleCount,
  OUT UINT64                 *MaximumCapsuleSize,
  OUT EFI_RESET_TYPE         *ResetType
 );
  
 // EFI Runtime Services
#define EFI_RUNTIME_SERVICES_SIGNATURE 0x56524553544e5552
#define EFI_RUNTIME_SERVICES_REVISION EFI_SPECIFICATION_VERSION
typedef struct { 
	EFI_TABLE_HEADER 					Hdr; 
	// 
	// Time Services 
	// 
	EFI_GET_TIME 						GetTime; 
	EFI_SET_TIME 						SetTime; 
	EFI_GET_WAKEUP_TIME 				GetWakeupTime; 
	EFI_SET_WAKEUP_TIME 				SetWakeupTime; 
	// 
	// Virtual Memory Services 
	// 
	EFI_SET_VIRTUAL_ADDRESS_MAP 		SetVirtualAddressMap;
	EFI_CONVERT_POINTER 				ConvertPointer; 
	// 
	// Variable Services 
	// 
	EFI_GET_VARIABLE 					GetVariable; 
	EFI_GET_NEXT_VARIABLE_NAME 			GetNextVariableName; 
	EFI_SET_VARIABLE 					SetVariable; 
	// 
	// Miscellaneous Services 
	// 
	EFI_GET_NEXT_HIGH_MONO_COUNT 		GetNextHighMonotonicCount; 
	EFI_RESET_SYSTEM 					ResetSystem;
	//
	// UEFI 2.0 Capsule Services
	// 
	EFI_UPDATE_CAPSULE 					UpdateCapsule; 
	EFI_QUERY_CAPSULE_CAPABILITIES 		QueryCapsuleCapabilities;
	//
	// Miscellaneous UEFI 2.0 Service
	// 
	EFI_QUERY_VARIABLE_INFO 			QueryVariableInfo;
} EFI_RUNTIME_SERVICES;

/*
 *
 *
 *
 *
 *
 *					EFI System Table
 *
 *
 *
 *
 *
 *
 *
 */
#define EFI_SYSTEM_TABLE_SIGNATURE 0x5453595320494249
#define EFI_2_80_SYSTEM_TABLE_REVISION ((2<<16) | (80))
#define EFI_2_70_SYSTEM_TABLE_REVISION ((2<<16) | (70))
#define EFI_2_60_SYSTEM_TABLE_REVISION ((2<<16) | (60))
#define EFI_2_50_SYSTEM_TABLE_REVISION ((2<<16) | (50))
#define EFI_2_40_SYSTEM_TABLE_REVISION ((2<<16) | (40))
#define EFI_2_31_SYSTEM_TABLE_REVISION ((2<<16) | (31))
#define EFI_2_30_SYSTEM_TABLE_REVISION ((2<<16) | (30))
#define EFI_2_20_SYSTEM_TABLE_REVISION ((2<<16) | (20))
#define EFI_2_10_SYSTEM_TABLE_REVISION ((2<<16) | (10))
#define EFI_2_00_SYSTEM_TABLE_REVISION ((2<<16) | (00))
#define EFI_1_10_SYSTEM_TABLE_REVISION ((1<<16) | (10))
#define EFI_1_02_SYSTEM_TABLE_REVISION ((1<<16) | (02))
#define EFI_SPECIFICATION_VERSION EFI_SYSTEM_TABLE_REVISION
#define EFI_SYSTEM_TABLE_REVISION EFI_2_8_SYSTEM_TABLE_REVISION
typedef struct {
	EFI_TABLE_HEADER 					Hdr;
	CHAR16 								*FirmwareVendor;
	UINT32 								FirmwareRevision;
	EFI_HANDLE 							ConsoleInHandle;
	EFI_SIMPLE_TEXT_INPUT_PROTOCOL 		*ConIn;
	EFI_HANDLE 							ConsoleOutHandle;
	EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL 	*ConOut;
	EFI_HANDLE 							StandardErrorHandle;
	EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL 	*StdErr;
	EFI_RUNTIME_SERVICES 				*RuntimeServices;
	EFI_BOOT_SERVICES 					*BootServices;
	UINTN 								NumberOfTableEntries;
	EFI_CONFIGURATION_TABLE 			*ConfigurationTable;
} EFI_SYSTEM_TABLE;

typedef
EFI_STATUS
(EFIAPI *EFI_IMAGE_ENTRY_POINT) (
	IN EFI_HANDLE ImageHandle,
	IN EFI_SYSTEM_TABLE *SystemTable
);

#endif