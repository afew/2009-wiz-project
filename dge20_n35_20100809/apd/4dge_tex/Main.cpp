// Implementation of the CMain class.
//
////////////////////////////////////////////////////////////////////////////////


#include "_StdAfx.h"


#define MEDIA_DIR	"../../media/"


CMain::CMain()
{
	m_pInput	= NULL;
	m_pCam		= NULL;
	m_pXYZ		= NULL;
	m_pGrid		= NULL;

	m_pIdx		= NULL;
	m_pVtx		= NULL;

	m_pObj1		= NULL;
	m_pObj2		= NULL;
}


INT	CMain::Init()
{
	// Input 持失
	if(DGE_FAILED(DGX_CreateInput(NULL, &m_pInput, m_pDev, m_hWnd)))
		return DGE_EFAIL;


	// Camera 持失
	if(DGE_FAILED(DGX_CreateCamera(NULL, &m_pCam, m_pDev)))
		return DGE_EFAIL;


	DGXVECTOR3	vcEye (60, -100, 60);
	DGXVECTOR3	vcLook(30,   0,  0);
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




	// Setup Index Buffer	
	m_pIdx = new DGE3D::VtxIdxW[12];


	// the front face index data
	m_pIdx[0] = DGE3D::VtxIdxW(0, 1, 2);
	m_pIdx[1] = DGE3D::VtxIdxW(0, 2, 3);

	// the back face index data
	m_pIdx[2] = DGE3D::VtxIdxW(4, 5, 6);
	m_pIdx[3] = DGE3D::VtxIdxW(4, 6, 7);

	// the top face index data
	m_pIdx[4] = DGE3D::VtxIdxW( 8,  9, 10);
	m_pIdx[5] = DGE3D::VtxIdxW( 8, 10, 11);

	// the bottom face index data
	m_pIdx[6] = DGE3D::VtxIdxW(12, 13, 14);
	m_pIdx[7] = DGE3D::VtxIdxW(12, 14, 15);

	// the left face index data
	m_pIdx[8] = DGE3D::VtxIdxW(16, 17, 18);
	m_pIdx[9] = DGE3D::VtxIdxW(16, 18, 19);

	// the right face index data
	m_pIdx[10] = DGE3D::VtxIdxW(20, 21, 22);
	m_pIdx[11] = DGE3D::VtxIdxW(20, 22, 23);



	// Setup Vertex Data
	m_pVtx = new VtxUV1[24];


	// the front face vertex data
	m_pVtx[ 0] = VtxUV1(-1.0F, -1.0F, -1.0F,  0.0F, 1.0F);
	m_pVtx[ 1] = VtxUV1(-1.0F,  1.0F, -1.0F,  0.0F, 0.0F);
	m_pVtx[ 2] = VtxUV1( 1.0F,  1.0F, -1.0F,  1.0F, 0.0F);
	m_pVtx[ 3] = VtxUV1( 1.0F, -1.0F, -1.0F,  1.0F, 1.0F);

	// the back face vertex data
	m_pVtx[ 4] = VtxUV1(-1.0F, -1.0F, +1.0F,  0.0F, 1.0F);
	m_pVtx[ 5] = VtxUV1( 1.0F, -1.0F, +1.0F,  0.0F, 0.0F);
	m_pVtx[ 6] = VtxUV1( 1.0F,  1.0F, +1.0F,  1.0F, 0.0F);
	m_pVtx[ 7] = VtxUV1(-1.0F,  1.0F, +1.0F,  1.0F, 1.0F);

	// the top face vertex data
	m_pVtx[ 8] = VtxUV1(-1.0F, +1.0F, -1.0F,  0.0F, 1.0F);
	m_pVtx[ 9] = VtxUV1(-1.0F, +1.0F,  1.0F,  0.0F, 0.0F);
	m_pVtx[10] = VtxUV1( 1.0F, +1.0F,  1.0F,  1.0F, 0.0F);
	m_pVtx[11] = VtxUV1( 1.0F, +1.0F, -1.0F,  1.0F, 1.0F);

	// the bottom face vertex data
	m_pVtx[12] = VtxUV1(-1.0F, -1.0F, -1.0F,  0.0F, 1.0F);
	m_pVtx[13] = VtxUV1( 1.0F, -1.0F, -1.0F,  0.0F, 0.0F);
	m_pVtx[14] = VtxUV1( 1.0F, -1.0F,  1.0F,  1.0F, 0.0F);
	m_pVtx[15] = VtxUV1(-1.0F, -1.0F,  1.0F,  1.0F, 1.0F);

	// the left face vertex data
	m_pVtx[16] = VtxUV1(-1.0F, -1.0F,  1.0F,  0.0F, 1.0F);
	m_pVtx[17] = VtxUV1(-1.0F,  1.0F,  1.0F,  0.0F, 0.0F);
	m_pVtx[18] = VtxUV1(-1.0F,  1.0F, -1.0F,  1.0F, 0.0F);
	m_pVtx[19] = VtxUV1(-1.0F, -1.0F, -1.0F,  1.0F, 1.0F);

	// the right face vertex data
	m_pVtx[20] = VtxUV1( 1.0F, -1.0F, -1.0F,  0.0F, 1.0F);
	m_pVtx[21] = VtxUV1( 1.0F,  1.0F, -1.0F,  0.0F, 0.0F);
	m_pVtx[22] = VtxUV1( 1.0F,  1.0F,  1.0F,  1.0F, 0.0F);
	m_pVtx[23] = VtxUV1( 1.0F, -1.0F,  1.0F,  1.0F, 1.0F);


	// Texture Coordinate
	m_pVtx[0].t = DGXVECTOR2(-0,-0);
	m_pVtx[1].t = DGXVECTOR2(+1,-0);
	m_pVtx[2].t = DGXVECTOR2(+1,+1);
	m_pVtx[3].t = DGXVECTOR2(-0,+1);
	m_pVtx[4].t = DGXVECTOR2(-0,-0);
	m_pVtx[5].t = DGXVECTOR2(+1,-0);
	m_pVtx[6].t = DGXVECTOR2(+1,+1);
	m_pVtx[7].t = DGXVECTOR2(-0,+1);





	m_pObj1 = new CRndObj;
	if(m_pObj1->Create(m_pDev, (void*)MEDIA_DIR"tex/wizLogo.tga"))
	{
		delete m_pObj1;
		return -1;
	}

	m_pObj1->SetIdx(m_pIdx, 6 * 2);
	m_pObj1->SetVtx(m_pVtx);



	m_pObj2 = new CRndObj;
	if(m_pObj2->Create(m_pDev, (void*)MEDIA_DIR"tex/bg.tga"))
	{
		delete m_pObj2;
		return -1;
	}

	m_pObj2->SetIdx(m_pIdx, 6 * 2);
	m_pObj2->SetVtx(m_pVtx);


	return DGE_OK;
}

