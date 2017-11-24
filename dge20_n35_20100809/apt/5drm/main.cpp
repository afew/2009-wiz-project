


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
#include <DGT_DRM.h>


#define MEDIA_DIR	"../../media/"


DGE_HWND		m_hWnd;				// Window 핸들
PDGE_DEVICE		m_pDev	= NULL;		// Device
PDGE_SPRITE		m_pSprite= NULL;	// 2D Sprite
PDGX_INPUT		m_pInput= NULL;		// Input
PDGE_TEXTURE	m_pTex	= NULL;		// Texture
PDGT_DRM		m_pDRM	= NULL;		// DRM

// DRM 확인
int certificationDRM = DGE_EFAIL;


// DRM Resource Load
int DGE_ResourceLoad()
{
	int		hr =0;

	BYTE*	pData = NULL;				// 데이터 저장 공간
	int		fileLength = 0;				// File Length


	hr = m_pDRM->NED_FileOpen("sprites/bg.png", "rb");		// 배경 화면 이미지 로드

	if(NED_FILE_OK != hr)
		return -1;


	fileLength =
		m_pDRM->NED_FileGetLength("sprites/bg.png");		// 파일 길이 얻기



	if(0 >= fileLength)										// 파일 길이 확인
	{
		printf("Err: NED_FileGetLength!\n");
		goto End;
	}

	pData = (BYTE*)calloc(fileLength, sizeof(BYTE));		// 데이터 저장 공간 생성

	hr = m_pDRM->NED_FileRead(pData, fileLength);			// 파일 읽기


	if(NED_FILE_OK != hr)									// 파일 읽기 실패
	{
		printf("DRM Check : Image Load Failed! Error Message : %d\n", hr);
		goto End;
	}


	// 이미지 메모리 로드
	//int hr = g_cSurface.LoadImageFromMemory(0, 0, (char*)pData, fileLength);
//	// Texture 생성
//	if(DGE_FAILED(hr = DGE_CreateTexture(NULL, &m_pTex, (DGE_HANDLE)sTex, NULL, &colorKey)))
//		goto End;



End:
	if(pData)
		free(pData);				// 데이터 저장 공간 해제

	m_pDRM->NED_FileClose();		// 파일 닫기

    return DGE_OK;
}






int InitDRM()
{
	INT		hr = DGE_EFAIL;

	BYTE*	version = NULL;


	// DRM 초기화
	if(0 != m_pDRM->InitialNED())
	{
		printf("Init DRM Failed.\n");
		return -1;
	}


	// 파일 열기( 대상 파일 고정 )
	hr = m_pDRM->NED_FileOpen("version.txt", "rb");

	if(NED_FILE_OK !=hr)
	{
		printf("NED_FileOpen Failed.\n");
		return -1;
	}


	version = (BYTE*)malloc(sizeof(BYTE) * 11);			// 버전 정보 저장 공간 생성 --> ( 2010-05-24 )
	memset(version, 0, sizeof(BYTE) * 11);				// 버전 정보 저장 공간 초기화

	hr = m_pDRM->NED_FileRead((BYTE*)version, 10);		// 파일 읽기
	if(NED_FILE_OK != hr)
	{
		hr = DGE_EFAIL;
		goto End;
	}


	if(0 == strcmp((char*)version, "Build Date: 2010 08 18"))		// 버전 확인
	{
		hr = DGE_OK;							// DRM 확인 성공
	}
	else
	{
		hr = DGE_EFAIL;							// 버전 불일치, DRM 확인 실패
		printf("Version does not match.\n");
	}

End:
	if(version)									// 버전 정보 저장 공간 해제
		free(version);

	m_pDRM->NED_FileClose();					// 파일 닫기

	return DGE_OK;
}



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




	m_pDev->BeginScene();		// Prepare Rendering...
	m_pDev->Clear(DGE_CLEAR_COLOR_BUFFER | DGE_CLEAR_DEPTH_BUFFER);	// Clear Backbuffer


	m_pSprite->Begin();			// Sprite Begin



	m_pDev->EndScene();			// Post Rendering...


	return DGE_OK;
}



// Main Program
INT main(INT argc, char* argv[])
{
	INT		hr = 0;

	hr = DGT_CreateDRM(NULL, &m_pDRM);
	if(DGE_FAILED(hr))
		goto End;



	// DRM 초기화
	certificationDRM = InitDRM();
	if(DGE_FAILED(certificationDRM))
		goto End;


	// DRM 확인 성공
	printf("Success Init DRM\n");


	// DGE 초기화
	if(DGE_FAILED(hr = DGE_Init()))
		return DGE_OK;

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

	
	DGE_ResourceLoad();




	// 프로그램 실행
	while(1)
	{
		if(DGE_FAILED(DGE_Run()))
			break;

		// Flipping
		m_pDev->Present(0,0,0,0);
	}


End:

	DGT_DestroyDRM(&m_pDRM);		// DRM 종료 처리
	
	DGE_DestroyTexture(&m_pTex);	// Texture 해제

	DGX_DestroyInput(&m_pInput);	// Input 해제
	DGE_DestroySprite(&m_pSprite);	// Sprite 해제
	DGE_DestroyDevice(&m_pDev);		// Device 해제
	DGE_DestroyWindow(m_hWnd);		// Window 해제
	DGE_Close();					// DGE 해제

	return DGE_OK;

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
				return DGE_OK;
			}
			break;
		}

		case WM_CLOSE:
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return DGE_OK;
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
