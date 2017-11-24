// Implementation of the IDGX_Network.
//
////////////////////////////////////////////////////////////////////////////////


#if defined(_WIN32) || defined(WIN32)
	#if _MSC_VER >= 1200
	#pragma warning(disable: 4996)
	#endif

	#include <winsock2.h>
	#include <windows.h>

#else

	#include <errno.h>
	#include <unistd.h>
	#include <netdb.h>
	#include <arpa/inet.h>
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <sys/select.h>
	#include <sys/time.h>
	#include <sys/ioctl.h>
	#include <sys/fcntl.h>
	#include <linux/tcp.h>

#endif


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "DGX_Network.h"


INT DGX_NetDeviceOpen()
{

#if defined(_WIN32) || defined(WIN32)
	INT hr;
	WORD	wVersion;
	WSADATA wsaData;

	DWORD	iBuf =0;
	INT		nTCP[2] = {IPPROTO_TCP, IPPROTO_UDP};
 
	wVersion = MAKEWORD( 2, 2 );
 
	if ( 0 != WSAStartup( wVersion, &wsaData ))
		return DGE_EFAIL;
 
	if ( LOBYTE( wsaData.wVersion ) != 2 || HIBYTE( wsaData.wVersion ) != 2 )
	{
		WSACleanup();
		return DGE_EFAIL; 
	}

	// 버퍼의 크기만 반환하고 에러를 발생해야 된다.
	hr = WSAEnumProtocols(0, 0, &iBuf);

	if( (DGE_SOCKET_ERROR != hr) && (WSAENOBUFS != WSAGetLastError()) )
	{
		WSACleanup();
		return DGE_EFAIL;
	}

	LPWSAPROTOCOL_INFO	pProtoInfo = (LPWSAPROTOCOL_INFO)malloc(iBuf);

	hr = WSAEnumProtocols(nTCP, pProtoInfo, &iBuf);
	free(pProtoInfo);

	if(DGE_SOCKET_ERROR ==hr)
	{
		WSACleanup();
		return DGE_EFAIL; 
	}

#else
	// 1. USB에 연결 되어 있는지 확인
	// 2. IP 확인
	

#endif

	return DGE_OK;
}

INT	DGX_NetDeviceClose()
{
#if defined(_WIN32) || defined(WIN32)
	WSACleanup();
#endif


	return DGE_OK;
}




INT DGX_SocketAddr(SOCKADDR_IN* pOut, char* sIp, char* sPort)
{
	memset(pOut, 0, sizeof(SOCKADDR_IN));
	pOut->sin_family=AF_INET;

	pOut->sin_addr.s_addr = (sIp) ? inet_addr(sIp): htonl(INADDR_ANY);
	pOut->sin_port=htons(atoi(sPort));
	
	return DGE_OK;
}

INT	DGX_SocketClose(SOCKET* scH)
{
	if(DGE_INVALID_SOCKET != *scH)
	{
#if defined(_WIN32) || defined(WIN32)
		::shutdown(*scH, SD_BOTH);
		::closesocket(*scH);
#else
		::shutdown(*scH, SHUT_RDWR);
		::close(*scH);
#endif

		*scH = DGE_INVALID_SOCKET;
	}

	return DGE_OK;
}

INT	DGX_SocketTcpCreate(SOCKET* pScH)
{
	BOOL	bReUse = TRUE;
	LINGER  stLinger={1,0};

	
	*pScH = socket(AF_INET, SOCK_STREAM, 0);
	
	if(DGE_INVALID_SOCKET == *pScH)
		return -1;



	// set SO_LINGER to off
	// do not linger on close waiting for unsent data to be sent
#if defined(_WIN32) || defined(WIN32)
	BOOL	bDontLinger = TRUE;
	if(DGE_SOCKET_ERROR == setsockopt(*pScH, SOL_SOCKET, SO_DONTLINGER, (const char*)&bDontLinger, sizeof(BOOL)))
		return -1;
#endif

	
	if(DGE_SOCKET_ERROR == setsockopt(*pScH, SOL_SOCKET, SO_LINGER, (const char*)&stLinger, sizeof(LINGER)))
		return -1;

	// set to SO_REUSEADDR
	// allow socket to be bound to an address that is already in use 

	if(DGE_SOCKET_ERROR == setsockopt(*pScH, SOL_SOCKET, SO_REUSEADDR, (const char*)&bReUse, sizeof(BOOL)))
		return -1;
	

	return DGE_OK;
}