INT	CMain::Destroy()
{
	SAFE_DELETE(	m_pObj1	);
	SAFE_DELETE(	m_pObj2	);

	SAFE_DELETE_ARRAY(	m_pIdx	);
	SAFE_DELETE_ARRAY(	m_pVtx	);


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







	// Setup World Matrix
	static int k =0;
	++k;

	DGXMATRIX	mtWld;
	DGXMATRIX	mtScl;
	DGXMATRIX	mtRotX;
	DGXMATRIX	mtRotZ;
	
	mtScl.SetupScaling(9.5F, 9.5F, 9.5F);
	mtRotZ.SetupRotationZ( DGXToRadian(k*3.5f));
	mtRotX.SetupRotationX( DGXToRadian(k*3.5f));

	mtWld = mtScl * mtRotZ * mtRotX;
	mtWld._41 = 10;
	mtWld._42 = -10;
	m_pObj1->SetMatrix(&mtWld);



	mtScl.SetupScaling(12.5F, 12.5F, 12.5F);
	mtRotZ.SetupRotationZ( DGXToRadian(k*2.5f));
	mtRotX.SetupRotationX( DGXToRadian(-k*1.5f));
	mtWld = mtScl * mtRotZ * mtRotX;
	mtWld._41 = 40;
	mtWld._42 = 80;
	m_pObj2->SetMatrix(&mtWld);


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


	m_pObj1->Render();
	m_pObj2->Render();



	m_pDev->EndScene();

	return DGE_OK;
}


