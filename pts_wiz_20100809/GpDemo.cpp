

#include "_StdAfx.h"


extern char* g_sSndBgm[8];
extern char* g_sSndSe[20];


CGpDemo::CGpDemo()
{
	m_bExit	= 0;
	m_nDemo	= 0;

	m_iDemoProcess		= 0;
	m_iDemoProcessSub	= 0;
	m_iDemoTimeCounter	= 0;
	m_iDemoAlphaCounter	= 0;
	memset(m_aiDemoAlphaCounter, 0, sizeof(m_aiDemoAlphaCounter));


	memset(m_vTex, 0, sizeof(m_vTex));
	memset(m_vBgt, 0, sizeof(m_vBgt));
	memset(m_vMst, 0, sizeof(m_vMst));
}


CGpDemo::~CGpDemo()
{
}


int CGpDemo::Init()
{
	int		i=0;

	m_bExit = 1;
	m_nDemo	= 0;

	m_iDemoProcess		= 0;
	m_iDemoProcessSub	= 0;
	m_iDemoTimeCounter	= 0;
	m_iDemoAlphaCounter	= 0;
	memset(m_aiDemoAlphaCounter, 0, sizeof(m_aiDemoAlphaCounter));


	LoadImage(&m_vTex[0], (char*)"image/demo/mesh.png", TRUE);				//プレ?ンナンバ?２にシステ?用ＢＭＰを読み込む

	int nFlag120 = GetSceneGameFlag1(120);


	// Demo Index
	if( nFlag120 > 0 && nFlag120 <= 10)			// 01
		m_nDemo	= 0;

	else if( nFlag120 > 10 && nFlag120 <= 20)	// 11
		m_nDemo	= 1;

	else if( nFlag120 > 20 && nFlag120 <= 30)	// 21
		m_nDemo	= 2;

	else if( nFlag120 > 30 && nFlag120 <= 40)	// 31
		m_nDemo	= 3;

	else if( nFlag120 > 40 && nFlag120 <= 50)	// 41
		m_nDemo	= 4;


	// load images.
	m_vTex[1]= g_pApp->m_pGpAct.m_vTex[110 + m_nDemo];

	if(0 == m_nDemo)
	{
		LoadImage2(&m_vBgt[ 0].pTex, (char*)"image/demo/demo_p_01_01.png");
		LoadImage2(&m_vBgt[ 1].pTex, (char*)"image/demo/demo_p_01_02.png");
		LoadImage2(&m_vBgt[ 2].pTex, (char*)"image/demo/demo_p_01_03.png");
		LoadImage2(&m_vBgt[ 3].pTex, (char*)"image/demo/demo_p_01_04.png");
		LoadImage2(&m_vBgt[ 4].pTex, (char*)"image/demo/demo_p_01_05.png");
		LoadImage2(&m_vBgt[ 5].pTex, (char*)"image/demo/demo_p_01_06.png");
		LoadImage2(&m_vBgt[ 6].pTex, (char*)"image/demo/demo_p_01_07.png");
		LoadImage2(&m_vBgt[ 7].pTex, (char*)"image/demo/demo_p_01_08.png");
		LoadImage2(&m_vBgt[ 8].pTex, (char*)"image/demo/demo_p_01_09.png");
		LoadImage2(&m_vBgt[ 9].pTex, (char*)"image/demo/demo_p_01_10.png");

		LoadImage2(&m_vBgt[10].pTex, (char*)"image/demo/demo_p_01_11.png");
		LoadImage2(&m_vBgt[11].pTex, (char*)"image/demo/demo_p_01_12.png");
		LoadImage2(&m_vBgt[12].pTex, (char*)"image/demo/demo_p_01_13.png");
		LoadImage2(&m_vBgt[13].pTex, (char*)"image/demo/demo_p_01_14.png");
		LoadImage2(&m_vBgt[14].pTex, (char*)"image/demo/demo_p_01_15.png");
		LoadImage2(&m_vBgt[15].pTex, (char*)"image/demo/demo_p_01_16.png");

		LoadImage2(&m_vMst[ 0].pTex, (char*)"image/demo/demo_m_01_01.png");
		LoadImage2(&m_vMst[ 1].pTex, (char*)"image/demo/demo_m_01_02.png");
		LoadImage2(&m_vMst[ 2].pTex, (char*)"image/demo/demo_m_01_03.png");
		LoadImage2(&m_vMst[ 3].pTex, (char*)"image/demo/demo_m_01_04.png");
		LoadImage2(&m_vMst[ 4].pTex, (char*)"image/demo/demo_m_01_05.png");
		LoadImage2(&m_vMst[ 5].pTex, (char*)"image/demo/demo_m_01_06.png");
		LoadImage2(&m_vMst[ 6].pTex, (char*)"image/demo/demo_m_01_07.png");
	}

	else if(1 == m_nDemo)
	{
		LoadImage2(&m_vBgt[ 0].pTex, (char*)"image/demo/demo_p_02_01.png");
		LoadImage2(&m_vBgt[ 1].pTex, (char*)"image/demo/demo_p_02_02.png");
		LoadImage2(&m_vBgt[ 2].pTex, (char*)"image/demo/demo_p_02_03.png");
		LoadImage2(&m_vBgt[ 3].pTex, (char*)"image/demo/demo_p_02_04.png");
		LoadImage2(&m_vBgt[ 4].pTex, (char*)"image/demo/demo_p_02_05.png");
		LoadImage2(&m_vBgt[ 5].pTex, (char*)"image/demo/demo_p_02_06.png");
		LoadImage2(&m_vBgt[ 6].pTex, (char*)"image/demo/demo_p_02_07.png");
		LoadImage2(&m_vBgt[ 7].pTex, (char*)"image/demo/demo_p_02_08.png");
		LoadImage2(&m_vBgt[ 8].pTex, (char*)"image/demo/demo_p_02_09.png");
		LoadImage2(&m_vBgt[ 9].pTex, (char*)"image/demo/demo_p_02_10.png");

		LoadImage2(&m_vBgt[10].pTex, (char*)"image/demo/demo_p_02_11.png");
		LoadImage2(&m_vBgt[11].pTex, (char*)"image/demo/demo_p_01_09.png");
		LoadImage2(&m_vBgt[12].pTex, (char*)"image/demo/demo_p_01_10.png");
		LoadImage2(&m_vBgt[13].pTex, (char*)"image/demo/demo_p_01_11.png");
		LoadImage2(&m_vBgt[14].pTex, (char*)"image/demo/demo_p_01_12.png");
		LoadImage2(&m_vBgt[15].pTex, (char*)"image/demo/demo_p_01_13.png");
		LoadImage2(&m_vBgt[16].pTex, (char*)"image/demo/demo_p_01_14.png");
		LoadImage2(&m_vBgt[17].pTex, (char*)"image/demo/demo_p_01_15.png");
		LoadImage2(&m_vBgt[18].pTex, (char*)"image/demo/demo_p_01_16.png");

		LoadImage2(&m_vMst[ 0].pTex, (char*)"image/demo/demo_m_02_01.png");
		LoadImage2(&m_vMst[ 1].pTex, (char*)"image/demo/demo_m_02_02.png");
		LoadImage2(&m_vMst[ 2].pTex, (char*)"image/demo/demo_m_02_03.png");
		LoadImage2(&m_vMst[ 3].pTex, (char*)"image/demo/demo_m_02_04.png");
		LoadImage2(&m_vMst[ 4].pTex, (char*)"image/demo/demo_m_02_05.png");
		LoadImage2(&m_vMst[ 5].pTex, (char*)"image/demo/demo_m_02_06.png");
		LoadImage2(&m_vMst[ 6].pTex, (char*)"image/demo/demo_m_02_07.png");
		LoadImage2(&m_vMst[ 7].pTex, (char*)"image/demo/demo_m_02_08.png");
		LoadImage2(&m_vMst[ 8].pTex, (char*)"image/demo/demo_m_02_09.png");
		LoadImage2(&m_vMst[ 9].pTex, (char*)"image/demo/demo_m_02_10.png");
	}

	else if(2 == m_nDemo)
	{
		LoadImage2(&m_vBgt[ 0].pTex, (char*)"image/demo/demo_p_03_01.png");
		LoadImage2(&m_vBgt[ 1].pTex, (char*)"image/demo/demo_p_03_02.png");
		LoadImage2(&m_vBgt[ 2].pTex, (char*)"image/demo/demo_p_03_03.png");
		LoadImage2(&m_vBgt[ 3].pTex, (char*)"image/demo/demo_p_03_04.png");
		LoadImage2(&m_vBgt[ 4].pTex, (char*)"image/demo/demo_p_03_05.png");
		LoadImage2(&m_vBgt[ 5].pTex, (char*)"image/demo/demo_p_02_08.png");
		LoadImage2(&m_vBgt[ 6].pTex, (char*)"image/demo/demo_p_02_09.png");
		
		LoadImage2(&m_vBgt[ 7].pTex, (char*)"image/demo/demo_p_01_07.png");
		LoadImage2(&m_vBgt[ 8].pTex, (char*)"image/demo/demo_p_01_09.png");
		LoadImage2(&m_vBgt[ 9].pTex, (char*)"image/demo/demo_p_01_10.png");
		LoadImage2(&m_vBgt[10].pTex, (char*)"image/demo/demo_p_01_11.png");
		LoadImage2(&m_vBgt[11].pTex, (char*)"image/demo/demo_p_01_12.png");
		LoadImage2(&m_vBgt[12].pTex, (char*)"image/demo/demo_p_01_13.png");
		LoadImage2(&m_vBgt[13].pTex, (char*)"image/demo/demo_p_01_14.png");
		LoadImage2(&m_vBgt[14].pTex, (char*)"image/demo/demo_p_01_15.png");
		LoadImage2(&m_vBgt[15].pTex, (char*)"image/demo/demo_p_01_16.png");

		LoadImage2(&m_vMst[ 0].pTex, (char*)"image/demo/demo_m_03_01.png");
		LoadImage2(&m_vMst[ 1].pTex, (char*)"image/demo/demo_m_03_02.png");
		LoadImage2(&m_vMst[ 2].pTex, (char*)"image/demo/demo_m_03_03.png");
		LoadImage2(&m_vMst[ 3].pTex, (char*)"image/demo/demo_m_03_04.png");
		LoadImage2(&m_vMst[ 4].pTex, (char*)"image/demo/demo_m_03_05.png");
		LoadImage2(&m_vMst[ 5].pTex, (char*)"image/demo/demo_m_03_06.png");
		LoadImage2(&m_vMst[ 6].pTex, (char*)"image/demo/demo_m_03_07.png");
		LoadImage2(&m_vMst[ 7].pTex, (char*)"image/demo/demo_m_03_08.png");
		LoadImage2(&m_vMst[ 8].pTex, (char*)"image/demo/demo_m_03_09.png");
		LoadImage2(&m_vMst[ 9].pTex, (char*)"image/demo/demo_m_03_10.png");
	}

	else if(3 == m_nDemo)
	{
		LoadImage2(&m_vBgt[ 0].pTex, (char*)"image/demo/demo_p_04_01.png");
		LoadImage2(&m_vBgt[ 1].pTex, (char*)"image/demo/demo_p_04_02.png");
		LoadImage2(&m_vBgt[ 2].pTex, (char*)"image/demo/demo_p_04_03.png");
		LoadImage2(&m_vBgt[ 3].pTex, (char*)"image/demo/demo_p_04_04.png");
		LoadImage2(&m_vBgt[ 4].pTex, (char*)"image/demo/demo_p_04_05.png");
		LoadImage2(&m_vBgt[ 5].pTex, (char*)"image/demo/demo_p_04_06.png");
		LoadImage2(&m_vBgt[ 6].pTex, (char*)"image/demo/demo_p_04_07.png");

		LoadImage2(&m_vBgt[ 7].pTex, (char*)"image/demo/demo_p_01_07.png");
		LoadImage2(&m_vBgt[ 8].pTex, (char*)"image/demo/demo_p_01_09.png");
		LoadImage2(&m_vBgt[ 9].pTex, (char*)"image/demo/demo_p_01_10.png");
		LoadImage2(&m_vBgt[10].pTex, (char*)"image/demo/demo_p_01_11.png");
		LoadImage2(&m_vBgt[11].pTex, (char*)"image/demo/demo_p_01_12.png");
		LoadImage2(&m_vBgt[12].pTex, (char*)"image/demo/demo_p_01_13.png");
		LoadImage2(&m_vBgt[13].pTex, (char*)"image/demo/demo_p_01_14.png");
		LoadImage2(&m_vBgt[14].pTex, (char*)"image/demo/demo_p_01_15.png");
		LoadImage2(&m_vBgt[15].pTex, (char*)"image/demo/demo_p_01_16.png");

		LoadImage2(&m_vMst[ 0].pTex, (char*)"image/demo/demo_m_04_01.png");
		LoadImage2(&m_vMst[ 1].pTex, (char*)"image/demo/demo_m_04_02.png");
		LoadImage2(&m_vMst[ 2].pTex, (char*)"image/demo/demo_m_04_03.png");
		LoadImage2(&m_vMst[ 3].pTex, (char*)"image/demo/demo_m_04_04.png");
		LoadImage2(&m_vMst[ 4].pTex, (char*)"image/demo/demo_m_04_05.png");
		LoadImage2(&m_vMst[ 5].pTex, (char*)"image/demo/demo_m_04_06.png");
		LoadImage2(&m_vMst[ 6].pTex, (char*)"image/demo/demo_m_04_07.png");
		LoadImage2(&m_vMst[ 7].pTex, (char*)"image/demo/demo_m_04_08.png");
		LoadImage2(&m_vMst[ 8].pTex, (char*)"image/demo/demo_m_04_09.png");
		LoadImage2(&m_vMst[ 9].pTex, (char*)"image/demo/demo_m_04_10.png");
	}

	else if(4 == m_nDemo)
	{
		LoadImage2(&m_vBgt[ 0].pTex, (char*)"image/demo/demo_p_05_01.png");
		LoadImage2(&m_vBgt[ 1].pTex, (char*)"image/demo/demo_p_05_02.png");
		LoadImage2(&m_vBgt[ 2].pTex, (char*)"image/demo/demo_p_05_03.png");
		LoadImage2(&m_vBgt[ 3].pTex, (char*)"image/demo/demo_p_05_04.png");
		LoadImage2(&m_vBgt[ 4].pTex, (char*)"image/demo/demo_p_05_05.png");
		LoadImage2(&m_vBgt[ 5].pTex, (char*)"image/demo/demo_p_05_06.png");
		LoadImage2(&m_vBgt[ 6].pTex, (char*)"image/demo/demo_p_05_07.png");

		LoadImage2(&m_vBgt[ 7].pTex, (char*)"image/demo/demo_p_01_07.png");
		LoadImage2(&m_vBgt[ 8].pTex, (char*)"image/demo/demo_p_01_09.png");
		LoadImage2(&m_vBgt[ 9].pTex, (char*)"image/demo/demo_p_01_10.png");
		LoadImage2(&m_vBgt[10].pTex, (char*)"image/demo/demo_p_01_11.png");
		LoadImage2(&m_vBgt[11].pTex, (char*)"image/demo/demo_p_01_12.png");
		LoadImage2(&m_vBgt[12].pTex, (char*)"image/demo/demo_p_01_13.png");
		LoadImage2(&m_vBgt[13].pTex, (char*)"image/demo/demo_p_01_14.png");
		LoadImage2(&m_vBgt[14].pTex, (char*)"image/demo/demo_p_01_15.png");
		LoadImage2(&m_vBgt[15].pTex, (char*)"image/demo/demo_p_01_16.png");

		LoadImage2(&m_vMst[ 0].pTex, (char*)"image/demo/demo_m_05_01.png");
		LoadImage2(&m_vMst[ 1].pTex, (char*)"image/demo/demo_m_05_02.png");
		LoadImage2(&m_vMst[ 2].pTex, (char*)"image/demo/demo_m_05_03.png");
		LoadImage2(&m_vMst[ 3].pTex, (char*)"image/demo/demo_m_05_04.png");
		LoadImage2(&m_vMst[ 4].pTex, (char*)"image/demo/demo_m_05_05.png");
		LoadImage2(&m_vMst[ 5].pTex, (char*)"image/demo/demo_m_05_06.png");
		LoadImage2(&m_vMst[ 6].pTex, (char*)"image/demo/demo_m_05_07.png");
		LoadImage2(&m_vMst[ 7].pTex, (char*)"image/demo/demo_m_05_08.png");
		LoadImage2(&m_vMst[ 8].pTex, (char*)"image/demo/demo_m_05_09.png");
		LoadImage2(&m_vMst[ 9].pTex, (char*)"image/demo/demo_m_05_10.png");
	}


	for(i=0; i< DEMO_IMAGE_MAX; ++i)
	{
		m_vBgt[i].SetAlpha(0);
		m_vMst[i].SetAlpha(0);
	}


	DGX_SoundRepeat(g_pApp->m_pSndBg, 1);
	DGX_SoundPlay(g_pApp->m_pSndBg);

	return 0;
}


