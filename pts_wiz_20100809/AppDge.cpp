// Implementation of the CAppDge class.
//
////////////////////////////////////////////////////////////////////////////////


#include "_StdAfx.h"


CAppDge* CAppDge::m_pAppDge = NULL;


CAppDge::CAppDge()
{
	CAppDge::m_pAppDge = this;

	m_hWnd		= NULL;
	m_pDev		= NULL;
	m_pSprite	= NULL;

	memset(m_sCls, 0, sizeof(m_sCls));
	strcpy(m_sCls,"DGE_Tutorial");


	m_nScnW		= 0;
	m_nScnH		= 0;

	m_fElapsed	= 0.0;
	m_fFPS		= 30.0F;
}


INT CAppDge::Create(DGE_HANDLE p1, DGE_HANDLE, DGE_HANDLE, DGE_HANDLE)
{
	DWORD	dColor =0xFF000000;


	// DGE 초기화
	if(DGE_FAILED(DGE_Init()))
		return 0;
	
	// Main Procedure 함수 설정
	if(DGE_FAILED(DGE_SetMainRunFunc(CAppDge::Run3D)))
		goto End;
	
	
	// Window 생성
	m_hWnd = DGE_CreateWindow(WndProc, m_sCls,320, 240);
	if(NULL == m_hWnd)
		goto End;


	DGE_WindowSize(&m_nScnW, &m_nScnH);
	
	// Device 생성
	if(DGE_FAILED(DGE_CreateDevice(NULL, &m_pDev, m_hWnd, NULL)))
		goto End;


	m_pDev->SetRenderState(DGE_RS_CLEAR_COLOR, dColor);

	
//	printf("DGE_CreateDevice Success\n");


	// Sprite 생성
	if(DGE_FAILED(DGE_CreateSprite(NULL, &m_pSprite, m_pDev)))
		goto End;

//	printf("DGE_CreateSprite Success\n");



	// Mixer Device 초기화
	if(DGE_FAILED(DGX_MixerOpen()))
		goto End;


	m_pDev->SetRenderState(DGE_RS_SHADE_MODEL, DGE_ST_SMOOTH);
	m_pDev->SetRenderState(DGE_RS_DEPTH_TEST, DGE_ST_ENABLE);
	m_pDev->SetRenderState(DGE_RS_CULL_FACE, DGE_ST_ENABLE);


	// Haptic Device Init
#if !defined(GP2X_WIZ)
	if(DGE_FAILED(DGE_HapticOpen()))
		goto End;
#endif


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

#if !defined(GP2X_WIZ)
	DGE_HapticClose();				// Haptic Device Release
#endif

	DGX_SoundDeviceClose();			// Sound Device 해제
	DGX_MixerClose();				// Mixer Device 해제

	DGE_DestroySprite(&m_pSprite);	// Sprite 해제
	DGE_DestroyDevice(&m_pDev);		// Device 해제
	DGE_DestroyWindow(m_hWnd);		// Window 해제
	
	DGE_Close();					// DGE 해제

	return DGE_OK;
}





LRESULT CAppDge::MsgProc(DGE_HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
#if defined(_WIN32) || defined(WIN32)
	switch (uMsg)
	{
//	case WM_KEYDOWN:
//		{
//			if(VK_ESCAPE == wParam)
//			{
//				SendMessage(hWnd, WM_CLOSE, 0, 0);
//				return 0;
//			}
//			break;
//		}
		
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




