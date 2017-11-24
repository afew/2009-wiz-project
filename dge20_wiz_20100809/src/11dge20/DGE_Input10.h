// Copyright(C) Gamepark Holdings. All rights reserved.
// Dogma-G Game Studios In-House Library DGE
//
// DGE Input 1.0: Touch Screen, Button.
//
////////////////////////////////////////////////////////////////////////////////


#if defined(_WIN32) || defined(WIN32)
	#if _MSC_VER > 1000
	#pragma once
	#endif
#endif


#ifndef _DGE_Input_H_
#define _DGE_Input_H_


#ifdef __cplusplus
extern "C" {
#endif


enum EDGE_INPUT
{
	DGEINPUT_DEFAULT	= 0xFFFF,
	DGEINPUT_READ_WAIT	= -1,
	DGEINPUT_READ_COMPLETE	= 0,


	// Type
	DGEINPUT_NONE		= 0,
	DGEINPUT_WIZ		= 3,

	// State
	DGEINPUT_KEYNONE	= 0,
	DGEINPUT_KEYDOWN	= 1,
	DGEINPUT_KEYUP		= 2,
	DGEINPUT_KEYPRESS	= 3,

	// Constant
	DGEINPUT_MAX_KEY	= 32,
	DGEINPUT_MAX_TSB	= 4,
	DGEINPUT_KEY_TOTAL	= 18,


	// Wiz Key Map
	DGEKEY_UP		= 0,	// 'W'

	DGEKEY_UP_LEFT	= 1,	// 'E'
	DGEKEY_U_L		= 1,	// UP-LEFT
	
	DGEKEY_LEFT		= 2,	// 'D'

	DGEKEY_DOWN_LEFT= 3,	// 'X'
	DGEKEY_D_L		= 3,	// DOWN-LEFT

	DGEKEY_DOWN		= 4,	// 'S'

	DGEKEY_DOWN_RIGHT=5,	// 'Z'
	DGEKEY_D_R		= 5,	// DOWN-RIGHT

	DGEKEY_RIGHT	= 6,	// 'A'

	DGEKEY_UP_RIGHT	= 7,	// 'Q'
	DGEKEY_U_R		= 7,	// UP-RIGHT

	DGEKEY_START	= 8,	// VK_LSHIFT
	DGEKEY_MENU		= 8,	// VK_LSHIFT

	DGEKEY_SELECT	= 9,	// VK_RSHIFT

	DGEKEY_FL		= 10,	// VK_LCONTROL
	DGEKEY_FR		= 11,	// VK_RCONTROL
	DGEKEY_FA		= 12,	// VK_LEFT
	DGEKEY_FB		= 13,	// VK_RIGHT
	DGEKEY_FX		= 14,	// VK_DOWN
	DGEKEY_FY		= 15,	// VK_UP

	DGEKEY_VOL_UP	= 16,	// VK_PRIOR(Page up)  only for wiz
	DGEKEY_VOL_DOWN	= 17,	// VK_NEXT(Page down) only for wiz

	DGEKEY_TAT		= 18,	// VK_TAB Joystic tact

	DGEKEY_HELP1	= 8,	// for caanoo corresponding to wiz start  VK_LSHIFT
	DGEKEY_HELP2	= 9,	// for caanoo corresponding to wiz select VK_RSHIFT

	DGEKEY_HOME		= 21,	// VK_HOME
	DGEKEY_HOLD		= 22,	// VK_END

	DGEKEY_USB_CON	= 19,
	DGEKEY_FUNC		= 20,
};


// Key Mapping
typedef unsigned char*	PKEYMAP;


// Touch Screen
typedef struct tagDGE_INPUT_TS
{
	int st;			// state
	int	x,y;		// Touch Screen X
}DGE_INPUT_TS;


// Analog Joy-stick
typedef struct tagDGE_INPUT_AJS
{
	int st;			// state: DGEINPUT_READ_WAIT or DGEINPUT_READ_COMPLETE
	int	x,y;		// Joy-stick x, y
}DGE_INPUT_AJS;


int DGE_InputOpen10(void* hWnd);			// Input 장치 사용 초기화. hWnd는 MS 윈도우에만 필요. 처리한 Event 숫자 반환. Event 숫자가 0이면 내부에서 처리한 것이 없음.
int DGE_InputClose10();						// Input 장치 사용 해제

int DGE_InputReadAjs10(DGE_INPUT_AJS* ajs);	// 2차원 x,y 반환[-127, 127], y 상단: 127, y 하단: -127
int DGE_InputReadTsb10(DGE_INPUT_TS* ts);	// Touch Screen 장치의 데이터 획득(st !=0 Event true, Screen X position, Screen Y position)
int DGE_InputReadKey10(PKEYMAP p);			// Keypad의 데이터 획득(unsigned char 32개 이상: 최소 32byte)




#define DGE_InputOpen		DGE_InputOpen10
#define DGE_InputClose		DGE_InputClose10

#define DGE_InputReadAjs	DGE_InputReadAjs10
#define DGE_InputReadTsb	DGE_InputReadTsb10
#define DGE_InputReadKey	DGE_InputReadKey10



#ifdef __cplusplus
}
#endif


#endif //_DGE_Input_H_

