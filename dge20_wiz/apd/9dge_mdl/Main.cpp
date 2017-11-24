// Implementation of the CMain class.
//
////////////////////////////////////////////////////////////////////////////////


#include "_StdAfx.h"


#define MEDIA_DIR	"../../media/model/"


CMain::CMain()
{
	m_pInput	= NULL;
	m_pCam		= NULL;
	m_pXYZ		= NULL;
	m_pGrid		= NULL;

	m_pMdlOrg1	= NULL;
	m_pMdlIns1	= NULL;

	m_pMdlOrg2	= NULL;
	m_pMdlIns2	= NULL;
}


INT	CMain::Init()
{
	// Input 생성
	if(DGE_FAILED(DGX_CreateInput(NULL, &m_pInput, m_pDev, m_hWnd)))
		return DGE_EFAIL;


	// Camera 생성
	if(DGE_FAILED(DGX_CreateCamera(NULL, &m_pCam, m_pDev)))
		return DGE_EFAIL;


	DGXVECTOR3	vcEye ( 5, -100, 30);
	DGXVECTOR3	vcLook( 5,   0,  30);
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




	char	sMdl1[DGE_MAX_PATH]= MEDIA_DIR"mong.ase";
	char	sMdl2[DGE_MAX_PATH]= MEDIA_DIR"mong.asb";

	// 원본 데이터 생성
	if(DGE_FAILED( DGX_CreateMdl("Ase Txt", &m_pMdlOrg1, m_pDev, (void*)sMdl1)))
		return DGE_EFAIL;

	if(DGE_FAILED( DGX_CreateMdl("Ase Bin", &m_pMdlOrg2, m_pDev, (void*)sMdl2)))
		return DGE_EFAIL;


	// 원본 데이터에서 모델 복제
	if(DGE_FAILED( DGX_CreateMdl("Ase Bin", &m_pMdlIns1, NULL, NULL, m_pMdlOrg2)))
		return DGE_EFAIL;

	if(DGE_FAILED( DGX_CreateMdl("Ase Bin", &m_pMdlIns2, NULL, NULL, m_pMdlOrg2)))
		return DGE_EFAIL;


	return DGE_OK;
}



INT	CMain::Destroy()
{	
	DGX_DestroyEntity(&m_pXYZ);
	DGX_DestroyEntity(&m_pGrid);
	
	DGX_DestroyCamera(&m_pCam);
	DGX_DestroyInput(&m_pInput);

	DGX_DestroyMdl(&m_pMdlOrg1);
	DGX_DestroyMdl(&m_pMdlIns1);

	DGX_DestroyMdl(&m_pMdlOrg2);
	DGX_DestroyMdl(&m_pMdlIns2);

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

	if(n>5)
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


	// 애니메이션에 필요한 시간과 행렬 설정
	DOUBLE fElapsedTime = this->GetElapsedTime();
	DOUBLE fTime;

	DGXMATRIX	mtRotX;
	DGXMATRIX	mtRotZ;
	DGXMATRIX	mtWld;

	DGXVECTOR3	vcOrg1(-45, 0, 0);

	mtWld.Identity();
	mtRotZ.SetupRotationZ(DGXToRadian(0));
	mtWld.SetupTranslation( &vcOrg1, FALSE);
	mtWld = mtRotX * mtRotZ * mtWld;
	fTime = fElapsedTime*0.8;

	m_pMdlOrg1->SetAttrib(DGXM_WORLD_MATRIX, &mtWld);
	m_pMdlOrg1->SetAttrib(DGXM_ADVANCE_TIME, &fTime);
//	{
//		struct _TT{ INT B; INT E;} t={10, 20};
//		m_pMdlOrg1->SetAttrib(DGXM_LOOP_SECTION, &t);
//	}

	m_pMdlOrg1->FrameMove();


	DGXVECTOR3	vcIns1(-15, 0, 0);

	mtWld.Identity();
	mtRotZ.SetupRotationZ(DGXToRadian(90));
	mtWld.SetupTranslation(&vcIns1, FALSE);
	mtWld = mtRotZ * mtWld;
	fTime = fElapsedTime*.4;

	m_pMdlIns1->SetAttrib(DGXM_WORLD_MATRIX, &mtWld);
	m_pMdlIns1->SetAttrib(DGXM_ADVANCE_TIME, &fTime);
	{
		struct _TT{ INT B; INT E;} t={10, 25};
		m_pMdlIns1->SetAttrib(DGXM_LOOP_SECTION, &t);
	}

	m_pMdlIns1->FrameMove();


//	float v1;
//	float v2;
//	m_pMdlOrg1->GetVal(DGXM_CURRENT_TIME, &v1);
//	m_pMdlIns1->GetVal(DGXM_CURRENT_TIME, &v2);
//	McUtil_SetWindowTitle("%f %f", v1, v2);

	DGXVECTOR3	vcOrg2(15, 0, 0);

	mtWld.Identity();
	mtRotZ.SetupRotationZ(DGXToRadian(-90));
	mtWld.SetupTranslation(&vcOrg2, FALSE);
	mtWld = mtRotZ * mtWld;
	fTime = fElapsedTime*.6f;

	m_pMdlOrg2->SetAttrib(DGXM_WORLD_MATRIX, &mtWld);
	m_pMdlOrg2->SetAttrib(DGXM_ADVANCE_TIME, &fTime);
	{
		struct _TT{ INT B; INT E;} t={25, 50};
		m_pMdlOrg2->SetAttrib(DGXM_LOOP_SECTION, &t);
	}
	m_pMdlOrg2->FrameMove();


	DGXVECTOR3	vcIns2(45, 0, 0);

	mtWld.Identity();
	mtRotZ.SetupRotationZ(DGXToRadian(-90));
	mtWld.SetupTranslation(&vcIns2, FALSE);
	mtWld = mtRotZ * mtWld;
	fTime = fElapsedTime*1.f;

	m_pMdlIns2->SetAttrib(DGXM_WORLD_MATRIX, &mtWld);
	m_pMdlIns2->SetAttrib(DGXM_ADVANCE_TIME, &fTime);
	{
		struct _TT{ INT B; INT E;} t={140, 140};
		m_pMdlIns2->SetAttrib(DGXM_LOOP_SECTION, &t);
	}
	m_pMdlIns2->FrameMove();




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

	// 모델 렌더링
	m_pMdlOrg1->Render();
	m_pMdlIns1->Render();

	m_pMdlOrg2->Render();
	m_pMdlIns2->Render();



	static int c =0;
	++c;

	DGXMATRIX	mtRotX;
	DGXMATRIX	mtRotZ;
	DGXMATRIX	mtWld;
	mtRotZ.SetupRotationZ( DGXToRadian(c*3.5f));
	mtRotX.SetupRotationX( DGXToRadian(c*3.5f));

	mtWld = mtRotZ * mtRotX;

	mtWld._41 = 10;
	mtWld._42 = -10;
	m_pDev->SetTransform(DGE_TS_WORLD, &mtWld);

	m_pDev->SetTransformIdentity(DGE_TS_WORLD);



	m_pDev->EndScene();

	return DGE_OK;
}


