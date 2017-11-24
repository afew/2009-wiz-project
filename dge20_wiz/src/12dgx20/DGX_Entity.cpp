// Implementation of the DGX_Entity class.
//
////////////////////////////////////////////////////////////////////////////////


#if defined(_WIN32) || defined(WIN32)
	#if _MSC_VER >= 1200
	#pragma warning(disable: 4996)
	#endif
#endif


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <DGE_Util.h>
#include <DGE_Math.h>
#include <DGE_Base.h>

#include "DGX_Entity.h"

#include "DGX_GeoGrid.h"
#include "DGX_GeoAxis.h"



// Create Entity Instance
INT DGX_CreateEntity(char* sCmd
				   , PDGX_ENTITY* pData
				   , DGE_HANDLE p1		// PDGE_DEVICE
				   , DGE_HANDLE p2		// User Data(Option)
				   , DGE_HANDLE p3		// No Use
				   , DGE_HANDLE p4		// No Use
					 )
{
	PDGX_ENTITY	pObj = NULL;

	(*pData) = NULL;

	if(0==DgeStr_Stricmp("Grid", sCmd))
		pObj = new CDGX_GeoGrid;

	else if(0==DgeStr_Stricmp("Axis", sCmd))
		pObj = new CDGX_GeoAxis;

	else
		return DGE_ECANNOTALLOCATED;


	if(DGE_FAILED(pObj->Create(p1, p2, p3, p4)))
	{
		delete pObj;
		return DGE_ECANNOTALLOCATED;
	}

	(*pData) = pObj;
	return DGE_OK;
}


INT DGX_DestroyEntity(PDGX_ENTITY* pData)
{
	if(NULL == *pData)
		return DGE_OK;

	delete *pData;
	(*pData) = NULL;

	return DGE_OK;
}


