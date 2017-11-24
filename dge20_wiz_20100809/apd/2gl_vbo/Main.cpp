// Implementation of the CMain class.
//
// VBO�� ���õ� �Լ�
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
	// Input ����
	if(DGE_FAILED(DGX_CreateInput(NULL, &m_pInput, m_pDev, m_hWnd)))
		return DGE_EFAIL;


	// Camera ����
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



	// VBO(Vertex Buffer Object) 1���� ����
	glGenBuffers(1, &m_Vtx);


	// �ý��� �޸𸮿� ���� ������ ����
	GLfloat vertices[] =
	{
		-10,-10,-10,  +10,-10,-10, +10,+10,-10, -10,+10,-10,
		-10,-10,+10,  +10,-10,+10, +10,+10,+10, -10,+10,+10
	};

	for(UINT i=0; i< sizeof(vertices)/sizeof(vertices[0]); ++i)
		vertices[i] = vertices[i];


	// VBO ���� ����
	glBindBuffer(GL_ARRAY_BUFFER,m_Vtx);

	// �ý��� �޸𸮿� ����� ���� �����͸� VBO�� ����
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	// ���� �����Ͱ� VBO�� �����Ǿ� �־ malloc, new�� ������ �޸𸮸�
	// ���⼭ �����ص� �ȴ�.
	// ���� ���� ����...
	//

	// VBO ���� ����
	glBindBuffer(GL_ARRAY_BUFFER, 0);




	// IBO(Index Buffer Object) ���� �� IBO�� VBO ��. ������ ���ؼ� ������ �̸��� ����.

	// 6�鿡 ���� IBO 6 ���� ����
	glGenBuffers(6, &m_Idx[0]);


	// Index ������
	WORD front [] = {2,1,3,0};	// front face
	WORD back  [] = {5,6,4,7};	// back face
	WORD top   [] = {6,2,7,3};	// top face
	WORD bottom[] = {1,5,0,4};	// bottom face
	WORD left  [] = {3,0,7,4};	// left face
	WORD right [] = {6,5,2,1};	// right face

	// IBO�� �ε��� ������ ����
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Idx[0]);	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(front ), front , GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Idx[1]);	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(back  ), back  , GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Idx[2]);	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(top   ), top   , GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Idx[3]);	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(bottom), bottom, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Idx[4]);	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(left  ), left  , GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Idx[5]);	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(right ), right , GL_STATIC_DRAW);

	// IBO ���� ����
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	return DGE_OK;
}

INT	CMain::Destroy()
{	
	// VBO ����
	if(m_Vtx)
	{
		glDeleteBuffers(1, &m_Vtx);
		m_Vtx =0;
	}

	// IBO ����
	if(m_Idx[0])
	{
		glDeleteBuffers(6, &m_Idx[0]);
		memset(m_Idx, 0, 6 * sizeof(DGE_INDEX_BUFFER) );
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

	glBindBuffer(GL_ARRAY_BUFFER, m_Vtx);
	glVertexPointer(3, GL_FLOAT, 0, 0);
	glEnableClientState(GL_VERTEX_ARRAY);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Idx[0]);	glColor4f(1,0,0,1);		glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Idx[1]);	glColor4f(0,1,0,1);		glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Idx[2]);	glColor4f(0,0,1,1);		glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Idx[3]);	glColor4f(1,1,0,1);		glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Idx[4]);	glColor4f(0,1,1,1);		glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Idx[5]);	glColor4f(1,0,1,1);		glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, 0);

	glDisableClientState(GL_VERTEX_ARRAY);

	glColor4f(1,1,1,1);


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	m_pDev->SetTransformIdentity(DGE_TS_WORLD);


	m_pDev->EndScene();

	return DGE_OK;
}


