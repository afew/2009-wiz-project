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



struct VtxNUV1 : public DGE3D::VxfNUV1
{
	VtxNUV1()
	{
		p.x = 0; p.y = 0; p.z = 0;
		n.x = 0; n.y = 0; n.z = 0;
		t.x = 0; t.y = 0;
	}

	VtxNUV1(FLOAT X,FLOAT Y,FLOAT Z
			, FLOAT NX,FLOAT NY,FLOAT NZ
			, FLOAT U,FLOAT V)
	{
		p.x = X; p.y = Y; p.z = Z;
		n.x =NX; n.y =NY; n.z = NZ;
		t.x = U; t.y = V;
	}
};

class CMain : public CAppDge
{
protected:
	PDGX_INPUT		m_pInput;	// Input
	PDGX_CAMERA		m_pCam;		// Camera Instance

	PDGX_ENTITY		m_pXYZ;		// X, Y, Z Axis Line
	PDGX_ENTITY		m_pGrid;	// Grid for Test
	
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


