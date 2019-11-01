/**
 *	Copyright (c) 2013 Sirius Corporation
 *	Nelson Sapalo da Siva Cole
 *	Lubango, 3 de Agosto de 2019 - Hora: 09h35
 *	File Name: efiprotocol.h
 **/
 
#ifndef __EFI_PROTOCOL_H__
#define __EFI_PROTOCOL_H__



/*

	UEFI Console Support



 */
 
 
 
/*
 *
 *
 *
 *
 *
 *				EFI Simple Text Input Protocol
 *
 *
 *
 *
 *
 */
#define EFI_SIMPLE_TEXT_INPUT_PROTOCOL_GUID \
{0x387477c1,0x69c7,0x11d2,\
{0x8e,0x39,0x00,0xa0,0xc9,0x69,0x72,0x3b}}

struct _EFI_SIMPLE_TEXT_INPUT_PROTOCOL;

typedef
EFI_STATUS
(EFIAPI *EFI_INPUT_RESET) (
	IN struct _EFI_SIMPLE_TEXT_INPUT_PROTOCOL *This,
	IN BOOLEAN ExtendedVerification
);

// EFI_INPUT_KEY
typedef struct {
	UINT16 ScanCode;
	CHAR16 UnicodeChar;
} EFI_INPUT_KEY;

typedef
EFI_STATUS
(EFIAPI *EFI_INPUT_READ_KEY) (
	IN struct _EFI_SIMPLE_TEXT_INPUT_PROTOCOL *This,
	OUT EFI_INPUT_KEY *Key
);

typedef struct _EFI_SIMPLE_TEXT_INPUT_PROTOCOL {
	EFI_INPUT_RESET 	Reset;
	EFI_INPUT_READ_KEY 	ReadKeyStroke;
	EFI_EVENT 			WaitForKey;
} EFI_SIMPLE_TEXT_INPUT_PROTOCOL;

/*
 *
 *
 *
 *
 *
 *				EFI Simple Text Input Ex Protocol
 *
 *
 *
 *
 *
 */
#define EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL_GUID \
{0xdd9e7534, 0x7762, 0x4698, \
{0x8c, 0x14, 0xf5, 0x85, 0x17, 0xa6, 0x25, 0xaa}}

struct _EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL;

#define EFI_SHIFT_STATE_VALID 0x80000000
#define EFI_RIGHT_SHIFT_PRESSED0x00000001
#define EFI_LEFT_SHIFT_PRESSED0x00000002
#define EFI_RIGHT_CONTROL_PRESSED0x00000004
#define EFI_LEFT_CONTROL_PRESSED0x00000008
#define EFI_RIGHT_ALT_PRESSED0x00000010
#define EFI_LEFT_ALT_PRESSED0x00000020
#define EFI_RIGHT_LOGO_PRESSED0x00000040
#define EFI_LEFT_LOGO_PRESSED0x00000080
#define EFI_MENU_KEY_PRESSED0x00000100
#define EFI_SYS_REQ_PRESSED0x00000200
//*******************************************************
// EFI_KEY_TOGGLE_STATE
//*******************************************************
typedef UINT8 EFI_KEY_TOGGLE_STATE;

#define EFI_TOGGLE_STATE_VALID0x80
#define EFI_KEY_STATE_EXPOSED0x40
#define EFI_SCROLL_LOCK_ACTIVE0x01
#define EFI_NUM_LOCK_ACTIVE0x02
#define EFI_CAPS_LOCK_ACTIVE0x04


typedef
EFI_STATUS
(EFIAPI *EFI_INPUT_RESET_EX) (
	IN struct _EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,
	IN BOOLEAN ExtendedVerification
);


// EFI_KEY_STATE
//
// Any Shift or Toggle State that is valid should have
// high order bit set.
//
typedef struct EFI_KEY_STATE {
	UINT32 KeyShiftState;
	EFI_KEY_TOGGLE_STATE KeyToggleState;
} EFI_KEY_STATE;
// EFI_KEY_DATA
typedef struct {
	EFI_INPUT_KEY Key;
	EFI_KEY_STATE KeyState;
} EFI_KEY_DATA;
typedef
EFI_STATUS
(EFIAPI *EFI_INPUT_READ_KEY_EX) (
	IN struct _EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,
	OUT EFI_KEY_DATA *KeyData
);

