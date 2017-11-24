// Implementation of the IDGX_Input.
//
////////////////////////////////////////////////////////////////////////////////

// GP wiz Key Mapping
//	/* function 2 */
//	#define	GPX_VK_UP			(1<<0)	
//	#define	GPX_VK_UP_LEFT		(1<<1)	
//	#define	GPX_VK_LEFT			(1<<2)	
//	#define	GPX_VK_DOWN_LEFT	(1<<3)	
//	#define	GPX_VK_DOWN			(1<<4)	
//	#define	GPX_VK_DOWN_RIGHT	(1<<5)	
//	#define	GPX_VK_RIGHT		(1<<6)	
//	#define	GPX_VK_UP_RIGHT		(1<<7)	
//	/* function 1 */
//	#define	GPX_VK_START		(1<<8)	
//	#define	GPX_VK_SELECT		(1<<9)	
//	#define	GPX_VK_FL			(1<<10)	
//	#define	GPX_VK_FR			(1<<11)	
//	#define	GPX_VK_FA			(1<<12)	
//	#define	GPX_VK_FB			(1<<13)	
//	#define	GPX_VK_FX			(1<<14)	
//	#define	GPX_VK_FY			(1<<15)	
//
//	#define	GPX_VK_VOL_UP		(1<<16)	
//	#define	GPX_VK_VOL_DOWN		(1<<17)	
//	#define GPX_VK_TAT			(1<<18)
//	#define GPX_VK_USB_CON		(1<<19)	
//
//	#define GPX_VK_FUNC			(1<<20)


#if defined(_WIN32) || defined(WIN32)
	#if _MSC_VER >= 1200
	#pragma warning(disable: 4996)
	#endif

	#include <windows.h>

#endif


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <DGE_Type.h>
#include <DGE_Base.h>
#include <DGE_Input10.h>

#include "DGX_Input.h"


class CDGX_Input : public IDGX_Input
{
public:
	static DGE_DEVICE	m_devKey;					// Key Device Handle
	static DGE_HWND		m_hWnd	;					// Window Handle. Need Window Application

#if defined(_WIN32) || defined(WIN32)
	static DGE_HANDLE	m_DevTs	;					// Touch Device Handle
#else
	static struct tsdev* m_DevTs;					// Touch Device Handle
#endif

protected:
	PDGE_DEVICE	m_pDev		;

	INT			m_bAct;

	BYTE		m_KeyCur[DGXINPUT_MAX_KEY];			// Current Keyboard
	BYTE		m_KeyOld[DGXINPUT_MAX_KEY];			// Old Keyboard
	BYTE		m_KeyMap[DGXINPUT_MAX_KEY];			// Key Map down: INPUTST_DOWN, up: INPUTST_UP, Press INPUTST_PRESS

	BYTE		m_TsbCur[DGXINPUT_MAX_TSB];			// Touch Screen Current Button
	BYTE		m_TsbOld[DGXINPUT_MAX_TSB];			// Old Bttton
	BYTE		m_TsbMap[DGXINPUT_MAX_TSB];			// Button Map down: INPUTST_DOWN, up: INPUTST_UP, Press INPUTST_PRESS 

	FLOAT		m_vAjCur[3];						// Analog Joystick Current Position
	FLOAT		m_vAjOld[3];						// Analog Joystick Old Position
	FLOAT		m_vAjGrd[3];						// Delta Ajs Position

	FLOAT		m_vTsCur[3];						// Tsb Current Position
	FLOAT		m_vTsOld[3];						// Tsb Old Position
	FLOAT		m_vTsGrd[3];						// Delta Tsb Position

public:
	CDGX_Input();
	virtual ~CDGX_Input();

	virtual INT			Update();				// Input Update
	virtual const BYTE* const GetKeyMap()const{	return (BYTE*)m_KeyMap;				}
	virtual const BYTE* const GetTsbMap()const{	return (BYTE*)m_TsbMap;				}
	virtual DGE_STATE	KeyDown(INT nKey)	{	if(!m_bAct) return 0;	return (DGXINPUT_KEYDOWN == m_KeyMap[nKey])? 1: 0;	}
	virtual DGE_STATE	KeyUp(INT nKey)		{	if(!m_bAct) return 0;	return (DGXINPUT_KEYUP   == m_KeyMap[nKey])? 1: 0;	}
	virtual DGE_STATE	KeyPress(INT nKey)	{	if(!m_bAct) return 0;	return (DGXINPUT_KEYPRESS== m_KeyMap[nKey])? 1: 0;	}
	virtual DGE_STATE	KeyState(INT nKey)	{	return m_KeyMap[nKey];				}

