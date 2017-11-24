// Implementation of the DGX_Camera.
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

#include <stdio.h>
#include <string.h>

#include <DGE_Math.h>
#include <DGE_Base.h>

#include "DGX_Camera.h"


// Single Camera
class CDGX_Camera : public IDGX_Camera
{
protected:
	PDGE_DEVICE	m_pDev;
	INT			m_eType;			// Camera Type
	
	// For View Matrix
	DGXVECTOR3	m_vcEye;			// Camera position
	DGXVECTOR3	m_vcLook;			// Look vector
	DGXVECTOR3	m_vcUp;				// up vector

	// For Projection Matrix
	FLOAT		m_fScnW;			// Screen Width
	FLOAT		m_fScnH;			// Screen Height
	FLOAT		m_fFv;				// Field of View
	FLOAT		m_fAs;				// Aspect
	FLOAT		m_fNr;				// Near
	FLOAT		m_fFr;				// Far
	
	FLOAT		m_fYaw;
	FLOAT		m_fPitch;

	DGXMATRIX	m_mtViw;			// View Matrix
	DGXMATRIX	m_mtPrj;			// Projection Matrix

	DGXVECTOR3	m_vcAxis[3];		// Camera Axis X, Y, Z

public:
	CDGX_Camera();
	virtual ~CDGX_Camera();

	virtual INT		Update();				// Setup View and Projection Matrix of Camera
	virtual INT		FrameMove();			// Update() + SetTransformViw() and SetTransformPrj()
	virtual INT		SetTransformViw();		// Setup View Matrix of Device and 3d Pipeline.
	virtual INT		SetTransformPrj();		// Setup Projection Matrix of Device and 3d Pipeline.

	virtual INT		Query(char* sCmd, void* pData);
	virtual INT		GetType();


	// Set Parameter
	virtual void	SetupParamView(const DGE_FLOAT3* Eye, const DGE_FLOAT3* LookAt, const DGE_FLOAT3* Up);
	virtual void	SetupParamProj(FLOAT fFov, FLOAT fScnW, FLOAT fScnH, FLOAT fNear, FLOAT fFar);

	// Individual Camera
	virtual void	SetupMatrixViw(const DGE_MATRIX*);
	virtual void	SetupMatrixPrj(const DGE_MATRIX*);

	// Get value
	virtual void	GetParamView(DGE_FLOAT3* Eye, DGE_FLOAT3* Look, DGE_FLOAT3* Up);
	virtual void	GetParamProj(FLOAT* fFov, FLOAT* fScnW, FLOAT* fScnH, FLOAT* fNear, FLOAT* fFar);
	
	virtual const	FLOAT*  const GetMatrixViw() const;
	virtual const	FLOAT*  const GetMatrixPrj() const;

	virtual const	FLOAT* const GetEye()	const;
	virtual const	FLOAT* const GetLook()	const;
	virtual const	FLOAT* const GetUp()	const;

	virtual const	FLOAT* const GetAxisX();
	virtual const	FLOAT* const GetAxisY();
	virtual const	FLOAT* const GetAxisZ();

	// Action
	virtual void	MoveSideward(FLOAT fSpeed);
	virtual void	MoveForward	(FLOAT fSpeed, FLOAT fY=1);
	virtual void	RotateYaw	(FLOAT fDelta, FLOAT fSpeed);
	virtual void	RotatePitch	(FLOAT fDelta, FLOAT fSpeed);

public:
	INT		Create(DGE_HANDLE =NULL, DGE_HANDLE =NULL, DGE_HANDLE =NULL, DGE_HANDLE =NULL);
	void	Destroy();
};




CDGX_Camera::CDGX_Camera()
{
	m_mtViw.Identity();
	m_mtPrj.Identity();

	m_fYaw		= 0.f;
	m_fPitch	= 0.f;

	m_vcEye		= DGXVECTOR3(10, -390, 40);
	m_vcLook	= DGXVECTOR3(0,0,0);
	m_vcUp		= DGXVECTOR3(0,0,1);
	
	m_fFv		= DGX_PI/4.0F;
	m_fScnW		= 320.0F;
	m_fScnH		= 240.0F;
	m_fAs		= m_fScnW/m_fScnH;
	m_fNr		= 1.0F;
	m_fFr		= 5000.0F;
}


CDGX_Camera::~CDGX_Camera()
{
	Destroy();
}



