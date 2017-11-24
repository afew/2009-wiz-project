//	Copyright(C) Gamepark Holdings. All rights reserved.
//	Dogma-G Game Studios In-House Library DGE
//
//	for 2D Sprite.
//
////////////////////////////////////////////////////////////////////////////////


#if defined(_WIN32) || defined(WIN32)
	#if _MSC_VER > 1000
	#pragma once
	#endif
#endif


#ifndef _DGE_Sprite_H_
#define _DGE_Sprite_H_

#include <DGE_Type.h>


class CDGE_Sprite : public IDGE_Sprite
{
protected:
	IDGE_Device*		m_pDev;

	static DGXVECTOR2	m_VtxPos[4];	// Position
	static DGXVECTOR2	m_VtxTex[4];	// Texture Coordinate

	FLOAT				m_fScnW;
	FLOAT				m_fScnH;

	FLOAT				m_mtPrj[20];
	FLOAT				m_mtViw[20];

public:
	CDGE_Sprite();
	virtual ~CDGE_Sprite();

	virtual INT		Begin(DWORD dMode=0);
	virtual INT		End();


	virtual INT		Draw( IDGE_Texture*		pTexture	// DGE_Texture Pointer
						, const DGE_RECT*	pImgRc		// Image rect
						, const DGE_FLOAT2* vcTrn		// Position
						, const DGE_COLORF*	Color=NULL	// color
						);
	

	virtual INT		DrawEx(IDGE_Texture*	pTexture	// DGE_Texture Pointer
						, const DGE_RECT*	pImgRc		// Image rect
						, const DGE_FLOAT2*	vcScl		// Scaling
						, const DGE_FLOAT2*	vcRot		// Rotation Center
						, FLOAT				fRot		// Angle(Radian)
						, const DGE_FLOAT2* vcTrn		// Position
						, const DGE_COLORF*	Color=NULL	// color
						);


	virtual INT		DrawFont( IDGE_Texture*		pTexture	// DGE_Texture Pointer
						, const DGE_RECT*	pImgRc		// Image rect
						, const DGE_FLOAT2* vcTrn		// Position
						, const DGE_COLORF*	Color=NULL	// color
						);
	

	virtual INT		DrawFontEx(IDGE_Texture*	pTexture	// DGE_Texture Pointer
						, const DGE_RECT*	pImgRc		// Image rect
						, const DGE_FLOAT2*	vcScl		// Scaling
						, const DGE_FLOAT2*	vcRot		// Rotation Center
						, FLOAT				fRot		// Angle(Radian)
						, const DGE_FLOAT2* vcTrn		// Position
						, const DGE_COLORF*	Color=NULL	// color
						);

	INT		Create(DGE_HANDLE =NULL, DGE_HANDLE =NULL, DGE_HANDLE =NULL, DGE_HANDLE =NULL);
	void	Destroy();
};


#endif




