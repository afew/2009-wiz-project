// Interface for the CAppDge class.
//
////////////////////////////////////////////////////////////////////////////////


#if defined(_WIN32) || defined(WIN32)
	#if _MSC_VER > 1000
	#pragma once
	#endif
#endif


#ifndef _AppDge_H_
#define _AppDge_H_


class CAppDge : public IDGE_AppFrame
{
protected:
	DGE_HANDLE		m_hWnd		;				// Window Handle
	PDGE_DEVICE		m_pDev		;				// DGE_DEVICE

	char			m_sCls[128]	;				// Program Class Name

	INT				m_nScnW		;				// Screen Width
	INT				m_nScnH		;				// Screen Height

	DOUBLE			m_fElapsed	;				// Elapsed Time
	FLOAT			m_fFPS		;				// Frame Per Second

public:
	CAppDge();

	virtual INT	Init()		{	return 0;	}
	virtual INT	Destroy()	{	return 0;	}
	virtual INT	FrameMove()	{	return 0;	}
	virtual INT	Render()	{	return 0;	}

	virtual INT	Query(char*, void*){	return -1;	}

	virtual INT	Create(DGE_HANDLE =NULL, DGE_HANDLE =NULL, DGE_HANDLE =NULL, DGE_HANDLE =NULL);
	virtual INT	Run();

	INT		Render3D();
	LRESULT MsgProc(DGE_HWND,UINT,WPARAM,LPARAM);	// Window Procedure

public:
	static CAppDge*	m_pAppDge;
	static INT	   DGE_CALLBACK Run3D(DGE_HANDLE);						// Main Processing
	static LRESULT DGE_WINAPI	WndProc(DGE_HWND,UINT,WPARAM,LPARAM);	// Window Procedure
protected:
	INT		Cleanup();
	void	UpdateStatus();

public:
	FLOAT	GetFPS()			{	return m_fFPS;		}
	DOUBLE	GetElapsedTime()	{	return m_fElapsed;	}
};


#endif

