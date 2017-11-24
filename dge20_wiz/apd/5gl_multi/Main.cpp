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

	m_pTex0		= NULL;
	m_pTex1		= NULL;
}


INT	CMain::Init()
{
	INT	hr = 0;

	// Input 持失
	if(DGE_FAILED(DGX_CreateInput(NULL, &m_pInput, m_pDev, m_hWnd)))
		return DGE_EFAIL;


	// Camera 持失
	if(DGE_FAILED(DGX_CreateCamera(NULL, &m_pCam, m_pDev)))
		return DGE_EFAIL;


//	DGXVECTOR3	vcEye (0, -130,  0);
//	DGXVECTOR3	vcLook(0,    0,  0);
//	DGXVECTOR3	vcUp  (0,    0,  1);
//
//	m_pCam->SetupParamView(&vcEye, &vcLook, &vcUp);
//
//	FLOAT	fFov = DGXToRadian(45.0F);
//	FLOAT	fScnW= FLOAT(m_nScnW);
//	FLOAT	fScnH= FLOAT(m_nScnH);
//	FLOAT	fNear= 1.0F;
//	FLOAT	fFar = 5000.0F;
//
//	m_pCam->SetupParamProj(fFov, fScnW, fScnH, fNear, fFar);





	if(DGE_FAILED(DGX_CreateEntity("Axis", &m_pXYZ, m_pDev)))
		return DGE_EFAIL;


	if(DGE_FAILED(DGX_CreateEntity("Grid", &m_pGrid, m_pDev)))
		return DGE_EFAIL;



	hr = DGE_CreateTexture(NULL, &m_pTex0, (void*)MEDIA_DIR"tex/stones.png");
	if(DGE_FAILED(hr))
		return DGE_ECANNOTALLOCATED;


	hr = DGE_CreateTexture(NULL, &m_pTex1, (void*)MEDIA_DIR"tex/env0.png");
	if(DGE_FAILED(hr))
		return DGE_ECANNOTALLOCATED;



	return DGE_OK;
}

INT	CMain::Destroy()
{
	DGE_DestroyTexture(&m_pTex0);
	DGE_DestroyTexture(&m_pTex1);

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





	return DGE_OK;
}


