// Implementation of the IDGE_Device.
//
////////////////////////////////////////////////////////////////////////////////


#if defined(_WIN32) || defined(WIN32)
	#if _MSC_VER >= 1200
	#pragma warning(disable: 4996)
	#endif

	#include <windows.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <gles/gl.h>
#include <gles/egl.h>


#include <DGE_Math.h>
#include <DGE_System.h>
#include "DGE_Base.h"


class CDGE_Device : public IDGE_Device
{
// System
protected:
	DGE_HWND	m_hWnd		;		// Window Handle
	DGE_HANDLE	m_pEgDsp	;		// Egl Display
	DGE_HANDLE	m_pEgSrf	;		// Egl Surface
	DGE_HANDLE	m_pEgCtx	;		// Egl Context

// Application
protected:
	DGE_HANDLE	m_psMain	;		// Main Application Pointer
	DGE_HANDLE	m_psSpt		;		// Sprite
	DGE_HANDLE	m_psInput	;		// Input
	DGE_HANDLE	m_psNet		;		// Network
	DGE_HANDLE	m_psUsrD1	;		// User Data1
	DGE_HANDLE	m_psUsrD2	;		// User Data2
	DGE_HANDLE	m_psUsrD3	;		// User Data3
	DGE_HANDLE	m_psUsrD4	;		// User Data4

// 3D Vertex Processing PipeLine
protected:
	static INT			m_ScnW		;		// Screen Width
	static INT			m_ScnH		;		// Screen Height
	static DGXCOLOR		m_dColor	;		// Clear Color

	static INT			m_dFVF		;		// Flexible Vertex Format
	static INT			m_iFVF		;		// Flexible Index Format

	static INT			m_BlndS		;		// Source Blend Function
	static INT			m_BlndD		;		// Dest Blend Function

	static DGXMATRIX	m_mtWld		;		// world Matrix
	static DGXMATRIX	m_mtViw		;		// View Matrix
	static DGXMATRIX	m_mtPrj		;		// Projection Matrix


// 3D Pixel Processing PipeLine
public:
	static	PDGE_TEXTURE m_pTex[4]	;		// Current Texture[4]
	static	INT			m_TssAdS[4]	;		// Texture Address mode for the S coordinate. default: GL_REPEAT
	static	INT			m_TssAdT[4]	;		// Texture Address mode for the T coordinate. default: GL_REPEAT
	static	INT			m_TssMin[4]	;		// Minification Filter. default: GL_LINEAR
	static	INT			m_TssMag[4]	;		// Magnification Filter. default: GL_LINEAR
	static	INT			m_TssOp [4]	;		// MultiTexture Blending Mode

public:
	CDGE_Device();
	virtual ~CDGE_Device();

	// 3D PipeLine Interface
	virtual	INT		SetTransform(INT nTransform, const DGE_HANDLE Val);
	virtual	INT		GetTransform(INT nTransform, DGE_HANDLE Val);
	virtual	INT		SetTransformIdentity(INT nTransform);

	virtual	INT		BeginScene();								// Prepare Rendering
	virtual	INT		EndScene();									// Post Rendering
	
	virtual	INT		SetRenderState(INT nState, INT v);			// Redering Machine State
	virtual	INT		SetRenderState(INT nState, void* v);		// Redering Machine State for Pointer
	virtual	INT		SetStatusEnable(INT nStatus);				// Wrapping glEnable()
	virtual	INT		SetStatusDisable(INT nStatus);				// Wrapping glDisable()


	// Sampler and Multi-texture State
	virtual INT		SetTextureEnv(INT v1, FLOAT v2);			// glTexEnvf(GL_TEXTURE_ENV, ..., ...)

	virtual INT		SetTextureAddressS (INT nState, INT v) { if(nState & 0xFFFFFFFC) return DGE_EFAIL; m_TssAdS[nState] = v; return DGE_OK;	}	// nState & 0xFFFFFFFC: 0~3만 사용
	virtual INT		SetTextureAddressT (INT nState, INT v) { if(nState & 0xFFFFFFFC) return DGE_EFAIL; m_TssAdT[nState] = v; return DGE_OK;	}
	virtual INT		SetTextureFilterMin(INT nState, INT v) { if(nState & 0xFFFFFFFC) return DGE_EFAIL; m_TssMin[nState] = v; return DGE_OK;	}
	virtual INT		SetTextureFilterMag(INT nState, INT v) { if(nState & 0xFFFFFFFC) return DGE_EFAIL; m_TssMag[nState] = v; return DGE_OK;	}
	virtual INT		SetTextureStageOp  (INT nState, INT v) { if(nState & 0xFFFFFFFC) return DGE_EFAIL; m_TssOp [nState] = v; return DGE_OK;	}


	// Vertex Format
	virtual	INT		SetFVF(INT nFVF);

	// Set Texture
	virtual INT		SetTexture(INT nState, PDGE_TEXTURE pTex);


	// Color Setting...
	virtual	INT		SetColor(FLOAT r, FLOAT g, FLOAT b, FLOAT a=1.f);	// glColor4f()
	virtual	INT		SetColor(FLOAT* v);									// glColor4v()


	// Rendering Primitive for Vertex Buffer Object
	virtual INT		SetStreamSource(PDGE_VB);
	virtual INT		SetIndices(PDGE_IB);
	virtual INT		DrawPrimitivef();
	virtual INT		DrawIndexedPrimitivef(INT nMode, INT nCount);


	// Rendering Primitive for User Memory Pointer
	virtual INT		DrawPrimitiveUPf(INT nMode, INT First, INT nVtx, const void* pVtx, INT nStride);
	virtual INT		DrawIndexedPrimitiveUPf(INT nMode, INT nIdx, const void *pIdx, const void* pVtx, INT nStride);

