

#if defined(_WIN32) || defined(WIN32)
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


enum
{
	BUFSIZE				= 512,
	MAX_SOCKET_EVENT	= 64
};


DGE_HANDLE		m_hWnd	= NULL;					// Window 핸들
PDGE_DEVICE		m_pDev	= NULL;					// Device
PDGX_INPUT		m_pInput= NULL;					// Input

char			m_sPt[32] = "20000";			// Host Port

SOCKET			m_scHost = DGE_INVALID_SOCKET;	// Socket
SOCKADDR_IN		m_sdHost={0};					// Socket addr

char			m_sBufSnd[512];					// Send Buffer
INT				m_nSend;						// Send byte
FD_SET			m_scFD;							// Socket File Descriptor Set

INT				m_fdMax;						// Max Socket
INT				m_iNsck;						// Socket Binding Number
SOCKET			m_rmH[MAX_SOCKET_EVENT]={0};	// Socket List




INT Fd_Set(SOCKET scH)
{
	INT i;
	INT n =-1;
	
	for (i=0; i<m_iNsck; ++i)
	{
		if (m_rmH[i] == scH)
		{
			n = i;
			break;
		}
	}

	if (i == m_iNsck)
	{
		n = i;

		if (m_iNsck < MAX_SOCKET_EVENT)
		{
			m_rmH[i] = scH;
			++m_iNsck;
		}
	}

	return n;
}

INT Fd_Clr(SOCKET scH)
{
	INT i;
	INT	n = -1;

	// n 찾기
	for (i=0; i<m_iNsck; ++i)
	{
		if (m_rmH[i] == scH)
		{
			n = i;
			break;
		}
	}

	for (i=0; i<m_iNsck; ++i)
	{
		if (m_rmH[i] == scH)
		{
			if(0xFFFFFFFF != m_rmH[i])
			{
				m_rmH[i] = 0xFFFFFFFF;
			}

			while (i < m_iNsck-1)
			{
				memcpy(&m_rmH[i], &m_rmH[i+1], sizeof(SOCKET));
				++i;
			}
			
			INT nCnt = m_iNsck-1;
			m_rmH[nCnt]= 0xFFFFFFFF;
			--m_iNsck;
			break;
		}
	}

	return n;
}





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


	if(m_pInput->KeyDown(DGEKEY_MENU))
		return -1;



	INT hr=-1;

	FD_SET	fdsRead;
	FD_SET	fdsExcp;
	TIMEVAL	timeout;


	if(!m_scHost)
		return -1;

	// 이렇게 매번 읽는 루틴에서 시간과 FD_SET을 다시 할당해야
	// 제대로 동작한다.
	memcpy(&fdsRead, &m_scFD, sizeof(FD_SET));
	memcpy(&fdsExcp, &m_scFD, sizeof(FD_SET));

	timeout.tv_sec = 0;
	timeout.tv_usec = 0;

	hr = DGX_SocketSelect(m_fdMax+1, &fdsRead, NULL, &fdsExcp, &timeout);

	if(DGE_FAILED(hr))
	{
		printf("DGX_SocketSelect() Failed\n");
		return -1;
	}



#if defined(_WIN32) || defined(WIN32)

	for(UINT fd=0; fd < m_scFD.fd_count; ++fd)
	{
 		if(FD_ISSET(m_scFD.fd_array[fd], &fdsRead))
		{
			if(m_scHost == m_scFD.fd_array[fd])
			{
				SOCKET scCln;
				SOCKADDR_IN	sdCln;
				INT iSizeAdd = sizeof(SOCKADDR_IN);

				if(DGE_SUCCEEDED(DGX_SocketAccept(&scCln, &sdCln, m_scHost)))
				{
					// m_scFD.fd_count를 증가 시킨다.
					FD_SET(scCln, &m_scFD);

					DGX_SocketNonBlocking(scCln);
					DGX_SocketNaggleOff(scCln);

					Fd_Set(scCln);
					printf("New Client: %d, Number: %d\n", scCln, (m_iNsck-1));
				}
			}

			else
			{
				INT		iRcv;
				char	sBufRcv[512]={0};
				iRcv	= DGX_SocketRecv(m_scFD.fd_array[fd], sBufRcv, BUFSIZE, 0/*MSG_OOB*/);

				if(iRcv>0)
				{
					sBufRcv[iRcv  ]=0;
					sBufRcv[iRcv+1]=0;

					printf("Recv(%d): %s\n", m_scFD.fd_array[fd], sBufRcv);


					memset(m_sBufSnd, 0, sizeof m_sBufSnd);
					sprintf(m_sBufSnd, "%d %s", m_scFD.fd_array[fd], sBufRcv);
					m_nSend = strlen(m_sBufSnd);
					
					// 받은 메시지를 접속한 클라이언트 모두에게 돌려준다.
					for(INT j=1;j<m_iNsck; ++j)
					{
						SOCKET scCln = m_rmH[j];
						DGX_SocketSend(scCln, m_sBufSnd, m_nSend, 0);
					}
				}
				else
				{
					// close
					SOCKET	scCln = m_scFD.fd_array[fd];
					printf("Socket Close: %d \n", scCln);

					// m_scFD.fd_count를 감소 시킨다.
					FD_CLR(scCln, &m_scFD);
					
					Fd_Clr(scCln);
					printf("Client: %d, Number: %d\n", scCln, (m_iNsck-1));

					DGX_SocketClose(&scCln);
				}
			}
		}
	

		if(FD_ISSET(m_scFD.fd_array[fd], &fdsExcp))
		{
			SOCKET	scCln = m_scFD.fd_array[fd];
			
			// m_scFD를 감소 시킨다.
			FD_CLR(scCln, &m_scFD);
			Fd_Clr(scCln);

			printf("Socket Exception and Close: %d, Number: %d\n", scCln, (m_iNsck-1));
			DGX_SocketClose(&scCln);
		}
	}