typedef
EFI_STATUS
(EFIAPI *EFI_SET_STATE) (
	IN struct _EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,
	IN EFI_KEY_TOGGLE_STATE *KeyToggleState
);

// EFI_KEY_NOTIFY
typedef
EFI_STATUS
(EFIAPI *EFI_KEY_NOTIFY_FUNCTION) (
	IN EFI_KEY_DATA*KeyData
);
typedef
EFI_STATUS
(EFIAPI *EFI_REGISTER_KEYSTROKE_NOTIFY) (
	IN struct _EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,
	IN EFI_KEY_DATA *KeyData,
	IN EFI_KEY_NOTIFY_FUNCTION KeyNotificationFunction,
	OUT VOID **NotifyHandle
);

typedef
EFI_STATUS
(EFIAPI *EFI_UNREGISTER_KEYSTROKE_NOTIFY) (
	IN struct _EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,
	IN VOID *NotificationHandle
);




typedef struct _EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL{
	EFI_INPUT_RESET_EX				Reset;
	EFI_INPUT_READ_KEY_EX			ReadKeyStrokeEx;
	EFI_EVENT						WaitForKeyEx;
	EFI_SET_STATE					SetState;
	EFI_REGISTER_KEYSTROKE_NOTIFY	RegisterKeyNotify;
	EFI_UNREGISTER_KEYSTROKE_NOTIFY	UnregisterKeyNotify;
} EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL;



/*
 *
 *
 *
 *
 *
 *				EFI Simple Text Output Protocol
 *
 *
 *
 *
 *
 */
#define EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL_GUID \
{0x387477c2,0x69c7,0x11d2,\
{0x8e,0x39,0x00,0xa0,0xc9,0x69,0x72,0x3b}}

struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;

// UNICODE DRAWING CHARACTERS
#define BOXDRAW_HORIZONTAL 0x2500
#define BOXDRAW_VERTICAL 0x2502
#define BOXDRAW_DOWN_RIGHT 0x250c
#define BOXDRAW_DOWN_LEFT 0x2510
#define BOXDRAW_UP_RIGHT 0x2514
#define BOXDRAW_UP_LEFT 0x2518
#define BOXDRAW_VERTICAL_RIGHT 0x251c
#define BOXDRAW_VERTICAL_LEFT 0x2524
#define BOXDRAW_DOWN_HORIZONTAL 0x252c
#define BOXDRAW_UP_HORIZONTAL 0x2534
#define BOXDRAW_VERTICAL_HORIZONTAL 0x253c

#define BOXDRAW_DOUBLE_HORIZONTAL 0x2550
#define BOXDRAW_DOUBLE_VERTICAL 0x2551
#define BOXDRAW_DOWN_RIGHT_DOUBLE 0x2552
#define BOXDRAW_DOWN_DOUBLE_RIGHT 0x2553
#define BOXDRAW_DOUBLE_DOWN_RIGHT 0x2554
#define BOXDRAW_DOWN_LEFT_DOUBLE 0x2555
#define BOXDRAW_DOWN_DOUBLE_LEFT 0x2556
#define BOXDRAW_DOUBLE_DOWN_LEFT 0x2557

#define BOXDRAW_UP_RIGHT_DOUBLE 0x2558
#define BOXDRAW_UP_DOUBLE_RIGHT 0x2559
#define BOXDRAW_DOUBLE_UP_RIGHT 0x255a

#define BOXDRAW_UP_LEFT_DOUBLE 0x255b
#define BOXDRAW_UP_DOUBLE_LEFT 0x255c
#define BOXDRAW_DOUBLE_UP_LEFT 0x255d

#define BOXDRAW_VERTICAL_RIGHT_DOUBLE 0x255e
#define BOXDRAW_VERTICAL_DOUBLE_RIGHT 0x255f
#define BOXDRAW_DOUBLE_VERTICAL_RIGHT 0x2560

#define BOXDRAW_VERTICAL_LEFT_DOUBLE 0x2561
#define BOXDRAW_VERTICAL_DOUBLE_LEFT 0x2562
#define BOXDRAW_DOUBLE_VERTICAL_LEFT 0x2563

#define BOXDRAW_DOWN_HORIZONTAL_DOUBLE 0x2564
#define BOXDRAW_DOWN_DOUBLE_HORIZONTAL 0x2565
#define BOXDRAW_DOUBLE_DOWN_HORIZONTAL 0x2566

