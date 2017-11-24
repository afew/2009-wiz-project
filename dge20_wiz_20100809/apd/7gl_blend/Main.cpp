// Implementation of the CMain class.
//
////////////////////////////////////////////////////////////////////////////////


#include "_StdAfx.h"


#define MEDIA_DIR	"../../media/"


#define NUM 50


/* Twinkling stars */
INT  twinkle=DGE_FALSE;




/* Define the star structure */
typedef struct
{
	int r, g, b;   /* Stars Color */
	GLfloat dist;  /* Stars Distance From Center */
	GLfloat angle; /* Stars Current Angle */
} star;

star stars[NUM];       /* Make an array of size 'NUM' of stars */

GLfloat zoom=-15.0f;   /* Viewing Distance Away From Stars */
GLfloat tilt=90.0f;    /* Tilt The View */

GLuint loop;           /* General Loop Variable */



CMain::CMain()
{
	m_pInput	= NULL;
	m_pCam		= NULL;
	m_pXYZ		= NULL;
	m_pGrid		= NULL;
	
	m_pTex		= NULL;
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
	
	
	DGXVECTOR3	vcEye (0, -130,  0);
	DGXVECTOR3	vcLook(0,    0,  0);
	DGXVECTOR3	vcUp  (0,    0,  1);

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
	
	
	
	hr = DGE_CreateTexture(NULL, &m_pTex, (void*)MEDIA_DIR"tex/star.bmp");
	if(DGE_FAILED(hr))
		return DGE_ECANNOTALLOCATED;
	


	/* Create A Loop That Goes Through All The Stars */
	for (loop=0; loop<NUM; loop++)
	{
		/* Start All The Stars At Angle Zero */
		stars[loop].angle=0.0f;
		
		/* Calculate Distance From The Center */
		stars[loop].dist=((float)loop/NUM)*5.0f;
		/* Give star[loop] A Random Red Intensity */
		stars[loop].r=rand() % 256;
		/* Give star[loop] A Random Green Intensity */
		stars[loop].g=rand() % 256;
		/* Give star[loop] A Random Blue Intensity */
		stars[loop].b=rand() % 256;
	}

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
	m_pDev->SetRenderState(DGE_RS_DEPTH_TEST, DGE_ST_DISABLE);
	
//	m_pXYZ->Render();
//	m_pGrid->Render();
	
	
	
	UINT	nTex0 = m_pTex->GetId();
	
	
	glLoadIdentity();


	/* Really Nice Perspective Calculations */
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	
	/* Enable Blending */
	glEnable(GL_BLEND);
	
	/* Set The Blending Function For Translucency */
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	

	static float spin=0;
	
	GLfloat texcoords[4][2];
	GLfloat vertices[4][3];
	GLubyte indices[4]={1, 0, 2, 3}; /* QUAD to TRIANGLE_STRIP conversion; */
	
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices);

	glActiveTexture(GL_TEXTURE0);
	//glClientActiveTexture(GL_TEXTURE0);
	glBindTexture (GL_TEXTURE_2D, nTex0);
	glEnable(GL_TEXTURE_2D);
	
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, 0, texcoords);
	


	/* Loop Through All The Stars */
	for (loop=0; loop<NUM; loop++)
	{
		/* Reset The View Before We Draw Each Star */
		glLoadIdentity();
		/* Zoom Into The Screen (Using The Value In 'zoom') */
		glTranslatef(0.0f, 0.0f, zoom);
		
		/* Tilt The View (Using The Value In 'tilt') */
		glRotatef(tilt, 1.0f, 0.0f, 0.0f);
		/* Rotate To The Current Stars Angle */
		glRotatef(stars[loop].angle, 0.0f, 1.0f, 0.0f);
		
		/* Move Forward On The X Plane */
		glTranslatef(stars[loop].dist, 0.0f, 0.0f);
		
		/* Cancel The Current Stars Angle */
		glRotatef(-stars[loop].angle, 0.0f, 1.0f, 0.0f);
		/* Cancel The Screen Tilt */
		glRotatef(-tilt, 1.0f, 0.0f, 0.0f);
		
		/* Twinkling Stars Enabled */
		if (twinkle)
		{
			/* Assign A Color Using Bytes */
			glColor4f((GLfloat)stars[(NUM-loop)-1].r/255.0f,
				(GLfloat)stars[(NUM-loop)-1].g/255.0f,
				(GLfloat)stars[(NUM-loop)-1].b/255.0f, 1.0f);
			
			/* Fill texture and vertex arrays */
			texcoords[0][0]=0.0f; texcoords[0][1]=0.0f;
			vertices[0][0]=-1.0f; vertices[0][1]=-1.0f; vertices[0][2]=0.0f;
			texcoords[1][0]=1.0f; texcoords[1][1]=0.0f;
			vertices[1][0]=1.0f; vertices[1][1]=-1.0f; vertices[1][2]=0.0f;
			texcoords[2][0]=1.0f; texcoords[2][1]=1.0f;
			vertices[2][0]=1.0f; vertices[2][1]=1.0f; vertices[2][2]=0.0f;
			texcoords[3][0]=0.0f; texcoords[3][1]=1.0f;
			vertices[3][0]=-1.0f; vertices[3][1]=1.0f; vertices[3][2]=0.0f;
			
			/* Draw one textured plane using two stripped triangles */
			glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, indices);
			
		}
		
		/* Rotate The Star On The Z Axis */
		glRotatef(spin, 0.0f, 0.0f, 1.0f);
		
		/* Assign A Color Using Bytes */
		glColor4f((GLfloat)stars[loop].r/255.0f,
			(GLfloat)stars[loop].g/255.0f,
			(GLfloat)stars[loop].b/255.0f, 1.0f);
		
		/* Fill texture and vertex arrays */
		texcoords[0][0]=0.0f; texcoords[0][1]=0.0f;
		vertices[0][0]=-1.0f; vertices[0][1]=-1.0f; vertices[0][2]=0.0f;
		texcoords[1][0]=1.0f; texcoords[1][1]=0.0f;
		vertices[1][0]=1.0f; vertices[1][1]=-1.0f; vertices[1][2]=0.0f;
		texcoords[2][0]=1.0f; texcoords[2][1]=1.0f;
		vertices[2][0]=1.0f; vertices[2][1]=1.0f; vertices[2][2]=0.0f;
		texcoords[3][0]=0.0f; texcoords[3][1]=1.0f;
		vertices[3][0]=-1.0f; vertices[3][1]=1.0f; vertices[3][2]=0.0f;
		
		/* Draw one textured plane using two stripped triangles */
		glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, indices);
		
		/* Used To Spin The Stars */
		spin+=0.01f;
		/* Changes The Angle Of A Star */
		stars[loop].angle+=(float)loop/NUM;
		/* Changes The Distance Of A Star */
		stars[loop].dist-=0.01f;
		
		/* Is The Star In The Middle Yet */
		if (stars[loop].dist<0.0f)
		{
			/* Move The Star 5 Units From The Center */
			stars[loop].dist+=5.0f;
			/* Give It A New Red Value */
			stars[loop].r=rand()%256;
			/* Give It A New Green Value */
			stars[loop].g=rand()%256;
			/* Give It A New Blue Value */
			stars[loop].b=rand()%256;
		}
	}
	
	/* Disable texcoords and vertices arrays */
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	


	glActiveTexture(GL_TEXTURE0);
	glBindTexture (GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
	
	
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);



	glDisable(GL_BLEND);

	
	m_pDev->SetRenderState(DGE_RS_CULL_FACE, DGE_ST_ENABLE);
	m_pDev->SetRenderState(DGE_RS_DEPTH_TEST, DGE_ST_ENABLE);
	


	m_pDev->EndScene();
	
	return DGE_OK;
}








