

#include "_StdAfx.h"


extern char* g_sSndBgm[8];
extern char* g_sSndSe[20];


CGpStage::CGpStage()
{
	m_bExit	= 0;

	m_nMode	= 0;
	memset(m_nA, 0, sizeof(m_nA));
	memset(m_nCsl, 0, sizeof(m_nCsl));
	memset(m_nTarget_save, 0, sizeof(m_nTarget_save));

	memset(m_vTex, 0, sizeof(m_vTex) );
}


CGpStage::~CGpStage()
{
}




int CGpStage::Init()
{
	m_bExit = 1;

	m_nMode = 0;		//現在選択されている?目	０：Ｇ?ＭＥＳＴ?ＲＴ?１：ＯＰＴＩＯＮ?２：ＥＸＩＴ
	memset( m_nA, 0, sizeof( m_nA ) );
	memset( m_nCsl, 0, sizeof( m_nCsl ) );
	memset( m_nTarget_save, 0, sizeof( m_nTarget_save ) );

	m_nCsl[1] = ( GetSceneGameFlag1(120) / 10 );
	m_nCsl[0] = ( GetSceneGameFlag1(120) % 10 ) - 1;
	if ( ( GetSceneGameFlag1(120) % 10 ) == 0 )
	{
		m_nCsl[1] = m_nCsl[1] - 1;
		m_nCsl[0] = 9 ;
	}


	m_vTex[0] = g_pApp->m_pGpAct.m_vTex[121];
	m_vTex[1] = g_pApp->m_pGpAct.m_vTex[122];
	m_vTex[2] = g_pApp->m_pGpAct.m_vTex[61];
	m_vTex[3] = g_pApp->m_pGpAct.m_vTex[6];
	m_vTex[4] = g_pApp->m_pGpAct.m_vTex[18];


	LoadFile( "save/target", &m_nTarget_save[0], sizeof( m_nTarget_save ) );


	DGX_SoundRepeat(g_pApp->m_pSndBg);
	DGX_SoundPlay( g_pApp->m_pSndBg );


	SetSceneGameFlag1(70, 0);

	return 0;
}


void CGpStage::Destroy()
{
	DGX_SoundStop( g_pApp->m_pSndBg );
}



int CGpStage::Update()
{
	if ( g_pApp->IsPushKey( DGXKEY_UP ) )
	{
		DGX_SoundPlay( g_pApp->m_pGpAct.m_pSndSe[EN_SE_SELECT] );

		m_nCsl[0]--;
		if ( m_nCsl[0] < 0 )
		{
			m_nCsl[0] = 10;
		}
	}
	else if ( g_pApp->IsPushKey( DGXKEY_DOWN ) )
	{
		DGX_SoundPlay( g_pApp->m_pGpAct.m_pSndSe[EN_SE_SELECT] );

		m_nCsl[0]++;
		if ( m_nCsl[0] >= 11 )
		{
			m_nCsl[0] = 0;
		}
	}

	if ( g_pApp->IsPushKey( DGXKEY_LEFT ) )
	{
		DGX_SoundPlay( g_pApp->m_pGpAct.m_pSndSe[EN_SE_SELECT] );

		m_nCsl[1]--;
		if ( m_nCsl[1] < 0 )
		{
			m_nCsl[1] = 4;
		}
	}
	else if ( g_pApp->IsPushKey( DGXKEY_RIGHT ) )
	{
		DGX_SoundPlay( g_pApp->m_pGpAct.m_pSndSe[EN_SE_SELECT] );

		m_nCsl[1]++;
		if ( m_nCsl[1] >= 5 )
		{
			m_nCsl[1] = 0;
		}
	}

	//	決定キ?を押した
	if ( g_pApp->IsPushOKKey() )
	{
		if ( m_nCsl[0] == 10 )
		{
			//exit
			SetSceneState(EN_SN_TITLE);
			m_bExit=0;
		}
		else
		{
			ResetGameFlag2();

			stageselect_init_save_data();

			SetSceneGameFlag1(127, 0);	//ト??ルア?ック
			SetSceneGameFlag1(123,-1);	//リプレイ選択時のステ?ジ
			SetSceneGameFlag1(132, 0);		//リプレイ
			SetSceneGameFlag1(70 , 1);
			SetSceneGameFlag1(128, 0);	//?ップビュ?
			SetSceneGameFlag1(129, 1);	//ステ?ジセレクトから開始
			SaveGameFlag2( "save/work.sav");

			ResetGameFlag2();
			SaveGameFlag2( "save/item_wk.sav");

			SetSceneGameFlag1(40, 4);
			SetSceneState(EN_SN_ACT);
			m_bExit=0;

			return m_bExit;
		}
	}

	//	キャンセルキ?を押した
	if ( g_pApp->IsPushCancelKey() )
	{
		SetSceneState(EN_SN_TITLE);
		m_bExit=0;
	}

	return m_bExit;
}