#define BOXDRAW_UP_HORIZONTAL_DOUBLE 0x2567
#define BOXDRAW_UP_DOUBLE_HORIZONTAL 0x2568
#define BOXDRAW_DOUBLE_UP_HORIZONTAL 0x2569

#define BOXDRAW_VERTICAL_HORIZONTAL_DOUBLE 0x256a
#define BOXDRAW_VERTICAL_DOUBLE_HORIZONTAL 0x256b
#define BOXDRAW_DOUBLE_VERTICAL_HORIZONTAL 0x256c

// EFI Required Block Elements Code Chart
#define BLOCKELEMENT_FULL_BLOCK 0x2588
#define BLOCKELEMENT_LIGHT_SHADE 0x2591
// EFI Required Geometric Shapes Code Chart
#define GEOMETRICSHAPE_UP_TRIANGLE 0x25b2
#define GEOMETRICSHAPE_RIGHT_TRIANGLE 0x25ba
#define GEOMETRICSHAPE_DOWN_TRIANGLE 0x25bc
#define GEOMETRICSHAPE_LEFT_TRIANGLE 0x25c4
// EFI Required Arrow shapes
#define ARROW_UP 0x2191
#define ARROW_DOWN 0x2193



// Attributes
#define EFI_BLACK 0x00
#define EFI_BLUE 0x01
#define EFI_GREEN 0x02
#define EFI_CYAN 0x03
#define EFI_RED 0x04
#define EFI_MAGENTA 0x05
#define EFI_BROWN 0x06
#define EFI_LIGHTGRAY 0x07
#define EFI_BRIGHT 0x08
#define EFI_DARKGRAY (EFI_BLACK | EFI_BRIGHT) 0x08
#define EFI_LIGHTBLUE 0x09
#define EFI_LIGHTGREEN 0x0A
#define EFI_LIGHTCYAN 0x0B
#define EFI_LIGHTRED 0x0C
#define EFI_LIGHTMAGENTA 0x0D
#define EFI_YELLOW 0x0E
#define EFI_WHITE 0x0F
#define EFI_BACKGROUND_BLACK 0x00
#define EFI_BACKGROUND_BLUE 0x10
#define EFI_BACKGROUND_GREEN 0x20
#define EFI_BACKGROUND_CYAN 0x30
#define EFI_BACKGROUND_RED 0x40
#define EFI_BACKGROUND_MAGENTA 0x50
#define EFI_BACKGROUND_BROWN 0x60
#define EFI_BACKGROUND_LIGHTGRAY 0x70
//
// Macro to accept color values in their raw form to create
// a value that represents both a foreground and background
// color in a single byte.
// For Foreground, and EFI_* value is valid from EFI_BLACK(0x00)
// to EFI_WHITE (0x0F).
// For Background, only EFI_BLACK, EFI_BLUE, EFI_GREEN,
// EFI_CYAN, EFI_RED, EFI_MAGENTA, EFI_BROWN, and EFI_LIGHTGRAY
// are acceptable.
//
// Do not use EFI_BACKGROUND_xxx values with this macro.
#define EFI_TEXT_ATTR(Foreground,Background) \
((Foreground) | ((Background) << 4))


typedef
EFI_STATUS
(EFIAPI *EFI_TEXT_RESET) (
	IN struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
	IN BOOLEAN ExtendedVerification
);

typedef
EFI_STATUS
(EFIAPI *EFI_TEXT_STRING) (
	IN struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
	IN CHAR16 *String
);

typedef
EFI_STATUS
(EFIAPI *EFI_TEXT_TEST_STRING) (
	IN struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
	IN CHAR16 *String
);

typedef
EFI_STATUS
(EFIAPI *EFI_TEXT_QUERY_MODE) (
	IN struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
	IN UINTN ModeNumber,
	OUT UINTN *Columns,
	OUT UINTN *Rows
);

typedef
EFI_STATUS
(* EFIAPI EFI_TEXT_SET_MODE) (
	IN struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
	IN UINTN ModeNumber
);

typedef
EFI_STATUS
(EFIAPI *EFI_TEXT_SET_ATTRIBUTE) (
	IN struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
	IN UINTN Attribute
);

typedef
EFI_STATUS
(EFIAPI *EFI_TEXT_CLEAR_SCREEN) (
	IN struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This
);

typedef
EFI_STATUS
(EFIAPI *EFI_TEXT_SET_CURSOR_POSITION) (
	IN struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
	IN UINTN Column,
	IN UINTN Row
);

