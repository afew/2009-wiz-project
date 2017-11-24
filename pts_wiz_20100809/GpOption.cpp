

#include "_StdAfx.h"


extern char* g_sSndBgm[8];
extern char* g_sSndSe[20];


CGpOption::CGpOption()
{
	m_bExit	= 0;

	m_nMode	= 0;		//現在選択されている?目	０：Ｇ?ＭＥＳＴ?ＲＴ?１：ＯＰＴＩＯＮ?２：ＥＸＩＴ
	m_nAg	= 0;
	memset(m_nSelct, 0, sizeof(m_nSelct));

	memset(m_nBak_scl, 0, sizeof(m_nBak_scl));
	memset(m_nBak_count, 0, sizeof(m_nBak_count));
	memset(m_nA, 0, sizeof(m_nA));
	memset(m_nB, 0, sizeof(m_nB));
	memset(m_nTolal_time, 0, sizeof(m_nTolal_time));
	memset(m_nTolal_time2, 0, sizeof(m_nTolal_time2));
	memset(m_nTolal_time3, 0, sizeof(m_nTolal_time3));

	memset(m_vTex, 0, sizeof(m_vTex) );

	m_pSndSe1	= NULL;
	m_pSndBg	= NULL;
}


CGpOption::~CGpOption()
{
}



int CGpOption::Init()
{
	int		i;
	int		wk;
	char	strbuf[1024];

	m_bExit = 1;

	m_nMode = 0;		//現在選択されている?目	０：Ｇ?ＭＥＳＴ?ＲＴ?１：ＯＰＴＩＯＮ?２：ＥＸＩＴ
	m_nAg = 0;
	memset( m_nSelct, 0, sizeof( m_nSelct ) );
	memset( m_nBak_scl, 0, sizeof( m_nBak_scl ) );
	memset( m_nBak_count, 0, sizeof( m_nBak_count ) );
	memset( m_nA, 0, sizeof( m_nA ) );
	memset( m_nB, 0, sizeof( m_nB ) );
	memset( m_nTolal_time, 0, sizeof( m_nTolal_time ) );
	memset( m_nTolal_time2, 0, sizeof( m_nTolal_time2 ) );
	memset( m_nTolal_time3, 0, sizeof( m_nTolal_time3 ) );
	memset( strbuf, 0, sizeof( strbuf ) );

	m_vTex[0] = g_pApp->m_pGpAct.m_vTex[61];
	m_vTex[1] = g_pApp->m_pGpAct.m_vTex[122];
	m_vTex[2] = g_pApp->m_pGpAct.m_vTex[18];


	if ( GetSceneGameFlag1(126) == 1 )
		LoadImage(&m_vTex[3], (char*)"image/title/option2.png", 1);		//プレ?ンナンバ?２にシステ?用ＢＭＰを読み込む
	else
		LoadImage(&m_vTex[3], (char*)"image/title/option1.png", 1);		//プレ?ンナンバ?２にシステ?用ＢＭＰを読み込む



	LoadImage(&m_vTex[4], (char*)"image/title/on_off.png", 1);								//プレ?ンナンバ?２にシステ?用ＢＭＰを読み込む



	m_nTolal_time[0] = 0;
	m_nTolal_time[1] = 0;
	m_nTolal_time[2] = 0;

	for ( i = 1; i <= 50; i++ )
	{
		wk = get2keta( GetSceneGameFlag1(200 + i), 1 );
		m_nTolal_time[0] = m_nTolal_time[0] + wk;
		if ( m_nTolal_time[0] >= 60 )
		{
			m_nTolal_time[0] = m_nTolal_time[0] - 60;
			m_nTolal_time[1]++;
		}

		wk = get2keta( GetSceneGameFlag1(200 + i), 100 );
		m_nTolal_time[1] = m_nTolal_time[1] + wk;
		if ( m_nTolal_time[1] >= 60 )
		{
			m_nTolal_time[1] = m_nTolal_time[1] - 60;
			m_nTolal_time[2]++;
		}


		wk = get2keta( GetSceneGameFlag1(200 + i), 10000 );
		m_nTolal_time[2] = m_nTolal_time[2] + wk;
		if ( m_nTolal_time[2] >= 999 )
		{
			m_nTolal_time[2] = 999;
			m_nTolal_time[1] = 59;
			m_nTolal_time[0] = 59;
		}


		/* スコア */
		wk = get2keta( GetSceneGameFlag1(250 + i), 1 );
		m_nTolal_time2[0] = m_nTolal_time2[0] + wk;
		if ( m_nTolal_time2[0] >= 60 )
		{
			m_nTolal_time2[0] = m_nTolal_time2[0] - 60;
			m_nTolal_time2[1]++;
		}


		wk = get2keta( GetSceneGameFlag1(250 + i), 100 );
		m_nTolal_time2[1] = m_nTolal_time2[1] + wk;
		if ( m_nTolal_time2[1] >= 60 )
		{
			m_nTolal_time2[1] = m_nTolal_time2[1] - 60;
			m_nTolal_time2[2]++;
		}


		wk = get2keta( GetSceneGameFlag1(250 + i), 10000 );
		m_nTolal_time2[2] = m_nTolal_time2[2] + wk;
		if ( m_nTolal_time2[2] >= 999 )
		{
			m_nTolal_time2[2] = 999;
			m_nTolal_time2[1] = 59;
			m_nTolal_time2[0] = 59;
		}
	}

	m_nTolal_time[3] = 0;
	for ( i = 1; i <= 50; i++ )
	{
		m_nTolal_time[3] = m_nTolal_time[3] + GetSceneGameFlag1(300 + i);
		m_nTolal_time2[3] = m_nTolal_time2[3] + GetSceneGameFlag1(350 + i);
	}



	/* スコア */
	m_nTolal_time3[0] = 0;
	m_nTolal_time3[1] = 0;
	m_nTolal_time3[2] = 0;
	m_nTolal_time3[3] = 0;

	wk = get2keta( GetSceneGameFlag1(137), 1 );
	m_nTolal_time3[0] = wk;

	wk = get2keta( GetSceneGameFlag1(137), 100 );
	m_nTolal_time3[1] = wk;

	wk = get2keta( GetSceneGameFlag1(137), 10000 );
	m_nTolal_time3[2] = wk;

	m_nTolal_time3[3] = GetSceneGameFlag1(138);

	m_nSelct[2] = GetSceneGameFlag1(133);	//アンカ??イプ
	m_nSelct[3] = GetSceneGameFlag1(134);	//アンカ??イプ

	DGX_CreateSound(NULL, &m_pSndSe1, g_sSndSe[EN_SE_SELECT] );

	return 0;
}


