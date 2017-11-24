

#include "_StdAfx.h"


CGpLogo::CGpLogo()
{
	m_bExit	= 0;
	m_nDemo	= 0;

	m_pTex		= NULL;
	m_dAlpVal	= 1;
	m_dAlpDir	= 5;
}


CGpLogo::~CGpLogo()
{
}


int CGpLogo::Init()
{
	m_bExit = 1;
	m_nDemo = 0;

	DWORD	dColorKey = 0xFF10633E;
	LoadImage(&m_pTex, (char*)"image/a_logo.png",dColorKey);


	m_dTimeBgn = DGE_GetTickCount();

	return 0;
}



void CGpLogo::Destroy()
{
	ReleaseImage(&m_pTex);
}


int CGpLogo::Update()
{
	int dTimeCur= DGE_GetTickCount();

	if(m_dAlpVal>0)
	{
		if((m_dTimeBgn + 1)<dTimeCur)
		{
			m_dTimeBgn = dTimeCur;

			m_dAlpVal += m_dAlpDir;

			if(m_dAlpVal>255)
			{
				m_dAlpVal = 255;
				m_dAlpDir = -5;
			}
		}
	}

	if(m_dAlpVal == 255)
	{
		g_pApp->Loading(0);
		g_pApp->Loading(1);
		g_pApp->Loading(2);
	}

	if(0 >= m_dAlpVal)
	{
		SetSceneGameFlag1(40, 0);					/* ?ƒCƒgƒ‹ */
		SetSceneState(EN_SN_TITLE);
		m_bExit=0;
	}

	return m_bExit;
}

void CGpLogo::Render()
{
	DGXCOLOR dColor(1,1,1, m_dAlpVal/255.5F);
	DWORD d = dColor;
	Blt(m_pTex, 50, 50, d);
}