typedef
EFI_STATUS
(EFIAPI *EFI_TEXT_ENABLE_CURSOR) (
	IN struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
	IN BOOLEAN Visible
);

typedef struct {
	INT32 		MaxMode;
	// current settings
	INT32 		Mode;
	INT32 		Attribute;
	INT32 		CursorColumn;
	INT32 		CursorRow;
	BOOLEAN 	CursorVisible;
} SIMPLE_TEXT_OUTPUT_MODE;


typedef struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL {
	EFI_TEXT_RESET 					Reset;
	EFI_TEXT_STRING 				OutputString;
	EFI_TEXT_TEST_STRING 			TestString; 
	EFI_TEXT_QUERY_MODE 			QueryMode; 
	EFI_TEXT_SET_MODE 				SetMode;
	EFI_TEXT_SET_ATTRIBUTE 			SetAttribute;
	EFI_TEXT_CLEAR_SCREEN 			ClearScreen;
	EFI_TEXT_SET_CURSOR_POSITION 	SetCursorPosition;
	EFI_TEXT_ENABLE_CURSOR 			EnableCursor;
	SIMPLE_TEXT_OUTPUT_MODE 		*Mode;
} EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;


/*

	UEFI Graphics Output Protocol  



 */
 
 
#define EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID \
{0x9042a9de,0x23dc,0x4a38,\
{0x96,0xfb,0x7a,0xde,0xd0,0x80,0x51,0x6a}}

struct _EFI_GRAPHICS_OUTPUT_PROTOCOL;


typedef struct {
	UINT32 RedMask;
	UINT32 GreenMask;
	UINT32 BlueMask;
	UINT32 ReservedMask;
} EFI_PIXEL_BITMASK;

typedef enum {
	PixelRedGreenBlueReserved8BitPerColor,
	PixelBlueGreenRedReserved8BitPerColor,
	PixelBitMask,
	PixelBltOnly,
	PixelFormatMax
} EFI_GRAPHICS_PIXEL_FORMAT;

typedef struct { 
	UINT32 Version; 
	UINT32 HorizontalResolution; 
	UINT32 VerticalResolution; 
	EFI_GRAPHICS_PIXEL_FORMAT PixelFormat; 
	EFI_PIXEL_BITMASK PixelInformation; 
	UINT32 PixelsPerScanLine;
} EFI_GRAPHICS_OUTPUT_MODE_INFORMATION;

/*
INTN
GetPixelElementSize (
IN EFI_PIXEL_BITMASK *PixelBits
)
{
	INTN HighestPixel = -1;
	INTN BluePixel;
	INTN RedPixel;
	INTN GreenPixel;
	INTN RsvdPixel;
	BluePixel = FindHighestSetBit (PixelBits->BlueMask);
	RedPixel = FindHighestSetBit (PixelBits->RedMask);
	GreenPixel = FindHighestSetBit (PixelBits->GreenMask);
	RsvdPixel = FindHighestSetBit (PixelBits->ReservedMask);
	HighestPixel = max (BluePixel, RedPixel);
	HighestPixel = max (HighestPixel, GreenPixel);
	HighestPixel = max (HighestPixel, RsvdPixel);
	return HighestPixel;
}

EFI_PHYSICAL_ADDRESS NewPixelAddress;
EFI_PHYSICAL_ADDRESS CurrentPixelAddress;
EFI_GRAPHICS_OUTPUT_MODE_INFORMATION OutputInfo;
INTN PixelElementSize;
switch (OutputInfo.PixelFormat) {
	case PixelBitMask:
		PixelElementSize = GetPixelElementSize (&OutputInfo.PixelInformation);
	break;
	case PixelBlueGreenRedReserved8BitPerColor:
	case PixelRedGreenBlueReserved8BitPerColor:
		PixelElementSize = sizeof (EFI_GRAPHICS_OUTPUT_BLT_PIXEL);
	break;
}
//
// NewPixelAddress after execution points to the pixel
// positioned one line below the one pointed by
// CurrentPixelAddress
//
NewPixelAddress = CurrentPixelAddress + (PixelElementSize * OutputInfo.PixelsPerScanLine); */


typedef struct { 
	UINT32 MaxMode; 
	UINT32 Mode; 
	EFI_GRAPHICS_OUTPUT_MODE_INFORMATION *Info;
	UINTN SizeOfInfo; 
	EFI_PHYSICAL_ADDRESS FrameBufferBase; 
	UINTN FrameBufferSize;
} EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE;