INT	CMain::Render()
{
	m_pDev->BeginScene();

	m_pDev->Clear(DGE_CLEAR_COLOR_BUFFER | DGE_CLEAR_DEPTH_BUFFER);

	m_pCam->SetTransformPrj();
	m_pCam->SetTransformViw();


	m_pDev->SetRenderState(DGE_RS_CULL_FACE, DGE_ST_DISABLE);

//	m_pXYZ->Render();
//	m_pGrid->Render();



	UINT	nTex0 = m_pTex0->GetId();
	UINT	nTex1 = m_pTex1->GetId();


	
	// Setup Vertex Data
	DGXVECTOR3	Pos[4];
	DGXVECTOR2	Tex[4];
	
	Tex[0] = DGXVECTOR2(0.0F, 0.0F);
	Tex[1] = DGXVECTOR2(1.0F, 0.0F);
	Tex[2] = DGXVECTOR2(1.0F, 1.0F);
	Tex[3] = DGXVECTOR2(0.0F, 1.0F);


	{
		Pos[0] = DGXVECTOR3(-1.0F, 0.0F, +0.0F);
		Pos[1] = DGXVECTOR3( 0.0F, 0.0F, +0.0F);
		Pos[2] = DGXVECTOR3( 0.0F, 0.0F, +1.0F);
		Pos[3] = DGXVECTOR3(-1.0F, 0.0F, +1.0F);

		glColor4f(0,1,1,1);
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glVertexPointer(3, DGE_FMT_FLOAT, 0, Pos);


		glTexEnvx(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

		glActiveTexture(GL_TEXTURE0);
		glClientActiveTexture(GL_TEXTURE0);
		glBindTexture (GL_TEXTURE_2D, nTex0);
		glEnable(GL_TEXTURE_2D);
		glTexCoordPointer(2, DGE_FMT_FLOAT, 0, Tex);


		glTexEnvx(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

		glTexParameterx(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterx(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameterx(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterx(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


		glTexEnvx(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);


		glActiveTexture(GL_TEXTURE1);
		glClientActiveTexture(GL_TEXTURE1);
		glBindTexture (GL_TEXTURE_2D, nTex1);
		glEnable(GL_TEXTURE_2D);
		glTexCoordPointer(2, DGE_FMT_FLOAT, 0, Tex);

		glTexEnvx(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

		glTexParameterx(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterx(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameterx(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterx(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glDrawArrays(DGE_PT_TRIANGLE_FAN, 0, 4);

		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}


	{
		Pos[0] = DGXVECTOR3( 0.0F, 0.0F, +0.0F);
		Pos[1] = DGXVECTOR3( 1.0F, 0.0F, +0.0F);
		Pos[2] = DGXVECTOR3( 1.0F, 0.0F, +1.0F);
		Pos[3] = DGXVECTOR3( 0.0F, 0.0F, +1.0F);

		glColor4f(1,0,1,1);
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glVertexPointer(3, DGE_FMT_FLOAT, 0, Pos);

		glTexEnvx(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_ADD);

		glActiveTexture(GL_TEXTURE0);
		glClientActiveTexture(GL_TEXTURE0);
		glBindTexture (GL_TEXTURE_2D, nTex0);
		glEnable(GL_TEXTURE_2D);
		glTexCoordPointer(2, DGE_FMT_FLOAT, 0, Tex);


		glTexEnvx(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_ADD);


		glTexParameterx(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterx(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameterx(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterx(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glActiveTexture(GL_TEXTURE1);
		glClientActiveTexture(GL_TEXTURE1);
		glBindTexture (GL_TEXTURE_2D, nTex1);
		glEnable(GL_TEXTURE_2D);
		glTexCoordPointer(2, DGE_FMT_FLOAT, 0, Tex);


		glTexEnvx(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_ADD);


		glTexParameterx(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterx(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameterx(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterx(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glDrawArrays(DGE_PT_TRIANGLE_FAN, 0, 4);

	}


	{
		Pos[0] = DGXVECTOR3(-1.0F, 0.0F, -1.0F);
		Pos[1] = DGXVECTOR3( 0.0F, 0.0F, -1.0F);
		Pos[2] = DGXVECTOR3( 0.0F, 0.0F, +0.0F);
		Pos[3] = DGXVECTOR3(-1.0F, 0.0F, +0.0F);

		glColor4f(0.6F,0.6F,0.6F,1);
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glVertexPointer(3, DGE_FMT_FLOAT, 0, Pos);


		glTexEnvx(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);


		glActiveTexture(GL_TEXTURE0);
		glClientActiveTexture(GL_TEXTURE0);
		glBindTexture (GL_TEXTURE_2D, nTex0);
		glEnable(GL_TEXTURE_2D);
		glTexCoordPointer(2, DGE_FMT_FLOAT, 0, Tex);


		glTexEnvx(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_ADD);


		glTexParameterx(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterx(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameterx(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterx(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		
		glTexEnvx(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_SUBTRACT);



		glActiveTexture(GL_TEXTURE1);
		glClientActiveTexture(GL_TEXTURE1);
		glBindTexture (GL_TEXTURE_2D, nTex1);
		glEnable(GL_TEXTURE_2D);
		glTexCoordPointer(2, DGE_FMT_FLOAT, 0, Tex);

		glTexParameterx(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterx(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameterx(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterx(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glDrawArrays(DGE_PT_TRIANGLE_FAN, 0, 4);
	}

	{
		Pos[0] = DGXVECTOR3( 0.0F, 0.0F, -1.0F);
		Pos[1] = DGXVECTOR3( 1.0F, 0.0F, -1.0F);
		Pos[2] = DGXVECTOR3( 1.0F, 0.0F, +0.0F);
		Pos[3] = DGXVECTOR3( 0.0F, 0.0F, +0.0F);

		glColor4f(0.3F,0.3F,0.3F,1);
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glVertexPointer(3, DGE_FMT_FLOAT, 0, Pos);

		glTexEnvx(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_ADD_SIGNED);


		glActiveTexture(GL_TEXTURE0);
		glClientActiveTexture(GL_TEXTURE0);
		glBindTexture (GL_TEXTURE_2D, nTex0);
		glEnable(GL_TEXTURE_2D);
		glTexCoordPointer(2, DGE_FMT_FLOAT, 0, Tex);

		glTexParameterx(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterx(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameterx(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterx(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexEnvx(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_INTERPOLATE);


		glActiveTexture(GL_TEXTURE1);
		glClientActiveTexture(GL_TEXTURE1);
		glBindTexture (GL_TEXTURE_2D, nTex1);
		glEnable(GL_TEXTURE_2D);
		glTexCoordPointer(2, DGE_FMT_FLOAT, 0, Tex);

		glTexEnvx(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_INTERPOLATE);

		glTexParameterx(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterx(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameterx(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterx(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glDrawArrays(DGE_PT_TRIANGLE_FAN, 0, 4);
	}


	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);


	glColor4f(1,1,1,1);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture (GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
	

	glActiveTexture(GL_TEXTURE0);
	glBindTexture (GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);



	m_pDev->EndScene();


	return DGE_OK;
}




