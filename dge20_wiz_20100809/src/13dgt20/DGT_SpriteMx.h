//	Copyright(C) Gamepark Holdings. All rights reserved.
//	Dogma-G Game Studios In-House Library DGE
//
//	for 2D Sprite Mixer.
//
////////////////////////////////////////////////////////////////////////////////


#if defined(_WIN32) || defined(WIN32)
	#if _MSC_VER > 1000
	#pragma once
	#endif
#endif


#ifndef _DGT_SpriteMx_H_
#define _DGT_SpriteMx_H_

#include <DGE_Type.h>


// Sprite Mixer
////////////////////////////////////////////////////////////////////////////////

interface IDGT_SpriteMx
{
	DGE_CLASS_DESTROYER(	IDGT_SpriteMx	);

	virtual INT		Begin(DWORD dMode=0)=0;						// Save Transform Matrix before 2D Sprite execution
	virtual INT		End()=0;									// Restore Saved 3D Envirionment Options


	// Assemble and Construction Layer
	virtual INT		Add(										// Unconditionally add new layer which is created with texture and an image area. But if latest texture is same to new texture, then add image area to latest layer.
								PDGE_TEXTURE		pTexture	// DGE_Texture Pointer
							,	const DGE_RECT*		pImgRc		// Image rect
							,	const DGE_FLOAT2*	 vcTrn		// Position
							,	const DGE_COLORF*	Color=NULL	// color
					)=0;

	virtual INT		AddEx(
								PDGE_TEXTURE		pTexture	// DGE_Texture Pointer
							,	const DGE_RECT*		pImgRc		// Image rect
							,	const DGE_FLOAT2*	vcScl		// Scaling
							,	const DGE_FLOAT2*	vcRot		// Rotation Center
							,	FLOAT				fRot		// Angle(Radian)
							,	const DGE_FLOAT2*	vcTrn		// Position
							,	const DGE_COLORF*	Color=NULL	// color
						) = 0;



	virtual INT		AddtoExist(									// If there exists texture same new texture, then add image area to exist layer.
								PDGE_TEXTURE		pTexture	// DGE_Texture Pointer
							,	const DGE_RECT*		pImgRc		// Image rect
							,	const DGE_FLOAT2*	 vcTrn		// Position
							,	const DGE_COLORF*	Color=NULL	// color
							)=0;

	virtual INT		AddtoExistEx(
								PDGE_TEXTURE		pTexture	// DGE_Texture Pointer
							,	const DGE_RECT*		pImgRc		// Image rect
							,	const DGE_FLOAT2*	vcScl		// Scaling
							,	const DGE_FLOAT2*	vcRot		// Rotation Center
							,	FLOAT				fRot		// Angle(Radian)
							,	const DGE_FLOAT2*	vcTrn		// Position
							,	const DGE_COLORF*	Color=NULL	// color
							) = 0;


	// Draw 2D..
	virtual INT		DrawLayer(INT nFirstL=0, INT nLastL=-1)=0;	// if nFirstL=0 and nLastL=-1 then Draw All Layers
	virtual INT		DrawLayer(PDGE_TEXTURE pTexture)=0;			// pTexture와 일치하는 모든 레이어를 그린다.

	virtual	INT		Clear()=0;
};

typedef	IDGT_SpriteMx*	PDGT_SPRITEMX;


// Create Sprite
INT DGT_CreateSpriteMx(char* sCmd
					   , PDGT_SPRITEMX* pData
					   , DGE_HANDLE p1			// IDGE_Device*
					   , DGE_HANDLE p2 = NULL	// No Use
					   , DGE_HANDLE p3 = NULL	// No Use
					   , DGE_HANDLE p4 = NULL	// No Use
					 );

// Destroy Sprite
INT DGT_DestroySpriteMx(PDGT_SPRITEMX* pData);


#endif



