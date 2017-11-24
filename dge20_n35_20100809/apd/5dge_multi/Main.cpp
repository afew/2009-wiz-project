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


	DGXVECTOR3	vcEye (0,-3.5F,  0);
	DGXVECTOR3	vcLook(0,  0,  0);
	DGXVECTOR3	vcUp  (0,  0,  1);

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
	speed *=40.0F;


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


	DWORD	dColor = 0xFF006699;
	m_pDev->SetRenderState(DGE_RS_CLEAR_COLOR, dColor);
	m_pDev->Clear(DGE_CLEAR_COLOR_BUFFER | DGE_CLEAR_DEPTH_BUFFER);
//
	m_pCam->SetTransformPrj();
	m_pCam->SetTransformViw();


//	m_pDev->SetRenderState(DGE_RS_CULL_FACE, DGE_ST_DISABLE);

//	m_pXYZ->Render();
//	m_pGrid->Render();



	// Color
	DGXCOLOR	pColor[3][3];

	pColor[0][0] = DGXCOLOR(1, 0, 0, 1);
	pColor[0][1] = DGXCOLOR(0, 1, 0, 1);
	pColor[0][2] = DGXCOLOR(0, 0, 1, 1);
	pColor[1][0] = DGXCOLOR(0, 1, 0, 1);
	pColor[1][1] = DGXCOLOR(1, 1, 0, 1);
	pColor[1][2] = DGXCOLOR(0, 1, 1, 1);
	pColor[2][0] = DGXCOLOR(1, 1, 1, 1);
	pColor[2][1] = DGXCOLOR(1, 1, 1, 1);
	pColor[2][2] = DGXCOLOR(1, 0, 1, 1);


	INT	nTexOp[3][3][2]=
	{
		{	{ DGE_TS_MODULATE, DGE_TS_SUBTRACT},	{ DGE_TS_DECAL, DGE_TS_MODULATE},		{ DGE_TS_MODULATE, DGE_TS_MODULATE},	},
		{	{ DGE_TS_ADD, DGE_TS_DECAL},			{ DGE_TS_SUBTRACT, DGE_TS_MODULATE},	{ DGE_TS_ADD_SIGNED, DGE_TS_ADD}		},
		{	{ DGE_TS_DECAL, DGE_TS_DECAL},			{ DGE_TS_MODULATE, DGE_TS_DECAL},		{ DGE_TS_DECAL, DGE_TS_ADD},			},
	};

	// Set Vertex Data
	VtxUV1		pVtx[4];

	pVtx[0].t = DGXVECTOR2(0.0F, 0.0F);
	pVtx[1].t = DGXVECTOR2(1.0F, 0.0F);
	pVtx[2].t = DGXVECTOR2(1.0F, 1.0F);
	pVtx[3].t = DGXVECTOR2(0.0F, 1.0F);

	pVtx[0].p = DGXVECTOR3(-1.0F, 0.0F, -1.0F);
	pVtx[1].p = DGXVECTOR3( 1.0F, 0.0F, -1.0F);
	pVtx[2].p = DGXVECTOR3( 1.0F, 0.0F,  1.0F);
	pVtx[3].p = DGXVECTOR3(-1.0F, 0.0F,  1.0F);


	m_pDev->SetTextureAddressS (0, DGE_TS_REPEAT);
	m_pDev->SetTextureAddressT (0, DGE_TS_REPEAT);
	m_pDev->SetTextureFilterMin(0, DGE_TS_LINEAR);
	m_pDev->SetTextureFilterMag(0, DGE_TS_LINEAR);

	m_pDev->SetTextureAddressS (1, DGE_TS_REPEAT);
	m_pDev->SetTextureAddressT (1, DGE_TS_REPEAT);
	m_pDev->SetTextureFilterMin(1, DGE_TS_LINEAR);
	m_pDev->SetTextureFilterMag(1, DGE_TS_LINEAR);

	m_pDev->SetFVF(VtxUV1::FVF);


	for(int k=0; k<3; ++k)
	{
		for(int i=0; i<3; ++i)
		{
			float	x = (i - 1.5f)*1.333F;
			float	z = (k - 1.5f)*1.0F;


			if(2 == k && 0 == i)
			{
				m_pDev->SetTexture(0, m_pTex0);
				m_pDev->SetTexture(1, NULL);
			}
			else if(2 == k && 1 == i)
			{
				m_pDev->SetTexture(0, m_pTex1);
				m_pDev->SetTexture(1, NULL);
			}
			else
			{
				m_pDev->SetTexture(0, m_pTex0);
				m_pDev->SetTexture(1, m_pTex1);
			}

			pVtx[0].p = DGXVECTOR3(        x, 0.0F, z    );
			pVtx[1].p = DGXVECTOR3( x+1.333F, 0.0F, z    );
			pVtx[2].p = DGXVECTOR3( x+1.333F, 0.0F, z+1.F);
			pVtx[3].p = DGXVECTOR3(        x, 0.0F, z+1.F);
			
			m_pDev->SetTextureStageOp (0, nTexOp[k][i][0]);
			m_pDev->SetTextureStageOp (0, nTexOp[k][i][1]);

			m_pDev->SetColor((FLOAT*)&pColor[k][i]);
			m_pDev->DrawPrimitiveUPf(DGE_PT_TRIANGLE_FAN, 0, 4, pVtx, sizeof(VtxUV1) );
		}
	}



	m_pDev->SetTexture(0, NULL);
	m_pDev->SetTexture(1, NULL);

	m_pDev->SetColor(1,1,1,1);



	m_pDev->EndScene();

	return DGE_OK;
}




