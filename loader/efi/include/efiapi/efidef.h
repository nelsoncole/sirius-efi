/**
 *	Copyright (c) 2013 Sirius Corporation
 *	Nelson Sapalo da Siva Cole
 *	Lubango, 29 de Julho de 2019 - Hora: 03h21
 *	File Name: efidef.h
 **/
 
#ifndef __EFI_DEF_H__
#define __EFI_DEF_H__

	
// Common UEFI data types
typedef char BOOLEAN;
typedef int INTN;
typedef unsigned UINTN;

typedef char INT8;
typedef unsigned char UINT8;

typedef short INT16;
typedef unsigned short UINT16; 
 
typedef long INT32;
typedef unsigned long UINT32;

typedef signed long long INT64;
typedef unsigned long long UINT64;

//typedef signed INT128;
//typedef unsigned UNT128;

typedef char CHAR8;
typedef short unsigned int CHAR16;

typedef void VOID;
 
// EFI_GUID // 128-bit buffer containing a unique identifier value. Unless otherwise specified, aligned on a 64-bit boundary.
typedef struct {
	UINT32 Data1;
	UINT16 Data2;
	UINT16 Data3;
	UINT8 Data4[8];
} EFI_GUID;

typedef UINTN EFI_STATUS;
typedef void *EFI_HANDLE;
typedef void *EFI_EVENT;
typedef UINT64 EFI_LBA;
typedef UINTN EFI_TPL;

//*******************************************************
//EFI_VIRTUAL_ADDRESS
//*******************************************************
//typedef UINT64 EFI_VIRTUAL_ADDRESS;
//*******************************************************
//EFI_PHYSICAL_ADDRESS
//*******************************************************
//typedef UINT64 EFI_PHYSICAL_ADDRESS;


#if defined(__x86_64__) || defined(__aarch64__)
	typedef UINT64 EFI_VIRTUAL_ADDRESS;
	typedef UINT64 EFI_PHYSICAL_ADDRESS;
	
#elif defined(__i386__) || defined(__arm__)
	typedef UINT32 EFI_PHYSICAL_ADDRESS;
	typedef UINT32 EFI_VIRTUAL_ADDRESS;
#else
#error YOUR ARCH HERE
#endif

typedef struct {          
    UINT16      Year;       // 1998 - 20XX
    UINT8       Month;      // 1 - 12
    UINT8       Day;        // 1 - 31
    UINT8       Hour;       // 0 - 23
    UINT8       Minute;     // 0 - 59
    UINT8       Second;     // 0 - 59
    UINT8       Pad1;
    UINT32      Nanosecond; // 0 - 999,999,999
    INT16       TimeZone;   // -1440 to 1440 or 2047
    UINT8       Daylight;
    UINT8       Pad2;
} EFI_TIME;

// EFI_MAC_ADDRESS //  32-byte buffer containing a network Media Access Control address.
typedef struct {
    UINT8                   Addr[32];
} EFI_MAC_ADDRESS;

// EFI_IPv4_ADDRESS // 4-byte buffer. An IPv4 internet protocol address.
typedef struct {
    UINT8                   Addr[4];
} EFI_IPv4_ADDRESS;

// EFI_IPv6_ADDRESS // 16-byte buffer. An IPv6 internet protocol address.
typedef struct {
    UINT8                   Addr[16];
} EFI_IPv6_ADDRESS;

// EFI_IP_ADDRESS //  16-byte buffer aligned on a 4-byte boundary. An IPv4 or IPv6 internet protocol address.
typedef struct {
    UINT32 ReceivedQueueTimeoutValue;
    UINT32 TransmitQueueTimeoutValue;
    UINT16 ProtocolTypeFilter;
    BOOLEAN EnableUnicastReceive;
    BOOLEAN EnableMulticastReceive;
    BOOLEAN EnableBroadcastReceive;
    BOOLEAN EnablePromiscuousReceive;
    BOOLEAN FlushQueuesOnReset;
    BOOLEAN EnableReceiveTimestamps;
    BOOLEAN DisableBackgroundPolling;
} EFI_MANAGED_NETWORK_CONFIG_DATA;