typedef
EFI_STATUS
(EFIAPI *EFI_GRAPHICS_OUTPUT_PROTOCOL_QUERY_MODE) (
	IN struct _EFI_GRAPHICS_OUTPUT_PROTOCOL *This,
	IN UINT32 ModeNumber,
	OUT UINTN *SizeOfInfo,
	OUT EFI_GRAPHICS_OUTPUT_MODE_INFORMATION **Info
);

typedef
EFI_STATUS
(EFIAPI *EFI_GRAPHICS_OUTPUT_PROTOCOL_SET_MODE) (
	IN struct _EFI_GRAPHICS_OUTPUT_PROTOCOL *This,
	IN UINT32 ModeNumber
);

typedef struct {
	UINT8 Blue;
	UINT8 Green;
	UINT8 Red;
	UINT8 Reserved;
} EFI_GRAPHICS_OUTPUT_BLT_PIXEL;
typedef enum {
	EfiBltVideoFill,
	EfiBltVideoToBltBuffer,
	EfiBltBufferToVideo,
	EfiBltVideoToVideo,
	EfiGraphicsOutputBltOperationMax
} EFI_GRAPHICS_OUTPUT_BLT_OPERATION;

typedef
EFI_STATUS
(EFIAPI *EFI_GRAPHICS_OUTPUT_PROTOCOL_BLT) (
	IN struct _EFI_GRAPHICS_OUTPUT_PROTOCOL *This,
	IN OUT EFI_GRAPHICS_OUTPUT_BLT_PIXEL *BltBuffer, OPTIONAL
	IN EFI_GRAPHICS_OUTPUT_BLT_OPERATION BltOperation,
	IN UINTN SourceX,
	IN UINTN SourceY,
	IN UINTN DestinationX,
	IN UINTN DestinationY,
	IN UINTN Width,
	IN UINTN Height,
	IN UINTN Delta OPTIONAL
);

 
typedef struct _EFI_GRAPHICS_OUTPUT_PROTOCOL {
	EFI_GRAPHICS_OUTPUT_PROTOCOL_QUERY_MODE QueryMode;
	EFI_GRAPHICS_OUTPUT_PROTOCOL_SET_MODE SetMode;
	EFI_GRAPHICS_OUTPUT_PROTOCOL_BLT Blt;
	EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE *Mode;
} EFI_GRAPHICS_OUTPUT_PROTOCOL;
 


/*

	UEFI Media Access



 */
 
// Load File Protocol
 
#define EFI_LOAD_FILE_PROTOCOL_GUID \
{0x56EC3091,0x954C,0x11d2,\
{0x8e,0x3f,0x00,0xa0, 0xc9,0x69,0x72,0x3b}}

struct _EFI_LOAD_FILE_PROTOCOL;
struct _EFI_DEVICE_PATH_PROTOCOL;


typedef
EFI_STATUS
(EFIAPI *EFI_LOAD_FILE) (
	IN struct _EFI_LOAD_FILE_PROTOCOL *This,
	IN struct _EFI_DEVICE_PATH_PROTOCOL *FilePath,
	IN BOOLEAN BootPolicy,
	IN OUT UINTN *BufferSize,
	IN VOID *Buffer OPTIONAL
);

typedef struct _EFI_LOAD_FILE_PROTOCOL {
	EFI_LOAD_FILE LoadFile;
} EFI_LOAD_FILE_PROTOCOL;


// Load File 2 Protocol

#define EFI_LOAD_FILE2_PROTOCOL_GUID \
{ 0x4006c0c1, 0xfcb3, 0x403e, \
{ 0x99, 0x6d, 0x4a, 0x6c, 0x87, 0x24, 0xe0, 0x6d }}

typedef EFI_LOAD_FILE_PROTOCOL EFI_LOAD_FILE2_PROTOCOL;

// Simple File System Protocol

#define EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID \
{0x0964e5b22,0x6459,0x11d2,\
{0x8e,0x39,0x00,0xa0,0xc9,0x69,0x72,0x3b}}


#define EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_REVISION 0x00010000

struct _EFI_SIMPLE_FILE_SYSTEM_PROTOCOL;
struct _EFI_FILE_PROTOCOL;

