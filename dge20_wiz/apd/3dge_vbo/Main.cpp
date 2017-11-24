// Implementation of the CMain class.
//
// VBO와 관련된 함수
//
//	- glBindBuffer
//	- glBufferData
//	- glBufferSubData
//	- glDeleteBuffers
//	- glGenBuffers
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
	// Input 생성
	if(DGE_FAILED(DGX_CreateInput(NULL, &m_pInput, m_pDev, m_hWnd)))
		return DGE_EFAIL;


	// Camera 생성
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




	////////////////////////////////////////////////////////////////////////////
	UINT i=0;


	// 시스템 메모리에 정점 데이터 생성
	float vertices[] =
	{
		-10,-10,-10,  +10,-10,-10, +10,+10,-10, -10,+10,-10,
		-10,-10,+10,  +10,-10,+10, +10,+10,+10, -10,+10,+10
	};


	for(i=0; i< sizeof(vertices)/sizeof(vertices[0]); ++i)
		vertices[i] = vertices[i];


	DWORD	dFVF = DGE_FVF_XYZ;
	INT		nSize = sizeof(vertices);
	if(DGE_FAILED(DGE_CreateVB(NULL, &m_pVB, m_pDev, &dFVF, vertices, &nSize)))
		return -1;




	dFVF = DGE_FMT_INDEX16;
	nSize = sizeof(WORD) * 4;

	for(i=0;i<6; ++i)
	{
		if(DGE_FAILED(DGE_CreateIB(NULL, &m_pIB[i], m_pDev, &dFVF)))
			return -1;
	}

	// Index 데이터
	WORD front [] = {2,1,3,0};	// front face
	WORD back  [] = {5,6,4,7};	// back face
	WORD top   [] = {6,2,7,3};	// top face
	WORD bottom[] = {1,5,0,4};	// bottom face
	WORD left  [] = {3,0,7,4};	// left face
	WORD right [] = {6,5,2,1};	// right face

	m_pIB[0]->Fill(front , nSize);
	m_pIB[1]->Fill(back  , nSize);
	m_pIB[2]->Fill(top   , nSize);
	m_pIB[3]->Fill(bottom, nSize);
	m_pIB[4]->Fill(left  , nSize);
	m_pIB[5]->Fill(right , nSize);

	return DGE_OK;
}


INT	CMain::Destroy()
{	
	INT i=0;

	DGE_DestroyVB(&m_pVB);	// VBO 해제

	for(i=0; i<6; ++i)
		DGE_DestroyIB(&m_pIB[i]);	// IBO 해제


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

	if(m_pInput->KeyPress(DGEKEY_FA))
		m_pCam->RotateYaw(fAngle_degree, speed);

	if(m_pInput->KeyPress(DGEKEY_FB))
		m_pCam->RotateYaw(fAngle_degree, -speed);

	if(m_pInput->KeyPress(DGEKEY_FY))
		m_pCam->RotatePitch(fAngle_degree, speed);

	if(m_pInput->KeyPress(DGEKEY_FX))
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



	m_pDev->SetRenderState(DGE_RS_CULL_FACE, DGE_ST_DISABLE);


	m_pXYZ->Render();
	m_pGrid->Render();



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

	m_pDev->SetStreamSource(m_pVB);
	m_pDev->SetFVF(DGE_FVF_XYZ);

	m_pDev->SetColor(1,0,0,1);		m_pDev->SetIndices(m_pIB[0]);	m_pDev->DrawIndexedPrimitivef(DGE_PT_TRIANGLE_STRIP, 4);
	m_pDev->SetColor(0,1,0,1);		m_pDev->SetIndices(m_pIB[1]);	m_pDev->DrawIndexedPrimitivef(DGE_PT_TRIANGLE_STRIP, 4);
	m_pDev->SetColor(0,0,1,1);		m_pDev->SetIndices(m_pIB[2]);	m_pDev->DrawIndexedPrimitivef(DGE_PT_TRIANGLE_STRIP, 4);
	m_pDev->SetColor(1,1,0,1);		m_pDev->SetIndices(m_pIB[3]);	m_pDev->DrawIndexedPrimitivef(DGE_PT_TRIANGLE_STRIP, 4);
	m_pDev->SetColor(0,1,1,1);		m_pDev->SetIndices(m_pIB[4]);	m_pDev->DrawIndexedPrimitivef(DGE_PT_TRIANGLE_STRIP, 4);
	m_pDev->SetColor(1,0,1,1);		m_pDev->SetIndices(m_pIB[5]);	m_pDev->DrawIndexedPrimitivef(DGE_PT_TRIANGLE_STRIP, 4);

	m_pDev->SetFVF(0);
	m_pDev->SetColor(1,1,1,1);

	m_pDev->SetStreamSource(NULL);
	m_pDev->SetIndices(NULL);

	m_pDev->SetTransformIdentity(DGE_TS_WORLD);


	m_pDev->EndScene();

	return DGE_OK;
}