#ifndef EFIAPI                  // Forces EFI calling conventions reguardless of compiler options 
    #ifdef _MSC_EXTENSIONS
        #define EFIAPI __cdecl  // Force C calling convention for Microsoft C compiler 
    #elif defined(HAVE_USE_MS_ABI)
        // Force amd64/ms calling conventions.
        #define EFIAPI __attribute__((ms_abi))
    #else
        #define EFIAPI          // Substitute expresion to force C calling convention 
    #endif
#endif

#ifndef IN 	// Prototype argument decoration for EFI parameters to indicate their direction
    #define IN 	// IN - argument is passed into the function
    #define OUT	// OUT - argument (pointer) is returned from the function
    #define OPTIONAL	// OPTIONAL - argument is optional
#endif


#ifndef CONST
   #define CONST const
#endif
#ifndef TRUE
    #define TRUE    ((BOOLEAN) 1)
    #define FALSE   ((BOOLEAN) 0)
#endif

#ifndef NULL
    #define NULL    ((VOID *) 0)
#endif

/*
 *
 *
 *
 *
 *
 *				EFI Status Codes
 *
 *
 *
 *
 *
 */
 
// Error Codes
#define EFI_ERROR(x)  (((INTN) x) < 0)
#define EFI_SUCCESS 				0
#define EFI_LOAD_ERROR				1
#define	EFI_INVALID_PARAMETER		2
#define	EFI_UNSUPPORTED				3
#define	EFI_BAD_BUFFER_SIZE			4
#define	EFI_BUFFER_TOO_SMALL		5
#define	EFI_NOT_READY				6
#define	EFI_DEVICE_ERROR			7
#define	EFI_WRITE_PROTECTED			8
#define	EFI_OUT_OF_RESOURCES		9
#define	EFI_VOLUME_CORRUPTED		10
#define	EFI_VOLUME_FULL				11
#define	EFI_NO_MEDIA				12
#define	EFI_MEDIA_CHANGED			13
#define	EFI_NOT_FOUND				14
#define	EFI_ACCESS_DENIED			15
#define	EFI_NO_RESPONSE				16
#define	EFI_NO_MAPPING				17
#define	EFI_TIMEOUT					18
#define	EFI_NOT_STARTED				19
#define	EFI_ALREADY_STARTED			20
#define	EFI_ABORTED					21
#define	EFI_ICMP_ERROR				22
#define	EFI_TFTP_ERROR				23
#define	EFI_PROTOCOL_ERROR			24
#define	EFI_INCOMPATIBLE_VERSION	25
#define	EFI_SECURITY_VIOLATION		26
#define	EFI_CRC_ERROR				27
#define	EFI_END_OF_MEDIA			28
#define	EFI_END_OF_FILE				31
#define	EFI_INVALID_LANGUAGE		32
#define	EFI_COMPROMISED_DATA		33
#define	EFI_IP_ADDRESS_CONFLICT		34
#define	EFI_HTTP_ERROR				35

// Warning Codes
#define EFI_WARNING(x) x
#define	EFI_WARN_UNKNOWN_GLYPH		1
#define	EFI_WARN_DELETE_FAILURE		2
#define	EFI_WARN_WRITE_FAILURE		3
#define	EFI_WARN_BUFFER_TOO_SMALL	4
#define	EFI_WARN_STALE_DATA			5
#define	EFI_WARN_FILE_SYSTEM		6
#define	EFI_WARN_RESET_REQUIRED		7




// FILE
#define EFI_FIELD_OFFSET(TYPE,Field) ((UINTN)(&(((TYPE *) 0)->Field)))
//


//MEMORY

#define EFI_PAGE_SIZE   4096
#define EFI_PAGE_MASK   0xFFF
#define EFI_PAGE_SHIFT  12

#define EFI_SIZE_TO_PAGES(a)  \
    ( ((a) >> EFI_PAGE_SHIFT) + ((a) & EFI_PAGE_MASK ? 1 : 0) )










#endif