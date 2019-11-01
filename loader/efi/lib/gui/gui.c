/**
 *	Copyright (c) 2013 Sirius Corporation
 *	Nelson Sapalo da Siva Cole
 *	Lubango, 8 de Setembro de 2019 - Hora: 18h05
 *	File Name: gui.c
 **/


#include <efi.h>


//Globais
extern CHAR8 font_data_8x8[128*8];
extern UINT16 font12x16[128*16];

GUI *G = 0;

GW_HAND* GlobalGwFocus = 0;
GW_HAND* GlobalObjectFocus = 0;



VOID PutPixel(UINTN X, UINTN Y, UINTN Color)
{
	
	*(UINT32*)((UINT32*)G->FrameBuffer + (G->ByteScanLine* Y) + X) = Color;
	
}

VOID PutPixelBuff(UINTN X, UINTN Y, UINTN Color,VOID *Buffer)
{
	
	*(UINT32*)((UINT32*)Buffer + (G->ByteScanLine * Y) + X) = Color;
	
}

// PixelClock default
VOID RefreshRate() 
{
	CopyMem(G->FrameBuffer,G->BankBuffer,G->HorizontalResolution * G->VerticalResolution * (G->Bpp/8));
	
}

UINTN LineDrawHorizontal ( 	UINTN X1,
							UINTN X2,
                       		UINTN Y, 
							UINTN Color,
							VOID *Buffer) 
{

	UINTN i;
	for(i = 0; i < X2; i++) {

		PutPixelBuff(X1 + i,Y,Color,Buffer);

	}
	return (X2 - X1);
}


UINTN LineDrawVertical ( 	UINTN Y1,
							UINTN Y2,
                       		UINTN X, 
							UINTN Color,
							VOID *Buffer)
{

	UINTN i;
	for(i = 0; i < Y2; i++) {

		PutPixelBuff(X,Y1 + i,Color,Buffer);

	}

	return (Y2 - Y1);

}


UINTN DrawRect (UINTN X1,
				UINTN Y1,
				UINTN X2,
                UINTN Y2, 
				UINTN Color,
				VOID *Buffer)
{
	// Top
	LineDrawHorizontal ( X1, X2, Y1,Color,Buffer);
	
	// Left
	LineDrawVertical (Y1,Y2,X1,Color,Buffer);
	
	// bottom
	LineDrawHorizontal ( X1, X2, Y1 + Y2,Color,Buffer);
	
	// right
	LineDrawVertical (Y1,Y2 + 1,X1 + X2,Color,Buffer);

	return ((X2 - X1) * (Y2 - Y1));

}

UINTN DrawArea (UINTN X1,
				UINTN Y1,
				UINTN X2,
                UINTN Y2, 
				UINTN Color,
				VOID *Buffer)
{

	UINTN i;
	
	for(i = 0; i < Y2; i++) {
		
		LineDrawHorizontal ( X1, X2, Y1 + i,Color,Buffer);
	}
	return ((X2 - X1) * (Y2 - Y1));

}


VOID DrawChar( 	UINTN X,
				UINTN Y,	
				UINTN C,
				UINTN FgColor,
				UINTN BgColor, 
				VOID *Buffer,
				VOID *FontBuffer )
{
   
	UINT16 font = 0;
	CONST UINT16 *font_data = (CONST UINT16*) FontBuffer;
   	INTN cx, cy;
	UINT16 mask;
    
   for(cy=0;cy < 16;cy++){
		mask = 1;
        font = font_data[(C *16) + cy];
		
                for(cx = 12 -1 ;cx >= 0;cx--){
 
                		if(font &mask)
							PutPixelBuff(X + cx,Y + cy,FgColor,Buffer);
						
                        else 
							PutPixelBuff(X + cx,Y + cy,BgColor,Buffer);
						
						mask += mask;
          }
        
    }
        
    

}