	virtual INT		DrawPrimitiveUPi(INT nMode, INT First, INT nVtx, const void* pVtx, INT nStride);
	virtual INT		DrawIndexedPrimitiveUPi(INT nMode, INT nIdx, const void *pIdx, const void* pVtx, INT nStride);


	virtual INT		Clear(DWORD nMode);
	virtual INT		Present(DGE_HANDLE =0, DGE_HANDLE  =0, DGE_HANDLE =0, DGE_HANDLE =0);


	// Application Data Interface.
	virtual DGE_HANDLE	GetMainApp	()	{	return m_psMain		;	}	// Main Application Pointer
	virtual DGE_HANDLE	GetSprite	()	{	return m_psSpt		;	}	// 2D Sprite Pointer
	virtual DGE_HANDLE	GetInput	()	{	return m_psInput	;	}	// Input Pointer
	virtual DGE_HANDLE	GetNetwork	()	{	return m_psNet		;	}	// Network Pointer
	virtual DGE_HANDLE	GetUserData1()	{	return m_psUsrD1	;	}	// User Data Pointer 1
	virtual DGE_HANDLE	GetUserData2()	{	return m_psUsrD2	;	}	// User Data Pointer 2
	virtual DGE_HANDLE	GetUserData3()	{	return m_psUsrD3	;	}	// User Data Pointer 3
	virtual DGE_HANDLE	GetUserData4()	{	return m_psUsrD4	;	}	// User Data Pointer 4

	virtual void	SetMainApp	(DGE_HANDLE	p){	m_psMain	= p;	}
	virtual void	SetSprite	(DGE_HANDLE	p){	m_psSpt		= p;	}
	virtual void	SetInput	(DGE_HANDLE	p){	m_psInput	= p;	}
	virtual void	SetNetwork	(DGE_HANDLE	p){	m_psNet		= p;	}
	virtual void	SetUserData1(DGE_HANDLE	p){	m_psUsrD1	= p;	}
	virtual void	SetUserData2(DGE_HANDLE	p){	m_psUsrD2	= p;	}
	virtual void	SetUserData3(DGE_HANDLE	p){	m_psUsrD3	= p;	}
	virtual void	SetUserData4(DGE_HANDLE	p){	m_psUsrD4	= p;	}


	INT		Create(DGE_HANDLE p1=NULL, DGE_HANDLE p2=NULL, DGE_HANDLE p3=NULL, DGE_HANDLE p4=NULL);
	void	Destroy();
};



INT			CDGE_Device::m_ScnW		;		// Screen Width
INT			CDGE_Device::m_ScnH		;		// Screen Height
DGXCOLOR	CDGE_Device::m_dColor	;		// Clear Color

INT			CDGE_Device::m_dFVF		;		// Flexible Vertex Format
INT			CDGE_Device::m_iFVF		;		// Flexible Index Format

INT			CDGE_Device::m_BlndS= GL_SRC_ALPHA			;		// Source Blend Function
INT			CDGE_Device::m_BlndD= GL_ONE_MINUS_SRC_ALPHA;		// Dest Blend Function


DGXMATRIX	CDGE_Device::m_mtWld	;		// world Matrix
DGXMATRIX	CDGE_Device::m_mtViw	;		// View Matrix
DGXMATRIX	CDGE_Device::m_mtPrj	;		// Projection Matrix

PDGE_TEXTURE CDGE_Device::m_pTex [4] = {0};	// Current Texture
INT			CDGE_Device::m_TssOp [4] = {GL_MODULATE,GL_MODULATE,GL_MODULATE,GL_MODULATE};
INT			CDGE_Device::m_TssMin[4] = {GL_LINEAR, GL_LINEAR, GL_LINEAR, GL_LINEAR};
INT			CDGE_Device::m_TssMag[4] = {GL_LINEAR, GL_LINEAR, GL_LINEAR, GL_LINEAR};
INT			CDGE_Device::m_TssAdS[4] = {GL_REPEAT, GL_REPEAT, GL_REPEAT, GL_REPEAT};
INT			CDGE_Device::m_TssAdT[4] = {GL_REPEAT, GL_REPEAT, GL_REPEAT, GL_REPEAT};

CDGE_Device::CDGE_Device()
{
	m_hWnd		= NULL;
	m_pEgDsp	= NULL;
	m_pEgSrf	= NULL;
	m_pEgCtx	= NULL;
	
	m_psMain	= NULL;
	m_psSpt		= NULL;
	m_psInput	= NULL;
	m_psNet		= NULL;
	m_psUsrD1	= NULL;
	m_psUsrD2	= NULL;
	m_psUsrD3	= NULL;
	m_psUsrD4	= NULL;

	m_dColor	= (DWORD)(0xFF001122);
	m_mtWld.Identity();
	m_mtViw.Identity();
	m_mtPrj.Identity();

	m_dFVF		= DGE_FVF_XYZ;
	m_dFVF		= DGE_FMT_INDEX16;
}


CDGE_Device::~CDGE_Device()
{
	Destroy();
}


void CDGE_Device::Destroy()
{
	eglMakeCurrent(m_pEgDsp, 0, 0, 0);
	eglDestroyContext(m_pEgDsp, m_pEgCtx);
	eglDestroySurface(m_pEgDsp, m_pEgSrf);

#if defined(_WIN32) || defined(WIN32)
	eglTerminate((NativeDisplayType)m_hWnd, (EGLDisplay)m_pEgDsp);
#else
	eglTerminate(m_pEgDsp);
#endif

	m_hWnd		= NULL;
	m_pEgDsp	= NULL;
	m_pEgSrf	= NULL;
	m_pEgCtx	= NULL;
}


// Setup EGL
#if defined(_WIN32) || defined(WIN32)


extern INT DGE_glInit();