#define EFI_FILE_PROTOCOL_REVISION 0x00010000
#define EFI_FILE_PROTOCOL_REVISION2 0x00020000
#define EFI_FILE_PROTOCOL_LATEST_REVISION EFI_FILE_PROTOCOL_REVISION2

//*******************************************************
// Open Modes
//*******************************************************
#define EFI_FILE_MODE_READ 0x0000000000000001
#define EFI_FILE_MODE_WRITE 0x0000000000000002
#define EFI_FILE_MODE_CREATE 0x8000000000000000
//*******************************************************
// File Attributes
//*******************************************************
#define EFI_FILE_READ_ONLY 0x0000000000000001
#define EFI_FILE_HIDDEN 0x0000000000000002
#define EFI_FILE_SYSTEM 0x0000000000000004
#define EFI_FILE_RESERVED 0x0000000000000008
#define EFI_FILE_DIRECTORY 0x0000000000000010
#define EFI_FILE_ARCHIVE 0x0000000000000020
#define EFI_FILE_VALID_ATTR 0x0000000000000037
typedef
EFI_STATUS
(EFIAPI *EFI_FILE_OPEN) (
	IN struct _EFI_FILE_PROTOCOL *This,
	OUT struct _EFI_FILE_PROTOCOL **NewHandle,
	IN CHAR16 *FileName,
	IN UINT64 OpenMode,
	IN UINT64 Attributes
);

typedef
EFI_STATUS
(EFIAPI *EFI_FILE_CLOSE) (
	IN struct _EFI_FILE_PROTOCOL *This
);

typedef
EFI_STATUS
(EFIAPI *EFI_FILE_DELETE) (
	IN struct _EFI_FILE_PROTOCOL *This
);

typedef
EFI_STATUS
(EFIAPI *EFI_FILE_READ) (
	IN struct _EFI_FILE_PROTOCOL *This,
	IN OUT UINTN *BufferSize,
	OUT VOID *Buffer
);

typedef
EFI_STATUS
(EFIAPI *EFI_FILE_WRITE) (
	IN struct _EFI_FILE_PROTOCOL *This,
	IN OUT UINTN *BufferSize,
	IN VOID *Buffer
);


typedef struct {
	EFI_EVENT Event;
	EFI_STATUS Status;
	UINTN BufferSize;
	VOID *Buffer;
} EFI_FILE_IO_TOKEN;

typedef
EFI_STATUS
(EFIAPI *EFI_FILE_OPEN_EX) (
	IN struct _EFI_FILE_PROTOCOL *This,
	OUT struct _EFI_FILE_PROTOCOL **NewHandle,
	IN CHAR16 *FileName,
	IN UINT64 OpenMode,
	IN UINT64 Attributes,
	IN OUT EFI_FILE_IO_TOKEN *Token
);

typedef
EFI_STATUS
(EFIAPI *EFI_FILE_READ_EX) (
	IN struct _EFI_FILE_PROTOCOL *This,
	IN OUT EFI_FILE_IO_TOKEN *Token
);

typedef
EFI_STATUS
(EFIAPI *EFI_FILE_WRITE_EX) (
	IN struct _EFI_FILE_PROTOCOL *This,
	IN OUT EFI_FILE_IO_TOKEN *Token
);

typedef
EFI_STATUS
(EFIAPI *EFI_FILE_FLUSH_EX) (
	IN struct _EFI_FILE_PROTOCOL *This,
	IN OUT EFI_FILE_IO_TOKEN *Token
);

typedef
EFI_STATUS
(EFIAPI *EFI_FILE_SET_POSITION) (
	IN struct _EFI_FILE_PROTOCOL *This,
	IN UINT64 Position
);

typedef
EFI_STATUS
(EFIAPI *EFI_FILE_GET_POSITION) (
	IN struct _EFI_FILE_PROTOCOL *This,
	OUT UINT64 *Position
);

typedef
EFI_STATUS
(EFIAPI *EFI_FILE_GET_INFO) (
	IN struct _EFI_FILE_PROTOCOL *This,
	IN EFI_GUID *InformationType,
	IN OUT UINTN *BufferSize,
	OUT VOID *Buffer
);

typedef
EFI_STATUS
(EFIAPI *EFI_FILE_SET_INFO) (
	IN struct _EFI_FILE_PROTOCOL *This,
	IN EFI_GUID *InformationType,
	IN UINTN BufferSize,
	IN VOID *Buffer
);

