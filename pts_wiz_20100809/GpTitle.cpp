

#include "_StdAfx.h"


extern char* g_sSndBgm[8];
extern char* g_sSndSe[20];


// ＢＭＰ用定数
enum
{
	EN_TITLE_image1 = 1,
	EN_TITLE_image2,
	EN_TITLE_image3,
	EN_TITLE_image4,
	EN_TITLE_image5,
	EN_TITLE_image6,
};


enum
{
	EN_TITLE_NONE		= -1,
	EN_TITLE_START		= 0,
	EN_TITLE_VIEW_MAP	= 1,
//	EN_TITLE_REPLAY		,
	EN_TITLE_SELECT_STAGE,
//	EN_TITLE_TUTORIAL	,
	EN_TITLE_OPTION		,
	EN_TITLE_EXIT		,
	EN_TITLE_END		,
};



CGpTitle::CGpTitle()
{
	m_bExit=0;
	m_nMode= EN_TITLE_START;
	memset(m_nA, 0, sizeof(m_nA));
	memset(m_nB, 0, sizeof(m_nB));
	m_nCaslanm = 0 ;
	memset(m_nKane, 0, sizeof(m_nKane) );

	m_nUracount = 0;
	m_nTitle = 0;

	memset(m_vTex, 0, sizeof(m_vTex));
}


CGpTitle::~CGpTitle()
{
}



int CGpTitle::Init()
{
// Sound Test
//	int	i=0, j=0;
//
//	while(g_sSndBgm[i])
//	{
//		DGX_CreateSound(NULL, &m_pSndT[i+j], g_sSndBgm[i]);
//		++i;
//	}
//
//	while(g_sSndSe[j])
//	{
//		DGX_CreateSound(NULL, &m_pSndT[i+j], g_sSndSe[j]);
//		++j;
//	}
//
//	for(i=0; i<32; ++i)
//		DGX_SoundPlay(m_pSndT[i]);
//
//	DGX_SoundPlay(m_pSndT[25]);




	DWORD	dColorKey = 0xFF10633E;


	m_bExit = 1;

	m_nTitle = 0;
	m_nMode = EN_TITLE_START;		//現在選択されている?目	０：Ｇ?ＭＥＳＴ?ＲＴ?１：ＯＰＴＩＯＮ?２：ＥＸＩＴ
	memset( m_nKane, 0, sizeof( m_nKane ) );
	m_nUracount = 0;
	m_nTitle = 0;
	m_nCaslanm = 0;

	if(NULL == m_vTex[1])	LoadImage(&m_vTex[1], (char*)"image/title/title_pipi.png", dColorKey);		//プレ?ンナンバ?２にシステ?用ＢＭＰを読み込む
	if(NULL == m_vTex[2])	LoadImage(&m_vTex[2], (char*)"image/title/title2.png", dColorKey);			//プレ?ンナンバ?２にシステ?用ＢＭＰを読み込む

	m_vTex[3] = g_pApp->m_pGpAct.m_vTex[61];
	m_vTex[5] = g_pApp->m_pGpAct.m_vTex[110];


	if(NULL == m_vTex[7])
	{
		if ( GetSceneGameFlag1(126) == 0)	LoadImage(&m_vTex[7], (char*)"image/title/title5.png", dColorKey);		//プレ?ンナンバ?２にシステ?用ＢＭＰを読み込む
		else								LoadImage(&m_vTex[7], (char*)"image/title/title5_ura.png",dColorKey);		//プレ?ンナンバ?２にシステ?用ＢＭＰを読み込む
	}



	m_vTex[18] = g_pApp->m_pGpAct.m_vTex[18];


	m_nA[0] = 100;
	m_nA[1] = 200;
	title_kane_set( 0, 300 );

	if ( GetSceneGameFlag1(123) != -1 )
		SetSceneGameFlag1(120, GetSceneGameFlag1(123) );	//リプレイ選択時のステ?ジ


	if ( GetSceneGameFlag1(120) > 50 )
		SetSceneGameFlag1(120, 50);



	// Background Sound Create
	if(NULL == g_pApp->m_pSndBg)
		DGX_CreateSound(NULL, &g_pApp->m_pSndBg, g_sSndBgm[EN_BGM_GAME01]);


	DGX_SoundRepeat( g_pApp->m_pSndBg );
	DGX_SoundPlay( g_pApp->m_pSndBg );

	return 0;
}