INT CDGE_Device::Create(DGE_HANDLE p1, DGE_HANDLE p2, DGE_HANDLE p3, DGE_HANDLE p4)
{
	if(NULL == p1)
		return DGE_EINVALIDATE_CALL;

	m_hWnd = (DGE_HWND)p1;


	// Setup Display
	// HDC를 반환 받는다.
	m_pEgDsp = eglGetDisplay((NativeDisplayType)m_hWnd);
	if(NULL == m_pEgDsp)
	{
		printf("Err: %d, %s \t", __LINE__, __FILE__);
		printf("eglGetDisplay() Failed\n");
		return DGE_ECANNOTALLOCATED;
	}



	// m_pEgSrf 는 HDC와 같음
	if(NULL == eglCreateWindowSurface(m_pEgDsp, NULL, m_hWnd, 0) )
	{
		printf("Err: %d, %s \t", __LINE__, __FILE__);
		printf("eglCreateWindowSurface() Failed\n");
		return DGE_ECANNOTALLOCATED;
	}


	printf("eglCreateWindowSurface() Success\n");


	m_pEgCtx = eglCreateContext(m_pEgDsp, NULL, NULL, NULL);

	if(NULL == m_pEgCtx)
	{
		printf("Err: %d, %s \t", __LINE__, __FILE__);
		printf("eglCreateContext() Failed\n");
		return DGE_ECANNOTALLOCATED;
	}

	printf("eglCreateContext() Success\n");


	// Make Current
	if (!eglMakeCurrent(m_pEgDsp, m_pEgSrf, m_pEgSrf, m_pEgCtx))
	{
		printf("Err: %d, %s \t", __LINE__, __FILE__);
		printf("eglMakeCurrent() Failed\n");
		return DGE_ECANNOTALLOCATED;
	}


	printf("eglMakeCurrent() Success\n");


	if(0>DGE_glInit())
	{
		printf("Initialize Device Failed.\n");
		return DGE_ECANNOTALLOCATED;
	}



	if (!eglSwapInterval(m_pEgDsp, 0)) 
	{
		printf("Err: %d, %s \t", __LINE__, __FILE__);
		printf("eglSwapInterval() Failed\n");
		return DGE_ECANNOTALLOCATED;
	}


	DGE_WindowSize(&m_ScnW, &m_ScnH);								// Viewport를 위한 Screen Width, Height 설정

	glClearColor(m_dColor.r, m_dColor.g, m_dColor.b, m_dColor.a);	// Clear Color로 동작 확인
	glShadeModel(GL_SMOOTH);
//	glTextureDither(0);


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	eglSwapBuffers(m_pEgDsp, m_pEgSrf);
	glFlush();


	printf("Complete EGL Create\n");

	return DGE_OK;
}

#else

INT CDGE_Device::Create(DGE_HANDLE p1, DGE_HANDLE p2, DGE_HANDLE p3, DGE_HANDLE p4)
{
	if(NULL == p1)
		return DGE_EINVALIDATE_CALL;

	m_hWnd = (DGE_HWND)p1;

	if(NULL == m_pEgDsp)
		m_pEgDsp = eglGetDisplay(EGL_DEFAULT_DISPLAY);

	if(NULL == m_pEgDsp)
	{
		printf("Err: %d, %s \t", __LINE__, __FILE__);
		printf("eglGetDisplay() Failed\n");
		return DGE_ECANNOTALLOCATED;
	}



	struct _Tconfig_att { EGLint a; EGLint b;	};
	const _Tconfig_att config_attrib[] =
	{
		{	EGL_SURFACE_TYPE,   EGL_WINDOW_BIT, },
		{	EGL_NONE,			EGL_NONE,		},
	};


	const	int MAX_CONFIG = 10;
	int			match;
	EGLConfig	eglConf[MAX_CONFIG]={0};

//	EGLint i = 0;
//	eglConf[i++] = EGL_RED_SIZE;
//	eglConf[i++] = 5;
//	eglConf[i++] = EGL_GREEN_SIZE;
//	eglConf[i++] = 6;
//	eglConf[i++] = EGL_BLUE_SIZE;
//	eglConf[i++] = 5;
//	eglConf[i++] = EGL_ALPHA_SIZE;
//	eglConf[i++] = 0;
//	eglConf[i++] = EGL_SURFACE_TYPE;
//	eglConf[i++] = EGL_WINDOW_BIT;
//	eglConf[i++] = EGL_NONE;

	EGLint ver_maj;
	EGLint ver_min;

	if (!eglInitialize(m_pEgDsp, &ver_maj, &ver_min))
	{
		printf("Err: %d, %s \t", __LINE__, __FILE__);
		printf("eglInitialize() Failed\n");
		return DGE_ECANNOTALLOCATED;
	}

	printf("eglInitialize() Success\n");


	if (!eglChooseConfig(m_pEgDsp, (const EGLint*)config_attrib, &eglConf[0], MAX_CONFIG, &match))
	{
		printf("Err: %d, %s \t", __LINE__, __FILE__);
		printf("eglChooseConfig() Failed\n");
		return DGE_ECANNOTALLOCATED;
	}

	printf("eglChooseConfig() Success\n");

	// No Match
	if(1>match)
	{
		printf("Err: %d, %s \t", __LINE__, __FILE__);
		printf("eglChooseConfig() Failed\n");
		return DGE_ECANNOTALLOCATED;
	}


	m_pEgSrf = eglCreateWindowSurface(m_pEgDsp, eglConf[0], m_hWnd, (const EGLint*)config_attrib);
	if(NULL == m_pEgSrf)
	{
		m_pEgSrf = eglCreateWindowSurface(m_pEgDsp, eglConf[0], m_hWnd, 0);
		if(NULL == m_pEgSrf)
		{
			printf("Err: %d, %s \t", __LINE__, __FILE__);
			printf("eglCreateWindowSurface() Failed\n");
			return DGE_ECANNOTALLOCATED;
		}
	}


	printf("eglCreateWindowSurface() Success\n");


	m_pEgCtx = eglCreateContext(m_pEgDsp, eglConf[0], EGL_NO_CONTEXT, (const EGLint*)config_attrib);

	if(NULL == m_pEgCtx)
	{
		m_pEgCtx = eglCreateContext(m_pEgDsp, eglConf[0], NULL, NULL);
		if(NULL == m_pEgCtx)
		{
			printf("Err: %d, %s \t", __LINE__, __FILE__);
			printf("eglCreateContext() Failed\n");
			return DGE_ECANNOTALLOCATED;
		}
	}
	

	printf("eglCreateContext() Success\n");


	// Make Current
	if (!eglMakeCurrent(m_pEgDsp, m_pEgSrf, m_pEgSrf, m_pEgCtx))
	{
		printf("Err: %d, %s \t", __LINE__, __FILE__);
		printf("eglMakeCurrent() Failed\n");
		return DGE_ECANNOTALLOCATED;
	}


	printf("eglMakeCurrent() Success\n");


//	printf("-------------------------------------\n");
//	printf("Window Handle: 0x%x\n", (void*)m_hWnd	);
//	printf("Window DC	 : 0x%x\n", (void*)m_hDC	);
//	printf("Egl Display  : 0x%x\n", (void*)m_pEgDsp	);
//	printf("Egl Surface  : 0x%x\n", (void*)m_pEgSrf	);
//	printf("Egl Context  : 0x%x\n", (void*)m_pEgCtx	);
//	printf("-------------------------------------\n");

	DGE_WindowSize(&m_ScnW, &m_ScnH);								// Viewport를 위한 Screen Width, Height 설정

	glClearColor(m_dColor.r, m_dColor.g, m_dColor.b, m_dColor.a);	// Clear Color로 동작 확인
	glShadeModel(GL_SMOOTH);
//	glTextureDither(0);


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	eglSwapBuffers(m_pEgDsp, m_pEgSrf);
	glFlush();


	printf("Complete EGL Create\n");

	return DGE_OK;
}