typedef
EFI_STATUS
(EFIAPI *EFI_FILE_FLUSH) (
	IN struct _EFI_FILE_PROTOCOL *This
);

typedef struct _EFI_FILE_PROTOCOL {
	UINT64 Revision;
	EFI_FILE_OPEN Open;
	EFI_FILE_CLOSE Close;
	EFI_FILE_DELETE Delete;
	EFI_FILE_READ Read;
	EFI_FILE_WRITE Write;
	EFI_FILE_GET_POSITION GetPosition;
	EFI_FILE_SET_POSITION SetPosition;
	EFI_FILE_GET_INFO GetInfo;
	EFI_FILE_SET_INFO SetInfo;
	EFI_FILE_FLUSH Flush;
	EFI_FILE_OPEN_EX OpenEx; // Added for revision 2
	EFI_FILE_READ_EX ReadEx; // Added for revision 2
	EFI_FILE_WRITE_EX WriteEx; // Added for revision 2
	EFI_FILE_FLUSH_EX FlushEx; // Added for revision 2
} EFI_FILE_PROTOCOL;


typedef
EFI_STATUS
(EFIAPI *EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_OPEN_VOLUME) (
	IN struct _EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *This,
	OUT EFI_FILE_PROTOCOL **Root
);

typedef struct _EFI_SIMPLE_FILE_SYSTEM_PROTOCOL {
	UINT64 Revision;
	EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_OPEN_VOLUME OpenVolume;
} EFI_SIMPLE_FILE_SYSTEM_PROTOCOL; 
 
 
 
// EFI File Info

#define EFI_FILE_INFO_ID   \
    { 0x9576e92, 0x6d3f, 0x11d2, {0x8e, 0x39, 0x0, 0xa0, 0xc9, 0x69, 0x72, 0x3b} }
 
//*******************************************************
// File Attribute Bits
//*******************************************************
#define EFI_FILE_READ_ONLY 0x0000000000000001
#define EFI_FILE_HIDDEN 0x0000000000000002
#define EFI_FILE_SYSTEM 0x0000000000000004
#define EFI_FILE_RESERVED 0x0000000000000008
#define EFI_FILE_DIRECTORY 0x0000000000000010
#define EFI_FILE_ARCHIVE 0x0000000000000020
#define EFI_FILE_VALID_ATTR 0x0000000000000037
 
typedef struct {
	UINT64 Size;
	UINT64 FileSize;
	UINT64 PhysicalSize;
	EFI_TIME CreateTime;
	EFI_TIME LastAccessTime;
	EFI_TIME ModificationTime;
	UINT64 Attribute;
	CHAR16 FileName[1];
} EFI_FILE_INFO;


#define SIZE_OF_EFI_FILE_INFO EFI_FIELD_OFFSET(EFI_FILE_INFO,FileName)

// EFI File System Info

#define EFI_FILE_SYSTEM_INFO_ID \
{0x09576e93,0x6d3f,0x11d2,0x8e39,0x00,0xa0,0xc9,0x69,0x72,\
0x3b}

typedef struct {
	UINT64 Size;
	BOOLEAN ReadOnly;
	UINT64 VolumeSize;
	UINT64 FreeSpace;
	UINT32 BlockSize;
	CHAR16 VolumeLabel[1];
} EFI_FILE_SYSTEM_INFO;

// EFI File System Volume Label

#define EFI_FILE_SYSTEM_VOLUME_LABEL_ID \
{0xdb47d7d3,0xfe81,0x11d3,0x9a35,\
{0x00,0x90,0x27,0x3f,0xC1,0x4d}}


typedef struct {
	CHAR16 *VolumeLabel; //CHAR16 VolumeLabel[];
} EFI_FILE_SYSTEM_VOLUME_LABEL;


/*


	EFI Block I/O Protocol



 */




#define EFI_BLOCK_IO_PROTOCOL_GUID \
{0x964e5b21,0x6459,0x11d2,\
{0x8e,0x39,0x00,0xa0,0xc9,0x69,0x72,0x3b}}

#define EFI_BLOCK_IO_PROTOCOL_REVISION2 0x00020001
#define EFI_BLOCK_IO_PROTOCOL_REVISION3 ((2<<16) | (31))

struct _EFI_BLOCK_IO_PROTOCOL;

