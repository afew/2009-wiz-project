// Implementation of the CMain class.
//
////////////////////////////////////////////////////////////////////////////////


#include "_StdAfx.h"


#define MEDIA_DIR	"../../media/"




//Structure to hold the optimized mesh data for rendering
struct FixedMesh
{
  GLshort indexCounter;
  GLshort vertexCounter;

  GLshort*	Indices;
  GLfloat*	Geometry;
  GLfloat*	Normals;
  GLfloat*	TexCoord;
};

//Structure to hold the data readed from the file
struct GenericObjectData
{
  char Name[128];
  char ParentName[128];
  unsigned int *Indices;
  GLfloat *Geometry;
  GLfloat *Normals;
  GLfloat *TexCoord;
  unsigned long iC;
  unsigned long vC;
};

//GSD file header
struct GSDHeader
{
  char id[32];
  char version[16];
  int numberOfSubObjects;
};


FixedMesh* LoadMeshFromFile(const char *filename)
{
	GenericObjectData o;
	FixedMesh* mesh= (FixedMesh*)malloc(sizeof(struct FixedMesh));
	unsigned int i;

	struct GSDHeader header;
	FILE *meshFile = fopen(filename,"rb");

	if(!meshFile)
		return NULL;

	/*The header holds a brief description of the file, the version number, and the number of meshes
	that are stored in the file. This type of files are thought for static meshes only*/
	fread(&header,sizeof(struct GSDHeader),1,meshFile); 

	//Check if there is at least one object
	if(header.numberOfSubObjects < 1)
		return NULL;

	// we only will use the first object, so we won't iterate over the others, if they exist
	fread(o.Name,sizeof(char)*128,1,meshFile); //read the object name
	fread(o.ParentName,sizeof(char)*128,1,meshFile); //Read the name of the parent object (useful for hierarchies)
	fread(&o.iC,sizeof(unsigned long),1,meshFile); //read the number of vertex indices
	fread(&o.vC,sizeof(unsigned long),1,meshFile); //read the number of vertices

	//allocate enough space for the indices and the GLshort version of them
	o.Indices = (unsigned int *)malloc(sizeof(unsigned int)*(o.iC));
	mesh->Indices = (short *)malloc(sizeof(GLshort)*(o.iC));
	fread(o.Indices, sizeof(unsigned int) * o.iC,1,meshFile); // read all indices

	//allocate enough space for the vertices and the GLfloat version of them
	o.Geometry = (GLfloat *)malloc(sizeof(GLfloat)*(o.vC * 3));
	mesh->Geometry = (GLfloat *)malloc(sizeof(GLfloat)*(o.vC * 3));
	fread(o.Geometry,o.vC * 3 * sizeof(GLfloat),1,meshFile); //read all vertices (1 vertex = 3 floats)

	//allocate enough space for the texture coordinates and the GLfloat version of them
	o.TexCoord = (GLfloat *)malloc(sizeof(GLfloat)*(o.vC * 2));
	mesh->TexCoord = (GLfloat *)malloc(sizeof(GLfloat)*(o.vC * 2));
	fread(o.TexCoord,o.vC * 2 * sizeof(GLfloat),1,meshFile);//read all texcoords (1 tex coord = 2 floats)

	//allocate enough space for the normals and the GLfloat version of them
	o.Normals=(GLfloat *)malloc(sizeof(GLfloat)*(o.vC * 3));
	mesh->Normals = (GLfloat *)malloc(sizeof(GLfloat)*(o.vC * 3));
	fread(o.Normals,o.vC * 3* sizeof(GLfloat),1,meshFile);//read all normals (1 normal = 3 floats)
	fclose(meshFile); //Do not need the file opened anymore

	// Convert data to optimized data types for OpenGL ES (GLfloat and GLshort)
	for(i=0;i<o.vC * 3;i++)
	{
		mesh->Geometry[i]= (o.Geometry[i]);
		mesh->Normals[i] = (o.Normals[i]);
	}

	for(i=0;i<o.vC * 2;i++)
		mesh->TexCoord[i] = (o.TexCoord[i]);

	for(i=0;i<o.iC;i++)
		mesh->Indices[i] = (GLshort)o.Indices[i];

	mesh->indexCounter = (GLshort)o.iC;
	mesh->vertexCounter= (GLshort)o.vC;

	//delete original values, we will use only the optimized ones
	free(o.Indices);
	free(o.Geometry);
	free(o.Normals);
	free(o.TexCoord);

	return mesh;
}



struct FixedMesh *mesh = NULL;


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


	DGXVECTOR3	vcEye (-4.70869F, 51.3707F, -71.1396F);
	DGXVECTOR3	vcLook(-2.91194F,-35.7724F, -28.4792F);
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




	//Load our scene file
	mesh = LoadMeshFromFile(MEDIA_DIR"data/scene.gsd");

	return DGE_OK;
}

INT	CMain::Destroy()
{
	 //delete mesh data
	free(mesh->Geometry);
	free(mesh->Indices);
	free(mesh->Normals);
	free(mesh->TexCoord);
	free(mesh);

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
	GLfloat fAngle_degree = 2.0f;

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


	m_pDev->SetRenderState(DGE_RS_SHADE_MODEL, DGE_ST_SMOOTH);
	m_pDev->SetRenderState(DGE_RS_DEPTH_TEST, DGE_ST_ENABLE);
	m_pDev->SetRenderState(DGE_RS_CULL_FACE, DGE_ST_ENABLE);



	//fog color
	DGXCOLOR fogColor(0, 0.7F, 0.9F, 0);

	glFogfv(GL_FOG_COLOR, (const GLfloat*)&fogColor);
	glFogf(GL_FOG_MODE, GL_LINEAR);
	glFogf(GL_FOG_START, 20);
	glFogf(GL_FOG_END,  100);

	glDisable(GL_FOG);


	// Lighting Position
	static GLfloat Rot=0;
	DGXVECTOR4	vcLight(0, 10, 0, 0);
	DGXCOLOR	amb(0.0F, 1.0F, 1.0F, 1.F);
	DGXCOLOR	dif(1.f, 1.0f, 0.f, 1);

	Rot += 0.04f;
	vcLight.x = 30*(GLfloat)sin(Rot);
	vcLight.z = 30*(GLfloat)cos(Rot);


	glLightfv(GL_LIGHT0, GL_AMBIENT,  (const GLfloat*)&amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE,  (const GLfloat*)&dif);
	glLightfv(GL_LIGHT0, GL_POSITION, (const GLfloat*)&vcLight);
	glEnable(GL_LIGHT0);						//Enable Light0 (switch on it)

	glEnable(GL_LIGHTING);						//Enable lighting computations

	
	
	// Set default OpenGL ES material settings
	DGXCOLOR mat_amb(0.2f, 0.2f, 0.2f, 0.2f);
	DGXCOLOR mat_dif(0.8f, 0.8f, 0.8f, 0.8f);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, (const GLfloat*)&mat_amb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, (const GLfloat*)&mat_dif);
	


	// Set Model position
	static GLfloat rotation = 0;
	rotation +=0.4f;

	glTranslatef(0, -5, -40);
	glRotatef(20, 1, 0, 0);
	glRotatef(rotation, 0, 1, 0);

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, mesh->Geometry);

	/* Normals are needed for the lighting computations */
	glEnableClientState(GL_NORMAL_ARRAY);
	glNormalPointer(GL_FLOAT, 0, mesh->Normals);

	glDrawElements(GL_TRIANGLES,mesh->indexCounter,GL_UNSIGNED_SHORT,mesh->Indices);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);



	m_pDev->EndScene();

	return DGE_OK;
}