#endif












INT CDGE_Device::SetTransform(INT nTransform, const DGE_HANDLE Val)
{
	if		(DGE_TS_WORLD== nTransform)	memcpy(&m_mtWld, Val, sizeof(DGXMATRIX));
	else if	(DGE_TS_PROJ == nTransform)	memcpy(&m_mtPrj, Val, sizeof(DGXMATRIX));
	else if	(DGE_TS_VIEW == nTransform)	memcpy(&m_mtViw, Val, sizeof(DGXMATRIX));
	else	return DGE_EFAIL;

	
	if(DGE_TS_WORLD == nTransform || DGE_TS_VIEW == nTransform)
	{
		DGXMATRIX	mtWldViw = m_mtWld*m_mtViw;		// OpenGL은 열 중심 행렬이지만 처리는 DX처럼 왼쪽에서 오른쪽으로 월드 * 뷰 * 투영으로 변환을 처리

		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixf((FLOAT*)&mtWldViw);
	}

	if(DGE_TS_PROJ == nTransform)
	{
		glViewport(0, 0, m_ScnW, m_ScnH);
		glMatrixMode(GL_PROJECTION);
		glLoadMatrixf((FLOAT*)&m_mtPrj);
	}

	return DGE_OK;
}

INT CDGE_Device::GetTransform(INT nTransform, DGE_HANDLE Val)
{
	if		(DGE_TS_WORLD== nTransform)	memcpy(Val, &m_mtWld, sizeof(DGXMATRIX));
	else if	(DGE_TS_PROJ == nTransform)	memcpy(Val, &m_mtPrj, sizeof(DGXMATRIX));
	else if	(DGE_TS_VIEW == nTransform)	memcpy(Val, &m_mtViw, sizeof(DGXMATRIX));
	else	return DGE_EFAIL;


	return DGE_OK;
}


INT CDGE_Device::SetTransformIdentity(INT nTransform)
{
	static FLOAT I[16]={1,0,0,0,
						0,1,0,0,
						0,0,1,0,
						0,0,0,1};

	if		(DGE_TS_WORLD== nTransform)	memcpy(&m_mtWld, I, sizeof m_mtWld);
	else if	(DGE_TS_VIEW == nTransform)	memcpy(&m_mtViw, I, sizeof m_mtViw);
	else if	(DGE_TS_PROJ == nTransform)	memcpy(&m_mtPrj, I, sizeof m_mtPrj);
	else	return DGE_EFAIL;

	return DGE_OK;
}





INT CDGE_Device::SetTextureEnv(INT v1, FLOAT v2)
{
	glTexEnvf(GL_TEXTURE_ENV, v1, v2);

	return DGE_OK;
}











INT CDGE_Device::SetFVF(INT nFVF)
{
	if(!(DGE_FVF_XYZ & nFVF))
		return DGE_EFAIL;

	m_dFVF = nFVF;

	if(0 == m_dFVF)
	{
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}

	return DGE_OK;
}


INT CDGE_Device::SetTexture(INT nState, PDGE_TEXTURE pTex)
{
	if(nState & 0xFFFFFFFC)
		return DGE_EFAIL;

	m_pTex[nState] = pTex;

	if(NULL == pTex)
	{
		glActiveTexture(GL_TEXTURE0 + nState);
		glBindTexture(GL_TEXTURE_2D, 0);
		glDisable(GL_TEXTURE_2D);

//		return DGE_OK;
	}

	return DGE_OK;

//	return m_pTex->BindTexture(m_TexOp, m_TexFilterMin, m_TexFilterMag, m_TexFilterAddS, m_TexFilterAddT);
}


INT CDGE_Device::SetColor(FLOAT r, FLOAT g, FLOAT b, FLOAT a)
{
	::glColor4f(r, g, b, a);
	return DGE_OK;
}