//*******************************************************
// EFI_BLOCK_IO_MEDIA
//*******************************************************
typedef struct {
	UINT32 MediaId;
	BOOLEAN RemovableMedia;
	BOOLEAN MediaPresent;
	BOOLEAN LogicalPartition;
	BOOLEAN ReadOnly;
	BOOLEAN WriteCaching;
	UINT32 BlockSize;
	UINT32 IoAlign;
	EFI_LBA LastBlock;
	EFI_LBA LowestAlignedLba; //added in Revision 2
	UINT32 LogicalBlocksPerPhysicalBlock;
	//added in Revision 2
	UINT32 OptimalTransferLengthGranularity;
	// added in Revision 3
} EFI_BLOCK_IO_MEDIA;

typedef
EFI_STATUS
(EFIAPI *EFI_BLOCK_RESET) (
	IN struct _EFI_BLOCK_IO_PROTOCOL *This,
	IN BOOLEAN ExtendedVerification
);

typedef
EFI_STATUS
(EFIAPI *EFI_BLOCK_READ) (
	IN struct _EFI_BLOCK_IO_PROTOCOL *This,
	IN UINT32 MediaId,
	IN EFI_LBA LBA,
	IN UINTN BufferSize,
	OUT VOID *Buffer
);

typedef
EFI_STATUS
(EFIAPI *EFI_BLOCK_WRITE) (
	IN struct _EFI_BLOCK_IO_PROTOCOL *This,
	IN UINT32 MediaId,
	IN EFI_LBA LBA,
	IN UINTN BufferSize,
	IN VOID *Buffer
);

typedef
EFI_STATUS
(EFIAPI *EFI_BLOCK_FLUSH) (
	IN struct _EFI_BLOCK_IO_PROTOCOL *This
);

typedef struct _EFI_BLOCK_IO_PROTOCOL {
	UINT64 Revision;
	EFI_BLOCK_IO_MEDIA *Media;
	EFI_BLOCK_RESET Reset;
	EFI_BLOCK_READ ReadBlocks;
	EFI_BLOCK_WRITE WriteBlocks;
	EFI_BLOCK_FLUSH FlushBlocks;
} EFI_BLOCK_IO_PROTOCOL;


/*


	EFI Block I/O 2 Protocol



 */

#define EFI_BLOCK_IO2_PROTOCOL_GUID \
{0xa77b2472, 0xe282, 0x4e9f, \
{0xa2, 0x45, 0xc2, 0xc0, 0xe2, 0x7b, 0xbc, 0xc1}}

struct _EFI_BLOCK_IO2_PROTOCOL;

typedef
EFI_STATUS
(EFIAPI *EFI_BLOCK_RESET_EX) (
	IN struct _EFI_BLOCK_IO2_PROTOCOL *This,
	IN BOOLEAN ExtendedVerification
);


typedef struct {
	EFI_EVENT Event;
	EFI_STATUS TransactionStatus;
} EFI_BLOCK_IO2_TOKEN;

typedef
EFI_STATUS
(EFIAPI *EFI_BLOCK_READ_EX) (
	IN struct _EFI_BLOCK_IO2_PROTOCOL *This,
	IN UINT32 MediaId,
	IN EFI_LBA LBA,
	IN OUT EFI_BLOCK_IO2_TOKEN *Token,
	IN UINTN BufferSize,
	OUT VOID *Buffer
);


typedef
EFI_STATUS
(EFIAPI *EFI_BLOCK_WRITE_EX) (
	IN struct _EFI_BLOCK_IO2_PROTOCOL *This,
	IN UINT32 MediaId,
	IN EFI_LBA LBA,
	IN OUT EFI_BLOCK_IO2_TOKEN *Token,
	IN UINTN BufferSize,
	IN VOID *Buffer
);

typedef
EFI_STATUS
(EFIAPI *EFI_BLOCK_FLUSH_EX) (
	IN struct _EFI_BLOCK_IO2_PROTOCOL *This,
	IN OUT EFI_BLOCK_IO2_TOKEN *Token
);

typedef struct _EFI_BLOCK_IO2_PROTOCOL {
	EFI_BLOCK_IO_MEDIA *Media;
	EFI_BLOCK_RESET_EX Reset;
	EFI_BLOCK_READ_EX ReadBlocksEx;
	EFI_BLOCK_WRITE_EX WriteBlocksEx;
	EFI_BLOCK_FLUSH_EX FlushBlocksEx;
} EFI_BLOCK_IO2_PROTOCOL;

 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 


#endif