void CGpStage::Render()
{
	int stage_hosei;
	int x;
	int y;
	int wk;
	int stage_no;
	int tergetnam;


	tergetnam = 0;
	stage_hosei = 0;

	if ( GetSceneGameFlag1(126) == 1 )
	{
		stage_hosei = 50;
	}

//		Blt(m_vTex[5, 0, 0 );
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

	//いろつけ
	tergetnam = 0;
	for ( x = 0; x < 5; x++ )
	{
		for ( y = 0; y < 10; y++ )
		{
			stage_no = ( ( x ) * 10 ) + ( y + 1 );
			//トロフィ?の?示
			//?イ?
			tergetnam = 0;
			if ( m_nTarget_save[200 + stage_no + stage_hosei] >= GetSceneGameFlag1(200 + stage_no + stage_hosei) )
			{
				tergetnam++;
			}
			//回?
			if ( m_nTarget_save[300 + stage_no + stage_hosei] >= GetSceneGameFlag1(300 + stage_no + stage_hosei) )
			{
				tergetnam++;
			}
			//隠し
			if ( GetSceneGameFlag1(400 + stage_no + stage_hosei) != 0 )
			{
				tergetnam++;
			}
			BltRect(m_vTex[2], 15 + ( x * 64 ) , 32 + ( y * 8 ), 0, 96 + ( tergetnam * 7 ) , 41 , 7 );	/* 達成度 */
		}
	}

	Blt(m_vTex[0], 0, 0 );
	if ( m_nCsl[0] == 10 )
	{
		// exit
		BltRect(m_vTex[2], 0 + ( 2 * 64 ) , 32 + ( 10 * 8 ), ( m_nA[1] / 10 ) * 16, 0 , 16 , 16 );	/* カ??ル */
	}
	else
	{
		BltNumericImage( m_nCsl[1] + 1, 1, 174, 135, m_vTex[4], 0, 0, 10, 8 );	/*  */
		BltNumericImage( m_nCsl[0] + 1 + ( m_nCsl[1] * 10 ), 2, 192, 135, m_vTex[4], 0, 0, 10, 8 );	/*  */

		BltRect(m_vTex[2], 0 + ( m_nCsl[1] * 64 ) , 28 + ( m_nCsl[0] * 8 ), ( m_nA[1] / 10 ) * 16, 0 , 16 , 16 );	/* カ??ル */

		stage_no = ( ( m_nCsl[1] ) * 10 ) + ( m_nCsl[0] + 1 );

		wk = get2keta( GetSceneGameFlag1(200 + stage_no + stage_hosei), 1 );
		BltNumericImage( wk, 2, 250, 148, m_vTex[4], 0, 0, 10, 8 );	/*  */
		wk = get2keta( GetSceneGameFlag1(200 + stage_no + stage_hosei), 100 );
		BltNumericImage( wk, 2, 220, 148, m_vTex[4], 0, 0, 10, 8 );	/*  */
		wk = get2keta( GetSceneGameFlag1(200 + stage_no + stage_hosei), 10000 );
		BltNumericImage( wk, 2, 190, 148, m_vTex[4], 0, 0, 10, 8 );	/*  */
		BltNumericImage2( GetSceneGameFlag1(300 + stage_no + stage_hosei), 2, 190, 178, m_vTex[4], 0, 0, 10, 8 );	/* Jump_counts */

		if ( GetSceneGameFlag1(300 + stage_no + stage_hosei) != 99 )
		{
			BltRect(m_vTex[3], 250, 180, 0 + ( ( ( stage_no - 1 ) % 10 ) * 32 ), 160 + ( ( ( stage_no - 1 ) / 10 ) * 32 ), 32, 32 );	/*  */
		}


		wk = get2keta( m_nTarget_save[200 + stage_no + stage_hosei], 1 );
		BltNumericImage( wk, 2, 250, 156, m_vTex[4], 0, 0, 10, 8 );	/*  */
		wk = get2keta( m_nTarget_save[200 + stage_no + stage_hosei], 100 );
		BltNumericImage( wk, 2, 220, 156, m_vTex[4], 0, 0, 10, 8 );	/*  */
		wk = get2keta( m_nTarget_save[200 + stage_no + stage_hosei], 10000 );
		BltNumericImage( wk, 2, 190, 156, m_vTex[4], 0, 0, 10, 8 );	/*  */
		BltNumericImage2( m_nTarget_save[300 + stage_no + stage_hosei], 2, 190, 186, m_vTex[4], 0, 0, 10, 8 );	/* Jump_counts */

		//トロフィ?の?示
		//?イ?
		if ( m_nTarget_save[200 + stage_no + stage_hosei] >= GetSceneGameFlag1(200 + stage_no + stage_hosei) )
		{
			BltRect(m_vTex[2], 0, 138, 0, 64, 32, 32 );	/* ?イ? */
			BltRect(m_vTex[2], 0 + 5, 138 + 4, 32 + ( ( ( m_nA[0] / 10 ) % 2 ) * 5 ), 37 , 5 , 7 );	/* カ??ル */
			BltRect(m_vTex[2], 0 + 20, 138 + 14, 32 + ( ( ( m_nA[0] / 10 ) % 2 ) * 5 ), 37 , 5 , 7 );	/* カ??ル */
		}
		else
		{
			BltRect(m_vTex[2], 0, 138, 0, 32, 32, 32 );	/* 土台 */
		}
		//回?
		if ( m_nTarget_save[300 + stage_no + stage_hosei] >= GetSceneGameFlag1(300 + stage_no + stage_hosei) )
		{
			BltRect(m_vTex[2], 0, 170, 32, 64, 32, 32 );	/* ?イ? */
			BltRect(m_vTex[2], 0 + 5, 170 + 4, 32 + ( ( ( m_nA[0] / 10 ) % 2 ) * 5 ), 37 , 5 , 7 );	/* カ??ル */
			BltRect(m_vTex[2], 0 + 20, 170 + 14, 32 + ( ( ( m_nA[0] / 10 ) % 2 ) * 5 ), 37 , 5 , 7 );	/* カ??ル */
		}
		else
		{
			BltRect(m_vTex[2], 0, 170, 0, 32, 32, 32 );	/* 土台 */
		}
		//隠し
		if ( GetSceneGameFlag1(400 + stage_no + stage_hosei) != 0 )
		{
			BltRect(m_vTex[4], 190, 214, 0, 176, 200, 8 );	/* ?イ? */
			BltRect(m_vTex[2], 0, 202, 64, 64, 32, 32 );	/* ?イ? */
			BltRect(m_vTex[2], 0 + 5, 202 + 4, 32 + ( ( ( m_nA[0] / 10 ) % 2 ) * 5 ), 37 , 5 , 7 );	/* カ??ル */
			BltRect(m_vTex[2], 0 + 20, 202 + 14, 32 + ( ( ( m_nA[0] / 10 ) % 2 ) * 5 ), 37 , 5 , 7 );	/* カ??ル */
		}
		else
		{
			BltRect(m_vTex[4], 190, 214, 0, 168, 200, 8 );	/* ?イ? */
			BltRect(m_vTex[2], 0, 202, 0, 32, 32, 32 );	/* 土台 */
		}

	}

}