INT CDGE_Device::SetColor(FLOAT* v)
{
	::glColor4f(v[0], v[1], v[2], v[3]);
	return DGE_OK;
}



INT CDGE_Device::BeginScene()
{
	return DGE_OK;
}

INT	CDGE_Device::EndScene()
{
	return DGE_OK;
}



INT CDGE_Device::SetRenderState(INT ns, INT v)
{
	if(DGE_RS_SHADE_MODEL == ns)
	{
		glShadeModel(v);
	}

	else if(DGE_RS_DEPTH_TEST == ns)
	{
		if(v)
			glEnable(ns);

		else
			glDisable(ns);
	}

	else if(DGE_RS_CULL_MODE == ns)
	{
		glFrontFace(v);
	}

	else if(DGE_RS_CULL_FACE == ns)
	{
		if(DGE_ST_BACK == v || DGE_ST_FRONT == v)
			glCullFace(v);

		else if(DGE_ST_ENABLE == v)
			glEnable(ns);

		else if(DGE_ST_DISABLE== v)
			glDisable(ns);
	}

	else if(DGE_RS_CLEAR_COLOR == ns)
	{
		DWORD dColor = v;
		CDGE_Device::m_dColor = dColor;
		glClearColor(m_dColor.r, m_dColor.g, m_dColor.b, m_dColor.a);
	}

	else if(DGE_RS_BLEND_SRC == ns)
	{
		m_BlndS = v;
		glBlendFunc( m_BlndS, m_BlndD);
	}

	else if(DGE_RS_BLEND_DEST == ns)
	{
		m_BlndD = v;
		glBlendFunc( m_BlndS, m_BlndD);
	}


	else if(DGE_RS_BLEND == ns)
	{
		if(v)
			glEnable(ns);

		else
			glDisable(ns);
	}

	else if(DGE_RS_FOG == ns)
	{
		if(v)
			glEnable(ns);
		else
			glDisable(ns);
	}

	else if(DGE_RS_LIGHTING == ns)
	{
		if(v)
			glEnable(ns);
		else
			glDisable(ns);
	}

	else if(DGE_RS_LIGHT0 <= ns && ns <= DGE_RS_LIGHT7)
	{
		if(v)
			glEnable(ns);
		else
			glDisable(ns);
	}


	return DGE_OK;
}


INT CDGE_Device::SetRenderState(INT ns, void* v)
{
	if(DGE_RS_CLEAR_COLOR == ns)
	{
		DGXCOLOR* dColor = (DGXCOLOR*)v;
		CDGE_Device::m_dColor = *dColor;
		glClearColor(m_dColor.r, m_dColor.g, m_dColor.b, m_dColor.a);
	}

	else if(DGE_RS_FOG_DATA == ns)
	{
		TDGE_FOG*  p = (TDGE_FOG*)v;

		glFogfv(GL_FOG_COLOR, (const GLfloat *)&p->FogColor);
		glFogf(GL_FOG_MODE,	 p->FogMode);
		glFogf(GL_FOG_START, p->FogBegin);
		glFogf(GL_FOG_END,	 p->FogEnd);
	}

	else if(DGE_RS_LIGHT0_DATA <= ns && ns <= DGE_RS_LIGHT7_DATA )
	{
		TDGE_LIGHT*  p = (TDGE_LIGHT*)v;
		INT nLgt = ns - DGE_RS_LIGHT0_DATA + GL_LIGHT0;

		if(0.0F < p->Amb.a)	glLightfv(nLgt, GL_AMBIENT				, (const GLfloat *)&p->Amb);
		if(0.0F < p->Dif.a)	glLightfv(nLgt, GL_DIFFUSE				, (const GLfloat *)&p->Dif);
		if(0.0F < p->Spc.a)	glLightfv(nLgt, GL_SPECULAR				, (const GLfloat *)&p->Spc);
		if(0.0F !=p->Pos.w)	glLightfv(nLgt, GL_POSITION				, (const GLfloat *)&p->Pos);
		if(0.0F !=p->Dir.w)	glLightfv(nLgt, GL_SPOT_DIRECTION		, (const GLfloat *)&p->Dir);
		if(0.0F !=p->Spe)	glLightf (nLgt, GL_SPOT_EXPONENT		,                   p->Spe);
		if(0.0F !=p->Cut)	glLightf (nLgt, GL_SPOT_CUTOFF			,                   p->Cut);
		if(0.0F !=p->Att0)	glLightf (nLgt, GL_CONSTANT_ATTENUATION	,                   p->Att0);
		if(0.0F !=p->Att1)	glLightf (nLgt, GL_LINEAR_ATTENUATION	,                   p->Att1);
		if(0.0F !=p->Att2)	glLightf (nLgt, GL_QUADRATIC_ATTENUATION,                   p->Att2);
	}

	else if(DGE_RS_MATERIAL_DATA == ns)
	{
		TDGE_MATERIAL*  p = (TDGE_MATERIAL*)v;
		if(0.0F < p->Amb.a)	glMaterialfv(p->Fce, GL_AMBIENT , (const GLfloat *)&p->Amb);
		if(0.0F < p->Dif.a)	glMaterialfv(p->Fce, GL_DIFFUSE , (const GLfloat *)&p->Dif);
		if(0.0F < p->Spc.a)	glMaterialfv(p->Fce, GL_SPECULAR, (const GLfloat *)&p->Spc);
		if(0.0F < p->Spc.a)	glMaterialfv(p->Fce, GL_EMISSION, (const GLfloat *)&p->Ems);
		if(0.0F !=p->Shp)	glMaterialf (p->Fce, GL_SHININESS,                  p->Shp);
	}

	return DGE_OK;
}


INT CDGE_Device::SetStatusEnable(INT nStatus)
{
	glEnable(nStatus);
	return DGE_OK;
}


