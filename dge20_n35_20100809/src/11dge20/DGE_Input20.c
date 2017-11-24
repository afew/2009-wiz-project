// Implementation of the DGE Input.
//
////////////////////////////////////////////////////////////////////////////////

#if defined(_WIN32) || defined(WIN32)
	#if _MSC_VER >= 1200
	#pragma warning(disable: 4996)
	#endif
#endif


#if defined(_WIN32) || defined(WIN32)
	#include <windows.h>
#else
	#include <unistd.h>
	#include <signal.h>
	#include <fcntl.h>

	#include <sys/ioctl.h>
	#include <sys/mman.h>
	#include <sys/time.h>
	#include <linux/input.h>

	#include <tslib.h>	// Touch Screen Lib

	#include <sys/types.h>
	#include <sys/poll.h>
	#include <pthread.h>


	#define JOYSTICK_FNAME		"/dev/input/event1"
	#define POLL_DEVICE_NUM 1
	#define POLL_INDEX_JOYSTICK 0
	#define MAX_EVENTS 64

#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>


#define DGE_OK						0x00000000
#define DGE_EFAIL					-1
#define DGE_ECANNOTACQUIRE_DEVICE	0XF0000005
#define DGE_INVALID_DEVICE			-1


//Key Definition..
#define N35_BTN_LEFT        0x124
#define N35_BTN_RIGHT       0x125
#define N35_BTN_A           0x120
#define N35_BTN_B           0x122
#define N35_BTN_X           0x121
#define N35_BTN_Y           0x123
#define N35_BTN_I           0x128
#define N35_BTN_II          0x129
#define N35_BTN_HOME        0x126
#define N35_BTN_ANALOG      0x12A
#define N35_BTN_HOLD        0x127


#include "DGE_Input20.h"


//#define CENTER_THRESHOLD 150
//#define CENTER_POS_VAL	511
#define CENTER_THRESHOLD (40)
#define CENTER_POS_VAL	(128)		//0x80


#if defined(_WIN32) || defined(WIN32)
	static void*	g_InputHwnd = NULL;						// Window Handle. Need Window Application
#else

	typedef enum
	{
		DIRECTION_CENTER	= -1,
		DIRECTION_UP		= 0,
		DIRECTION_DOWN		= 4,
		DIRECTION_LEFT		= 2,
		DIRECTION_RIGHT		= 6,
		DIRECTION_UP_LEFT	= 1,
		DIRECTION_UP_RIGHT	= 7,
		DIRECTION_DOWN_LEFT = 3,
		DIRECTION_DOWN_RIGHT= 5,
	} direction_t ;


//	static int			g_InputKey = DGE_INVALID_DEVICE;	// Key Device Handle
	static struct tsdev* g_InputTs = NULL;					// Touch Device Handle
	static int			g_InputAjs = DGE_INVALID_DEVICE;	// Analog joy-stick Handle

	static int			g_InputAjsX  = 0x80;				// Complete Position of X
	static int			g_InputAjsY  = 0x80;				// Complete Position of Y
	static int			g_InputAjsXt = 0x80;				// Temp Position of X
	static int			g_InputAjsYt = 0x80;				// Temp Position of Y

	static int			g_InputAjsE =DIRECTION_CENTER;		// Ajs Complete Emulating for 8-button

	pthread_t			g_InputAjsThread;					// Ajs Thread
	int					g_InputAjsThreadID;					// Ajs Thread ID

	static int			g_InputTbsX  = 0x0;					// Complete Touch Screeb Position of X
	static int			g_InputTbsY  = 0x0;					// Complete Touch Screeb Position of Y
	static int			g_InputTbsT  = 0x0;					// Touch State

	static int			g_InputKey[32] = {0};				// Touch State


#endif




#define DISTANCE_SQUARE_VALUE (CENTER_THRESHOLD * CENTER_THRESHOLD)
int check_distance_from_origin(int x, int y)
{
	int x_square = x * x;
	int y_square = y * y;

	if( (x_square + y_square) < DISTANCE_SQUARE_VALUE)
		return 0;

	return 1;
}