void CGpOption::Destroy()
{
	int i;

	for ( i = 0; i < OPTION_IMAGE_MAX; i++ )
	{
		if(0 == i || 1 == i || 2 == i)
			continue;

		ReleaseImage(&m_vTex[i]);
	}

	DGX_DestroySound(&m_pSndSe1);
	DGX_DestroySound(&m_pSndBg);
}


int CGpOption::Update()
{
	int		load_rc = 0;
	char	strbuf[260]={0};

	if ( m_nAg == 0 )
	{
		if ( g_pApp->IsPushKey( DGXKEY_UP ) )
		{
			DGX_SoundPlay( m_pSndSe1 );
			m_nMode--;
			if ( m_nMode == 14 )
			{
				m_nMode = 5;
			}
			if ( m_nMode <= -1 )
			{
				m_nMode = 15;
			}
		}
		else if ( g_pApp->IsPushKey( DGXKEY_DOWN ) )
		{
			DGX_SoundPlay( m_pSndSe1 );
			m_nMode++;
			if ( m_nMode == 6 )
			{
				m_nMode = 15;
			}
			if ( m_nMode >= 16 )
			{
				m_nMode = 0;
			}
		}
	}
	if ( g_pApp->IsPushKey( DGXKEY_LEFT ) )
	{
		DGX_SoundPlay( m_pSndSe1 );


		if ( m_nMode != 2 )		// is not Use up Key
			m_nSelct[m_nMode]--;


		if ( m_nSelct[m_nMode] < 0 )
		{
			m_nSelct[m_nMode] = 0;
		}
		if( ( m_nMode == 4 ) && ( m_nAg == 1 ) )
		{
			sprintf(strbuf,"image/option/%d.png", m_nSelct[m_nMode] );


			PDGE_TEXTURE	pTex = NULL;
			load_rc = LoadImage(&pTex, strbuf, FALSE );

			if(pTex)
			{
				ReleaseImage(&m_vTex[5]);
				m_vTex[5] = pTex;
			}
		}
	}
	else if ( g_pApp->IsPushKey( DGXKEY_RIGHT ) )
	{
		DGX_SoundPlay( m_pSndSe1 );


		if ( m_nMode != 2 )		// is not Use up Key
			m_nSelct[m_nMode]++;


		if ( m_nMode == 0 )	/* BGM */
		{
			if ( m_nSelct[m_nMode] > ( EN_BGM_END - 1 ) )
			{
				m_nSelct[m_nMode] = ( EN_BGM_END - 1 );
			}
		}
		if ( m_nMode == 1 )	/* SE */
		{
			if ( m_nSelct[m_nMode] > ( EN_SE_END - 1 ) )
			{
				m_nSelct[m_nMode] = ( EN_SE_END - 1 );
			}
		}
		if ( m_nMode == 2 )	/* 上ジャンプ */
		{
//			if ( m_nSelct[m_nMode] > 1 )
//			{
//				m_nSelct[m_nMode] = 1;
//			}
		}
		if ( m_nMode == 3 )	/* 開始演出 */
		{
			if ( m_nSelct[m_nMode] > 1 )
			{
				m_nSelct[m_nMode] = 1;
			}
		}
		if ( ( m_nMode == 4 ) && ( m_nAg == 1 ) )
		{
			if ( m_nSelct[m_nMode] > 16 )
			{
				m_nSelct[m_nMode] = 16;
			}
			sprintf(strbuf,"image/option/%d.png", m_nSelct[m_nMode] );

			PDGE_TEXTURE	pTex = NULL;
			load_rc = LoadImage(&pTex, strbuf, FALSE );

			if(NULL == pTex)
			{
				m_nSelct[m_nMode]--;
			}
			else
			{
				ReleaseImage(&m_vTex[5]);
				m_vTex[5] = pTex;
			}
		}
	}


	//	決定が押される
	if ( g_pApp->IsPushOKKey() )
	{
		if ( m_nMode == 15 )	/* Exit */
		{
			SetSceneGameFlag1(133, m_nSelct[2]);	//アンカ??イプ
			SetSceneGameFlag1(134, m_nSelct[3]);	//アンカ??イプ
			SaveGameFlag("config/config.fig");

			SetSceneGameFlag1(40, 1);						/* モ?ドによって変える */
			SetSceneState(EN_SN_TITLE);
			m_bExit=0;
		}

		// Ending...
		else if ( m_nMode == 5 )
		{
			if ( GetSceneGameFlag1(100) == 1 )
			{
				SetSceneGameFlag1(40, 5);						/* モ?ドによって変える */
				SetSceneState(EN_SN_ENDING);
				m_bExit=0;
			}
//			else
//			{
//				DGX_DestroySound(&m_pSndSe1);
//				DGX_CreateSound(NULL, &m_pSndSe1, g_sSndSe[EN_SE_MSG]);
//				DGX_SoundPlay( m_pSndSe1 );
//			}
		}
		else if ( m_nMode == 4 )
		{
			m_nAg = 1;
			sprintf(strbuf,"image/option/%d.png", m_nSelct[m_nMode] );

			ReleaseImage(&m_vTex[5]);
			LoadImage(&m_vTex[5], strbuf, FALSE );
		}
		else if ( m_nMode == 1 )	/* se test */
		{
			PDGX_SOUND	pSnd = NULL;
			char* sSound = g_sSndSe[ m_nSelct[m_nMode] ];

			DGX_CreateSound(NULL, &pSnd, sSound);

			if(pSnd)
			{
				DGX_DestroySound(&m_pSndSe1);
				m_pSndSe1 = pSnd;
				DGX_SoundPlay( m_pSndSe1 );
			}
		}
		else if ( m_nMode == 0 )	/* bgm test */
		{
			PDGX_SOUND	pSnd = NULL;
			char* sSound = g_sSndBgm[  m_nSelct[m_nMode] ];

			DGX_CreateSound(NULL, &pSnd, sSound);

			if(pSnd)
			{
				DGX_DestroySound(&m_pSndBg);
				m_pSndBg = pSnd;
				DGX_SoundPlay( m_pSndBg );
			}
		}
	}

	//	キャンセルが押される
	if ( g_pApp->IsPushCancelKey(  ) )
	{
		if ( m_nMode == 13 )	/* Exit */
		{
		}
		else if ( m_nMode == 6 )
		{
		}
		else if ( m_nMode == 5 )
		{
		}
		else if ( m_nMode == 4 )
		{
			m_nAg = 0;
		}
		else if ( m_nMode == 3 )
		{
			m_nSelct[m_nMode] = 0;
		}
		else if ( m_nMode == 2 )
		{
//			m_nSelct[m_nMode] = 0;
		}
		else if ( m_nMode == 1 )	/* se test */
		{
			DGX_DestroySound(&m_pSndSe1);
			DGX_DestroySound(&m_pSndBg);
		}
		else if ( m_nMode == 0 )	/* bgm test */
		{
			DGX_DestroySound(&m_pSndBg);
		}

		if ( m_nAg == 1 )
		{
			m_nAg = 0;
		}
	}


	return m_bExit;
}