void CDGX_Camera::Destroy()
{
}


INT CDGX_Camera::Create(DGE_HANDLE p1, DGE_HANDLE p2, DGE_HANDLE p3, DGE_HANDLE p4)
{
	if(NULL == p1)
		return DGE_EFAIL;

	m_pDev = (PDGE_DEVICE)p1;

	return DGE_OK;
}


INT CDGX_Camera::SetTransformViw()
{
	// X-Y 평면에 Z 축이 위로 향하는 공간에서 2, 3의 교환과 14, 24, 34의 반전이 필요
	DGXMATRIX	mtViw;
	mtViw._11 = m_mtViw._11;	mtViw._12 = m_mtViw._13;	mtViw._13 = -m_mtViw._12;	mtViw._14 = -m_mtViw._14;
	mtViw._21 = m_mtViw._21;	mtViw._22 = m_mtViw._23;	mtViw._23 = -m_mtViw._22;	mtViw._24 = -m_mtViw._24;
	mtViw._31 = m_mtViw._31;	mtViw._32 = m_mtViw._33;	mtViw._33 = -m_mtViw._32;	mtViw._34 = -m_mtViw._34;
	mtViw._41 = m_mtViw._41;	mtViw._42 = m_mtViw._43;	mtViw._43 = -m_mtViw._42;	mtViw._44 = +m_mtViw._44;

	m_pDev->SetTransform(DGE_TS_VIEW, &mtViw);
	return DGE_OK;
}

INT CDGX_Camera::SetTransformPrj()
{
	m_pDev->SetTransform(DGE_TS_PROJ, &m_mtPrj);
	return DGE_OK;
}


INT CDGX_Camera::Query(char*, void*)
{
	return -1;
}



INT CDGX_Camera::Update()
{
	m_vcAxis[0].x = m_mtViw._11;
	m_vcAxis[0].y = m_mtViw._21;
	m_vcAxis[0].z = m_mtViw._31;

	m_vcAxis[1].x = m_mtViw._12;
	m_vcAxis[1].y = m_mtViw._22;
	m_vcAxis[1].z = m_mtViw._32;

	m_vcAxis[2].x = m_mtViw._13;
	m_vcAxis[2].y = m_mtViw._23;
	m_vcAxis[2].z = m_mtViw._33;

	return DGE_OK;
}


INT CDGX_Camera::FrameMove()
{
	Update();

	SetTransformViw();
	SetTransformPrj();

	return DGE_OK;
}




void CDGX_Camera::SetupParamView(const DGE_FLOAT3* vcEye, const DGE_FLOAT3* vcLook, const DGE_FLOAT3* vcUp)
{
	m_vcEye		= (FLOAT*)vcEye;
	m_vcLook	= (FLOAT*)vcLook;
	m_vcUp		= (FLOAT*)vcUp;

	m_mtViw.SetupViewRH(&m_vcEye, &m_vcLook, &m_vcUp);
}

void CDGX_Camera::SetupParamProj(FLOAT fFov, FLOAT fScnW, FLOAT fScnH, FLOAT fNear, FLOAT fFar)
{
	m_fFv	= fFov;
	m_fScnW	= fScnW;
	m_fScnH	= fScnH;
	m_fAs	= m_fScnW/m_fScnH;
	m_fNr	= fNear;
	m_fFr	= fFar;

	m_mtPrj.SetupPerspectiveRH(m_fFv, m_fAs, m_fNr, m_fFr);
}

INT	CDGX_Camera::GetType()
{
	return m_eType;
}


void CDGX_Camera::GetParamView(DGE_FLOAT3* vcEye, DGE_FLOAT3* vcLook, DGE_FLOAT3* vcUp)
{
	memcpy(vcEye , &m_vcEye	, sizeof(FLOAT));
	memcpy(vcLook, &m_vcLook, sizeof(FLOAT));
	memcpy(vcUp  , &m_vcUp	, sizeof(FLOAT));
}


void CDGX_Camera::GetParamProj(FLOAT* fFov, FLOAT* fScnW, FLOAT* fScnH, FLOAT* fNear, FLOAT* fFar)
{
	*fFov	= m_fFv	;
	*fScnW	= m_fScnW	;
	*fScnH	= m_fScnH	;
	*fNear	= m_fNr	;
	*fFar	= m_fFr	;
}