VOID DrawCharTransparent(	UINTN X,
							UINTN Y,	
							UINTN C,
							UINTN FgColor, 
							VOID *Buffer,
							VOID *FontBuffer)
{
	UINT16 font = 0;
	CONST UINT16 *font_data = (CONST UINT16*) FontBuffer;
   	INTN cx, cy;
	UINT16 mask;
    
   for(cy=0;cy < 16;cy++){
		mask = 1;
        font = font_data[(C *16) + cy];
		
                for(cx = 12 -1 ;cx >= 0;cx--){ 
                       if(font &mask)
							PutPixelBuff(X + cx,Y + cy,FgColor,Buffer);
						mask += mask;
                  
          }
        
    }

}				
				

UINTN UpdateBoxDraw(GW_HAND *Hand)
{
	Hand->Font.Area.X 		= Hand->X + 8;
	Hand->Font.Area.Y 		= Hand->Y + 8;
	Hand->Font.Area.Width 	= Hand->Width  - 8;
	Hand->Font.Area.Height 	= Hand->Height - 8;
	
	Hand->Font.SizeX		= Hand->Font.Area.Width/Hand->Font.FontSizeX;
	Hand->Font.SizeY		= Hand->Font.Area.Height/Hand->Font.FontSizeY;
	
	Hand->Font.CursorX = Hand->Font.SetPositionCursorX;
	Hand->Font.CursorY = Hand->Font.SetPositionCursorY;
	
	Hand->Font.RSizeX = 0;
	
	return (0);
}

UINTN InitializeBoxDraw(GW_HAND *Hand,
						UINTN X,	
						UINTN Y,
						UINTN FgColor,
						UINTN BgColor,
						VOID *FontBuffer)
{
	
	
	Hand->Font.FontSizeX 	= X;
	Hand->Font.FontSizeY 	= Y;
	Hand->Font.FgColor 		= FgColor;
	Hand->Font.BgColor 		= BgColor;
	Hand->Font.FontBuffer 	= (VOID*)FontBuffer;
	
	Hand->Font.SetPositionCursorX 		= Hand->Font.SetPositionCursorY = Hand->Font.RSizeX = 0;
	
	return (0);
}


UINTN BoxDraw(	GW_HAND *Hand,
				UINTN C,
				UINTN FgColor,
				UINTN BgColor, 
				VOID *Buffer)
{
	
	
	if(Hand->Font.CursorY >= Hand->Font.SizeY){
		//scroll
		Hand->Font.CursorX = Hand->Font.CursorY = 0;
		Hand->Font.RSizeX = 0;
	}
	if( Hand->Font.CursorX >= Hand->Font.SizeX || C == '\n'){
		Hand->Font.CursorY++;
		Hand->Font.CursorX = 0;
		Hand->Font.RSizeX = 0;
	}
	if(C == '\t'){
			Hand->Font.CursorX += 8;
	}
	else if(C >=' '){
		if(C == 'i' || C == 'I' || C == 'l')
				Hand->Font.RSizeX +=4;
							
		
		DrawCharTransparent(Hand->Font.CursorX * (Hand->Font.FontSizeX-2) + Hand->Font.Area.X - Hand->Font.RSizeX,
							Hand->Font.CursorY * Hand->Font.FontSizeY + Hand->Font.Area.Y,
							C,
							FgColor,Buffer,Hand->Font.FontBuffer);
							
							Hand->Font.CursorX++;
							
	}
	
	
	return (C);
}





/*

	Windows

*/

//#define W_BARRA_TITUL_SIZE 24 // vertical pixel


/*        	Estrutura de nossa janela
 *
 *   1 - Barra de tÃ­tulo (tÃ­tulo, status, icone)
 *   2 - Borda
 *   3 - Coordenada X
 *   4 - Coordenada Y
 *   5 - Largura
 *   6 - Altura
 *   7 - Area
 *   8 - 0
 *   9 - Menu
 *  10 - Estilo (Scroll (Horizontal e Vertical))
 *  11 - Flag
 *
 *
 */
 
