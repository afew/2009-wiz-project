// Implementation of the DGE Input10.
//
////////////////////////////////////////////////////////////////////////////////

#if defined(_WIN32) || defined(WIN32)
	#if _MSC_VER >= 1200
	#pragma warning(disable: 4996)
	#endif

	#include <windows.h>

#else

	#include <unistd.h>
	#include <signal.h>
	#include <fcntl.h>

	#include <sys/ioctl.h>
	#include <sys/mman.h>
	#include <sys/time.h>
	#include <linux/input.h>

	// Touch Screen Lib
	#include <tslib.h>

#endif


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define DGE_OK						0x00000000
#define DGE_EFAIL					-1
#define DGE_ECANNOTACQUIRE_DEVICE	0XF0000005
#define DGE_NOEVENT					0x00000000
#define DGE_INVALID_DEVICE			-1


#include "DGE_Input10.h"


#if defined(_WIN32) || defined(WIN32)
	static void*	g_Input10Hwnd =NULL;					// Window Handle. Need Window Application
#else
	static int		g_Input10Key =DGE_INVALID_DEVICE;		// Key Device Handle
	static struct tsdev* g_Input10Ts = NULL;				// Touch Device Handle
#endif


int DGE_InputOpen10(void*	hWnd)
{
#if defined(_WIN32) || defined(WIN32)
	g_Input10Hwnd = hWnd;

#else

	// Open Touch Screen
	if(NULL == g_Input10Ts)
	{
		// 터치 드라이버 오픈
		g_Input10Ts = ts_open("/dev/input/event0",  O_RDONLY | O_NDELAY );
		if(!g_Input10Ts)
		{
			printf("Err: %d, %s \t", __LINE__, __FILE__);
			printf( "Touch Screen Open Failed\n");
			return DGE_INVALID_DEVICE;
		}

		printf("Touch Screen open Success\n");


		// TS 라이브러리 초기화
		if (ts_config(g_Input10Ts))
		{
			printf("Err: %d, %s \t", __LINE__, __FILE__);
			printf( "Touch Screen Config Failed\n");
			return DGE_INVALID_DEVICE;
		}

		printf("Touch Screen Config Success\n");
	}


	// Open Key...
	if(0>g_Input10Key)
	{
		g_Input10Key = open("/dev/GPIO", O_RDONLY | O_NDELAY );

		if( 0> g_Input10Key)
		{
			printf("Err: %d, %s \t", __LINE__, __FILE__);
 			printf( "Key Open Failed\n");
			return DGE_INVALID_DEVICE;
		}

		printf("Key Open Success\n");
	}
#endif

	return DGE_OK;
}


int DGE_InputClose10()
{
#if defined(_WIN32) || defined(WIN32)
	g_Input10Hwnd = NULL;
#else

	if(g_Input10Ts)
	{
		ts_close(g_Input10Ts);
		g_Input10Ts = NULL;
	}

	if(DGE_INVALID_DEVICE != g_Input10Key)
	{
		close(g_Input10Key);
		g_Input10Key = DGE_INVALID_DEVICE;
	}
#endif

	printf("Input Close Success\n");

	return DGE_OK;
}




int DGE_InputReadTsb10(DGE_INPUT_TS* ts)
{
	int		hr = DGE_NOEVENT;

#if defined(_WIN32) || defined(WIN32)

	POINT pt={0};

	ts->x = DGEINPUT_DEFAULT;
	ts->y = DGEINPUT_DEFAULT;
	ts->st =DGEINPUT_DEFAULT;


	if(NULL == g_Input10Hwnd || g_Input10Hwnd != GetActiveWindow() )
		return DGE_ECANNOTACQUIRE_DEVICE;

	GetCursorPos(&pt);
	ScreenToClient(g_Input10Hwnd, &pt);

	ts->x = pt.x;
	ts->y = pt.y;
	ts->st = (GetAsyncKeyState(VK_LBUTTON) & 0x8000) ? 1: 0;	// Wiz는 LButton만 활성화
	return 1;		// Window의 이벤트는 항상 있다고 가정

#else

	// Touch Screen은 TS 사용
	//TS 좌표 값을 읽어온다.
	struct ts_sample samp={0};

	ts->x = DGEINPUT_DEFAULT;
	ts->y = DGEINPUT_DEFAULT;
	ts->st= DGEINPUT_DEFAULT;

//	printf("before ts_read: %d %x %d\n", hr, g_Input10Ts, samp.pressure);

	hr = ts_read(g_Input10Ts, &samp, 1);

//	printf("after ts_read: %d %x %d\n", hr, g_Input10Ts, samp.pressure);

	if(0>hr)
	{
		printf("Err: %d, %s \t", __LINE__, __FILE__);
		printf( "Touch Screen Read Failed\n");
		return DGE_ECANNOTACQUIRE_DEVICE;
	}


//	printf("Ts: hr: %3d Event pressure: %d\n", hr, samp.pressure);

	// No Event
	if(0==hr)
		return hr;


	ts->x = samp.x;
	ts->y = samp.y;
	ts->st= samp.pressure? 1: 0;

	// printf("Ts: hr: %3d Event pressure: %d\n", hr, samp.pressure);
	// printf("%ld.%06ld: %6d %6d %6d\n", samp.tv.tv_sec, samp.tv.tv_usec, samp.x, samp.y, samp.pressure);

#endif
	return 1;
}


