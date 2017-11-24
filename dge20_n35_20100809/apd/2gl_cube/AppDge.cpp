// Implementation of the CAppDge class.
//
////////////////////////////////////////////////////////////////////////////////


#if defined(_WIN32) || defined(WIN32)
	#if _MSC_VER >= 1200
	#pragma warning(disable: 4996)
	#endif

	#include <Windows.h>
#endif


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <DGE_Type.h>
#include <DGE_System.h>
#include <DGE_Time.h>
#include <DGE_Math.h>
#include <DGE_Base.h>


#include "AppDge.h"


CAppDge* CAppDge::m_pAppDge = NULL;


CAppDge::CAppDge()
{
	CAppDge::m_pAppDge = this;

	m_hWnd		= NULL;
	m_pDev		= NULL;

	memset(m_sCls, 0, sizeof(m_sCls));
	strcpy(m_sCls,"DGE_Tutorial");


	m_nScnW		= 0;
	m_nScnH		= 0;

	m_fElapsed	= 0.0;
	m_fFPS		= 30.0F;
}


INT CAppDge::Create(DGE_HANDLE p1, DGE_HANDLE, DGE_HANDLE, DGE_HANDLE)
{
	// DGE 초기화
	if(DGE_FAILED(DGE_Init()))
		return 0;
	
	// Main Procedure 함수 설정
	if(DGE_FAILED(DGE_SetMainRunFunc(CAppDge::Run3D)))
		goto End;
	
	
	// Window 생성
	m_hWnd = DGE_CreateWindow(WndProc, m_sCls);
	if(NULL == m_hWnd)
		goto End;


	DGE_WindowSize(&m_nScnW, &m_nScnH);
	
	// Device 생성
	if(DGE_FAILED(DGE_CreateDevice(NULL, &m_pDev, m_hWnd, NULL)))
		goto End;
	
	printf("DGE_CreateDevice Success\n");


	m_pDev->SetRenderState(DGE_RS_SHADE_MODEL, DGE_ST_SMOOTH);
	m_pDev->SetRenderState(DGE_RS_DEPTH_TEST, DGE_ST_ENABLE);
	m_pDev->SetRenderState(DGE_RS_CULL_FACE, DGE_ST_ENABLE);


	if(DGE_FAILED(Init()))
		goto End;


	return DGE_OK;


End:
	Cleanup();
	return DGE_OK;
}


INT CAppDge::Run()
{
	while(1)	// 프로그램 실행
	{
		if(DGE_FAILED(DGE_Run()))
			break;

	}

	Cleanup();
	
	return DGE_OK;
}


INT	CAppDge::Render3D()
{
	if(DGE_FAILED(FrameMove()))
		return DGE_EFAIL;


	if(DGE_FAILED(Render()))
		return DGE_EFAIL;

	m_pDev->Present(0,0,0,0);

	UpdateStatus();


	return DGE_OK;
}


INT	DGE_CALLBACK CAppDge::Run3D(DGE_HANDLE)
{
#if defined(_WIN32) || defined(WIN32)
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


	if(CAppDge::m_pAppDge)
		return CAppDge::m_pAppDge->Render3D();

	return DGE_OK;
}


INT CAppDge::Cleanup()
{
	Destroy();

	// Device 해제
	DGE_DestroyDevice(&m_pDev);
	
	// Window 해제
	DGE_DestroyWindow(m_hWnd);
	
	// DGE 해제
	DGE_Close();

	return DGE_OK;
}





LRESULT CAppDge::MsgProc(DGE_HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
#if defined(_WIN32) || defined(WIN32)
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
#endif

	return DGE_OK;
}


// Window Message Procedure
LRESULT DGE_WINAPI CAppDge::WndProc(DGE_HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if(CAppDge::m_pAppDge)
		return CAppDge::m_pAppDge->MsgProc(hWnd, uMsg, wParam, lParam);

#if defined(_WIN32) || defined(WIN32)
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
#endif

	return DGE_OK;
}



void CAppDge::UpdateStatus()
{
#if defined(_WIN32)
	static INT		MaxCount = 10;
#else
	static INT		MaxCount = 10;
#endif
	
	static INT     iCnt = 0;
	static DWORD   dBgn = ::DGE_GetTickCount();
	DWORD   dCur = ::DGE_GetTickCount();  // GetTickCount()
	
	++iCnt;
	
	if(iCnt>=MaxCount)
	{
		m_fElapsed = DOUBLE(dCur-dBgn)/(iCnt*1000);

		m_fFPS = float(1/m_fElapsed);
		iCnt = 0;
		dBgn = dCur;
	}
}




