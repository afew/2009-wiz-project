
// Implementation of the CMain class.
//
////////////////////////////////////////////////////////////////////////////////


#include "_StdAfx.h"


#define MEDIA_DIR	"../../media/"


//Structure to hold the optimized m_pMesh data for rendering
struct Mesh_t
{
	INT		nIdx;
	INT		nVtx;
	WORD*	pIdx;
	VtxNUV1* pVtx;
};


//GSD file header
struct GSDHeader
{
  char	id[32];
  char	version[16];
  int	nSubObj;
};



// Desc: Load GSD Mesh
// Original: http://www.nehe.net
// 
INT LoadMeshFromFile(Mesh_t** pOut, const char *filename)
{
	char	Name[128]={0};
	char	Parent[128]={0};

	UINT	nIdx;
	UINT	nVtx;

	UINT*	pIdx;

	FLOAT*	pPos;
	FLOAT*	pNor;
	FLOAT*	pTex;

	UINT	i;

	GSDHeader header;
	Mesh_t*	pMesh = NULL;
	FILE*	fp = NULL;


	fp = fopen(filename,"rb");
	if(!fp)
		return -1;

	fread(&header,sizeof(GSDHeader),1,fp); 

	if(header.nSubObj< 1)
	{
		fclose(fp);
		return -1;
	}

	fread(Name	,sizeof(char ), 128, fp); //read the object name
	fread(Parent,sizeof(char ), 128, fp); //Read the name of the parent object (useful for hierarchies)
	fread(&nIdx	,sizeof(UINT),    1, fp); //read the number of vertex indices
	fread(&nVtx	,sizeof(UINT),    1, fp); //read the number of vertices


	pIdx =		  (UINT*)malloc(sizeof(UINT)*(nIdx));
	fread(pIdx, sizeof(UINT), nIdx,fp);


	pPos = (FLOAT *)malloc(sizeof(FLOAT)* 3 * nVtx);	fread(pPos, sizeof(FLOAT), 3 * nVtx, fp);
	pTex = (FLOAT *)malloc(sizeof(FLOAT)* 2 * nVtx);	fread(pTex, sizeof(FLOAT), 2 * nVtx, fp);
	pNor = (FLOAT *)malloc(sizeof(FLOAT)* 3 * nVtx);	fread(pNor, sizeof(FLOAT), 3 * nVtx, fp);

	fclose(fp);


	// Convert data y <--> z
	for(i=0;i<nVtx; ++i)
	{
		FLOAT	t;

		t = pPos[i*3+1];
		pPos[i*3+1] = pPos[i*3+2];
		pPos[i*3+2] = t;

		t = pNor[i*3+1];
		pNor[i*3+1] = pNor[i*3+2];
		pNor[i*3+2] = t;
	}


	// Convert index 1 <--> 2
	for(i=0;i<nIdx; i +=3)
	{
		INT t;

		t = pIdx[i+1];
		pIdx[i+1] = pIdx[i+2];
		pIdx[i+2] = t;
	}



	// Create Mesh_t Instance
	pMesh= (Mesh_t*)malloc(sizeof(Mesh_t));
	pMesh->pIdx = (WORD*)malloc(sizeof(WORD)*(nIdx));			// Create Index Buffer of Mesh
	pMesh->pVtx = (VtxNUV1*)malloc( sizeof(VtxNUV1) * nVtx);	// Create Vertex Buffer of Mesh



	// Convert data to Short and Copy
	for(i=0;i<nIdx; ++i)
		pMesh->pIdx[i] = (WORD)pIdx[i];


	// Setup Data of Mesh_t Instance
	pMesh->nIdx= nIdx;
	pMesh->nVtx= nVtx;
	

	// Fill Vertex Data
	for(i=0; i<nVtx; ++i)
	{
		pMesh->pVtx[i].p.x = pPos[i*3+0];
		pMesh->pVtx[i].p.y = pPos[i*3+1];
		pMesh->pVtx[i].p.z = pPos[i*3+2];

		pMesh->pVtx[i].n.x = pNor[i*3+0];
		pMesh->pVtx[i].n.y = pNor[i*3+1];
		pMesh->pVtx[i].n.z = pNor[i*3+2];

		pMesh->pVtx[i].t.x = pTex[i*2+0];
		pMesh->pVtx[i].t.y = pTex[i*2+1];
	}

	// Clear Temporary Buffer
	free(pPos);
	free(pNor);
	free(pTex);
	free(pIdx);

	// Finally, Copy Mesh Pointer to Output Data
	*pOut = pMesh;

	return DGE_OK;
}