void CGpOption::Render()
{
	int i;
	int x, y;


	m_nA[0]++;
	if ( m_nA[0] > 100 )
	{
		m_nA[0] = 0;
	}
	m_nA[1]++;
	if ( m_nA[1] >= 40 )
	{
		m_nA[1] = 0;
	}
	for ( x = 0; x < 5; x++ )
	{
		for ( y = 0; y < 4; y++ )
		{
			Blt(m_vTex[1], ( x * 100 )- m_nA[0], ( y * 100 ) - m_nA[0] );
		}
	}



	if ( m_nAg == 0 )
	{
		Blt(m_vTex[3], 60, 40 );
		BltRect(m_vTex[0], 40, 52 + ( m_nMode * 8 ) , 0 + ( m_nA[1] / 10 ) * 16 , 0, 16, 16 );

		for ( i = 0; i < 2 ; i++ )
		{
			//数値の?目
			BltNumericImage( m_nSelct[i], 2, 200, 56 + ( i * 8 ), m_vTex[2], 0, 0, 10, 8 );	/*  */
		}
		BltRect(m_vTex[4] , 200, 56 + ( 2 * 8 ), 0, ( m_nSelct[2] ) * 8 , 200, 8 );	/* lvel */
		BltRect(m_vTex[4] , 200, 56 + ( 3 * 8 ), 0, ( m_nSelct[3] ) * 8 , 200, 8 );	/* lvel */

		BltNumericImage2( GetSceneGameFlag1(110), 3, 180, 64 + ( 6 * 8 ), m_vTex[2], 0, 0, 10, 8 );			/* プレイ?イ? */
		BltNumericImage( GetSceneGameFlag1(109), 2, 200 + 20 + 10, 64 + ( 6 * 8 ), m_vTex[2], 0, 0, 10, 8 );	/* プレイ?イ? */
		BltNumericImage( GetSceneGameFlag1(108), 2, 200 + 40 + 20, 64 + ( 6 * 8 ), m_vTex[2], 0, 0, 10, 8 );	/* プレイ?イ? */

		BltNumericImage2( m_nTolal_time[2], 3, 180, 64 + ( 7 * 8 ), m_vTex[2], 0, 0, 10, 8 );			/* クリア?イ? */
		BltNumericImage( m_nTolal_time[1], 2, 200 + 20 + 10, 64 + ( 7 * 8 ), m_vTex[2], 0, 0, 10, 8 );	/* クリア?イ? */
		BltNumericImage( m_nTolal_time[0], 2, 200 + 40 + 20, 64 + ( 7 * 8 ), m_vTex[2], 0, 0, 10, 8 );	/* クリア?イ? */

		BltNumericImage2( m_nTolal_time[3], 4, 170, 64 + ( 8 * 8 ), m_vTex[2], 0, 0, 10, 8 );				/* 回?回数 */


		if ( GetSceneGameFlag1(126) == 1 )
		{
			BltNumericImage2( m_nTolal_time2[2], 3, 180, 64 + ( 12 * 8 ), m_vTex[2], 0, 0, 10, 8 );	/* 資金 */
			BltNumericImage( m_nTolal_time2[1], 2, 200 + 20 + 10, 64 + ( 12 * 8 ), m_vTex[2], 0, 0, 10, 8 );	/* 資金 */
			BltNumericImage( m_nTolal_time2[0], 2, 200 + 40 + 20, 64 + ( 12 * 8 ), m_vTex[2], 0, 0, 10, 8 );	/* 資金 */

			BltNumericImage2( m_nTolal_time2[3], 4, 170, 64 + ( 13 * 8 ), m_vTex[2], 0, 0, 10, 8 );	/* 資金 */
		}

	}
	else
	{
		/* ギャラリ?モ?ド */
		/* ギャラリ?モ?ド */
		Blt(m_vTex[5], 0, 0 );

		BltNumericImage( m_nSelct[m_nMode], 2, 300, 230, m_vTex[2], 0, 0, 10, 8 );	/* No. */
	}
}

