

#include <vector>

using namespace std;

#if defined(_WIN32)
	#pragma comment(lib, "dge20_.lib")
	#pragma comment(lib, "dgx20_.lib")

	#pragma comment(lib, "OpenGL32.lib")
	#pragma comment(lib, "winmm.lib")

	#include <windows.h>
#endif

#include <stdio.h>

#include <DGE_System.h>
#include <DGE_Time.h>
#include <DGE_Math.h>
#include <DGE_Base.h>
#include <DGX_Media.h>


DGE_HWND		m_hWnd;				// Window 핸들
PDGE_DEVICE		m_pDev	= NULL;		// Device


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
	if(c>10*60)
	{
		printf("Game Process Terminated\n");
		return -1;
	}


	FLOAT fFrame = GetAppFrame();


	static INT n=0;
	++n;

	if(n>20)
	{
//		printf("%f\n", fFrame);
		n = 0;
	}


	// Volume Setting
	INT	volLeft	= 10 + rand()%100;
	INT	volRight= 10 + rand()%100;

	printf("Set Volume(Left, Right): %3d %3d   ", volLeft, volRight);

	DGX_MixerSetVolume(DGX_MIXER_VOLUME, volLeft, volRight);

	volLeft	= 0;	volRight= 0;
	DGX_MixerGetVolume(DGX_MIXER_VOLUME, &volLeft, &volRight);

	printf("Get: %d %d\n", volLeft, volRight);



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
	INT	volMax=0;
	INT	volMin=0;

	INT	volLeft=-200;
	INT	volRight=127;
	
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
	// Mixer Device 초기화
	if(DGE_FAILED(DGX_MixerOpen()))
		goto End;


	// Volume Range 얻기
	DGX_MixerGetVolumeRange(&volMax, &volMin);

	

	// Volume Setting
	DGX_MixerSetVolume(DGX_MIXER_VOLUME, volLeft, volRight);



	// 프로그램 실행
	while(1)
	{
		if(DGE_FAILED(DGE_Run()))
			break;

		// Flipping
		m_pDev->Present(0,0,0,0);
	}


End:
	// Mixer Device 해제
	DGX_MixerClose();

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
