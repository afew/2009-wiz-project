

#if defined(_WIN32)
	#pragma comment(lib, "dge20_.lib")
	#pragma comment(lib, "dgx20_.lib")

	#pragma comment(lib, "opengl32.lib")

	#include <windows.h>
	#include <gles/gl.h>
	#include <gles/egl.h>
#else
	#include <OpenGLES/gl.h>
	#include <OpenGLES/egl.h>
#endif

#include <stdio.h>

#include <DGE_System.h>
#include <DGE_Math.h>
#include <DGE_Time.h>

#include <DGE_Base.h>


DGE_HANDLE		m_hWnd;				// Window �ڵ�
IDGE_Device*	m_pDev = NULL;		// Device


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





INT DGE_CALLBACK Run(void*)
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


	static int n=0;
	++n;

	if(n>120)
	{
		printf("%f\n", fFrame);
		n = 0;
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
int main(int argc, char* argv[])
{
	// DGE �ʱ�ȭ
	DGE_Init();

	printf("DGE_Init\n");

	// Main Procedure �Լ� ����
	DGE_SetMainRunFunc(Run);

	// Window ����
	m_hWnd = DGE_CreateWindow(WndProc, "DGE_Tutorial");
	if(NULL == m_hWnd)
	{
		printf("DGE_CreateWindow Failed\n");
		return -1;
	}

	// Device ����
	if(DGE_FAILED(DGE_CreateDevice(NULL, &m_pDev, m_hWnd, NULL)))
	{
		printf("DGE_CreateDevice Failed\n");
		return -1;
	}




	// ���α׷� ����
	while(1)
	{
		if(DGE_FAILED(DGE_Run()))
			break;

		// Flipping
		m_pDev->Present(0,0,0,0);
	}

	// Device ����
	DGE_DestroyDevice(&m_pDev);

	// Window ����
	DGE_DestroyWindow(m_hWnd);

	// DGE ����
	DGE_Close();

	
	return 0;
}