INT	DGX_SocketUdpCreate(SOCKET* pScH)
{
	BOOL	bReUse = TRUE;
	LINGER  stLinger={1,0};

	
	*pScH = socket(AF_INET, SOCK_DGRAM, 0);
	
	if(DGE_INVALID_SOCKET == *pScH)
		return -1;


	// set SO_LINGER to off
	// do not linger on close waiting for unsent data to be sent
#if defined(_WIN32) || defined(WIN32)
	BOOL	bDontLinger = TRUE;
	if(DGE_SOCKET_ERROR == setsockopt(*pScH, SOL_SOCKET, SO_DONTLINGER, (const char*)&bDontLinger, sizeof(BOOL)))
		return -1;
#endif

	
	if(DGE_SOCKET_ERROR == setsockopt(*pScH, SOL_SOCKET, SO_LINGER, (const char*)&stLinger, sizeof(LINGER)))
		return -1;

	// set to SO_REUSEADDR
	// allow socket to be bound to an address that is already in use 

	if(DGE_SOCKET_ERROR == setsockopt(*pScH, SOL_SOCKET, SO_REUSEADDR, (const char*)&bReUse, sizeof(BOOL)))
		return -1;

	return DGE_OK;
}

INT	DGX_SocketConnect(SOCKET scH, SOCKADDR_IN* psdH)
{
	INT	hr=-1;

	hr = connect(scH, (SOCKADDR*)psdH, sizeof(SOCKADDR_IN));
	
	// 소켓이 비동기일 경우 이것을 반드시 확인
	if(DGE_SOCKET_ERROR == hr)
	{
		INT er;
#if defined(_WIN32) || defined(WIN32)
		er = WSAGetLastError();
		if( !(WSA_IO_PENDING ==er || WSAEWOULDBLOCK==er || WSAEISCONN==er) )
#else
		er  = errno	;
		if( EWOULDBLOCK !=er )
#endif
		{
			printf("Err: %d, %s \t", __LINE__, __FILE__);
			printf( "connect() Failed\n");
			return DGE_SOCKET_ERROR;
		}

		hr = DGE_OK;
	}

	return DGE_OK;
}

INT	DGX_SocketBind(SOCKET scH, SOCKADDR_IN* pSdH)
{
	INT hr=-1;

	hr = bind(scH, (SOCKADDR*)pSdH, sizeof(SOCKADDR_IN));

	if(DGE_SOCKET_ERROR == hr)
	{
		INT er;
#if defined(_WIN32) || defined(WIN32)
		er = WSAGetLastError();
		if( !(WSA_IO_PENDING ==er || WSAEWOULDBLOCK==er || WSAEISCONN==er) )
#else
		er  = errno	;
		if( EWOULDBLOCK !=er )
#endif
		{
			printf("Err: %d, %s \t", __LINE__, __FILE__);
			printf( "bind() Failed\n");
			return DGE_EFAIL;
		}
	}

	return DGE_OK;
}

INT	DGX_SocketListen(SOCKET scH)
{
	INT hr=-1;

	hr = listen(scH, SOMAXCONN);

	if(DGE_SOCKET_ERROR == hr)
	{
		INT er;
#if defined(_WIN32) || defined(WIN32)
		er = WSAGetLastError();
		if( !(WSA_IO_PENDING ==er || WSAEWOULDBLOCK==er || WSAEISCONN==er) )
#else
		er  = errno	;
		if( EWOULDBLOCK !=er )
#endif
		{
			printf("Err: %d, %s \t", __LINE__, __FILE__);
			printf( "listen() Failed\n");
			return DGE_EFAIL;
		}
	}

	return DGE_OK;
}



INT DGX_SocketSend(SOCKET s, const char* b, int l, int f)
{
	INT hr=-1;

	hr = ::send(s, b, l, f);

	if(DGE_SOCKET_ERROR == hr)
	{
		INT er;
#if defined(_WIN32) || defined(WIN32)
		er = WSAGetLastError();
		if( !(WSA_IO_PENDING ==er || WSAEWOULDBLOCK==er || WSAEISCONN==er) )
#else
		er  = errno	;
		if( EWOULDBLOCK !=er )
#endif
		{
			printf("Err: %d, %s \t", __LINE__, __FILE__);
			printf( "Socket Send() Failed\n");
			return DGE_SOCKET_ERROR;
		}

		return DGE_OK;
	}
	else if( 0 == hr)
		return DGE_SOCKET_ERROR;


	return hr;
}

INT	DGX_SocketRecv(SOCKET s, char* b, int l, int f)
{
	INT hr=-1;

	hr = ::recv(s, b, l, f);

	if(DGE_SOCKET_ERROR == hr)
	{
		INT er;
#if defined(_WIN32) || defined(WIN32)
		er = WSAGetLastError();
		if( !(WSA_IO_PENDING == er || WSAEWOULDBLOCK== er || WSAEISCONN==er) )
#else
		er  = errno	;
		if( EWOULDBLOCK != er )
#endif
		{
			printf("Err: %d, %s \t", __LINE__, __FILE__);
			printf( "Socket Recv() Failed\n");
			return DGE_SOCKET_ERROR;
		}

		return DGE_OK;
	}
	else if( 0 == hr)
		return DGE_SOCKET_ERROR;

	return hr;
}


