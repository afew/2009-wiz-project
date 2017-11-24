// RndObj.cpp: implementation of the CRndObj class.
//
////////////////////////////////////////////////////////////////////////////////


#include "_StdAfx.h"


CRndObj::CRndObj()
{
	m_pDev	= NULL;
	m_pTex	= NULL;

	m_nFce	= 0;
	m_pIdx	= NULL;
	m_pVtx	= NULL;
}

CRndObj::~CRndObj()
{
	Destroy();
}

void CRndObj::Destroy()
{
	DGE_DestroyTexture(&m_pTex);
}


INT CRndObj::Create(void* p1, void* p2, void*, void*)
{
	INT		hr = 0;
	char*	sFile=NULL;

	if(!p1)
		return DGE_EFAIL;

	m_pDev	= (PDGE_DEVICE)p1;
	sFile	= (char*)p2;

	hr = DGE_CreateTexture(NULL, &m_pTex, sFile);

	if(DGE_FAILED(hr))
		return DGE_ECANNOTALLOCATED;


	return DGE_OK;
}

INT CRndObj::FrameMove()
{
	return DGE_OK;
}

void CRndObj::Render()
{
	m_pDev->SetTexture(0, m_pTex);
	m_pDev->SetTransform(DGE_TS_WORLD, &m_mtWld);
	m_pDev->SetFVF(DGE3D::VxfUV1::FVF);
	m_pDev->DrawIndexedPrimitiveUPf(DGE_PT_TRIANGLE_LIST, m_nFce* 3, m_pIdx, m_pVtx, sizeof(DGE3D::VxfUV1));

	m_pDev->SetTransformIdentity(DGE_TS_WORLD);
	m_pDev->SetTexture(0, 0);
}





void CRndObj::SetMatrix(const DGXMATRIX* v)
{
	m_mtWld = *v;
}


void CRndObj::SetIdx(const void* v, INT nFace)
{
	m_nFce = nFace;
	m_pIdx = (DGE3D::VtxIdxW*)v;
}

void CRndObj::SetVtx(const void* v)
{
	m_pVtx = (DGE3D::VxfUV1*)v;
}



