


#if defined(_WIN32)
	#pragma comment(lib, "freetype2311MT_D.lib")

	#pragma comment(lib, "dge20_.lib")
	#pragma comment(lib, "dgx20_.lib")
	#pragma comment(lib, "dgt20_.lib")

	#pragma comment(lib, "zImgJpg_.lib")
	#pragma comment(lib, "png124_.lib")
	#pragma comment(lib, "zlib123_.lib")

	#pragma comment(lib, "OpenGL32.lib")

	#include <windows.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <math.h>

#include <DGE_System.h>
#include <DGE_Time.h>
#include <DGE_Math.h>
#include <DGE_Base.h>
#include <DGX_Input.h>
#include <DGX_Font.h>
#include <DGT_VKB.h>


#define MEDIA_DIR	"../../media/"


DGE_HWND		m_hWnd;				// Window 핸들
PDGE_DEVICE		m_pDev	= NULL;		// Device
PDGE_SPRITE		m_pSprite= NULL;	// 2D Sprite
PDGX_INPUT		m_pInput= NULL;		// Input
PDGE_TEXTURE	m_pTex	= NULL;		// Texture
PDGX_FONT		m_pFont	= NULL;		// Font
PDGT_VKB		m_pVKB	= NULL;		// Virtual Keyboard

BOOL			g_bVkcall;
int				isVisible = TRUE;


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
#else

	
#endif

	static INT c=0;
	++c;

//	if(c>20*60*20)
	if(c>20*60*25)
	{
		printf("Game Process Terminated\n");
		return -1;
	}

	FLOAT fFrame = GetAppFrame();

	static INT n=0;
	++n;
//	if(n>15)
//	{
//		printf("%f\n", fFrame);
//		n = 0;
//	}

	m_pInput->Update();			// Input Update

	DGXCOLOR	FontColor(1, 1, 0, 1);
	DGXVECTOR2	FontPos(55, 34);

	m_pFont->SetString("Hello world");
	m_pFont->SetColor(&FontColor);
	


	if(m_pInput->KeyDown(DGXKEY_START))
		return -1;




	char	sBuf[128];
	char*	sDstStr = NULL;
	int		iLen = 0;

	int		tsb = m_pInput->TsbUp();

//	if(tsb)
//		printf("tsb: %d\n", n);


	// 터치 단일 입력 발생
	if(m_pInput->TsbDown())
	{
		// 가상 키보드 입력 전달
		DGXVECTOR3* vcPos = (DGXVECTOR3*)m_pInput->GetTsbPos();

		m_pVKB->ProcessVK( INT(vcPos->x), INT(vcPos->y), TRUE);

		// 가상 키보드 입력 내용 반영
		m_pVKB->ConvertString();
	}

	sDstStr = (char*)m_pVKB->GetDestString();


	if(sDstStr)
		iLen = strlen(sDstStr);

	if(iLen)
		strcpy(sBuf, sDstStr);
	else
		memset(sBuf, 0, 128);


#if defined(WIN32) || defined(_WIN32)
	SetWindowText(GetActiveWindow(), sBuf);
#endif

	m_pFont->SetString("");
	m_pFont->SetPos(&FontPos);

	if(iLen)
	{
		m_pFont->SetColor(&FontColor);
		m_pFont->SetString(sDstStr);
	}


	// 가상 키보드 Update
	m_pVKB->FrameMove();





	m_pDev->BeginScene();		// Prepare Rendering...
	m_pDev->Clear(DGE_CLEAR_COLOR_BUFFER | DGE_CLEAR_DEPTH_BUFFER);	// Clear Backbuffer

	m_pSprite->Begin();			// Sprite Begin
	m_pVKB->Render();
	m_pSprite->End();			// Sprite End


	m_pSprite->Begin();			// Sprite Begin
	// 가상 키보드 표시 여부 확인
	// 표시
	// 지정된 문자열을 출력한다.
	m_pFont->DrawTxt();

	m_pSprite->End();			// Sprite End




	m_pDev->EndScene();			// Post Rendering...


	return 0;
}



// Main Program
INT main(INT argc, char* argv[])
{
	INT		hr = 0;
	char		sFont[] = MEDIA_DIR"font/gulim.ttf";
	char		sTex [] = MEDIA_DIR"vkb/keyboard_512.bmp";

	TDGX_FONT	tFont(sFont, 12);

	UINT		nTex = 0;
	DWORD colorKey =0xFF000000;



	// DGE 초기화
	if(DGE_FAILED(hr = DGE_Init()))
		return 0;

	// Main Procedure 함수 설정
	if(DGE_FAILED(hr = DGE_SetMainRunFunc(Run)))
		goto End;


	// Window 생성
	m_hWnd = DGE_CreateWindow(WndProc, "DGE_Tutorial");
	if(NULL == m_hWnd)
		goto End;

	// Device 생성
	if(DGE_FAILED(hr = DGE_CreateDevice(NULL, &m_pDev, m_hWnd, NULL)))
		goto End;

	// Sprite 생성
	if(DGE_FAILED(hr = DGE_CreateSprite(NULL, &m_pSprite, m_pDev)))
		goto End;

	// Input 생성
	if(DGE_FAILED(hr = DGX_CreateInput(NULL, &m_pInput, m_pDev, m_hWnd)))
		goto End;

	// Font 라이브러리 생성
	if(DGE_FAILED(hr = DGX_TFFontOpen()))
		goto End;

	// Font 생성
	if(DGE_FAILED(hr = DGX_CreateFont(NULL, &m_pFont, &tFont, m_pSprite)))
		goto End;


	// Texture 생성
	if(DGE_FAILED(hr = DGE_CreateTexture(NULL, &m_pTex, (DGE_HANDLE)sTex, NULL, &colorKey)))
		goto End;


	// Texture ID
	nTex = m_pTex->GetId();


	// Virtual Keyboard 생성
	if(DGE_FAILED(hr = DGT_CreateVKB(NULL, &m_pVKB, &nTex)))
		goto End;


	m_pVKB->SetAnimation(DGT_VKB_FADE);
	m_pVKB->SetFPS(DGE_FALSE);



	// 가상 키보드
	m_pVKB->SetFinishCode(&g_bVkcall);
	m_pVKB->SetLimit(8,7);


	


	// 프로그램 실행
	while(1)
	{
		if(DGE_FAILED(DGE_Run()))
			break;

		// Flipping
		m_pDev->Present(0,0,0,0);
	}


End:
	DGT_DestroyVKB(&m_pVKB);		// VKB 해제
	DGE_DestroyTexture(&m_pTex);	// Texture 해제
	DGX_DestroyFont(&m_pFont);		// Font 해제

	DGX_TFFontClose();				// Font Library 해제

	DGX_DestroyInput(&m_pInput);	// Input 해제
	DGE_DestroySprite(&m_pSprite);	// Sprite 해제
	DGE_DestroyDevice(&m_pDev);		// Device 해제
	DGE_DestroyWindow(m_hWnd);		// Window 해제
	DGE_Close();					// DGE 해제

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
