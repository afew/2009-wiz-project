//	Copyright(C) Gamepark Holdings. All rights reserved.
//	Dogma-G Game Studios In-House Library DGE
//
// Interface for the IDGX_Camera class.
//
////////////////////////////////////////////////////////////////////////////////


#if defined(_WIN32) || defined(WIN32)
	#if _MSC_VER > 1000
	#pragma once
	#endif
#endif


#ifndef _DGX_Camera_H_
#define _DGX_Camera_H_

#include <DGE_Type.h>


enum EDGX_CAMERA
{
	DGX_CAM_NONE	=0,		//
	DGX_CAM_FIRST,			// 1st Person
	DGX_CAM_THIRD,			// 3rd Person
};


struct TDGX_CAMERA
{
	// for Projection Matrix
	FLOAT	fScnW;			// Screen Width
	FLOAT	fScnH;			// Screen Height
	FLOAT	fFov;			// Field of View
	FLOAT	fNear;			// Near value
	FLOAT	fFar;			// Far value

	// for View Matrix
	FLOAT	vEye[3];		// Camera Position X,Y,Z
	FLOAT	vLook[3];		// Camera Look At Position X,Y,Z
	FLOAT	vUp[3];			// Camera Up Vector X,Y,Z
};


// Single Camera
interface IDGX_Camera
{
	DGE_CLASS_DESTROYER(	IDGX_Camera	);

	virtual INT		Update()=0;				// Setup View and Projection Matrix of Camera
	virtual INT		FrameMove()=0;			// Update() + SetTransformViw() and SetTransformPrj()
	virtual INT		SetTransformViw()=0;	// Setup View Matrix of Device and 3d Pipeline.
	virtual INT		SetTransformPrj()=0;	// Setup Projection Matrix of Device and 3d Pipeline.

	virtual INT		Query(char* sCmd, void* pData)=0;
	virtual INT		GetType()=0;	



	// Set Parameter
	virtual void	SetupParamView(const DGE_FLOAT3* Eye, const DGE_FLOAT3* LookAt, const DGE_FLOAT3* Up)=0;
	virtual void	SetupParamProj(FLOAT fFov, FLOAT fScnW, FLOAT fScnH, FLOAT fNear, FLOAT fFar)=0;

	virtual void	SetupMatrixViw(const DGE_MATRIX*)=0;
	virtual void	SetupMatrixPrj(const DGE_MATRIX*)=0;

	// Get value
	virtual void	GetParamView(DGE_FLOAT3* Eye, DGE_FLOAT3* Look, DGE_FLOAT3* Up)=0;
	virtual void	GetParamProj(FLOAT* fFov, FLOAT* fScnW, FLOAT* fScnH, FLOAT* fNear, FLOAT* fFar)=0;
	
	virtual const	FLOAT* const GetMatrixViw() const=0;
	virtual const	FLOAT* const GetMatrixPrj() const=0;

	virtual const	FLOAT* const GetEye()  const=0;
	virtual const	FLOAT* const GetLook() const=0;
	virtual const	FLOAT* const GetUp()   const=0;

	virtual const	FLOAT* const GetAxisX()=0;
	virtual const	FLOAT* const GetAxisY()=0;
	virtual const	FLOAT* const GetAxisZ()=0;

	// Action
	virtual void	MoveSideward(FLOAT fSpeed)=0;
	virtual void	MoveForward	(FLOAT fSpeed, FLOAT fY=1)=0;
	virtual void	RotateYaw	(FLOAT fDelta, FLOAT fSpeed)=0;
	virtual void	RotatePitch	(FLOAT fDelta, FLOAT fSpeed)=0;
};


typedef IDGX_Camera*	PDGX_CAMERA;


// Create Camera Instance
INT DGX_CreateCamera(char* sCmd
				   , PDGX_CAMERA* pData
				   , DGE_HANDLE p1			// PDGE_DEVICE
				   , DGE_HANDLE p2 = NULL	// User Data(Option)
				   , DGE_HANDLE p3 = NULL	// No Use
				   , DGE_HANDLE p4 = NULL	// No Use
					 );



// Destroy Camera Instance
INT DGX_DestroyCamera(PDGX_CAMERA* pData);


#endif



