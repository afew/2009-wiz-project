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



struct VtxUV1 : public DGE3D::VxfUV1
{
	VtxUV1()
	{
		p.x = 0; p.y = 0; p.z = 0;
		t.x = 0; t.y = 0;
	}

	VtxUV1(FLOAT X,FLOAT Y,FLOAT Z,FLOAT U,FLOAT V)
	{
		p.x = X; p.y = Y; p.z = Z;
		t.x = U; t.y = V;
	}
};

class CMain : public CAppDge
{
protected:
	PDGX_INPUT		m_pInput;		// Input
	PDGX_CAMERA		m_pCam;			// Camera Instance

	PDGX_ENTITY		m_pXYZ;			// X, Y, Z Axis Line
	PDGX_ENTITY		m_pGrid;		// Grid for Test

	PDGE_TEXTURE	m_pTex0;		// Texture 0
	PDGE_TEXTURE	m_pTex1;		// Texture 1

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