INT CDGE_Device::SetStatusDisable(INT nStatus)
{
	glDisable(nStatus);
	return DGE_OK;
}




// Rendering Primitive for Vertex Buffer Object
INT CDGE_Device::SetStreamSource(PDGE_VB pVB)
{
	if(NULL == pVB)
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		return DGE_OK;
	}

	return pVB->Bind(TRUE);
}

INT CDGE_Device::SetIndices(PDGE_IB pIB)
{
	if(NULL == pIB)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		m_iFVF	= DGE_FMT_INDEX16;
		return DGE_OK;
	}


	m_iFVF	= pIB->GetFmt();

	return pIB->Bind(TRUE);
}


INT CDGE_Device::DrawPrimitivef()
{
	return DGE_OK;
}


INT CDGE_Device::DrawIndexedPrimitivef(INT nMode, INT nCount)
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, DGE_FMT_FLOAT, 0, 0);

	glDrawElements(nMode, nCount, m_iFVF, 0);

	return DGE_OK;
}





INT CDGE_Device::DrawPrimitiveUPf(INT nMode, INT First, INT nVtx, const void* pVtx, INT nStride)
{
	char*	p = (char*)pVtx;
	INT		dFVF = m_dFVF;

	UINT	nTex0 = 0;
	UINT	nTex1 = 0;

	if(!pVtx)
		return DGE_EFAIL;

	if(!(DGE_FVF_XYZ & dFVF))	// 위치가 없으면 실패
		return DGE_EFAIL;


	if(m_pTex[0]) nTex0 = m_pTex[0]->GetId();
	if(m_pTex[1]) nTex1 = m_pTex[1]->GetId();


	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);


	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer  (3, DGE_FMT_FLOAT,	nStride, p); p += sizeof(DGE_FLOAT3);


	if( DGE_FVF_NORMAL & m_dFVF){	glEnableClientState(GL_NORMAL_ARRAY);		glNormalPointer  (   DGE_FMT_FLOAT,	nStride, p); p += sizeof(DGE_FLOAT3);	}
	if( DGE_FVF_DIFFUSE & dFVF)	{	glEnableClientState(GL_COLOR_ARRAY);		glColorPointer   (4, DGE_FMT_UBYTE,	nStride, p); p += sizeof(DGE_COLORB);	}


	if( DGE_FVF_TEX1 & dFVF)
	{
		if(nTex0)
		{
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, nTex0);
			glEnable(GL_TEXTURE_2D);

			glTexCoordPointer(2, DGE_FMT_FLOAT,	nStride, p);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_TssAdS[0]);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_TssAdT[0]);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_TssMin[0]);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_TssMag[0]);

			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, (GLfloat)m_TssOp[0]);

		}

		if(nTex0 && nTex1)
		{
			glActiveTexture(GL_TEXTURE1);
			glClientActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, nTex1);
			glEnable(GL_TEXTURE_2D);

			glTexCoordPointer(2, DGE_FMT_FLOAT,	nStride, p);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_TssAdS[1]);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_TssAdT[1]);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_TssMin[1]);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_TssMag[1]);

			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, (GLfloat)m_TssOp[1]);
		}
	}



	glDrawArrays(nMode, First, nVtx);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	return DGE_OK;
}




INT CDGE_Device::DrawIndexedPrimitiveUPf(INT nMode, INT nIdx, const void *pIdx, const void* pVtx, INT nStride)
{
	char*	p = (char*)pVtx;
	INT		dFVF = m_dFVF;

	UINT	nTex0 = 0;
	UINT	nTex1 = 0;

	if(!pVtx)
		return DGE_EFAIL;

	if(!(DGE_FVF_XYZ & dFVF))	// 위치가 없으면 실패
		return DGE_EFAIL;


	if(m_pTex[0]) nTex0 = m_pTex[0]->GetId();
	if(m_pTex[1]) nTex1 = m_pTex[1]->GetId();


	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);


	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer  (3, DGE_FMT_FLOAT,	nStride, p); p += sizeof(DGE_FLOAT3);



	if( DGE_FVF_NORMAL & dFVF)	{	glEnableClientState(GL_NORMAL_ARRAY);		glNormalPointer  (   DGE_FMT_FLOAT,	nStride, p); p += sizeof(DGE_FLOAT3);	}
	if( DGE_FVF_DIFFUSE & dFVF)	{	glEnableClientState(GL_COLOR_ARRAY);		glColorPointer   (4, DGE_FMT_UBYTE, nStride, p); p += sizeof(DGE_COLORB);	}


	if( DGE_FVF_TEX1 & dFVF)
	{
		if(nTex0)
		{
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, nTex0);
			glEnable(GL_TEXTURE_2D);

			glTexCoordPointer(2, DGE_FMT_FLOAT,	nStride, p);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_TssAdS[0]);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_TssAdT[0]);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_TssMin[0]);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_TssMag[0]);

			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, (GLfloat)m_TssOp[0]);
		}

		if(nTex0 && nTex1)
		{
			glActiveTexture(GL_TEXTURE1);
			glClientActiveTexture(GL_TEXTURE1);
			glBindTexture (GL_TEXTURE_2D, nTex1);
			glEnable(GL_TEXTURE_2D);

			glTexCoordPointer(2, DGE_FMT_FLOAT,	nStride, p);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_TssAdS[1]);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_TssAdT[1]);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_TssMin[1]);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_TssMag[1]);

			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, (GLfloat)m_TssOp[1]);

		}
	}


	glDrawElements(nMode, nIdx, DGE_FMT_INDEX16, pIdx);


	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);


	return DGE_OK;
}


