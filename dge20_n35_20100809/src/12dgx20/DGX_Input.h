//	Copyright(C) Gamepark Holdings. All rights reserved.
//	Dogma-G Game Studios In-House Library DGE
//
// Interface for the IDGX_Input class.
//
////////////////////////////////////////////////////////////////////////////////


#if defined(_WIN32) || defined(WIN32)
	#if _MSC_VER > 1000
	#pragma once
	#endif
#endif


#ifndef _DGX_Input_H_
#define _DGX_Input_H_

#include <DGE_Type.h>


enum EDGX_INPUT
{
	DGXINPUT_DEFAULT	= 0xFFFF,
	DGXINPUT_READ_WAIT	= -1,
	DGXINPUT_READ_COMPLETE	= 0,


	// Type
	DGXINPUT_NONE		= 0,
	DGXINPUT_WIZ		= 3,

	// State
	DGXINPUT_KEYNONE	= 0,
	DGXINPUT_KEYDOWN	= 1,
	DGXINPUT_KEYUP		= 2,
	DGXINPUT_KEYPRESS	= 3,

	// Constant
	DGXINPUT_MAX_KEY	= 32,
	DGXINPUT_MAX_TSB	= 4,
	DGXINPUT_KEY_TOTAL	= 18,


	// Wiz Key Map
	DGXKEY_UP		= 0,	// 'W'

	DGXKEY_UP_LEFT	= 1,	// 'E'
	DGXKEY_U_L		= 1,	// UP-LEFT
	
	DGXKEY_LEFT		= 2,	// 'D'

	DGXKEY_DOWN_LEFT= 3,	// 'X'
	DGXKEY_D_L		= 3,	// DOWN-LEFT

	DGXKEY_DOWN		= 4,	// 'S'

	DGXKEY_DOWN_RIGHT=5,	// 'Z'
	DGXKEY_D_R		= 5,	// DOWN-RIGHT

	DGXKEY_RIGHT	= 6,	// 'A'

	DGXKEY_UP_RIGHT	= 7,	// 'Q'
	DGXKEY_U_R		= 7,	// UP-RIGHT

	DGXKEY_START	= 8,	// VK_LSHIFT
	DGXKEY_MENU		= 8,	// VK_LSHIFT
	DGXKEY_SELECT	= 9,	// VK_RSHIFT

	DGXKEY_FL		= 10,	// VK_LCONTROL
	DGXKEY_FR		= 11,	// VK_RCONTROL
	DGXKEY_FA		= 12,	// VK_LEFT
	DGXKEY_FB		= 13,	// VK_RIGHT
	DGXKEY_FX		= 14,	// VK_DOWN
	DGXKEY_FY		= 15,	// VK_UP

	DGXKEY_VOL_UP	= 16,	// VK_PRIOR(Page up)  only for wiz
	DGXKEY_VOL_DOWN	= 17,	// VK_NEXT(Page down) only for wiz

	DGXKEY_TAT		= 18,	// VK_TAB Joystic tact

	DGXKEY_HELP1	= 8,	// for caanoo corresponding to wiz start  VK_LSHIFT
	DGXKEY_HELP2	= 9,	// for caanoo corresponding to wiz select VK_RSHIFT

	DGXKEY_HOME		= 21,	// VK_HOME
	DGXKEY_HOLD		= 22,	// VK_END

	DGXKEY_USB_CON	= 19,
	DGXKEY_FUNC		= 20,
};

interface IDGX_Input
{
	DGE_CLASS_DESTROYER(	IDGX_Input	);

	virtual INT			Update()=0;					// Input Update
	virtual const BYTE* const GetKeyMap()const=0;	// Key+Button Map
	virtual const BYTE* const GetTsbMap()const=0;	// Touch Screen Map

	virtual DGE_STATE	KeyDown(INT nKey)=0;
	virtual DGE_STATE	KeyUp(INT nKey)=0;
	virtual DGE_STATE	KeyPress(INT nKey)=0;
	virtual DGE_STATE	KeyState(INT nKey)=0;

	virtual DGE_STATE	TsbDown(INT nTsb=0)=0;
	virtual DGE_STATE	TsbUp(INT nTsb=0)=0;
	virtual DGE_STATE	TsbPress(INT nTsb=0)=0;
	virtual DGE_STATE	TsbState(INT nTsb=0)=0;

	virtual const FLOAT* const GetAjsPos()const=0;	// Analog Joystick Position Need FLOAT x 3
	virtual const FLOAT* const GetAjsGrd()const=0;	// Gradient of Analog Joystick Need FLOAT x 3
	virtual DGE_STATE	IsAjsMove()=0;

	virtual const FLOAT* const GetTsbPos()const=0;	// Touch Screen Position Need FLOAT x 3
	virtual const FLOAT* const GetTsbGrd()const=0;	// Gradient of Touch Screen Need FLOAT x 3
	virtual DGE_STATE	IsTsbMove()=0;

	virtual void		SetCurKey(BYTE* pKey, INT iLen = DGXINPUT_MAX_KEY)=0;
	virtual void		SetCurTsb(BYTE* pTsb, INT iLen = DGXINPUT_MAX_TSB)=0;
	virtual void		SetTsbPos(FLOAT* vcPos)=0;

	virtual DGE_STATE	IsInRect(INT left, INT top, INT right, INT bottom)=0;

	virtual void		Reset()=0;
	virtual void		SetActive(INT bActive=TRUE)=0;		// return input values only active state.
	virtual INT			GetActive()=0;
};


typedef IDGX_Input*	PDGX_INPUT;


// Create Key, Touch Screen Input Controller
// 내부에서 저 수준 입출력 함수 DGX_Input***()를 사용해서 처리
// 장치의 사용 초기화 함
INT DGX_CreateInput(char* sCmd
				   , PDGX_INPUT* pData
				   , DGE_HANDLE p1				// Window Handle
				   , DGE_HANDLE p2 = NULL		// User Data(Option)
				   , DGE_HANDLE p3 = NULL		// No Use
				   , DGE_HANDLE p4 = NULL		// No Use
					 );

// Destroy Input Controller: 장치의 사용 해제됨(저 수준과 혼용 주의)
INT DGX_DestroyInput(PDGX_INPUT* pData);


#endif