#else

	for(INT fd=0; fd<=m_fdMax; ++fd)
	{
 		if(FD_ISSET(fd, &fdsRead))
		{
			// 접속 요청
			if(m_scHost == fd)
			{
				SOCKET		scCln;
				SOCKADDR_IN	sdCln;

				if(DGE_SUCCEEDED(DGX_SocketAccept(&scCln, &sdCln, m_scHost)))
				{
					// m_scFD.fd_count를 증가 시킨다.
					FD_SET(scCln, &m_scFD);


					DGX_SocketNonBlocking(scCln);
					DGX_SocketNaggleOff(scCln);


					// 최대 값 재 설정
					if(m_fdMax<scCln)
						m_fdMax = scCln;

					Fd_Set(scCln);
					printf("New Client: %d, Number: %d\n", scCln, (m_iNsck-1));
				}
			}

			else
			{
				INT		iRcv;
				char	sBufRcv[512]={0};
				iRcv = DGX_SocketRecv(fd, sBufRcv, BUFSIZE, 0/*MSG_OOB*/);

				if(iRcv>0)
				{
					sBufRcv[iRcv  ]=0;
					sBufRcv[iRcv+1]=0;

					printf("Recv(%d): %s\n", fd, sBufRcv);

					char	m_sBufSnd[512]={0};
					sprintf(m_sBufSnd, "%d %s", fd, sBufRcv);
					m_nSend = strlen(m_sBufSnd);

					// 받은 메시지를 접속한 클라이언트 모두에게 돌려준다.
					for(UINT j=1;j<m_iNsck; ++j)
					{
						SOCKET scCln = m_rmH[j];
						DGX_SocketSend(scCln, m_sBufSnd, m_nSend, 0);
					}
					
//					for(INT j=0;j<=m_fdMax; ++j)
//					{
//						if(m_scHost != j)
//							send(j, m_sBufSnd, m_nSend, 0);
//					}
				}
				else
				{
					// close
					SOCKET	scCln = fd;
					printf("Socket Close: %d \n", scCln);

					// m_scFD를 감소 시킨다.
					FD_CLR(scCln, &m_scFD);
					
					Fd_Clr(scCln);
					printf("Client: %d, Number: %d\n", scCln, (m_iNsck-1));

					DGX_SocketClose(&scCln);
				}
			}
		}


		if(FD_ISSET(fd, &fdsExcp))
		{
			SOCKET	scCln = fd;

			// m_scFD를 감소 시킨다.
			FD_CLR(scCln, &m_scFD);
			Fd_Clr(scCln);

			printf("Socket Exception and Close: %d, Number: %d\n", scCln, (m_iNsck-1));
			DGX_SocketClose(&scCln);
		}
	}

#endif



	m_pDev->BeginScene();

	// Clear Backbuffer
	m_pDev->Clear(DGE_CLEAR_COLOR_BUFFER | DGE_CLEAR_DEPTH_BUFFER);


	m_pDev->EndScene();

	return 0; 
}



// Main Program
INT main(INT argc, char* argv[])
{
	INT hr=-1;

	printf("Start I/O멀티 플렉싱 서버(select).\nPort: %s\n", m_sPt);

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
	hr = DGE_CreateDevice(NULL, &m_pDev, m_hWnd, NULL);
	if(DGE_FAILED(hr))
		goto End;
	
	
	// Input 생성
	hr = DGX_CreateInput(NULL, &m_pInput, m_pDev, m_hWnd);
	if(DGE_FAILED(hr))
		goto End;



	// Network Application
	if(DGE_FAILED(DGX_NetDeviceOpen()))
	{
		printf("DGX_NetDeviceOpen() Failed\n");
		goto End;
	}

	// 서버 접속을 위한 TCP소켓 생성
	if(DGE_FAILED(DGX_SocketTcpCreate(&m_scHost)))
	{
		printf("DGX_SocketTcpCreate() Failed\n");
		goto End;
	}

	printf("Socket: %d\n", m_scHost);

	// Host IP, Port 설정
	if(DGE_FAILED(DGX_SocketAddr(&m_sdHost, NULL, m_sPt)))
	{
		printf("DGX_SocketAddr() Failed\n");
		goto End;
	}


	// Set Non-Blocking Socket
	if(DGE_FAILED(DGX_SocketNonBlocking(m_scHost, TRUE)))
	{
		printf("DGX_SocketNonBlocking() Failed\n");
		goto End;
	}

	// Host IP, Port 설정
	if(DGE_FAILED(DGX_SocketAddr(&m_sdHost, NULL, m_sPt)))
	{
		printf("DGX_SocketAddr() Failed\n");
		goto End;
	}


	// 5. Bind Socket
	if(DGE_FAILED(DGX_SocketBind(m_scHost, &m_sdHost)))
	{
		printf("DGX_SocketBind() Failed\n");
		goto End;
	}


	//6. Listen
	if(DGE_FAILED(DGX_SocketListen(m_scHost)))
	{
		printf("DGX_SocketListen() Failed\n");
		goto End;
	}


			
	FD_ZERO(&m_scFD);
	FD_SET(m_scHost, &m_scFD);

	// Socket을 0xFFFFFFFF 값으로 채운다.(INVALIDATE_SOCKET)
	memset(m_rmH, 0xFF, sizeof m_rmH);
	m_iNsck	= 0;
	Fd_Set(m_scHost);	// ACCEPT 소켓을 추가함

	m_fdMax = m_scHost;


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