int calculate_direction_by_angle(int x_in, int y_in) 
{
	int x, y;
	int angle_percent;

	x = x_in - CENTER_POS_VAL;
	y = y_in - CENTER_POS_VAL;
	y = -y;


	//(x, y) position is in  near-by center position
	if(!check_distance_from_origin(x, y))
		return DIRECTION_CENTER;


	//handle zero value...
	if(!x || !y)
	{
		if(x < 0)
			return DIRECTION_LEFT;		// y is zero

		else if(0 < x)
			return DIRECTION_RIGHT;		// y is zero

		else if(y < 0)
			return DIRECTION_DOWN;

		else if(0 < y)
			return DIRECTION_UP;		// x is zero

		else 
			return DIRECTION_CENTER;	 // all x, y are zero
	}

	angle_percent = (y * 100) / x;
	//printf("angle_percent = %d\n", angle_percent);
	if((-25 <= angle_percent) && (angle_percent < 25)) {	//left or right
		if(x < 0) 
			return DIRECTION_LEFT;
		else 
			return DIRECTION_RIGHT;
	} else if((25 <= angle_percent) && (angle_percent < 400)) { // left-down, or right up
		if(x < 0)
			return DIRECTION_DOWN_LEFT;
		else 
			return DIRECTION_UP_RIGHT;
	} else if((-400 < angle_percent) && (angle_percent < -25)) { //left-up or right-down
		if(x < 0)
			return DIRECTION_UP_LEFT;
		else 
			return DIRECTION_DOWN_RIGHT;
	} else {
		if(0 < y) 
			return DIRECTION_UP;
		else 
			return DIRECTION_DOWN;
	}

	//calculate angle 

}


#if !defined(_WIN32) && !defined(WIN32)

// Pthread - 대부분의 시간을 poll()함수의 waiting으로 소비 -> CPU 점유율 낮음.
void *thread_polling_joystick(void * data)
{
//	int receive_flag = 0;

	struct input_event event[MAX_EVENTS];
	struct pollfd poll_event[POLL_DEVICE_NUM];
	int poll_result;
	int read_byte;
	int event_number;
	int i;
	int key_value=0;

	//set-up polling events..
	poll_event[POLL_INDEX_JOYSTICK].fd = g_InputAjs;
	poll_event[POLL_INDEX_JOYSTICK].events = POLLIN;


	while(1)
	{
		poll_result = poll((struct pollfd *) &poll_event, 1, 20);

		if(poll_result < 0)
		{
			//poll error
			printf("poll - error...\n");
			exit(EXIT_FAILURE);
		}

		if(poll_result == 0)
		{		
			//there is no event in 50 milliseconds... 
			continue;
		}
		
		if(poll_event[POLL_INDEX_JOYSTICK].revents & POLLIN)
		{
			read_byte = read(g_InputAjs, event, sizeof(event));
			event_number = read_byte / sizeof(struct input_event);

			//printf("event_number : %d\n", event_number);

			for(i = 0; i < event_number ; ++i)
			{
				if (event[i].type == EV_ABS)
				{
					switch (event[i].code)
					{
						case ABS_X:
							// receive_flag |= 0x01;
							g_InputAjsXt = event[i].value;
						break;

						case ABS_Y:
							// receive_flag |= 0x02;
						    g_InputAjsYt = event[i].value;
						break;
					}
				}

				else if(event[i].type == EV_SYN)
				{
					// printf("%d.%03d ", event[i].time.tv_sec, event[i].time.tv_usec / 1000); 

					//if(receive_flag & 0x01)	printf("x : %d ", g_InputAjsXt);
					//if(receive_flag & 0x02)	printf("y : %d ", g_InputAjsYt);
					//printf("\n");
					// receive_flag = 0;

					g_InputAjsX = g_InputAjsXt;
					g_InputAjsY = g_InputAjsYt;

					//printf("event sync is complete -------> update position value\n  %d.%03d x : 0x%x %d, y : 0x%x %d\n",	event[i].time.tv_sec, 
					//												event[i].time.tv_usec / 1000, 
					//												g_InputAjsX, g_InputAjsX,g_InputAjsY, g_InputAjsY);
					//												

					g_InputAjsE = calculate_direction_by_angle(g_InputAjsX, g_InputAjsY);

				}

				else if(event[i].type == EV_KEY)
				{
					key_value = event[i].value;

					switch(event[i].code)
					{
						case N35_BTN_LEFT :	g_InputKey[DGEKEY_FL	] =	key_value;	break;
						case N35_BTN_RIGHT:	g_InputKey[DGEKEY_FR	] =	key_value;	break;
						case N35_BTN_A:		g_InputKey[DGEKEY_FA	] =	key_value;	break;
						case N35_BTN_B:		g_InputKey[DGEKEY_FB	] =	key_value;	break;
						case N35_BTN_X:		g_InputKey[DGEKEY_FX	] =	key_value;	break;
						case N35_BTN_Y:		g_InputKey[DGEKEY_FY	] =	key_value;	break;
						case N35_BTN_I:		g_InputKey[DGEKEY_HELP1	] =	key_value;	break;
						case N35_BTN_II:	g_InputKey[DGEKEY_HELP2	] =	key_value;	break;
						case N35_BTN_HOME:	g_InputKey[DGEKEY_HOME	] =	key_value;	break;
						case N35_BTN_ANALOG:g_InputKey[DGEKEY_TAT	] =	key_value;	break;
						case N35_BTN_HOLD:	g_InputKey[DGEKEY_HOLD	] =	key_value;	break;
					}
				}
			}
		}
	}
}


