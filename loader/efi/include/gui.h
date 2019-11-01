/**
 *	Copyright (c) 2013 Sirius Corporation
 *	Nelson Sapalo da Siva Cole
 *	Lubango, 13 de Setembro de 2019 - Hora: 18h033
 *	File Name: gui.h
 **/
 
 
#define W_BARRA_TITUL_SIZE 28
#define GW_HANDLE_EDIT 		1
#define GW_HANDLE_BUTTON	2
#define GW_HANDLE_LABEL 	3
#define GW_HANDLE_LIST 		4

#define GW_FLAG_INVISIBLE 	0
#define GW_FLAG_VISIBLE 	1
#define GW_FLAG_READY 		2

#define GW_SMG_FLAG_BIT			0x80000000

#define GW_SMG_BUTTON		0
#define GW_SMG_EDIT			1
#define GW_SMG_LIST			2

#define GW_STYLE(x) x

#define FONT_SIZE_X 8
#define FONT_SIZE_Y 8


typedef struct _GUI_AREA {
	
	UINTN HorizontalStart;
	UINTN VerticalStart;
	UINTN HorizontalEnd;
	UINTN VerticalEnd;

}GUI_AREA;

typedef struct _GUI
{
	// Default
	UINTN	Pitch;
	UINTN  	Bpp;
	UINTN  	Planes;
    UINTN	HorizontalResolution;  		//	width;
	UINTN	VerticalResolution;  		//	hight;
 	UINTN	ByteScanLine;	
    UINTN	MaxPixelClock;
	UINTN 	FrameBufferSize;
	VOID	*FrameBuffer;
	VOID	*BankBuffer;
	VOID	*WindowScreen;
	VOID	*WindowBackground; 
	
	// Extra
	GUI_AREA Area;
	

}__attribute__ ((packed)) GUI;

///
typedef struct _GW_AREA {
	UINTN X;
	UINTN Y;
	UINTN Width;
	UINTN Height; 
}GW_AREA;

typedef struct _GW_FONT {

	GW_AREA Area;
	UINTN SizeX;
	UINTN SizeY;
	UINTN FontSizeX;
	UINTN FontSizeY;
	UINTN FgColor;
	UINTN BgColor;
	UINTN CursorX;
	UINTN CursorY;
	
	UINTN SetPositionCursorX;
	UINTN SetPositionCursorY;
	
	UINTN RSizeX;
	
	VOID *FontBuffer;
	

} GW_FONT;  

typedef struct _GW_HAND {

	CHAR8 *Title;
	VOID *Menu;
	UINTN X;
	UINTN Y;
	UINTN Width;
	UINTN Height; 
	UINTN Style;
	UINTN Flag; // Nelson o bit 1 Ã© para informar, se a janela jÃ¡ foi registrada
	VOID *Buffer;
	
	GW_AREA Area;
	GW_FONT Font;
	
	UINTN Type;
	UINTN Msg1;
	UINTN Msg2;
	UINTN RMsg1;
	UINTN RMsg2;

	
}__attribute__ ((packed)) GW_HAND;




VOID PutPixel(UINTN X, UINTN Y, UINTN Color);
VOID RefreshRate();

UINTN DrawRect (UINTN X1,
				UINTN Y1,
				UINTN X2,
                UINTN Y2, 
				UINTN Color,
				VOID *Buffer);
				
VOID DrawChar( 	UINTN X,
				UINTN Y,	
				UINTN C,
				UINTN FgColor,
				UINTN BgColor, 
				VOID *Buffer,
				VOID *FontBuffer );
VOID DrawCharTransparent(	UINTN X,
							UINTN Y,	
							UINTN C,
							UINTN FgColor, 
							VOID *Buffer,
							VOID *FontBuffer);
				
UINTN DrawArea (UINTN X1,
				UINTN Y1,
				UINTN X2,
                UINTN Y2, 
				UINTN Color,
				VOID *Buffer);
				
UINTN UpdateBoxDraw(GW_HAND *Hand);
UINTN InitializeBoxDraw(GW_HAND *Hand,
						UINTN X,	
						UINTN Y,
						UINTN FgColor,
						UINTN BgColor,
						VOID *FontBuffer);
UINTN BoxDraw(	GW_HAND *Hand,
				UINTN C,
				UINTN FgColor,
				UINTN BgColor, 
				VOID *Buffer);
				



GW_HAND *CreateWindow(	CONST CHAR8 *Title,
						VOID *Menu,
						UINTN X,
						UINTN Y,
						UINTN Width,
						UINTN Height, 
						UINTN Style,
						UINTN Flag);

GW_HAND *CreateObject(	GW_HAND *GwHand,
						UINTN Type,
						UINTN X,
						UINTN Y,
						UINTN Width,
						UINTN Height, 
						UINTN Style,
						UINTN Flag);

UINTN UpdateWindow(GW_HAND *GwHand);
UINTN UpdateObject(	GW_HAND *GwHand,GW_HAND *Hand);
						
UINTN Send(GW_HAND *Hand,UINTN Msg1, UINTN Msg2);
GW_HAND *Receive();
UINTN GwSetFocus(GW_HAND *Hand);
UINTN ObjectSetFocus(GW_HAND *Hand);































