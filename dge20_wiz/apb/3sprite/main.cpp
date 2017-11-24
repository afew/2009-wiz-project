



#include <vector>

using namespace std;

#if defined(_WIN32)
	#pragma comment(lib, "dge20_.lib")
	#pragma comment(lib, "dgx20_.lib")

	#pragma comment(lib, "zImgJpg_.lib")
	#pragma comment(lib, "png124_.lib")
	#pragma comment(lib, "zlib123_.lib")

	#pragma comment(lib, "OpenGL32.lib")

	#include <windows.h>
#endif

#include <stdio.h>

#include <gles/gl.h>
#include <gles/egl.h>


#include <DGE_Type.h>
#include <DGE_System.h>
#include <DGE_Time.h>
#include <DGE_Math.h>
#include <DGE_Base.h>


#define MEDIA_DIR	"../../media/"



DGE_HANDLE		m_hWnd;				// Window 핸들
PDGE_DEVICE		m_pDev	= NULL;		// Device
PDGE_SPRITE		m_pSprite= NULL;	// 2D Sprite

vector<PDGE_TEXTURE>	m_vTex;		// Texture List

FLOAT GetAppFrame();
LRESULT DGE_WINAPI WndProc(DGE_HWND, UINT, WPARAM, LPARAM);


INT DGE_CALLBACK Run(DGE_HANDLE)
{
#if defined(_WIN32)
	static MSG msg ={0};

	if(msg.message==WM_QUIT)
		return -1;

	if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
	{
		::TranslateMessage( &msg );
		::DispatchMessage( &msg );
	}

	Sleep(10);
#else

	
#endif

	static INT c=0;
	++c;

//	if(c>20*60*20)
	if(c>20*60)
	{
		printf("Game Process Terminated\n");
		return -1;
	}


	FLOAT fFrame = GetAppFrame();


	static INT n=0;
	++n;

	if(n>5)
	{
		printf("%f\n", fFrame);
		n = 0;
	}


	// Prepare Rendering...
	m_pDev->BeginScene();

	// Clear Backbuffer
	m_pDev->Clear(DGE_CLEAR_COLOR_BUFFER | DGE_CLEAR_DEPTH_BUFFER);

	// Sprite Begin
	m_pSprite->Begin();

//	m_pSprite->Draw(NULL, NULL, NULL);

	
	m_pSprite->Draw(m_vTex[0], NULL, NULL);

	DGE_RECT	rc;
	DGXVECTOR2	s;
	DGXVECTOR2	r;
	DGXVECTOR2	t;
	DGXCOLOR	d;


	rc = DGE_RECT(  0,   0, 128, 128);	t = DGXVECTOR2(  10,  10);							m_pSprite->Draw(m_vTex[1], &rc, &t);
	rc = DGE_RECT(128,   0, 256, 128);	t = DGXVECTOR2( 138,  10);	d = DGXCOLOR(1,0,0,1);	m_pSprite->Draw(m_vTex[2], &rc, &t, &d);
	rc = DGE_RECT(  0, 128, 128, 256);	t = DGXVECTOR2(  10, 138);	d = DGXCOLOR(0,1,0,1);	m_pSprite->Draw(m_vTex[3], &rc, &t, &d);
	rc = DGE_RECT(128, 128, 256, 256);	t = DGXVECTOR2( 138, 138);	d = DGXCOLOR(0,0,1,1);	m_pSprite->Draw(m_vTex[4], &rc, &t, &d);


	for(INT i=5; i<44; ++i)
	{
		FLOAT X = FLOAT(rand()%320)-60;
		FLOAT Y = FLOAT(rand()%240)-60;

		t = DGXVECTOR2(X, Y);
		m_pSprite->Draw(m_vTex[i], NULL, &t, NULL);
	}


	float fRadian = DGXToRadian(c*2.f);

	fRadian = DGXToRadian(c);

	rc = DGE_RECT(0,0, m_vTex[45]->GetImgW(), m_vTex[5]->GetImgH());
	s	= DGXVECTOR2( -.5f, .5f);
	r	= DGXVECTOR2(100, 100);
	t	= DGXVECTOR2(100, 100);
	d	= DGXCOLOR(0,1,1,0.5f);

	m_pSprite->DrawEx(m_vTex[45]
					, &rc
					, &s
					, &r
					, fRadian
					, &t
					, &d);

	// Sprite End
	m_pSprite->End();


	// Post Rendering...
	m_pDev->EndScene();


	return 0;
}