int DGE_InputReadKey10(PKEYMAP pOut)
{
	int			hr=0;
	unsigned long k=0;
	int			n=0;

#if defined(_WIN32) || defined(WIN32)
	unsigned short	Key = 0;
	unsigned char	KeyCur[256]={0};

	if(NULL == pOut || NULL == g_Input10Hwnd || g_Input10Hwnd != GetActiveWindow() )
		return DGE_ECANNOTACQUIRE_DEVICE;

	for(n=1; n<256; ++n)
	{
		Key = GetAsyncKeyState(n) & 0x8000;
		KeyCur[n] = (Key)? 1: 0;
	}

	pOut[DGEKEY_UP		 ] = KeyCur['W'		];
	pOut[DGEKEY_UP_LEFT	 ] = KeyCur['Q'		];
	pOut[DGEKEY_LEFT	 ] = KeyCur['A'		];
	pOut[DGEKEY_DOWN_LEFT] = KeyCur['Z'		];
	pOut[DGEKEY_DOWN	 ] = KeyCur['S'		];
	pOut[DGEKEY_DOWN_RIGHT]= KeyCur['X'		];
	pOut[DGEKEY_RIGHT	 ] = KeyCur['D'		];
	pOut[DGEKEY_UP_RIGHT ] = KeyCur['E'		];

	pOut[DGEKEY_MENU	 ] = KeyCur[VK_LSHIFT];
	pOut[DGEKEY_SELECT	 ] = KeyCur[VK_RSHIFT];

	pOut[DGEKEY_FL		 ] = KeyCur[VK_LCONTROL];
	pOut[DGEKEY_FR		 ] = KeyCur[VK_RCONTROL];
	pOut[DGEKEY_FA		 ] = KeyCur[VK_LEFT	];
	pOut[DGEKEY_FB		 ] = KeyCur[VK_RIGHT];
	pOut[DGEKEY_FX		 ] = KeyCur[VK_DOWN	];
	pOut[DGEKEY_FY		 ] = KeyCur[VK_UP	];

	pOut[DGEKEY_VOL_UP	 ] = KeyCur[VK_PRIOR];
	pOut[DGEKEY_VOL_DOWN ] = KeyCur[VK_NEXT ];

	pOut[DGEKEY_TAT		 ] = KeyCur[VK_TAB	];

	pOut[DGEKEY_HELP1	 ] = KeyCur[VK_LSHIFT];
	pOut[DGEKEY_HELP2	 ] = KeyCur[VK_RSHIFT];

	pOut[DGEKEY_HOME	 ] = KeyCur[VK_HOME	];
	pOut[DGEKEY_HOLD	 ] = KeyCur[VK_END	];
#else

	// Wiz는 bit단위로 이벤트가 4byte에 기록되어 있음.
	// Keypad 를 읽어 온다.
	hr = read(g_Input10Key, &k, sizeof(unsigned long));
	if(0>hr)
	{
		printf("Err: %d, %s \t", __LINE__, __FILE__);
		printf( "key read Failed\n");
		return DGE_ECANNOTACQUIRE_DEVICE;
	}

	for(n=0; n<32; ++n)
		pOut[n] = ( k & (1<<n) ) ? 1: 0;

#endif

	return DGE_OK;
}




int DGE_InputReadAjs10(DGE_INPUT_AJS* ajs)
{
	ajs->x = 0xFFFF;
	ajs->y = 0xFFFF;
	ajs->st= -1;

	return -1;
}



