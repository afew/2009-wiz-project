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

	m_pMdl		= NULL;
}


INT	CMain::Init()
{
	// Input 持失
	if(DGE_FAILED(DGX_CreateInput(NULL, &m_pInput, m_pDev, m_hWnd)))
		return DGE_EFAIL;


	// Camera 持失
	if(DGE_FAILED(DGX_CreateCamera(NULL, &m_pCam, m_pDev)))
		return DGE_EFAIL;


	DGXVECTOR3	vcEye (16, -50, 10);
	DGXVECTOR3	vcLook(16,  50, 15);
	DGXVECTOR3	vcUp  ( 0,   0,  1);
	m_pCam->SetupParamView(&vcEye, &vcLook, &vcUp);

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

	SAFE_DELETE(	m_pMdl	);

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
		return DGE_EFAIL;
	}
	

	static int n = 0;
	++n;

	if(n>32)
	{
		printf("FPS: %3.f\n", m_fFPS);
		n = 0;
	}

	// Input Update
	m_pInput->Update();

	const BYTE*	pKey = m_pInput->GetKeyMap();

	if(pKey[DGEKEY_MENU])
		return DGE_EFAIL;



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

	if(pKey[DGEKEY_FA])
		m_pCam->RotateYaw(fAngle_degree, speed);

	if(pKey[DGEKEY_FB])
		m_pCam->RotateYaw(fAngle_degree, -speed);

	if(pKey[DGEKEY_FY])
		m_pCam->RotatePitch(fAngle_degree, speed);

	if(pKey[DGEKEY_FX])
		m_pCam->RotatePitch(fAngle_degree, -speed);

	
	m_pCam->Update();


	DOUBLE fElapsedTime = this->GetElapsedTime();
	DOUBLE fTime;


	if(m_pMdl)
	{
		DGXMATRIX	mtRotX;
		DGXMATRIX	mtRotZ;
		DGXMATRIX	mtWld;

		DGXVECTOR3	vcOrg1(16, 16, 0);

		mtWld.Identity();
		mtRotZ.SetupRotationZ(DGXToRadian(0));
		mtWld.SetupTranslation( &vcOrg1, FALSE);
		mtWld = mtRotX * mtRotZ * mtWld;
		fTime = fElapsedTime*1.0;

		m_pMdl->SetAttrib(DGXM_WORLD_MATRIX, &mtWld);
		m_pMdl->SetAttrib(DGXM_ADVANCE_TIME, &fTime);

		m_pMdl->FrameMove();


		DGXVECTOR3	vcIns1(-15, 0, 0);

		mtWld.Identity();
		mtRotZ.SetupRotationZ(DGXToRadian(90));
		mtWld.SetupTranslation(&vcIns1, FALSE);
		mtWld = mtRotZ * mtWld;
		fTime = fElapsedTime*.4;
	}


#if defined(_WIN32) || defined(WIN32)
	char	sBuf[128]={0};
	sprintf(sBuf, "%lf", fElapsedTime);
	SetWindowText((HWND)m_hWnd, sBuf);
#endif
	
	return DGE_OK;
}


INT	CMain::Render()
{
	m_pDev->BeginScene();

	m_pDev->Clear(DGE_CLEAR_COLOR_BUFFER | DGE_CLEAR_DEPTH_BUFFER);

	m_pCam->SetTransformPrj();
	m_pCam->SetTransformViw();


	m_pDev->SetRenderState(DGE_RS_CULL_FACE, DGE_ST_ENABLE);
	m_pDev->SetRenderState(DGE_RS_CULL_MODE, DGE_ST_CCW);
	m_pDev->SetRenderState(DGE_RS_CULL_FACE, DGE_ST_BACK);

	
	m_pXYZ->Render();
	m_pGrid->Render();

	if(m_pMdl)
		m_pMdl->Render();

	m_pDev->EndScene();


	return DGE_OK;
}


LRESULT CMain::MsgProc(DGE_HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{


#if defined(_WIN32) || defined(WIN32)
	if(WM_LBUTTONDOWN == uMsg && (GetAsyncKeyState(VK_LCONTROL ) &0X8000))
	{
		CHAR			sDir[MAX_PATH]="\0";
		OPENFILENAME	OFN;
		CHAR			sF[MAX_PATH];
		CHAR			sMdlFile[MAX_PATH]="";
		CHAR			InitDir[MAX_PATH]={0};
		
		GetCurrentDirectory(MAX_PATH, sDir);

		strcpy(InitDir, sDir);

		memset(&OFN, 0, sizeof(OFN));
		OFN.lStructSize = sizeof(OFN);
		OFN.hwndOwner = hWnd;
		OFN.lpstrFilter="ase Files(*.ase)\0*.ase\0All Files(*.*)\0*.*\0";
		OFN.lpstrFile=sMdlFile;
		OFN.nMaxFile=MAX_PATH;
		
		OFN.lpstrTitle="Choose the file...";
		OFN.lpstrFileTitle=sF;
		OFN.nMaxFileTitle=MAX_PATH;
		OFN.lpstrDefExt="ase";

		OFN.lpstrInitialDir	= InitDir;

		if( !GetOpenFileName(&OFN))
			return 0;

		SetCurrentDirectory(sDir);

		PDGX_MDL pMdl	;		// Original
		if(DGE_SUCCEEDED( DGX_CreateMdl("Ase Txt", &pMdl, m_pDev, (void*)sMdlFile)))
		{
			SAFE_DELETE(	m_pMdl	);
			m_pMdl = pMdl;

			printf("Model Load Success: %s\n", sMdlFile);
		}
		else
			printf("Model Load Failed: %s\n", sMdlFile);



		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
#endif

	return CAppDge::MsgProc(hWnd, uMsg, wParam, lParam);
}