void DrawMesh(PDGE_DEVICE pDev, Mesh_t* pMesh)
{
	pDev->SetFVF(VtxNUV1::FVF);
	pDev->SetTexture(0, NULL);
	
	pDev->DrawIndexedPrimitiveUPf(DGE_PT_TRIANGLE_LIST, pMesh->nIdx, pMesh->pIdx, pMesh->pVtx, sizeof(VtxNUV1));

}



Mesh_t* m_pMesh = NULL;


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


	DGXVECTOR3	vcEye ( 40.0F,-40.0F,  20.F);
	DGXVECTOR3	vcLook( 0.0F,  0.0F,   5.F);
	DGXVECTOR3	vcUp  ( 0.0F,  0.0F,  1.0F);

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



	//Load our scene file
	if(DGE_FAILED(LoadMeshFromFile(&m_pMesh, MEDIA_DIR"data/scene.gsd")))
		return DGE_OK;

	return DGE_OK;
}

INT	CMain::Destroy()
{
	 //delete m_pMesh data
	free(m_pMesh->pVtx);
	free(m_pMesh->pIdx);
	free(m_pMesh);

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


	// Camera Translation
	if(pKey[DGEKEY_UP])
		m_pCam->MoveForward(+speed);

	if(pKey[DGEKEY_DOWN])
		m_pCam->MoveForward(-speed);

	if(pKey[DGEKEY_LEFT])
		m_pCam->MoveSideward(-speed);

	if(pKey[DGEKEY_RIGHT])
		m_pCam->MoveSideward(+speed);


	// Camera Rotation
	FLOAT fAngle_degree = 2.0f;

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


	DWORD clearColor = DGXCOLOR(0, 0.7F, 0.9F, 0);
	m_pDev->SetRenderState(DGE_RS_CLEAR_COLOR, clearColor);

	m_pDev->Clear(DGE_CLEAR_COLOR_BUFFER | DGE_CLEAR_DEPTH_BUFFER);

	m_pCam->SetTransformPrj();
	m_pCam->SetTransformViw();


	m_pDev->SetRenderState(DGE_RS_SHADE_MODEL, DGE_ST_SMOOTH);		// Set Shade Model
	m_pDev->SetRenderState(DGE_RS_DEPTH_TEST, DGE_ST_ENABLE);		// Enable Depth Test
	m_pDev->SetRenderState(DGE_RS_CULL_FACE, DGE_ST_ENABLE);		// Enable Culling


//	m_pXYZ->Render();
//	m_pGrid->Render();


	m_pDev->SetRenderState(DGE_RS_LIGHTING, DGE_ST_ENABLE);			// Enable lighting computations
	m_pDev->SetRenderState(DGE_RS_FOG, DGE_ST_ENABLE);				// Enable Fog



	// Fog Setting
	TDGE_FOG fog;
	{
		fog.FogColor= DGXCOLOR(0, 0.7F, 0.9F, 0);
		fog.FogMode	= DGE_ST_FOG_LINEAR;
		fog.FogBegin= 20.F;
		fog.FogEnd	= 120.F;
	};

	m_pDev->SetRenderState(DGE_RS_FOG_DATA, &fog);




	// Lighting Position
	static FLOAT Rot=0;
	DGXVECTOR4	vcLight(0, 0, 10, 1);
	FLOAT	fR = 80;

	Rot += 0.02f;
	vcLight.x = fR*(FLOAT)cos(Rot);
	vcLight.y = fR*(FLOAT)sin(Rot);


	// Lighting Setting
	TDGE_LIGHT lgt0;
	memset(&lgt0, 0, sizeof(TDGE_LIGHT));
	{
		lgt0.Amb = DGXCOLOR(0.0F, 0.0F, 1.0F, 1.F);
		lgt0.Dif = DGXCOLOR(0.0F, 0.0F, 1.0F, 1.F);
		lgt0.Pos = vcLight;
	};

	m_pDev->SetRenderState(DGE_RS_LIGHT0_DATA, &lgt0);
	m_pDev->SetRenderState(DGE_RS_LIGHT0, DGE_ST_ENABLE);			// Enable Light0


	vcLight.x = fR*(FLOAT)cos(Rot + DGXToRadian(120));
	vcLight.y = fR*(FLOAT)sin(Rot + DGXToRadian(120));
	TDGE_LIGHT lgt1;
	memset(&lgt1, 0, sizeof(TDGE_LIGHT));
	{
		lgt1.Amb = DGXCOLOR(1.0F, 0.0F, 0.0F, 1.F);
		lgt1.Dif = DGXCOLOR(1.0F, 0.0F, 0.0F, 1.F);
		lgt1.Pos = vcLight;
	};

	m_pDev->SetRenderState(DGE_RS_LIGHT1_DATA, &lgt1);
	m_pDev->SetRenderState(DGE_RS_LIGHT1, DGE_ST_ENABLE);			// Enable Light1
	

	vcLight.x = fR*(FLOAT)cos(Rot + DGXToRadian(240));
	vcLight.y = fR*(FLOAT)sin(Rot + DGXToRadian(240));
	TDGE_LIGHT lgt2;
	memset(&lgt2, 0, sizeof(TDGE_LIGHT));
	{
		lgt2.Amb = DGXCOLOR(0.0F, 1.0F, 0.0F, 1.F);
		lgt2.Dif = DGXCOLOR(0.0F, 1.0F, 0.0F, 1.F);
		lgt2.Pos = vcLight;
	};

	m_pDev->SetRenderState(DGE_RS_LIGHT2_DATA, &lgt2);
	m_pDev->SetRenderState(DGE_RS_LIGHT2, DGE_ST_ENABLE);			// Enable Light2
	

	
	
	// Material Setting
	TDGE_MATERIAL mtl;
	memset(&mtl, 0, sizeof(TDGE_MATERIAL));
	{
		mtl.Amb = DGXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		mtl.Dif = DGXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	};

	m_pDev->SetRenderState(DGE_RS_MATERIAL_DATA, &mtl);


	// Set Model position
	static FLOAT fRot = 0;
	fRot +=0.4f;

	DGXMATRIX	mtRot;
	mtRot.SetupRotationZ( DGXToRadian(fRot));

	m_pDev->SetTransform(DGE_TS_WORLD, &mtRot);

	DrawMesh(m_pDev, m_pMesh);
	m_pDev->SetTransformIdentity(DGE_TS_WORLD);


	m_pDev->SetRenderState(DGE_RS_LIGHTING, DGE_ST_DISABLE);			// Disable lighting computations
	m_pDev->SetRenderState(DGE_RS_FOG, DGE_ST_DISABLE);					// Disable Fog

	m_pDev->SetRenderState(DGE_RS_DEPTH_TEST, DGE_ST_DISABLE);
	m_pDev->SetRenderState(DGE_RS_CULL_FACE, DGE_ST_DISABLE);
	m_pDev->SetRenderState(DGE_RS_LIGHTING, DGE_ST_DISABLE);





	m_pDev->EndScene();

	return DGE_OK;
}


