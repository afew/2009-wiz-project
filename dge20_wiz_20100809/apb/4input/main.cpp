
#if defined(_WIN32)
	#pragma comment(lib, "dge20_.lib")
	#pragma comment(lib, "dgx20_.lib")
	#pragma comment(lib, "dgt20_.lib")

	#pragma comment(lib, "OpenGL32.lib")

	#include <windows.h>
#endif

#include <stdio.h>

#include <DGE_System.h>
#include <DGE_Time.h>
#include <DGE_Math.h>
#include <DGE_Base.h>
#include <DGX_Input.h>


DGE_HANDLE		m_hWnd;				// Window 핸들
PDGE_DEVICE		m_pDev	= NULL;		// Device
PDGX_INPUT		m_pInput= NULL;		// Input


FLOAT GetAppFrame();
LRESULT DGE_WINAPI WndProc(DGE_HWND, UINT, WPARAM, LPARAM);


INT DGE_CALLBACK Run(DGE_HANDLE)
{
#if defined(_WIN32)
	static MSG msg ={0};

	if(msg.message==WM_QUIT)
		return DGE_EFAIL;

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

	if(c>120*60*5)
//	if(c>20*60)
	{
		printf("Game Process Terminated\n");
		return -1;
	}


	FLOAT fFrame = GetAppFrame();


	static INT n=0;
	++n;

	if(n>5)
	{
//		printf("%3.f\n", fFrame);
		n = 0;
	}

	

	m_pInput->Update();


	DGXVECTOR3	vcTsbPos = m_pInput->GetTsbPos();
	DGE_STATE	nTsbState= m_pInput->TsbState();

	if(nTsbState)
		printf("%3.f %3.f %d\n", vcTsbPos.x, vcTsbPos.y, nTsbState);


	const BYTE*	pKey = m_pInput->GetKeyMap();
	const BYTE*	pTsb = m_pInput->GetTsbMap();

	for(int i=0; i<DGXINPUT_KEY_TOTAL; ++i)
	{
		if(pKey[i])
		{
			printf("You Pressed %d: state: %d\n", i, pKey[i]);
		}
	}


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


	printf("DGX_CreateInput Success\n");

	// 프로그램 실행
	while(1)
	{
		if(DGE_FAILED(DGE_Run()))
			break;

		// Flipping
		m_pDev->Present(0,0,0,0);
	}


End:
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