#endif







int DGE_InputOpen20(void*	hWnd)
{
#if defined(_WIN32) || defined(WIN32)
	g_InputHwnd = hWnd;

#else
	// struct input_event event={0};

	// Open Ajs..
	if(g_InputAjs<0)
	{
		g_InputAjs = open(JOYSTICK_FNAME, O_RDONLY| O_NONBLOCK);

		if(g_InputAjs < 0)
		{
			printf("Err: %d, %s \t", __LINE__, __FILE__);
			printf("Couldn't open Analog Joystic.\n");
			return DGE_INVALID_DEVICE;
		}

		// Call read...
		// nEvent = read(g_InputAjs, g_InputAjs_E, sizeof(g_InputAjs_E));
		// printf("Ajs Open Success\n");

		g_InputAjsThreadID = pthread_create(&g_InputAjsThread, NULL, thread_polling_joystick, NULL);
		pthread_detach(g_InputAjsThread);

		if(g_InputAjsThreadID < 0) {
			perror("thread create error...\n");
			exit(0);
		}
	}


	// Open Touch Screen
	if(NULL == g_InputTs)
	{
		// 터치 드라이버 오픈
		g_InputTs = ts_open("/dev/input/event0",  O_RDONLY | O_NDELAY );
		if(!g_InputTs)
		{
			printf("Err: %d, %s \t", __LINE__, __FILE__);
			printf( "Touch Screen Open Failed\n");
			return DGE_INVALID_DEVICE;
		}

		printf("Touch Screen open Success\n");


		// TS 라이브러리 초기화
		if (ts_config(g_InputTs))
		{
			printf("Err: %d, %s \t", __LINE__, __FILE__);
			printf( "Touch Screen Config Failed\n");
			return DGE_INVALID_DEVICE;
		}

		printf("Touch Screen Config Success\n");
	}
	
	
	// Open Key...
//	if(g_InputKey<0)
//	{
//		g_InputKey = open("/dev/GPIO", O_RDONLY | O_NDELAY );
//
//		if( 0> g_InputKey)
//		{
//			printf("Err: %d, %s \t", __LINE__, __FILE__);
// 			printf( "Key Open Failed\n");
//			return DGE_INVALID_DEVICE;
//		}
//
//		printf("Key Open Success\n");
//	}

	printf("Key Open Success\n");
#endif

	return DGE_OK;
}


int DGE_InputClose20()
{
#if defined(_WIN32) || defined(WIN32)
	g_InputHwnd = NULL;
#else
	if(DGE_INVALID_DEVICE != g_InputAjs)
	{
		close(g_InputAjs);
		g_InputAjs = DGE_INVALID_DEVICE;
	}

	if(g_InputTs)
	{
		ts_close(g_InputTs);
		g_InputTs = NULL;
	}

//	if(DGE_INVALID_DEVICE != g_InputKey)
//	{
//		close(g_InputKey);
//		g_InputKey = DGE_INVALID_DEVICE;
//	}
#endif

	printf("Input Close Success\n");

	return DGE_OK;
}