INT CDGE_Device::DrawPrimitiveUPi(INT nMode, INT First, INT nVtx, const void* pVtx, INT nStride)
{
	char*	p = (char*)pVtx;
	INT		dFVF = m_dFVF;

	UINT	nTex0 = 0;
	UINT	nTex1 = 0;

	if(!pVtx)
		return DGE_EFAIL;

	if(!(DGE_FVF_XYZ & dFVF))	// 위치가 없으면 실패
		return DGE_EFAIL;


	if(m_pTex[0]) nTex0 = m_pTex[0]->GetId();
	if(m_pTex[1]) nTex1 = m_pTex[1]->GetId();


	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);


	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer  (3, DGE_FMT_FIXED,	nStride, p); p += sizeof(DGE_INT3  );



	if( DGE_FVF_NORMAL & dFVF)	{	glEnableClientState(GL_NORMAL_ARRAY);		glNormalPointer  (   DGE_FMT_FIXED,	nStride, p); p += sizeof(DGE_INT3  );	}
	if( DGE_FVF_DIFFUSE & dFVF)	{	glEnableClientState(GL_COLOR_ARRAY);		glColorPointer   (4, DGE_FMT_UBYTE, nStride, p); p += sizeof(DGE_COLORB);	}


	if( DGE_FVF_TEX1 & dFVF)
	{
		if(nTex0)
		{
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, nTex0);
			glEnable(GL_TEXTURE_2D);

			glTexCoordPointer(2, DGE_FMT_FIXED,	nStride, p);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_TssAdS[0]);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_TssAdT[0]);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_TssMin[0]);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_TssMag[0]);

			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, (GLfloat)m_TssOp[0]);

		}

		if(nTex0 && nTex1)
		{
			glActiveTexture(GL_TEXTURE1);
			glClientActiveTexture(GL_TEXTURE1);
			glBindTexture (GL_TEXTURE_2D, nTex1);
			glEnable(GL_TEXTURE_2D);

			glTexCoordPointer(2, DGE_FMT_FIXED,	nStride, p);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_TssAdS[1]);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_TssAdT[1]);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_TssMin[1]);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_TssMag[1]);

			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, (GLfloat)m_TssOp[1]);

		}
	}


	glDrawArrays(nMode, First, nVtx);


	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	return DGE_OK;
}




INT CDGE_Device::DrawIndexedPrimitiveUPi(INT nMode, INT nIdx, const void *pIdx, const void* pVtx, INT nStride)
{
	char*	p = (char*)pVtx;
	INT		dFVF = m_dFVF;

	UINT	nTex0 = 0;
	UINT	nTex1 = 0;

	if(!pVtx)
		return DGE_EFAIL;

	if(!(DGE_FVF_XYZ & dFVF))	// 위치가 없으면 실패
		return DGE_EFAIL;


	if(m_pTex[0]) nTex0 = m_pTex[0]->GetId();
	if(m_pTex[1]) nTex1 = m_pTex[1]->GetId();


	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);


	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer  (3, DGE_FMT_FIXED,	nStride, p); p += sizeof(DGE_INT3  );


	if( DGE_FVF_NORMAL & dFVF)	{	glEnableClientState(GL_NORMAL_ARRAY);		glNormalPointer  (   DGE_FMT_FIXED,	nStride, p); p += sizeof(DGE_INT3  );	}
	if( DGE_FVF_DIFFUSE & dFVF)	{	glEnableClientState(GL_COLOR_ARRAY);		glColorPointer   (4, DGE_FMT_UBYTE, nStride, p); p += sizeof(DGE_COLORB);	}


	if( DGE_FVF_TEX1 & dFVF)
	{
		if(nTex0)
		{
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, nTex0);
			glEnable(GL_TEXTURE_2D);

			glTexCoordPointer(2, DGE_FMT_FIXED,	nStride, p);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_TssAdS[0]);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_TssAdT[0]);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_TssMin[0]);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_TssMag[0]);

			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, (GLfloat)m_TssOp[0]);

		}

		if(nTex0 && nTex1)
		{
			glActiveTexture(GL_TEXTURE1);
			glClientActiveTexture(GL_TEXTURE1);
			glBindTexture (GL_TEXTURE_2D, nTex1);
			glEnable(GL_TEXTURE_2D);

			glTexCoordPointer(2, DGE_FMT_FIXED,	nStride, p);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_TssAdS[1]);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_TssAdT[1]);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_TssMin[1]);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_TssMag[1]);

			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, (GLfloat)m_TssOp[1]);

		}
	}


	glDrawElements(nMode, nIdx, DGE_FMT_INDEX16, pIdx);


	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);


	return DGE_OK;
}






INT CDGE_Device::Clear(DWORD dClearMode)
{
	glClear(dClearMode);
	return DGE_OK;
}

INT CDGE_Device::Present(DGE_HANDLE p1, DGE_HANDLE p2, DGE_HANDLE p3, DGE_HANDLE p4)
{
	eglSwapBuffers(m_pEgDsp, m_pEgSrf);
	glFlush();
	return DGE_OK;
}


// Create Device
INT DGE_CreateDevice(char* sCmd
					   , PDGE_DEVICE* pData
					   , DGE_HANDLE p1			// Window Handle
					   , DGE_HANDLE p2			// Main Application Program Pointer
					   , DGE_HANDLE p3			// No Use
					   , DGE_HANDLE p4			// No Use
					 )
{
	CDGE_Device* pObj = NULL;
	*pData		= NULL;

	pObj = new CDGE_Device;

	if(DGE_FAILED(pObj->Create(p1, p2, p3, p4)))
	{
		delete pObj;
		return DGE_ECANNOTALLOCATED;
	}

	*pData = pObj;
	return DGE_OK;
}


INT DGE_DestroyDevice(PDGE_DEVICE* pData)
{
	if(NULL == *pData)
		return DGE_OK;

	delete *pData;
	(*pData) = NULL;

	return DGE_OK;
}


