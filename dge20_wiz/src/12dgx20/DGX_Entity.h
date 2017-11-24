// Interface for the 3D utilities classes.
//
////////////////////////////////////////////////////////////////////////////////


#if defined(_WIN32) || defined(WIN32)
	#if _MSC_VER > 1000
	#pragma once
	#endif
#endif


#ifndef _IDGX_Entity_H_
#define _IDGX_Entity_H_

#include <DGE_Type.h>


interface IDGX_Entity
{
	DGE_CLASS_DESTROYER(	IDGX_Entity	);

	virtual INT		Create(void* =0, void* =0, void* =0, void* =0)=0;
	virtual void	Destroy()=0;
	virtual INT		FrameMove()=0;
	virtual void	Render()=0;

	virtual INT		Query(char* sCmd, void* pData)=0;
};


typedef	IDGX_Entity*	PDGX_ENTITY;


// Create Entity Instance
INT DGX_CreateEntity(char* sCmd
				   , PDGX_ENTITY* pData
				   , DGE_HANDLE p1			// PDGE_DEVICE
				   , DGE_HANDLE p2 = NULL	// User Data(Option)
				   , DGE_HANDLE p3 = NULL	// No Use
				   , DGE_HANDLE p4 = NULL	// No Use
					 );



// Destroy Entity Instance
INT DGX_DestroyEntity(PDGX_ENTITY* pData);


#endif