// Main Program
INT main(INT argc, char* argv[])
{
	INT	i;
	
	// DGE 초기화
	if(DGE_FAILED(DGE_Init()))
		return 0;

	// Main Procedure 함수 설정
	if(DGE_FAILED(DGE_SetMainRunFunc(Run)))
		goto End;


	// Window 생성
	m_hWnd = DGE_CreateWindow(WndProc, "DGE_Tutorial");
	if(NULL == m_hWnd)
		goto End;

	// Device 생성
	if(DGE_FAILED(DGE_CreateDevice(NULL, &m_pDev, m_hWnd, NULL)))
		goto End;


	printf("DGE_CreateDevice Success\n");


	// Sprite 생성
	if(DGE_FAILED(DGE_CreateSprite(NULL, &m_pSprite, m_pDev)))
		goto End;

	printf("DGE_CreateSprite Success\n");


	for(i=0;i<46; ++i)
	{
		char	sFile[128]={0};

		
		if(i<10)
			sprintf(sFile, MEDIA_DIR"tex/t0%d.tga", i);
		else
			sprintf(sFile, MEDIA_DIR"tex/t%d.tga", i);

		PDGE_TEXTURE	pTex = NULL;
		if(DGE_FAILED(DGE_CreateTexture(NULL, &pTex, (DGE_HANDLE)sFile)))
			goto End;

		m_vTex.push_back(pTex);
	}

	printf("DGE_CreateTexture Success\n");


	// 프로그램 실행
	while(1)
	{
		if(DGE_FAILED(DGE_Run()))
			break;

		// Flipping
		m_pDev->Present(0,0,0,0);
	}


End:
	// Texture 해제

	for(i=0;i<m_vTex.size(); ++i)
	{
		PDGE_TEXTURE pTex = m_vTex[i];
		DGE_DestroyTexture(&pTex);
	}

	m_vTex.clear();


	// Sprite 해제
	DGE_DestroySprite(&m_pSprite);

	// Device 해제
	DGE_DestroyDevice(&m_pDev);

	// Window 해제
	DGE_DestroyWindow(m_hWnd);

	// DGE 해제
	DGE_Close();

	return 0;

}






// Window Message Procedure
LRESULT DGE_WINAPI WndProc(DGE_HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
#if defined(_WIN32)
	switch (uMsg)
	{
		case WM_KEYDOWN:
		{
			if(VK_ESCAPE == wParam)
			{
				SendMessage(hWnd, WM_CLOSE, 0, 0);
				return 0;
			}
			break;
		}

		case WM_CLOSE:
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
#else

	return DGE_OK;

#endif
}



FLOAT GetAppFrame()
{
#if defined(_WIN32)
	static INT		MaxCount = 30;
#else
	static INT		MaxCount = 10;
#endif

	static DOUBLE  fFps = 0.;
	static INT     iCnt = 0;
	static DWORD   dBgn = ::DGE_GetTickCount();
	DWORD   dCur = ::DGE_GetTickCount();  // GetTickCount()

	++iCnt;

	if(iCnt>=MaxCount)
	{
		fFps = DOUBLE(dCur-dBgn);
		fFps = iCnt*1000./fFps;
		iCnt = 0;
		dBgn = dCur;
	}

	return (FLOAT)fFps;
}
