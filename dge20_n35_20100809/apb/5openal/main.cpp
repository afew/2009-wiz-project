


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


ALvoid DisplayALError(ALbyte *szText, ALint errorcode)
{
	printf("%s%s", szText, alGetString(errorcode));
}


DGE_HWND		m_hWnd;				// Window 핸들
PDGE_DEVICE		m_pDev	= NULL;		// Device
PDGX_INPUT		m_pInput= NULL;		// Input

ALsizei		size1=0;
ALsizei		freq1=0;
ALenum		format1=0;
ALvoid*		data1=NULL;
ALboolean	loop1=0;

ALuint		uiBuffer1=0;
ALuint		uiSource1=0;
char		sFile1[] = MEDIA_DIR"ding.wav";


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
	if(c>20*60*5)
	{
		printf("Game Process Terminated\n");
		return -1;
	}

	FLOAT fFrame = GetAppFrame();

//	static INT n=0;
//	++n;
//
//	if(n>5)
//	{
//		printf("%f\n", fFrame);
//		n = 0;
//	}

	// Input Update
	m_pInput->Update();



	if(m_pInput->KeyDown(DGXKEY_START))
		return -1;


	// Play ding.wav
	if(m_pInput->KeyDown(DGXKEY_FX))
		alSourcePlay( uiSource1);						// Play Source




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
	ALint	hr;


	hr = DGX_SoundDeviceOpen();

	if(DGE_FAILED(hr))
	{
		printf("Failed to Initialize Open AL\n");
		goto End;
	}

	
	{
		alutLoadWAVFile(sFile1, &format1, &data1, &size1, &freq1, &loop1);		// Load footsteps.wav
		hr = alGetError();
		if(AL_NO_ERROR != hr)
		{
			DisplayALError("alutLoadWAVFile: ", hr);
			goto End;
		}


		alGenBuffers( 1, &uiBuffer1 );					// Generate Buffers
		hr = alGetError();
		if(AL_NO_ERROR != hr)
		{
			DisplayALError("alGenBuffers: ", hr);
			goto End;
		}

		alBufferData(uiBuffer1,format1,data1,size1,ALsizei(freq1*1.F));
		free(data1);
		hr = alGetError();
		if(AL_NO_ERROR != hr)
			goto End;


		alGenSources( 1, &uiSource1 );					// Generate a Source to playback the Buffer
		alSourcei( uiSource1, AL_BUFFER, uiBuffer1 );

		alSourcef(uiSource1,AL_GAIN, 1.F);				// Set volume
		alSourcei(uiSource1,AL_LOOPING, AL_FALSE);		// Set looping
	}

	
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





	alSourcePlay( uiSource1);						// Play Source




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
	alSourceStop(uiSource1);
	alDeleteSources(1, &uiSource1);
	alDeleteBuffers(1, &uiBuffer1);


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