int DGE_InputReadAjs20(DGE_INPUT_AJS* ajs)
{
#if defined(_WIN32) || defined(WIN32)
	return DGE_INVALID_DEVICE;
#else
	int hr		= DGEINPUT_READ_COMPLETE;

	ajs->x = g_InputAjsX;
	ajs->y = g_InputAjsY;
	ajs->st= g_InputAjsE;

	// printf("Read Ajs: %3d %3d %+2d\n", g_InputAjsX, g_InputAjsY, g_InputAjsE); 

	return hr;
#endif
}


int DGE_InputReadTsb20(DGE_INPUT_TS* ts)
{
	int		hr = DGE_OK;

	ts->x = DGEINPUT_DEFAULT;
	ts->y = DGEINPUT_DEFAULT;
	ts->st =DGEINPUT_DEFAULT;


#if defined(_WIN32) || defined(WIN32)

	POINT pt={0};

	if(NULL == g_Input10Hwnd || g_Input10Hwnd != GetActiveWindow() )
		return DGE_ECANNOTACQUIRE_DEVICE;

	GetCursorPos(&pt);
	ScreenToClient(g_Input10Hwnd, &pt);

	ts->x = pt.x;
	ts->y = pt.y;
	ts->st = (GetAsyncKeyState(VK_LBUTTON) & 0x8000) ? 1: 0;	// Wiz는 LButton만 활성화

	return hr;
#else

	// Use TS struct and Read TS Coordinate
	struct ts_sample samp={0};
	hr = ts_read(g_InputTs, &samp, 1);

	// Device Error
	if(0>hr)
	{
		printf("Err: %d, %s \t", __LINE__, __FILE__);
		printf( "Touch Screen Read Failed\n");
		return DGE_ECANNOTACQUIRE_DEVICE;
	}


	// 0 == hr → No Event
	// 0  < hr → Receave Event
	if(0<hr)
	{
		g_InputTbsX  = samp.x;					// Complete Touch Screeb Position of X
		g_InputTbsY  = samp.y;					// Complete Touch Screeb Position of Y
		g_InputTbsT  = samp.pressure? 1: 0;		// Touch State
	}

	ts->x = g_InputTbsX;
	ts->y = g_InputTbsY;
	ts->st= g_InputTbsT;

	// printf("%ld.%06ld: %6d %6d %6d\n", samp.tv.tv_sec, samp.tv.tv_usec, samp.x, samp.y, samp.pressure);
#endif
	return DGE_OK;
}


int DGE_InputReadKey20(PKEYMAP pOut)
{
	int			hr=0;
	unsigned long k=0;
	int			n=0;


#if defined(_WIN32) || defined(WIN32)

	void*		hAct = NULL;
	unsigned short	Key = 0;
	unsigned char	KeyCur[256]={0};


	if(NULL == pOut || NULL == g_InputHwnd)
		return DGE_ECANNOTACQUIRE_DEVICE;

	if(g_InputHwnd != GetActiveWindow() )
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

	pOut[DGEKEY_TAP		 ] = KeyCur[VK_TAB	];

	pOut[DGEKEY_HELP1	 ] = KeyCur[VK_LSHIFT];
	pOut[DGEKEY_HELP2	 ] = KeyCur[VK_RSHIFT];

	pOut[DGEKEY_HOME	 ] = KeyCur[VK_HOME	];
	pOut[DGEKEY_HOLD	 ] = KeyCur[VK_END	];

#else

	if(NULL == pOut)
		return DGE_ECANNOTACQUIRE_DEVICE;




	// Wiz는 bit단위로 이벤트가 4byte에 기록되어 있음.
	// Keypad 를 읽어 온다.
// Old
//	hr = read( g_InputKey, &k, sizeof(unsigned long));
//	if(0>hr)
//	{
//		printf("Err: %d, %s \t", __LINE__, __FILE__);
//		printf( "key read Failed\n");
//		return DGE_ECANNOTACQUIRE_DEVICE;
//	}
//
//	for(n=0; n<32; ++n)
//		pOut[n] = ( k & (1<<n) ) ? 1: 0;



	for(n=0; n<32; ++n)
	{
		k = g_InputKey[n];
		pOut[n] = k? 1: 0;
	}



	if(0<=g_InputAjsE)
		pOut[g_InputAjsE] = 1;

#endif

	return DGE_OK;
	
}


