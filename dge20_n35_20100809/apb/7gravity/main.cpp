//
// Gravity Sensor Example.
//
////////////////////////////////////////////////////////////////////////////////


#if defined(_WIN32)
	#pragma comment(linker, "/subsystem:console")
	#pragma comment(lib, "freetype2311MT_D.lib")

	#pragma comment(lib, "dge20_.lib")
	#pragma comment(lib, "dgx20_.lib")

	#pragma comment(lib, "zImgJpg_.lib")
	#pragma comment(lib, "png124_.lib")
	#pragma comment(lib, "zlib123_.lib")

	#pragma comment(lib, "libgles_cm.lib")

	#include <windows.h>
#endif

#include <stdio.h>

#include <DGE_Type.h>
#include <DGE_System.h>
#include <DGE_Time.h>
#include <DGE_Math.h>
#include <DGE_Base.h>
#include <DGE_Gsensor.h>
#include <DGX_Font.h>


#define MEDIA_DIR	"../../media/font/"


DGE_HANDLE		m_hWnd;					// Window �ڵ�
PDGE_DEVICE		m_pDev	= NULL;			// Device
PDGE_SPRITE		m_pSprite= NULL;		// 2D Sprite
PDGX_FONT		m_pFont	= NULL;			// Font

// G ���� ȯ��
DGE_GSENSOR_ENV g_GsEnv;

// G ���� ����
DGE_GSENSOR_VAL g_GsRead;


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
	if(c>20*60 *5)
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
	DGE_COLORF dFont(1, 1, 0, 1);

	DGXVECTOR2 vcPos(15,15);


	// Read G-sensor
	if(DGE_SUCCEEDED(DGE_GsensorRead(&g_GsRead)))
	{
		g_GsRead.x /= 10;
		g_GsRead.y /= 10;
		g_GsRead.z /= 10;

		g_GsRead.x *= 10;
		g_GsRead.y *= 10;
		g_GsRead.z *= 10;

		sprintf(sbuf, "%3d %3d %3d", g_GsRead.x, g_GsRead.y, g_GsRead.z);
	}

	m_pFont->SetString(sbuf);
	m_pFont->SetColor(&dFont);
	m_pFont->SetPos(&vcPos);


	m_pDev->BeginScene();	// Prepare Rendering...

	m_pDev->Clear(DGE_CLEAR_COLOR_BUFFER | DGE_CLEAR_DEPTH_BUFFER);	// Clear Backbuffer

	m_pSprite->Begin();		// Sprite Begin

	m_pFont->DrawTxt();


	m_pSprite->End();		// Sprite End


	m_pDev->EndScene();		// Post Rendering...

	return 0;
}




// Main Program
INT main(INT argc, char* argv[])
{
	char		sFont[] = MEDIA_DIR"hyuin.ttf";
	TDGX_FONT	tFont(sFont, 10);
	
	
	// DGE �ʱ�ȭ
	if(DGE_FAILED(DGE_Init()))
		return 0;

	// Main Procedure �Լ� ����
	if(DGE_FAILED(DGE_SetMainRunFunc(Run)))
		goto End;

	
	// Window ����
	m_hWnd = DGE_CreateWindow(WndProc, "DGE_Tutorial");
	if(NULL == m_hWnd)
		goto End;

	// Device ����
	if(DGE_FAILED(DGE_CreateDevice(NULL, &m_pDev, m_hWnd, NULL)))
		goto End;


	// Sprite ����
	if(DGE_FAILED(DGE_CreateSprite(NULL, &m_pSprite, m_pDev)))
		goto End;

	
	// Font ���̺귯�� ����
	if(DGE_FAILED(DGX_TFFontOpen()))
		goto End;

	printf("DGX_TFFontOpen Success\n");

	// Font ����
	if(DGE_FAILED(DGX_CreateFont(NULL, &m_pFont, &tFont, m_pSprite)))
		goto End;

	printf("DGX_CreateFont Success\n");


	// G ���� ��� �ʱ�ȭ
	if(DGE_FAILED(DGE_GsensorOpen()))
		goto End;


	printf("G-sensor Open Success\n");


	// G ���� ȯ�� ����( �⺻ �� ��� )	
	g_GsEnv.Range = DGE_GSN_GRAN2;
	g_GsEnv.Resolution = DGE_GSN_GRES12;
	g_GsEnv.TapHz = DGE_GSN_TAB400;
	g_GsEnv.TiltHz = DGE_GSN_TILT12;
	g_GsEnv.TiltTimer = 5;

	// G ���� ȯ�� ����
	if(DGE_FAILED(DGE_GsensorSetEnv(&g_GsEnv)))
		goto End;

	printf("G-sensor Set Environment Success\n");



	// ���α׷� ����
	while(1)
	{
		if(DGE_FAILED(DGE_Run()))
			break;

		// Flipping
		m_pDev->Present(0,0,0,0);
	}

End:

	DGE_GsensorClose();				// G ���� ��� ���� ó��

	DGX_DestroyFont(&m_pFont);		// Font ��ü ����
	DGX_TFFontClose();				// Font ���̺귯�� ����
	DGE_DestroySprite(&m_pSprite);	// Sprite ����
	DGE_DestroyDevice(&m_pDev);		// Device ����
	DGE_DestroyWindow(m_hWnd);		// Window ����
	DGE_Close();					// DGE ����

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