/***************************************************************************/
// NAME      = init_save_data
// FUNCTION  = セ?ブフ?イルの初期値を設定
// NOTES     =
// DATE      =
// AUTHER    = koizumi
// HISTORY   =
// PARAMETER = なし
// RETURN    = なし
/***************************************************************************/
void CGpStage::stageselect_init_save_data()
{
	SetSceneGameFlag2(0, 8 * 32 );	/* Ｘ */
	SetSceneGameFlag2(1, ( 2 * 32 ) - 16);	/* Ｙ */

	if ( GetSceneGameFlag1(126) == 1 )
	{
		SetSceneGameFlag2(2, 2);	/* ステ?ジ */
	}
	else
	{
		SetSceneGameFlag2(2, 1);	/* ステ?ジ */
	}

	SetSceneGameFlag1(120, ( ( m_nCsl[1] ) * 10 ) + ( m_nCsl[0] + 1 )  );
	SetSceneGameFlag2( 3, GetSceneGameFlag1(120) );	/* 画面Ｎｏ */
	SetSceneGameFlag2( 4, 0);	/* 向き */
	SetSceneGameFlag2( 5, 3);	/* 現在ＨＰ */
	SetSceneGameFlag2( 6, 3);	/* 最大ＨＰ */
	SetSceneGameFlag2( 7, 0);	/* ハ?トのかけら所持個数 */
	SetSceneGameFlag2( 8, 0);	/* 現在設定スキル */
	SetSceneGameFlag2( 9, 0);	/* テレ???使用不可、スクロ?ル不可フラグ */
	SetSceneGameFlag2(10, 0);	/* テレ???使用不可フラグ */

	SetSceneGameFlag2(20, 0); 	/* 時 */
	SetSceneGameFlag2(21, 0); 	/* 分 */
	SetSceneGameFlag2(22, 0); 	/* 秒 */

	SetSceneGameFlag2(30, 0);	/* テレ????使用 */
	SetSceneGameFlag2(31, 0);	/* テレ????ステ?ジ */
	SetSceneGameFlag2(32, 0);	/* テレ????画面Ｎｏ */
	SetSceneGameFlag2(33, 0);	/* テレ????Ｘ */
	SetSceneGameFlag2(34, 0);	/* テレ????Ｙ */

	SetSceneGameFlag2(40, 0);	/* 取得スキル１ */
	SetSceneGameFlag2(41, 0);	/* 取得スキル２ */
	SetSceneGameFlag2(42, 0);	/* 取得スキル３ */
	SetSceneGameFlag2(43, 0);	/* 取得スキル４ */

}