GW_HAND *CreateWindow(	CONST CHAR8 *Title,
						VOID *Menu,
						UINTN X,
						UINTN Y,
						UINTN Width,
						UINTN Height, 
						UINTN Style,
						UINTN Flag)
{
	
	GW_HAND *GwHand  = (GW_HAND*) Malloc(sizeof(GW_HAND));
	
	GwHand->Title 	= (CHAR8*) Title;		
	GwHand->Menu 	= (VOID*) Menu;
	GwHand->X 		= X; // coordenada X
	GwHand->Y 		= Y; // Coordenada Y
	GwHand->Width	= Width; // largura
	GwHand->Height	= Height; // altura
	GwHand->Style	= Style;
	GwHand->Flag	= Flag;
	GwHand->Buffer	= (VOID*) G->BankBuffer; // Nelson tem que alocar memoria

	// area
	GwHand->Area.X 		= X; // area coordenada X
	GwHand->Area.Y 		= Y + W_BARRA_TITUL_SIZE; // area Coordenada Y
	GwHand->Area.Width	= Width; // area largura
	GwHand->Area.Height	= Height - W_BARRA_TITUL_SIZE; // area altura
	
	
	//Font
	InitializeBoxDraw(GwHand,12,16,-1,0,font12x16);


	// Registrar janela
	//
	//
	//
	

	// Area de janela
	DrawRect (GwHand->X,GwHand->Y,GwHand->Width,GwHand->Height,0xffccccff,GwHand->Buffer);
	// barra de title
	DrawArea (GwHand->X + 1,GwHand->Y + 1,GwHand->Area.Width -1,W_BARRA_TITUL_SIZE -1, \
				0,GwHand->Buffer);
	// area
	DrawArea (GwHand->Area.X + 1,GwHand->Area.Y + 1,GwHand->Area.Width -1,GwHand->Area.Height -1, \
				0xff,GwHand->Buffer);


	// Barra de titule
	LineDrawHorizontal ( GwHand->X,GwHand->Width,GwHand->Y + W_BARRA_TITUL_SIZE,0xffccccff,GwHand->Buffer);

	
	// Title
	CHAR8 *Tmp = (CHAR8*) Title;
	GwHand->Font.SetPositionCursorX = 30;
	UpdateBoxDraw(GwHand);
	
	while(*Tmp)
		BoxDraw(GwHand,*Tmp++,0xffffff,0xff,GwHand->Buffer);
	
	
	// Status
	/*
	BoxDrawSectCursorPosition(0,0);
	BoxDrawSectLen(10,10);
	BoxDrawSectPosition(X + GwHand->Width - 8*4 ,Y + 8);
	BoxDraw('-', 0xffccccff, 0, GwHand->Buffer);
	BoxDraw(' ', 0xffccccff, 0, GwHand->Buffer);
	BoxDraw('X', 0xffccccff, 0, GwHand->Buffer);*/
	
	
	
	// border
	//wBorder(1,1,1,1,0x09f911,(gHAND)wH);


	return (GW_HAND*) GwHand;	

}


GW_HAND *CreateObject(	GW_HAND *GwHand,
						UINTN Type,
						UINTN X,
						UINTN Y,
						UINTN Width,
						UINTN Height, 
						UINTN Style,
						UINTN Flag)
{
	GW_HAND *Hand = (GW_HAND*) Malloc(sizeof(GW_HAND));

	
	Hand->Area.X 		= X;
	Hand->Area.Y		= Y;
	Hand->Area.Width	= Width;
	Hand->Area.Height	= Height;
	
	Hand->X 		= GwHand->Area.X + X; // coordenada X
	Hand->Y 		= GwHand->Area.Y + Y; // Coordenada Y
	Hand->Width		= Width; // largura
	Hand->Height	= Height; // altura
	Hand->Style		= Style;
	Hand->Flag		= Flag;// &GW_FLANG_READY;//Flag;
	
	Hand->Type 		= Type;
	Hand->Msg1		= 0;
	Hand->Msg2		= 0;
	
	//Font
	InitializeBoxDraw(Hand,12,16,-1,0,font12x16);
	
	
	switch(Hand->Type){
		
		case GW_HANDLE_LABEL:			
				// Area
				DrawRect (Hand->X,Hand->Y,Hand->Width,Hand->Height,0xff,GwHand->Buffer);
				DrawArea (Hand->X + 1,Hand->Y + 1,Hand->Width -1,Hand->Height -1, \
				0xff,GwHand->Buffer);
				
			break;
			
		case GW_HANDLE_LIST:
				// Area
				DrawRect (Hand->X,Hand->Y,Hand->Width,Hand->Height,0xffccccff,GwHand->Buffer);
				
				DrawArea (Hand->X + 1,Hand->Y + 1,Hand->Width -1,Hand->Height -1, \
				0,GwHand->Buffer);
				
				
				Hand->Buffer = (VOID*) Malloc(1024);
				SetMem(Hand->Buffer,1024,0);

			break;
			
		default:
			
			break;
		
	}
	
	
	return (GW_HAND*) Hand;
	
}