	virtual DGE_STATE	TsbDown(INT nTsb=0)	{	if(!m_bAct) return 0;	return (DGXINPUT_KEYDOWN == m_TsbMap[nTsb])? 1: 0;	}
	virtual DGE_STATE	TsbUp(INT nTsb=0)	{	if(!m_bAct) return 0;	return (DGXINPUT_KEYUP   == m_TsbMap[nTsb])? 1: 0;	}
	virtual DGE_STATE	TsbPress(INT nTsb=0){	if(!m_bAct) return 0;	return (DGXINPUT_KEYPRESS== m_TsbMap[nTsb])? 1: 0;	}
	virtual DGE_STATE	TsbState(INT nTsb=0){	return m_TsbMap[nTsb];				}

	virtual const FLOAT* const GetAjsPos()const	{	return m_vAjCur;				}
	virtual const FLOAT* const GetAjsGrd()const	{	return m_vAjOld;				}
	virtual DGE_STATE	IsAjsMove()				{	if(!m_bAct) return 0;	return (m_vAjCur != m_vAjOld)? 1:0;	}

	virtual const FLOAT* const GetTsbPos()const	{	return m_vTsCur;				}
	virtual const FLOAT* const GetTsbGrd()const	{	return m_vTsGrd;				}
	virtual DGE_STATE	IsTsbMove()				{	if(!m_bAct) return 0;	return (m_vTsCur != m_vTsOld)? 1:0;	}

	virtual void		SetCurKey(BYTE* pKey, INT iLen = DGXINPUT_MAX_KEY);
	virtual void		SetCurTsb(BYTE* pTsb, INT iLen = DGXINPUT_MAX_TSB);
	virtual void		SetTsbPos(FLOAT* vcPos);
	virtual DGE_STATE	IsInRect(INT left, INT top, INT right, INT bottom);

	virtual void		Reset();
	virtual void		SetActive(INT bAct=TRUE)	{	m_bAct = bAct;	}
	virtual INT			GetActive()					{	return m_bAct;	}

public:
	INT		Create(void* =0, void* =0, void* =0, void* =0);
	void	Destroy();
};



DGE_DEVICE	 CDGX_Input::m_devKey = -1;				// Key Device Handle
DGE_HWND	CDGX_Input::m_hWnd   = NULL;			// Window Handle. Need Window Application

#if defined(_WIN32) || defined(WIN32)
	DGE_HANDLE	CDGX_Input::m_DevTs = NULL;			// Touch Device Handle
#else
	struct tsdev* CDGX_Input::m_DevTs = NULL;		// Touch Device Handle
#endif

	

CDGX_Input::CDGX_Input()
{
	m_pDev	= NULL;		//
	m_hWnd	= NULL;		// Window Handle. Need Window Application

	memset(m_KeyCur, 0, DGXINPUT_MAX_KEY );
	memset(m_KeyOld, 0, DGXINPUT_MAX_KEY );
	memset(m_KeyMap, 0, DGXINPUT_MAX_KEY );

	memset(m_TsbCur, 0, DGXINPUT_MAX_TSB );
	memset(m_TsbOld, 0, DGXINPUT_MAX_TSB );
	memset(m_TsbMap, 0, DGXINPUT_MAX_TSB );

	memset(&m_vAjCur, 0, sizeof m_vAjCur );
	memset(&m_vAjOld, 0, sizeof m_vAjOld );

	memset(&m_vTsCur, 0, sizeof m_vTsCur );
	memset(&m_vTsOld, 0, sizeof m_vTsOld );

	m_bAct = TRUE;
}


CDGX_Input::~CDGX_Input()
{
	Destroy();
}

void CDGX_Input::Destroy()
{
	DGE_InputClose();
}



