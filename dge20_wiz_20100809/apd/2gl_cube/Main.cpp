// Implementation of the CMain class.
//
////////////////////////////////////////////////////////////////////////////////


#include "_StdAfx.h"


CMain::CMain()
{
	m_pInput	= NULL;
	m_pCam		= NULL;
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




	static float vertices[] =
	{
		-10,-10,-10,  +10,-10,-10, +10,+10,-10, -10,+10,-10,
		-10,-10,+10,  +10,-10,+10, +10,+10,+10, -10,+10,+10
	};

	m_pCube = vertices;

	for(int i=0; i< sizeof(vertices)/sizeof(vertices[0]); ++i)
		vertices[i] = vertices[i];


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



	//      7 +----------+ 6
	//       /|         /|
	//      / |        / |
	//     /  |       /  |
	//  3 +----------+ 2 |
	//    |   |      |   |
	//    | 4 +------|---+ 5
	//    |  /       |  /
	//    | /        | /
	//    |/         |/
	//  0 +----------+ 1 

	static WORD front[]  = {2,1,3,0};
	static WORD back[]   = {5,6,4,7}; //back face
	static WORD top[]    = {6,2,7,3}; //top face
	static WORD bottom[] = {1,5,0,4}; //bottom face
	static WORD left[]   = {3,0,7,4}; //left face
	static WORD right[]  = {6,5,2,1}; //right face

	

	//Enable the vertices array
	glEnableClientState(GL_VERTEX_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, m_pCube);
	
	glColor4f(1,0,0,1);	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, front);
	glColor4f(0,1,0,1);	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, back);
	glColor4f(0,0,1,1);	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, top);
	glColor4f(1,1,0,1);	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, bottom);
	glColor4f(0,1,1,1);	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, left);
	glColor4f(1,0,1,1);	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, right);

	glDisableClientState(GL_VERTEX_ARRAY);

	glColor4f(1,1,1,1);

	m_pDev->SetTransformIdentity(DGE_TS_WORLD);


	m_pDev->EndScene();

	return DGE_OK;
}