UINTN UpdateWindow(GW_HAND *GwHand)
{
	
	GwHand->Area.X 		= GwHand->X; // area coordenada X
	GwHand->Area.Y 		= GwHand->Y + W_BARRA_TITUL_SIZE; // area Coordenada Y
	GwHand->Area.Width	= GwHand->Width; // area largura
	GwHand->Area.Height	= GwHand->Height - W_BARRA_TITUL_SIZE; // area altura
	

	if(!(GwHand->Flag &GW_FLAG_VISIBLE)) return 1;
	// Area de janela
	DrawRect (GwHand->X,GwHand->Y,GwHand->Width,GwHand->Height,0xccccff,GwHand->Buffer);
	// barra de title
	DrawArea (GwHand->X + 1,GwHand->Y + 1,GwHand->Area.Width -1,W_BARRA_TITUL_SIZE -1, \
				0,GwHand->Buffer);
	// area
	DrawArea (GwHand->Area.X + 1,GwHand->Area.Y + 1,GwHand->Area.Width -1,GwHand->Area.Height -1, \
				0xff,GwHand->Buffer);

	// Barra de titule
	LineDrawHorizontal ( GwHand->X,GwHand->Width,GwHand->Y + W_BARRA_TITUL_SIZE,0xccccff,GwHand->Buffer);

	
	// Title
	CHAR8 *Tmp = (CHAR8*) GwHand->Title;
	
	GwHand->Font.SetPositionCursorX = 30;
	UpdateBoxDraw(GwHand);
	while(*Tmp)
		BoxDraw(GwHand,*Tmp++,0xffffff,0xff,GwHand->Buffer);
	
	// Status
	/*
	BoxDrawSectCursorPosition(0,0);
	BoxDrawSectLen(10,10);
	BoxDrawSectPosition(GwHand->X + GwHand->Width - 8*4 ,GwHand->Y + 8);
	BoxDraw('-', 0xffccccff, 0, GwHand->Buffer);
	BoxDraw(' ', 0xffccccff, 0, GwHand->Buffer);
	BoxDraw('X', 0xffccccff, 0, GwHand->Buffer);*/
	
	
	
	// border
	//wBorder(1,1,1,1,0x09f911,(gHAND)wH);
	
	
	
	return 0;
}

