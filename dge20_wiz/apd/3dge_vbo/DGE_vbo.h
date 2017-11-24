// Interface for DGX Vertex Buffer Object.
//
////////////////////////////////////////////////////////////////////////////////


#if defined(_WIN32) || defined(WIN32)
	#if _MSC_VER > 1000
		#pragma once
	#endif
#endif


#ifndef _IDGE_VB_H_
#define	_IDGE_VB_H_

#include <DGE_Type.h>


interface IDGE_VB
{
	DGE_CLASS_DESTROYER(	IDGE_VB	);

	virtual INT		Fill(DGE_HANDLE pBuf, INT nBufSize, BOOL bReCreateVB=FALSE)=0;	// Fill Buffer
	virtual INT		Bind(BOOL bBind=FALSE)=0;										// Bind Buffer

	virtual	void	SetOwner(DGE_HANDLE)=0;	// Setting Owner. if Owner Exist. Texture instance cannot be destroyed.
	virtual	void*	GetOwner()=0;
};


typedef	IDGE_VB*	PDGE_VB;


// Create Vertex Buffer Instance
INT DGE_CreateVB(char* sCmd
				   , PDGE_VB* pData
				   , DGE_HANDLE p1			// PDGE_DEVICE
				   , DGE_HANDLE p2			// Input FVF
				   , DGE_HANDLE p3 = NULL	// Input Buffer pointer
				   , DGE_HANDLE p4 = NULL	// Input Buffer Size(Byte)
					 );

// Destroy VB Instance
INT DGE_DestroyVB(PDGE_VB* pData);




#endif




