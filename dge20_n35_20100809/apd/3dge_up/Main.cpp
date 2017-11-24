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

	// front face
	m_pIdx[ 0] = DGE3D::VtxIdxW(2,1,3);
	m_pIdx[ 1] = DGE3D::VtxIdxW(1,3,0);

	// back face
	m_pIdx[ 2] = DGE3D::VtxIdxW(5,6,4);
	m_pIdx[ 3] = DGE3D::VtxIdxW(6,4,7);

	// top face
	m_pIdx[ 4] = DGE3D::VtxIdxW(6,2,7);
	m_pIdx[ 5] = DGE3D::VtxIdxW(2,7,3);

	// bottom face
	m_pIdx[ 6] = DGE3D::VtxIdxW(1,5,0);
	m_pIdx[ 7] = DGE3D::VtxIdxW(5,0,4);

	// left face
	m_pIdx[ 8] = DGE3D::VtxIdxW(3,0,7);
	m_pIdx[ 9] = DGE3D::VtxIdxW(0,7,4);

	// right face
	m_pIdx[10] = DGE3D::VtxIdxW(6,5,2);
	m_pIdx[11] = DGE3D::VtxIdxW(5,2,1);


	// Setup Vertex buffer for Object1
	DGE3D::Vxf*	pVtx1 = new DGE3D::Vxf[8];

	pVtx1[0].p = DGXVECTOR3(-10,-10,-10);
	pVtx1[1].p = DGXVECTOR3(+10,-10,-10);
	pVtx1[2].p = DGXVECTOR3(+10,+10,-10);
	pVtx1[3].p = DGXVECTOR3(-10,+10,-10);
	pVtx1[4].p = DGXVECTOR3(-10,-10,+10);
	pVtx1[5].p = DGXVECTOR3(+10,-10,+10);
	pVtx1[6].p = DGXVECTOR3(+10,+10,+10);
	pVtx1[7].p = DGXVECTOR3(-10,+10,+10);

	m_pObj1.pIdx = m_pIdx;
	m_pObj1.pVtx = pVtx1;


	// Setup Vertex buffer for Object2
	DGE3D::VxfD* pVtx2 = new DGE3D::VxfD[8];

	pVtx2[0].p = DGXVECTOR3(-10,-10,-10);
	pVtx2[1].p = DGXVECTOR3(+10,-10,-10);
	pVtx2[2].p = DGXVECTOR3(+10,+10,-10);
	pVtx2[3].p = DGXVECTOR3(-10,+10,-10);
	pVtx2[4].p = DGXVECTOR3(-10,-10,+10);
	pVtx2[5].p = DGXVECTOR3(+10,-10,+10);
	pVtx2[6].p = DGXVECTOR3(+10,+10,+10);
	pVtx2[7].p = DGXVECTOR3(-10,+10,+10);

	pVtx2[0].d = DGE_COLORB(255,   0,   0, 255);
	pVtx2[1].d = DGE_COLORB(  0, 255,   0, 255);
	pVtx2[2].d = DGE_COLORB(  0,   0, 255, 255);
	pVtx2[3].d = DGE_COLORB(255, 255,   0, 255);
	pVtx2[4].d = DGE_COLORB(  0, 255, 255, 255);
	pVtx2[5].d = DGE_COLORB(255,   0, 255, 255);
	pVtx2[6].d = DGE_COLORB(255,   0,   0, 255);
	pVtx2[7].d = DGE_COLORB(  0, 255,   0, 255);

	m_pObj2.pIdx = m_pIdx;
	m_pObj2.pVtx = pVtx2;

	return DGE_OK;
}

INT	CMain::Destroy()
{
	if(m_pObj1.pVtx)
	{
		DGE3D::Vxf*	 pVtx = (DGE3D::Vxf*)m_pObj1.pVtx;
		delete [] pVtx;
		m_pObj1.pVtx = NULL;
	}

	if(m_pObj2.pVtx)
	{
		DGE3D::VxfD* pVtx = (DGE3D::VxfD*)m_pObj2.pVtx;
		delete [] pVtx;
		m_pObj2.pVtx = NULL;
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
	if(c>20*60 * 1)
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



	// Setup World Matrix
	static int k =0;
	++k;

	DGXMATRIX	mtRotX;
	DGXMATRIX	mtRotZ;
	
	mtRotZ.SetupRotationZ( DGXToRadian(k*3.5f));
	mtRotX.SetupRotationX( DGXToRadian(k*3.5f));

	m_pObj1.mtWld = mtRotZ * mtRotX;
	m_pObj1.mtWld._41 = 10;
	m_pObj1.mtWld._42 = -10;



	mtRotZ.SetupRotationZ( DGXToRadian(k*2.5f));
	mtRotX.SetupRotationX( DGXToRadian(-k*1.5f));

	m_pObj2.mtWld = mtRotZ * mtRotX;
	m_pObj2.mtWld._41 = 40;
	m_pObj2.mtWld._42 = 10;


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


	m_pDev->SetTransform(DGE_TS_WORLD, &m_pObj1.mtWld);
	m_pDev->SetFVF(DGE3D::Vxf::FVF);

	glColor4f(1,0,0,1);		m_pDev->DrawIndexedPrimitiveUPf(GL_TRIANGLES, 2* 3, &m_pIdx[0*2], m_pObj1.pVtx, sizeof(DGE3D::Vxf));
	glColor4f(0,1,0,1);		m_pDev->DrawIndexedPrimitiveUPf(GL_TRIANGLES, 2* 3, &m_pIdx[1*2], m_pObj1.pVtx, sizeof(DGE3D::Vxf));
	glColor4f(0,0,1,1);		m_pDev->DrawIndexedPrimitiveUPf(GL_TRIANGLES, 2* 3, &m_pIdx[2*2], m_pObj1.pVtx, sizeof(DGE3D::Vxf));
	glColor4f(1,1,0,1);		m_pDev->DrawIndexedPrimitiveUPf(GL_TRIANGLES, 2* 3, &m_pIdx[3*2], m_pObj1.pVtx, sizeof(DGE3D::Vxf));
	glColor4f(0,1,1,1);		m_pDev->DrawIndexedPrimitiveUPf(GL_TRIANGLES, 2* 3, &m_pIdx[4*2], m_pObj1.pVtx, sizeof(DGE3D::Vxf));
	glColor4f(1,0,1,1);		m_pDev->DrawIndexedPrimitiveUPf(GL_TRIANGLES, 2* 3, &m_pIdx[5*2], m_pObj1.pVtx, sizeof(DGE3D::Vxf));

	glColor4f(1,1,1,1);


	m_pDev->SetTransform(DGE_TS_WORLD, &m_pObj2.mtWld);
	m_pDev->SetFVF(DGE3D::VxfD::FVF);
	m_pDev->DrawIndexedPrimitiveUPf(GL_TRIANGLES, 6*2*3, m_pIdx, m_pObj2.pVtx, sizeof(DGE3D::VxfD));

	m_pDev->SetTransformIdentity(DGE_TS_WORLD);



	m_pDev->EndScene();

	return DGE_OK;
}



