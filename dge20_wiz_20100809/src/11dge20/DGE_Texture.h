//	Copyright(C) Gamepark Holdings. All rights reserved.
//	Dogma-G Game Studios In-House Library DGE
//
//	for Texture.
//
////////////////////////////////////////////////////////////////////////////////


#if defined(_WIN32) || defined(WIN32)
	#if _MSC_VER > 1000
	#pragma once
	#endif
#endif


#ifndef _DGE_Texture_H_
#define _DGE_Texture_H_

#include <DGE_Type.h>


class CDGE_Texture : public IDGE_Texture
{
protected:
	UINT	m_nTex	;				// Id
	UINT	m_Format;				// Pixel Format
	UINT	m_Type	;				// Pixel Type


	UINT	m_ImgW	;				// Image Width
	UINT	m_ImgH	;				// Image Height
	UINT	m_ImgD	;				// Image Depth
	DWORD	m_ImgC	;				// Image ColorKey

	void*	m_pOwn	;				// Owner

	char	m_sName[DGE_MAX_PATH];	// File Name for Search

public:
	CDGE_Texture ();
	virtual ~CDGE_Texture();

	virtual const char* const GetName()const{	return m_sName;	}
	virtual UINT	GetId()			{	return m_nTex;	}
	virtual	UINT	GetFormat()		{	return m_Format;}
	virtual UINT	GetType()		{	return m_Type;	}

	virtual UINT	GetImgW()		{	return m_ImgW;	}
	virtual UINT	GetImgH()		{	return m_ImgH;	}
	virtual UINT	GetImgD()		{	return m_ImgD;	}
	virtual DWORD	GetImgC()		{	return m_ImgC;	}

	virtual	void	SetOwner(void* p){	m_pOwn = p;		}
	virtual	void*	GetOwner()		{	return m_pOwn;	}

	virtual	INT		BindTexture(INT modulate, INT smp_addrS, INT smp_addrT, INT filter_S, INT filter_T);	// Binding Texture: nState is not supported. If moduate =0  then Release Binding
	virtual	INT		CopyTexImage2D();

public:
	INT			Create(DGE_HANDLE =0, DGE_HANDLE =0, DGE_HANDLE =0, DGE_HANDLE =0);

protected:
	void		Destroy();
};


#endif



