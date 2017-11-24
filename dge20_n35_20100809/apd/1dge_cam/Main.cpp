// Implementation of the CMain class.
//
////////////////////////////////////////////////////////////////////////////////


#include "_StdAfx.h"


CMain::CMain()
{
	m_pInput	= NULL;
	m_pCam		= NULL;
	m_pXYZ		= NULL;
	m_pGrid		= NULL;
}


INT	CMain::Init()
{
	// Input 持失
	if(DGE_FAILED(DGX_CreateInput(NULL, &m_pInput, m_pDev, m_hWnd)))
		return DGE_EFAIL;


	// Camera 持失
	if(DGE_FAILED(DGX_CreateCamera(NULL, &m_pCam, m_pDev)))
		return DGE_EFAIL;



	DGXVECTOR3	vcEye (30, -100, 30);
	DGXVECTOR3	vcLook(30,   0,  0);
	DGXVECTOR3	vcUp  ( 0,   0,  1);
	m_pCam->SetupParamView( &vcEye, &vcLook, &vcUp);

	FLOAT	fFov = DGXToRadian(45.0F);
	FLOAT	fScnW= FLOAT(m_nScnW);
	FLOAT	fScnH= FLOAT(m_nScnH);
	FLOAT	fNear= 1.0F;
	FLOAT	fFar = 5000.0F;
	m_pCam->SetupParamProj(fFov, fScnW, fScnH, fNear, fFar);


	if(DGE_FAILED(DGX_CreateEntity("Axis", &m_pXYZ, m_pDev)))
		return DGE_EFAIL;


	if(DGE_FAILED(DGX_CreateEntity("Grid", &m_pGrid, m_pDev)))
		return DGE_EFAIL;

	return DGE_OK;
}

INT	CMain::Destroy()
{	
	DGX_DestroyEntity(&m_pXYZ);
	DGX_DestroyEntity(&m_pGrid);
	
	DGX_DestroyCamera(&m_pCam);
	DGX_DestroyInput(&m_pInput);

	return DGE_OK;
}

INT	CMain::FrameMove()
{
#if defined(_WIN32) || defined(WIN32)
	Sleep(10);
#endif
	

	static INT c=0;
	++c;

	//	if(c>20*60*20)
	if(c>20*60 * 10)
	{
		printf("Game Process Terminated\n");
		return -1;
	}
	printf("FPS: %3.f\n", m_fFPS);



	// Input Update
	m_pInput->Update();

	const BYTE*	pKey = m_pInput->GetKeyMap();
	const BYTE*	pTsb = m_pInput->GetTsbMap();

	if(pKey[DGEKEY_MENU])
		return -1;


	// Move, Rotation Speed
	FLOAT speed = (FLOAT)m_fElapsed;
	speed *=100.f;


	// Translation
	if(pKey[DGEKEY_UP])
		m_pCam->MoveForward(+speed);

	if(pKey[DGEKEY_DOWN])
		m_pCam->MoveForward(-speed);

	if(pKey[DGEKEY_LEFT])
		m_pCam->MoveSideward(-speed);

	if(pKey[DGEKEY_RIGHT])
		m_pCam->MoveSideward(+speed);


	// Rotation
	float fAngle_degree = 2.0f;

	if(pKey[DGEKEY_FA])
		m_pCam->RotateYaw(fAngle_degree, speed);

	if(pKey[DGEKEY_FB])
		m_pCam->RotateYaw(fAngle_degree, -speed);

	if(pKey[DGEKEY_FY])
		m_pCam->RotatePitch(fAngle_degree, speed);

	if(pKey[DGEKEY_FX])
		m_pCam->RotatePitch(fAngle_degree, -speed);


	m_pCam->Update();
	
	return DGE_OK;
}


INT	CMain::Render()
{
	m_pDev->BeginScene();

	m_pDev->Clear(DGE_CLEAR_COLOR_BUFFER | DGE_CLEAR_DEPTH_BUFFER);

	m_pCam->SetTransformPrj();
	m_pCam->SetTransformViw();


	m_pDev->SetRenderState(DGE_RS_CULL_FACE, DGE_ST_ENABLE);

	m_pXYZ->Render();
	m_pGrid->Render();


	m_pDev->EndScene();

	return DGE_OK;
}


