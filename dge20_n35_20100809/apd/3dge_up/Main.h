// Interface for the CMain class.
//
////////////////////////////////////////////////////////////////////////////////


#if defined(_WIN32) || defined(WIN32)
	#if _MSC_VER > 1000
		#pragma once
	#endif
#endif


#ifndef _CMain_H_
#define _CMain_H_


struct RndObject
{
	DGXMATRIX	mtWld;		// Object world Matrix
	
	void*		pIdx;		// Common Index Data
	void*		pVtx;		// Vertex Data
};

class CMain : public CAppDge
{
protected:
	PDGX_INPUT		m_pInput;		// Input
	PDGX_CAMERA		m_pCam;			// Camera Instance

	PDGX_ENTITY		m_pXYZ;			// X, Y, Z Axis Line
	PDGX_ENTITY		m_pGrid;		// Grid for Test


	DGE3D::VtxIdxW	m_pIdx[12];		// Common Index Data


	RndObject		m_pObj1;
	RndObject		m_pObj2;
	
public:
	CMain();
	
	virtual INT	Init();
	virtual INT	Destroy();
	virtual INT	FrameMove();
	virtual INT	Render();
};

extern	CMain*	g_pApp;
#define	GMAIN	g_pApp

#endif


