// Implementation of the CDGX_GeoGrid class.
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
#include "DGX_GeoGrid.h"



CDGX_GeoGrid::CDGX_GeoGrid()
{
	m_pDev	= NULL;
}

CDGX_GeoGrid::~CDGX_GeoGrid()
{
	Destroy();
}


INT CDGX_GeoGrid::Create(void* p1, void*, void*, void*)
{
	INT		i;

	m_pDev	= (PDGE_DEVICE)p1;

	
	for(i=0; i<8; ++i)
	{
		m_pLine[8*i +0 ] = CDGX_GeoGrid::Vtx(-128.0F,  16.0F* (i+1), -2.0F, (i%2)? 0xFF999999 : 0xFF666666);
		m_pLine[8*i +1 ] = CDGX_GeoGrid::Vtx( 128.0F,  16.0F* (i+1), -2.0F, (i%2)? 0xFF999999 : 0xFF666666);
		m_pLine[8*i +2 ] = CDGX_GeoGrid::Vtx(-128.0F, -16.0F* (i+1), -2.0F, (i%2)? 0xFF999999 : 0xFF666666);
		m_pLine[8*i +3 ] = CDGX_GeoGrid::Vtx( 128.0F, -16.0F* (i+1), -2.0F, (i%2)? 0xFF999999 : 0xFF666666);

		m_pLine[8*i +4 ] = CDGX_GeoGrid::Vtx( 16.0F* (i+1),-128.0F, -2.0F, (i%2)? 0xFF999999 : 0xFF666666);
		m_pLine[8*i +5 ] = CDGX_GeoGrid::Vtx( 16.0F* (i+1), 128.0F, -2.0F, (i%2)? 0xFF999999 : 0xFF666666);
		m_pLine[8*i +6 ] = CDGX_GeoGrid::Vtx(-16.0F* (i+1),-128.0F, -2.0F, (i%2)? 0xFF999999 : 0xFF666666);
		m_pLine[8*i +7 ] = CDGX_GeoGrid::Vtx(-16.0F* (i+1), 128.0F, -2.0F, (i%2)? 0xFF999999 : 0xFF666666);
	}

	return 0;
}


void CDGX_GeoGrid::Render()
{
	m_pDev->SetFVF(CDGX_GeoGrid::Vtx::FVF);
	m_pDev->DrawPrimitiveUPf(GL_LINES, 0, 72, m_pLine, sizeof(CDGX_GeoGrid::Vtx) );
}