void CGpTitle::Destroy()
{
	DGX_SoundStop(g_pApp->m_pSndBg);
}


void CGpTitle::ReleseTexture()
{
	int i;
	for ( i = 0; i < BMPBUFF_MAX; i++ )
	{
		if(3 == i || 5 == i || 18 == i)
			continue;

		ReleaseImage(&m_vTex[i]);
	}
}


int CGpTitle::Update()
{
	if ( g_pApp->IsPushKey( DGXKEY_UP ) )
	{
		DGX_SoundPlay( g_pApp->m_pGpAct.m_pSndSe[EN_SE_SELECT] );
		m_nMode--;
		if ( m_nMode == EN_TITLE_NONE )
		{
			m_nMode = EN_TITLE_EXIT;
		}
	}
	else if ( g_pApp->IsPushKey( DGXKEY_DOWN ) )
	{
		DGX_SoundPlay( g_pApp->m_pGpAct.m_pSndSe[EN_SE_SELECT] );
		m_nMode++;
		if ( m_nMode == EN_TITLE_END )
		{
			m_nMode = EN_TITLE_START;
		}
	}


	if ( g_pApp->IsPushKey( DGXKEY_LEFT ) )
	{
		if ( m_nMode == EN_TITLE_START || m_nMode == EN_TITLE_VIEW_MAP )
		{
//			int t = DGXKEY_LEFT;
//			printf("GpTitle: %d\n", t);
			
			DGX_SoundPlay( g_pApp->m_pGpAct.m_pSndSe[EN_SE_SELECT] );

			int nState = GetSceneGameFlag1(120);
			--nState;
			SetSceneGameFlag1(120, nState);

			if ( GetSceneGameFlag1(120) < 1 )
			{
				SetSceneGameFlag1(120, GetSceneGameFlag1(121) );

				if ( GetSceneGameFlag1(120) > 50 )
				{
					SetSceneGameFlag1(120, 50);
				}
			}
		}

		//(E) 2010-07-27 Editor: AFEW
//		if ( m_nMode == EN_TITLE_REPLAY )
//		{
//			int t = DGXKEY_LEFT;
//			printf("GpTitle: %d\n", t);
//
//			DGX_SoundPlay( g_pApp->m_pGpAct.m_pSndSe[EN_SE_SELECT] );
//
//			int nState = GetSceneGameFlag1(124);
//			--nState;
//			SetSceneGameFlag1(124, nState);
//
//			if ( GetSceneGameFlag1(124) < 0 )
//			{
//				SetSceneGameFlag1(124, 1);
//			}
//		}

	}

	else if ( g_pApp->IsPushKey( DGXKEY_RIGHT ) )
	{
		if ( m_nMode == EN_TITLE_START || m_nMode == EN_TITLE_VIEW_MAP )
		{
			DGX_SoundPlay( g_pApp->m_pGpAct.m_pSndSe[EN_SE_SELECT] );
			int nState = GetSceneGameFlag1(120);
			++nState;
			SetSceneGameFlag1(120, nState);

			if ( ( GetSceneGameFlag1(120) > GetSceneGameFlag1(121) ) || ( GetSceneGameFlag1(120) > 50 ) )
			{
				SetSceneGameFlag1(120, 1);
			}
		}

		//(E) 2010-07-27 Editor: AFEW
		// Replay
//		if ( m_nMode == EN_TITLE_REPLAY )
//		{
//			DGX_SoundPlay( g_pApp->m_pGpAct.m_pSndSe[EN_SE_SELECT] );
//			int nState = GetSceneGameFlag1(124);
//			++nState;
//			SetSceneGameFlag1(124, nState);
//
//			if ( GetSceneGameFlag1(124) > 1 )
//			{
//				SetSceneGameFlag1(124, 0);
//			}
//		}

	}

	if ( g_pApp->IsPressKey( DGXKEY_LEFT ) )
	{
		m_nB[0]++;

		if ( m_nMode == EN_TITLE_START || m_nMode == EN_TITLE_VIEW_MAP )
		{
			if ( m_nB[0] >= 12 )
			{
				m_nB[0] = 0;

				DGX_SoundPlay( g_pApp->m_pGpAct.m_pSndSe[EN_SE_SELECT] );

				int nState = GetSceneGameFlag1(120);
				--nState;
				SetSceneGameFlag1(120, nState);

				if ( GetSceneGameFlag1(120) < 1 )
				{
					SetSceneGameFlag1(120, GetSceneGameFlag1(121) );

					if ( GetSceneGameFlag1(120) > 50 )
					{
						SetSceneGameFlag1(120, 50);
					}
				}
			}
		}
	}
	else if ( g_pApp->IsPressKey( DGXKEY_RIGHT ) )
	{
		m_nB[0]++;
		if ( m_nMode == EN_TITLE_START || m_nMode == EN_TITLE_VIEW_MAP )
		{
			if ( m_nB[0] >= 12 )
			{
				m_nB[0] = 0;

				DGX_SoundPlay( g_pApp->m_pGpAct.m_pSndSe[EN_SE_SELECT] );

				int nState = GetSceneGameFlag1(120);
				nState++;
				SetSceneGameFlag1(120, nState);

				if ( ( GetSceneGameFlag1(120) > GetSceneGameFlag1(121) ) || ( GetSceneGameFlag1(120) > 50 ) )
				{
					SetSceneGameFlag1(120, 1);
				}
			}
		}
	}
	else
	{
		m_nB[0] = 0;
	}

	//	決定キ?を押した
	if ( g_pApp->IsPushOKKey() )
	{
		if ( m_nMode == EN_TITLE_EXIT )					/* Exit */
		{
			SetSceneGameFlag1(123, -1);		//リプレイ選択時のステ?ジ
			SetSceneGameFlag1(40 , 10);		/* モ?ドによって変える */
			SetSceneState(EN_SN_EXIT);
			m_bExit=0;
		}
		else if ( m_nMode == EN_TITLE_OPTION )			/* option */
		{
			SetSceneGameFlag1(123, -1);		//リプレイ選択時のステ?ジ
			SetSceneGameFlag1(40 ,  3);
			SetSceneState(EN_SN_OPTION);
			m_bExit=0;
		}
		else if ( m_nMode == EN_TITLE_SELECT_STAGE )		/* stage select */
		{
			SetSceneGameFlag1(70, 1);
			SetSceneState(EN_SN_STAGE);
			m_bExit=0;
		}

		//(E) 2010-07-27 Editor: AFEW
		// Tutorial
//		else if ( m_nMode == EN_TITLE_TUTORIAL )			/* demo */
//		{
//			ResetGameFlag2();
//
//			title_init_save_data();
//
//			SetSceneGameFlag1(125, 0);	/* replay nomal */
//			SetSceneGameFlag1(123, GetSceneGameFlag1(120));	//リプレイ選択時のステ?ジ
//			SetSceneGameFlag1(132, 1);		//リプレイ
//
//			SetSceneGameFlag1( 70, 1);
//			SetSceneGameFlag1(128, 0);	//?ップビュ?
//			SetSceneGameFlag1(129, 0);	//ステ?ジセレクトから開始
//
//			SaveGameFlag2( "save/work.sav");
//
//			ResetGameFlag2();
//			SaveGameFlag2( "save/item_wk.sav");
//
//			SetSceneGameFlag1(40, 4);
//
//			SetSceneState(EN_SN_ACT);
//			m_bExit=0;
//		}
		

		//(E) 2010-07-27 Editor: AFEW
		// Replay
//		else if ( m_nMode == EN_TITLE_REPLAY )
//		{
//			if ( replay_file_find() == 1 )
//			{
//				ResetGameFlag2();
//
//				title_init_save_data();
//
//				SetSceneGameFlag1(127, 0);	//ト??ルア?ック
//				SetSceneGameFlag1(125, 0);	/* replay nomal */
//				SetSceneGameFlag1(123, GetSceneGameFlag1(120) );	//リプレイ選択時のステ?ジ
//				SetSceneGameFlag1(132, 1);		//リプレイ
//				SetSceneGameFlag1( 70, 1);
//				SetSceneGameFlag1(128, 0);	//?ップビュ?
//				SetSceneGameFlag1(129, 0);	//ステ?ジセレクトから開始
//
//				SaveGameFlag2( "save/work.sav");
//
//				ResetGameFlag2();
//				SaveGameFlag2( "save/item_wk.sav");
//
//				SetSceneGameFlag1(40, 4);
//
//				SetSceneState(EN_SN_ACT);
//				m_bExit=0;
//
//				return m_bExit;
//			}
//
//			else
//			{
//				DGX_SoundPlay( g_pApp->m_pGpAct.m_pSndSe[EN_SE_MSG] );
//			}
//
//		}

		else if ( m_nMode == EN_TITLE_VIEW_MAP )			// map view
		{
			ResetGameFlag2();

			title_init_save_data();

			SetSceneGameFlag1(127, 0);		//ト??ルア?ック
			SetSceneGameFlag1(123,-1);		//リプレイ選択時のステ?ジ
			SetSceneGameFlag1(132, 0);		//リプレイ
			SetSceneGameFlag1( 70, 1);
			SetSceneGameFlag1(128, 1);		//?ップビュ?
			SetSceneGameFlag1(129, 0);		//ステ?ジセレクトから開始

			SaveGameFlag2( "save/work.sav");

			ResetGameFlag2();
			SaveGameFlag2( "save/item_wk.sav");

			SetSceneGameFlag1(40, 4);

			SetSceneState(EN_SN_ACT);

			m_bExit=0;

			return m_bExit;

		}

		else if ( m_nMode == EN_TITLE_START )	/* new */
		{
			ResetGameFlag2();

			title_init_save_data();

			SetSceneGameFlag1(127, 0);	//ト??ルア?ック
			SetSceneGameFlag1(123,-1);	//リプレイ選択時のステ?ジ
			SetSceneGameFlag1(132, 0);		//リプレイ
			SetSceneGameFlag1( 70, 1);
			SetSceneGameFlag1(128, 0);	//?ップビュ?
			SetSceneGameFlag1(129, 0);	//ステ?ジセレクトから開始

			SaveGameFlag2( "save/work.sav");

			ResetGameFlag2();
			SaveGameFlag2( "save/item_wk.sav");

			SetSceneGameFlag1(40, 4);
			SetSceneState(EN_SN_ACT);

			m_bExit=0;

			if (
			     ( GetSceneGameFlag1(120) == 1 )
			  || ( GetSceneGameFlag1(120) == 11 )
			  || ( GetSceneGameFlag1(120) == 21 )
			  || ( GetSceneGameFlag1(120) == 31 )
			  || ( GetSceneGameFlag1(120) == 41 )
			   )
			{
				SetSceneState(EN_SN_DEMO);
			}

			return m_bExit;
		}

	}
	//	キャンセルキ?を押した
	if ( g_pApp->IsPushCancelKey() )
	{
		if ( m_nMode == EN_TITLE_START )	/* 裏面 */
		{
/*
			if ( GetSceneGameFlag1(100] == 1 )
			{
				m_nUracount++;
				if ( m_nUracount >= 16 )
				{
					if ( GetSceneGameFlag1(126] == 0 )
					{
						GetSceneGameFlag1(126] = 1;
						LoadImage("image/title/title5_ura.png",7,dColorKey);				//プレ?ンナンバ?２にシステ?用ＢＭＰを読み込む
					}
					else
					{
						GetSceneGameFlag1(126] = 0;
						LoadImage("image/title/title5.png",7,dColorKey);				//プレ?ンナンバ?２にシステ?用ＢＭＰを読み込む
					}
					m_nUracount = 0;
				}
			}
*/
		}


		//(E) 2010-07-27 Editor: AFEW
		// Replay jamp
//		if ( m_nMode == EN_TITLE_REPLAY )
//		{
//			if ( replay_file_find2() == 1 )
//			{
//				ResetGameFlag2();
//
//				title_init_save_data();
//
//				SetSceneGameFlag1(127, 0);	//ト??ルア?ック
//				SetSceneGameFlag1(125, 1);	/* replay jamp */
//				SetSceneGameFlag1(123, GetSceneGameFlag1(120) );	//リプレイ選択時のステ?ジ
//				SetSceneGameFlag1(132, 1);		//リプレイ
//				SetSceneGameFlag1(129, 0);	//ステ?ジセレクトから開始
//				SetSceneGameFlag1( 70, 1);
//
//				SaveGameFlag2( "save/work.sav");
//
//				ResetGameFlag2();
//				SaveGameFlag2( "save/item_wk.sav");
//
//				SetSceneGameFlag1(40, 4);
//
//				SetSceneState(EN_SN_ACT);
//				m_bExit=0;
//			}
//			else
//			{
//				DGX_SoundPlay( g_pApp->m_pGpAct.m_pSndSe[EN_SE_MSG] );
//			}
//		}

	}


	return m_bExit;
}



