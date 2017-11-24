



#include <vector>

using namespace std;

#if defined(_WIN32)
	#pragma comment(linker, "/subsystem:console")
	#pragma comment(lib, "freetype2311MT_D.lib")

	#pragma comment(lib, "dge20_.lib")
	#pragma comment(lib, "dgx20_.lib")

	#pragma comment(lib, "zImgJpg_.lib")
	#pragma comment(lib, "png124_.lib")
	#pragma comment(lib, "zlib123_.lib")

	#pragma comment(lib, "OpenGL32.lib")

	#include <windows.h>
#endif

#include <stdio.h>

#include <DGE_Type.h>
#include <DGE_System.h>
#include <DGE_Time.h>
#include <DGE_Math.h>
#include <DGE_Base.h>
#include <DGX_Font.h>


#define MEDIA_DIR	"../../media/"


DGE_HANDLE		m_hWnd;					// Window 핸들
PDGE_DEVICE		m_pDev	= NULL;			// Device
PDGE_SPRITE		m_pSprite= NULL;		// 2D Sprite
PDGX_FONT		m_pFont[10]	= {NULL};	// Font

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
	if(c>20*60 *10)
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
	

	char sbuf[128]={0};
	sprintf(sbuf, "gpH: Count: %3d, Frame: %4.f", c, fFrame);

	m_pFont[0]->SetString(sbuf);

	m_pFont[1]->SetString(sbuf);
	m_pFont[2]->SetString(sbuf);
	m_pFont[3]->SetString(sbuf);
	m_pFont[4]->SetString(sbuf);
	m_pFont[5]->SetString(sbuf);
	m_pFont[6]->SetString(sbuf);
	m_pFont[7]->SetString(sbuf);
	m_pFont[8]->SetString(sbuf);
	m_pFont[9]->SetString(sbuf);


	int i;
	for(i=0; i<10; ++i)
	{
		DGXVECTOR2 vcPos(5,5+ 25*i);
		
		m_pFont[i]->SetPos(&vcPos);
		m_pFont[i]->SetColor(&DGE_COLORF(1, 1, 0, 1));
	}

	// Prepare Rendering...
	m_pDev->BeginScene();

	// Clear Backbuffer
	m_pDev->Clear(DGE_CLEAR_COLOR_BUFFER | DGE_CLEAR_DEPTH_BUFFER);


	// Sprite Begin
	m_pSprite->Begin();
	

	for(i=0; i<10; ++i)
	{
		m_pFont[i]->DrawTxt();
	}

	// Sprite End
	m_pSprite->End();


	// Post Rendering...
	m_pDev->EndScene();

	return 0;
}




// Main Program
INT main(INT argc, char* argv[])
{
	int i;
	char	sFont1[] = MEDIA_DIR"font/hyuin.ttf";
	
	
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


	
	
	// Font 라이브러리 생성
	if(DGE_FAILED(DGX_TFFontOpen()))
		goto End;

	printf("DGX_TFFontOpen Success\n");

	for(i=0; i<10; ++i)
	{
		TDGX_FONT	tFont(sFont1, 9+i);

		if(DGE_FAILED(DGX_CreateFont(NULL, &m_pFont[i], &tFont, m_pSprite)))
			goto End;
	}

	printf("DGX_CreateFont Success\n");





	// 프로그램 실행
	while(1)
	{
		if(DGE_FAILED(DGE_Run()))
			break;

		// Flipping
		m_pDev->Present(0,0,0,0);
	}


End:

	// Font 객체 해제
	for(i=0; i<10; ++i)
	{
		DGX_DestroyFont(&m_pFont[i]);
	}

	

	// Font 라이브러리 해제
	DGX_TFFontClose();


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
	static INT		MaxCount = 10;
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
