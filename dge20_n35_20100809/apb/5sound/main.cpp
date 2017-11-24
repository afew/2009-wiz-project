


#if defined(_WIN32)
	#pragma comment(lib, "dge20_.lib")
	#pragma comment(lib, "dgx20_.lib")

	#pragma comment(lib, "OpenGL32.lib")

	#pragma comment(lib, "winmm.lib")
	#pragma comment(lib, "openal11_.lib")
	#pragma comment(lib, "openalc11_.lib")
	#pragma comment(lib, "openalu11_.lib")
	#pragma comment(lib, "openalut11_.lib")


	#include <windows.h>
	#include <conio.h>

	#include <AL_win/al.h>
	#include <AL_win/alc.h>
	#include <AL_win/alut.h>

#else
	#include <AL/al.h>
	#include <AL/alc.h>
	#include <AL/alut.h>

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
#include <DGX_Sound.h>


#define MEDIA_DIR	"../../media/sound/"
//#define MEDIA_DIR	"sound/"



DGE_HWND		m_hWnd;				// Window 핸들
PDGE_DEVICE		m_pDev	= NULL;		// Device
PDGX_INPUT		m_pInput= NULL;		// Input

#define MAX_SOUND	4

PDGX_SOUND		m_pSnd[MAX_SOUND];	// Sound Instance



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
	if(c>20*60*25)
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


	// Input Update
	m_pInput->Update();


	if(m_pInput->KeyDown(DGXKEY_START))
		return -1;


	// Play Sound
	if(m_pInput->KeyDown(DGXKEY_FA))
	{
		for(int i=2; i<MAX_SOUND; ++i)
			m_pSnd[i]->Play();
	}

	// Play ding.wav
	if(m_pInput->KeyDown(DGXKEY_FB))
		m_pSnd[0]->Play();


	// Play ding.wav
	if(m_pInput->KeyDown(DGXKEY_FY))
		m_pSnd[1]->Play();
	

	// Prepare Rendering...
	m_pDev->BeginScene();


	// Clear Backbuffer
	m_pDev->Clear(DGE_CLEAR_COLOR_BUFFER | DGE_CLEAR_DEPTH_BUFFER);


	// Post Rendering...
	m_pDev->EndScene();


	return 0;
}



// Main Program
INT main(INT argc, char* argv[])
{
	INT		hr = 0;
	INT		i;


	char* soundfile[] =
	{
		MEDIA_DIR"ding.wav",
		MEDIA_DIR"2.wav",
		MEDIA_DIR"3.wav",
		MEDIA_DIR"groove1.wav",
		MEDIA_DIR"tsound1.wav",
		MEDIA_DIR"mono.wav",
		MEDIA_DIR"stereo.wav",		
	};


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


	// Input 생성
	if(DGE_FAILED(DGX_CreateInput(NULL, &m_pInput, m_pDev, m_hWnd)))
		goto End;


	// Sound Device 생성
	if(DGE_FAILED(DGX_SoundDeviceOpen()))
		goto End;

	printf("DGE_CreateDevice Success\n");


	// Sound 객체 생성
	for(i=0; i<MAX_SOUND; ++i)
	{
		hr = DGX_CreateSound(NULL, &m_pSnd[i], soundfile[i]);
		if(DGE_FAILED(hr))
			goto End;

		m_pSnd[i]->SetVolume(0.8F);		// 볼륨 설정
		m_pSnd[i]->SetRepeat(1);		// 반복 횟수
	}


	printf("Sound Load Complete\n");





	// 프로그램 실행
	while(1)
	{
		if(DGE_FAILED(DGE_Run()))
			break;

		// Flipping
		m_pDev->Present(0,0,0,0);
	}


End:

	// Sound 객체 해제
	for(i=0; i<MAX_SOUND; ++i)
		DGX_DestroySound(&m_pSnd[i]);


	// Sound Device 해제
	DGX_SoundDeviceClose();


	// Input 해제
	DGX_DestroyInput(&m_pInput);


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
