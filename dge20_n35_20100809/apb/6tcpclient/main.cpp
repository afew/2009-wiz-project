

#if defined(_WIN32)
	#pragma comment(lib, "dge20_.lib")
	#pragma comment(lib, "dgx20_.lib")
	#pragma comment(lib, "dgt20_.lib")

	#pragma comment(lib, "OpenGL32.lib")

	#pragma comment(lib, "WS2_32.lib")

	#include <windows.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include <DGE_System.h>
#include <DGE_Time.h>
#include <DGE_Math.h>
#include <DGE_Base.h>
#include <DGE_Input10.h>
#include <DGX_Input.h>
#include <DGX_Network.h>


DGE_HANDLE		m_hWnd	= NULL;					// Window 핸들
PDGE_DEVICE		m_pDev	= NULL;					// Device
PDGX_INPUT		m_pInput= NULL;					// Input

//char			m_sPt[32] = "20000";			// Host Port
//char			m_sIp[64] = "192.168.0.36";		// Server IP

char			m_sPt[32] = {0};				// Host Port
char			m_sIp[64] = {0};				// Server IP


SOCKET			m_scHost = DGE_INVALID_SOCKET;	// Socket
SOCKADDR_IN		m_sdHost={0};					// Socket addr

INT				m_nSend;						// Send Byte
char			m_sBufSnd[512];					// Send Buffer

INT				m_nRecv;						// Recv Byte
char			m_sBufRcv[512]={0};


FLOAT	GetAppFrame();
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


	
//	if(m_pInput->KeyDown(IDGX_Input::DGEKEY_FB))
	if(nTsbState)
	{
		static int c=0;
		++c;

		memset(m_sBufSnd, 0, sizeof m_sBufSnd);
		sprintf(m_sBufSnd, "Socket(%d) 안녕하세요: %d \n", m_scHost, c);

		int iLen = strlen(m_sBufSnd);
		m_nSend = DGX_SocketSend(m_scHost, m_sBufSnd, iLen, 0);

		printf("Send Byte: %d\n", m_nSend);

	}



	if(m_pInput->KeyDown(DGEKEY_START))
		return -1;




	// 데이터 수신
	m_nRecv = DGX_SocketRecv(m_scHost, m_sBufRcv, sizeof m_sBufRcv, 0);
	
	if(DGE_SOCKET_ERROR == m_nRecv)
	{
		printf("Gracefully closed\n");
		return -1;
	}

	// 비동기 입출력이면 데이터 수신 없음
	else if(0 == m_nRecv)
	{
//		printf("Receive Socket Error\n");
	}
	else if(0<m_nRecv)
	{
		m_sBufRcv[m_nRecv  ]=0;
		m_sBufRcv[m_nRecv+1]=0;
		printf("Recv from server : %s\n", m_sBufRcv);
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
	FILE* fp = fopen("host.txt", "rt");
	char	sLine[128]={0};
	if(NULL == fp)
	{
		printf("host.txt Open Failed\n");
		return 0;
	}

	fgets(sLine, 128, fp);
	fclose(fp);
	
	printf("%s\n", sLine);
	sscanf(sLine, "%*s %s %s", m_sIp, m_sPt);

	printf("Server Ip, port: %s:%s", m_sIp, m_sPt);

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





	// Network Application
	if(DGE_FAILED(DGX_NetDeviceOpen()))
	{
		printf("Network Device Failed\n");
		goto End;
	}


	// 서버 접속을 위한 TCP소켓 생성
	if(DGE_FAILED(DGX_SocketTcpCreate(&m_scHost)))
	{
		printf("Create TCP Socket Failed\n");
		goto End;
	}
	
	
	// Server IP, Port 설정
	if(DGE_FAILED(DGX_SocketAddr(&m_sdHost, m_sIp, m_sPt)))
	{
		printf("Setup Non-blocking Socket Failed\n");
		goto End;
	}


	// Connetion to Server
	if(DGE_FAILED(DGX_SocketConnect(m_scHost, &m_sdHost)))
	{
		printf("Socket Connection Failed\n");
		goto End;
	}


	// Set Non-Blocking Socket
	if(DGE_FAILED(DGX_SocketNonBlocking(m_scHost, TRUE)))
	{
		printf("Setup Non-blocking Socket Failed\n");
		goto End;
	}





	// 프로그램 실행
	while(1)
	{
		if(DGE_FAILED(DGE_Run()))
			break;

		// Flipping
		m_pDev->Present(0,0,0,0);
	}


End:
	// 소켓 해제
	DGX_SocketClose(&m_scHost);

	// 네트워크 해제
	DGX_NetDeviceClose();

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