INT CDGX_Input::Create(void* p1, void* p2, void* p3, void* p4)
{
	INT		hr = 0;

	hr = DGE_InputOpen(p2);
	if(DGE_FAILED(hr))
	{
		printf("Err: %d, %s \t", __LINE__, __FILE__);
		printf("DGX_InputOpen() Failed\n");
		return DGE_ECANNOTACQUIRE_DEVICE;
	}

	
	m_pDev	= (PDGE_DEVICE)p1;
	m_hWnd	= (DGE_HWND)p2;

	if(m_pDev)
		m_pDev->SetInput(this);

	return DGE_OK;
}


INT	CDGX_Input::Update()
{
	INT				hr;
	INT				n;
	DGE_INPUT_AJS	aj;
	DGE_INPUT_TS	ts;

	memcpy(m_KeyOld, m_KeyCur,	DGXINPUT_MAX_KEY);
	memset(m_KeyCur,	 0,		DGXINPUT_MAX_KEY);
	memset(m_KeyMap,	 0,		DGXINPUT_MAX_KEY);

	// Read Ajs
	hr = DGE_InputReadAjs(&aj);
	{
		m_vAjCur[0] = (FLOAT)aj.x;
		m_vAjCur[1] = (FLOAT)aj.y;
	}


	// Read key-button
	hr = DGE_InputReadKey(m_KeyCur);



	// Touch Screen Data
#if defined(_WIN32) || defined(WIN32)

	memcpy(m_TsbOld, m_TsbCur,	DGXINPUT_MAX_TSB);
	memset(m_TsbCur, 0,			DGXINPUT_MAX_TSB);
	memset(m_TsbMap, 0,			DGXINPUT_MAX_TSB);

	// Read
	hr = DGE_InputReadTsb(&ts);
	{
		m_vTsCur[0] = (FLOAT)ts.x;
		m_vTsCur[1] = (FLOAT)ts.y;
		m_TsbCur[0] = ts.st;
	}

	// setup
	for(n=0; n<DGXINPUT_MAX_TSB; ++n)
		m_TsbCur[n] = m_TsbCur[n] ? 1: 0;

	for(n=0; n<DGXINPUT_MAX_TSB; ++n)
	{
		INT nOld = m_TsbOld[n];
		INT nCur = m_TsbCur[n];

		if		(0 == nOld && 1 ==nCur)	m_TsbMap[n] = DGXINPUT_KEYDOWN;		// Down
		else if	(1 == nOld && 0 ==nCur)	m_TsbMap[n] = DGXINPUT_KEYUP;		// Up
		else if	(1 == nOld && 1 ==nCur)	m_TsbMap[n] = DGXINPUT_KEYPRESS;	// Press
	}

#else

	// Read
	hr = DGE_InputReadTsb(&ts);

	// 장치 Error
	if(0>hr)
		return -1;


	// Setup
	m_TsbOld[0] = m_TsbCur[0];

	if(0<hr)							// Event 가 있을 때만 처리
	{
		m_vTsCur[0] = (FLOAT)ts.x;
		m_vTsCur[1] = (FLOAT)ts.y;
		m_TsbCur[0] = ts.st;
	}

	if( m_TsbCur[0] == 1)
	{
		if(m_TsbOld[0] == m_TsbCur[0])
		{
			m_TsbMap[0] = DGXINPUT_KEYPRESS;
			//printf("Ts Press\n");			
		}
		else
		{			
			m_TsbMap[0] = DGXINPUT_KEYDOWN;
			//printf("Ts Down\n");
		}
	}
	else if(m_TsbCur[0] == 0)
	{
		if(m_TsbOld[0] == m_TsbCur[0])
		{
			m_TsbMap[0] = DGXINPUT_KEYNONE;
		}
		else
		{
			m_TsbMap[0] = DGXINPUT_KEYUP;
//			printf("Ts Up\n");
		}
	}

#endif

	////////////////////////////////////////////////////////////////////////////


	// setup Keyboard data
	for(n=0; n<DGXINPUT_KEY_TOTAL; ++n)
		m_KeyCur[n] = m_KeyCur[n] ? 1: 0;

	for(n=0; n<DGXINPUT_MAX_KEY; ++n)
	{
		INT nOld = m_KeyOld[n];
		INT nCur = m_KeyCur[n];

		if		(0 == nOld && 1 ==nCur)	m_KeyMap[n] = DGXINPUT_KEYDOWN;		// Down
		else if	(1 == nOld && 0 ==nCur)	m_KeyMap[n] = DGXINPUT_KEYUP;		// Up
		else if	(1 == nOld && 1 ==nCur)	m_KeyMap[n] = DGXINPUT_KEYPRESS;	// Press
	}


	////////////////////////////////////////////////////////////////////////////



	// Update Analog Joystick  Data
	m_vAjGrd[0] = m_vAjCur[0] - m_vAjOld[0];
	m_vAjGrd[1] = m_vAjCur[1] - m_vAjOld[1];
	m_vAjGrd[2] = m_vAjCur[2] - m_vAjOld[2];

	m_vAjOld[0] = m_vAjCur[0];
	m_vAjOld[1] = m_vAjCur[1];
	m_vAjOld[2] = m_vAjCur[2];


	// Update Touch Screen Data
	m_vTsGrd[0] = m_vTsCur[0] - m_vTsOld[0];
	m_vTsGrd[1] = m_vTsCur[1] - m_vTsOld[1];
	m_vTsGrd[2] = m_vTsCur[2] - m_vTsOld[2];

	m_vTsOld[0] = m_vTsCur[0];
	m_vTsOld[1] = m_vTsCur[1];
	m_vTsOld[2] = m_vTsCur[2];

	return DGE_OK;
}


