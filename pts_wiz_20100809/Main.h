// Interface for the CMain class.
//
////////////////////////////////////////////////////////////////////////////////


#if defined(_WIN32) || defined(WIN32)
	#if _MSC_VER > 1000
		#pragma once
	#endif
#endif


#ifndef _CMain_H_
#define _CMain_H_


class CMain : public CAppDge
{
protected:
	PDGX_INPUT		m_pInput;		// Input
	INT				m_bReset;

protected:
	CGpLogo			m_pGpLogo;
	CGpTitle		m_pGpTitle;

public:
	CGpAct			m_pGpAct;
	CGpEnding		m_pGpEnding;

protected:
	CGpOption		m_pGpOption;
	CGpStage		m_pGpStage;
	CGpDemo			m_pGpDemo;

public:
	PDGX_SOUND		m_pSndBg;

public:
	CMain();
	
	virtual INT	Init();
	virtual INT	Destroy();
	virtual INT	FrameMove();
	virtual INT	Render();

public:
	int			m_nScnSt;
	long		m_nGameFlag1[1024];
	long		m_nGameFlag2[1024];
	long		m_nDebugDisp;
	long		m_nDebugStageProduct;

protected:
	int		m_nTickPrv;
	int		m_nTickCur;
	long	m_dSoundVol;

public:
	int		system_keys();
	void	FPSWait();

	int		IsPressKey(INT nKey);
	int		IsPushKey(INT nKey);
	int		IsPushOKKey();
	int		IsPushCancelKey();

	void	Loading(int n);
};

extern	CMain*	g_pApp;
#define	GMAIN	g_pApp


extern	PDGE_SPRITE	g_pSprite;
extern	PDGE_DEVICE	g_pDevice;



int		GetSceneState();				// Scene state
void	SetSceneState(int nState);		// Scene state

long	GetSceneDebugDisp();
long	GetSceneDebugStateProduct();

long*	GetSceneGameFlag1();
long*	GetSceneGameFlag2();

long	GetSceneGameFlag1(int nIdx);
void	SetSceneGameFlag1(int nIdx, int v);

long	GetSceneGameFlag2(int nIdx);
void	SetSceneGameFlag2(int nIdx, int v);


void	ResetGameFlag();
void	ResetGameFlag2();
int		LoadGameFlag( char *fn );
int		SaveGameFlag( char *fn );
int		LoadGameFlag2( char *fn );
int		SaveGameFlag2( char *fn );


#endif


