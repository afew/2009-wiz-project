// Implementation of the CDGX_Ast class.
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

#include <DGE_Type.h>
#include <DGE_Util.h>
#include <DGE_System.h>
#include <DGE_Math.h>
#include <DGE_Base.h>

#include "DGX_Mdl.h"

#include "_dge_ase/DGX_Ast.h"
#include "_dge_ase/DGX_AstIns.h"

#include "_dge_ase/DGX_Asb.h"
#include "_dge_ase/DGX_AsbIns.h"



INT DGX_CreateMdl(char* sCmd
				 , PDGX_MDL* pData		// Output data
				 , void* pDev			// Device
				 , void* sName			// Model File Name
				 , void* pOrg			// Original DGX_Mdl Pointer for Clone Creating
				 , void* p4				// Not Use
				 )
{
	PDGX_MDL pObj = NULL;

	*pData	= NULL;

	if(NULL==sCmd)
		return DGE_EFAIL;


	if(0==DgeStr_Stricmp(sCmd, "Ase Txt"))
	{
		if(sName && !pOrg)
		{
			pObj = new CDGX_Ast;
			if(DGE_FAILED(pObj->Create(pDev, sName)))
			{
				delete pObj;
				return DGE_ECANNOTALLOCATED;
			}
		}
		else
		{
			pObj = new CDGX_AstIns;
			if(DGE_FAILED(pObj->Create(pOrg, NULL)))
			{
				delete pObj;
				return DGE_ECANNOTALLOCATED;
			}
		}
	}
	
	else if(0==DgeStr_Stricmp(sCmd, "Ase Bin"))
	{
		if(sName && !pOrg)
		{
			pObj= new CDGX_Asb;
			if(DGE_FAILED(pObj->Create(pDev, sName)))
			{
				delete pObj;
				return DGE_ECANNOTALLOCATED;
			}
		}
		else
		{
			pObj= new CDGX_AsbIns;
			if(DGE_FAILED(pObj->Create(pOrg, NULL)))
			{
				delete pObj;
				return DGE_ECANNOTALLOCATED;
			}
		}
	}


	*pData = pObj;
	return DGE_OK;
}