const FLOAT* const CDGX_Camera::GetMatrixViw() const{	return (FLOAT*)&m_mtViw;	}
const FLOAT* const CDGX_Camera::GetMatrixPrj() const{	return (FLOAT*)&m_mtPrj;	}
const FLOAT* const CDGX_Camera::GetEye() const		{	return (FLOAT*)&m_vcEye;	}
const FLOAT* const CDGX_Camera::GetLook() const		{	return (FLOAT*)&m_vcLook;	}
const FLOAT* const CDGX_Camera::GetUp() const		{	return (FLOAT*)&m_vcUp;		}


const FLOAT* const CDGX_Camera::GetAxisX()			{	return (FLOAT*)&m_vcAxis[0];	}
const FLOAT* const CDGX_Camera::GetAxisY()			{	return (FLOAT*)&m_vcAxis[1];	}
const FLOAT* const CDGX_Camera::GetAxisZ()			{	return (FLOAT*)&m_vcAxis[2];	}


// Individual Camera
void CDGX_Camera::SetupMatrixViw(const DGE_MATRIX* mtViw){	m_mtViw = (FLOAT*)mtViw;	}
void CDGX_Camera::SetupMatrixPrj(const DGE_MATRIX* mtPrj){	m_mtPrj = (FLOAT*)mtPrj;	}


void CDGX_Camera::MoveSideward(FLOAT speed)
{
	DGXVECTOR3 Z = m_vcLook - m_vcEye;


	DGXVECTOR3    X;
	X.Cross(&Z, &m_vcUp);
	X.Normalize();

	X *=speed;
	m_vcEye  += X;
	m_vcLook += X;

	m_mtViw.SetupViewRH(&m_vcEye, &m_vcLook, &m_vcUp);
}

void CDGX_Camera::MoveForward(FLOAT speed, FLOAT)
{
	DGXVECTOR3 T = m_vcLook - m_vcEye;
	T.Normalize();

	T *=speed;

	m_vcLook +=T;
	m_vcEye  +=T;
	m_mtViw.SetupViewRH(&m_vcEye, &m_vcLook, &m_vcUp);
}

void CDGX_Camera::RotateYaw(FLOAT fDelta,FLOAT fSpeed)
{
	m_fYaw		= DGXToRadian(fDelta*fSpeed);

	DGXMATRIX	rot;
	DGXVECTOR3	vcZ = m_vcLook - m_vcEye;


	{
		rot.SetupRotationZ(m_fYaw);
		rot.TransformCoord(&vcZ, &vcZ);
		rot.TransformCoord(&m_vcUp, &m_vcUp);
		
		m_vcLook	= vcZ + m_vcEye;

		m_mtViw.SetupViewRH(&m_vcEye, &m_vcLook, &m_vcUp);
	}
	
}

void CDGX_Camera::RotatePitch(FLOAT fDelta,FLOAT fSpeed)
{
	m_fPitch	= DGXToRadian(fDelta*fSpeed);

	DGXMATRIX	rot;
	DGXVECTOR3 vcZ = m_vcLook - m_vcEye;
	DGXVECTOR3 vcX = DGXVECTOR3(m_mtViw._11, m_mtViw._21, m_mtViw._31);


	{
		rot.SetupRotationAxis(&vcX, m_fPitch);
		rot.TransformCoord(&vcZ, &vcZ);
		rot.TransformCoord(&m_vcUp, &m_vcUp);

		m_vcLook	= vcZ + m_vcEye;

		m_mtViw.SetupViewRH(&m_vcEye, &m_vcLook, &m_vcUp);
	}

}

INT DGX_CreateCamera(char* sCmd
				   , PDGX_CAMERA* pData
				   , DGE_HANDLE p1			// Window Handle
				   , DGE_HANDLE p2			// User Data(Option)
				   , DGE_HANDLE p3			// No Use
				   , DGE_HANDLE p4			// No Use
					 )
{
	CDGX_Camera* pObj = NULL;

	*pData = NULL;

	pObj = new CDGX_Camera;
	if(DGE_FAILED(pObj->Create(p1, p2, p3, p4)))
	{
		delete pObj;
		return DGE_ECANNOTALLOCATED;
	}

	(*pData) = pObj;
	return DGE_OK;
}


INT DGX_DestroyCamera(PDGX_CAMERA* pData)
{
	if(NULL == *pData)
		return DGE_OK;

	delete *pData;
	(*pData) = NULL;

	return DGE_OK;
}






