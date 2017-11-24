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

	m_pEft		= NULL;
}


INT	CMain::Init()
{
	// Input 持失
	if(DGE_FAILED(DGX_CreateInput(NULL, &m_pInput, m_pDev, m_hWnd)))
		return DGE_EFAIL;
	
	
	// Camera 持失
	if(DGE_FAILED(DGX_CreateCamera(NULL, &m_pCam, m_pDev)))
		return DGE_EFAIL;
	
	
	DGXVECTOR3	vcEye (0, -130,  0);
	DGXVECTOR3	vcLook(0,    0,  0);
	DGXVECTOR3	vcUp  (0,    0,  1);

	m_pCam->SetupParamView(&vcEye, &vcLook, &vcUp);

	FLOAT	fFov = DGXToRadian(45.0F);
	FLOAT	fScnW= FLOAT(m_nScnW);
	FLOAT	fScnH= FLOAT(m_nScnH);
	FLOAT	fNear= 1.0F;
	FLOAT	fFar = 5000.0F;

	m_pCam->SetupParamProj(fFov, fScnW, fScnH, fNear, fFar);
	
	
	
	if(DGE_FAILED(DGX_CreateEntity((char*)"Axis", &m_pXYZ, m_pDev)))
		return DGE_EFAIL;
	
	
	if(DGE_FAILED(DGX_CreateEntity((char*)"Grid", &m_pGrid, m_pDev)))
		return DGE_EFAIL;
	


	m_pEft = new CParticle;
	if(DGE_FAILED(m_pEft->Create(m_pDev)))
	{
		delete m_pEft;
		m_pEft = NULL;

		return DGE_EFAIL;
	}

	return DGE_OK;
}


INT	CMain::Destroy()
{
	if(m_pEft)
	{
		delete m_pEft;
		m_pEft = NULL;
	}

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
	if(c>20*60 * 30)
	{
		printf("Game Process Terminated\n");
		return -1;
	}
	
	
	static int n = 0;
	++n;
	
	if(n>5)
	{
		printf("FPS: %3.f\n", m_fFPS);
		n = 0;
	}
	
	
	// Input Update
	m_pInput->Update();
	
	const BYTE*	pKey = m_pInput->GetKeyMap();
	
	if(pKey[DGEKEY_MENU])
		return -1;
	
	
	// Move, Rotation Speed
	FLOAT speed = (FLOAT)this->GetElapsedTime();
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
	
	if(m_pInput->KeyPress(DGEKEY_FA))
		m_pCam->RotateYaw(fAngle_degree, speed);
	
	if(m_pInput->KeyPress(DGEKEY_FB))
		m_pCam->RotateYaw(fAngle_degree, -speed);
	
	if(m_pInput->KeyPress(DGEKEY_FY))
		m_pCam->RotatePitch(fAngle_degree, speed);
	
	if(m_pInput->KeyPress(DGEKEY_FX))
		m_pCam->RotatePitch(fAngle_degree, -speed);
	
	
	m_pCam->Update();



	m_pEft->FrameMove();
	
	
	return DGE_OK;
}



INT	CMain::Render()
{
	m_pDev->BeginScene();

	m_pDev->Clear(DGE_CLEAR_COLOR_BUFFER | DGE_CLEAR_DEPTH_BUFFER);
	
	m_pCam->SetTransformPrj();
	m_pCam->SetTransformViw();
	
	
//	m_pXYZ->Render();
//	m_pGrid->Render();

	m_pEft->Render();



	m_pDev->EndScene();
	
	return DGE_OK;
}








