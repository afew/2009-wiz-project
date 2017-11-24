// Interface for the DGX_Mdl class.
//
////////////////////////////////////////////////////////////////////////////////


#if defined(_WIN32) || defined(WIN32)
	#if _MSC_VER > 1000
	#pragma once
	#endif
#endif


#ifndef _DGX_Mdl_H_
#define _DGX_Mdl_H_


#include <DGE_Type.h>


interface IDGX_Mdl
{
	DGE_CLASS_DESTROYER(	IDGX_Mdl	);

	virtual INT		Create(void* =NULL, void* =NULL, void* =NULL, void* =NULL)=0;
	virtual void	Destroy()=0;

	virtual	INT		FrameMove()=0;
	virtual void	Render()=0;

	virtual INT		SetAttrib(DWORD dCmd, void* pData)=0;
	virtual INT		GetAttrib(DWORD dCmd, void* pData)=0;
};


enum EDGX_MDL
{
	DGXM_TEXNAME	=	128,
	DGXM_HEADEAR	=	64,

	// Command and Attribute Setup
	DGXM_ADVANCE_TIME		= 0x001001,
	DGXM_CURRENT_TIME		= 0x001002,

	DGXM_WORLD_MATRIX		= 0x001003,		// World Matrix
	DGXM_WORLD_MATRIX_PT	= 0x001004,		// World Matrix Address

	DGXM_GEOMETRY_MATRIX	= 0x001005,		// Updated Geometry Matrix
	DGXM_GEOMETRY_MATRIX_PT	= 0x001006,		// Updated Geometry Matrix Address

	DGXM_LOOP_SECTION		= 0x001011,		// Animation Loop Section
	DGXM_FRAME_INDEX		= 0x001012,
	DGXM_FRAME_INDEX_ABSOLUTE=0x001013,

	// Command Execution
	DGXM_EXEC_TEXTURE_LOAD	= 0x100001,		// Texture Loading Command. Need Color Key for pData
};


typedef	IDGX_Mdl*	PDGX_MDL;


INT DGX_CreateMdl(char* sCmd			// Create MDL
				 , PDGX_MDL* pData		// Output data
				 , void* pDev			// Device
				 , void* sName	= NULL	// Model File Name
				 , void* pOrg	= NULL	// Original DGX_Mdl Pointer for Clone Creating
				 , void* p4		= NULL	// Not Use
				 );


INT DGX_DestroyMdl(PDGX_MDL* pData);	// Destroy MDL


#endif



