// Copyright(C) Gamepark Holdings. All rights reserved.
// Dogma-G Game Studios In-House Library DGE
//
// DGE Input: Analog Joystick, Touch Screen, Button.
//
////////////////////////////////////////////////////////////////////////////////


#if defined(_WIN32) || defined(WIN32)
	#if _MSC_VER > 1000
	#pragma once
	#endif
#endif


#ifndef _DGE_Input_H_
#define _DGE_Input_H_



//==============================================================================
// Defines.
//==============================================================================

enum _EN_DIRKEY_LIST
{
	DDKEY_NONE = 0,
	DDKEY_UP_LEFT,
	DDKEY_UP_RIGHT,
	DDKEY_DOWN_LEFT,
	DDKEY_DOWN_RIGHT,
	DDKEY_TOTAL
};

enum _EN_TOUCH_LIST
{
	TOUCH_NONE = 0,
	TOUCH_DOWN,
	TOUCH_UP,
	TOUCH_TOTAL
};

enum _EN_KEY_LIST {
	DKEY_UP = 0,
	DKEY_LEFT,
	DKEY_DOWN,
	DKEY_RIGHT,
	DKEY_MENU,
	DKEY_SELECT,
	DKEY_L,
	DKEY_R,
	DKEY_A,
	DKEY_B,
	DKEY_X,
	DKEY_Y,
	DKEY_VOL_UP,
	DKEY_VOL_DOWN,
	DKEY_TOTAL
};


//===============================================================================
// Define class.
//===============================================================================
class DGE_Input
{
public:
	DGE_Input ();
	~DGE_Input ();

	void Initialize ();
	void ScanInputDevice ();
	int  IsPushKey ( int iKey );
	int  IsPushKeyOnce ( int iKey );
	int  IsNeutral ();
	int  IsTouch ()		{	return m_IsTouch;	}
	int  GetTouchX ()	{	return m_iTouch_X;	}
	int  GetTouchY ()	{	return m_iTouch_Y;	}
	int  StrikeTouchArea ( int iLeft, int iTop, int iRight, int iBottom );
	int  GetExit ()		{	return m_IsExit;	}							// engine function.

private:
	int			m_KEY;
	int			m_iKeydata;
	int			m_iTouch_X;
	int			m_iTouch_Y;
	int			m_IsTouch;
	int			m_IsExit;
	int			m_aiKeyCheck [ DKEY_TOTAL ];
};


extern DGE_Input g_cInput;







#if (DGE_SDK_VER >= 0x00020000)
	#include <DGE_Input20.h>
	
	#define DGE_InputOpen		DGE_InputOpen20
	#define DGE_InputClose		DGE_InputClose20

	#define DGE_InputReadAjs	DGE_InputReadAjs20
	#define DGE_InputReadTsb	DGE_InputReadTsb20
	#define DGE_InputReadKey	DGE_InputReadKey20
#else

	#include <DGE_Input10.h>
	#define DGE_InputOpen		DGE_InputOpen10
	#define DGE_InputClose		DGE_InputClose10

	#define DGE_InputReadTsb	DGE_InputReadTsb10
	#define DGE_InputReadKey	DGE_InputReadKey10
#endif



#endif //_DGE_Input_H_