void CGpDemo::Destroy()
{
	int i;

	ReleaseImage( &m_vTex[0]);

	for(i=0; i< DEMO_IMAGE_MAX; ++i)
	{
		ReleaseImage( &m_vBgt[i].pTex);
		ReleaseImage( &m_vMst[i].pTex);
	}

	DGX_SoundRepeat(g_pApp->m_pSndBg);
	DGX_SoundStop(g_pApp->m_pSndBg);
}



int CGpDemo::Update()
{
	if(0 == m_nDemo)
	{
		// set alpha value.
		m_iDemoAlphaCounter += 5;
		if( 255 < m_iDemoAlphaCounter )
			m_iDemoAlphaCounter = 255;

		switch ( m_iDemoProcess )
		{
		case 0:
			{
				if( 0 == m_iDemoProcessSub )
				{
					SetAlpha(&m_vBgt[0], m_iDemoAlphaCounter);

					if( 255 == m_iDemoAlphaCounter )
					{
						m_iDemoProcessSub = 10;
						m_iDemoTimeCounter = 0;
						m_iDemoAlphaCounter = 0;
					}
				}
				else if( 10 == m_iDemoProcessSub )
				{
					SetAlpha(&m_vMst[0], m_iDemoAlphaCounter);

					if( 255 <= m_iDemoAlphaCounter )
					{
						m_iDemoTimeCounter++;

						if( 80 <= m_iDemoTimeCounter )
						{
							m_iDemoProcessSub = 20;
							m_iDemoTimeCounter = 0;
							m_iDemoAlphaCounter = 0;
						}
					}
				}
				else if( 20 == m_iDemoProcessSub )
				{
					SetAlpha(&m_vBgt[1], m_iDemoAlphaCounter);

					if( 255 == m_iDemoAlphaCounter )
					{
						m_iDemoProcessSub = 30;
						m_iDemoAlphaCounter = 0;
					}
				}
				else if( 30 == m_iDemoProcessSub )
				{
					SetAlpha(&m_vBgt[2], m_iDemoAlphaCounter);

					if( 255 == m_iDemoAlphaCounter )
					{
						m_iDemoProcessSub = 40;
						m_iDemoTimeCounter = 0;
						m_iDemoAlphaCounter = 0;
					}
				}
				else if( 40 == m_iDemoProcessSub )
				{
					SetAlpha(&m_vMst[1], m_iDemoAlphaCounter);

					if( 255 <= m_iDemoAlphaCounter )
					{
						m_iDemoTimeCounter++;

						if( 80 <= m_iDemoTimeCounter )
						{
							m_iDemoProcessSub = 50;
							m_iDemoTimeCounter = 0;
							m_iDemoAlphaCounter = 0;
						}
					}
				}
				else if( 50 == m_iDemoProcessSub )
				{
					SetAlpha(&m_vBgt[3], m_iDemoAlphaCounter);

					if( 255 == m_iDemoAlphaCounter )
					{
						m_iDemoProcessSub = 60;
						m_iDemoTimeCounter = 0;
						m_iDemoAlphaCounter = 0;
					}
				}
				else if( 60 == m_iDemoProcessSub )
				{
					SetAlpha(&m_vMst[2], m_iDemoAlphaCounter);

					if( 255 <= m_iDemoAlphaCounter )
					{
						m_iDemoTimeCounter++;

						if( 80 <= m_iDemoTimeCounter )
						{
							m_iDemoProcess = 1;
							m_iDemoProcessSub = 0;
							m_iDemoTimeCounter = 0;
							m_iDemoAlphaCounter = 0;
						}
					}
				}
			}
			break;

		case 1:
			{
				if( 0 == m_iDemoProcessSub )
				{
					SetAlpha(&m_vBgt[4], m_iDemoAlphaCounter);

					if( 255 == m_iDemoAlphaCounter )
					{
						m_iDemoProcessSub = 10;
						m_iDemoTimeCounter = 0;
						m_iDemoAlphaCounter = 0;
					}
				}
				else if( 10 == m_iDemoProcessSub )
				{
					SetAlpha(&m_vMst[3], m_iDemoAlphaCounter);

					if( 255 <= m_iDemoAlphaCounter )
					{
						m_iDemoTimeCounter++;
						if( 130 <= m_iDemoTimeCounter )
						{
							m_iDemoProcess = 2;
							m_iDemoProcessSub = 0;
							m_iDemoTimeCounter = 0;
							m_iDemoAlphaCounter = 0;
						}
					}
				}
			}
			break;

		case 2:
			{
				if( 0 == m_iDemoProcessSub )
				{
					SetAlpha(&m_vBgt[5], m_iDemoAlphaCounter);

					if( 255 == m_iDemoAlphaCounter )		{	m_iDemoProcessSub = 10;		m_iDemoTimeCounter = 0;		m_iDemoAlphaCounter = 0;	}
				}
				else if( 10 == m_iDemoProcessSub )
				{
					SetAlpha(&m_vMst[4], m_iDemoAlphaCounter);
					SetAlpha(&m_vMst[5], m_iDemoAlphaCounter);

					if( 255 <= m_iDemoAlphaCounter )
					{
						m_iDemoTimeCounter++;
						if( 130 <= m_iDemoTimeCounter )		{	m_iDemoProcess = 3;		m_iDemoProcessSub = 0;	m_iDemoTimeCounter = 0;	m_iDemoAlphaCounter = 0;	}
					}
				}
			}
			break;

		case 3:
			{
				if( 0 == m_iDemoProcessSub )
				{
					SetAlpha(&m_vBgt[6], m_iDemoAlphaCounter);
					SetAlpha(&m_vBgt[7], m_iDemoAlphaCounter);

					if( 255 == m_iDemoAlphaCounter )
					{
						m_iDemoProcessSub = 10;
						m_iDemoAlphaCounter = 0;

						m_aiDemoAlphaCounter [0] = 0;
						m_aiDemoAlphaCounter [1] = -70;
						m_aiDemoAlphaCounter [2] = -140;
						m_aiDemoAlphaCounter [3] = -210;
						m_aiDemoAlphaCounter [4] = -280;
						m_aiDemoAlphaCounter [5] = -350;
						m_aiDemoAlphaCounter [6] = -420;
						m_aiDemoAlphaCounter [7] = -490;
					}
				}
				else if( 10 == m_iDemoProcessSub )
				{
					m_aiDemoAlphaCounter [0] += 5;	if( 255 < m_aiDemoAlphaCounter [0] )		m_aiDemoAlphaCounter [0] = 255;
					m_aiDemoAlphaCounter [1] += 5;	if( 255 < m_aiDemoAlphaCounter [1] )		m_aiDemoAlphaCounter [1] = 255;
					m_aiDemoAlphaCounter [2] += 5;	if( 255 < m_aiDemoAlphaCounter [2] )		m_aiDemoAlphaCounter [2] = 255;
					m_aiDemoAlphaCounter [3] += 5;	if( 255 < m_aiDemoAlphaCounter [3] )		m_aiDemoAlphaCounter [3] = 255;
					m_aiDemoAlphaCounter [4] += 5;	if( 255 < m_aiDemoAlphaCounter [4] )		m_aiDemoAlphaCounter [4] = 255;
					m_aiDemoAlphaCounter [5] += 5;	if( 255 < m_aiDemoAlphaCounter [5] )		m_aiDemoAlphaCounter [5] = 255;
					m_aiDemoAlphaCounter [6] += 5;	if( 255 < m_aiDemoAlphaCounter [6] )		m_aiDemoAlphaCounter [6] = 255;
					m_aiDemoAlphaCounter [7] += 5;	if( 255 < m_aiDemoAlphaCounter [7] )		m_aiDemoAlphaCounter [7] = 255;

					if( 0 < m_aiDemoAlphaCounter [0] )	SetAlpha(&m_vBgt[ 8], m_aiDemoAlphaCounter [0]);
					if( 0 < m_aiDemoAlphaCounter [1] )	SetAlpha(&m_vBgt[ 9], m_aiDemoAlphaCounter [1]);
					if( 0 < m_aiDemoAlphaCounter [2] )	SetAlpha(&m_vBgt[10], m_aiDemoAlphaCounter [2]);
					if( 0 < m_aiDemoAlphaCounter [3] )	SetAlpha(&m_vBgt[11], m_aiDemoAlphaCounter [3]);
					if( 0 < m_aiDemoAlphaCounter [4] )	SetAlpha(&m_vBgt[12], m_aiDemoAlphaCounter [4]);
					if( 0 < m_aiDemoAlphaCounter [5] )	SetAlpha(&m_vBgt[13], m_aiDemoAlphaCounter [5]);
					if( 0 < m_aiDemoAlphaCounter [6] )	SetAlpha(&m_vBgt[14], m_aiDemoAlphaCounter [6]);
					if( 0 < m_aiDemoAlphaCounter [7] )	SetAlpha(&m_vBgt[15], m_aiDemoAlphaCounter [7]);


					if( 255 <= m_aiDemoAlphaCounter [7] )	{	m_iDemoProcessSub = 20;	m_iDemoAlphaCounter = 0;	m_iDemoTimeCounter = 0;	}
				}
				else if( 20 == m_iDemoProcessSub )
				{
					SetAlpha(&m_vMst[6], m_iDemoAlphaCounter);

					if( 255 == m_iDemoAlphaCounter )
					{
						m_iDemoTimeCounter++;

						if(250 <= m_iDemoTimeCounter)
						{
							m_iDemoProcess = 100;
						}
					}
				}
			}
			break;

		default:
			SetSceneState(EN_SN_ACT);
			m_bExit=0;
			break;
		}
	}

	else if(1 == m_nDemo)
	{
		// set alpha value.
		m_iDemoAlphaCounter += 5;
		if( 255 < m_iDemoAlphaCounter )
			m_iDemoAlphaCounter = 255;

		switch ( m_iDemoProcess )
		{
		case 0:
			{
				if( 0 == m_iDemoProcessSub )
				{
					SetAlpha(&m_vBgt[0], m_iDemoAlphaCounter);
					SetAlpha(&m_vBgt[1], m_iDemoAlphaCounter);

					if( 255 == m_iDemoAlphaCounter )	{	m_iDemoProcessSub = 10;		m_iDemoTimeCounter = 0;		m_iDemoAlphaCounter = 0;	}
				}
				else if( 10 == m_iDemoProcessSub )
				{
					SetAlpha(&m_vMst[0], m_iDemoAlphaCounter);

					if( 255 <= m_iDemoAlphaCounter )
					{
						m_iDemoTimeCounter++;
						if( 130 <= m_iDemoTimeCounter )		{	m_iDemoProcess = 1;	m_iDemoProcessSub = 0;		m_iDemoTimeCounter = 0;		m_iDemoAlphaCounter = 0;	}
					}
				}
			}
			break;

		case 1:
			{
				if( 0 == m_iDemoProcessSub )
				{
					SetAlpha(&m_vBgt[2], m_iDemoAlphaCounter);
					SetAlpha(&m_vBgt[3], m_iDemoAlphaCounter);

					if( 255 == m_iDemoAlphaCounter )	{	m_iDemoProcessSub = 10;		m_iDemoTimeCounter = 0;		m_iDemoAlphaCounter = 0;	}
				}
				else if( 10 == m_iDemoProcessSub )
				{
					SetAlpha(&m_vMst[1], m_iDemoAlphaCounter);

					if( 255 <= m_iDemoAlphaCounter )
					{
						m_iDemoTimeCounter++;
						if( 130 <= m_iDemoTimeCounter )		{	m_iDemoProcessSub = 20;		m_iDemoTimeCounter = 0;		m_iDemoAlphaCounter = 0;	}
					}
				}
				else if( 20 == m_iDemoProcessSub )
				{
					SetAlpha(&m_vBgt[4], m_iDemoAlphaCounter);
					SetAlpha(&m_vBgt[5], m_iDemoAlphaCounter);

					if( 255 == m_iDemoAlphaCounter )	{	m_iDemoProcessSub = 30;		m_iDemoTimeCounter = 0;		m_iDemoAlphaCounter = 0;	}
				}
				else if( 30 == m_iDemoProcessSub )
				{
					SetAlpha(&m_vMst[2], m_iDemoAlphaCounter);

					if( 255 <= m_iDemoAlphaCounter )
					{
						m_iDemoTimeCounter++;
						if( 130 <= m_iDemoTimeCounter )		{	m_iDemoProcessSub = 40;		m_iDemoTimeCounter = 0;		m_iDemoAlphaCounter = 0;	}
					}
				}
				else if( 40 == m_iDemoProcessSub )
				{
					SetAlpha(&m_vMst[3], m_iDemoAlphaCounter);

					if( 255 <= m_iDemoAlphaCounter )
					{
						m_iDemoTimeCounter++;
						if( 130 <= m_iDemoTimeCounter )		{	m_iDemoProcessSub = 50;		m_iDemoTimeCounter = 0;		m_iDemoAlphaCounter = 0;	}
					}
				}
				else if( 50 == m_iDemoProcessSub )
				{
					SetAlpha(&m_vMst[4], m_iDemoAlphaCounter);

					if( 255 <= m_iDemoAlphaCounter )
					{
						m_iDemoTimeCounter++;
						if( 130 <= m_iDemoTimeCounter )		{	m_iDemoProcess = 2;	m_iDemoProcessSub = 0;		m_iDemoTimeCounter = 0;		m_iDemoAlphaCounter = 0;	}
					}
				}
			}
			break;

		case 2:
			{
				if( 0 == m_iDemoProcessSub )
				{
					SetAlpha(&m_vBgt[6], m_iDemoAlphaCounter);

					if( 255 == m_iDemoAlphaCounter )
					{
						m_iDemoProcessSub = 10;
						m_iDemoTimeCounter = 0;
						m_iDemoAlphaCounter = 0;
					}
				}
				else if( 10 == m_iDemoProcessSub )
				{
					SetAlpha(&m_vMst[5], m_iDemoAlphaCounter);

					if( 255 <= m_iDemoAlphaCounter )
					{
						m_iDemoTimeCounter++;

						if( 130 <= m_iDemoTimeCounter )
						{
							m_iDemoProcessSub = 20;
							m_iDemoTimeCounter = 0;
							m_iDemoAlphaCounter = 0;
						}
					}
				}
				else if( 20 == m_iDemoProcessSub )
				{
					SetAlpha(&m_vMst[6], m_iDemoAlphaCounter);

					if( 255 <= m_iDemoAlphaCounter )
					{
						m_iDemoTimeCounter++;
						if( 130 <= m_iDemoTimeCounter )
						{
							m_iDemoProcess = 3;
							m_iDemoProcessSub = 0;
							m_iDemoTimeCounter = 0;
							m_iDemoAlphaCounter = 0;
						}
					}
				}
			}
			break;

		case 3:
			{
				if( 0 == m_iDemoProcessSub )
				{
					SetAlpha(&m_vBgt[7], m_iDemoAlphaCounter);
					SetAlpha(&m_vBgt[8], m_iDemoAlphaCounter);

					if( 255 == m_iDemoAlphaCounter )
					{
						m_iDemoProcessSub = 10;
						m_iDemoTimeCounter = 0;
						m_iDemoAlphaCounter = 0;
					}
				}
				else if( 10 == m_iDemoProcessSub )
				{
					SetAlpha(&m_vMst[7], m_iDemoAlphaCounter);

					if( 255 <= m_iDemoAlphaCounter )
					{
						m_iDemoTimeCounter++;

						if( 130 <= m_iDemoTimeCounter )
						{
							m_iDemoProcessSub = 20;
							m_iDemoTimeCounter = 0;
							m_iDemoAlphaCounter = 0;
						}
					}
				}
				else if( 20 == m_iDemoProcessSub )
				{
					SetAlpha(&m_vMst[8], m_iDemoAlphaCounter);

					if( 255 <= m_iDemoAlphaCounter )
					{
						m_iDemoTimeCounter++;

						if( 130 <= m_iDemoTimeCounter )
						{
							m_iDemoProcess = 4;
							m_iDemoProcessSub = 0;
							m_iDemoTimeCounter = 0;
							m_iDemoAlphaCounter = 0;
						}
					}
				}
			}
			break;

		case 4:
			{
				if( 0 == m_iDemoProcessSub )
				{
					SetAlpha(&m_vBgt[ 9], m_iDemoAlphaCounter);
					SetAlpha(&m_vBgt[10], m_iDemoAlphaCounter);

					if( 255 == m_iDemoAlphaCounter )
					{
						m_iDemoProcessSub = 10;
						m_iDemoAlphaCounter = 0;

						m_aiDemoAlphaCounter [0] = 0;
						m_aiDemoAlphaCounter [1] = -70;
						m_aiDemoAlphaCounter [2] = -140;
						m_aiDemoAlphaCounter [3] = -210;
						m_aiDemoAlphaCounter [4] = -280;
						m_aiDemoAlphaCounter [5] = -350;
						m_aiDemoAlphaCounter [6] = -420;
						m_aiDemoAlphaCounter [7] = -490;
					}
				}
				else if( 10 == m_iDemoProcessSub )
				{
					m_aiDemoAlphaCounter [0] += 5;	if( 255 < m_aiDemoAlphaCounter [0] )		m_aiDemoAlphaCounter [0] = 255;
					m_aiDemoAlphaCounter [1] += 5;	if( 255 < m_aiDemoAlphaCounter [1] )		m_aiDemoAlphaCounter [1] = 255;
					m_aiDemoAlphaCounter [2] += 5;	if( 255 < m_aiDemoAlphaCounter [2] )		m_aiDemoAlphaCounter [2] = 255;
					m_aiDemoAlphaCounter [3] += 5;	if( 255 < m_aiDemoAlphaCounter [3] )		m_aiDemoAlphaCounter [3] = 255;
					m_aiDemoAlphaCounter [4] += 5;	if( 255 < m_aiDemoAlphaCounter [4] )		m_aiDemoAlphaCounter [4] = 255;
					m_aiDemoAlphaCounter [5] += 5;	if( 255 < m_aiDemoAlphaCounter [5] )		m_aiDemoAlphaCounter [5] = 255;
					m_aiDemoAlphaCounter [6] += 5;	if( 255 < m_aiDemoAlphaCounter [6] )		m_aiDemoAlphaCounter [6] = 255;
					m_aiDemoAlphaCounter [7] += 5;	if( 255 < m_aiDemoAlphaCounter [7] )		m_aiDemoAlphaCounter [7] = 255;


					if( 0 < m_aiDemoAlphaCounter [0] )	SetAlpha(&m_vBgt[11], m_aiDemoAlphaCounter [0]);
					if( 0 < m_aiDemoAlphaCounter [1] )	SetAlpha(&m_vBgt[12], m_aiDemoAlphaCounter [1]);
					if( 0 < m_aiDemoAlphaCounter [2] )	SetAlpha(&m_vBgt[13], m_aiDemoAlphaCounter [2]);
					if( 0 < m_aiDemoAlphaCounter [3] )	SetAlpha(&m_vBgt[14], m_aiDemoAlphaCounter [3]);
					if( 0 < m_aiDemoAlphaCounter [4] )	SetAlpha(&m_vBgt[15], m_aiDemoAlphaCounter [4]);
					if( 0 < m_aiDemoAlphaCounter [5] )	SetAlpha(&m_vBgt[16], m_aiDemoAlphaCounter [5]);
					if( 0 < m_aiDemoAlphaCounter [6] )	SetAlpha(&m_vBgt[17], m_aiDemoAlphaCounter [6]);
					if( 0 < m_aiDemoAlphaCounter [7] )	SetAlpha(&m_vBgt[18], m_aiDemoAlphaCounter [7]);

					if( 255 <= m_aiDemoAlphaCounter [7] )
					{
						m_iDemoProcessSub = 20;
						m_iDemoAlphaCounter = 0;
						m_iDemoTimeCounter = 0;
					}
				}
				{
					SetAlpha(&m_vMst[9], m_iDemoAlphaCounter);

					if( 255 == m_iDemoAlphaCounter )
					{
						m_iDemoTimeCounter++;

						if(250 <= m_iDemoTimeCounter)
						{
							m_iDemoProcess = 100;
						}
					}
				}
			}
			break;


		default:
			SetSceneState(EN_SN_ACT);
			m_bExit=0;
			break;
		}
	}

	else if(2 == m_nDemo)
	{
		// set alpha value.
		m_iDemoAlphaCounter += 5;
		if( 255 < m_iDemoAlphaCounter )
			m_iDemoAlphaCounter = 255;

		switch ( m_iDemoProcess )
		{
		case 0:
			{
				if( 0 == m_iDemoProcessSub )
				{
					SetAlpha(&m_vBgt[0], m_iDemoAlphaCounter);

					if( 255 == m_iDemoAlphaCounter )	{	m_iDemoProcessSub = 10;		m_iDemoTimeCounter = 0;		m_iDemoAlphaCounter = 0;	}
				}
				else if( 10 == m_iDemoProcessSub )
				{
					SetAlpha(&m_vMst[0], m_iDemoAlphaCounter);

					if( 255 <= m_iDemoAlphaCounter )
					{
						m_iDemoTimeCounter++;
						if( 130 <= m_iDemoTimeCounter )		{	m_iDemoProcessSub = 20;		m_iDemoTimeCounter = 0;		m_iDemoAlphaCounter = 0;	}
					}
				}
				else if( 20 == m_iDemoProcessSub )
				{
					SetAlpha(&m_vMst[1], m_iDemoAlphaCounter);

					if( 255 <= m_iDemoAlphaCounter )
					{
						m_iDemoTimeCounter++;
						if( 130 <= m_iDemoTimeCounter )		{	m_iDemoProcessSub = 30;		m_iDemoTimeCounter = 0;		m_iDemoAlphaCounter = 0;	}
					}
				}
				else if( 30 == m_iDemoProcessSub )
				{
					SetAlpha(&m_vMst[2], m_iDemoAlphaCounter);

					if( 255 <= m_iDemoAlphaCounter )
					{
						m_iDemoTimeCounter++;
						if( 130 <= m_iDemoTimeCounter )		{	m_iDemoProcessSub = 40;		m_iDemoTimeCounter = 0;		m_iDemoAlphaCounter = 0;	}
					}
				}
				else if( 40 == m_iDemoProcessSub )
				{
					SetAlpha(&m_vBgt[1], m_iDemoAlphaCounter);

					if( 255 == m_iDemoAlphaCounter )		{	m_iDemoProcessSub = 50;		m_iDemoTimeCounter = 0;		m_iDemoAlphaCounter = 0;	}
				}
				else if( 50 == m_iDemoProcessSub )
				{
					SetAlpha(&m_vMst[3], m_iDemoAlphaCounter);

					if( 255 <= m_iDemoAlphaCounter )
					{
						m_iDemoTimeCounter++;
						if( 130 <= m_iDemoTimeCounter )		{	m_iDemoProcessSub = 60;		m_iDemoTimeCounter = 0;		m_iDemoAlphaCounter = 0;	}
					}
				}
				else if( 60 == m_iDemoProcessSub )
				{
					SetAlpha(&m_vBgt[2], m_iDemoAlphaCounter);

					if( 255 == m_iDemoAlphaCounter )		{	m_iDemoProcessSub = 70;		m_iDemoTimeCounter = 0;		m_iDemoAlphaCounter = 0;	}
				}
				else if( 70 == m_iDemoProcessSub )
				{
					SetAlpha(&m_vBgt[3], m_iDemoAlphaCounter);

					if( 255 == m_iDemoAlphaCounter )		{	m_iDemoProcessSub = 80;		m_iDemoTimeCounter = 0;		m_iDemoAlphaCounter = 0;	}
				}
				else if( 80 == m_iDemoProcessSub )
				{
					SetAlpha(&m_vMst[4], m_iDemoAlphaCounter);

					if( 255 <= m_iDemoAlphaCounter )
					{
						m_iDemoTimeCounter++;
						if( 130 <= m_iDemoTimeCounter )		{	m_iDemoProcessSub = 90;		m_iDemoTimeCounter = 0;		m_iDemoAlphaCounter = 0;	}
					}
				}
				else if( 90 == m_iDemoProcessSub )
				{
					SetAlpha(&m_vMst[5], m_iDemoAlphaCounter);

					if( 255 <= m_iDemoAlphaCounter )
					{
						m_iDemoTimeCounter++;
						if( 130 <= m_iDemoTimeCounter )		{	m_iDemoProcessSub = 100;		m_iDemoTimeCounter = 0;		m_iDemoAlphaCounter = 0;	}
					}
				}
				else if( 100 == m_iDemoProcessSub )
				{
					SetAlpha(&m_vMst[6], m_iDemoAlphaCounter);

					if( 255 <= m_iDemoAlphaCounter )
					{
						m_iDemoTimeCounter++;
						if( 130 <= m_iDemoTimeCounter )		{	m_iDemoProcess = 1;	m_iDemoProcessSub = 0;		m_iDemoTimeCounter = 0;		m_iDemoAlphaCounter = 0;	}
					}
				}

			}
			break;

		case 1:
			{
				if( 0 == m_iDemoProcessSub )
				{
					SetAlpha(&m_vBgt[4], m_iDemoAlphaCounter);

					if( 255 == m_iDemoAlphaCounter )	{	m_iDemoProcessSub = 10;		m_iDemoTimeCounter = 0;		m_iDemoAlphaCounter = 0;	}
				}
				else if( 10 == m_iDemoProcessSub )
				{
					SetAlpha(&m_vMst[7], m_iDemoAlphaCounter);

					if( 255 <= m_iDemoAlphaCounter )
					{
						m_iDemoTimeCounter++;
						if( 130 <= m_iDemoTimeCounter )		{	m_iDemoProcess = 2;	m_iDemoProcessSub = 0;		m_iDemoTimeCounter = 0;		m_iDemoAlphaCounter = 0;	}
					}
				}
			}
			break;

		case 2:
			{
				if( 0 == m_iDemoProcessSub )
				{
					SetAlpha(&m_vBgt[5], m_iDemoAlphaCounter);
					SetAlpha(&m_vBgt[6], m_iDemoAlphaCounter);

					if( 255 == m_iDemoAlphaCounter )	{	m_iDemoProcessSub = 10;		m_iDemoTimeCounter = 0;		m_iDemoAlphaCounter = 0;	}
				}
				else if( 10 == m_iDemoProcessSub )
				{
					SetAlpha(&m_vMst[8], m_iDemoAlphaCounter);

					if( 255 <= m_iDemoAlphaCounter )
					{
						m_iDemoTimeCounter++;
						if( 130 <= m_iDemoTimeCounter )		{	m_iDemoProcess = 3;	m_iDemoProcessSub = 0;		m_iDemoTimeCounter = 0;		m_iDemoAlphaCounter = 0;	}
					}
				}
			}
			break;

		case 3:
			{
				if( 0 == m_iDemoProcessSub )
				{
					SetAlpha(&m_vBgt[7], m_iDemoAlphaCounter);

					if( 255 == m_iDemoAlphaCounter )
					{
						m_iDemoProcessSub = 10;
						m_iDemoAlphaCounter = 0;

						m_aiDemoAlphaCounter [0] = 0;
						m_aiDemoAlphaCounter [1] = -70;
						m_aiDemoAlphaCounter [2] = -140;
						m_aiDemoAlphaCounter [3] = -210;
						m_aiDemoAlphaCounter [4] = -280;
						m_aiDemoAlphaCounter [5] = -350;
						m_aiDemoAlphaCounter [6] = -420;
						m_aiDemoAlphaCounter [7] = -490;
					}
				}
				else if( 10 == m_iDemoProcessSub )
				{
					m_aiDemoAlphaCounter [0] += 5;	if( 255 < m_aiDemoAlphaCounter [0] )		m_aiDemoAlphaCounter [0] = 255;
					m_aiDemoAlphaCounter [1] += 5;	if( 255 < m_aiDemoAlphaCounter [1] )		m_aiDemoAlphaCounter [1] = 255;
					m_aiDemoAlphaCounter [2] += 5;	if( 255 < m_aiDemoAlphaCounter [2] )		m_aiDemoAlphaCounter [2] = 255;
					m_aiDemoAlphaCounter [3] += 5;	if( 255 < m_aiDemoAlphaCounter [3] )		m_aiDemoAlphaCounter [3] = 255;
					m_aiDemoAlphaCounter [4] += 5;	if( 255 < m_aiDemoAlphaCounter [4] )		m_aiDemoAlphaCounter [4] = 255;
					m_aiDemoAlphaCounter [5] += 5;	if( 255 < m_aiDemoAlphaCounter [5] )		m_aiDemoAlphaCounter [5] = 255;
					m_aiDemoAlphaCounter [6] += 5;	if( 255 < m_aiDemoAlphaCounter [6] )		m_aiDemoAlphaCounter [6] = 255;
					m_aiDemoAlphaCounter [7] += 5;	if( 255 < m_aiDemoAlphaCounter [7] )		m_aiDemoAlphaCounter [7] = 255;

					if( 0 < m_aiDemoAlphaCounter [0] )	SetAlpha(&m_vBgt[ 8], m_aiDemoAlphaCounter [0]);
					if( 0 < m_aiDemoAlphaCounter [1] )	SetAlpha(&m_vBgt[ 9], m_aiDemoAlphaCounter [1]);
					if( 0 < m_aiDemoAlphaCounter [2] )	SetAlpha(&m_vBgt[10], m_aiDemoAlphaCounter [2]);
					if( 0 < m_aiDemoAlphaCounter [3] )	SetAlpha(&m_vBgt[11], m_aiDemoAlphaCounter [3]);
					if( 0 < m_aiDemoAlphaCounter [4] )	SetAlpha(&m_vBgt[12], m_aiDemoAlphaCounter [4]);
					if( 0 < m_aiDemoAlphaCounter [5] )	SetAlpha(&m_vBgt[13], m_aiDemoAlphaCounter [5]);
					if( 0 < m_aiDemoAlphaCounter [6] )	SetAlpha(&m_vBgt[14], m_aiDemoAlphaCounter [6]);
					if( 0 < m_aiDemoAlphaCounter [7] )	SetAlpha(&m_vBgt[15], m_aiDemoAlphaCounter [7]);


					if( 255 <= m_aiDemoAlphaCounter [7] )	{	m_iDemoProcessSub = 20;	m_iDemoAlphaCounter = 0;	m_iDemoTimeCounter = 0;	}
				}
				else if( 20 == m_iDemoProcessSub )
				{
					SetAlpha(&m_vMst[9], m_iDemoAlphaCounter);

					if( 255 == m_iDemoAlphaCounter )
					{
						m_iDemoTimeCounter++;

						if(250 <= m_iDemoTimeCounter)
						{
							m_iDemoProcess = 100;
						}
					}
				}
			}
			break;

		default:
			SetSceneState(EN_SN_ACT);
			m_bExit=0;
			break;
		}
	}

	else if(3 == m_nDemo)
	{
		// set alpha value.
		m_iDemoAlphaCounter += 5;
		if( 255 < m_iDemoAlphaCounter )
			m_iDemoAlphaCounter = 255;

		switch ( m_iDemoProcess )
		{
		case 0:
			{
				if( 0 == m_iDemoProcessSub )
				{
					SetAlpha(&m_vBgt[0], m_iDemoAlphaCounter);

					if( 255 == m_iDemoAlphaCounter )	{	m_iDemoProcessSub = 10;		m_iDemoTimeCounter = 0;		m_iDemoAlphaCounter = 0;	}
				}
				else if( 10 == m_iDemoProcessSub )
				{
					SetAlpha(&m_vMst[0], m_iDemoAlphaCounter);

					if( 255 <= m_iDemoAlphaCounter )
					{
						m_iDemoTimeCounter++;
						if( 130 <= m_iDemoTimeCounter )		{	m_iDemoProcessSub = 20;		m_iDemoTimeCounter = 0;		m_iDemoAlphaCounter = 0;	}
					}
				}
				else if( 20 == m_iDemoProcessSub )
				{
					SetAlpha(&m_vBgt[1], m_iDemoAlphaCounter);

					if( 255 == m_iDemoAlphaCounter )	{	m_iDemoProcessSub = 30;		m_iDemoTimeCounter = 0;		m_iDemoAlphaCounter = 0;	}
				}
				else if( 30 == m_iDemoProcessSub )
				{
					SetAlpha(&m_vMst[1], m_iDemoAlphaCounter);

					if( 255 <= m_iDemoAlphaCounter )
					{
						m_iDemoTimeCounter++;
						if( 130 <= m_iDemoTimeCounter )		{	m_iDemoProcess = 1;	m_iDemoProcessSub = 0;		m_iDemoTimeCounter = 0;		m_iDemoAlphaCounter = 0;	}
					}
				}
			}
			break;

		case 1:
			{
				if( 0 == m_iDemoProcessSub )
				{
					SetAlpha(&m_vBgt[2], m_iDemoAlphaCounter);

					if( 255 == m_iDemoAlphaCounter )	{	m_iDemoProcessSub = 10;		m_iDemoTimeCounter = 0;		m_iDemoAlphaCounter = 0;	}
				}
				else if( 10 == m_iDemoProcessSub )
				{
					SetAlpha(&m_vMst[2], m_iDemoAlphaCounter);

					if( 255 <= m_iDemoAlphaCounter )
					{
						m_iDemoTimeCounter++;
						if( 130 <= m_iDemoTimeCounter )		{	m_iDemoProcess = 2;	m_iDemoProcessSub = 0;		m_iDemoTimeCounter = 0;		m_iDemoAlphaCounter = 0;	}
					}
				}
			}
			break;

		case 2:
			{
				if( 0 == m_iDemoProcessSub )
				{
					SetAlpha(&m_vBgt[4], m_iDemoAlphaCounter);

					if( 255 == m_iDemoAlphaCounter )	{	m_iDemoProcessSub = 10;		m_iDemoTimeCounter = 0;		m_iDemoAlphaCounter = 0;	}
				}
				else if( 10 == m_iDemoProcessSub )
				{
					SetAlpha(&m_vMst[3], m_iDemoAlphaCounter);

					if( 255 <= m_iDemoAlphaCounter )
					{
						m_iDemoTimeCounter++;
						if( 130 <= m_iDemoTimeCounter )		{	m_iDemoProcessSub = 20;		m_iDemoTimeCounter = 0;		m_iDemoAlphaCounter = 0;	}
					}
				}
				else if( 20 == m_iDemoProcessSub )
				{
					SetAlpha(&m_vBgt[3], m_iDemoAlphaCounter);

					if( 255 == m_iDemoAlphaCounter )	{	m_iDemoProcessSub = 30;		m_iDemoTimeCounter = 0;		m_iDemoAlphaCounter = 0;	}
				}
				else if( 30 == m_iDemoProcessSub )
				{
					SetAlpha(&m_vMst[4], m_iDemoAlphaCounter);

					if( 255 <= m_iDemoAlphaCounter )
					{
						m_iDemoTimeCounter++;
						if( 130 <= m_iDemoTimeCounter )		{	m_iDemoProcessSub = 40;		m_iDemoTimeCounter = 0;		m_iDemoAlphaCounter = 0;	}
					}
				}
				else if( 40 == m_iDemoProcessSub )
				{
					SetAlpha(&m_vMst[5], m_iDemoAlphaCounter);

					if( 255 <= m_iDemoAlphaCounter )
					{
						m_iDemoTimeCounter++;
						if( 130 <= m_iDemoTimeCounter )		{	m_iDemoProcess = 3;	m_iDemoProcessSub = 0;		m_iDemoTimeCounter = 0;		m_iDemoAlphaCounter = 0;	}
					}
				}
			}
			break;

		case 3:
			{
				if( 0 == m_iDemoProcessSub )
				{
					SetAlpha(&m_vBgt[5], m_iDemoAlphaCounter);

					if( 255 == m_iDemoAlphaCounter )
					{
						m_iDemoProcessSub = 10;
						m_iDemoTimeCounter = 0;
						m_iDemoAlphaCounter = 0;

						m_aiDemoAlphaCounter[0] = 1;
					}

				}
				else if( 10 == m_iDemoProcessSub )
				{
					SetAlpha(&m_vMst[6], m_iDemoAlphaCounter);

					if( 255 <= m_iDemoAlphaCounter )
					{
						m_iDemoTimeCounter++;
						if( 130 <= m_iDemoTimeCounter )		{	m_iDemoProcessSub = 20;		m_iDemoTimeCounter = 0;		m_iDemoAlphaCounter = 0;	}
					}
				}
				else if( 20 == m_iDemoProcessSub )
				{
					SetAlpha(&m_vBgt[6], m_iDemoAlphaCounter);

					if( 255 == m_iDemoAlphaCounter )	{	m_iDemoProcessSub = 30;		m_iDemoTimeCounter = 0;		m_iDemoAlphaCounter = 0;	}
				}
				else if( 30 == m_iDemoProcessSub )
				{

					if(m_aiDemoAlphaCounter[0])
						SetAlpha(&m_vMst[7], m_iDemoAlphaCounter);
					else
						SetAlpha(&m_vMst[8], m_iDemoAlphaCounter);


					if( 255 <= m_iDemoAlphaCounter )
					{
						m_iDemoTimeCounter++;

						if(255<m_iDemoTimeCounter)
						{
							m_iDemoTimeCounter = 0;
							m_iDemoAlphaCounter = 0;
							m_aiDemoAlphaCounter[0] = 0;
							SetAlpha(&m_vMst[7], 0);
						}


						if( 130 <= m_iDemoTimeCounter && 0 == m_aiDemoAlphaCounter[0])
						{
							m_iDemoProcess = 4;
							m_iDemoProcessSub = 0;
							m_iDemoTimeCounter = 0;
							m_iDemoAlphaCounter = 0;
						}
					}
				}
			}

			break;

		case 4:
			{
				if ( 0 == m_iDemoProcessSub )
				{
					SetAlpha(&m_vBgt[7], m_iDemoAlphaCounter);

					if ( 255 == m_iDemoAlphaCounter )
					{
						m_iDemoProcessSub = 10;
						m_iDemoAlphaCounter = 0;

						m_aiDemoAlphaCounter [0] = 0;
						m_aiDemoAlphaCounter [1] = -70;
						m_aiDemoAlphaCounter [2] = -140;
						m_aiDemoAlphaCounter [3] = -210;
						m_aiDemoAlphaCounter [4] = -280;
						m_aiDemoAlphaCounter [5] = -350;
						m_aiDemoAlphaCounter [6] = -420;
						m_aiDemoAlphaCounter [7] = -490;
					}
				}
				else if ( 10 == m_iDemoProcessSub )
				{
					m_aiDemoAlphaCounter [0] += 5;	if ( 255 < m_aiDemoAlphaCounter [0] )		m_aiDemoAlphaCounter [0] = 255;
					m_aiDemoAlphaCounter [1] += 5;	if ( 255 < m_aiDemoAlphaCounter [1] )		m_aiDemoAlphaCounter [1] = 255;
					m_aiDemoAlphaCounter [2] += 5;	if ( 255 < m_aiDemoAlphaCounter [2] )		m_aiDemoAlphaCounter [2] = 255;
					m_aiDemoAlphaCounter [3] += 5;	if ( 255 < m_aiDemoAlphaCounter [3] )		m_aiDemoAlphaCounter [3] = 255;
					m_aiDemoAlphaCounter [4] += 5;	if ( 255 < m_aiDemoAlphaCounter [4] )		m_aiDemoAlphaCounter [4] = 255;
					m_aiDemoAlphaCounter [5] += 5;	if ( 255 < m_aiDemoAlphaCounter [5] )		m_aiDemoAlphaCounter [5] = 255;
					m_aiDemoAlphaCounter [6] += 5;	if ( 255 < m_aiDemoAlphaCounter [6] )		m_aiDemoAlphaCounter [6] = 255;
					m_aiDemoAlphaCounter [7] += 5;	if ( 255 < m_aiDemoAlphaCounter [7] )		m_aiDemoAlphaCounter [7] = 255;

					if ( 0 < m_aiDemoAlphaCounter [0] )	SetAlpha(&m_vBgt[ 8], m_aiDemoAlphaCounter [0]);
					if ( 0 < m_aiDemoAlphaCounter [1] )	SetAlpha(&m_vBgt[ 9], m_aiDemoAlphaCounter [1]);
					if ( 0 < m_aiDemoAlphaCounter [2] )	SetAlpha(&m_vBgt[10], m_aiDemoAlphaCounter [2]);
					if ( 0 < m_aiDemoAlphaCounter [3] )	SetAlpha(&m_vBgt[11], m_aiDemoAlphaCounter [3]);
					if ( 0 < m_aiDemoAlphaCounter [4] )	SetAlpha(&m_vBgt[12], m_aiDemoAlphaCounter [4]);
					if ( 0 < m_aiDemoAlphaCounter [5] )	SetAlpha(&m_vBgt[13], m_aiDemoAlphaCounter [5]);
					if ( 0 < m_aiDemoAlphaCounter [6] )	SetAlpha(&m_vBgt[14], m_aiDemoAlphaCounter [6]);
					if ( 0 < m_aiDemoAlphaCounter [7] )	SetAlpha(&m_vBgt[15], m_aiDemoAlphaCounter [7]);


					if ( 255 <= m_aiDemoAlphaCounter [7] )	{	m_iDemoProcessSub = 20;	m_iDemoAlphaCounter = 0;	m_iDemoTimeCounter = 0;	}
				}
				else if ( 20 == m_iDemoProcessSub )
				{
					SetAlpha(&m_vMst[9], m_iDemoAlphaCounter);

					if ( 255 == m_iDemoAlphaCounter )
					{
						m_iDemoTimeCounter++;

						if(250 <= m_iDemoTimeCounter)
						{
							m_iDemoProcess = 100;
						}
					}
				}
			}
			break;

		default:
			SetSceneState(EN_SN_ACT);
			m_bExit=0;
			break;
		}
	}

	else if(4 == m_nDemo)
	{
		// set alpha value.
		m_iDemoAlphaCounter += 5;
		if( 255 < m_iDemoAlphaCounter )
			m_iDemoAlphaCounter = 255;

		switch ( m_iDemoProcess )
		{
		case 0:
			{
				if( 0 == m_iDemoProcessSub )
				{
					SetAlpha(&m_vBgt[0], m_iDemoAlphaCounter);

					if( 255 == m_iDemoAlphaCounter )	{	m_iDemoProcessSub = 10;		m_iDemoTimeCounter = 0;		m_iDemoAlphaCounter = 0;	}
				}
				else if( 10 == m_iDemoProcessSub )
				{
					SetAlpha(&m_vMst[0], m_iDemoAlphaCounter);

					if( 255 <= m_iDemoAlphaCounter )
					{
						m_iDemoTimeCounter++;
						if( 130 <= m_iDemoTimeCounter )		{	m_iDemoProcessSub = 20;		m_iDemoTimeCounter = 0;		m_iDemoAlphaCounter = 0;	}
					}
				}
				else if( 20 == m_iDemoProcessSub )
				{
					SetAlpha(&m_vMst[1], m_iDemoAlphaCounter);

					if( 255 <= m_iDemoAlphaCounter )
					{
						m_iDemoTimeCounter++;
						if( 130 <= m_iDemoTimeCounter )		{	m_iDemoProcess = 1;	m_iDemoProcessSub = 0;		m_iDemoTimeCounter = 0;		m_iDemoAlphaCounter = 0;	}
					}
				}
			}
			break;

		case 1:
			{
				if( 0 == m_iDemoProcessSub )
				{
					SetAlpha(&m_vBgt[1], m_iDemoAlphaCounter);

					if( 255 == m_iDemoAlphaCounter )	{	m_iDemoProcessSub = 10;		m_iDemoTimeCounter = 0;		m_iDemoAlphaCounter = 0;	}
				}
				else if( 10 == m_iDemoProcessSub )
				{
					SetAlpha(&m_vMst[2], m_iDemoAlphaCounter);

					if( 255 <= m_iDemoAlphaCounter )
					{
						m_iDemoTimeCounter++;
						if( 130 <= m_iDemoTimeCounter )		{	m_iDemoProcessSub = 20;		m_iDemoTimeCounter = 0;		m_iDemoAlphaCounter = 0;	}
					}
				}
				else if( 20 == m_iDemoProcessSub )
				{
					SetAlpha(&m_vBgt[2], m_iDemoAlphaCounter);

					if( 255 == m_iDemoAlphaCounter )	{	m_iDemoProcessSub = 30;		m_iDemoTimeCounter = 0;		m_iDemoAlphaCounter = 0;	}
				}
				else if( 30 == m_iDemoProcessSub )
				{
					SetAlpha(&m_vMst[3], m_iDemoAlphaCounter);

					if( 255 <= m_iDemoAlphaCounter )
					{
						m_iDemoTimeCounter++;
						if( 130 <= m_iDemoTimeCounter )		{	m_iDemoProcess = 2;	m_iDemoProcessSub = 0;		m_iDemoTimeCounter = 0;		m_iDemoAlphaCounter = 0;	}
					}
				}
			}
			break;

		case 2:
			{
				if( 0 == m_iDemoProcessSub )
				{
					SetAlpha(&m_vBgt[3], m_iDemoAlphaCounter);

					if( 255 == m_iDemoAlphaCounter )	{	m_iDemoProcessSub = 10;		m_iDemoTimeCounter = 0;		m_iDemoAlphaCounter = 0;	}
				}
				else if( 10 == m_iDemoProcessSub )
				{
					SetAlpha(&m_vMst[4], m_iDemoAlphaCounter);

					m_iDemoTimeCounter++;
					if( 130 <= m_iDemoTimeCounter )		{	m_iDemoProcessSub = 20;		m_iDemoTimeCounter = 0;		m_iDemoAlphaCounter = 0;	}
				}
				else if( 20 == m_iDemoProcessSub )
				{
					SetAlpha(&m_vMst[5], m_iDemoAlphaCounter);

					if( 255 <= m_iDemoAlphaCounter )
					{
						m_iDemoTimeCounter++;
						if( 130 <= m_iDemoTimeCounter )		{	m_iDemoProcess = 3;	m_iDemoProcessSub = 0;		m_iDemoTimeCounter = 0;		m_iDemoAlphaCounter = 0;	}
					}
				}
			}
			break;

		case 3:
			{
				if( 0 == m_iDemoProcessSub )
				{
					SetAlpha(&m_vBgt[4], m_iDemoAlphaCounter);

					if( 255 == m_iDemoAlphaCounter )	{	m_iDemoProcessSub = 10;		m_iDemoTimeCounter = 0;		m_iDemoAlphaCounter = 0;	}
				}
				else if( 10 == m_iDemoProcessSub )
				{
					SetAlpha(&m_vMst[6], m_iDemoAlphaCounter);

					if( 255 <= m_iDemoAlphaCounter )
					{
						m_iDemoTimeCounter++;
						if( 130 <= m_iDemoTimeCounter )		{	m_iDemoProcess = 4;	m_iDemoProcessSub = 0;		m_iDemoTimeCounter = 0;		m_iDemoAlphaCounter = 0;	}
					}
				}
			}
			break;

		case 4:
			{
				if( 0 == m_iDemoProcessSub )
				{
					SetAlpha(&m_vBgt[5], m_iDemoAlphaCounter);

					if( 255 == m_iDemoAlphaCounter )
					{
						m_iDemoProcessSub = 10;
						m_iDemoTimeCounter = 0;
						m_iDemoAlphaCounter = 0;
					
						m_aiDemoAlphaCounter[0] = 1;
					}
				}
				else if( 10 == m_iDemoProcessSub )
				{
					if(m_aiDemoAlphaCounter[0])
						SetAlpha(&m_vMst[7], m_iDemoAlphaCounter);
					else
						SetAlpha(&m_vMst[8], m_iDemoAlphaCounter);


					if( 255 <= m_iDemoAlphaCounter )
					{
						m_iDemoTimeCounter++;

						if(255<m_iDemoTimeCounter)
						{
							m_iDemoTimeCounter = 0;
							m_iDemoAlphaCounter = 0;
							m_aiDemoAlphaCounter[0] = 0;
							SetAlpha(&m_vMst[7], 0);
						}


						if( 130 <= m_iDemoTimeCounter && 0 == m_aiDemoAlphaCounter[0])
						{
							m_iDemoProcess = 5;
							m_iDemoProcessSub = 0;
							m_iDemoTimeCounter = 0;
							m_iDemoAlphaCounter = 0;
						}
					}
				}
			}
			break;


		case 5:
			{
				if ( 0 == m_iDemoProcessSub )
				{
					SetAlpha(&m_vBgt[7], m_iDemoAlphaCounter);

					if ( 255 == m_iDemoAlphaCounter )
					{
						m_iDemoProcessSub = 10;
						m_iDemoAlphaCounter = 0;

						m_aiDemoAlphaCounter [0] = 0;
						m_aiDemoAlphaCounter [1] = -70;
						m_aiDemoAlphaCounter [2] = -140;
						m_aiDemoAlphaCounter [3] = -210;
						m_aiDemoAlphaCounter [4] = -280;
						m_aiDemoAlphaCounter [5] = -350;
						m_aiDemoAlphaCounter [6] = -420;
						m_aiDemoAlphaCounter [7] = -490;
					}
				}
				else if ( 10 == m_iDemoProcessSub )
				{
					m_aiDemoAlphaCounter [0] += 5;	if ( 255 < m_aiDemoAlphaCounter [0] )		m_aiDemoAlphaCounter [0] = 255;
					m_aiDemoAlphaCounter [1] += 5;	if ( 255 < m_aiDemoAlphaCounter [1] )		m_aiDemoAlphaCounter [1] = 255;
					m_aiDemoAlphaCounter [2] += 5;	if ( 255 < m_aiDemoAlphaCounter [2] )		m_aiDemoAlphaCounter [2] = 255;
					m_aiDemoAlphaCounter [3] += 5;	if ( 255 < m_aiDemoAlphaCounter [3] )		m_aiDemoAlphaCounter [3] = 255;
					m_aiDemoAlphaCounter [4] += 5;	if ( 255 < m_aiDemoAlphaCounter [4] )		m_aiDemoAlphaCounter [4] = 255;
					m_aiDemoAlphaCounter [5] += 5;	if ( 255 < m_aiDemoAlphaCounter [5] )		m_aiDemoAlphaCounter [5] = 255;
					m_aiDemoAlphaCounter [6] += 5;	if ( 255 < m_aiDemoAlphaCounter [6] )		m_aiDemoAlphaCounter [6] = 255;
					m_aiDemoAlphaCounter [7] += 5;	if ( 255 < m_aiDemoAlphaCounter [7] )		m_aiDemoAlphaCounter [7] = 255;

					if ( 0 < m_aiDemoAlphaCounter [0] )	SetAlpha(&m_vBgt[ 8], m_aiDemoAlphaCounter [0]);
					if ( 0 < m_aiDemoAlphaCounter [1] )	SetAlpha(&m_vBgt[ 9], m_aiDemoAlphaCounter [1]);
					if ( 0 < m_aiDemoAlphaCounter [2] )	SetAlpha(&m_vBgt[10], m_aiDemoAlphaCounter [2]);
					if ( 0 < m_aiDemoAlphaCounter [3] )	SetAlpha(&m_vBgt[11], m_aiDemoAlphaCounter [3]);
					if ( 0 < m_aiDemoAlphaCounter [4] )	SetAlpha(&m_vBgt[12], m_aiDemoAlphaCounter [4]);
					if ( 0 < m_aiDemoAlphaCounter [5] )	SetAlpha(&m_vBgt[13], m_aiDemoAlphaCounter [5]);
					if ( 0 < m_aiDemoAlphaCounter [6] )	SetAlpha(&m_vBgt[14], m_aiDemoAlphaCounter [6]);
					if ( 0 < m_aiDemoAlphaCounter [7] )	SetAlpha(&m_vBgt[15], m_aiDemoAlphaCounter [7]);


					if ( 255 <= m_aiDemoAlphaCounter [7] )	{	m_iDemoProcessSub = 20;	m_iDemoAlphaCounter = 0;	m_iDemoTimeCounter = 0;	}
				}
				else if ( 20 == m_iDemoProcessSub )
				{
					SetAlpha(&m_vMst[9], m_iDemoAlphaCounter);

					if ( 255 == m_iDemoAlphaCounter )
					{
						m_iDemoTimeCounter++;

						if(250 <= m_iDemoTimeCounter)
						{
							m_iDemoProcess = 100;
						}
					}
				}
			}
			break;

		default:
			SetSceneState(EN_SN_ACT);
			m_bExit=0;
			break;
		}
	}



	//	キャンセルキ?を押した
	if( g_pApp->IsPushCancelKey() )
	{
		SetSceneState(EN_SN_ACT);
		m_bExit=0;
	}


	return m_bExit;
}



