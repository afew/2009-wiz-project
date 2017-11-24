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


class CMain : public CAppDge
{
protected:
	PDGX_INPUT		m_pInput;		// Input
	PDGX_CAMERA		m_pCam;			// Camera Instance

	PDGX_ENTITY		m_pXYZ	;		// X, Y, Z Axis Line
	PDGX_ENTITY		m_pGrid	;		// Grid Instance

	PDGX_MDL		m_pMdlOrg1	;		// Original 1
	PDGX_MDL		m_pMdlIns1	;		// Instance 1

	PDGX_MDL		m_pMdlOrg2	;		// Original 2
	PDGX_MDL		m_pMdlIns2	;		// Instance 3



	
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