void CGpTitle::Render()
{
	//-------------------------------------------------------------
	//変数宣言
	int stage_hosei;
	int wk;
	//-------------------------------------------------------------

	stage_hosei = 0;
	if ( GetSceneGameFlag1(126) == 1 )
	{
		stage_hosei = 50;
	}

	//背景クリア
//	ClearSecondary();


	//?イトル画面の?送
	//-------------------------------------------------------------
	//-------------------------------------------------------------

	if ( m_nTitle == 0 )
	{
		Blt(m_vTex[5], 0, 0 );

		Blt(m_vTex[1], 110 - m_nA[0] + 45, 0 + m_nA[1]+ 70 );

		m_nA[0] = m_nA[0] - 10;
		if ( m_nA[0] < 0 )
		{
			m_nA[0] = 0;
		}
		m_nA[1] = m_nA[1] - 20;
		if ( m_nA[1] < 0 )
		{
			m_nA[1] = 0;
		}

		// Select Image
		Blt(m_vTex[2], 0- 80 +125, 0+120 );
//		Blt(m_vTex[7], 0, 0 );
//		BltRect(m_vTex[7], 0, 0 - ( c[0] * c[0] * c[0] ), 0, 64, 192, 96 );
		title_kane_disp(  );

		m_nCaslanm++;
		if ( m_nCaslanm >= 40 )
		{
			m_nCaslanm = 0;
		}

		// Cursor
		BltRect(m_vTex[3], 96 - 70, 118 + ( m_nMode * 20 ), ( m_nCaslanm / 10 ) * 16, 0 , 16 , 16 );	/* カ??ル */

		// Stage
		BltNumericImage2( GetSceneGameFlag1(120), 2, 262 - 80 - 31 -15, 136 - 16+4, m_vTex[18], 0, 0, 10, 8 );	/* ステ?ジ */

		//(E) 2010-07-27 Editor: AFEW
		// Replay
		//BltRect(m_vTex[18], 262 - 80 - 32, 168 - 16, 0, 56 + ( GetSceneGameFlag1(124) * 8 ), 100, 8 );	/* リプレイ?イプ */

		BltRect(m_vTex[18], 5, 230 , 0, 24, 100, 8 );	/*  */
		BltRect(m_vTex[18], 50, 230 , 0, 8, 100, 8 );	/*  */

		wk = get2keta( GetSceneGameFlag1(200 + GetSceneGameFlag1(120) + stage_hosei), 1 );
		BltNumericImage( wk, 2, 110, 230, m_vTex[18], 0, 0, 10, 8 );	/*  */

		wk = get2keta( GetSceneGameFlag1(200 + GetSceneGameFlag1(120) + stage_hosei), 100 );
		BltNumericImage( wk, 2, 80, 230, m_vTex[18], 0, 0, 10, 8 );	/*  */
		wk = get2keta( GetSceneGameFlag1(200 + GetSceneGameFlag1(120) + stage_hosei), 10000 );
		BltNumericImage( wk, 2, 50, 230, m_vTex[18], 0, 0, 10, 8 );	/*  */

		BltRect(m_vTex[18], 150, 230, 0, 80, 100, 8 );	/*  */

		BltNumericImage2( GetSceneGameFlag1(300 + GetSceneGameFlag1(120) + stage_hosei), 2, 240, 230, m_vTex[18], 0, 0, 10, 8 );	/* Jump_counts */

//		BltRect(m_vTex[18], 90, 230, 0, 8, 100, 8 );	/*  */
//		BltRect(m_vTex[18], 5, 230, 0, 48, 100, 8 );	/*  */
//		BltNumericImage( GetSceneGameFlag1(108], 2, 150, 230, 18, 0, 0, 10, 8 );	/* 時間 */
//		BltNumericImage( GetSceneGameFlag1(109], 2, 120, 230, 18, 0, 0, 10, 8 );	/* 時間 */
//		BltNumericImage( GetSceneGameFlag1(110], 2, 90, 230, 18, 0, 0, 10, 8 );	/* 時間 */

	}

	if ( GetSceneGameFlag1(61) == 0 )
	{
		Blt(m_vTex[109] , -160, -120 );
	}

	//キ?入力検査
//	g_pApp->KeyInput();

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
void CGpTitle::title_init_save_data()
{
	SetSceneGameFlag2(0, 8 * 32);	/* Ｘ */
	SetSceneGameFlag2(1, ( 2 * 32 ) - 16);	/* Ｙ */
	if ( GetSceneGameFlag1(126) == 1 )
	{
		SetSceneGameFlag2(2, 2);	/* ステ?ジ */
	}
	else
	{
		SetSceneGameFlag2(2, 1);	/* ステ?ジ */
	}

	SetSceneGameFlag2( 3, GetSceneGameFlag1(120));	/* 画面Ｎｏ */
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


	/* イニシャライズが必要な場合はここに記述する */
//	SetSceneGameFlag2(100]	= ;	/* イベントフラグ[100]?[199] */

	/* 100?399イベント用フラグ */

}

/***************************************************************************/
// NAME      = kane_set
// FUNCTION  = ?イトル文字の生成
// NOTES     =
// DATE      =
// AUTHER    = koizumi
// HISTORY   =
// PARAMETER = x：初期位置
//             y：初期位置
// RETURN    = なし
/***************************************************************************/
void CGpTitle::title_kane_set( int x, int y )
{
	int i;

	for ( i = 0; i < 20; i++ )
	{
		if ( m_nKane[0 + ( i * 10 )] == 0 )
		{
			m_nKane[0 + ( i * 10 )] = 1;
			m_nKane[1 + ( i * 10 )] = x;
			m_nKane[2 + ( i * 10 )] = y;
			m_nKane[4 + ( i * 10 )] = 0;
			m_nKane[3 + ( i * 10 )] = 0;
			m_nKane[5 + ( i * 10 )] = 0;
			m_nKane[6 + ( i * 10 )] = 0;
			m_nKane[7 + ( i * 10 )] = 0;
			m_nKane[8 + ( i * 10 )] = 0;
			m_nKane[9 + ( i * 10 )] = 6;
			break;
		}
	}
}


/***************************************************************************/
// NAME      = kane_disp
// FUNCTION  = ?イトル文字の?示
// NOTES     =
// DATE      =
// AUTHER    = koizumi
// HISTORY   =
// PARAMETER = なし
// RETURN    = なし
/***************************************************************************/
void CGpTitle::title_kane_disp()
{
	int i;

	for ( i = 0; i < 20; i++ )
	{
		if ( m_nKane[0 + ( i * 10 )] == 1 )
		{
			BltRect(m_vTex[7], m_nKane[1 + ( i * 10 )], ( 0 - m_nKane[2 + ( i * 10 )] ) + 240 - 104, 0, 0, 300, 126 );

			title_k_jmp( i );
		}
	}
}


/***************************************************************************/
// NAME      = k_jmp
// FUNCTION  = ?イトル文字のY?示位置計算
// NOTES     =
// DATE      =
// AUTHER    = koizumi
// HISTORY   =
// PARAMETER = i：バッフ?番号
// RETURN    = なし
/***************************************************************************/
void CGpTitle::title_k_jmp( int i )
{
	int y1;



	if ( m_nKane[6 + ( i * 10 )] == 10 )
	{
		if ( m_nKane[9 + ( i * 10 )] > 0 )
		{
			m_nKane[6 + ( i * 10 )] = m_nKane[9 + ( i * 10 )];
			m_nKane[9 + ( i * 10 )] = m_nKane[9 + ( i * 10 )] - 1;
		}
		return;
	}

	m_nKane[5 + ( i * 10 )]++;
	if ( m_nKane[5 + ( i * 10 )] >= 10 )
	{
		m_nKane[5 + ( i * 10 )] = 0;
	}

	if ( m_nKane[5 + ( i * 10 )] == 0 )
	{
		m_nKane[6 + ( i * 10 )] = m_nKane[6 + ( i * 10 )] - 3;
		if ( ( m_nKane[6 + ( i * 10 )] <= 2 ) && ( m_nKane[6 + ( i * 10 )] > -2 ) )
		{
			m_nKane[6 + ( i * 10 )] = -3;
		}
		if ( m_nKane[6 + ( i * 10 )] < -8 )
		{
			m_nKane[6 + ( i * 10 )] = -8;
		}
		/* 地面判定 */
	}

	/* 今回の位置 */
	y1 = ( ( 0 - m_nKane[6 + ( i * 10 )] ) * ( 0 - m_nKane[6 + ( i * 10 )] ) * ( 0 - m_nKane[6 + ( i * 10 )] ) );
	m_nKane[2 + ( i * 10 )] = m_nKane[2 + ( i * 10 )] - ( y1 / 25 );

	if ( m_nKane[2 + ( i * 10 )] < 140 )
	{
		m_nKane[6 + ( i * 10 )] = 10;
	}
}



/***************************************************************************/
// NAME      = replay_file_find
// FUNCTION  = リプレイフ?イルの検索
// NOTES     =
// DATE      =
// AUTHER    = koizumi
// HISTORY   =
// PARAMETER = なし
// RETURN    = フ?イルの有無
/***************************************************************************/
int CGpTitle::replay_file_find()
{
	long	i;

	int		file_j;
	int		stage = 1;
	char	strbuf[260]={0};

	if ( GetSceneGameFlag1(126) == 1 )
	{
		stage = 2;	/* 裏ステ?ジ */
	}
	else
	{
	}

	file_j = 1;

	sprintf( strbuf, "replay/%d/replay_data_%d.dat", ( int )stage, ( int )GetSceneGameFlag1(120) );
	if ( LoadFile( strbuf, &i, 1 ) )
	{
		file_j = 0;
	}

	return( file_j );
}


/***************************************************************************/
// NAME      = replay_file_find2
// FUNCTION  = 最短ジャンプリプレイフ?イルの検索
// NOTES     =
// DATE      =
// AUTHER    = koizumi
// HISTORY   =
// PARAMETER = なし
// RETURN    = フ?イルの有無
/***************************************************************************/
int CGpTitle::replay_file_find2()
{
	long	i;
	int		file_j;
	int		stage = 1;
	char	strbuf[260]={0};

	if ( GetSceneGameFlag1(126) == 1 )
	{
		stage = 2;	/* 裏ステ?ジ */
	}
	else
	{
	}

	file_j = 1;
	sprintf( strbuf, "replay/%d/replay_data_j%d.dat", ( int )stage, ( int )GetSceneGameFlag1(120) );
	if ( LoadFile( strbuf, &i, 1 ) )
	{
		file_j = 0;
	}

	return( file_j );
}