void CGpDemo::Render()
{
	Blt ( m_vTex[1], 0, 0);
	Blt ( m_vTex[0], 0, 0);

	if(0 == m_nDemo)
	{
		if( 0 == m_iDemoProcess )
		{
			if( 0 <= m_iDemoProcessSub )
				draw_fix(&m_vBgt[0], 1, 1);

			if( 10 <= m_iDemoProcessSub && 30 >= m_iDemoProcessSub )
				draw_fix(&m_vMst[0], ( 320 - m_vMst[0].pTex->GetImgW() ) / 2, 210);

			if( 20 <= m_iDemoProcessSub )
				draw_fix(&m_vBgt[1],  180, 1);

			if( 30 <= m_iDemoProcessSub )
				draw_fix(&m_vBgt[2], 240, 1);

			if( 40 <= m_iDemoProcessSub && 50 >= m_iDemoProcessSub )
				draw_fix(&m_vMst[1], ( 320 - m_vMst[1].pTex->GetImgW() ) / 2, 210);

			if( 50 <= m_iDemoProcessSub )
				draw_fix(&m_vBgt[3], 180, 100);

			if( 60 <= m_iDemoProcessSub )
				draw_fix(&m_vMst[2], ( 320 - m_vMst[2].pTex->GetImgW() ) / 2, 210);
		}
		else if( 1 == m_iDemoProcess )
		{
			if( 0 <= m_iDemoProcessSub )
				draw_fix(&m_vBgt[4], -1, 20);

			if( 10 <= m_iDemoProcessSub )
				draw_fix(&m_vMst[3], ( 320 - m_vMst[3].pTex->GetImgW() ) / 2, 200);
		}
		else if( 2 == m_iDemoProcess )
		{
			if( 0 <= m_iDemoProcessSub )
				draw_fix(&m_vBgt[5], 2, 10);

			if( 10 <= m_iDemoProcessSub )
			{
				draw_fix(&m_vMst[4], ( 320 - m_vMst[4].pTex->GetImgW() ) / 2, 190);
				draw_fix(&m_vMst[5], ( 320 - m_vMst[5].pTex->GetImgW() ) / 2, 210);
			}
		}
		else if( 3 == m_iDemoProcess )
		{
			if( 0 <= m_iDemoProcessSub )
				draw_fix(&m_vBgt[6], 12, 2);

			//if( 0 <= m_iDemoProcessSub )
			//	draw_fix(&m_vBgt[7], 95, 10);

			if( 10 <= m_iDemoProcessSub )
			{
				draw_fix(&m_vBgt[ 8], 130, 30 - 8);
				draw_fix(&m_vBgt[ 9], 166, 33 - 8);
				draw_fix(&m_vBgt[10], 202, 27 - 8);
				draw_fix(&m_vBgt[11], 234, 30 - 8);
				draw_fix(&m_vBgt[12], 260, 30 - 8);
				draw_fix(&m_vBgt[13], 160, 65 - 8);
				draw_fix(&m_vBgt[14], 200, 67 - 8);
				draw_fix(&m_vBgt[15], 240, 64 - 8);
			}

			if( 20 <= m_iDemoProcessSub )
				draw_fix(&m_vMst[6], ( 320 - m_vMst[6].pTex->GetImgW() ) / 2, 210);
		}
	}

	else if(1 == m_nDemo)
	{
		if( 0 == m_iDemoProcess )
		{
			if( 0 <= m_iDemoProcessSub )
				draw_fix(&m_vBgt[0], 1, 30);

			if( 0 <= m_iDemoProcessSub )
				draw_fix(&m_vBgt[1], 39, 74);

			if( 10 <= m_iDemoProcessSub )
				draw_fix(&m_vMst[0], ( 320 - m_vMst[0].pTex->GetImgW() ) / 2, 190);
		}
		else if( 1 == m_iDemoProcess )
		{
			if( 0 <= m_iDemoProcessSub )
				draw_fix(&m_vBgt[2], 1, 2);

			if( 0 <= m_iDemoProcessSub )
				draw_fix(&m_vBgt[3], 22, 6);

			if( 10 <= m_iDemoProcessSub && 20 >= m_iDemoProcessSub )
				draw_fix(&m_vMst[1], ( 320 - m_vMst[1].pTex->GetImgW() ) / 2, 200);

			if( 20 <= m_iDemoProcessSub )
				draw_fix(&m_vBgt[4], 124, 25);

			if( 20 <= m_iDemoProcessSub )
				draw_fix(&m_vBgt[5], 228, 26);

			if( 30 <= m_iDemoProcessSub && 40 > m_iDemoProcessSub )
				draw_fix(&m_vMst[2], ( 320 - m_vMst[2].pTex->GetImgW() ) / 2, 200);

			if( 40 <= m_iDemoProcessSub && 50 > m_iDemoProcessSub )
				draw_fix(&m_vMst[3], ( 320 - m_vMst[3].pTex->GetImgW() ) / 2, 200);

			if( 50 <= m_iDemoProcessSub && 60 > m_iDemoProcessSub )
				draw_fix(&m_vMst[4], ( 320 - m_vMst[4].pTex->GetImgW() ) / 2, 200);

		}

		else if( 2 == m_iDemoProcess )
		{
			if( 0 <= m_iDemoProcessSub )
				draw_fix(&m_vBgt[6], 94, 2);

			if( 10 <= m_iDemoProcessSub && 20 > m_iDemoProcessSub )
				draw_fix(&m_vMst[5], ( 320 - m_vMst[5].pTex->GetImgW() ) / 2, 200);

			if( 20 <= m_iDemoProcessSub && 30 >= m_iDemoProcessSub )
				draw_fix(&m_vMst[6], ( 320 - m_vMst[6].pTex->GetImgW() ) / 2, 200);
		}
		else if( 3 == m_iDemoProcess )
		{
			if( 0 <= m_iDemoProcessSub )
				draw_fix(&m_vBgt[7],32, 10);

			if( 0 <= m_iDemoProcessSub )
				draw_fix(&m_vBgt[8],126, 0);

			if( 10 <= m_iDemoProcessSub && 20 > m_iDemoProcessSub )
				draw_fix(&m_vMst[7], ( 320 - m_vMst[7].pTex->GetImgW() ) / 2, 200);

			if( 20 <= m_iDemoProcessSub && 30 > m_iDemoProcessSub )
				draw_fix(&m_vMst[8], ( 320 - m_vMst[8].pTex->GetImgW() ) / 2, 200);
		}
		else if( 4 == m_iDemoProcess )
		{
			if( 0 <= m_iDemoProcessSub )
				draw_fix(&m_vBgt[9], 70, 10);

			if( 0 <= m_iDemoProcessSub )
				draw_fix(&m_vBgt[10],2, 13);

			if( 20 <= m_iDemoProcessSub && 30 > m_iDemoProcessSub )
				draw_fix(&m_vMst[9], ( 320 - m_vMst[9].pTex->GetImgW() ) / 2, 200);

			if( 10 <= m_iDemoProcessSub )
			{
				draw_fix(&m_vBgt[11], 10,  20);
				draw_fix(&m_vBgt[12], 10,  55);
				draw_fix(&m_vBgt[13], 10,  84);
				draw_fix(&m_vBgt[14], 12, 116);
				draw_fix(&m_vBgt[15], 40,  30);
				draw_fix(&m_vBgt[16], 40,  65);
				draw_fix(&m_vBgt[17], 40, 104);
				draw_fix(&m_vBgt[18], 75,  70);
			}
		}
	}

	else if(2 == m_nDemo)
	{
		if( 0 == m_iDemoProcess )
		{
			if( 0 <= m_iDemoProcessSub )
				draw_fix(&m_vBgt[0], 4, 0);

			if( 10 <= m_iDemoProcessSub && 20 > m_iDemoProcessSub )
				draw_fix(&m_vMst[0], ( 320 - m_vMst[0].pTex->GetImgW() ) / 2, 210);

			if( 20 <= m_iDemoProcessSub && 30 > m_iDemoProcessSub )
				draw_fix(&m_vMst[1], ( 320 - m_vMst[1].pTex->GetImgW() ) / 2, 210);

			if( 30 <= m_iDemoProcessSub && 40 > m_iDemoProcessSub )
				draw_fix(&m_vMst[2], ( 320 - m_vMst[2].pTex->GetImgW() ) / 2, 210);

			if( 40 <= m_iDemoProcessSub )
				draw_fix(&m_vBgt[1],140, 2);

			if( 50 <= m_iDemoProcessSub && 60 > m_iDemoProcessSub )
				draw_fix(&m_vMst[3], ( 320 - m_vMst[3].pTex->GetImgW() ) / 2, 210);

			if( 60 <= m_iDemoProcessSub )
				draw_fix(&m_vBgt[2], 220, 2);

			if( 70 <= m_iDemoProcessSub )
				draw_fix(&m_vBgt[3], 130, 70);

			if( 80 <= m_iDemoProcessSub && 90 > m_iDemoProcessSub )
				draw_fix(&m_vMst[4], ( 320 - m_vMst[4].pTex->GetImgW() ) / 2, 210);

			if( 90 <= m_iDemoProcessSub && 100 > m_iDemoProcessSub )
				draw_fix(&m_vMst[5], ( 320 - m_vMst[5].pTex->GetImgW() ) / 2, 210);

			if( 100 <= m_iDemoProcessSub && 110 > m_iDemoProcessSub )
				draw_fix(&m_vMst[6], ( 320 - m_vMst[6].pTex->GetImgW() ) / 2, 210);
		}
		else if( 1 == m_iDemoProcess )
		{
			if( 0 <= m_iDemoProcessSub )
				draw_fix(&m_vBgt[4], 96, 2);

			if( 10 <= m_iDemoProcessSub && 20 > m_iDemoProcessSub )
				draw_fix(&m_vMst[7], ( 320 - m_vMst[7].pTex->GetImgW() ) / 2, 210);
		}
		else if( 2 == m_iDemoProcess )
		{
			if( 0 <= m_iDemoProcessSub )
				draw_fix(&m_vBgt[5], 32, 10);

			if( 0 <= m_iDemoProcessSub )
				draw_fix(&m_vBgt[6], 126, 0);

			if( 10 <= m_iDemoProcessSub && 20 > m_iDemoProcessSub )
				draw_fix(&m_vMst[8], ( 320 - m_vMst[8].pTex->GetImgW() ) / 2, 200);
		}
		else if( 3 == m_iDemoProcess )
		{
			if( 0 <= m_iDemoProcessSub )
				draw_fix(&m_vBgt[7], 12, 2);

			if( 10 <= m_iDemoProcessSub )
			{
				draw_fix(&m_vBgt[ 8],  130, 30 - 8);
				draw_fix(&m_vBgt[ 9],  166, 33 - 8);
				draw_fix(&m_vBgt[10],  202, 27 - 8);
				draw_fix(&m_vBgt[11],  234, 30 - 8);
				draw_fix(&m_vBgt[12],  260, 30 - 8);
				draw_fix(&m_vBgt[13],  160, 65 - 8);
				draw_fix(&m_vBgt[14],  200, 67 - 8);
				draw_fix(&m_vBgt[15],  240, 64 - 8);
			}

			if( 20 <= m_iDemoProcessSub )
				draw_fix(&m_vMst[9], ( 320 - m_vMst[9].pTex->GetImgW() ) / 2, 210);
		}
	}
	else if(3 == m_nDemo)
	{
		if( 0 == m_iDemoProcess )
		{
			if( 0 <= m_iDemoProcessSub )
				draw_fix(&m_vBgt[0], 86, 86);

			if( 10 <= m_iDemoProcessSub && 20 > m_iDemoProcessSub )
				draw_fix(&m_vMst[0], ( 320 - m_vMst[0].pTex->GetImgW() ) / 2, 210);

			if( 20 <= m_iDemoProcessSub )
				draw_fix(&m_vBgt[1], 0, 0);

			if( 30 <= m_iDemoProcessSub && 40 > m_iDemoProcessSub )
				draw_fix(&m_vMst[1], ( 320 - m_vMst[1].pTex->GetImgW() ) / 2, 210);
		}
		else if( 1 == m_iDemoProcess )
		{
			if( 0 <= m_iDemoProcessSub )
				draw_fix(&m_vBgt[2],74, 10);

			if( 10 <= m_iDemoProcessSub && 20 > m_iDemoProcessSub )
				draw_fix(&m_vMst[2], ( 320 - m_vMst[2].pTex->GetImgW() ) / 2, 210);
		}

		else if( 2 == m_iDemoProcess )
		{
			if( 0 <= m_iDemoProcessSub )
				draw_fix(&m_vBgt[4],30, 0);

			if( 10 <= m_iDemoProcessSub && 20 > m_iDemoProcessSub )
				draw_fix(&m_vMst[3], ( 320 - m_vMst[3].pTex->GetImgW() ) / 2, 210);

			if( 20 <= m_iDemoProcessSub )
				draw_fix(&m_vBgt[3], 160, 80);

			if( 30 <= m_iDemoProcessSub && 40 > m_iDemoProcessSub )
				draw_fix(&m_vMst[4], ( 320 - m_vMst[4].pTex->GetImgW() ) / 2, 210);

			if( 40 <= m_iDemoProcessSub && 50 > m_iDemoProcessSub )
				draw_fix(&m_vMst[5], ( 320 - m_vMst[5].pTex->GetImgW() ) / 2, 210);
		}

		else if( 3 == m_iDemoProcess )
		{
			if( 0 <= m_iDemoProcessSub )
				draw_fix(&m_vBgt[5], 20, 3);

			if( 10 <= m_iDemoProcessSub && 20 > m_iDemoProcessSub )
				draw_fix(&m_vMst[6], ( 320 - m_vMst[6].pTex->GetImgW() ) / 2, 210);

			if( 20 <= m_iDemoProcessSub )
				draw_fix(&m_vBgt[6], 160, 20);

			if( 30 <= m_iDemoProcessSub && 40 > m_iDemoProcessSub )
			{
				draw_fix(&m_vMst[7], ( 320 - m_vMst[7].pTex->GetImgW() ) / 2, 210);
				draw_fix(&m_vMst[8], ( 320 - m_vMst[8].pTex->GetImgW() ) / 2, 210);
			}
		}

		else if ( 4 == m_iDemoProcess )
		{
			if ( 0 <= m_iDemoProcessSub )
				draw_fix(&m_vBgt[7], 12, 2);

			if ( 10 <= m_iDemoProcessSub )
			{
				draw_fix(&m_vBgt[ 8],  130, 30 - 8);
				draw_fix(&m_vBgt[ 9],  166, 33 - 8);
				draw_fix(&m_vBgt[10],  202, 27 - 8);
				draw_fix(&m_vBgt[11],  234, 30 - 8);
				draw_fix(&m_vBgt[12],  260, 30 - 8);
				draw_fix(&m_vBgt[13],  160, 65 - 8);
				draw_fix(&m_vBgt[14],  200, 67 - 8);
				draw_fix(&m_vBgt[15],  240, 64 - 8);
			}

			if ( 20 <= m_iDemoProcessSub )
				draw_fix(&m_vMst[9], ( 320 - m_vMst[9].pTex->GetImgW() ) / 2, 210);
		}

	}
	else if(4 == m_nDemo)
	{
		if( 0 == m_iDemoProcess )
		{
			if( 0 <= m_iDemoProcessSub )
				draw_fix(&m_vBgt[0], 96, 5);

			if( 10 <= m_iDemoProcessSub && 20 > m_iDemoProcessSub )
				draw_fix(&m_vMst[0], ( 320 - m_vMst[0].pTex->GetImgW() ) / 2, 210);

			if( 20 <= m_iDemoProcessSub && 30 > m_iDemoProcessSub )
				draw_fix(&m_vMst[1], ( 320 - m_vMst[1].pTex->GetImgW() ) / 2, 210);
		}

		else if( 1 == m_iDemoProcess )
		{
			if( 0 <= m_iDemoProcessSub )
				draw_fix(&m_vBgt[1], 65, 6);

			if( 10 <= m_iDemoProcessSub && 20 > m_iDemoProcessSub )
				draw_fix(&m_vMst[2], ( 320 - m_vMst[2].pTex->GetImgW() ) / 2, 210);

			if( 20 <= m_iDemoProcessSub )
				draw_fix(&m_vBgt[2], 2, 100);

			if( 30 <= m_iDemoProcessSub && 40 > m_iDemoProcessSub )
				draw_fix(&m_vMst[3], ( 320 - m_vMst[3].pTex->GetImgW() ) / 2, 210);
		}
		else if( 2 == m_iDemoProcess )
		{
			if( 0 <= m_iDemoProcessSub )
				draw_fix(&m_vBgt[3], 95, 6);

			if( 10 <= m_iDemoProcessSub && 20 > m_iDemoProcessSub )
				draw_fix(&m_vMst[4], ( 320 - m_vMst[4].pTex->GetImgW() ) / 2, 210);

			if( 20 <= m_iDemoProcessSub && 30 > m_iDemoProcessSub )
				draw_fix(&m_vMst[5], ( 320 - m_vMst[5].pTex->GetImgW() ) / 2, 210);
		}

		else if( 3 == m_iDemoProcess )
		{
			if( 0 <= m_iDemoProcessSub )
				draw_fix(&m_vBgt[4], 1, 20);

			if( 10 <= m_iDemoProcessSub && 20 > m_iDemoProcessSub )
				draw_fix(&m_vMst[6], ( 320 - m_vMst[6].pTex->GetImgW() ) / 2, 210);
		}

		else if( 4 == m_iDemoProcess )
		{
			if( 0 <= m_iDemoProcessSub )
				draw_fix(&m_vBgt[5], 87, 0);

			if( 10 <= m_iDemoProcessSub && 20 > m_iDemoProcessSub )
			{
				draw_fix(&m_vMst[7], ( 320 - m_vMst[7].pTex->GetImgW() ) / 2, 210);
				draw_fix(&m_vMst[8], ( 320 - m_vMst[8].pTex->GetImgW() ) / 2, 210);
			}
		}

		else if ( 5 == m_iDemoProcess )
		{
			if ( 0 <= m_iDemoProcessSub )
				draw_fix(&m_vBgt[7], 12, 2);

			if ( 10 <= m_iDemoProcessSub )
			{
				draw_fix(&m_vBgt[ 8],  130, 30 - 8);
				draw_fix(&m_vBgt[ 9],  166, 33 - 8);
				draw_fix(&m_vBgt[10],  202, 27 - 8);
				draw_fix(&m_vBgt[11],  234, 30 - 8);
				draw_fix(&m_vBgt[12],  260, 30 - 8);
				draw_fix(&m_vBgt[13],  160, 65 - 8);
				draw_fix(&m_vBgt[14],  200, 67 - 8);
				draw_fix(&m_vBgt[15],  240, 64 - 8);
			}

			if ( 20 <= m_iDemoProcessSub )
				draw_fix(&m_vMst[9], ( 320 - m_vMst[9].pTex->GetImgW() ) / 2, 210);
		}
	}


}