INT DGE_DrawPrimitiveUPf(INT dFVF, INT nMode, INT First, INT nVtx, const void* pVtx, INT nStride)
{
	char* p = (char*)pVtx;

	if(!pVtx)
		return DGE_EFAIL;

	if(!(DGE_FVF_XYZ & dFVF))	// 위치가 없으면 실패
		return DGE_EFAIL;


	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);


								{ 	glEnableClientState(GL_VERTEX_ARRAY);		glVertexPointer  (3, DGE_FMT_FLOAT,	nStride, p); p += sizeof(DGE_FLOAT3);	}
	if( DGE_FVF_NORMAL & dFVF)	{	glEnableClientState(GL_NORMAL_ARRAY);		glNormalPointer  (   DGE_FMT_FLOAT,	nStride, p); p += sizeof(DGE_FLOAT3);	}
	if( DGE_FVF_DIFFUSE & dFVF)	{	glEnableClientState(GL_COLOR_ARRAY);		glColorPointer   (4, DGE_FMT_UBYTE,	nStride, p); p += sizeof(DGE_COLORB);	}
	if( DGE_FVF_TEX1 & dFVF)	{	glEnableClientState(GL_TEXTURE_COORD_ARRAY);glTexCoordPointer(2, DGE_FMT_FLOAT,	nStride, p); p += sizeof(DGE_FLOAT2);	}

	glDrawArrays(nMode, First, nVtx);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	return DGE_OK;
}



INT DGE_DrawIndexedPrimitiveUPf(INT dFVF, INT nMode, INT nIdx, const void *pIdx, const void* pVtx, INT nStride)
{
	char* p = (char*)pVtx;

	if(!pVtx)
		return DGE_EFAIL;

	if(!(DGE_FVF_XYZ & dFVF))	// 위치가 없으면 실패
		return DGE_EFAIL;


	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);


								{ 	glEnableClientState(GL_VERTEX_ARRAY);		glVertexPointer  (3, DGE_FMT_FLOAT,	nStride, p); p += sizeof(DGE_FLOAT3);	}
	if( DGE_FVF_NORMAL & dFVF)	{	glEnableClientState(GL_NORMAL_ARRAY);		glNormalPointer  (   DGE_FMT_FLOAT,	nStride, p); p += sizeof(DGE_FLOAT3);	}
	if( DGE_FVF_DIFFUSE & dFVF)	{	glEnableClientState(GL_COLOR_ARRAY);		glColorPointer   (4, DGE_FMT_UBYTE, nStride, p); p += sizeof(DGE_COLORB);	}
	if( DGE_FVF_TEX1 & dFVF)	{	glEnableClientState(GL_TEXTURE_COORD_ARRAY);glTexCoordPointer(2, DGE_FMT_FLOAT,	nStride, p); p += sizeof(DGE_FLOAT2);	}


	glDrawElements(nMode, nIdx, DGE_FMT_INDEX16, pIdx);


	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);


	return DGE_OK;
}



INT DGE_DrawPrimitiveUPi(INT dFVF, INT nMode, INT First, INT nVtx, const void* pVtx, INT nStride)
{
	char* p = (char*)pVtx;

	if(!pVtx)
		return DGE_EFAIL;

	if(!(DGE_FVF_XYZ & dFVF))	// 위치가 없으면 실패
		return DGE_EFAIL;


	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);


								{	glEnableClientState(GL_VERTEX_ARRAY);		glVertexPointer  (3, DGE_FMT_FIXED,	nStride, p); p += sizeof(DGE_INT3  );	}
	if( DGE_FVF_NORMAL & dFVF)	{	glEnableClientState(GL_NORMAL_ARRAY);		glNormalPointer  (   DGE_FMT_FIXED,	nStride, p); p += sizeof(DGE_INT3  );	}
	if( DGE_FVF_DIFFUSE & dFVF)	{	glEnableClientState(GL_COLOR_ARRAY);		glColorPointer   (4, DGE_FMT_UBYTE, nStride, p); p += sizeof(DGE_COLORB);	}
	if( DGE_FVF_TEX1 & dFVF)	{	glEnableClientState(GL_TEXTURE_COORD_ARRAY);glTexCoordPointer(2, DGE_FMT_FIXED,	nStride, p); p += sizeof(DGE_INT3  );	}

	glDrawArrays(nMode, First, nVtx);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);


	return DGE_OK;
}



INT DGE_DrawIndexedPrimitiveUPi(INT dFVF, INT nMode, INT nIdx, const void *pIdx, const void* pVtx, INT nStride)
{
	char* p = (char*)pVtx;

	if(!pVtx)
		return DGE_EFAIL;

	if(!(DGE_FVF_XYZ & dFVF))	// 위치가 없으면 실패
		return DGE_EFAIL;


	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

								{	glEnableClientState(GL_VERTEX_ARRAY);		glVertexPointer  (3, DGE_FMT_FIXED,	nStride, p); p += sizeof(DGE_INT3  );	}
	if( DGE_FVF_NORMAL & dFVF)	{	glEnableClientState(GL_NORMAL_ARRAY);		glNormalPointer  (   DGE_FMT_FIXED,	nStride, p); p += sizeof(DGE_INT3  );	}
	if( DGE_FVF_DIFFUSE & dFVF)	{	glEnableClientState(GL_COLOR_ARRAY);		glColorPointer   (4, DGE_FMT_UBYTE, nStride, p); p += sizeof(DGE_COLORB);	}
	if( DGE_FVF_TEX1 & dFVF)	{	glEnableClientState(GL_TEXTURE_COORD_ARRAY);glTexCoordPointer(2, DGE_FMT_FIXED,	nStride, p); p += sizeof(DGE_INT3  );	}

	glDrawElements(nMode, nIdx, DGE_FMT_INDEX16, pIdx);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);


	return DGE_OK;
}

