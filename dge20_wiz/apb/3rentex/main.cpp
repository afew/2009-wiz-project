



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


#include <DGE_Type.h>
#include <DGE_System.h>
#include <DGE_Time.h>
#include <DGE_Math.h>
#include <DGE_Base.h>


#define MEDIA_DIR	"../../media/tex/"
//#define MEDIA_DIR	"tex/"



DGE_HANDLE		m_hWnd;				// Window 핸들
PDGE_DEVICE		m_pDev	= NULL;		// Device
PDGE_SPRITE		m_pSprite= NULL;	// 2D Sprite

PDGE_TEXTURE	m_pTex1;			// Texture 1
PDGE_TEXTURE	m_pTex2;			// Texture 2
PDGE_TEXTURE	m_pTexR;			// Texture 3

INT				g_ImgW=320;
INT				g_ImgH=240;


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
	if(c>20*30)
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

	DGXCOLOR r(0,0,1,1);
	m_pDev->SetRenderState(DGE_RS_CLEAR_COLOR, &r);


	m_pDev->BeginScene();			// Prepare Rendering...
	m_pDev->Clear(DGE_CLEAR_COLOR_BUFFER | DGE_CLEAR_DEPTH_BUFFER);	// Clear Backbuffer

	m_pSprite->Begin();

	glViewport(0,0,g_ImgW, g_ImgH);
	m_pSprite->Draw(m_pTex1, NULL, NULL);

	DGXVECTOR2 pos(10, 10);
	m_pSprite->Draw(m_pTex2, NULL, &pos);

	glViewport(0,0,320, 240);
	m_pSprite->End();						// Sprite End
	m_pDev->EndScene();						// Post Rendering...

	m_pTexR->CopyTexImage2D();				// Copy From Frame Buffer




	m_pDev->BeginScene();			// Prepare Rendering...
	m_pDev->Clear(DGE_CLEAR_COLOR_BUFFER | DGE_CLEAR_DEPTH_BUFFER);	// Clear Backbuffer

	

	m_pSprite->Begin();

	m_pSprite->Draw(m_pTexR, NULL, &pos);

	m_pSprite->End();						// Sprite End
	m_pDev->EndScene();						// Post Rendering...


	return 0;
}




// Main Program
INT main(INT argc, char* argv[])
{
	char sFile1 [] = MEDIA_DIR"dummy_8.bmp";
	char sFile2 [] = MEDIA_DIR"t20.tga";

	TDGE_IMAGE	t=
	{
		  DGE_FMT_RGB
		, DGE_FMT_UBYTE
		, g_ImgW
		, g_ImgH
	};
	
	// DGE 초기화
	if(DGE_FAILED(DGE_Init()))
		return 0;

	// Main Procedure 함수 설정
	if(DGE_FAILED(DGE_SetMainRunFunc(Run)))
		goto End;


	// Window 생성
	m_hWnd = DGE_CreateWindow(WndProc, "DGE_Tutorial", 320, 240);
	if(NULL == m_hWnd)
		goto End;

	// Device 생성
	if(DGE_FAILED(DGE_CreateDevice(NULL, &m_pDev, m_hWnd, NULL)))
		goto End;


	// Sprite 생성
	if(DGE_FAILED(DGE_CreateSprite(NULL, &m_pSprite, m_pDev)))
		goto End;




	if(DGE_FAILED(DGE_CreateTexture(NULL, &m_pTex1, (DGE_HANDLE)sFile1)))
		goto End;

	if(DGE_FAILED(DGE_CreateTexture(NULL, &m_pTex2, (DGE_HANDLE)sFile2)))
		goto End;


	// for rendering copy texture
//	if(DGE_FAILED(DGE_CreateTexture(NULL, &m_pTexR, NULL, &t)))
//		goto End;

	if(DGE_FAILED(DGE_CreateTexture(NULL, &m_pTexR, NULL, NULL, (DGE_HANDLE)&g_ImgW, (DGE_HANDLE)&g_ImgH)))
		goto End;






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
	DGE_DestroyTexture(&m_pTex1);
	DGE_DestroyTexture(&m_pTex2);
	DGE_DestroyTexture(&m_pTexR);

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