void CDGX_Input::SetCurKey(BYTE* pKey, INT iLen)
{
	INT i =0;
	INT n = DGXINPUT_MAX_KEY;

	if(n> iLen)
		n= iLen;

	for(i=0; i<n; ++i)
		m_KeyCur[i] = pKey[i];
}

void CDGX_Input::SetCurTsb(BYTE* pTsb, INT iLen)
{
	INT i =0;
	INT n = DGXINPUT_MAX_KEY;

	if(n> iLen)
		n= iLen;

	for(i=0; i<n; ++i)
		m_TsbCur[i] = pTsb[i];
}


void CDGX_Input::SetTsbPos(FLOAT* vcPos)
{
	m_vTsCur[0] = vcPos[0];
	m_vTsCur[1] = vcPos[1];
	m_vTsCur[2] = vcPos[2];
}



DGE_STATE CDGX_Input::IsInRect(INT left, INT top, INT right, INT bottom)
{
	if(!m_bAct)
		return 0;

	return (	m_vTsCur[0]>=left
			&&	m_vTsCur[1]>=top
			&&	m_vTsCur[0]<=right
			&&	m_vTsCur[1]<=bottom);
}



void CDGX_Input::Reset()
{
	memset(m_KeyCur, 0, sizeof(m_KeyCur));
	memset(m_KeyOld, 0, sizeof(m_KeyOld));
	memset(m_KeyMap, 0, sizeof(m_KeyMap));

	memset(m_TsbCur, 0, sizeof(m_TsbCur));
	memset(m_TsbOld, 0, sizeof(m_TsbOld));
	memset(m_TsbMap, 0, sizeof(m_TsbMap));

	memset(&m_vTsCur, 0, sizeof(m_vTsCur));
	memset(&m_vTsOld, 0, sizeof(m_vTsOld));
}


INT DGX_CreateInput(char* sCmd
				   , PDGX_INPUT* pData
				   , DGE_HANDLE p1		// Window Handle
				   , DGE_HANDLE p2		// User Data(Option)
				   , DGE_HANDLE p3		// No Use
				   , DGE_HANDLE p4		// No Use
					 )
{
	CDGX_Input* pObj = NULL;
	*pData = NULL;

	pObj = new CDGX_Input;
	if(DGE_FAILED(pObj->Create(p1, p2, p3, p4)))
	{
		delete pObj;
		return DGE_ECANNOTALLOCATED;
	}

	(*pData) = pObj;
	return DGE_OK;
}



INT DGX_DestroyInput(PDGX_INPUT* pData)
{
	if(NULL == *pData)
		return DGE_OK;

	delete *pData;
	(*pData) = NULL;

	return DGE_OK;
}