UINTN UpdateObject(	GW_HAND *GwHand,GW_HAND *Hand)
{
	
	
	
	Hand->X 		= GwHand->Area.X + Hand->Area.X; // coordenada X
	Hand->Y 		= GwHand->Area.Y + Hand->Area.Y; // Coordenada Y
	
	if(!(Hand->Flag&GW_FLAG_VISIBLE)) return 1;
	
	switch(Hand->Type){
		
		case GW_HANDLE_LABEL:			
				// Area
				DrawRect (Hand->X,Hand->Y,Hand->Width,Hand->Height,0xff,GwHand->Buffer);
				DrawArea (Hand->X + 1,Hand->Y + 1,Hand->Width -1,Hand->Height -1, \
				0xff,GwHand->Buffer);
				
				// Data
				if((Hand->Flag &GW_FLAG_READY)) {
				
					CHAR8 *Tmp = (CHAR8*) Hand->Buffer;
					UpdateBoxDraw(Hand);
					while(*Tmp)
						BoxDraw(Hand,*Tmp++,0xffffff,0xff,GwHand->Buffer);
				}
				
			break;
			
		case GW_HANDLE_LIST:
				// Area
				DrawRect (Hand->X,Hand->Y,Hand->Width,Hand->Height,0xffccccff,GwHand->Buffer);
				
				DrawArea (Hand->X + 1,Hand->Y + 1,Hand->Width -1,Hand->Height -1,0,GwHand->Buffer);
				
				// Data
				if((Hand->Flag &GW_FLAG_READY)) {
					// New item
				
					CHAR8 *Tmp = (CHAR8*) Hand->Buffer;
					
					UpdateBoxDraw(Hand);
					while(*Tmp)
						BoxDraw(Hand,*Tmp++,0xffffff,0xff,GwHand->Buffer);
					
	
					// Select item
					if(GlobalObjectFocus == Hand) {
						if((Hand->Msg2 * 16) < (Hand->Area.Height - 16) )
						DrawRect (Hand->X + 8,Hand->Y + 8 + (Hand->Msg2 *16),Hand->Width - 20 ,16,0x808080,GwHand->Buffer);
					}
				
				}
			break;
			
		default:
			
			break;
		
	}
	return 0;
}



 static UINTN GwStrLength(CHAR8 *Source)
{
	CHAR8 *src = (CHAR8*)Source;
	UINTN i = 0;
	
	while(src[i] != 0)++i;
	
	return (UINTN)i;
}

UINTN Send(GW_HAND *Hand,UINTN Msg1, UINTN Msg2)
{
	
	
	CHAR8 *src;
	UINTN data1;
	UINTN data2;
	
	
	if((Msg2&GW_SMG_FLAG_BIT)) {
		switch(Msg1){
					
			case GW_FLAG_INVISIBLE:
				Hand->Flag &= ~GW_FLAG_VISIBLE;
				break;
			case GW_FLAG_VISIBLE:
				Hand->Flag |= GW_FLAG_VISIBLE;
				break;
		}
		return 0;
	}
	
	switch(Hand->Type){
		
		case GW_HANDLE_LABEL:
		
				Hand->Msg1 = Msg1;
				Hand->Msg2 = Msg2 &0x7fffffff;
		
				Hand->Buffer = (VOID*) Msg1;
				Hand->Flag |= GW_FLAG_READY;
			
			break;
		case GW_HANDLE_LIST:
		
			if(!Msg1) {
				Hand->Msg2 = Msg2 &0x7fffffff;
				return 0;
			}
			
			Hand->Msg1 = Msg1;
			
			src = (CHAR8*) Msg1;
			
			data1 = GwStrLength(Hand->Buffer);
			
			data2 = GwStrLength(src);
		
			CopyMem(Hand->Buffer + data1,src,data2);
			
			*(CHAR8*)(Hand->Buffer + data1 + data2) = '\n';
			
			Hand->Flag  |= GW_FLAG_READY;
			
			break;
		default:
		
			break;
	}
	
	return 0;
}

GW_HAND *Receive()
{
		//if(!(GlobalObjectFocus->Flag)) return 0;
		
		switch(GlobalObjectFocus->Type){
		
			case GW_HANDLE_LABEL:
				break;
				
			case GW_HANDLE_LIST:
					GlobalObjectFocus->RMsg1 = 1;
					GlobalObjectFocus->RMsg2 = GlobalObjectFocus->Msg2;
				break;
		default:
		
			break;
	}
			
		
		return (GW_HAND *)GlobalObjectFocus;

}


UINTN GwSetFocus(GW_HAND *Hand)
{
	
	GlobalGwFocus = Hand;
	
	return 0;
	
}

UINTN ObjectSetFocus(GW_HAND *Hand)
{
	
	GlobalObjectFocus = Hand;
	
	return 0;
	
}



















