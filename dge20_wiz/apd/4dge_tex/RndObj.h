// RndObj.h: interface for the CRndObj class.
//
////////////////////////////////////////////////////////////////////////////////


#if defined(_WIN32) || defined(WIN32)
	#if _MSC_VER > 1000
		#pragma once
	#endif
#endif


#ifndef _RndObj_H_
#define _RndObj_H_


class CRndObj
{
protected:
	PDGE_DEVICE			m_pDev;			// Rendering Device


	DGXMATRIX			m_mtWld;		// Object world Matrix

	PDGE_TEXTURE		m_pTex;			// Texture

	INT					m_nFce;			// Face Number
	DGE3D::VtxIdxW*		m_pIdx;			// Common Index Data
	DGE3D::VxfUV1*		m_pVtx;			// Vertex Data

public:
	CRndObj();
	virtual ~CRndObj();

	INT		Create(void* =NULL, void* =NULL, void* =NULL, void* =NULL);
	void	Destroy();

	INT		FrameMove();
	void	Render();

	void	SetMatrix(const DGXMATRIX* v);
	void	SetIdx(const void* v, INT nFace);
	void	SetVtx(const void* v);
};

#endif



