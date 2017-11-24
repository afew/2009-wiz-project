//	Copyright(C) Gamepark Holdings. All rights reserved.
//	Dogma-G Game Studios In-House Library DGE
//
// Interface for the IDGX_Network class.
//
////////////////////////////////////////////////////////////////////////////////


#if defined(_WIN32) || defined(WIN32)
	#if _MSC_VER > 1000
	#pragma once
	#endif
#endif


#ifndef _DGX_Network_H_
#define _DGX_Network_H_


#define __need_timeval

#include <DGE_Type.h>


#if !( defined(_WIN32) || defined(WIN32) )
	#include <netdb.h>
	#include <arpa/inet.h>

	typedef	int				SOCKET;
	typedef sockaddr		SOCKADDR;
	typedef sockaddr_in		SOCKADDR_IN;
	typedef fd_set			FD_SET;
	typedef timeval			TIMEVAL;
	typedef hostent			HOSTENT;
	typedef linger			LINGER;

#endif



enum EDGE_NETWORK
{
	DGE_INVALID_SOCKET	= (SOCKET)(~0),
	DGE_SOCKET_ERROR	= (-1),
};


INT		DGX_NetDeviceOpen();			// Network Device Open
INT		DGX_NetDeviceClose();			// Network Device Close

// Socket Creation
INT		DGX_SocketAddr(SOCKADDR_IN* pOut, char* sIp, char* sPort);	// Setting Socket Address
INT		DGX_SocketClose(SOCKET* scH);								// Socket Close
INT		DGX_SocketTcpCreate(SOCKET* pScH);							// Create TCP Socket
INT		DGX_SocketUdpCreate(SOCKET* pScH);							// Create UDP Socket

INT		DGX_SocketConnect(SOCKET scH, SOCKADDR_IN* psdH);			// Connection
INT		DGX_SocketBind(SOCKET scH, SOCKADDR_IN* pSdH);				// Socket Binding
INT		DGX_SocketListen(SOCKET scH);								// Socket Listen

// Accept
INT		DGX_SocketAccept(SOCKET* pscOut			// Output Socket
						, SOCKADDR_IN* psdOut	// Output Socket Address
						, SOCKET scListen		// Listen socket
						);

INT		DGX_SocketSend(SOCKET scH, const char* Buf, int len, int flags);	// Data(Buffer) Send (Write)
INT		DGX_SocketRecv(SOCKET scH, char* Buf, int len, int flags);			// Data(Buffer) Receive (Read)


// I/O Model
INT		DGX_SocketSelect(INT nFDS, FD_SET* pFdRead, FD_SET* pFdWrite, FD_SET* pFdExcept, TIMEVAL* timeout);	// Select I/O Model


// Socket Option
INT		DGX_SocketNonBlocking(SOCKET scH, BOOL bOn=TRUE);	// Set NonBlocking
INT		DGX_SocketNaggleOff(SOCKET scH, BOOL bOff=TRUE);	// Off nagle Algorithm
INT		DGX_SocketRecvTimeOut(SOCKET scH, INT v);			// Recv time Out(Second)
INT		DGX_SocketSendTimeOut(SOCKET scH, INT v);			// Send time Out(Second)

INT		DGX_SocketDirectBuffer(SOCKET scH);					// Disable send buffering on the socket

INT		DGX_LocalIpAddress(	char* sIp						// List
							,	INT* piN=NULL				// Count
							,	INT* iWidth=NULL);			// Get Local Ip Addresses






#endif



