// Implementation of the CDGX_GeoAxis class.
//
////////////////////////////////////////////////////////////////////////////////


#if defined(_WIN32) || defined(WIN32)
	#if _MSC_VER >= 1200
	#pragma warning(disable: 4996)
	#endif

	#include <windows.h>

#endif


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <gles/gl.h>
#include <gles/egl.h>

#include <DGE_Math.h>
#include <DGE_Base.h>

#include "DGX_Entity.h"
#include "DGX_GeoAxis.h"



CDGX_GeoAxis::CDGX_GeoAxis()
{
	m_pDev	= NULL;
}

CDGX_GeoAxis::~CDGX_GeoAxis()
{
	Destroy();
}


INT CDGX_GeoAxis::Create(void* p1, void*, void*, void*)
{
	FLOAT	fMax = 5000;

	m_pDev	= (PDGE_DEVICE)p1;
	
	m_pLine[ 0] = CDGX_GeoAxis::Vtx(-fMax,     0,     0, 0xFF990000);
	m_pLine[ 1] = CDGX_GeoAxis::Vtx(    0,     0,     0, 0xFF990000);
	m_pLine[ 2] = CDGX_GeoAxis::Vtx(    0,     0,     0, 0xFFFF0000);
	m_pLine[ 3] = CDGX_GeoAxis::Vtx( fMax,     0,     0, 0xFFFF0000);
	
	m_pLine[ 4] = CDGX_GeoAxis::Vtx(    0, -fMax,     0, 0xFF009900);
	m_pLine[ 5] = CDGX_GeoAxis::Vtx(    0,     0,     0, 0xFF009900);
	m_pLine[ 6] = CDGX_GeoAxis::Vtx(    0,     0,     0, 0xFF00FF00);
	m_pLine[ 7] = CDGX_GeoAxis::Vtx(    0,  fMax,     0, 0xFF00FF00);
	
	m_pLine[ 8] = CDGX_GeoAxis::Vtx(    0,     0, -fMax, 0xFF000099);
	m_pLine[ 9] = CDGX_GeoAxis::Vtx(    0,     0,     0, 0xFF000099);
	m_pLine[10] = CDGX_GeoAxis::Vtx(    0,     0,     0, 0xFF0000FF);
	m_pLine[11] = CDGX_GeoAxis::Vtx(    0,     0,  fMax, 0xFF0000FF);

	return 0;
}


void CDGX_GeoAxis::Render()
{
	m_pDev->SetFVF(CDGX_GeoAxis::Vtx::FVF);
	m_pDev->DrawPrimitiveUPf(GL_LINES, 0, 12, m_pLine, sizeof(CDGX_GeoAxis::Vtx) );
}