INT	DGX_SocketAccept(SOCKET* pscOut			// Output Socket
					, SOCKADDR_IN* psdOut	// Output Socket Address
					, SOCKET scListen		// Listen socket
					)						// Accept

{
	*pscOut = DGE_INVALID_SOCKET;

	SOCKET	scCln=0;

#if defined(_WIN32) || defined(WIN32)
	INT				iSizeAdd = sizeof(SOCKADDR_IN);
#else
	unsigned int	iSizeAdd = sizeof(SOCKADDR_IN);
#endif

	scCln = ::accept(scListen, (SOCKADDR*)psdOut, &iSizeAdd);
	
	// 리슨소켓이 비동기의 경우
	if(DGE_SOCKET_ERROR == scCln || DGE_INVALID_SOCKET ==scCln)
	{
		INT er;
#if defined(_WIN32) || defined(WIN32)
		er = WSAGetLastError();
		if( !(WSA_IO_PENDING ==er || WSAEWOULDBLOCK==er || WSAEISCONN==er) )
#else
		er  = errno	;
		if( EWOULDBLOCK !=er )
#endif
		{
			printf("Err: %d, %s \t", __LINE__, __FILE__);
			printf( "accept() Failed\n");
			return DGE_SOCKET_ERROR;
		}

		// 비동기모드로 계속 돌고 있다.
		return DGE_OK;
	}

	*pscOut = scCln;
	return DGE_OK;
}



INT DGX_SocketSelect(INT nFDS, FD_SET* pFdRead, FD_SET* pFdWrite, FD_SET* pFdExcept, TIMEVAL* timeout)
{
	INT hr=-1;

	hr = ::select(nFDS, pFdRead, pFdWrite, pFdExcept, timeout);

	if(DGE_SOCKET_ERROR == hr)
	{
		INT er;
#if defined(_WIN32) || defined(WIN32)
		er = WSAGetLastError();
		if( !(WSA_IO_PENDING ==er || WSAEWOULDBLOCK==er || WSAEISCONN==er) )
#else
		er  = errno	;
		if( EWOULDBLOCK != er || EINTR != er)
#endif
		{
			printf("Err: %d, %s \t", __LINE__, __FILE__);
			printf( "Socket Select() Failed\n");
			return DGE_SOCKET_ERROR;
		}

		return DGE_OK;
	}

	return DGE_OK;
}


INT DGX_SocketNonBlocking(SOCKET scH, BOOL bOn)
{
	u_long on =bOn? 1: 0;
#if defined(_WIN32) || defined(WIN32)
	return ioctlsocket(scH, FIONBIO, &on);
#else
//	fcntl(scH, F_SETFL, O_NONBLOCK);
	return ioctl(scH, FIONBIO, &on);
#endif
}

INT DGX_SocketNaggleOff(SOCKET scH, BOOL bOff)
{
	BOOL bNagle = bOff? 1: 0; // Nagle 알고리즘 작동 중지
	return setsockopt(scH, IPPROTO_TCP, TCP_NODELAY, (char*)&bNagle, sizeof bNagle);
}


INT DGX_SocketRecvTimeOut(SOCKET scH, INT timeOut)
{
	TIMEVAL v={ timeOut, 0};
	return setsockopt(scH, SOL_SOCKET, SO_RCVTIMEO, (const char*)&v, sizeof v);
}

INT DGX_SocketSendTimeOut(SOCKET scH, INT timeOut)
{
	TIMEVAL v={ timeOut, 0};
	return setsockopt(scH, SOL_SOCKET, SO_SNDTIMEO, (const char*)&v, sizeof v);
}

INT DGX_SocketDirectBuffer(SOCKET scH)
{
	INT nZero=0;
	return setsockopt(scH, SOL_SOCKET, SO_SNDBUF, (const char*)&nZero, sizeof nZero);
}


INT DGX_LocalIpAddress(char* sIp/*IP List*/, INT* piN/*IP Count*/, INT* iWidth)
{
	SOCKADDR_IN sdH;
	HOSTENT*	pHost=0;
	char		sHost[512];
	INT			i=0;

	INT nIp=0;
	INT	nWs=16;

	memset(sHost, 0, sizeof sHost);

	if(::gethostname(sHost, sizeof sHost))
		return -1;

	pHost = ::gethostbyname(sHost);

	if(!pHost)
		return -1;

	//설마 네트워크 IP 32개 이상 가진 녀석은 없을 것!!!!!
	for(i=0;pHost->h_addr_list[i] && i<32; ++i)
	{
		memcpy(&sdH.sin_addr, pHost->h_addr_list[i], pHost->h_length);
		strcpy(sIp + i* (nWs), inet_ntoa(sdH.sin_addr));
		++nIp;
	}

	if(piN)
		*piN = nIp;

	if(iWidth)
		*iWidth = nWs;


	return 0;
}


