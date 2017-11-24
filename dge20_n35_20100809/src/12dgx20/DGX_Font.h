//	Copyright(C) Gamepark Holdings. All rights reserved.
//	Dogma-G Game Studios In-House Library DGE
//
//	for 3D Rendering Pipe Line.
//
////////////////////////////////////////////////////////////////////////////////


#if defined(_WIN32) || defined(WIN32)
	#if _MSC_VER > 1000
	#pragma once
	#endif
#endif


#ifndef _DGX_Font_H_
#define _DGX_Font_H_

#include <DGE_Type.h>



struct TDGX_FONT
{
	INT		iHeight	;						// Height
	char*	sName	;						// Font File Name

	TDGX_FONT(char*	_s,	INT _h=12) : iHeight(_h), sName(_s){}
};

interface IDGX_Font
{
	DGE_CLASS_DESTROYER(	IDGX_Font	);

	virtual INT		SetString(const char* sMsg)=0;
	virtual	INT		SetColor(const DGE_COLORF*)=0;
	virtual INT		SetPos(const DGE_FLOAT2*)=0;
	virtual INT		DrawTxt()=0;
};

typedef	IDGX_Font*	PDGX_FONT;



INT DGX_TFFontOpen();		// FreeTypeFont Library Open
INT	DGX_TFFontClose();		// FreeTypeFont Liberay Close




// Create Font
INT DGX_CreateFont(char* sCmd
				   , PDGX_FONT* pData
				   , DGE_HANDLE p1			// TDGX_Font*
				   , DGE_HANDLE p2			// PDGE_SPRITE
				   , DGE_HANDLE p3 = NULL	// No Use
				   , DGE_HANDLE p4 = NULL	// No Use
					 );

// Destroy Font
INT DGX_DestroyFont(PDGX_FONT* pData);


#endif




