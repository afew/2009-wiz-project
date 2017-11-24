

#include "_StdAfx.h"


extern char* g_sSndBgm[8];
extern char* g_sSndSe[20];


static long enm1_parameter[10 * 20] =
{
/*   HP */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 0未使用 */
	  1,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 1 */
	  1,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 2 */
	  1,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 3 */
	  1,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 4 */
	  1,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 5 */
	  1,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 6 */
	  1,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 7 */
	  1,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 8 */
	  1,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 9 */
	  1,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 10 */
	  1,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 11 */
	  1,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 12 */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0 	/* 20未使用 */
};

static long enm2_parameter[10 * 20] =
{
/*   HP */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 0未使用 */
	  1,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 1 */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 2 */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 3 */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 4 */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 5 */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 6 */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 7 */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 8 */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 9 */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0 	/* 20未使用 */
};

static long enm3_parameter[10 * 20] =
{
/*   HP   金 攻撃 属性 相性 */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 0未使用 */
	  1,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 1 */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 2 */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 3 */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 4 */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 5 */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 6 */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 7 */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 8 */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 9 */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0 	/* 20未使用 */
};

static long enm4_parameter[10 * 20] =
{
/*   HP */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 0未使用 */
	  7,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 1?ス */
	  7,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 2 */
	 30,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 3 */
	 27,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 4 */
     42,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 5 */
     30,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 6 */
      1,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 7 */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 8 */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 9 */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0 	/* 20未使用 */
};

static long item_data[3] = { 32, 50, 20 };			/* アイテ?の情報?サイズ、最大配置個数、1デ??バッフ?数 */
static long enm_data[3] = { 0, 30, 30 };			/* 敵の情報??備、最大配置個数、1デ??バッフ?数 */
static long MapInfo[10] =
{
	20 * 5									/* 0:?ップのxサイズ */
,	15 * 5									/* 1:?ップのyサイズ */
,	( 20 * 5 ) * 32							/* 2:?ップのx?示サイズ */
,	( 15 * 5 ) * 32							/* 3:?ップのy?示サイズ */
,   20										/* 4:ヘッ?デ??部のデ??数 */
};
static long char_size[10] =
{
	32										/* char_size[0] 横幅 */
,	32										/* char_size[1] 高さ */
,	10										/* char_size[2] 判定しない幅左（左からドットでカウント） */
,	( 32 - 10 )								/* char_size[3] 判定しない幅右（左からドットでカウント） */
,	8										/* char_size[4] アニメ?ションパ??ン数 */
};

static long player[50];									/* プレイヤ?用バッフ? */
											/* player[0] X */
											/* player[1] Y */
											/* player[2] 状態 */
											/* player[3] 向き */
											/* player[4] BMP内の?示位置X */
											/* player[5] BMP内の?示位置Y */
											/* player[6] 掴み中の移動補正X */
											/* player[7] 掴み中の移動補正Y */
											/* player[8] 現在HP */
											/* player[9] 敵を掴んでいる */
											/* player[10] アニメ?ションフレ??カウン? */
											/* player[11] アニメ?ションカウン? */
											/* player[12] アニメ?ションフレ??指定 */
											/* player[13] ジャンプフレ??カウン? */
											/* player[14] ジャンプカウン? */
											/* player[15] ?スの場合のX */
											/* player[16] ?スの場合のY */
											/* player[17] 無敵時間 */
											/* player[18] 着地モ?ション用カウン? */
											/* player[19] 回?可?か */
											/* player[20] ?ップの回?角度 */
											/* player[21] ?ップの回?角度目標 */
											/* player[22] 回?入力のウエイト */
											/* player[23] 回?角度差分 */
											/* player[24] secret item get ?示時間  */
											/* player[25] ??ンをおしてジャンプしたフラグ */
											/* player[26] 長時間落下したフラグ（着地フェクト用） */
											/* player[27] 掴んだときに入力されていたキ? */
											/* player[28] 移動床モ?ション */
											/* player[29] 横ばね吹き飛び中 */
											/* player[30] lastone?示 */
											/* player[31] カットインの?示 */
											/* player[32] カットインの種類 */
											/* player[33] アイテ?を押した時の移動量 */
											/* player[34]  */
											/* player[35]  */
											/* player[36]  */
											/* player[37]  */
											/* player[38]  */
static long dp_x;									/* プレイヤ?の?示位置（画面内の相対座標） */
static long dp_y;									/* プレイヤ?の?示位置（画面内の相対座標） */
static long dp_x2 = 80;								/* プレイヤ?の?示位置（画面内の相対座標） */
static long demo[10];
static long map1[10200];								/* ( MapInfo[0] * MapInfo[1] ) + MapInfo[4] 背景用バッフ? レイヤ?1 */
static long map2[10200];							 	/* MapInfo[0] * MapInfo[1] 背景用バッフ? レイヤ?2 */
static long mapfile[10200];							/* MapInfo[0] * MapInfo[1] 背景用バッフ? レイヤ?2 */
static long map_data[20];							/* ヘッ?情報 */
static long bak_cnt = 0;							/* 背景アニメ?ション用カウン? */
static long bak_alldrow = 0;						/* 背景の?画をクリップするか */
static long d_x = 0;								/* 背景?示位置 */
static long d_y = 0;								/* 背景?示位置 */
static long kamera = 0;

static long next_px = 0;							/* 画面切り替え時のキャラ移動対策 */
static long next_py = 0;

static long map_rot_info = 0;							/* ?ップの向き */
#ifdef GP2X
static const long atk_rr1 =30;						/* 腕の回?速度 */
#else
static const long atk_rr1 =5;						/* 腕の回?速度 */
#endif


static long stage = 0;								/* ステ?ジ番号 */
static long secretitemget = 0;						/* 隠しアイテ?の取得 */
static long target_save[1024];


#define PARTICLE	50


struct Tparticle
{
	int		vcX;	// pshotf2[0] Velocity x
	int		vcY;	// pshotf2[1] Velocity y
	int		bAv;	// pshotf2[2] Alive
	int		IgX;	// pshotf2[4] Image Source Index X
	int		psX;	// pshotf2[5] Position X
	int		psY;	// pshotf2[6] Position Y
	int		IgC;	// pshotf2[7] Image Source Current Index
	int		IgM;	// pshotf2[8] Image Source Current Index
	int		nTp;	// pshotf2[9] type 						
	int		nAp;	// Alpha
};


static long pshot[10 * 10];							/* プレイヤ?攻撃用情報 */
static long pshotf[10 * 40];						/* プレイヤ?攻撃用情報 */
static Tparticle pshotf2[PARTICLE];					/* プレイヤ?攻撃用情報 */


static long pmshot[20 * 40];						/* プレイヤ?攻撃用情報 */
static long pjumpf[100];							/* プレイヤ?攻撃用情報 */
static long item[20 * 50];							/* アイテ?用バッフ? */
static long item_wk[5*100];							/* 地面 その他の?ップ情報 */

static long enemy[30 * 30];							/* enm_data[1] * enm_data[2] 敵情報	*/

static long mgc_e[10 * 20] ;						/* MGC?示情報			*/
static long p_ef[1000] ;							/* 汎用バッフ?（足跡等）*/
static long kane[200];								/* アイテ?用バッフ? */

static long Jump_counts = 0;
static long snack_count = 0;
static long all_snack_count = 0;
static long save_data[512];							/* 保存情報 */
static long test[5];
static long rayer[5];								/* 背景スクロ?ル量 */
static long play_time[5];


static long replay[60 * 60 * 10];	/* フレ??＊秒＊分 */
static long replay_time = 1;
static long replay_time_MAX = 60 * 60 * 10;	/* 最大時間 */
static long replay_load_key[10];

static long replay_save_flag = 0;				/* 保存を行うか 1:しない */
static long rrkey[5];								/* 入力キ?方向 */


static long one_event = 0;							/* 重なって発生するイベントの前回重なっていたかのフラグ */


//(E) 2010-07-28 Editor: AFEW
// y Epsilon
static int m_EpsY = 8;

static int m_bEnding = 0;


CGpAct::CGpAct()
{
	m_bExit = 0;
	m_nSn = 0;

	memset(m_vTex, 0, sizeof(m_vTex));

	memset(m_pSndSe, 0, sizeof(m_pSndSe));
	m_pSndBg	= NULL;
	m_nSndBg	= 0;
	m_bDemo		= 0;
}


CGpAct::~CGpAct()
{
}


// ｰﾔﾀﾓ ﾇﾃｷｹﾀﾌ ﾁ�ﾀ� ﾈ｣ﾃ�( ﾀﾌｺ･ﾆｮ > ｰﾔﾀﾓ ﾇﾃｷｹﾀﾌ, ｰﾔﾀﾓ ﾇﾃｷｹﾀﾌ > ｰﾔﾀﾓ ﾇﾃｷｹﾀﾌ ( ｽｺﾅﾗﾀﾌﾁ� ﾀﾌｵｿ ) )
int CGpAct::Init()
{
	long i;
	long x;
	long y;
	long wk;
	long d_num;

	char	strbuf[260]={0};

	m_bExit = 1;
	m_nSn = 0;
	bak_cnt = 0;							/* 背景アニメ?ション用カウン? */
	bak_alldrow = 0;						/* 背景の?画をクリップするか */
	d_x = 0;								/* 背景?示位置 */
	d_y = 0;								/* 背景?示位置 */
	next_px = 0;							/* 画面切り替え時のキャラ移動対策 */
	next_py = 0;
	stage = 0;								/* ステ?ジ番号 */
	Jump_counts = 0;
	snack_count = 0;
	all_snack_count = 0;
	replay_time = 1;
	replay_time_MAX = 60 * 60 * 10;	/* 最大時間 */
	replay_save_flag = 0;				/* 保存を行うか 1:しない */
	one_event = 0;							/* 重なって発生するイベントの前回重なっていたかのフラグ */
	map_rot_info = 0;							/* ?ップの向き */
	secretitemget = 0;						/* 隠しアイテ?の取得 */

//#if FALSE
	memset( player, 0, sizeof( player ) );									/* プレイヤ?用バッフ? */
	memset( demo, 0, sizeof( demo ) );
	memset( map1, 0, sizeof( map1 ) );								/* 背景用バッフ? レイヤ?1 */
	memset( map2, 0, sizeof( map2 ) );								/* 背景用バッフ? レイヤ?2 */
	memset( map_data, 0, sizeof( map_data ) );
	memset( pshot, 0, sizeof( pshot ) );							/* プレイヤ?攻撃用情報 */
	memset( pshotf, 0, sizeof( pshotf ) );						/* プレイヤ?攻撃用情報 */
	memset( pshotf2, 0, sizeof( pshotf2 ) );						/* プレイヤ?攻撃用情報 */
	memset( pmshot, 0, sizeof( pmshot ) );						/* プレイヤ?攻撃用情報 */
	memset( pjumpf, 0, sizeof( pjumpf ) );							/* プレイヤ?攻撃用情報 */
	memset( item, 0, sizeof( item ) );							/* アイテ?用バッフ? */
	memset( item_wk, 0, sizeof( item_wk ) );							/* 地面 その他の?ップ情報 */
	memset( enemy, 0, sizeof( enemy ) );								/* 敵情報															*/
	memset( mgc_e, 0, sizeof( mgc_e ) ) ;						/* MGC?示情報														*/
	memset( p_ef, 0, sizeof( p_ef ) ) ;							/* 汎用バッフ?（足跡等）														*/
	memset( kane, 0, sizeof( kane ) );								/* アイテ?用バッフ? */
	memset( save_data, 0, sizeof( save_data ) );							/* 保存情報 */
	memset( test, 0, sizeof( test ) );
	memset( rayer, 0, sizeof( rayer ) );								/* 背景スクロ?ル量 */
	memset( play_time, 0, sizeof( play_time ) );
	memset( replay, 0, sizeof( replay ) );	/* フレ??＊秒＊分 */
	memset( replay_load_key, 0, sizeof( replay_load_key ) );
	memset( rrkey, 0, sizeof( rrkey ) );								/* 入力キ?方向 */
	memset( target_save, 0, sizeof( target_save ) );
//#endif

	/* かけら取得情報 */
	ResetGameFlag2();				/* フ?イルなし */

	for ( i = 0; i <= 500; ++i )
	{
		item_wk[i] = GetSceneGameFlag2(i);
	}


	ResetGameFlag2();
	LoadGameFlag2( "save/work.sav");
	for ( i = 0; i < 512; ++i )
	{
		save_data[i] = GetSceneGameFlag2(i);
	}

	LoadFile( "save/target", &target_save[0], sizeof( target_save ) );

	player[8] = 1;			/* HP */
	stage = save_data[2];
	d_num = save_data[3]; 	/* 画面 */


	SetSceneGameFlag1(120, d_num);


	player[20] = 0;
	player[21] = 0;
	player[22] = 1;


	/* レイヤ?１ */
	ResetGameFlag2();
	sprintf(strbuf,"data/%d/%d_%d.map", ( int )stage , ( int )1, ( int )d_num );
	if ( 0 == LoadFile( strbuf, map1, sizeof( map1 ) ) )
	{
	}
	else
	{
		/* フ?イルがない */
		if ( 1 == GetSceneGameFlag1(132) )	/* リプレイ */
		{
			SetSceneState(EN_SN_TITLE);	/* ?イトルへ */
		}
		else
		{
//			GetSceneGameFlag1(40) = 5;	/* エンディングへ */
//			SetSceneState(EN_SN_ENDING);	/* ?イトルへ */
			m_bEnding = TRUE;
			return 0;
		}

		m_nSn = 10;
	}

	for ( i = 0 ; i <= 20 ; ++i )
	{
		map_data[i] = map1[i + ( MapInfo[0] * MapInfo[1] )];
	}



	player[0] = map_data[9] * 32;
	player[1] = ( map_data[10] * 32 );

	if ( 0 != GetSceneGameFlag1(128) )	//?ップビュ?
	{
		item_set( 1, player[0], player[1], 0, d_num );
	}

	/* レイヤ?２ */
	ResetGameFlag2();
	sprintf(strbuf,"data/%d/%d_%d.map", ( int )stage , ( int )2, ( int )d_num );
	LoadFile( strbuf, map2, sizeof( map2 ) );

	/* アイテ?配置 */
	ResetGameFlag2();
	sprintf(strbuf,"data/%d/i%d_%d.map", ( int )stage , ( int )1, ( int )d_num );


	LoadFile( strbuf, mapfile, sizeof( mapfile ) );
	{
		for ( x = 0; x < MapInfo[0] ; x++ )
		{
			for ( y = 0; y < MapInfo[1] ; y++ )
			{
				if ( mapfile[x + ( y * MapInfo[0] )] != 0 )
				{
					if ( mapfile[x + ( y * MapInfo[0] )] == 1 )
					{
						//キャラク??
					}
					else
					{
						item_set( mapfile[x + ( y * MapInfo[0] )], x * 32, ( ( MapInfo[1] - 1 - y ) * 32 ), x + ( y * MapInfo[0] ), d_num );
					}
				}
			}
		}
	}



	ResetGameFlag2();				/* フ?イルなし */
	sprintf( strbuf,"data/%d/e%d_%d.map", ( int )stage , ( int )1, ( int )d_num );
	LoadFile( strbuf, mapfile, sizeof( mapfile ) );

	/* 敵配置 */
	for ( x = 0; x < MapInfo[0] ; x++ )
	{
		for ( y = 0; y < MapInfo[1] ; y++ )
		{
			if ( mapfile[x + ( y * MapInfo[0] )] != 0 )
			{
				enm_set( mapfile[x + ( y * MapInfo[0] )], x * 32, ( ( MapInfo[1] - 1 - y ) * 32 ) );
			}
		}
	}

	player[14] = 10;	/* ジャンプカウン? */
	player[15] = player[0];
	player[16] = player[1];
	player[2] = 0;



	if ( 1 == GetSceneGameFlag1(132) )
	{
		if ( 1 != replay_file_load() )
		{
			/* フ?イルが読めなかった */
			SetSceneState(EN_SN_TITLE);	/* ?イトルへ */
			m_nSn = 10;
			return 0;
		}
	}
	else
	{
	}


	if ( 1== GetSceneGameFlag1(127) )	//ト??ルア?ック
	{
		wk = get2keta( GetSceneGameFlag1(135), 1 );

		play_time[0] = play_time[0] + wk;

		if ( play_time[0] >= 60 )
		{
			play_time[0] = play_time[0] - 60;
			play_time[1]++;
		}


		wk = get2keta( GetSceneGameFlag1(135) , 100 );
		play_time[1] = play_time[1] + wk;
		if ( play_time[1] >= 60 )
		{
			play_time[1] = play_time[1] - 60;
			play_time[2]++;
		}


		wk = get2keta( GetSceneGameFlag1(135) , 10000 );
		play_time[2] = play_time[2] + wk;
		if ( play_time[2] >= 999 )
		{
			play_time[2] = 999;
			play_time[1] = 59;
			play_time[0] = 59;
		}

		if ( 5== GetSceneGameFlag1(40) )
		{
			if ( GetSceneGameFlag1(137) > GetSceneGameFlag1(135) )	//ト??ルア?ック クリア時間
			{
				SetSceneGameFlag1(137, GetSceneGameFlag1(135));
			}
			if ( GetSceneGameFlag1(138) > GetSceneGameFlag1(136) )	//ト??ルア?ック クリアジャンプ
			{
				SetSceneGameFlag1(138, GetSceneGameFlag1(136));
			}
		}
	}


	//(E) 2010-08-05 Editor: AFEW
	//	sprintf(strbuf,"image/player/ri%d.png", ( int )GetSceneGameFlag1(122) );
	//	LoadImage(&m_vTex[1], strbuf, TRUE);					//プレ?ンナンバ?２にシステ?用ＢＭＰを読み込む

	sprintf(strbuf,"image/map/map%d_1.png", ( int )stage );
	ReleaseImage(&m_vTex[10]);
	LoadImage(&m_vTex[10],strbuf,TRUE);					//プレ?ンナンバ?２にシステ?用ＢＭＰを読み込む

	sprintf(strbuf,"image/map/map%d_2.png", ( int )stage );
	ReleaseImage(&m_vTex[11]);
	LoadImage(&m_vTex[11],strbuf,TRUE);					//プレ?ンナンバ?２にシステ?用ＢＭＰを読み込む

	sprintf(strbuf,"image/map/item%d.png", ( int )stage );
	ReleaseImage(&m_vTex[12]);
	LoadImage(&m_vTex[12],strbuf,TRUE);					//プレ?ンナンバ?２にシステ?用ＢＭＰを読み込む


	// Loading 0
	Loading(0);

	// Loading 1
	Loading(1);


	// Loading 2
	Loading(2);


	if ( 0 != GetSceneGameFlag1(128) )	//?ップビュ?
		m_nSn = 6;




	//(E) 2010-07-15 Editor: AFEW
	if(m_pSndBg)
		m_pSndBg->SetVolume( 100/128.F );

	INT nSndOld = m_nSndBg;
	INT nSndNew = 0;

	
	if( 0 < save_data[3] && save_data[3] <= 10 )
		nSndNew = EN_BGM_GAME02;

	else if( 10 < save_data[3] && save_data[3] <= 20 )
		nSndNew = EN_BGM_GAME03;

	else if( 20 < save_data[3] && save_data[3] <= 30 )
		nSndNew = EN_BGM_GAME04;

	else if( 30 < save_data[3] && save_data[3] <= 40 )
		nSndNew = EN_BGM_GAME05;

	else if( 40 < save_data[3] && save_data[3] <= 50 )
		nSndNew = EN_BGM_GAME06;


	if(nSndOld != nSndNew || NULL == m_pSndBg)
	{
		DGX_DestroySound(&m_pSndBg);
		DGX_CreateSound(NULL, &m_pSndBg, g_sSndBgm[nSndNew]);
		DGX_SoundRepeat(m_pSndBg);


		char*	sSndSe = NULL;
	
		sSndSe = g_sSndSe[EN_SE_CL1 + nSndNew - 1];
		DGX_DestroySound(&m_pSndSe[EN_SE_CL1]);
		DGX_CreateSound(NULL, &m_pSndSe[EN_SE_CL21], sSndSe);

		sSndSe = g_sSndSe[EN_SE_CL21 + nSndNew - 1];
		DGX_DestroySound(&m_pSndSe[EN_SE_CL21]);
		DGX_CreateSound(NULL, &m_pSndSe[EN_SE_CL1], sSndSe);
	}

	SetSceneGameFlag1(71, 0);
	SetSceneGameFlag1(70, 0);

	m_nSndBg = nSndNew;
	DGX_SoundPlay(m_pSndBg);
	
	return 0;
}


void CGpAct::Loading(int n)
{
	if(0 == n)
	{
		if(NULL == m_vTex[1])	LoadImage(&m_vTex[1], (char*)"image/player/ri0.png",TRUE);				//プレ?ンナンバ?２にシステ?用ＢＭＰを読み込む
		if(NULL == m_vTex[4])	LoadImage(&m_vTex[4], (char*)"image/player/atk2.png",TRUE);				//プレ?ンナンバ?２にシステ?用ＢＭＰを読み込む
		if(NULL == m_vTex[5])	LoadImage(&m_vTex[5], (char*)"image/player/atkf.png",TRUE);				//プレ?ンナンバ?２にシステ?用ＢＭＰを読み込む
		if(NULL == m_vTex[6])	LoadImage(&m_vTex[6], (char*)"image/player/cutin.png",TRUE);			//プレ?ンナンバ?２にシステ?用ＢＭＰを読み込む

		if(NULL == m_vTex[18])	LoadImage(&m_vTex[18], (char*)"image/sys/fonts2.png",TRUE);				//プレ?ンナンバ?２にシステ?用ＢＭＰを読み込む
		if(NULL == m_vTex[40])	LoadImage(&m_vTex[40], (char*)"image/enm/e32.png",TRUE);				//プレ?ンナンバ?２にシステ?用ＢＭＰを読み込む
		if(NULL == m_vTex[60])	LoadImage(&m_vTex[60], (char*)"image/sys/menu.png", TRUE);				//プレ?ンナンバ?２にシステ?用ＢＭＰを読み込む
		if(NULL == m_vTex[61])	LoadImage(&m_vTex[61], (char*)"image/title/scl.png", TRUE);			//プレ?ンナンバ?２にシステ?用ＢＭＰを読み込む
	}
	else if( 1 == n)
	{
		if(NULL == m_vTex[67])	LoadImage(&m_vTex[67], (char*)"image/sys/input.png", TRUE);			//プレ?ンナンバ?２にシステ?用ＢＭＰを読み込む
		if(NULL == m_vTex[68])	LoadImage(&m_vTex[68], (char*)"image/sys/new1.png", TRUE);				//プレ?ンナンバ?２にシステ?用ＢＭＰを読み込む
		if(NULL == m_vTex[69])	LoadImage(&m_vTex[69], (char*)"image/sys/new2.png", TRUE);				//プレ?ンナンバ?２にシステ?用ＢＭＰを読み込む
		if(NULL == m_vTex[70])	LoadImage(&m_vTex[70], (char*)"image/sys/mini_map.png", TRUE);			//プレ?ンナンバ?２にシステ?用ＢＭＰを読み込む

		if(NULL == m_vTex[71])	LoadImage(&m_vTex[71], (char*)"image/sys/stagestart.png", TRUE);		//プレ?ンナンバ?２にシステ?用ＢＭＰを読み込む
		if(NULL == m_vTex[72])	LoadImage(&m_vTex[72], (char*)"image/bak/0.png", TRUE);				//プレ?ンナンバ?２にシステ?用ＢＭＰを読み込む
		if(NULL == m_vTex[73])	LoadImage(&m_vTex[73], (char*)"image/sys/new3.png", TRUE);				//プレ?ンナンバ?２にシステ?用ＢＭＰを読み込む
		if(NULL == m_vTex[74])	LoadImage(&m_vTex[74], (char*)"image/sys/new4.png", TRUE);				//プレ?ンナンバ?２にシステ?用ＢＭＰを読み込む
		if(NULL == m_vTex[75])	LoadImage(&m_vTex[75], (char*)"image/sys/scor.png", TRUE);				//プレ?ンナンバ?２にシステ?用ＢＭＰを読み込む
		if(NULL == m_vTex[76])	LoadImage(&m_vTex[76], (char*)"image/sys/houkou.png", TRUE);			//プレ?ンナンバ?２にシステ?用ＢＭＰを読み込む

		if(NULL == m_vTex[110])	LoadImage(&m_vTex[110], (char*)"image/bak/1_256.png", FALSE);
		if(NULL == m_vTex[111])	LoadImage(&m_vTex[111], (char*)"image/bak/2_256.png", FALSE);
		if(NULL == m_vTex[112])	LoadImage(&m_vTex[112], (char*)"image/bak/3_256.png", FALSE);
		if(NULL == m_vTex[113])	LoadImage(&m_vTex[113], (char*)"image/bak/4_256.png", FALSE);
		if(NULL == m_vTex[114])	LoadImage(&m_vTex[114], (char*)"image/bak/5_256.png", FALSE);

		if(NULL == m_vTex[120])	LoadImage(&m_vTex[120], (char*)"image/color.png", FALSE);

		//(E) 2010-08-05 Editor: AFEW
		if(NULL == m_vTex[121])	LoadImage(&m_vTex[121], (char*)"image/title/stageselect.png", TRUE);		//プレ?ンナンバ?２にシステ?用ＢＭＰを読み込む
		if(NULL == m_vTex[122])	LoadImage(&m_vTex[122], (char*)"image/title/potion_bak.png", FALSE );		//プレ?ンナンバ?１に?イトル画面背景を読み込む
	}
	else if( 2 == n)
	{
		if(NULL == m_pSndSe[EN_SE_ATK1	 ])	DGX_CreateSound(NULL, &m_pSndSe[EN_SE_ATK1	 ], g_sSndSe[ EN_SE_ATK1  ]);
		if(NULL == m_pSndSe[EN_SE_L1     ])	DGX_CreateSound(NULL, &m_pSndSe[EN_SE_L1     ], g_sSndSe[EN_SE_L1     ]);
		if(NULL == m_pSndSe[EN_SE_LANDING])	DGX_CreateSound(NULL, &m_pSndSe[EN_SE_LANDING], g_sSndSe[EN_SE_LANDING]);
		if(NULL == m_pSndSe[EN_SE_MSG    ])	DGX_CreateSound(NULL, &m_pSndSe[EN_SE_MSG    ], g_sSndSe[EN_SE_MSG    ]);
		if(NULL == m_pSndSe[EN_SE_SELECT ])	DGX_CreateSound(NULL, &m_pSndSe[EN_SE_SELECT ], g_sSndSe[EN_SE_SELECT ]);
		if(NULL == m_pSndSe[EN_SE_SW     ])	DGX_CreateSound(NULL, &m_pSndSe[EN_SE_SW     ], g_sSndSe[EN_SE_SW     ]);
		if(NULL == m_pSndSe[EN_SE_JUMP   ])	DGX_CreateSound(NULL, &m_pSndSe[EN_SE_JUMP   ], g_sSndSe[EN_SE_JUMP   ]);
		if(NULL == m_pSndSe[EN_SE_PAWA   ])	DGX_CreateSound(NULL, &m_pSndSe[EN_SE_PAWA   ], g_sSndSe[EN_SE_PAWA   ]);
	}
}




void CGpAct::Destroy()
{
	long i;

	save_file_w();

	for ( i = 0; i < EN_SE_END; ++i )
		DGX_SoundStop(m_pSndSe[i] );

	DGX_SoundStop(m_pSndBg);


	m_bExit = 0;
	m_nSn = 0;


	int TexList[] =
	{
		  4,   5,   6,  18,  40,
		 60,  61,  67,  68,  69,
		 70,  71,  72,  73,  74,
		 75,  76, 110, 111, 112,
		113, 114, 120, 121, 122,
		1000,
	};


	int j=0;

	for ( i = 0; i < BMPBUFF_MAX; ++i )
	{
		if(i == TexList[j])
		{
			++j;
			continue;
		}

		ReleaseImage(&m_vTex[i] );
	}
}


void CGpAct::ReleseTexture()
{
	int i;
	for ( i = 0; i < BMPBUFF_MAX; ++i )
		ReleaseImage(&m_vTex[i] );
}


void CGpAct::ReleseSound()
{
	int i;
	
	for ( i = 0; i < EN_SE_END; ++i )
		DGX_DestroySound(&m_pSndSe[i] );

	DGX_DestroySound(&m_pSndBg);
	m_nSndBg	= 0;
}


int CGpAct::Update()
{
	long i;
	long old_x;
	long houkou;
	long kakudosa;

	houkou = 0;
	kakudosa = 0;

	if(m_bEnding)
	{
		SetSceneState(EN_SN_ENDING);

		g_pApp->m_pGpEnding.Destroy();
		g_pApp->m_pGpEnding.Init();
		m_bEnding = 0;
		m_bExit = 0;
		return m_bExit;
	}


	if(m_bDemo)
	{
		SetSceneState(EN_SN_DEMO);
		m_bDemo = 0;
		m_bExit = 0;
		return m_bExit;
	}

	if(0 == m_nSn)			// State Fade in. so there is no job. return.
		return m_bExit;


	if(4 == m_nSn)			// Popup window
	{
		window_keys();
		return m_bExit;
	}

	if(6 == m_nSn)			// view Map
	{
		mapview_keys();
		return m_bExit;
	}


	if ( ( m_nSn == 1 ) || ( m_nSn == 5 ) )
	{
		play_time[0] = play_time[0] + 1;
		if ( play_time[0] >= 60 )
		{
			play_time[0] = 0;
			play_time[1] = play_time[1] + 1;
			if ( play_time[1] >= 60 )
			{
				play_time[1] = 0;
				play_time[2] = play_time[2] + 1;
				if ( play_time[2] >= 60 )
				{
					if ( play_time[2] >= 10 )
					{
						play_time[2] = 10;
					}
				}
			}
		}
	}
	if ( 0 == GetSceneGameFlag1(132) )
	{
		replay_input_save();		/* リプレイデ??保存 */
	}
	else
	{
		replay_input_load();		/* リプレイデ??再生 */
	}
	replay_time++;
	if ( replay_time > replay_time_MAX )
	{
		replay_time = replay_time_MAX;	/* 最大時間を越えた、保存しない */
		replay_save_flag = 1;			/* 保存しない */
	}

	for ( i = 0; i < 5; ++i )
	{
		rrkey[i] = 0;						/* 入力キ?方向 */
	}

	player[17]--;			/* 無敵時間 */
	if ( player[17] <= 0 )
	{
		player[17] = 0;
	}
	if ( player[9] == 0 )
	{
		jmp();
	}


	if ( ( item_up() != -1 ) && ( player[14] == 10 ) )	/* アイテ?の上に乗っている */
	{
		player[1] = item_up();
	}

	player[19] = 0;	// 回?可?かフラグ


	if ( player[2] == 31 )
	{
	}
	else
	{
		old_x = player[0];

		if ( player[9] == 1 )	//回?中
		{
		}
		else
		{
			//(E) 2010-07-15 Editor: AFEW
			//	if ( ( ( g_pApp->IsPressKey( DGXKEY_LEFT ) ) && ( 0 == GetSceneGameFlag1(132) ) )		// 左
			//		|| ( ( replay_load_key[0] == 1 ) && ( 1 == GetSceneGameFlag1(132) ) ) )


			INT nLeft = g_pApp->IsPressKey(DGXKEY_LEFT) || g_pApp->IsPressKey(DGXKEY_UP_LEFT);
			INT nRight= g_pApp->IsPressKey(DGXKEY_RIGHT) || g_pApp->IsPressKey(DGXKEY_UP_RIGHT);

			if ( ( nLeft  && ( 0 == GetSceneGameFlag1(132) ) )		// 左
				  || ( ( replay_load_key[0] == 1 ) && ( 1 == GetSceneGameFlag1(132) ) ) )
			{

				player[3] = 1;	/* 向き */
				if ( player[2] == 0 )
				{
					player[10] = 0;	/* アニメ?ション間隔フレ??設定 */
					player[11] = 0;	/* アニメ?ションカウン? */
					player[2] = 1;	/* 歩き */
				}
				else if ( player[2] == 1 )
				{
					player[0] = player[0] - 2;	/* キャラク??移動 */
				}
				else if ( player[2] == 21 )
				{
					player[0] = player[0] - 2;	/* キャラク??移動 */
				}

			}
			//(E) 2010-07-15 Editor: AFEW
			//	else if ( ( ( g_pApp->IsPressKey( DGXKEY_RIGHT ) ) && ( 0 == GetSceneGameFlag1(132) ) )	// 右
			//		|| ( ( replay_load_key[1] == 1 ) && ( 1 == GetSceneGameFlag1(132) ) ) )

			else if ( ( nRight && ( 0 == GetSceneGameFlag1(132) ) )	// 右
				  || ( ( replay_load_key[1] == 1 ) && ( 1 == GetSceneGameFlag1(132) ) ) )
			{
				player[3] = 0;
				if ( player[2] == 0 )
				{
					player[10] = 0;
					player[11] = 0;
					player[2] = 1;
				}
				else if ( player[2] == 1 )
				{
					player[0] = player[0] + 2;
				}
				else if ( player[2] == 21 )
				{
					player[0] = player[0] + 2;
				}
			}
			else
			{
				if ( player[2] == 1 )
				{
					player[10] = 0;
					player[11] = 0;
					player[2] = 0;
				}
			}
		}



		if ( player[28] != 0 )	/* 移動床 */
		{
			player[0] = player[0] + player[28];
		}
		player[28] = 0;

		if ( player[29] > 0 )	/* 移動床 */
		{
			player[0] = player[0] + ( player[29] * 1 );
			player[29] = player[29] - 1;
		}
		else if ( player[29] < 0 )
		{
			player[0] = player[0] + ( player[29] * 1 );
			player[29] = player[29] + 1;
		}

		/* 前回の位置から移動した */
		if ( old_x > player[0] )
		{
			idou_l();	/* 左移動の壁判定 */
		}
		else if ( old_x < player[0] )
		{
			idou_r();	/* 右移動の壁判定 */
		}
		player[33] = ( player[0] - old_x );



		//	スペ?スキ?が押される
		if ( ( ( g_pApp->IsPressKey( DGXKEY_FA ) )  && ( GetSceneGameFlag1(132) == 0 ) ) 		/* 移動速度低下 */
			|| ( ( replay_load_key[4] == 1 ) && ( GetSceneGameFlag1(132) == 1 ) ) )
		{
			if ( player[19] != 0 )	//
			{
				if ( player[9] == 0 )
				{
					DGX_SoundPlay(m_pSndSe[EN_SE_PAWA]);

				#if !defined(GP2X_WIZ)
					// Haptic Play
					//printf("Haptic Play\n");
					DGE_HapticEnable(TRUE);

					// ﾇ�ﾀ� ﾁ�ｵｿ ﾀ蠧｡ ｻ�ﾅﾂ ﾈｮﾀﾎ
					if(DGE_VIB_STATUS_BUSY == DGE_HapticStatus())
					{
						// ﾀﾛｵｿ ﾁﾟ

						// ﾁ�ｵｿ ﾁ､ﾁ�
						DGE_HapticStop();
					}
					DGE_HapticPlay(140, 120);
				#endif


					m_nSn = 5;
					player[20] = 0;
					player[21] = 0;
					player[22] = 0;

					player[10] = 0;
					player[11] = 0;
					player[4] = 0;
					player[5] = 3;
					player[2] = 2;		// つかみ



					if ( player[19] == 1 )	//
					{
						player[22] = 10;
						player[20] = player[21];
						player[21] = player[21] + 90;
					}
					if ( player[19] == 2 )	//
					{
						player[22] = 10;
						player[20] = player[21];
						player[21] = player[21] - 90;
					}
					if ( player[21] < 0 )
					{
						player[21] = player[21] + 360;
					}
					if ( player[21] >= 360 )
					{
						player[21] = player[21] - 360;
					}

				}
				player[9] = 1;
			}
		}

		kakudosa = ( player[21] - player[20] );		// 回?が終了した

		if ( kakudosa == 0 )		// 差がない場合は回さない
		{
			if ( player[9] == 1 )
			{
				Jump_counts++;
				DGX_SoundPlay( m_pSndSe[EN_SE_ATK1] );
				rotmap( player[21] );	// 回?

				player[10] = 0;
				player[11] = 0;
				player[2] = 0;		// ﾆｭｰﾄﾗﾙ

				player[14] = 0;		// 落下
				player[13] = 0;

				player[1] = player[1] + 8;	// あたり判定が長方?なので浮かせる

				m_nSn = 1;
				player[9] = 0;

				switch( player[21] )
				{
				case 90:
					map_rot_info = map_rot_info - 1;							/* ?ップの向き */
					break;
				case 180:
					map_rot_info = map_rot_info + 2;							/* ?ップの向き */
					break;
				case 270:
					map_rot_info = map_rot_info + 1;							/* ?ップの向き */
					break;
				default:
					break;
				}
				if ( map_rot_info < 0 )	// 超えた
				{
					map_rot_info = map_rot_info + 4;
				}
				if ( map_rot_info > 3 )	// 超えた
				{
					map_rot_info = map_rot_info - 4;
				}

			}
		}
		else
		{
			if ( kakudosa == 0 )		// 差がない場合は回さない
			{
			}
			else if ( kakudosa < 0 ) // 目標角度に対して現在地はプラス
			{
				if ( -180 > kakudosa )  // 180度超えている場合は逆回?
				{
					player[20] = player[20] + atk_rr1;
					houkou = 1;
				}
				else
				{
					player[20] = player[20] - atk_rr1;
					houkou = 0;
				}
			}
			else if ( kakudosa > 0 ) // 目標角度に対して現在地は?イナス
			{
				if ( 180 < kakudosa )
				{
					player[20] = player[20] - atk_rr1;
					houkou = 0;
				}
				else
				{
					player[20] = player[20] + atk_rr1;
					houkou = 1;
				}
			}
			// 360度を越えた場合は0度にオフセット
			if ( player[20] < 0 )
			{
				player[20] = player[20] + 360;
			}
			if ( player[20] >= 360 )
			{
				player[20] = player[20] - 360;
			}
		}



		// Jump Action
		//(E) 2010-07-15 Editor: AFEW
		//if ( ( ( ( g_pApp->IsPushKey( DGXKEY_FX ) )
		//	|| ( g_pApp->IsPushKey( DGXKEY_UP ) && ( GetSceneGameFlag1(133) == 1 ) ) ) && ( GetSceneGameFlag1(132) == 0 ) )
		//	|| ( ( replay_load_key[6] == 1 ) && ( GetSceneGameFlag1(132) == 1 ) ) )


		INT nUp = g_pApp->IsPushKey( DGXKEY_UP) || g_pApp->IsPushKey( DGXKEY_U_L) || g_pApp->IsPushKey( DGXKEY_U_R);


		int t1 = 0;									// g_pApp->IsPushKey( DGXKEY_FX );		// FY Key
		int t2 = nUp;								// g_pApp->IsPushKey( DGXKEY_UP );
		int t3 = GetSceneGameFlag1(133) == 1;
		int t4 = GetSceneGameFlag1(132) == 0;
		int t5 = replay_load_key[6] == 1;
		int t6 = GetSceneGameFlag1(132) == 1;
		int t7 = t1	|| ( t2 && t3 );


		if( (t7 && t4) || (t5 && t6) )
		{
			if ( player[9] == 0 )	// つかんでいない
			{
				if ( ( player[2] != 11 ) && ( player[2] != 31 ) && ( player[14] == 10 ) )	/* 地上で攻撃、?メ?ジじゃない */
				{
					if (
						   ( ( ( map1_item_j( player[0] + ( char_size[0] / 2 ), player[1] + ( char_size[1] / 2 ) ) >= 100 )
						    && ( map1_item_j( player[0] + ( char_size[0] / 2 ), player[1] + ( char_size[1] / 2 ) ) <= 119 ) )
						  || ( ( map1_item_j( player[0] + ( char_size[0] / 2 ), player[1] + ( char_size[1] / 2 ) ) >= 200 )
						    && ( map1_item_j( player[0] + ( char_size[0] / 2 ), player[1] + ( char_size[1] / 2 ) ) <= 219 ) ) )
					   )
					{
					}
					else
					{
						DGX_SoundPlay( m_pSndSe[EN_SE_JUMP] );
						/* アイテ?に乗っていない場合はそこがリトライ位置 */
						if ( item_up() == -1 )
						{
							player[15] = player[0];
							player[16] = player[1];
						}
						player[10] = 0;
						player[11] = 0;
						player[2] = 21;	/* 空中 */
						player[14] = 5;
						player[13] = 0;
						player[25] = 1;
						jmp_st();
					}
				}
			}
		}

		if ( ( ( g_pApp->IsPressKey( DGXKEY_FX ) ) && ( GetSceneGameFlag1(132) == 0 ) )
			|| ( ( replay_load_key[5] == 1 ) && ( GetSceneGameFlag1(132) == 1 ) ) )
		{
		}
		else
		{
			if ( player[14] == 10 )
			{
			}
			else
			{
				if ( ( player[14] > 0 ) && ( player[25] == 1 ) )	/* 途中で落下 */
				{
//					player[14] = -1;
				}
			}
			player[25] = 0;
		}
	}


	if ( Jump_counts > 99 )
	{
		Jump_counts = 99;
	}


	//(E) 2010-07-20 Editor: AFEW
	/* 12??ン?か?Ｃが押された */
#if defined(GP2X_WIZ)
	int PopupKey = DGXKEY_SELECT;
#else
	int PopupKey = DGXKEY_HOME;
#endif


	if ( g_pApp->IsPushKey( PopupKey ) )
	{
		if ( m_nSn != 5 && m_nSn !=2 )	//回?中ではない
		{
			m_nSn = 4;
			demo[0] = 0;
			demo[1] = 0;
		}
	}




	if ( player[0] < 0 )	/* 画面左?判定 */
	{
		player[0] = 0;
		/*
		イベント中にsave_data[9]を設定することで、一時的にスクロ?ル不可とする。
		?ス戦などに使用
		*/
		if ( save_data[9] == 1 )	/* スクロ?ル不可 */
		{
		}

		else
		{
			if ( player[1] <= 460 )					/* キャラク??上方向が画面内 */
			{
				if ( map_data[4] == 1 )			/* スクロ?ル情報あり */
				{
					wait_scl( 2, map_data[5] );	/* スクロ?ル */
				}
				else if ( map_data[4] == 2 )	/* ステ?ジ移動情報あり */
				{
					end_scl( map_data[5] );		/* ステ?ジ移動 */
				}
			}
		}
	}




	if ( player[0] > ( MapInfo[2] - char_size[0] ) )	/* 画面右?判定 */
	{
		player[0] =  MapInfo[2] - char_size[0];
		if ( save_data[9] == 1 )	/* スクロ?ル不可 */ 
		{
		}

		else
		{
			if ( player[1] <= ( MapInfo[1] ) )
			{
				if ( map_data[6] == 1 )
				{
					wait_scl( 3, map_data[7] );
				}
				else if ( map_data[6] == 2 )
				{
					end_scl( map_data[7] );
				}
			}
		}
	}


	if ( player[1] <= 0 )	/* 画面下 */
	{
		if ( save_data[9] == 1 )	/* スクロ?ル不可 */
		{
		}
		else
		{
			if ( map_data[2] == 1 )
			{
				wait_scl( 1, map_data[3] );
			}
			else if ( map_data[2] == 2 )
			{
				end_scl( map_data[3] );
			}
		}
	}


	if ( player[1] >= ( MapInfo[3] - char_size[1] ) )	/* 画面上 */
	{
		if ( save_data[9] == 1 )	/* スクロ?ル不可 */
		{
		}
		else
		{
			if ( map_data[0] == 1 )
			{
				wait_scl( 0 , map_data[1] );
			}
			else if ( map_data[0] == 2 )
			{
				end_scl( map_data[1] );
			}
		}
	}

	return m_bExit;
}


void CGpAct::fram_set()
{
	if ( player[2] == 0 )	/* ニュ?トラル */
	{
		player[12] = 10;
	}
	if ( player[2] == 1 )	/* 歩き */
	{
		player[12] = 10;
	}
	if ( player[2] == 2 )	/* つかみ */
	{
		player[12] = 5;
	}
	if ( player[2] == 11 )	/* 攻撃 */
	{
		player[12] = 2;
	}
	if ( player[2] == 21 )	/* 空中 */
	{
		player[12] = 5;
	}
	if ( player[2] == 31 )	/* やられ */
	{
		player[12] = 10;
	}
	if ( player[2] == 33 )	/* クリア */
	{
		player[12] = 10;
	}
	if ( player[2] == 61 )	/* 上向き */
	{
		player[12] = 10;
	}
}


/* すい中の場合はジャンプ力増加 */
void CGpAct::jmp_st()
{
	long px1 ;
	long px2 ;
	long py ;
	long py2 ;

	px1 = ( player[0] + char_size[2] ) / 32;
	px2 = ( player[0] + char_size[3] ) / 32;
	py = ( MapInfo[1] - ( ( player[1] + ( char_size[1] - 5 ) ) / 32 ) );
	py2 = ( MapInfo[1] - ( ( player[1] + char_size[1] + ( char_size[1] - 5 ) ) / 32 ) );
	/* 水中判定 */

	if ( ( map1[ px1 + ( ( py ) * MapInfo[0] ) ] == 319 ) || ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] == 319 )
	  || ( map1[ px1 + ( ( py ) * MapInfo[0] ) ] == 419 ) || ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] == 419 )
	  || ( map1[ px1 + ( ( py ) * MapInfo[0] ) ] == 318 ) || ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] == 318 )
	  || ( map1[ px1 + ( ( py ) * MapInfo[0] ) ] == 418 ) || ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] == 418 )
	  || ( map1[ px1 + ( ( py ) * MapInfo[0] ) ] == 719 ) || ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] == 719 )
	  || ( map1[ px1 + ( ( py ) * MapInfo[0] ) ] == 718 ) || ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] == 718 ) )
	{
	}
	else
	{
	}
}

/* ジャンプＹ位置計算 */
void CGpAct::jmp()
{
	if(2 == m_nSn)
		return;
	
	long y1;
	long px ;
	long px1 ;
	long px2 ;
	long py ;
	long py3 ;

	/* ジャンプフレ??カウント */
	player[13]++;
	if ( player[13] >= 10 )
	{
		player[13] = 0;
	}

	if ( player[2] == 41 )	/* はしご中 */
	{
		player[18] = 0;			/* つかみからジャンプ */
		player[28] = 0;			/* 流されている */

		player[14] = 10;
		return;
	}

	/* 今回の位置 */
	px = ( player[0] + ( char_size[0] / 2 ) ) / 32;
	px1 = ( player[0] + char_size[2] ) / 32;
	px2 = ( player[0] + char_size[3] ) / 32;
//		py = ( 16 - ( ( player[1] + ( char_size[1] - 5 ) ) / 32 ) );
	py = ( MapInfo[1] - ( ( player[1] + ( char_size[1] - 5 ) ) / 32 ) );

	if ( player[14] == 10 ) 	/* 地上 */
	{

		/* 100 ? 200は地面 */
		/* 足元が地面ではない */
		if ( ( ( !( ( map1[ px1 + ( ( py ) * MapInfo[0] ) ] >= 100 ) && ( map1[ px1 + ( ( py ) * MapInfo[0] ) ] <= 119 ) ) )
		  && ( !( ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] >= 100 ) && ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] <= 119 ) ) )
		  && ( !( ( map1[ px1 + ( ( py ) * MapInfo[0] ) ] >= 200 ) && ( map1[ px1 + ( ( py ) * MapInfo[0] ) ] <= 219 ) ) )
		  && ( !( ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] >= 200 ) && ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] <= 219 ) ) )
		  && ( !( ( map1[ px1 + ( ( py ) * MapInfo[0] ) ] >= 600 ) && ( map1[ px1 + ( ( py ) * MapInfo[0] ) ] <= 619 ) ) )
		  && ( !( ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] >= 600 ) && ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] <= 619 ) ) ) )
		  || ( ( ( player[1] ) % 32 ) != 0 ) )
		{
			if ( item_up() != -1 )	/* アイテ?の上に乗っている */
			{
				player[1] = item_up();
				player[14] = 10;
				return;
			}

			/* 歩き中なら空中状態へ移行 */
			if ( ( player[2] == 0 )
			  || ( player[2] == 1 ) )
			{
				player[10] = 0;
				player[11] = 0;
				player[2] = 21;		/* 空中 */
			}
			player[14] = -1;			/* 落下開始 */
			player[13] = 0;

			if ( player[2] == 31 )	/* ?メ?ジ中 */
			{
			}
		}
		else
		{
			return;
		}
	}
	else
	{
		/* 歩き中なら空中状態へ移行 */
		if ( ( player[2] == 0 )
		  || ( player[2] == 1 ) )
		{
			player[10] = 0;
			player[11] = 0;
			player[2] = 21;		/* 空中 */
		}
		player[22] = 0;					/* 盾カウン? */
	}

	/* 10フレ??に1回Y座標計算 */
	if ( player[13] == 0 )
	{
		player[14] = player[14] - 2;	/* ジャンプ力減少 */

		/* 頂?付近は-1落下開始とする */
		if ( ( player[14] <= 2 ) && ( player[14] > -2 ) )
		{
			player[14] = -1;
		}

		if ( player[14] < -4 )	/* 最速落下を設定 */
		{
			player[14] = -4;
		}

		if ( ( map1[ px1 + ( ( py ) * MapInfo[0] ) ] == 319 ) || ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] == 319 )
		  || ( map1[ px1 + ( ( py ) * MapInfo[0] ) ] == 419 ) || ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] == 419 )
		  || ( map1[ px1 + ( ( py ) * MapInfo[0] ) ] == 318 ) || ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] == 318 )
		  || ( map1[ px1 + ( ( py ) * MapInfo[0] ) ] == 418 ) || ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] == 418 )
		  || ( map1[ px1 + ( ( py ) * MapInfo[0] ) ] == 719 ) || ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] == 719 )
		  || ( map1[ px1 + ( ( py ) * MapInfo[0] ) ] == 718 ) || ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] == 718 ) )
		{
		}
	}

	/* 水中判定等の背景によって落下速度が変わる場合は判定する */
	/* 今回の位置 */
	y1 = ( ( 0 - player[14] ) * ( 0 - player[14] ) * ( 0 - player[14] ) );
	px1 = ( player[0] + char_size[2] ) / 32;
	px2 = ( player[0] + char_size[3] ) / 32;
	py = ( MapInfo[1] - ( ( player[1] + ( char_size[1] - 5 ) ) / 32 ) );

	if ( ( map1[ px1 + ( ( py ) * MapInfo[0] ) ] == 319 ) || ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] == 319 )
	  || ( map1[ px1 + ( ( py ) * MapInfo[0] ) ] == 419 ) || ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] == 419 )
	  || ( map1[ px1 + ( ( py ) * MapInfo[0] ) ] == 318 ) || ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] == 318 )
	  || ( map1[ px1 + ( ( py ) * MapInfo[0] ) ] == 418 ) || ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] == 418 )
	  || ( map1[ px1 + ( ( py ) * MapInfo[0] ) ] == 719 ) || ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] == 719 )
	  || ( map1[ px1 + ( ( py ) * MapInfo[0] ) ] == 718 ) || ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] == 718 ) )
	{
		if ( player[14] > 0 ) /* 上昇中 */
		{
			player[1] = player[1] - ( y1 / 15 );
		}
		else
		{
			player[1] = player[1] - ( y1 / 50 );
		}
	}
	else
	{

		player[1] = player[1] - ( y1 / 20 );	/* Y移動 */
	}


	/* 落下、上昇可?判定 */
	/* 画面外の場合は行わない */
	if ( player[1] >= ( MapInfo[3] - char_size[1] ) )
	{
		return;
	}
	py3 = ( MapInfo[1] - ( ( player[1] + char_size[1] + 32 ) / 32 ) );

	/* 落下 */
	if ( player[14] <= 0 )													/* 上り中は判定しない */
	{
		/* 地面判定 */
		if ( ( ( map1[ px1 + ( ( py ) * MapInfo[0] ) ] >= 100 ) && ( map1[ px1 + ( ( py ) * MapInfo[0] ) ] <= 119 ) )
		  || ( ( map1[ px1 + ( ( py ) * MapInfo[0] ) ] >= 200 ) && ( map1[ px1 + ( ( py ) * MapInfo[0] ) ] <= 219 ) )
		  || ( ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] >= 100 ) && ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] <= 119 ) )
		  || ( ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] >= 200 ) && ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] <= 219 ) )
		  || ( ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] >= 600 ) && ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] <= 619 ) ) )
		{
			/* 着地 */
			if ( player[8] > 0 )	/* HPがある場合は効果音を鳴らす */
			{
				DGX_SoundPlay( m_pSndSe[EN_SE_LANDING] );
				se_wav( 9 );
			}
			if ( ( player[2] != 31 ) && ( player[2] != 32 ) )	/* ?メ?ジ中じゃない */
			{
				player[2] = 0;							/* 立ち状態へ */
				player[11] = 0;							/* アニメ?ションカウン?クリア */
			}
			player[1] = ( ( MapInfo[1] - py ) * 32 ); 		/* 着地した?スのY座標に合わせる */
			player[14] = 10;								/* ジャンプ力を地上に設定 */

			player[18] = 0;			/* つかみからジャンプ */
			player[28] = 0;			/* 流されている */

			p_jump_f_set( player[0], player[1] );
		}
		else
		{
			if ( item_up() != -1 )						/* アイテ?の上に乗っている */
			{
				DGX_SoundPlay( m_pSndSe[EN_SE_LANDING] );
				se_wav( 9 );
				if ( ( player[2] != 31 ) && ( player[2] != 32 ) )	/* ?メ?ジ中じゃない */
				{
					player[2] = 0;							/* 着地 */
					player[11] = 0;							/* アニメ?ションカウン?クリア */
				}
				player[1] = item_up();
				player[14] = 10;

				player[18] = 0;			/* つかみからジャンプ */
				player[28] = 0;			/* 流されている */

				p_jump_f_set( player[0], player[1] );
			}
		}
	}
	else		/* 上昇中 */
	{
		/* 地面判定 */
		if ( ( ( map1[ px1 + ( ( py3 ) * MapInfo[0] ) ] >= 100 ) && ( map1[ px1 + ( ( py3 ) * MapInfo[0] ) ] <= 119 ) )
		  || ( ( map1[ px1 + ( ( py3 ) * MapInfo[0] ) ] >= 200 ) && ( map1[ px1 + ( ( py3 ) * MapInfo[0] ) ] <= 219 ) )
		  || ( ( map1[ px2 + ( ( py3 ) * MapInfo[0] ) ] >= 100 ) && ( map1[ px2 + ( ( py3 ) * MapInfo[0] ) ] <= 119 ) )
		  || ( ( map1[ px2 + ( ( py3 ) * MapInfo[0] ) ] >= 200 ) && ( map1[ px2 + ( ( py3 ) * MapInfo[0] ) ] <= 219 ) ) )
		{
			/* 頭がぶつかった */
			player[13] = 0;
			player[14] = -3;		/* 落下 */
		}
		else
		{
			if ( item_up2() != -1 )	/* アイテ?に頭がぶつかる */
			{
				player[1] = item_up2();
				player[13] = 0;
				player[14] = -3;
			}
		}
	}
	/* 画面外、下に行った */
	if ( player[1] <= -14 )
	{
		if ( map_data[2] == 0 )		/* スクロ?ルしない場合は?メ?ジ */
		{
			if ( player[8] > 0 )			/* HPがある */
			{
				if ( player[17] == 0 )	/* 無敵時間が無い */
				{
					player[17] = 120;	/* 無敵時間 */
					player[8] = player[8] - 1;/* ?メ?ジ */
					se_wav( 1 );	/* ?メ?ジ効果音 */
				}
				if ( player[8] > 0 )		/* HPがある */
				{
					player[0] = player[15];	/* リトライ位置に移動 */
					player[1] = player[16];
					wait_scl2( save_data[3] ,player[0], player[1] );	/* 暗?戻り */

				}
				else
				{
					player[1] = -14;
				}
			}
			else
			{
				player[1] = -14;
			}
		}
	}

}

/* 左方向への移動判定 */
void CGpAct::idou_l()
{
	long px ;
	long py1 ;
	long py2 ;
	long bx ;
	long by ;

	long i;


	/* 今回の位置 */
	/* player[29]横バネ吹き飛び補正 */
	px = ( player[0] + char_size[2] + player[29] ) / 32;
	py1 = ( MapInfo[1] - ( ( player[1] + 32 + ( char_size[1] / 2 )  ) / 32 ) );
	py2 = ( MapInfo[1] - ( ( player[1] + 32 + 5 ) / 32 ) ); 						/* 足より５ドット高い場所を判定する */
	/* 画面外は一番上で判定 */
	if ( player[1] >= ( MapInfo[3] - char_size[1] ) )
	{
		py1 = 0;
		py2 = 0;
	}

	/* 502はしご上?501はしご中 */
	/* 壁に埋まった場合は壁際に移動 */
	if ( ( ( map1[ px + ( ( py1 ) * MapInfo[0] ) ] >= 100 ) && ( map1[ px + ( ( py1 ) * MapInfo[0] ) ] <= 299 ) )
	  || ( ( map1[ px + ( ( py2 ) * MapInfo[0] ) ] >= 100 ) && ( map1[ px + ( ( py2 ) * MapInfo[0] ) ] <= 299 ) ) )
	{
		px = ( player[0] + 16 ) / 32;
		player[0] = px * 32 - char_size[2];
		player[29] = 0;

		player[19] = 1;	//
	}
	else
	{

	}
	for ( i = 0; i < item_data[1]; ++i )
	{
		if ( item[( i * item_data[2] ) + 0 ] == 1 )
		{
			bx = item[( i * item_data[2] ) + 3 ] % 100;
			by = item[( i * item_data[2] ) + 3 ] / 100;
			/* プレイヤ?との当たり判定 */
			if ( ( ( (item[1 + ( i * item_data[2] )]  ) < (player[0]  + player[29] + char_size[3] ) )	/* 自?とのあたり判定 */
				&& ( (player[0] + player[29] + char_size[2] ) < (item[1 + ( i * item_data[2] )] + item_data[0] ) )
				&& ( (item[2 + ( i * item_data[2] )] ) < (player[1] + char_size[1] - 5 ) )
				&& ( (player[1] + 5 ) < ( item[2 + ( i * item_data[2] )] + item_data[0] ) ) ) )
			{
				if (
				     ( by == 3 ) /* 移動不可アイテ? */
				  || ( by == 6 ) /* 移動不可アイテ? */
				   )
				{
					px = ( player[0] + 16 ) / 32;
					player[0] = px * 32 - char_size[2];

					player[29] = 0;
					player[19] = 1;	//
				}
			}
		}
	}

}
/* 自分の左右に移動可?か？ */
void CGpAct::idou_r()
{
	long px ;
	long py1 ;
	long py2 ;
	long bx ;
	long by ;

	long i;

	/* 今回の位置 */
	/* player[29]横バネ吹き飛び補正 */
	px = ( player[0] + char_size[3] + player[29] ) / 32;
	py1 = ( MapInfo[1] - ( ( player[1] + 32 + ( char_size[1] / 2 ) ) / 32 ) );
	py2 = ( MapInfo[1] - ( ( player[1] + 32 + 5 ) / 32 ) ); /* 足より５ドット高い場所を判定する */
	/* 画面外は一番上で判定 */
	if ( player[1] >= ( MapInfo[3] - char_size[1] ) )
	{
		py1 = 0;
		py2 = 0;
	}

	/* 502はしご上?501はしご中 */
	if ( ( ( map1[ px + ( ( py1 ) * MapInfo[0] ) ] >= 100 ) && ( map1[ px + ( ( py1 ) * MapInfo[0] ) ] <= 299 ) )
	  || ( ( map1[ px + ( ( py2 ) * MapInfo[0] ) ] >= 100 ) && ( map1[ px + ( ( py2 ) * MapInfo[0] ) ] <= 299 ) ) )
	{
		px = ( player[0] + 16 ) / 32;
		player[0] = px * 32 + 9;
		player[29] = 0;

		player[19] = 2;
	}
	else
	{
	}
	for ( i = 0; i < item_data[1]; ++i )
	{
		if ( item[( i * item_data[2] ) + 0 ] == 1 )
		{
			bx = item[( i * item_data[2] ) + 3 ] % 100;
			by = item[( i * item_data[2] ) + 3 ] / 100;
			/* プレイヤ?との当たり判定 */
			if ( ( ( (item[1 + ( i * item_data[2] )]  ) < (player[0] + player[29] + char_size[3] ) )	/* 自?とのあたり判定 */
				&& ( (player[0] + player[29] + char_size[2] ) < (item[1 + ( i * item_data[2] )] + 32 ) )
				&& ( (item[2 + ( i * item_data[2] )] ) < (player[1] + char_size[1] - 5 ) )
				&& ( (player[1] + 5 ) < ( item[2 + ( i * item_data[2] )] + 32 ) ) ) )
			{
				if (
				     ( by == 3 ) /* 移動不可アイテ? */
				  || ( by == 6 ) /* 移動不可アイテ? */
				   )
				{
					px = ( player[0] + 16 ) / 32;
					player[0] = px * 32 + 9;

					player[29] = 0;
					player[19] = 2;
				}
			}
		}

	}

}

void CGpAct::Render()
{
	bg_disp();


	switch( m_nSn )
	{
	case 0:							// Before Play. Fade in
		bakdisp1();
		bakdisp2();
		item_disp();


		item_line();
		g_pSprite->Begin();

		enm_disp();
		playerdisp();
		snack_counter_disp();		// おやつカウン?
		mapdisp();
		stage_start();
		debugdisp();
		break;
		
	case 1 :						// Playing
		bakdisp1();
		bakdisp2();
		item_disp();

		item_line();
		g_pSprite->Begin();


		kane_disp();
		enm_disp();
		e_shot_disp();
		playerdisp();
		p_jump_f_disp();
		p_shot_disp();
		p_mgc_disp();
		p_shot_f2_disp();
		p_shot_f_disp();
		snack_counter_disp(); // おやつカウン?
		mapdisp();
		debugdisp();		/* デバッグ情報 */
		stage_endj();

		break;

	case 2 :				// Stage Clear
		bakdisp1();
		bakdisp2();
		item_disp();


		item_line();
		g_pSprite->Begin();

		p_shot_f2_disp();

		snack_counter_disp(); // おやつカウン?
		mapdisp();
		stage_claer();
		playerdisp();
		debugdisp();
		break;

	case 3 :		//ゲ??オ?バ?
		bakdisp1();
		bakdisp2();
		item_disp();


		item_line();
		g_pSprite->Begin();


		enm_disp();
		e_shot_disp();
		jmp();
		playerdisp();
		p_shot_disp();
		p_mgc_disp();
		p_shot_f2_disp();
		snack_counter_disp(); // おやつカウン?
		mapdisp();
		stage_end();
		debugdisp();
		break;


	case 4 :				// Return Game, Restart, Exit
		bakdisp1();
		bakdisp2();
		item_disp();

		item_line();
		g_pSprite->Begin();


		kane_disp();
		enm_disp();
		e_shot_disp();
		playerdisp();
		p_jump_f_disp();
		p_shot_disp();
		p_mgc_disp();
		p_shot_f2_disp();
		p_shot_f_disp();
		snack_counter_disp(); // おやつカウン?
		mapdisp();
		window_disp();
		debugdisp();
		break;

	case 5 :				// Rotation of Replay
		bak_rot();
		snack_counter_disp(); // おやつカウン?
		mapdisp();
		debugdisp();		/* デバッグ情報 */
		break;

	case 6 :				// view Map
		bakdisp1();
		bakdisp2();
		item_disp();

		item_line();
		g_pSprite->Begin();


		kane_disp();
		enm_disp();
		e_shot_disp();
		playerdisp();
		p_jump_f_disp();
		p_shot_disp();
		p_mgc_disp();
		p_shot_f2_disp();
		p_shot_f_disp();
		snack_counter_disp(); // おやつカウン?
		mapdisp();
		debugdisp();		/* デバッグ情報 */
		stage_endj();
		break;
	default :	//	どの条件にも満たない場合

		/* 画面切り替え時の?示対策 */
		player[0] = next_px;
		player[1] = next_py;

		m_bExit = 0;
		break;
	}
}



/* 一時フ?イル保存 */
void CGpAct::save_file_w()
{
	long i;

	SaveGameFlag("save/config");


	ResetGameFlag2();
//	save_data[7] = player[7];	/* ハ?トのかけら所持個数 */
	save_data[5] = player[8];	/* HP */
	save_data[2] = stage;

	save_data[0] = player[0];	/* Ｘ */
	save_data[1] = player[1];	/* Ｙ */
	save_data[4] = player[3];	/* 向き */
//	save_data[8] = player[6];	/* スキル */

	for ( i = 0; i < 512; ++i )
	{
		SetSceneGameFlag2(i, save_data[i] );
	}
	SaveGameFlag2( "save/work.sav");

	/* アイテ?取得情報 */
	ResetGameFlag2();

	for ( i = 0; i < 500; ++i )
	{
		SetSceneGameFlag2(i, item_wk[i] );
	}

	SaveGameFlag2("save/item_wk.sav");

}


// Rendering Player

void CGpAct::playerdisp()
{
	long arm_muki;

	arm_muki = 0;

	player[10]++;
	if ( player[10] >= player[12] )
	{
		player[10] = 0;

		player[11]++;
		/* 8パ??ンで1パ??ン目に戻る */
		if ( player[11] >= char_size[4] )
		{
			player[11] = 0;
			if ( player[2] == 21 )	/* 空中 */
			{
				player[11] = ( char_size[4] - 1 - 3 );		/* 5に戻す */
			}
			if ( player[2] == 11 )	/* 攻撃終了 */
			{
				player[2] = 0;
				if ( player[14] != 10 )	/* 空中 */
				{
					player[2] = 21;
				}
			}
			if ( player[2] == 31 )	/* ?メ?ジ */
			{
				player[2] = 0;
				if ( player[14] != 10 )	/* 空中 */
				{
					player[2] = 21;
				}
			}
			if ( player[2] == 32 )	/* ?ウンゲ??オ?バ? */
			{
				player[2] = 32;
				player[11] = ( char_size[4] - 1 );		/* 最終パ??ンのまま */
			}
			if ( player[2] == 33 )	/* クリア */
			{
				player[2] = 33;
				player[11] = ( char_size[4] - 1 - 3 );		/* 5に戻す */
			}
		}
	}

	fram_set();

	/* 画面相対座標での?示位置 */
	if ( player[3] == 1 )
	{
		if ( kamera < 0 )
		{
			kamera = 0;
		}
		kamera = kamera + 1;
		if ( kamera > 20 )
		{
			kamera = 20;
		}
		dp_x2 = dp_x2 + ( kamera / 6 );
		if ( dp_x2 > 200 )
		{
			dp_x2 = 200;
		}
	}
	else
	{
		if ( kamera > 0 )
		{
			kamera = 0;
		}
		kamera = kamera - 1;
		if ( kamera < -20 )
		{
			kamera = -20;
		}
		dp_x2 = dp_x2 + ( kamera / 6 );
		if ( dp_x2 < 80 )
		{
			dp_x2 = 80;
		}
	}
	dp_x2 = 160;

	dp_x = dp_x2 - 16;

	dp_y = 120 - 16;



	if ( player[2] == 0 )
	{
		player[4] = 0;
		player[5] = 0;
	}
	if ( player[18] > 0 )	/* 着地モ?ション?示 */
	{
		player[18]--;
	}
	if ( player[2] != 0 )
	{
		player[18] = 0;
	}
	else
	{
	}


	if ( player[2] == 1 )		/* 歩き */
	{
		player[4] = 0;
		player[5] = 1;
	}
	if ( player[2] == 2 )		/* つかみ */
	{
		player[4] = 0;
		player[5] = 3;
	}
	if ( player[2] == 11 )
	{
		player[4] = 0;
		player[5] = 3;
	}
	if ( player[2] == 21 )
	{
		player[4] = 0;
		player[5] = 2;
		if ( player[14] < 0 )	/* 落ちてる */
		{
			player[5] = 7;
		}
	}
	if ( player[2] == 31 )	/* ?メ?ジ */
	{
		player[4] = 0;
		player[5] = 5;

	}
	if ( player[2] == 32 )	/* ゲ??オ?バ? */
	{
		player[4] = 0;
		player[5] = 5;

	}
	if ( player[2] == 33 )	/* クリア */
	{
		player[4] = 0;
		player[5] = 8;

	}

	if ( GetSceneGameFlag1(128) == 0 )	//?ップビュ?ではない
	{
		if ( ( player[17] % 2 ) == 0 )
		{
			//(E) 2010-07-10 Editor: AFEW
			int tx = ( player[11] * char_size[0] ) + ( player[4] * ( char_size[0] * char_size[4] ) );
			int ty = ( player[5] * ( char_size[1] * 2 ) ) + ( player[3] * char_size[1] );

			if(ty>=320)
				ty = ty - (448 - 288);
			
			BltRect(m_vTex[1],
			         dp_x,
			         240 - dp_y - char_size[1],
			         tx,
			         ty,
			         char_size[0],
			         char_size[1] );
		}

		if ( player[30] > 0 )
		{
			player[30]--;
			BltRect(m_vTex[18], dp_x - 30, 240 - dp_y + 4, 0, 160, 100, 8 );	/* last one */
		}
		if ( player[24] > 0 )
		{
			player[24]--;
			BltRect(m_vTex[18], dp_x - 30, 240 - dp_y + 4 + 10, 0, 184, 200, 16 );	/* secret item get */
		}

		
		// Notify Direction of Rotation
		switch ( player[19] )
		{
		case 1:
			BltRect(m_vTex[5],
			         dp_x - 32,
			         240 - dp_y - char_size[1],
			         0,
			         80,
			         32,
			         32 );
			break;
		case 2:
			BltRect(m_vTex[5],
			         dp_x + 32,
			         240 - dp_y - char_size[1],
			         32,
			         80,
			         32,
			         32 );
			break;
		default:
			break;
		}
	}
}


void CGpAct::bg_disp()
{
	long x;
	long y;
	long b_x;
	long b_y;
	long i;

	x = 0;
	y = 0;
	b_x = 0;
	b_y = 0;
	i = 0;

	if ( GetSceneGameFlag1(67) == 1 )
	{
		rayer[0] = rayer[0] + 1;
		if ( rayer[0] > 640 )
		{
			rayer[0] = rayer[0] - 640;
		}
		rayer[1] = rayer[1] + 2;
		if ( rayer[1] > 640 )
		{
			rayer[1] = rayer[1] - 640;
		}
		rayer[2] = rayer[2] + 4;
		if ( rayer[2] > 640 )
		{
			rayer[2] = rayer[2] - 640;
		}
	}

	//画面背景を画面全体に?送
	bak_cnt = bak_cnt + 1;
	if ( bak_cnt >= 40 )
	{
		bak_cnt = 0;
	}


	d_x = player[0] - dp_x2 + 16 ;

	d_y = ( MapInfo[3] - 240 ) + ( 120 - 16 ) - player[1];



	/* 背景アニメ?ションON */

	int mapIdx = (save_data[3]+9)/10 -1;

	if(mapIdx<0)	mapIdx = 0;
	if(mapIdx>4)	mapIdx = 4;

	mapIdx += 110;

	Blt(m_vTex[mapIdx], 0, 0 );						/* 背景スクロ?ル演出 */
}


void CGpAct::bakdisp1()
{
	long x;
	long y;
	long b_x;
	long b_y;
	long i;

	x = 0;
	y = 0;
	b_x = 0;
	b_y = 0;
	i = 0;

	/* stage13,14,17は多重スクロ?ル */
	/* 地面?示 */
	for ( x = 0; x < MapInfo[1]; x++ )
	{
		for ( y = 0; y < MapInfo[1]; y++ )
		{

			if ( ( ( ( d_x - 32 ) <= ( x * 32 ) )
			  && ( ( d_y - 32 ) <= ( y * 32 ) )
			  && ( ( d_x + 320 + 32 ) >= ( x * 32 ) )
			  && ( ( d_y + 240 + 32 ) >= ( y * 32 ) ) )
			  || ( bak_alldrow == 1 )	 					/* 背景の?画をクリップするか */
			   )
			{
				b_y = map1[ x + ( y * MapInfo[0] ) ] / 100;
				b_x = map1[ x + ( y * MapInfo[0] ) ] % 100;

				
				if ( ( map1[ x + ( y * MapInfo[0] ) ] >= 100 ) && ( map1[ x + ( y * MapInfo[0] ) ] <= 219 ) )
				{
					//(E) 2010-07-14 Editor: AFEW
					// Empty Pixel
					//BltRect(m_vTex[10], ( x * 32 ) - d_x , ( y * 32 ) - d_y , 0 * 32 , 0 * 32 ,32, 32 );
				}
				else
				{
					int tx = (b_x-1) * 32;
					int ty = 0;


					if ( b_y == 1 )
					{
						ty = (5 + map_rot_info -1) * 32;
						BltRect(m_vTex[10], ( x * 32 )  - d_x , ( y * 32 )  - d_y , tx , ty, 32, 32 );
					}
					if ( b_y == 3 )
					{
						ty = (9 + map_rot_info -1) * 32;
						BltRect(m_vTex[10], ( x * 32 )  - d_x , ( y * 32 )  - d_y , tx , ty, 32, 32 );
					}
				}
			}
		}
	}

}


void CGpAct::bakdisp2()
{
	long i;
	long x;
	long y;
	long b_x;
	long b_y;

	i = bak_cnt / 10;

	for ( x = 0; x < MapInfo[1]; x++ )
	{
		for ( y = 0; y < MapInfo[1]; y++ )
		{

			if ( ( ( ( d_x - 32 ) <= ( x * 32 ) )
			  && ( ( d_y - 32 ) <= ( y * 32 ) )
			  && ( ( d_x + 320 + 32 ) >= ( x * 32 ) )
			  && ( ( d_y + 240 + 32 ) >= ( y * 32 ) ) )
			  || ( bak_alldrow == 1 )	 					/* 背景の?画をクリップするか */
			   )
			{

				if ( ( map1[ x + ( y * MapInfo[0] ) ] >= 100 ) && ( map1[ x + ( y * MapInfo[0] ) ] <= 219 ) )
				{
					b_y = map1[ x + ( y * MapInfo[0] ) ] / 100;
					b_x = map1[ x + ( y * MapInfo[0] ) ] % 100;
					if ( b_y == 1 )
					{
						//(E) 2010-07-14 Editor: AFEW
						int tx = ( b_x + ( ( map_data[13] - 1) * 2 ) -1 ) * 32;
						int ty = ( 5 + map_rot_info -1) * 32;
						BltRect(m_vTex[10], ( x * 32 )  - d_x , ( y * 32 )  - d_y , tx, ty ,32, 32 );
					}
					if ( b_y == 3 )
					{
						//(E) 2010-07-14 Editor: AFEW
						int tx = (b_x-1) * 32;
						int ty = ( 9 + map_rot_info -1) * 32;
						BltRect(m_vTex[10], ( x * 32 )  - d_x , ( y * 32 )  - d_y , tx, ty ,32, 32 );
					}

					b_y = map2[ x + ( y * MapInfo[0] ) ] / 100;
					b_x = map2[ x + ( y * MapInfo[0] ) ] % 100;
					if ( b_y == 1 )
					{
						//(E) 2010-07-14 Editor: AFEW
						int tx = (b_x-1) * 32;
						int ty = ( 5 + map_rot_info -1) * 32;

						tx -= 32;
						ty -= 32;
						BltRect(m_vTex[11], ( x * 32 )  - d_x , ( y * 32 )  - d_y , tx, ty ,32, 32 );
					}
					if ( b_y == 3 )
					{
						//(E) 2010-07-14 Editor: AFEW
						int tx = (b_x-1) * 32;
						int ty = ( 9 + map_rot_info -1) * 32;

						tx -= 32;
						ty -= 32;
						BltRect(m_vTex[11], ( x * 32 )  - d_x , ( y * 32 )  - d_y , tx, ty ,32, 32 );
					}
				}
				else
				{
					b_y = map2[ x + ( y * MapInfo[0] ) ] / 100;
					b_x = map2[ x + ( y * MapInfo[0] ) ] % 100;
					if ( b_y == 1 )
					{
						//(E) 2010-07-14 Editor: AFEW
						int tx = (b_x-1) * 32;
						int ty = ( 5 + map_rot_info -1) * 32;

						tx -= 32;
						ty -= 32;

						BltRect(m_vTex[11], ( x * 32 )  - d_x , ( y * 32 )  - d_y , tx, ty ,32, 32 );
					}

					if ( b_y == 3 )
					{
						//(E) 2010-07-14 Editor: AFEW
						int tx = (b_x-1) * 32;
						int ty = ( 9 + map_rot_info -1) * 32;

						tx -= 32;
						ty -= 32;
						BltRect(m_vTex[11], ( x * 32 )  - d_x , ( y * 32 )  - d_y , tx, ty ,32, 32 );
					}
				}
			}
		}
	}
}



void CGpAct::bak_rot()
{
	g_pSprite->Begin();

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
		glTranslatef(160, 120, 0);
		glRotatef(-(float)player[20], 0, 0, 1);
		glTranslatef(-160, -120, 0);
			bakdisp1();
			bakdisp2();
			item_disp();

			item_line();

	glPopMatrix();

	g_pSprite->End();

	g_pSprite->Begin();

	glPushMatrix();
		glTranslatef(160, 120, 0);
		glRotatef(-(float)player[20], 0, 0, 1);
		glTranslatef(-160, -120, 0);
			kane_disp();
			enm_disp();
			e_shot_disp();
			playerdisp();
			p_jump_f_disp();
			p_shot_disp();
			p_mgc_disp();
			p_shot_f2_disp();
			p_shot_f_disp();
	glPopMatrix();


	snack_counter_disp(); // おやつカウン?
	mapdisp();
	debugdisp();		/* デバッグ情報 */
	stage_endj();

	g_pSprite->End();
}




/* Ｗ?ＩＴつきスクロ?ル */
void CGpAct::wait_scl( long type, long d_num )
{
/*
	0:上	1:下	2:左	3:右
	よみこむフ?イルＮＯ
*/
	long i;
	long x;
	long y;
	char	strbuf[260]={0};

	se_wav( 14 );
	screen_BackupPlane();

	/* バッフ?クリア */
	for ( i = 0; i < 100; ++i )
	{
		p_ef[i * 5] = 0;						/* 存在 */
	}
	for ( i = 0; i < 40; ++i )
	{
		pmshot[i * 20 + 2] = 0;						/* 存在 */
	}
	for ( i = 0; i < 10; ++i )
	{
		pshot[i * 10 + 0] = 0 ;
	}
	for ( i = 0; i < 40; ++i )
	{
		pshotf[i * 10 + 0] = 0 ;
	}
	/* バッフ?クリア */
	for ( i = 0; i < 50; ++i )
	{
		item[i * 10 + 0] = 0 ;
	}
	for ( i = 0; i < 20; ++i )
	{
		enemy[i * 20 + 0] = 0 ;					/* 存在してない */
	}
	for ( i = 0; i < 20; ++i )
	{
		mgc_e[i * 10 + 0] = 0 ;					/* 存在してない */
	}
	for ( i = 0; i < 20; ++i )
	{
		kane[i * 10 + 0] = 0 ;					/* 存在してない */
	}



	ResetGameFlag2();
	sprintf(strbuf,"data/%d/%d_%d.map", (int)stage , (int)1, (int)d_num );
	LoadGameFlag2(strbuf);
	{
		for ( i = 0; i <= 319; ++i )
		{
			map1[i] = GetSceneGameFlag2(i);
		}
	}
	for ( i = 0 ; i <= 20 ; ++i )
	{
		map_data[i] = GetSceneGameFlag2(i + 320);
	}

	for ( i = 0 ; i < 5 ; ++i )
	{
		sprintf(strbuf,"image/bak/%d.png", (int)map_data[11 + i] );

		if ( ( i == 0 ) || ( map_data[11 + i] != 0 ) )
		{
			ReleaseImage(&m_vTex[110 + i]);
			LoadImage(&m_vTex[110 + i], strbuf, 0 );					//プレ?ンナンバ?２にシステ?用ＢＭＰを読み込む
		}
		else
		{
			ReleaseImage(&m_vTex[110 + i]);
		}
	}



	/* レイヤ?２ */
	ResetGameFlag2();
	sprintf(strbuf,"data/%d/%d_%d.map", (int)stage , (int)2, (int)d_num );
	if ( LoadGameFlag2(strbuf) == 0 )
	{
		for ( i = 0; i <= 319; ++i )
		{
			map2[i] = GetSceneGameFlag2(i);
		}
	}


	/* アイテ?配置 */
	ResetGameFlag2();
	sprintf(strbuf,"data/%d/i%d_%d.map", (int)stage , (int)1, (int)d_num );
	if ( LoadGameFlag2(strbuf) == 0 )
	{
		for ( x = 0; x <= 19 ; x++ )
		{
			for ( y = 0; y <= 16 ; y++ )
			{
				if ( GetSceneGameFlag2(x + ( y * 20 ) ) != 0 )
				{
					item_set( GetSceneGameFlag2(x + ( y * 20 ) ),  x * 32, ( ( 14 - y ) * 32 ) + 16, x + ( y * 20 ), d_num );
				}
			}
		}
	}


	ResetGameFlag2();				/* フ?イルなし */
	sprintf( strbuf,"data/%d/e%d_%d.map", (int)stage , (int)1, (int)d_num );
	LoadGameFlag2( strbuf );	/* 敵配置 */
	/* 敵配置 */
	for ( x = 0; x <= 19 ; x++ )
	{
		for ( y = 0; y <= 16 ; y++ )
		{
			if ( GetSceneGameFlag2(x + ( y * 20 ) ) != 0 )
			{
				enm_set( GetSceneGameFlag2(x + ( y * 20 ) ), x * 32, ( ( 14 - y ) * 32 ) + 16 );
			}
		}
	}

	save_data[3] = d_num;

	/* 上スクロ?ル */
	if ( type == 0 )
	{
		player[1] = 0;
	}
	/* 下スクロ?ル */
	if ( type == 1 )
	{
		player[1] = ( 480 - 32 - 16 );
	}
	/* 横スクロ?ル */
	if ( type == 3 )
	{
		player[0] = 0;
	}
	/* 横スクロ?ル */
	if ( type == 2 )
	{
		player[0] = ( 640 - 32 );
	}



	/* リトライ場所設定 */
	player[15] = player[0];
	player[16] = player[1];

	player[9] = 0;			/* 掴んでいる敵は消える */

}

/* Ｗ?ＩＴつきスクロ?ル */
void CGpAct::wait_scl2( long d_num ,long init_x, long init_y )
{
/*
	0:上	1:下	2:左	3:右
	よみこむフ?イルＮＯ
*/
	long i;
	long x;
	long y;
	char	strbuf[260]={0};

//	se_wav( 14 );
//	screen_BackupPlane();

	/* バッフ?クリア */
	for ( i = 0; i < 100; ++i )
	{
		p_ef[i * 5] = 0;						/* 存在 */
	}
	for ( i = 0; i < 40; ++i )
	{
		pmshot[i * 20 + 2] = 0;						/* 存在 */
	}
	for ( i = 0; i < 10; ++i )
	{
		pshot[i * 10 + 0] = 0 ;
	}
	for ( i = 0; i < 40; ++i )
	{
		pshotf[i * 10 + 0] = 0 ;
	}
	/* バッフ?クリア */
	for ( i = 0; i < 50; ++i )
	{
		item[i * 10 + 0] = 0 ;
	}
	for ( i = 0; i < 20; ++i )
	{
		enemy[i * 20 + 0] = 0 ;					/* 存在してない */
	}
	for ( i = 0; i < 20; ++i )
	{
		mgc_e[i * 10 + 0] = 0 ;					/* 存在してない */
	}
	for ( i = 0; i < 20; ++i )
	{
		kane[i * 10 + 0] = 0 ;					/* 存在してない */
	}


	ResetGameFlag2();
	sprintf(strbuf,"data/%d/%d_%d.map", (int)stage , (int)1, (int)d_num );
	LoadGameFlag2(strbuf);
	{
		for ( i = 0; i <= 319; ++i )
		{
			map1[i] = GetSceneGameFlag2(i);
		}
	}
	for ( i = 0 ; i <= 20 ; ++i )
	{
		map_data[i] = GetSceneGameFlag2(i + 320);
	}

	for ( i = 0 ; i < 5 ; ++i )
	{
		sprintf(strbuf,"image/bak/%d.png", (int)map_data[11 + i] );

		if ( ( i == 0 ) || ( map_data[11 + i] != 0 ) )
		{
			ReleaseImage(&m_vTex[110 + i]);
			LoadImage(&m_vTex[110 + i], strbuf, 0 );					//プレ?ンナンバ?２にシステ?用ＢＭＰを読み込む
		}
		else
		{
			ReleaseImage(&m_vTex[110 + i]);
		}
	}



	/* レイヤ?２ */
	ResetGameFlag2();
	sprintf(strbuf,"data/%d/%d_%d.map", (int)stage , (int)2, (int)d_num );
	if ( LoadGameFlag2(strbuf) == 0 )
	{
		for ( i = 0; i <= 319; ++i )
		{
			map2[i] = GetSceneGameFlag2(i);
		}
	}


	/* アイテ?配置 */
	ResetGameFlag2();
	sprintf(strbuf,"data/%d/i%d_%d.map", (int)stage , (int)1, (int)d_num );
	if ( LoadGameFlag2(strbuf) == 0 )
	{
		for ( x = 0; x <= 19 ; x++ )
		{
			for ( y = 0; y <= 16 ; y++ )
			{
				if ( GetSceneGameFlag2(x + ( y * 20 ) ) != 0 )
				{
					item_set( GetSceneGameFlag2(x + ( y * 20 )), x * 32, ( ( 14 - y ) * 32 ) + 16, x + ( y * 20 ), d_num );
				}
			}
		}
	}

	ResetGameFlag2();				/* フ?イルなし */
	sprintf( strbuf,"data/%d/e%d_%d.map", (int)stage , (int)1, (int)d_num );
	LoadGameFlag2( strbuf );	/* 敵配置 */
	/* 敵配置 */
	for ( x = 0; x <= 19 ; x++ )
	{
		for ( y = 0; y <= 16 ; y++ )
		{
			if ( GetSceneGameFlag2(x + ( y * 20 ) ) != 0 )
			{
				enm_set( GetSceneGameFlag2(x + ( y * 20 ) ), x * 32, ( ( 14 - y ) * 32 ) + 16 );
			}
		}
	}

	save_data[3] = d_num;

	player[0] = init_x;
	player[1] = init_y;


	/* リトライ場所設定 */
	player[15] = player[0];
	player[16] = player[1];


}

/* Ｗ?ＩＴつきスクロ?ル(reload専用、敵の再配置を行わない) */
void CGpAct::wait_scl3()
{
/*
	0:上	1:下	2:左	3:右
	よみこむフ?イルＮＯ
*/
	long i;
	long x;
	long y;
	long d_num;
	char	strbuf[260]={0};

	d_num = save_data[3];


	/* バッフ?クリア */
	for ( i = 0; i < 100; ++i )
	{
		p_ef[i * 10] = 0;						/* 存在 */
	}
	for ( i = 0; i < 40; ++i )
	{
		pmshot[i * 20 + 2] = 0;						/* 存在 */
	}
	for ( i = 0; i < 10; ++i )
	{
		pshot[i * 10 + 0] = 0 ;
	}
	for ( i = 0; i < 40; ++i )
	{
		pshotf[i * 10 + 0] = 0 ;
	}
	/* バッフ?クリア */
	for ( i = 0; i < 50; ++i )
	{
		item[i * 10 + 0] = 0 ;
	}
	for ( i = 0; i < 20; ++i )
	{
		if ( enemy[0 + ( i * 20 )] == 1 )					/* 存在してない */
		{
			enemy[1 + ( i * 20 )] = enemy[14 + ( i * 20 )] ;					/* 存在してない */
			enemy[2 + ( i * 20 )] = enemy[15 + ( i * 20 )] ;					/* 存在してない */
		}
	}
	for ( i = 0; i < 20; ++i )
	{
		mgc_e[i * 10 + 0] = 0 ;					/* 存在してない */
	}


	ResetGameFlag2();
	sprintf(strbuf,"data/%d/%d_%d.map", (int)stage , (int)1, (int)d_num );
	LoadGameFlag2(strbuf);
	{
		for ( i = 0; i <= 319; ++i )
		{
			map1[i] = GetSceneGameFlag2(i);
		}
	}
	for ( i = 0 ; i <= 20 ; ++i )
	{
		map_data[i] = GetSceneGameFlag2(i + 320);
	}

	for ( i = 0 ; i < 5 ; ++i )
	{
		sprintf(strbuf,"image/bak/%d.png", (int)map_data[11 + i] );

		if ( ( i == 0 ) || ( map_data[11 + i] != 0 ) )
		{
			ReleaseImage(&m_vTex[110 + i]);
			LoadImage(&m_vTex[110 + i], strbuf, 0 );					//プレ?ンナンバ?２にシステ?用ＢＭＰを読み込む
		}
		else
		{
			ReleaseImage(&m_vTex[110 + i]);
		}
	}



	/* レイヤ?２ */
	ResetGameFlag2();
	sprintf(strbuf,"data/%d/%d_%d.map", (int)stage , (int)2, (int)d_num );
	if ( LoadGameFlag2(strbuf) == 0 )
	{
		for ( i = 0; i <= 319; ++i )
		{
			map2[i] = GetSceneGameFlag2(i);
		}
	}


	/* アイテ?配置 */
	ResetGameFlag2();
	sprintf(strbuf,"data/%d/i%d_%d.map", (int)stage , (int)1, (int)d_num );
	if ( LoadGameFlag2(strbuf) == 0 )
	{
		for ( x = 0; x <= 19 ; x++ )
		{
			for ( y = 0; y <= 16 ; y++ )
			{
				if ( GetSceneGameFlag2(x + ( y * 20 ) ) != 0 )
				{
					item_set( GetSceneGameFlag2(x + ( y * 20 ) ), x * 32, ( ( 14 - y ) * 32 ) + 16, x + ( y * 20 ), d_num );
				}
			}
		}
	}

	ResetGameFlag2();				/* フ?イルなし */
	sprintf( strbuf,"data/%d/e%d_%d.map", (int)stage , (int)1, (int)d_num );
	LoadGameFlag2( strbuf );	/* 敵配置 */
	/* 敵配置 */
	for ( x = 0; x <= 19 ; x++ )
	{
		for ( y = 0; y <= 16 ; y++ )
		{
			if ( GetSceneGameFlag2(x + ( y * 20 ) ) != 0 )
			{
//				enm_set( GetSceneGameFlag2(x + ( y * 20 ) ), x * 32, ( ( 14 - y ) * 32 ) + 16 );
			}
		}
	}


	/* リトライ場所設定 */
	player[15] = player[0];
	player[16] = player[1];


}

void CGpAct::rotmap( long rot )
{
	long i;
	long size;
	long x;
	long y;
	long wx;
	long wy;
	long k;
	long by;
	long bx;

	k = 0;
	wx = 0;
	wy = 0;
	by = 0;
	bx = 0;

	x = 0;
	y = 0;


	switch( rot )
	{
	case 0:			// 移動無し
	case 360:		// 移動無し
		break;
	default:
		memcpy( mapfile, map1, sizeof( map1 ) );
		for ( x = 0; x < MapInfo[1]; x++ )
		{
			for ( y = 0; y < MapInfo[1]; y++ )
			{
				rotchangemap( x, y, rot , &wx, &wy );
				map1[ wx + ( wy * MapInfo[0] ) ] = mapfile[ ( x ) + ( y * MapInfo[0] ) ];
			}
		}

		memcpy( mapfile, map2, sizeof( map2 ) );
		for ( x = 0; x < MapInfo[1]; x++ )
		{
			for ( y = 0; y < MapInfo[1]; y++ )
			{
				rotchangemap( x, y, rot , &wx, &wy );
				map2[ wx + ( wy * MapInfo[0] ) ] = mapfile[ ( x ) + ( y * MapInfo[0] ) ];
			}
		}

		break;
	}



	wx = 0;
	wy = 0;
	// プレイヤ?の座標を変換
	rotchange( player[0] + ( char_size[0] / 2 ), player[1] + ( char_size[1] / 2 ), rot, &wx, &wy );

	player[0] = wx - ( char_size[0] / 2 ) - 1;	//壁に埋まってしまうため補正
	player[1] = wy - ( char_size[1] / 2 );


	for ( i = 0; i < item_data[1]; ++i )
	{
		if ( item[( i * item_data[2] ) + 0 ] == 1 )
		{
			rotchange( item[( i * item_data[2] ) + 1 ] + ( item_data[0] / 2 ), item[( i * item_data[2] ) + 2 ] + ( item_data[0] / 2 ), rot, &wx, &wy );
			item[( i * item_data[2] ) + 1 ] = wx - ( item_data[0] / 2 );
			item[( i * item_data[2] ) + 2 ] = wy - ( item_data[0] / 2 );

		}
	}
	for ( i = 0; i < item_data[1]; ++i )
	{
		if ( item[( i * item_data[2] ) + 0 ] == 1 )
		{
			by = item[( i * item_data[2] ) + 3 ] / 100;
			bx = item[( i * item_data[2] ) + 3 ] % 100;
			switch ( by )
			{
			case 2:	// 上方向
			case 3:
			case 4:
				if ( item[7 + ( i * item_data[2] )] >= 0 )
				{
					k = item[7 + ( i * item_data[2] )];	// 支?の取得
					item[6 + ( i * item_data[2] )] = 12;
					item[8 + ( i * item_data[2] )] = ( ( item[( k * item_data[2] ) + 1 ] + item[4 + ( i * item_data[2] )] ) - item[( i * item_data[2] ) + 1 ] ) / 10;
					item[9 + ( i * item_data[2] )] = ( ( item[( k * item_data[2] ) + 2 ] + item[5 + ( i * item_data[2] )] ) - item[( i * item_data[2] ) + 2 ] ) / 10;
				}
				break;
			case 10:
				switch( bx )
				{
				case 3:
				case 4:
				case 5:
				case 6:
					if ( rot == 270 )
					{
						item[( i * item_data[2] ) + 3 ] = item[( i * item_data[2] ) + 3 ] + 1;
					}
					else
					{
						item[( i * item_data[2] ) + 3 ] = item[( i * item_data[2] ) + 3 ] - 1;
					}
					if ( item[( i * item_data[2] ) + 3 ] > 1006 )
					{
						item[( i * item_data[2] ) + 3 ] = item[( i * item_data[2] ) + 3 ] - 4;
					}
					if ( item[( i * item_data[2] ) + 3 ] < 1003 )
					{
						item[( i * item_data[2] ) + 3 ] = item[( i * item_data[2] ) + 3 ] + 4;
					}
					break;
				default:
					break;
				}
				break;
			default:
				break;
			}
		}
	}
	for ( i = 0; i < enm_data[1]; ++i )
	{
		if ( enemy[0 +( i * enm_data[2] )] == 1 )
		{
			size = 32;
			/* 敵のサイズ取得 */
			if ( enemy[3 + ( i * enm_data[2] )] == 1 )
			{
				size = 32;
			}
			if ( enemy[3 + ( i * enm_data[2] )] == 2 )
			{
				size = 32;
			}
			if ( enemy[3 + ( i * enm_data[2] )] == 3 )
			{
				size = 32;
			}
			if ( enemy[3 + ( i * enm_data[2] )] == 4 )	/* 4?ス */
			{
				size = 32;
			}
			if ( enemy[3 + ( i * enm_data[2] )] == 5 )	/* 5?ス */
			{
				size = 32;
			}
			if ( enemy[3 + ( i * enm_data[2] )] == 6 )	/* 6?ス */
			{
				size = 32;
			}
			rotchange( enemy[( i * enm_data[2] ) + 1 ] + ( size / 2 ), enemy[( i * enm_data[2] ) + 2 ] + ( size / 2 ), rot, &wx, &wy );
			enemy[( i * enm_data[2] ) + 1 ] = wx - ( size / 2 );
			enemy[( i * enm_data[2] ) + 2 ] = wy - ( size / 2 );
		}
	}


	//パ?ティクルの移動
	for ( i = 0; i < PARTICLE; ++i )
	{
		if( !pshotf2[i].bAv)
			continue;

		rotchange( ( pshotf2[i].psX >> 16 ) + 16, ( pshotf2[i].psY >> 16 ) + 16, rot, &wx, &wy );
		pshotf2[i].psX = wx << 16 ;	/* 初期位置の設定 */
		pshotf2[i].psY = wy << 16 ;
	}

#ifdef GP2X
	replay_time = replay_time + 15;
#endif

}

void CGpAct::rotchangemap( long x1, long y1, long deg, long *x2, long *y2 )
{
	long rad; // 回?角度(ラジアン)

	long cx;
	long cy;

	long dx;
	long dy;

	long tmpX;
	long tmpY;


	rad = 360 - deg;

	cx = MapInfo[1] / 2; // ?ップの中心座標(X)
	cy = MapInfo[1] / 2; // ?ップの中心座標(Y)

	dx = x1 - cx; // 中心からの距離(X)
	dy = y1 - cy; // 中心からの距離(Y)

	tmpX = dx*funcCos(rad) - dy*funcSin(rad); // 回?
	tmpY = dx*funcSin(rad) + dy*funcCos(rad);

	tmpX = tmpX + ( 1 << 15 );
	tmpY = tmpY + ( 1 << 15 );

	*x2 = ( cx + ( tmpX >> 16 ) ); // 元の座標にオフセットする
	*y2 = ( cy + ( tmpY >> 16 ) );

}

void CGpAct::rotchange( long x1, long y1, long deg, long *x2, long *y2 )
{
	long rad; // 回?角度(ラジアン)

	long cx;
	long cy;

	long dx;
	long dy;

	long tmpX;
	long tmpY;

	rad = deg;

	cx = MapInfo[3] / 2; // ?ップの中心座標(X)
	cy = MapInfo[3] / 2; // ?ップの中心座標(Y)

	dx = x1 - cx; // 中心からの距離(X)
	dy = y1 - cy; // 中心からの距離(Y)

	tmpX = dx*funcCos(rad) - dy*funcSin(rad); // 回?
	tmpY = dx*funcSin(rad) + dy*funcCos(rad);

	tmpX = tmpX + ( 1 << 15 );
	tmpY = tmpY + ( 1 << 15 );

	*x2 = ( cx + ( tmpX >> 16 ) ); // 元の座標にオフセットする
	*y2 = ( cy + ( tmpY >> 16 ) );

}


// おやつカウン???示
void CGpAct::snack_counter_disp()
{
	long px;
	long py;
	long x;
	long dx;
	long dy;
	long i;
	long old_count;
	// おやつカウント

	old_count = snack_count;
	snack_count = 0;

	for(i = 0; i < enm_data[1]; ++i)
	{
		if ( ( enemy[0 +( i * enm_data[2] )] == 1 ) && ( enemy[3 +( i * enm_data[2] )] != 4 ) )
		{
			snack_count++;
		}
	}

	if ( ( old_count != snack_count ) && ( snack_count == 1 ) )
	{
		//last oneの?示
		player[30] = 180;
	}
	if ( ( old_count != snack_count ) && ( snack_count == 0 ) )
	{
		//last oneの?示
		player[30] = 0;
	}
	// 左上
	px = 10;
	py = 18;
	// 文字サイズ
	dx = 10;
	dy = 8;
	// 'rest' 残りおやつ
	x = 0;


	BltRect(m_vTex[18], 105, 2+m_EpsY, 0, 72, 100, 8 );	/* replay */
	BltNumericImage2( snack_count, 2, 155, 2+m_EpsY, m_vTex[18], 0, 0, 10, 8 );
}


//?ニ?ップの?示
void CGpAct::minimap_disp()
{
	long px;
	long py;
	long size;
	long width;
	long height;
	long i;
	long x;
	long y;
	// 左上
	px   = 2;
	py   = 12;
	size = 1;
	width  = size*MapInfo[1];
	height = size*MapInfo[1];

	if ( GetSceneGameFlag1(132) == 0 )
	{
		return;
	}


	Blt(m_vTex[70], px, py );

	// プレイヤ?
	x = px + 0      + ((player[0] / 32 + 0) * size);
	y = py + height - ((player[1] / 32 + 1) * size);
	BltRect(m_vTex[120], x, y, 127, 191, size, size );
	// おやつ
	for( i = 0; i < enm_data[1]; ++i)
	{
		if ( enemy[0 +( i * enm_data[2] )] == 1 )
		{
			x = px + 0      + ((enemy[1 +( i * enm_data[2])] / 32 + 0) * size);
			y = py + height - ((enemy[2 +( i * enm_data[2])] / 32 + 1) * size);
			BltRect(m_vTex[120], x, y, 127, 127, size, size );
		}
	}
}


//情報?示
void CGpAct::mapdisp()
{
	int stage_hosei;

	long wk;

	stage_hosei = 0;
	if ( stage == 2 )
	{
		stage_hosei = 50;
	}

	if ( GetSceneGameFlag1(128) != 0 )	//?ップビュ?
	{
		BltRect(m_vTex[18], 10, 25+m_EpsY, 0, 136, 100, 8 * 1 );	/* mapview */
	}

	if ( GetSceneGameFlag1(132) == 1 )
	{
//		if ( stage != 0 )
//		{
//			BltRect(m_vTex[18], 10, 15, 0, 32, 100, 8 );	/* replay */
//		}

		/* キ?入力 */
		if ( replay_load_key[0] == 1 )  /* l */
		{
			if ( replay_load_key[2] == 1 )  /* up */
			{
				BltRect(m_vTex[67], 10, 150, 256, 0, 64, 64 );	/* l */
			}
			else if ( replay_load_key[3] == 1 )  /* down */
			{
				BltRect(m_vTex[67], 10, 150, 192, 64, 64, 64 );	/* l */
			}
			else
			{
				BltRect(m_vTex[67], 10, 150, 128, 64, 64, 64 );	/* l */
			}
		}
		else if ( replay_load_key[1] == 1 )  /* r */
		{
			if ( replay_load_key[2] == 1 )  /* up */
			{
				BltRect(m_vTex[67], 10, 150, 192, 0, 64, 64 );	/* r */
			}
			else if ( replay_load_key[3] == 1 )  /* down */
			{
				BltRect(m_vTex[67], 10, 150, 256, 64, 64, 64 );	/* r */
			}
			else
			{
				BltRect(m_vTex[67], 10, 150, 64, 64, 64, 64 );	/* r */
			}
		}
		else
		{
			if ( replay_load_key[2] == 1 )  /* up */
			{
				BltRect(m_vTex[67], 10, 150, 64, 0, 64, 64 );	/* r */
			}
			else if ( replay_load_key[3] == 1 )  /* down */
			{
				BltRect(m_vTex[67], 10, 150, 128, 0, 64, 64 );	/* r */
			}
			else
			{
				BltRect(m_vTex[67], 10, 150, 0, 0, 64, 64 );	/* r */
			}
		}
		if ( replay_load_key[4] == 1 )  /* 1 */
		{
			BltRect(m_vTex[67], 90, 190, 32, 128, 32, 32 );	/* off */
		}
		else
		{
			BltRect(m_vTex[67], 90, 190, 0, 128, 32, 32 );	/* on */
		}
		if ( replay_load_key[5] == 1 )  /* 2 */
		{
			BltRect(m_vTex[67], 130, 190, 32, 128, 32, 32 );	/* off */
		}
		else
		{
			BltRect(m_vTex[67], 130, 190, 0, 128, 32, 32 );	/* on */
		}
	}

	if ( stage != 0 )
	{
		if ( GetSceneGameFlag1(127) == 1 )	//ト??ルア?ック
		{
			BltRect(m_vTex[18], 5, 220, 0, 128, 100, 8 );	/* rank */
		}
		else if ( stage == 2 )
		{
			BltRect(m_vTex[18], 5, 220, 0, 112, 100, 8 );	/* rank */
		}
		else
		{
			if ( ( save_data[3] >= 1 ) && ( save_data[3] <= 10 ) )
			{
				BltRect(m_vTex[18], 5, 220, 0, 88, 100, 8 );	/* rank */
			}
			if ( ( save_data[3] >= 11 ) && ( save_data[3] <= 30 ) )
			{
				BltRect(m_vTex[18], 5, 220, 0, 96, 100, 8 );	/* rank */
			}
			if ( ( save_data[3] >= 31 ) && ( save_data[3] <= 50 ) )
			{
				BltRect(m_vTex[18], 5, 220, 0, 104, 100, 8 );	/* rank */
			}
		}


		// state
		BltRect(m_vTex[18], 10, 2+m_EpsY, 0, 40, 100, 8 );	/*  */
		BltNumericImage2( save_data[3], 2, 70, 2+m_EpsY, m_vTex[18], 0, 0, 10, 8 );	/* d_num */

		if ( GetSceneGameFlag1(127) == 1 )	//ト??ルア?ック
		{
			BltRect(m_vTex[18], 180, 2, 0, 120, 100, 8 );	/*  */
			BltNumericImage2( GetSceneGameFlag1(136), 3, 250, 2, m_vTex[18], 0, 0, 10, 8 );	/* miss count */
		}
		else
		{
			BltRect(m_vTex[18], 190, 2+m_EpsY, 0, 80, 100, 8 );	/*  */
			BltNumericImage2( Jump_counts, 2, 280, 2+m_EpsY, m_vTex[18], 0, 0, 10, 8 );	/* Jump_counts */
		}

		BltRect(m_vTex[18], 50, 230, 0, 8, 100, 8 );	/*  */
		BltRect(m_vTex[18], 5, 230, 0, 16, 100, 8 );	/*  */

		BltRect(m_vTex[18], 200, 230 , 0, 8, 100, 8 );	/*  */
		BltRect(m_vTex[18], 155, 230 , 0, 24, 100, 8 );	/*  */

		BltNumericImage( play_time[0], 2, 110, 230, m_vTex[18], 0, 0, 10, 8 );	/* 時間 */
		BltNumericImage( play_time[1], 2,  80, 230, m_vTex[18], 0, 0, 10, 8 );	/* 時間 */
		BltNumericImage( play_time[2], 2,  50, 230, m_vTex[18], 0, 0, 10, 8 );	/* 時間 */

		if ( GetSceneGameFlag1(127) == 1 )	//ト??ルア?ック
		{
			wk = get2keta( GetSceneGameFlag1(137) , 1 );
			BltNumericImage( wk, 2, 260, 230, m_vTex[18], 0, 0, 10, 8 );

			wk = get2keta( GetSceneGameFlag1(137) , 100 );
			BltNumericImage( wk, 2, 230, 230, m_vTex[18], 0, 0, 10, 8 );

			wk = get2keta( GetSceneGameFlag1(137) , 10000 );
			BltNumericImage( wk, 2, 200, 230, m_vTex[18], 0, 0, 10, 8 );
		}
		else
		{
			wk = get2keta( GetSceneGameFlag1(200 + save_data[3] + stage_hosei) , 1 );
			BltNumericImage( wk, 2, 260, 230, m_vTex[18], 0, 0, 10, 8 );

			wk = get2keta( GetSceneGameFlag1(200 + save_data[3] + stage_hosei) , 100 );
			BltNumericImage( wk, 2, 230, 230, m_vTex[18], 0, 0, 10, 8 );

			wk = get2keta( GetSceneGameFlag1(200 + save_data[3] + stage_hosei) , 10000 );
			BltNumericImage( wk, 2, 200, 230, m_vTex[18], 0, 0, 10, 8 );
		}
	}
	else
	{
		BltRect(m_vTex[18], 190, 2, 0, 80, 100, 8 );	/*  */
		BltNumericImage2( Jump_counts, 2, 280, 2, m_vTex[18], 0, 0, 10, 8 );	/* Jump_counts */
	}

	// 方向の?示
	BltRect(m_vTex[76], 280, 122, 0 + ( map_rot_info * 32 ), 0, 32, 32 );	/*  */

	//完成品の?示
	BltRect(m_vTex[6], 240, 240 - 96, 0, 64 , 96, 96 );	/*  */
	if ( ( m_nSn == 1 ) || ( m_nSn == 5 ) || ( m_nSn == 4 ) )
	{
		if ( snack_count != all_snack_count )
		{
			BltRect(m_vTex[6], 240 + 32, 240 - 96 + 32, 0 + ( ( ( save_data[3] - 1 ) % 10 ) * 32 ), 160 + ( ( ( save_data[3] - 1 ) / 10 ) * 32 ) , 32 - ( ( snack_count * 100 ) / ( ( all_snack_count * 100 ) / 32 ) ), 32 );	/*  */
		}
	}

	//カットインの?示
	if ( player[31] > 0 )
	{
		wk = player[31];
		if ( wk < 60 )
		{
			wk = 0;
		}
		else
		{
			wk = wk - 60;
		}
		BltRect(m_vTex[6], ( 320 - 64 ) + ( wk * wk ), 240 - 64 - 20, 0 + ( player[32] * 64 ), 0 , 64, 64 );	/*  */
		player[31]--;
	}

}



// se再生
void CGpAct::se_wav(long SeWavNo)
{

}



//開始
void CGpAct::stage_start()
{
	int x = 0;
	int y = 0;
	int rec = 0;
	int rec2 = 0;


	demo[0]++;

	rec = 32 - ( demo[0] * 2 );
	if ( rec < 0 )
	{
		rec = 0;
	}
	rec2 = demo[0];
	if ( rec2 > 16 )
	{
		rec2 = 16;
	}

	for ( x = 0; x < 10; x++ )
	{
		for ( y = 0; y < 8; y++ )
		{
			BltRect(m_vTex[72], ( x * 32 ) + rec2, ( y * 32 ) + rec2, 0, 0, rec, rec );
		}
	}

	// stage start
	BltRect(m_vTex[71], 90, 80, 0, 0, 200, 32 );

	if ( demo[0] >= 120 )
	{
		// go
		BltRect(m_vTex[71], 150, 140, 0, 64, 200, 32 );
	}
	else if ( demo[0] >= 60 )
	{
		// ready
		BltRect(m_vTex[71], 130, 140, 0, 32, 200, 32 );
	}

	if (
	     ( demo[0] >= 180 )
	  || ( ( 0 != GetSceneDebugStateProduct() ) && ( demo[0] >= 2 ) )
	  || ( ( GetSceneGameFlag1(134) != 0 ) && ( demo[0] >= 2 ) )
	   )
	{
		demo[0] = 0;
		m_nSn = 1;
	}

}


void CGpAct::stage_endj()
{

	if ( player[8] <= 0 )		/* ライフ０ */
	{

		player[2] = 32;	/* ?ウンモ?ション */
		player[10] = 0;	/* ?ウンモ?ション */
		player[11] = 0;	/* ?ウンモ?ション */

		m_nSn = 3;
		demo[0] = 0;
	}
}

void CGpAct::stage_claer()
{
	int stage_hosei;
	int rec = 0;
	int rec2 = 0;
	int x = 0;
	int y = 0;
	int newrecode = 0;
	int fead = 0;
	int wk = 0;

	stage_hosei = 0;
	if ( stage == 2 )
	{
		stage_hosei = 50;
	}


	if ( demo[0] == 0 )
	{
		demo[1] = 62;
//		demo[2] = 126;
		demo[2] = 148;
	}
	demo[0]++;


	play_time[4] = 1000000 + ( play_time[2] * 10000 ) + ( play_time[1] * 100 ) + ( play_time[0] );

	fead = demo[0] - 140;
	if ( fead < 0 )
	{
		fead = 0;
	}
	rec = ( fead * 2 );
	if ( rec > 32 )
	{
		rec = 32;
	}
	rec2 = 16 - fead;
	if ( rec2 < 0 )
	{
		rec2 = 0;
	}

	for ( x = 0; x < 10; x++ )
	{
		for ( y = 0; y < 8; y++ )
		{
			BltRect(m_vTex[72], ( x * 32 ) + rec2, ( y * 32 ) + rec2, 0, 0, rec, rec );
		}
	}

	if ( GetSceneGameFlag1(127) == 0 )	//ト??ルア?ック
	{
		if ( ( GetSceneGameFlag1(300 + save_data[3] + stage_hosei) > Jump_counts ) )
		{
			if ( GetSceneGameFlag1(132) == 0 )
			{
				// 新記?
				Blt(m_vTex[74], 74, 18);
				Blt(m_vTex[69], 29, 188 );
				newrecode = 1;
			}
		}
		if ( ( GetSceneGameFlag1(200 + save_data[3] + stage_hosei) > play_time[4] ) )
		{
			if ( GetSceneGameFlag1(132) == 0 )
			{
				// 新記?
				Blt(m_vTex[74], 74, 18);
				Blt(m_vTex[68], 19, 208 );
				newrecode = 1;
			}
		}
	}
	if ( newrecode == 0 )
	{
		// stage clear
		Blt(m_vTex[73], 70, 18);
		BltRect(m_vTex[71], 90, 180, 0, 96, 200, 32 );


		//(E) 2010-07-21 Editor: AFEW
		if ( demo[0] == 1 )
		{
			//(E) 2010-07-10 Editor: AFEW
			if(m_pSndBg)
				m_pSndBg->SetVolume( 10/128.F );

			DGX_SoundPlay( m_pSndSe[EN_SE_CL21] );						// Play
		}
	}
	else
	{
		if ( demo[0] == 1 )
		{
			//(E) 2010-07-10 Editor: AFEW
			if(m_pSndBg)
				m_pSndBg->SetVolume( 100/128.F );

			DGX_SoundPlay( m_pSndSe[EN_SE_CL1] );						// Play
		}
	}

	if ( stage != 0 )
	{
		Blt(m_vTex[75], 30, 138 );
		//目標?イ?
		if ( target_save[200 + save_data[3] + stage_hosei] >= play_time[4] )
		{
			BltRect(m_vTex[61], 20, 138, 0, 128 , 20, 20 );
		}
		//目標回?
		if ( target_save[300 + save_data[3] + stage_hosei] >= Jump_counts )
		{
			BltRect(m_vTex[61], 20, 154, 0, 128 , 20, 20 );
		}
		// best
		wk = get2keta( target_save[200 + save_data[3] + stage_hosei], 1 );
		BltNumericImage( wk, 2, 250, 146, m_vTex[18], 0, 0, 10, 8 );	/*  */

		wk = get2keta( target_save[200 + save_data[3] + stage_hosei], 100 );
		BltNumericImage( wk, 2, 220, 146, m_vTex[18], 0, 0, 10, 8 );	/*  */

		wk = get2keta( target_save[200 + save_data[3] + stage_hosei], 10000 );
		BltNumericImage( wk, 2, 190, 146, m_vTex[18], 0, 0, 10, 8 );	/*  */

		BltNumericImage2( target_save[300 + save_data[3] + stage_hosei], 2, 190, 162, m_vTex[18], 0, 0, 10, 8 );	/* Jump_counts */

		// now
		wk = get2keta( play_time[4], 1 );
		BltNumericImage( wk, 2, 250, 138, m_vTex[18], 0, 0, 10, 8 );	/*  */

		wk = get2keta( play_time[4], 100 );
		BltNumericImage( wk, 2, 220, 138, m_vTex[18], 0, 0, 10, 8 );	/*  */

		wk = get2keta( play_time[4], 10000 );
		BltNumericImage( wk, 2, 190, 138, m_vTex[18], 0, 0, 10, 8 );	/*  */

		BltNumericImage2( Jump_counts, 2, 190, 154, m_vTex[18], 0, 0, 10, 8 );	/* Jump_counts */

		if ( secretitemget == 1 )
		{
			BltRect(m_vTex[18], 190, 170, 0, 176, 200, 8 );	/* ?イ? */
			BltRect(m_vTex[61], 20, 170, 0, 128 , 20, 20 );
		}
		else
		{
			BltRect(m_vTex[18], 190, 170, 0, 168, 200, 8 );	/* ?イ? */
		}

		BltRect(m_vTex[18], 200, 230 , 0, 8, 100, 8 );	/*  */
		BltRect(m_vTex[18], 155, 230 , 0, 24, 100, 8 );	/*  */

		wk = get2keta( GetSceneGameFlag1(200 + save_data[3] + stage_hosei) , 1 );
		BltNumericImage( wk, 2, 260, 230, m_vTex[18], 0, 0, 10, 8 );

		wk = get2keta( GetSceneGameFlag1(200 + save_data[3] + stage_hosei) , 100 );
		BltNumericImage( wk, 2, 230, 230, m_vTex[18], 0, 0, 10, 8 );

		wk = get2keta( GetSceneGameFlag1(200 + save_data[3] + stage_hosei) , 10000 );
		BltNumericImage( wk, 2, 200, 230, m_vTex[18], 0, 0, 10, 8 );



	}
	//完成品の取得1
	if ( demo[2] > 0 )
	{
		demo[2] = demo[2] - 1;
		if ( demo[2] <= 0 )
		{
//			DGX_SoundPlay( m_pSndSe[EN_SE_CL1] );
		}
		demo[1] = demo[1] + 3;
		if ( demo[1] > 360 )
		{
			demo[1] = demo[1] - 360;
		}
		x = 160 + ( ( funcSin( demo[1] ) * ( demo[2] ) ) >> 16 );
		y = 120 + ( ( funcCos( demo[1] ) * ( demo[2] ) ) >> 16 );
		BltRect(m_vTex[6], x - 16, y - 16, 0 + ( ( ( save_data[3] - 1 ) % 10 ) * 32 ), 160 + ( ( ( save_data[3] - 1 ) / 10 ) * 32 ), 32, 32 );	/*  */


		p_shot_f2_set( x, y , 2 + ( rand() % 3 ) );
	}
	else
	{
		BltRect(m_vTex[6], 110, 104, 0 + ( ( ( save_data[3] - 1 ) % 10 ) * 32 ), 160 + ( ( ( save_data[3] - 1 ) / 10 ) * 32 ), 32, 32 );	/*  */
	}




	if ( demo[0] >= ( 60 * 3 ) )
	{
		demo[0] = ( 60 * 3 );

		//(E) 2010-07-16 Editor: AFEW
		//BltRect(m_vTex[18], 180, 114, 0, 144, 100, 8 * 2 );	/* 1 key to exit  */
	}

	if ( ( ( demo[0] >= ( 60 * 3 ) ) && ( g_pApp->IsPushOKKey() ) )|| ( ( 0 != GetSceneDebugStateProduct() ) && ( demo[0] >= 2 ) ) )
	{
		if ( GetSceneGameFlag1(132) == 0 )
		{
			if ( GetSceneGameFlag1(127) == 1 )	//ト??ルア?ック
			{
				SetSceneGameFlag1(135, play_time[4]);
			}
			else
			{
				replay_file_save_w();
				if ( GetSceneGameFlag1(200 + save_data[3] + stage_hosei) > play_time[4] )
				{
					SetSceneGameFlag1(200 + save_data[3] + stage_hosei, play_time[4]);	/* スコア保存 */

					replay_file_save( 0 );
				}

				if ( GetSceneGameFlag1(300 + save_data[3] + stage_hosei) > Jump_counts )
				{
					SetSceneGameFlag1(300 + save_data[3] + stage_hosei, Jump_counts);	/* スコア保存 */

					replay_file_save( 1 );
				}

				if ( secretitemget == 1 )
				{
					SetSceneGameFlag1(400 + save_data[3] + stage_hosei, 1);
				}
			}

			if ( GetSceneGameFlag1(129) != 0 )	//ステ?ジセレクトから開始
			{
				SetSceneGameFlag1(40, 1);
				SetSceneState(EN_SN_STAGE);
				Destroy();
				m_bExit = 0;
			}
			else
			{
				save_data[3]++;
				SetSceneGameFlag1(120, save_data[3]);

				//(E) 2010-07-20 Editor: AFEW

				if(51>save_data[3])
					save_file_w();

				if (
				     ( save_data[3] == 1 )
				  || ( save_data[3] == 11 )
				  || ( save_data[3] == 21 )
				  || ( save_data[3] == 31 )
				  || ( save_data[3] == 41 )
				   )
				{
					if ( GetSceneGameFlag1(127) == 0 )	//ト??ルア?ックではない
					{
						m_bDemo = 1;
					}
				}
			}


			if ( GetSceneGameFlag1(121) < save_data[3] )
			{
				SetSceneGameFlag1(121, save_data[3]);
			}
		}
		else
		{
//			replay_file_save_w();
			if ( GetSceneGameFlag1(129) != 0 )	//ステ?ジセレクトから開始
			{
				SetSceneGameFlag1(40, 1);
				SetSceneState(EN_SN_STAGE);
				Destroy();
				m_bExit = 0;
			}
			else
			{
				save_data[3]++;
			}
			if ( ( GetSceneGameFlag1(124) == 1 ) || ( stage == 0 ) )	/* リプレイＯＮＥ */
			{
				SetSceneGameFlag1(40, 1);
				SetSceneState(EN_SN_TITLE);
			}
		}
		m_nSn = 10;
	}


	if ( player[2] != 33 )
	{
		player[10] = 0 ;
		player[11] = 0 ;
		player[2] = 33 ;
	}
}


void CGpAct::stage_end()
{
	demo[0]++;
	if ( demo[0] > 60 )
	{
		if ( player[8] <= 0 )		/* ライフ０ */
		{
			long nState = GetSceneGameFlag1(136);
			++nState;
			SetSceneGameFlag1(136, nState);

			if ( GetSceneGameFlag1(136) > 999 )	/* ?スカウント */
			{
				SetSceneGameFlag1(136, 999);
			}
		}
		if ( GetSceneGameFlag1(127) == 1 )	//ト??ルア?ック
		{
			play_time[4] = 1000000 + ( play_time[2] * 10000 ) + ( play_time[1] * 100 ) + ( play_time[0] );
			SetSceneGameFlag1(135, play_time[4]);
		}

		SetSceneGameFlag1(71, 1);
		m_nSn = 10;
	}
}


/* ?ップの?に触れてステ?ジ移動 */
void CGpAct::end_scl( long s_num )
{
}



void CGpAct::p_shot_set( long type , long muki, long houkou )
{
	long i;

	for ( i = 0; i < 10; ++i )
	{
		if ( pshot[( i * 10 ) + 0 ] == 0 )
		{
			pshot[( i * 10 ) + 0 ] = 1;
			pshot[( i * 10 ) + 1 ] = player[0];
			pshot[( i * 10 ) + 2 ] = player[1];
			pshot[( i * 10 ) + 3 ] = houkou;	/* 左右 */
			pshot[( i * 10 ) + 4 ] = muki;	/* 方向 */
			pshot[( i * 10 ) + 5 ] = 0;
			pshot[( i * 10 ) + 6 ] = 0;
			pshot[( i * 10 ) + 7 ] = type;
			pshot[( i * 10 ) + 8 ] = 0;		/* あたり判定座標X */
			pshot[( i * 10 ) + 9 ] = 0;		/* あたり判定座標X */

			break;
		}
	}
}


void CGpAct::p_shot_disp()
{
	long i;

	for ( i = 0; i < 10; ++i )
	{
		if ( pshot[( i * 10 ) + 0 ] == 1 )
		{
			/* 位置補正 */
			pshot[( i * 10 ) + 1 ] = player[0];
			pshot[( i * 10 ) + 2 ] = player[1];

			if ( pshot[( i * 10 ) + 3 ] == 0 )
			{
				if ( pshot[( i * 10 ) + 4 ] == 0 )
				{
					pshot[( i * 10 ) + 1 ] = player[0] - 16;
					pshot[( i * 10 ) + 2 ] = player[1] + 16;
					pshot[( i * 10 ) + 8 ] = 0;		/* あたり判定座標X */
					pshot[( i * 10 ) + 9 ] = 0;		/* あたり判定座標X */
				}
				if ( pshot[( i * 10 ) + 4 ] == 1 )
				{
					pshot[( i * 10 ) + 1 ] = player[0] + 5;
					pshot[( i * 10 ) + 2 ] = player[1] + 10;
					pshot[( i * 10 ) + 8 ] = 0;		/* あたり判定座標X */
					pshot[( i * 10 ) + 9 ] = 0;		/* あたり判定座標X */
				}
				if ( pshot[( i * 10 ) + 4 ] == 2 )
				{
					pshot[( i * 10 ) + 1 ] = player[0] + 5;
					pshot[( i * 10 ) + 2 ] = player[1] - 16;
					pshot[( i * 10 ) + 8 ] = 0;		/* あたり判定座標X */
					pshot[( i * 10 ) + 9 ] = 0;		/* あたり判定座標X */
				}
				if ( pshot[( i * 10 ) + 4 ] == 3 )
				{
					pshot[( i * 10 ) + 1 ] = player[0] + 5;
					pshot[( i * 10 ) + 2 ] = player[1] - 43;
					pshot[( i * 10 ) + 8 ] = 0;		/* あたり判定座標X */
					pshot[( i * 10 ) + 9 ] = 0;		/* あたり判定座標X */
				}
				if ( pshot[( i * 10 ) + 4 ] == 4 )
				{
					pshot[( i * 10 ) + 1 ] = player[0] - 16;
					pshot[( i * 10 ) + 2 ] = player[1] - 43;
					pshot[( i * 10 ) + 8 ] = 0;		/* あたり判定座標X */
					pshot[( i * 10 ) + 9 ] = 0;		/* あたり判定座標X */
				}
			}
			else if ( pshot[( i * 10 ) + 3 ] == 1 )
			{
				if ( pshot[( i * 10 ) + 4 ] == 0 )
				{
					pshot[( i * 10 ) + 1 ] = player[0] - 16;
					pshot[( i * 10 ) + 2 ] = player[1] + 16;
				}
				if ( pshot[( i * 10 ) + 4 ] == 1 )
				{
					pshot[( i * 10 ) + 1 ] = player[0] - 37;
					pshot[( i * 10 ) + 2 ] = player[1] + 10;
				}
				if ( pshot[( i * 10 ) + 4 ] == 2 )
				{
					pshot[( i * 10 ) + 1 ] = player[0] - 37;
					pshot[( i * 10 ) + 2 ] = player[1] - 16;
				}
				if ( pshot[( i * 10 ) + 4 ] == 3 )
				{
					pshot[( i * 10 ) + 1 ] = player[0] - 37;
					pshot[( i * 10 ) + 2 ] = player[1] - 43;
				}
				if ( pshot[( i * 10 ) + 4 ] == 4 )
				{
					pshot[( i * 10 ) + 1 ] = player[0] - 16;
					pshot[( i * 10 ) + 2 ] = player[1] - 43;
				}
			}


			BltRect(m_vTex[3], pshot[( i * 10 ) + 1 ] - d_x, 480 - pshot[( i * 10 ) + 2 ] - 64 - d_y , pshot[( i * 10 ) + 6 ] * 64, pshot[( i * 10 ) + 3 ] * 256, 64, 64 );

			pshot[( i * 10 ) + 5 ]++;
			if ( pshot[( i * 10 ) + 5 ] >= 4 )
			{
				pshot[( i * 10 ) + 5 ] = 0;
				pshot[( i * 10 ) + 6 ]++;
				if ( pshot[( i * 10 ) + 6 ] >= 4 )
				{
					pshot[( i * 10 ) + 6 ] = 0;
					pshot[( i * 10 ) + 0 ] = 0;
				}
			}
		}
	}
}

void CGpAct::p_shot_f_set( long x, long y , long type )
{
	long i;

	for ( i = 0; i < 40; ++i )
	{
		if ( pshotf[( i * 10 ) + 0 ] == 0 )
		{
			pshotf[( i * 10 ) + 0 ] = 1;
			pshotf[( i * 10 ) + 1 ] = x;
			pshotf[( i * 10 ) + 2 ] = y;
			pshotf[( i * 10 ) + 5 ] = 120 / 10;
			pshotf[( i * 10 ) + 6 ] = 70 / 10;
			pshotf[( i * 10 ) + 7 ] = type;
			pshotf[( i * 10 ) + 8 ] = 0;
			break;
		}
	}
}


void CGpAct::p_shot_f_disp()
{
	long i;

	for ( i = 0; i < 40; ++i )
	{
		if ( pshotf[( i * 10 ) + 0 ] == 1 )
		{
			pshotf[( i * 10 ) + 1 ] = pshotf[( i * 10 ) + 1 ] + pshotf[( i * 10 ) + 5 ];
			pshotf[( i * 10 ) + 2 ] = pshotf[( i * 10 ) + 2 ] + pshotf[( i * 10 ) + 6 ];


			//(E) 2010-07-14 Editor: AFEW
			int tx = ( ( ( pshotf[( i * 10 ) + 7 ] / 100 ) - 1 ) * 128 );
			int ty = 32 * ( pshotf[( i * 10 ) + 7 ] % 100 );

			if(512<=ty)
			{
				tx += 384;
				ty  = ty - (512 - 64);
			}

			BltRect(m_vTex[40]  ,
			         pshotf[( i * 10 ) + 1 ] - 16,
			         pshotf[( i * 10 ) + 2 ] - 16,
			         tx, ty, 32,32);

			pshotf[( i * 10 ) + 8 ]++;

			if ( pshotf[( i * 10 ) + 8 ] >= 10 )
			{
				pshotf[( i * 10 ) + 0 ] = 0;
			}
		}
	}
}



void CGpAct::p_shot_f2_set( long x, long y, long muki )
{
	long k;
	long rg;
	int i=0;

	if(0 == muki)
	{
		for( i = 0; i < 20; ++i)
		{
			if ( pshotf2[i].bAv != 0 )
				continue;

			rg = ( ( rand() % 360 ) );
			k = ( rand() % 5 ) + 1;


			pshotf2[i].vcX = funcSin( rg ) * k;	/* Velocity x */
			pshotf2[i].vcY = funcCos( rg ) * k;	/* Velocity y */
			pshotf2[i].bAv = 1;					/* Alive */
			pshotf2[i].IgX = 0 ;				/* Image Source Index X */
			pshotf2[i].psX = x  << 16 ;			/* Position X */
			pshotf2[i].psY = y  << 16 ;			/* Position Y */
			pshotf2[i].IgC = 0 ;				/* Image Source Current Index */
			pshotf2[i].IgM = 10 ; 				/* Image Source Current Index */
			pshotf2[i].nTp = muki ; 			/* type */

			pshotf2[i].nAp = 255 ; 				/* Alpha */
		}
		
		return;
	}

	else
	{
		// Search Dead Particle
		for( i = 0; i < PARTICLE; ++i)
		{
			if ( 0 == pshotf2[i].bAv)
				break;
		}

		// No Dead Particle
		if(i == PARTICLE)
			return;


		rg = ( ( rand() % 360 ) );
		k = ( rand() % 5 ) + 1;


		pshotf2[i].vcX = funcSin( rg ) * k;	/* Velocity x */
		pshotf2[i].vcY = funcCos( rg ) * k;	/* Velocity y */
		pshotf2[i].bAv = 1;					/* Alive */
		pshotf2[i].IgX = 0 ;				/* Image Source Index X */
		pshotf2[i].psX = x  << 16 ;			/* Position X */
		pshotf2[i].psY = y  << 16 ;			/* Position Y */
		pshotf2[i].IgC = 0 ;				/* Image Source Current Index */
		pshotf2[i].IgM = 10 ; 				/* Image Source Current Index */
		pshotf2[i].nTp = muki ; 			/* type */

		pshotf2[i].nAp = 255 ; 				/* Alpha */
	}
}


void CGpAct::p_shot_f2_disp()
{
	long ii;

	int nStar=0;

	int	dx=0, dy=0, sx=0, sy=0, w=32, h=32;

	DGXCOLOR	dCol (1,1,1,1);
	DWORD		d;

	for ( ii = 0; ii < PARTICLE; ii++ )
	{
		if( pshotf2[ii].bAv != 1 )
			continue;


		nStar	= pshotf2[ii].nTp;
		dCol.a	= pshotf2[ii].nAp/255.5f;
		d = dCol;


		// Final Effect
		if(nStar)
		{
			dx = ( pshotf2[ii].psX >> 16 );
			dy = ( pshotf2[ii].psY >> 16 ) - 32;
			sx = pshotf2[ii].IgX * 32;
			sy = 128 + ( ( pshotf2[ii].nTp - 2 ) * 32 );
		}
		// Effect Stars
		else
		{
			dx = ( pshotf2[ii].psX >> 16 ) - d_x;
			dy = ( 0 - ( pshotf2[ii].psY >> 16 ) ) + MapInfo[3] - 32 - d_y;
			sx = pshotf2[ii].IgX * 32;
			sy = 32;
		}


		BltRect(m_vTex[5], dx, dy, sx, sy, w, h, d);


		pshotf2[ii].psX += pshotf2[ii].vcX;		/* Update Position X */
		pshotf2[ii].psY += pshotf2[ii].vcY;		/* Update Position Y */
		pshotf2[ii].IgC++ ;							/* Update Current Image Index */

		pshotf2[ii].nAp -=4;						/* Update Alpha*/

		if(pshotf2[ii].nAp<0)
		{
			pshotf2[ii].nAp = 0;
			pshotf2[ii].bAv = 0;
		}
			

		if ( pshotf2[ii].IgC >= pshotf2[ii].IgM )
		{
			pshotf2[ii].IgC  = 0;
			pshotf2[ii].IgX += 1;						/* Increase Index */
			
			if ( pshotf2[ii].IgX >= 2 )
			{
				pshotf2[ii].bAv = 0;				/* 存在無し */
			}
		}
	}

}












void CGpAct::item_set( long type, long x, long y, long iti, long g_num )
{
	long i;
	long bx;
	long by;

	i = 0;
	bx = 0;
	by = 0;

	by = type / 100;

	if ( by == 5 )
	{
		//スイッ?の?画順は前
		for ( i = 0; i < item_data[1]; ++i )
		{
			if ( item[( i * item_data[2] ) + 0 ] == 0 )
			{
				item[( i * item_data[2] ) + 0 ] = 1;
				item[( i * item_data[2] ) + 1 ] = x;
				item[( i * item_data[2] ) + 2 ] = y;
				item[( i * item_data[2] ) + 3 ] = type;
				item[( i * item_data[2] ) + 4 ] = 0;	// 支?からの相対位置X
				item[( i * item_data[2] ) + 5 ] = 0;	// 支?からの相対位置Y
				item[( i * item_data[2] ) + 6 ] = 0;	/* 移動カウン? */
				item[( i * item_data[2] ) + 7 ] = -1;	/* 支?の?イン? */
				item[( i * item_data[2] ) + 8 ] = 0;	/* 移動量X */
				item[( i * item_data[2] ) + 9 ] = 0;	/* 移動量Y */
				item[( i * item_data[2] ) + 10 ] = -1;	/* 敵の?イン? */


				break;
			}
		}
	}
	else
	{
		for ( i = ( item_data[1] - 1 ); i > 0; i-- )
		{
			if ( item[( i * item_data[2] ) + 0 ] == 0 )
			{
				item[( i * item_data[2] ) + 0 ] = 1;
				item[( i * item_data[2] ) + 1 ] = x;
				item[( i * item_data[2] ) + 2 ] = y;
				item[( i * item_data[2] ) + 3 ] = type;
				item[( i * item_data[2] ) + 4 ] = 0;	// 支?からの相対位置X
				item[( i * item_data[2] ) + 5 ] = 0;	// 支?からの相対位置Y
				item[( i * item_data[2] ) + 6 ] = 0;	/* 移動カウン? */
				item[( i * item_data[2] ) + 7 ] = -1;	/* 支?の?イン? */
				item[( i * item_data[2] ) + 8 ] = 0;	/* 移動量X */
				item[( i * item_data[2] ) + 9 ] = 0;	/* 移動量Y */
				item[( i * item_data[2] ) + 10 ] = -1;	/* 敵の?イン? */


				break;
			}
		}
	}

}


long CGpAct::item_sonzai( long map1, long map2 )
{
	long i;
	long hr;

	hr = 1;
	for ( i = 0; i < 100; ++i )
	{
		if ( item_wk[0 + ( i * 5 )] == 1 )
		{
			if ( ( item_wk[1 + ( i * 5 )] == map1 )
			  && ( item_wk[2 + ( i * 5 )] == map2 )
			  && ( item_wk[3 + ( i * 5 )] == stage ) )
			{
				hr = 0;
				break;
			}
		}
	}

	return( hr );
}


void CGpAct::item_disp()
{
	long i;
	long k;
	long bx;
	long by;
	long k_f;
	long wbx;
	long disp_x_j;
	long disp_y_j;
	long ii;
	long bx2;
	long by2;

	ii = 0;
	bx2 = 0;
	by2 = 0;
	wbx = 0;
	k_f = 0;
	disp_x_j = 0;
	disp_y_j = 0;

	for ( i = 0; i < item_data[1]; ++i )
	{
		if ( item[( i * item_data[2] ) + 0 ] == 1 )
		{
			bx = item[3 + ( i * item_data[2] )] % 100 ;
			by = item[3 + ( i * item_data[2] )] / 100 ;

			disp_x_j = item[1 + ( i * item_data[2] )];
			disp_y_j = ( 0 - item[2 + ( i * item_data[2] )] ) + MapInfo[3];
			if ( ( ( ( d_x - item_data[0] ) <= ( disp_x_j ) )
			  && ( ( d_y - item_data[0] ) <= ( disp_y_j  ) )
			  && ( ( d_x + 320 + item_data[0] ) >= ( disp_x_j ) )
			  && ( ( d_y + 240 + item_data[0] ) >= ( disp_y_j ) ) )
			  || ( bak_alldrow == 1 )	 					/* 背景の?画をクリップするか */
			   )
			{

				int tx = item_data[0] * bx;
				int ty = by * item_data[0];

				tx -= 32;
				ty -= 32;


				BltRect(m_vTex[12]
						, item[1 + ( i * item_data[2] )] - d_x
						, ( 0 - item[2 + ( i * item_data[2] )] ) + MapInfo[3] - item_data[0] - d_y
						, tx
						, ty
						, item_data[0]
						, item_data[0]
						);

			}

			/* プレイヤ?との当たり判定 */
			if ( ( ( (item[1 + ( i * item_data[2] )] + 0 ) <= (player[0] + char_size[3] ) )	/* 自?とのあたり判定 */
				&& ( (player[0] + char_size[2] ) < (item[1 + ( i * item_data[2] )] + item_data[0] - 0 ) )
				&& ( (item[2 + ( i * item_data[2] )]  + 0 ) < (player[1] + ( char_size[1] - 10 ) ) )
				&& ( (player[1] + 5 ) < ( item[2 + ( i * item_data[2] )] + item_data[0] - 0 ) ) )
				&& ( m_nSn == 1 ) )
			{
				k_f = 1;
				if (
				     ( ( by == 10 ) && ( bx == 7 ) )
				   )
				{
					//押せるブロック
					//キャラク??が地面にいる
					if ( player[33] > 0 )
					{
						if ( ( player[14] == 10 ) && ( item[( i * item_data[2] ) + 4 ] == 10 ) )
						{
							/* 壁じゃなかったら */
							if (
								   ( ( ( map1_item_j_Isitem( item[1 + ( i * item_data[2] )] + item_data[0] + player[33], item[2 + ( i * item_data[2] )] + 16, i ) >= 100 )
								    && ( map1_item_j_Isitem( item[1 + ( i * item_data[2] )] + item_data[0] + player[33], item[2 + ( i * item_data[2] )] + 16, i ) <= 119 ) )
								  || ( ( map1_item_j_Isitem( item[1 + ( i * item_data[2] )] + item_data[0] + player[33], item[2 + ( i * item_data[2] )] + 16, i ) >= 200 )
								    && ( map1_item_j_Isitem( item[1 + ( i * item_data[2] )] + item_data[0] + player[33], item[2 + ( i * item_data[2] )] + 16, i ) <= 219 ) ) )
							   )
							{
								player[0] = item[1 + ( i * item_data[2] )] - ( char_size[3] );
								player[29] = 0;
							}
							else
							{
								if ( item[8 + ( i * item_data[2] )] >= 0 )
								{
									item[( i * item_data[2] ) + 1 ] = item[( i * item_data[2] ) + 1 ] + player[33] ;
									player[29] = 0;
								}
							}
						}
						else
						{
							player[0] = item[1 + ( i * item_data[2] )] - ( char_size[3] );
							player[29] = 0;
						}
					}
					else if ( player[33] < 0 )
					{
						/* 壁じゃなかったら */
						if ( ( player[14] == 10 ) && ( item[( i * item_data[2] ) + 4 ] == 10 ) )
						{
							if (
								   ( ( ( map1_item_j_Isitem( item[1 + ( i * item_data[2] )] + player[33] , item[2 + ( i * item_data[2] )] + 16, i ) >= 100 )
								    && ( map1_item_j_Isitem( item[1 + ( i * item_data[2] )] + player[33] , item[2 + ( i * item_data[2] )] + 16, i ) <= 119 ) )
								  || ( ( map1_item_j_Isitem( item[1 + ( i * item_data[2] )] + player[33] , item[2 + ( i * item_data[2] )] + 16, i ) >= 200 )
								    && ( map1_item_j_Isitem( item[1 + ( i * item_data[2] )] + player[33] , item[2 + ( i * item_data[2] )] + 16, i ) <= 219 ) ) )
							   )
							{
								player[0] = item[1 + ( i * item_data[2] )] + item_data[0] - char_size[2];
								player[29] = 0;
							}
							else
							{
								if ( item[8 + ( i * item_data[2] )] >= 0 )
								{
									item[( i * item_data[2] ) + 1 ] = item[( i * item_data[2] ) + 1 ] + player[33] ;
									player[29] = 0;
								}
							}
						}
						else
						{
							player[0] = item[1 + ( i * item_data[2] )] + item_data[0] - char_size[2];
							player[29] = 0;
						}
					}
				}

			}
			if ( ( ( (item[1 + ( i * item_data[2] )] + 10 ) <= (player[0] + char_size[3] ) )	/* 自?とのあたり判定 */
				&& ( (player[0] + char_size[2] ) < (item[1 + ( i * item_data[2] )] + item_data[0] - 10 ) )
				&& ( (item[2 + ( i * item_data[2] )]  + 10 ) < (player[1] + ( char_size[1] - 10 ) ) )
				&& ( (player[1] + 5 ) < ( item[2 + ( i * item_data[2] )] + item_data[0] - 10 ) ) )
				&& ( m_nSn == 1 ) )
			{

				if ( one_event == 0 )
				{
					one_event = 1;
					if (
					     ( ( by == 10 ) && ( bx == 1 ) )
					  || ( ( by == 10 ) && ( bx == 2 ) )
					   )
					{
						//Rotation Setting
						DGX_SoundPlay( m_pSndSe[EN_SE_PAWA] );

						m_nSn = 5;
						player[20] = 0;
						player[21] = 0;
						player[22] = 0;

						player[10] = 0;
						player[11] = 0;
						player[4] = 0;
						player[5] = 3;
						player[2] = 2;		// つかみ


						player[22] = 10;
						player[20] = player[21];
						//乗っているアイテ?によって回?方向を決定
						if ( ( by == 10 ) && ( bx == 1 ) )
						{
							player[21] = player[21] - 90;
						}
						if ( ( by == 10 ) && ( bx == 2 ) )
						{
							player[21] = player[21] + 90;
						}

						if ( player[21] < 0 )
						{
							player[21] = player[21] + 360;
						}
						if ( player[21] >= 360 )
						{
							player[21] = player[21] - 360;
						}
						player[9] = 1;
					}
				}
				if ( ( by == 10 ) && ( bx == 3 ) )
				{
					//上バネ
					DGX_SoundPlay( m_pSndSe[EN_SE_JUMP] );
					/* アイテ?に乗っていない場合はそこがリトライ位置 */
					if ( player[2] != 31 )
					{
						player[10] = 0;
						player[11] = 0;
						player[2] = 21;	/* 空中 */
					}
					player[14] = 7;
					player[13] = 0;
					player[25] = 1;
					jmp_st();
				}
				if (
				     ( ( by == 10 ) && ( bx == 4 ) )
				  || ( ( by == 10 ) && ( bx == 6 ) )
				   )
				{
					//横バネ
					DGX_SoundPlay( m_pSndSe[EN_SE_JUMP] );


					if ( ( by == 10 ) && ( bx == 4 ) )
					{
						player[29] = 20;	// 横バネふき飛び力
					}
					else
					{
						player[29] = -20;	// 横バネふき飛び力
					}
				}
			}

			if (
			     ( m_nSn == 1 )
			  || ( m_nSn == 6 )
			   )
			{
				switch ( by )
				{
				case 2:	// 上方向
				case 3:
				case 4:
					if ( item[( i * item_data[2] ) + 7 ] >= 0 )	// 支?が存在する
					{
						if ( item[6 + ( i * item_data[2] )] > 0 )
						{
							/* プレイヤ?との当たり判定 */
							if ( ( ( (item[1 + ( i * item_data[2] )] + item[( i * item_data[2] ) + 8 ] ) <= (player[0] + char_size[3] ) )	/* 自?とのあたり判定 */
								&& ( (player[0] + char_size[2] ) < (item[1 + ( i * item_data[2] )] + item_data[0] + item[( i * item_data[2] ) + 8 ] ) )
								&& ( (item[2 + ( i * item_data[2] )]  + item[( i * item_data[2] ) + 9 ] ) < (player[1] + ( char_size[1] ) ) )
								&& ( (player[1] ) < ( item[2 + ( i * item_data[2] )] + item_data[0] + item[( i * item_data[2] ) + 9 ] ) ) )
								&& ( by == 3 )
							   )
							{
							}
							else
							{
								item[( i * item_data[2] ) + 1 ] = item[( i * item_data[2] ) + 1 ] + item[( i * item_data[2] ) + 8 ] ;
								item[( i * item_data[2] ) + 2 ] = item[( i * item_data[2] ) + 2 ] + item[( i * item_data[2] ) + 9 ] ;
								item[( i * item_data[2] ) + 6 ]--;
							}

							if ( item[6 + ( i * item_data[2] )] == 1 )	// 移動フレ??数が停?の場合
							{
								k = item[7 + ( i * item_data[2] )];	// 支?の取得
								item[( i * item_data[2] ) + 1 ] = ( item[( k * item_data[2] ) + 1 ] + item[4 + ( i * item_data[2] )] ) ;
								item[( i * item_data[2] ) + 2 ] = ( item[( k * item_data[2] ) + 2 ] + item[5 + ( i * item_data[2] )] ) ;
								item[( i * item_data[2] ) + 6 ] = 0;
							}
							if ( item[( i * item_data[2] ) + 10 ] >= 0 )	// 敵の?イン?が存在する
							{
								k = item[10 + ( i * item_data[2] )];	// 支?の取得
								enemy[1 +( k * enm_data[2] )] = item[1 + ( i * item_data[2] )];
								enemy[2 +( k * enm_data[2] )] = item[2 + ( i * item_data[2] )];
							}
						}
					}
					else
					{
						if ( item[( i * item_data[2] ) + 7 ] == -1 )		// 初回検索
						{
							//支?を検索
							item[( i * item_data[2] ) + 7 ] = -2;	//無し
							for ( ii = 0; ii < item_data[1]; ii++ )
							{
								if ( item[( ii * item_data[2] ) + 0 ] != 0 )
								{
									bx2 = item[( ii * item_data[2] ) + 3 ] % 100;
									by2 = item[( ii * item_data[2] ) + 3 ] / 100;
									switch( by )
									{
									case 2:
									case 3:
									case 4:
										if ( ( by2 == 1 ) && ( bx2 == bx ) )
										{
											// 支?からの相対位置を保存
											item[( i * item_data[2] ) + 4 ] = item[( i * item_data[2] ) + 1 ] - item[( ii * item_data[2] ) + 1 ];	/* 動作用バッフ? */
											item[( i * item_data[2] ) + 5 ] = item[( i * item_data[2] ) + 2 ] - item[( ii * item_data[2] ) + 2 ];	/* 動作用バッフ? */
											item[( i * item_data[2] ) + 7 ] = ii;
										}
										break;
									default:
										break;
									}
									if ( item[( i * item_data[2] ) + 7 ] != -2 )
									{
										// 支?が見つかった
										break;
									}
								}
							}
						}
						if ( by == 4 )	// 敵移動アイテ?
						{
							if ( item[( i * item_data[2] ) + 10 ] == -1 )		// 初回検索
							{
								//支?を検索
								item[( i * item_data[2] ) + 10 ] = -2;	//無し
								for ( ii = 0; ii < enm_data[1]; ii++ )
								{
									if ( enemy[0 +( ii * enm_data[2] )] == 1 )
									{
										//同じ座標に敵がいる場合?イン?の取得
										if (
										     ( enemy[1 +( ii * enm_data[2] )] == item[( i * item_data[2] ) + 1 ] )
										  && ( enemy[2 +( ii * enm_data[2] )] == item[( i * item_data[2] ) + 2 ] )
										   )
										{
											item[( i * item_data[2] ) + 10 ] = ii;	/* 動作用バッフ? */
										}
									}
								}
							}
						}
					}
					break;
				case 10:
					if ( bx == 7 )
					{
						if ( GetSceneGameFlag1(128) == 0 )	//?ップビュ?ではない
						{
							//箱
							item_jmp( i );
						}
					}
					break;
				case 5:
					// スイッ?
					k = 0;
					if ( ( ( (item[1 + ( i * item_data[2] )] + 0 ) <= (player[0] + char_size[3] ) )	/* 自?とのあたり判定 */
						&& ( (player[0] + char_size[2] ) < (item[1 + ( i * item_data[2] )] + item_data[0] - 0 ) )
						&& ( (item[2 + ( i * item_data[2] )]  + 0 ) < (player[1] + ( char_size[1] - 10 ) ) )
						&& ( (player[1] + 5 ) < ( item[2 + ( i * item_data[2] )] + item_data[0] - 0 ) ) )
						&& ( m_nSn == 1 ) )
					{
						// スイッ?が入っている
						k = 1;
					}
					else
					{
						for ( ii = 0; ii < item_data[1]; ii++ )
						{
							if ( item[( ii * item_data[2] ) + 0 ] != 0 )
							{
								bx2 = item[( ii * item_data[2] ) + 3 ] % 100;
								by2 = item[( ii * item_data[2] ) + 3 ] / 100;
								if (
								     ( ( by2 == 10 ) && ( bx2 == 7 ) )
								  || ( by2 == 2 )
								  || ( by2 == 3 )
								  || ( by2 == 4 )
								   )
								{
									//箱を検索して当たり判定を行う
									if ( ( ( (item[1 + ( i  * item_data[2] )] ) < ( item[1 + ( ii * item_data[2] )] + item_data[0] ) )	/* 自?とのあたり判定 */
										&& ( (item[1 + ( ii * item_data[2] )] ) < ( item[1 + ( i  * item_data[2] )] + item_data[0] ) )
										&& ( (item[2 + ( i  * item_data[2] )] ) < ( item[2 + ( ii * item_data[2] )] + item_data[0] ) )
										&& ( (item[2 + ( ii * item_data[2] )] ) < ( item[2 + ( i  * item_data[2] )] + item_data[0] ) ) ) )
									{
										k = 1;
									}
								}
							}
						}
					}
					if ( k == 1 )
					{
						// スイッ?が入っている
						if ( item[4 + ( i * item_data[2] )] == 0 )
						{
							//前回が押されていなかった
							DGX_SoundPlay( m_pSndSe[EN_SE_SW] );
						}
						item[4 + ( i * item_data[2] )] = 1;
					}
					else
					{
						item[4 + ( i * item_data[2] )] = 0;
					}
					break;
				case 6:
				case 7:
					//スイッ?で消えるブロック
					//スイッ?が入っていない
					item[3 + ( i * item_data[2] )] = 600 + bx;
					for ( ii = 0; ii < item_data[1]; ii++ )
					{
						if ( item[( ii * item_data[2] ) + 0 ] != 0 )
						{
							bx2 = item[( ii * item_data[2] ) + 3 ] % 100;
							by2 = item[( ii * item_data[2] ) + 3 ] / 100;
							if ( ( by2 == 5 ) && ( bx2 == bx ) )
							{
								if ( item[( ii * item_data[2] ) + 4 ] != 0 )
								{
									//スイッ?が入っている
									item[3 + ( i * item_data[2] )] = 700 + bx;
								}
							}
						}
					}

					break;
				default:
					break;
				}
			}
		}
	}
	if ( ( k_f == 0 ) && ( m_nSn == 1 ) )
	{
		one_event = 0;
	}
}



/* アイテ?のＹ座標計算 */
void CGpAct::item_jmp( int i )
{
	int y1;
	int px1 ;
	int px2 ;
	int py ;
	int py2 ;
	int py3 ;

	test[1] = 0;
	px1 = ( item[( i * item_data[2] ) + 1 ] + 5 ) / 32;
	px2 = ( item[( i * item_data[2] ) + 1 ] + ( 32 - 5 ) ) / 32;
	py = ( MapInfo[1] - ( ( item[( i * item_data[2] ) + 2 ] + 28 ) / 32 ) );

	item[( i * item_data[2] ) + 5 ]++;
	if ( item[( i * item_data[2] ) + 5 ] >= 10 )
	{
		item[( i * item_data[2] ) + 5 ] = 0;
	}

	if ( item[( i * item_data[2] ) + 4 ] == 10 )
	{
		/* 地面判定 */
		if ( ( ( ( map1[ px1 + ( ( py ) * MapInfo[0] ) ] >= 100 ) && ( map1[ px1 + ( ( py ) * MapInfo[0] ) ] <= 299 ) )
		  || ( ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] >= 100 ) && ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] <= 299 ) )
		  || ( ( map1[ px1 + ( ( py ) * MapInfo[0] ) ] >= 600 ) && ( map1[ px1 + ( ( py ) * MapInfo[0] ) ] <= 619 ) )
		  || ( ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] >= 600 ) && ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] <= 619 ) ) )
		  && ( ( ( item[( i * item_data[2] ) + 2 ] ) % 32 ) == 0 ) )
		{
			return;
		}
		else
		{
			if ( item_up_Isitem( i ) != -1 )	/* アイテ?の上に乗っている */
			{
				item[( i * item_data[2] ) + 2 ] = item_up_Isitem( i );
				item[( i * item_data[2] ) + 4 ] = 10;
				return;
			}
			item[( i * item_data[2] ) + 4 ]  = -1;
			item[( i * item_data[2] ) + 5 ]  = 0;
		}
	}


	if ( item[( i * item_data[2] ) + 5 ] == 0 )
	{
		item[( i * item_data[2] ) + 4 ]  = item[( i * item_data[2] ) + 4 ]  - 3;
		if ( ( item[( i * item_data[2] ) + 4 ]  <= 2 ) && ( item[( i * item_data[2] ) + 4 ]  > -2 ) )
		{
			item[( i * item_data[2] ) + 4 ]  = -1;
		}
		if ( item[( i * item_data[2] ) + 4 ]  < -4 )
		{
			item[( i * item_data[2] ) + 4 ]  = -4;
		}
		/* 地面判定 */
	}

	/* 画面?で落ちるのを防? */
	if ( ( item[( i * item_data[2] ) + 1 ] < 0 ) || ( item[( i * item_data[2] ) + 1 ] > ( MapInfo[2] - 32 ) ) )
	{
		item[( i * item_data[2] ) + 4 ]  = 0;
	}
	/* 今回の位置 */
	y1 = ( ( 0 - item[( i * item_data[2] ) + 4 ]  ) * ( 0 - item[( i * item_data[2] ) + 4 ]  ) * ( 0 - item[( i * item_data[2] ) + 4 ]  ) );

	px1 = ( item[( i * item_data[2] ) + 1 ] + 16 ) / 32;
	px2 = ( item[( i * item_data[2] ) + 1 ] + 16 ) / 32;
	py = ( MapInfo[1] - ( ( item[( i * item_data[2] ) + 2 ] + 28 ) / 32 ) );
	py2 = ( MapInfo[1] - ( ( item[( i * item_data[2] ) + 2 ] + 49 + 48 ) / 32 ) );
	item[( i * item_data[2] ) + 2 ] = item[( i * item_data[2] ) + 2 ] - ( y1 / 20 );
	py3 = ( MapInfo[1] - ( ( item[( i * item_data[2] ) + 2 ] + 32 + 32 + 16 ) / 32 ) );

	if ( item[( i * item_data[2] ) + 2 ] > MapInfo[3] )
	{
		return;
	}

	if ( item[( i * item_data[2] ) + 4 ]  <= 0 ) 													/* 上り中は判定しない */
	{
		/* 地面判定 */
		if ( ( ( map1[ px1 + ( ( py ) * MapInfo[0] ) ] >= 100 ) && ( map1[ px1 + ( ( py ) * MapInfo[0] ) ] <= 299 ) )
		  || ( ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] >= 100 ) && ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] <= 299 ) )
		  || ( ( map1[ px1 + ( ( py ) * MapInfo[0] ) ] >= 600 ) && ( map1[ px1 + ( ( py ) * MapInfo[0] ) ] <= 619 ) )
		  || ( ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] >= 600 ) && ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] <= 619 ) ) )
		{
			item[( i * item_data[2] ) + 2 ] = ( ( MapInfo[1] - py ) * 32 );
			item[( i * item_data[2] ) + 4 ]  = 10;
		}
		else
		{
			if ( item_up_Isitem( i ) != -1 )	/* アイテ?の上に乗っている */
			{
				item[( i * item_data[2] ) + 2 ] = item_up_Isitem( i );
				item[( i * item_data[2] ) + 4 ] = 10;
				return;
			}
		}
	}
	else		/* 上昇中 */
	{
		/* 地面判定 */
		if ( ( ( map1[ px1 + ( ( py3 ) * MapInfo[0] ) ] >= 100 ) && ( map1[ px1 + ( ( py3 ) * MapInfo[0] ) ] <= 119 ) )
		  || ( ( map1[ px1 + ( ( py3 ) * MapInfo[0] ) ] >= 200 ) && ( map1[ px1 + ( ( py3 ) * MapInfo[0] ) ] <= 219 ) )
		  || ( ( map1[ px2 + ( ( py3 ) * MapInfo[0] ) ] >= 100 ) && ( map1[ px2 + ( ( py3 ) * MapInfo[0] ) ] <= 119 ) )
		  || ( ( map1[ px2 + ( ( py3 ) * MapInfo[0] ) ] >= 200 ) && ( map1[ px2 + ( ( py3 ) * MapInfo[0] ) ] <= 219 ) ) )
		{
			item[( i * item_data[2] ) + 4 ]  = -1;
		}
	}
	if ( item[( i * item_data[2] ) + 2 ] <= -14 )
	{
		item[( i * item_data[2] ) + 0 ] = 0;
	}

}


// アイテ?同士に線を
void CGpAct::item_line()
{
	int i;
	int by;
	int k;
	int harfsize;
	int x1;
	int y1;
	int x2;
	int y2;

	k = 0;
	i = 0;
	by = 0;
	harfsize = item_data[0] / 2;	// 半分

	//(E) 2010-07-10 Editor: AFEW
	glLineWidth(4);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);

	glEnableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	glColor4f(1.F, 1.F, 1.F, 1.F);


	for ( i = 0; i < item_data[1]; ++i )
	{
		if ( item[( i * item_data[2] ) + 0 ] == 1 )
		{
			by = item[( i * item_data[2] ) + 3 ] / 100;
			switch ( by )
			{
			case 2:	// 上方向
			case 3:
			case 4:
				if ( item[7 + ( i * item_data[2] )] >= 0 )
				{
					k = item[7 + ( i * item_data[2] )];	// 支?の取得

					x1 = ( ( item[1 + ( i * item_data[2] )] + harfsize ) - d_x );
					y1 = ( ( 0 - item[2 + ( i * item_data[2] )] ) + MapInfo[3] - item_data[0] - d_y + harfsize - 1 );
					x2 = ( ( item[1 + ( k * item_data[2] )] + harfsize ) - d_x );
					y2 = ( ( 0 - item[2 + ( k * item_data[2] )] ) + MapInfo[3] - item_data[0] - d_y + harfsize - 1 );

					drawGRPline( x1, y1, x2, y2, 0xFFFFFFFF );
				}

				break;
			}
		}
	}

	glLineWidth(1);
}



//アイテ?の落下時に使用
//進入不可アイテ?が足元にある場合は、座標を返す
long CGpAct::item_up_Isitem( long item_index )
{
	long i;
	long bx;
	long by;
	long px;
	long py;

	px = item[1 + ( item_index * item_data[2] )];
	py = item[2 + ( item_index * item_data[2] )];

	for ( i = 0; i < item_data[1]; ++i )
	{
//		if ( ( item[( i * item_data[2] ) + 0 ] == 1 ) && ( item_index != i ) )
		if ( ( item[( i * item_data[2] ) + 0 ] == 1 ) )
		{
			//自分は判定しない
			bx = item[3 + ( i * item_data[2] )] % 100 ;
			by = item[3 + ( i * item_data[2] )] / 100 ;

			if (
			     ( by == 2 )
			  || ( by == 3 )
			  || ( by == 6 )
			  || ( ( by == 10 ) && ( bx == 7 ) )
			   )
			{
				if ( ( ( (item[1 + ( i * item_data[2] )]  ) < ( px + item_data[0] - 5 ) )	/* 自?とのあたり判定 */
					&& ( (px + 5) < (item[1 + ( i * item_data[2] )] + item_data[0] ) )
					&& ( (item[2 + ( i * item_data[2] )] + 27 ) < (py + 10 ) )
					&& ( (py - 1) < ( item[2 + ( i * item_data[2] )] + item_data[0] ) ) ) )
				{
					return( item[2 + ( i * item_data[2] )] + 32 );
				}
			}
		}
	}
	if ( ( ( (player[0] + 10  ) < ( px + item_data[0] ) )	/* 自?とのあたり判定 */
		&& ( (px ) < (player[0] + 22 ) )
		&& ( (player[1] + 27 ) < (py + 10 ) )
		&& ( (py - 1) < ( player[1] + 32 ) ) ) )
	{
		return( player[1] + 32 );
	}

	return( -1 );
}

long CGpAct::item_up()
{
	long i;
	long bx;
	long by;

	for ( i = 0; i < item_data[1]; ++i )
	{
		if ( item[( i * item_data[2] ) + 0 ] == 1 )
		{
			bx = item[3 + ( i * item_data[2] )] % 100 ;
			by = item[3 + ( i * item_data[2] )] / 100 ;

			if (
			     ( by == 2 )
			  || ( by == 3 )
			  || ( by == 6 )
			  || ( ( by == 10 ) && ( bx == 7 ) )
			   )
			{
				if ( ( ( (item[1 + ( i * item_data[2] )]  ) < (player[0] + 22 ) )	/* 自?とのあたり判定 */
					&& ( (player[0] + 10 ) < (item[1 + ( i * item_data[2] )] + 32 ) )
					&& ( (item[2 + ( i * item_data[2] )] + 27 ) < (player[1] + 10 ) )
					&& ( (player[1] - 1 ) < ( item[2 + ( i * item_data[2] )] + 32 ) ) ) )
				{
					return( item[2 + ( i * item_data[2] )] + 32 );
				}
			}
		}
	}
	return( -1 );
}
long CGpAct::item_up2()
{
	long i;
	long bx;
	long by;

	for ( i = 0; i < item_data[1]; ++i )
	{
		if ( item[( i * item_data[2] ) + 0 ] == 1 )
		{
			bx = item[3 + ( i * item_data[2] )] % 100 ;
			by = item[3 + ( i * item_data[2] )] / 100 ;

			if (
			     ( by == 3 )
			  || ( by == 6 )
			  || ( ( by == 10 ) && ( bx == 7 ) )
			   )
			{
				if ( ( ( (item[1 + ( i * item_data[2] )]  ) < (player[0] + 22 ) )	/* 自?とのあたり判定 */
					&& ( (player[0] + 10 ) < (item[1 + ( i * item_data[2] )] + 32 ) )
					&& ( (item[2 + ( i * item_data[2] )] + 0 ) < (player[1] + 33 ) )
					&& ( (player[1] + 20 ) < ( item[2 + ( i * item_data[2] )] + 32 ) ) ) )
				{
					return( item[2 + ( i * item_data[2] )] - 32 );
				}
			}
		}
	}

	return( -1 );
}


/* アイテ?に重なって上が押された時のイベント */
long CGpAct::item_event()
{
	long i;
	long hr;
	long r_f;

	hr = 0;

	for ( i = 0; i < item_data[1]; ++i )
	{
		if ( item[( i * item_data[2] ) + 0 ] == 1 )
		{
			r_f = 0;

			/* プレイヤ?との当たり判定 */
			if ( ( ( (item[1 + ( i * item_data[2] )]  ) < (player[0] + 22 ) )	/* 自?とのあたり判定 */
				&& ( (player[0] + 10 ) < (item[1 + ( i * item_data[2] )] + 32 ) )
				&& ( (item[2 + ( i * item_data[2] )] ) < (player[1] + 32 ) )
				&& ( (player[1] + 5 ) < ( item[2 + ( i * item_data[2] )] + 32 ) ) )
				&& ( player[14] == 10 ) )
			{
				r_f = 1;
				player[18] = 0;	/* 着地モ?ションとほったらかしアニメ?ションの解除 */

			}

			if ( ( r_f == 1 ) && ( item[( i * item_data[2] ) + 7 ] == 0 ) )
			{
				if ( ( item[( i * 10 ) + 3 ] >= 100 ) && ( item[( i * 10 ) + 3 ] <= 220 ) ) /* 看板 */
				{
					hr = 1;
//					event_set( item[( i * 10 ) + 3 ] , i );
				}
				break;
			}

		}
	}
	return( hr );
}


//敵作成
/* ?ップフ?イルから生成する場合 */
void CGpAct::enm_set( long type, long x, long y )
{
	int i;
	int size;
	int syu;
	int j;


	for ( i = 0; i < enm_data[1]; ++i )
	{
		if ( enemy[0 + ( i * enm_data[2] )] == 0 )
		{
			for ( j = 0; j < enm_data[2] ; j++ )
			{
				enemy[j + ( i * enm_data[2] )] = 0;
			}


			enemy[0 + ( i * enm_data[2] )] = 1;
			enemy[1 + ( i * enm_data[2] )] = x;
			enemy[2 + ( i * enm_data[2] )] = y;
			size = type / 100;
			syu = type % 100;

			enemy[3 + ( i * enm_data[2] )] = size;


			enemy[4 + ( i * enm_data[2] )] = syu;
//			enemy[5 + ( i * enm_data[2] )] = e_hp( type ) ;
			enemy[5 + ( i * enm_data[2] )] = 1 ;
			enemy[6 + ( i * enm_data[2] )] = 0;				/* やられカウン? */
			enemy[7 + ( i * enm_data[2] )] = 0;				/* 位置補正 */
			enemy[8 + ( i * enm_data[2] )] = 0;				/* ?示パ??ン */
			enemy[9 + ( i * enm_data[2] )] = 0;				/* 向き */
			enemy[10+ ( i * enm_data[2] )] = 0;				/* ?示Ｙ */
			enemy[11+ ( i * enm_data[2] )] = type;			/* 種類 */
			enemy[12+ ( i * enm_data[2] )] = 0;				/* ジャンプフレ??カウン? */
			enemy[13+ ( i * enm_data[2] )] = 0;				/* ジャンプカウン? */
			enemy[14+ ( i * enm_data[2] )] = x;				/* 再配置情報X */
			enemy[15+ ( i * enm_data[2] )] = y;				/* 再配置情報Y */
			enemy[16+ ( i * enm_data[2] )] = 0;				/* 無敵時間 */
			enemy[17+ ( i * enm_data[2] )] = 0;	/* ?メ?ジ */
			enemy[18+ ( i * enm_data[2] )] = 1;				/* 再配置を行うか */
			enemy[19+ ( i * enm_data[2] )] = 0;/* Gold */
			enemy[20+ ( i * enm_data[2] )] = 0;				/* 動作用バッフ? */
			enemy[21+ ( i * enm_data[2] )] = 0;				/* 動作用バッフ? */
			enemy[22+ ( i * enm_data[2] )] = 0;				/* 動作用バッフ? */
			enemy[23+ ( i * enm_data[2] )] = 0;				/* 動作用バッフ? */
			enemy[24+ ( i * enm_data[2] )] = 0;				/* 動作用バッフ? */
			enemy[25+ ( i * enm_data[2] )] = 0;				/* 動作用バッフ? */
			enemy[26+ ( i * enm_data[2] )] = 0;				/* 動作用バッフ? */
			enemy[27+ ( i * enm_data[2] )] = 0;				/* 動作用バッフ? */
			enemy[28+ ( i * enm_data[2] )] = 0;				/* 移動量X */
			enemy[29+ ( i * enm_data[2] )] = 0;				/* 移動量Y */

			if ( size != 4 )
			{
				all_snack_count++;
			}

			break;
		}
	}
}


//敵作成
/* 敵から敵が生成される場合 */
void enm_set2( long type, long x, long y ,long muki )
{
	int i;
	int size;
	int syu;
	int j;

	for ( i = 0; i < enm_data[1]; ++i )
	{
		if ( enemy[0 + ( i * enm_data[2] )] == 0 )
		{
			for ( j = 0; j < enm_data[2] ; j++ )
			{
				enemy[j + ( i * enm_data[2] )] = 0;
			}


			enemy[0 + ( i * enm_data[2] )] = 1;
			enemy[1 + ( i * enm_data[2] )] = x;
			enemy[2 + ( i * enm_data[2] )] = y;
			size = type / 100;
			syu = type % 100;
			enemy[3 + ( i * enm_data[2] )] = size;

			enemy[4 + ( i * enm_data[2] )] = syu;
//			enemy[5 + ( i * enm_data[2] )] = e_hp( type ) ;
			enemy[5 + ( i * enm_data[2] )] = 1 ;
			enemy[6 + ( i * enm_data[2] )] = 0;				/* やられカウン? */
			enemy[7 + ( i * enm_data[2] )] = 0;				/* 位置補正 */
			enemy[8 + ( i * enm_data[2] )] = 0;				/* ?示パ??ン */
			enemy[9 + ( i * enm_data[2] )] = muki;			/* 向き */
			enemy[10+ ( i * enm_data[2] )] = 0;				/* ?示Ｙ */
			enemy[11+ ( i * enm_data[2] )] = type;			/* 種類 */
			enemy[12+ ( i * enm_data[2] )] = 0;				/* ジャンプフレ??カウン? */
			enemy[13+ ( i * enm_data[2] )] = 0;				/* ジャンプカウン? */
			enemy[14+ ( i * enm_data[2] )] = x;				/* 再配置情報X */
			enemy[15+ ( i * enm_data[2] )] = y;				/* 再配置情報Y */
			enemy[16+ ( i * enm_data[2] )] = 0;				/* 無敵時間 */
			enemy[17+ ( i * enm_data[2] )] = 0;	/* ?メ?ジ */
			enemy[18+ ( i * enm_data[2] )] = 0;				/* 再配置を行うか */
			enemy[19+ ( i * enm_data[2] )] = 0;/* Gold */
			enemy[20+ ( i * enm_data[2] )] = 0;				/* 動作用バッフ? */
			enemy[21+ ( i * enm_data[2] )] = 0;				/* 動作用バッフ? */
			enemy[22+ ( i * enm_data[2] )] = 0;				/* 動作用バッフ? */
			enemy[23+ ( i * enm_data[2] )] = 0;				/* 動作用バッフ? */
			enemy[24+ ( i * enm_data[2] )] = 0;				/* 動作用バッフ? */
			enemy[25+ ( i * enm_data[2] )] = 0;				/* 動作用バッフ? */
			enemy[26+ ( i * enm_data[2] )] = 0;				/* 動作用バッフ? */
			enemy[27+ ( i * enm_data[2] )] = 0;				/* 動作用バッフ? */
			enemy[28+ ( i * enm_data[2] )] = 0;				/* 動作用バッフ? */
			enemy[29+ ( i * enm_data[2] )] = 0;				/* 動作用バッフ? */

			break;
		}
	}
}



/* 敵のＨＰを設定（e_setで使われる） */
long e_hp( long type )
{
	long hr = 1;

	if ( ( type / 100 ) == 1 )	/* 32 */
		hr = enm1_parameter[ 10 * ( type - 100 ) + 0 ];

	if ( ( type / 100 ) == 2 )	/* 48 */
		hr = enm2_parameter[ 10 * ( type - 200 ) + 0 ];

	if ( ( type / 100 ) == 3 )	/* 64 */
		hr = enm3_parameter[ 10 * ( type - 300 ) + 0 ];

	if ( ( type / 100 ) == 4 )	/* 128 */
		hr = enm4_parameter[ 10 * ( type - 400 ) + 0 ];


	return hr;
}


void CGpAct::enm_disp()
{
	long i;
	long k;
	long size ;
	long size2;
	long akt_size2;
	long p_h;
	long all;
	long size_hosei_x;
	long size_hosei_y;
	long isclaer;
	long is_tukami;
	long disp_x_j;
	long disp_y_j;

	disp_x_j = 0;
	disp_y_j = 0;

	is_tukami = 0;
	isclaer = 0;
	size_hosei_x = 0;
	size_hosei_y = 0;
	p_h = 32;	/* プレイヤ?の当たり判定 */
	all = 1;
	size = 0;
	akt_size2 = 0;

	for ( i = 0; i < enm_data[1]; ++i )
	{
		if ( enemy[0 +( i * enm_data[2] )] == 1 )
		{
			if ( enemy[3 + ( i * enm_data[2] )] != 4 )	/* 4?ス */
			{
				isclaer = 1;
			}
			all = 0;
			/* 無敵時間が存在する場合はカウント */
			if ( enemy[16 + ( i * enm_data[2] )] > 0 )
			{
				enemy[16 + ( i * enm_data[2] )]--;
			}

			/* 敵のサイズ取得 */
			if ( enemy[3 + ( i * enm_data[2] )] == 1 )
			{
				size = 32;
			}
			if ( enemy[3 + ( i * enm_data[2] )] == 2 )
			{
				size = 32;
			}
			if ( enemy[3 + ( i * enm_data[2] )] == 3 )
			{
				size = 32;
			}
			if ( enemy[3 + ( i * enm_data[2] )] == 4 )	/* 4?ス */
			{
				size = 32;
			}
			if ( enemy[3 + ( i * enm_data[2] )] == 5 )	/* 5?ス */
			{
				size = 32;
			}
			if ( enemy[3 + ( i * enm_data[2] )] == 6 )	/* 6?ス */
			{
				size = 32;
			}

			size_hosei_x = 5;
			size_hosei_y = 10;

			/* 画面内の敵だけ?画する */
			disp_x_j = enemy[1 + ( i * enm_data[2] )];
			disp_y_j = ( 0 - enemy[2 + ( i * enm_data[2] )] ) + MapInfo[3];

			if ( ( ( ( d_x - size ) <= ( disp_x_j ) )
			  && ( ( d_y - size ) <= ( disp_y_j  ) )
			  && ( ( d_x + 320 + size ) >= ( disp_x_j ) )
			  && ( ( d_y + 240 + size ) >= ( disp_y_j ) ) )
			  || ( bak_alldrow == 1 )	 					/* 背景の?画をクリップするか */
			   )
			{

				if ( enemy[6 + ( i * enm_data[2] )] > 0 )	/* やられ */
				{
					if ( ( ( enemy[16 + ( i * enm_data[2] )] % 2 ) == 0 ) || ( m_nSn != 1 ) )
					{
						BltRect(m_vTex[39] + enemy[3 + ( i * enm_data[2] )],
							    enemy[1 + ( i * enm_data[2] )]  - d_x,
							    ( 0 - enemy[2 + ( i * enm_data[2] )] ) + MapInfo[3] - size  - d_y,
							    ( size * 8 ) + ( enemy[9 + ( i * enm_data[2])] *  size ),
							    size * ( enemy[4 + ( i * enm_data[2] )] + enemy[10+ ( i * enm_data[2] )] ),
							    size,
							    size );
					}
				}

				else
				{

					if ( ( ( enemy[16 + ( i * enm_data[2] )] % 2 ) == 0 ) || ( m_nSn != 1 ) )
					{
						if ( enemy[3 + ( i * enm_data[2] )] == 4 )	//隠しアイテ?
						{
							if ( snack_count == 1 )
							{
								//(E) 2010-07-14 Editor: AFEW
								int tx = ( size * enemy[8 + ( i * enm_data[2] )] ) + ( enemy[9 + ( i * enm_data[2] )] * ( size * 4 ) ) + ( ( enemy[3 + ( i * enm_data[2] )] - 1 ) * 128 );
								int ty = size * ( enemy[4 + ( i * enm_data[2] )] + enemy[10+ ( i * enm_data[2] )] );

								if(512<=ty)
								{
									tx += 384;
									ty  = ty - (512 - 64);
								}

								BltRect(m_vTex[40]  ,
									     enemy[1 + ( i * enm_data[2] )]  - d_x,
									     ( 0 - enemy[2 + ( i * enm_data[2] )] ) + MapInfo[3] - size  - d_y,
									     tx, ty, size, size );
							}
						}
						else
						{
							//(E) 2010-07-14 Editor: AFEW
							int tx = ( size * enemy[8 + ( i * enm_data[2] )] ) + ( enemy[9 + ( i * enm_data[2] )] * ( size * 4 ) ) + ( ( enemy[3 + ( i * enm_data[2] )] - 1 ) * 128 );
							int ty = size * ( enemy[4 + ( i * enm_data[2] )] + enemy[10+ ( i * enm_data[2] )] )	;

							if(512<=ty)
							{
								tx += 384;
								ty  = ty - (512 - 64);
							}

							BltRect(m_vTex[40]  ,
								     enemy[1 + ( i * enm_data[2] )]  - d_x,
								     ( 0 - enemy[2 + ( i * enm_data[2] )] ) + MapInfo[3] - size  - d_y,
								     tx, ty, size, size );
						}
					}
				}
			}

			/* 画面内の敵だけ?画する */
			if ( ( ( d_x - 320 - 64 ) <= ( disp_x_j ) )
			  && ( ( d_y - 240 - 64 ) <= ( disp_y_j  ) )
			  && ( ( d_x + 640 + 64 ) >= ( disp_x_j ) )
			  && ( ( d_y + 480 + 64 ) >= ( disp_y_j ) ) )
			{
				e_move( i );	/* 敵キャラ種類別動作 */
			}

			/* ?スは画面外へ移動しない */
#if FALSE
			if ( enemy[3 + ( i * enm_data[2] )] >= 4 )	/* 5?ス */
			{
				if ( enemy[i * enm_data[2] + 1] > ( MapInfo[2] - size ) )
				{
					enemy[i * enm_data[2] + 1] = ( MapInfo[2] - size );
				}
				if ( enemy[i * enm_data[2] + 1] < 1 )
				{
					enemy[i * enm_data[2] + 1] = 1;
				}
			}
#endif
			/* 画面外へ移動した場合は消去 */
			if ( ( enemy[1 + ( i * enm_data[2] )] >= ( MapInfo[2] + size ) )
			  || ( enemy[1 + ( i * enm_data[2] )] <= ( 0 - size ) )
			  || ( enemy[2 + ( i * enm_data[2] )] <= ( 0 - size ) )
			  || ( enemy[2 + ( i * enm_data[2] )] >= ( MapInfo[3] + size ) ) )
			{
			}

			/* プレイヤ?との当たり判定 */
			if ( ( ( (enemy[1 + i * enm_data[2]] + size_hosei_x ) < (player[0] + char_size[3] ) )	/* 自?とのあたり判定 */
				&& ( (player[0] + char_size[2] ) < (enemy[1 + i * enm_data[2]] + size - size_hosei_x ) )
				&& ( (enemy[2 + i * enm_data[2]] + size_hosei_y ) < (player[1] + p_h) )
				&& ( (player[1] + 5 ) < ( enemy[2 + i * enm_data[2]] + size - size_hosei_y - 10 ) ) )
				&& ( player[17] == 0 ) 					/* 無敵時間が無い */
				&& ( enemy[6 + i * enm_data[2]] == 0 ) )			/* 敵の無敵時間がない */
			{
				if ( GetSceneGameFlag1(128) == 0 )	//?ップビュ?ではない
				{
					if ( enemy[3 + ( i * enm_data[2] )] == 4 )
					{
						if ( snack_count == 1 )
						{
							enemy[0 + i * enm_data[2]] = 0;		/* 消去 */
							DGX_SoundPlay( m_pSndSe[EN_SE_L1] );
							p_shot_f2_set( ( enemy[1 + i * enm_data[2]] ) , ( enemy[2 + i * enm_data[2]] ), 0 );
							p_shot_f_set( 160 ,120, enemy[11 + i * enm_data[2]] );
							player[24] = 180;
							player[31] = 70; //カットイン
							player[32] = ( rand() % 3 ); //カットイン
							secretitemget = 1;						/* 隠しアイテ?の取得 */
						}
					}
					else
					{
						enemy[0 + i * enm_data[2]] = 0;		/* 消去 */
						DGX_SoundPlay( m_pSndSe[EN_SE_L1] );

						p_shot_f2_set( ( enemy[1 + i * enm_data[2]] ) , ( enemy[2 + i * enm_data[2]] ), 0 );
						p_shot_f_set( 160 ,120, enemy[11 + i * enm_data[2]] );
						player[31] = 70; //カットイン
						player[32] = ( rand() % 3 ); //カットイン
					}
				}
			}

			/* ?せない特別な敵（針等） */

//			if (
//			     ( ( enemy[11 + i * enm_data[2]] == 406 ) && ( ( enemy[8+ ( i * enm_data[2] )] == 1 ) || ( enemy[8+ ( i * enm_data[2] )] == 2 ) ) )		/* 6?ス */
//			   )
//			{
//			}
//			else
			{
				/* 敵とオブジェクトの当たり判定 */
				for ( k = 0; k < 40 ; k++ )
				{
					/* オブジェクトのサイズ */
					size2 = 32;
					/* プレイヤ?の弾との当たり判定 */
					if ( ( ( ( enemy[1 + i * enm_data[2]] + size_hosei_x ) < ( ( pmshot[5 + k * 20] >> 16 ) + size2 ) )
						&& ( ( ( pmshot[5 + k * 20] >> 16 ) + akt_size2 ) < ( enemy[1 + i * enm_data[2]] + size - size_hosei_x  ) )
						&& ( ( enemy[2 + i * enm_data[2]] + size_hosei_y ) < ( ( pmshot[6 + k * 20] >> 16 ) + size2 ) )
						&& ( ( ( pmshot[6 + k * 20] >> 16 ) + akt_size2 ) < ( enemy[2 + i * enm_data[2]] + size - size_hosei_y - 10  ) ) )
						&& ( pmshot[2 + k * 20] == 1 ) )
					{
						/* 無敵時間が存在しない */
						if ( enemy[16 + ( i * enm_data[2] )] == 0 )
						{
							/* 攻撃が効かない特別な敵 */
#if FALSE
							if (
							     ( ( enemy[11 + ( i * enm_data[2] )] == 114 ) && ( enemy[ 9 + ( i * enm_data[2] )] == 1 ) && ( pmshot[3 + k * 20] == 2 ) )	/* コサクン */
							  || ( ( enemy[11 + ( i * enm_data[2] )] == 114 ) && ( enemy[ 9 + ( i * enm_data[2] )] == 0 ) && ( pmshot[3 + k * 20] == 3 ) )	/* コサクン */
							  || ( ( enemy[11 + ( i * enm_data[2] )] == 114 ) && ( pmshot[3 + k * 20] == 1 ) )	/* コサクン */
							  || ( ( enemy[11 + ( i * enm_data[2] )] == 112 ) && ( enemy[8 + ( i * enm_data[2] )] == 0 ) )	/* ア?ン */
							  || ( ( enemy[11 + ( i * enm_data[2] )] == 112 ) && ( enemy[8 + ( i * enm_data[2] )] == 1 ) )	/* ア?ン */
							   )
							{
								pmshot[2 + k * 20] = 0;		/* 弾消去 */
								se_wav( 2 );
								/* 下攻撃の場合はジャンプ */
								if ( pmshot[3 + k * 20] == 1 )
								{
									/* はねる */
									player[10] = 0;			/* アニメ?ションフレ??カウン?のクリア */
									player[11] = 0;			/* アニメ?ションカウン?のクリア */
									player[2] = 21;			/* 空中状態 */

									player[14] = 5;			/* ジャンプ力の設定、これによって高さが変わる 1?9 */
									player[13] = 0;			/* ジャンプフレ??カウン?のクリア */
			//						player[25] = 1;			/* ??ンを押してジャンプしたフラグ */
								}
							}
							else
							{
								/* 攻撃ヒット効果の?示を配置 */
								p_shot_f_set( ( pmshot[5 + k * 20] >> 16 ) , ( pmshot[6 + k * 20] >> 16 ), 0 );

								/* 敵HPを減少 */
								enemy[5 + ( i * enm_data[2] )] = enemy[5 + ( i * enm_data[2] )] - 1;

								/* 向き設定 */
								if ( enemy[3 + ( i * enm_data[2] )] < 4 )	/* 4?スは変わらない */
								{
									if ( pmshot[10 + k * 20] == 1 )
									{
										enemy[9 + ( i * enm_data[2] )] = 0;
									}
									else
									{
										enemy[9 + ( i * enm_data[2] )] = 1;
									}
								}

//								pmshot[2 + k * 20] = 0;				/* 弾消去 */
								if ( enemy[5 + ( i * enm_data[2] )] <= 0 )		/* ?した */
								{

									/* ?した際のイベントを実行 */
									/* ?ス以外でも行う場合はここの判断文を追加 */
									if ( enemy[3 + ( i * enm_data[2] )] >= 4 )	/* 4?ス */
									{
										enemy[16 + ( i * enm_data[2] )] = 59;	/* 無敵時間の設定 */
//										boss_dead( enemy[1 + ( i * enm_data[2] )], enemy[2 + ( i * enm_data[2] )], i );
//										event_set_enm( enemy[11 + ( i * enm_data[2] )] , i );
#if FALSE
										for ( l = 0; l < enm_data[1]; l++ )
										{
											enemy[5 + ( l * enm_data[2] )] = 0;
											enemy[6 + ( l * enm_data[2] )] = 60;		/* 消去 */
											enemy[16 + ( l * enm_data[2] )] = 60;
										}
#endif
									}

									p_shot_f2_set( ( pmshot[5 + k * 20] >> 16 ) - 4, ( pmshot[6 + k * 20] >> 16 ) + 4, 0 );
									enemy[6 + ( i * enm_data[2] )] = 30;		/* ?メ?ジくらいモ?ション?示フレ??数 */
									enemy[16 + ( i * enm_data[2] )] = 60;	/* 無敵時間の設定 */
									se_wav( 5 );
								}
								else
								{
									/* ?してない */
									/* 無敵時間設定 */
									enemy[6 + ( i * enm_data[2] )] = 30;		/* のけぞり時間 */
									enemy[7 + ( i * enm_data[2] )] = 6;		/* 位置補正 */
									enemy[16 + ( i * enm_data[2] )] = 60;	/* 無敵時間 */
									se_wav( 4 );
									if ( enemy[3 + ( i * enm_data[2] )] >= 4 )	/* ?スのときはのけぞりがない */
									{
										enemy[6 + ( i * enm_data[2] )] = 0;		/* のけぞり時間 */
										enemy[7 + ( i * enm_data[2] )] = 0;		/* 位置補正 */
									}
								}
							}
#endif
						}
					}
				}
			}

			if ( enemy[7 + ( i * enm_data[2] )] > 0 )
			{
				enemy[7 + ( i * enm_data[2] )]--;					/* 移動補正 */
				/* 壁に埋まらないように判定 */
				if ( enemy[9 + ( i * enm_data[2] )] == 0 )
				{
					if ( ( ( map1_item_j( enemy[1 + ( i * enm_data[2] )] - 4 , enemy[2 + ( i * enm_data[2] )] + 2 ) >= 100 )
					    && ( map1_item_j( enemy[1 + ( i * enm_data[2] )] - 4 , enemy[2 + ( i * enm_data[2] )] + 2 ) <= 119 ) )
					  || ( ( map1_item_j( enemy[1 + ( i * enm_data[2] )] - 4 , enemy[2 + ( i * enm_data[2] )] + 2 ) >= 200 )
					    && ( map1_item_j( enemy[1 + ( i * enm_data[2] )] - 4 , enemy[2 + ( i * enm_data[2] )] + 2 ) <= 219 ) ) )
					{
					}
					else
					{
						enemy[1 + ( i * enm_data[2] )] = enemy[1 + ( i * enm_data[2] )] - ( enemy[7 + ( i * enm_data[2] )] * enemy[7 + ( i * enm_data[2] )] );
					}
				}
				else
				{
					if ( ( ( map1_item_j( enemy[1 + ( i * enm_data[2] )] + size + 4, enemy[2 + ( i * enm_data[2] )] + 2 ) >= 100 )
					    && ( map1_item_j( enemy[1 + ( i * enm_data[2] )] + size + 4, enemy[2 + ( i * enm_data[2] )] + 2 ) <= 119 ) )
					  || ( ( map1_item_j( enemy[1 + ( i * enm_data[2] )] + size + 4, enemy[2 + ( i * enm_data[2] )] + 2 ) >= 200 )
					    && ( map1_item_j( enemy[1 + ( i * enm_data[2] )] + size + 4, enemy[2 + ( i * enm_data[2] )] + 2 ) <= 219 ) ) )
					{
					}
					else
					{
						enemy[1 + ( i * enm_data[2] )] = enemy[1 + ( i * enm_data[2] )] + ( enemy[7 + ( i * enm_data[2] )] * enemy[7 + ( i * enm_data[2] )] );
					}
				}
			}

			/* ?メ?ジくらいモ?ション */
			if ( enemy[6 + ( i * enm_data[2] )] > 0 )
			{
				enemy[6 + ( i * enm_data[2] )]--;					/* 消えるまでカウン? */
				if ( enemy[6 + ( i * enm_data[2] )] == 0 )
				{
					if ( enemy[5 + ( i * enm_data[2] )] <= 0 )		/* HPが無い場合 */
					{
						if ( enemy[3 + ( i * enm_data[2] )] >= 4 )	/* ?ス */
						{
							se_wav( 18 );				/* ?スを?した効果音 */

						}
						else
						{
#if FALSE
							if ( Rand( 5 ) == 0 )	/* ライフ出現 */
							{
								se_wav( 7 );
								kane_set( enemy[1 + ( i * enm_data[2] )] + ( ( size / 2 ) - 16 ), enemy[2 + ( i * enm_data[2] )] , 0, enemy[19+ ( i * enm_data[2] )] );
							}
							else
							{
								se_wav( 7 );
								kane_set( enemy[1 + ( i * enm_data[2] )] + ( ( size / 2 ) - 16 ), enemy[2 + ( i * enm_data[2] )] , 1, enemy[19+ ( i * enm_data[2] )] );
							}
							/* 画面外の場合に再配置を行う */
							if ( enemy[18 + ( i * enm_data[2] )] == 1 )
							{
								set_enmreset_tbl( enemy[14 + ( i * enm_data[2] )], enemy[15 + ( i * enm_data[2] )], enemy[11 + ( i * enm_data[2] )] );
							}
#endif
						}
						enemy[0 + ( i * enm_data[2] )] = 0;		/* 消去 */

					}
				}
			}
		}
	}


	if ( ( isclaer == 0 ) )	/* ?スしてとってもクリア */
	{
		m_nSn = 2;
		demo[0] = 0;

		DGX_SoundStop(m_pSndBg);
	}
}


void CGpAct::e_move( long i )
{

	if ( enemy[6 + ( i * enm_data[2] )] > 0 )
	{
		return;
	}
	if ( enemy[5 + ( i * enm_data[2] )] <= 0 )	/* ?した */
	{
		return;
	}

	enemy[8 + ( i * enm_data[2] )] = map_rot_info;		/* アニメ?ションパ??ン */
	enemy[9 + ( i * enm_data[2] )] = 0;		/* アニメ?ションパ??ン */
	enemy[14 + ( i * enm_data[2] )] = 0;

}



/* 敵ショット生成 */

/* ショット移動 */
void CGpAct::e_shot_disp()
{
	long i;
	long p_h;
	long size ;

	p_h = 22;	/* プレイヤ?の当たり判定 */
	size = 0;

	/* 発生位置X */
	/* 発生位置Y */
	for ( i = 0; i < 20; ++i )
	{
		if ( mgc_e[i * 10 + 0] == 1 )					/* 存在している */
		{
			if ( mgc_e[i * 10 + 9] == 4010 ) 	/* １?ス */
			{
				size = 32;
				BltRect(m_vTex[50], ( mgc_e[i * 10 + 1] >> 16 ) - d_x , ( 0 - ( mgc_e[i * 10 + 2] >> 16 ) ) + 480 - 32 - d_y, mgc_e[i * 10 + 3] * 32, 0 , 32, 32 );
				mgc_e[i * 10 + 1] = mgc_e[i * 10 + 1] + mgc_e[i * 10 + 4];		/* X */
				mgc_e[i * 10 + 2] = mgc_e[i * 10 + 2] + mgc_e[i * 10 + 5];		/* Y */
				mgc_e[i * 10 + 3]++;					/* アニメ?ションカウン? */
				if ( mgc_e[i * 10 + 3] >= 4 )
				{
					mgc_e[i * 10 + 3] = 0;
				}
			}

			/* プレイヤ?との当たり判定 */
			if ( ( ( ( ( mgc_e[1 + i * 10] >> 16 ) ) < (player[0] + 22 ) )	/* 自?とのあたり判定 */
				&& ( (player[0] + 10 ) < ( ( mgc_e[1 + i * 10] >> 16 ) + size ) )
				&& ( ( ( mgc_e[2 + i * 10] >> 16 ) ) < (player[1] + p_h) )
				&& ( (player[1] + 5  ) < ( ( mgc_e[2 + i * 10] >> 16 ) + size ) ) )
				&& ( player[17] == 0 ) )
			{
				player[10] = 0;
				player[11] = 0;
				player[12] = 4;
				player[13] = 0;
				player[2] = 31;	/* ?メ?ジ */
				player[17] = 120;	/* 無敵時間 */
				player[8] = player[8] - 1;

				se_wav( 1 );
			}


			if ( ( ( mgc_e[i * 10 + 1] >> 16 ) >= 640 ) || ( ( mgc_e[i * 10 + 1] >> 16 ) <= 0 ) || ( ( mgc_e[i * 10 + 2] >> 16 ) <= -100 )|| ( ( mgc_e[i * 10 + 2] >> 16 ) >= 480 ))
			{
				mgc_e[i * 10 + 0] = 0;
			}
		}
	}
}


/* 敵用ジャンプ */
void enmjmp( long i )
{
	long y1;
	long px ;
	long px1 ;
	long px2 ;
	long py ;
	long py2 ;

	long size;
	long e10;

	if ( enemy[3 + ( i * 20 )] == 1 )
	{
		size = 16;
	}
	else if ( enemy[3 + ( i * 20 )] == 2 )
	{
		size = 24;
	}
	else
	{
		size = 16;
	}

	if ( enemy[13 + ( i * 20 )] == 10 )
	{
		/* 今回の位置 */
		px = ( enemy[1 + ( i * 20 )] + 32 ) / 32;
		px1 = ( enemy[1 + ( i * 20 )] + size ) / 32;
		px2 = ( enemy[1 + ( i * 20 )] + size ) / 32;
		py = ( 16 - ( ( enemy[2 + ( i * 20 )] + 28 ) / 32 ) );
		/* 100 ? 200は地面 */
		if ( ( !( ( map1[ px1 + ( ( py ) * 20 ) ] >= 100 ) && ( map1[ px1 + ( ( py ) * 20 ) ] <= 119 ) ) )
		  && ( !( ( map1[ px2 + ( ( py ) * 20 ) ] >= 100 ) && ( map1[ px2 + ( ( py ) * 20 ) ] <= 119 ) ) )
		  && ( !( ( map1[ px1 + ( ( py ) * 20 ) ] >= 200 ) && ( map1[ px1 + ( ( py ) * 20 ) ] <= 219 ) ) )
		  && ( !( ( map1[ px2 + ( ( py ) * 20 ) ] >= 200 ) && ( map1[ px2 + ( ( py ) * 20 ) ] <= 219 ) ) )
		  && ( !( ( map1[ px1 + ( ( py ) * 20 ) ] >= 600 ) && ( map1[ px1 + ( ( py ) * 20 ) ] <= 619 ) ) )
		  && ( !( ( map1[ px2 + ( ( py ) * 20 ) ] >= 600 ) && ( map1[ px2 + ( ( py ) * 20 ) ] <= 619 ) ) ) )
		{
			enemy[13+ ( i * 20 )] = 0;
			enemy[12+ ( i * 20 )] = 0;
		}
		else
		{
			return;
		}
	}

	enemy[12 + ( i * 20 )]++;
	if ( enemy[12+ ( i * 20 )] >= 10 )
	{
		enemy[12+ ( i * 20 )] = 0;

		enemy[13 + ( i * 20 )] = enemy[13 + ( i * 20 )] - 3;


		if ( ( enemy[13 + ( i * 20 )] <= 2 ) && ( enemy[13 + ( i * 20 )] > -2 ) )
		{
			enemy[13 + ( i * 20 )] = -3;
		}
		if ( enemy[13 + ( i * 20 )] < -8 )
		{
			enemy[13 + ( i * 20 )] = -8;
		}
		/* 地面判定 */
	}


	/* 画面?で落ちるのを防? */
	e10 = enemy[13 + ( i * 20 )];
	if (  enemy[1+ ( i * 20 )] > ( 630 - size - size ) )
	{
		if ( enemy[13+ ( i * 20 )] < 0 )	/* 落下 */
		{
			e10 = 0;
		}
	}


	/* 今回の位置 */
	y1 = ( ( 0 - e10 ) * ( 0 - e10 ) * ( 0 - e10 ) );
//	player[1] = player[1] - ( y1 / 30 );


	enemy[2 + ( i * 20 )] = enemy[2 + ( i * 20 )] - ( y1 / 25 );
	px1 = ( enemy[1 + ( i * 20 )] + size ) / 32;
	px2 = ( enemy[1 + ( i * 20 )] + size ) / 32;
	py = ( 16 - ( ( enemy[2 + ( i * 20 )] + 28 ) / 32 ) );
	py2 = ( 16 - ( ( enemy[2 + ( i * 20 )] + 49 + 48 ) / 32 ) );
//	py = ( 16 - ( ( player[1] ) / 32 ) );

	if ( enemy[2 + ( i * 20 )] > 480 )
	{
		return;
	}

	if ( enemy[13 + ( i * 20 )] <= 0 )													/* 上り中は判定しない */
	{
		/* 地面判定 */
		if ( ( ( map1[ px1 + ( ( py ) * 20 ) ] >= 100 ) && ( map1[ px1 + ( ( py ) * 20 ) ] <= 119 ) )
		  || ( ( map1[ px1 + ( ( py ) * 20 ) ] >= 200 ) && ( map1[ px1 + ( ( py ) * 20 ) ] <= 219 ) )
		  || ( ( map1[ px1 + ( ( py ) * 20 ) ] >= 600 ) && ( map1[ px1 + ( ( py ) * 20 ) ] <= 619 ) )
		  || ( ( map1[ px2 + ( ( py ) * 20 ) ] >= 600 ) && ( map1[ px2 + ( ( py ) * 20 ) ] <= 619 ) ) )
		{
			enemy[2 + ( i * 20 )] = ( ( 16 - py ) * 32 ) - 16;
			enemy[13 + ( i * 20 )] = 10;
		}
	}
	else		/* 上昇中 */
	{
		if ( enemy[1+ ( i * 20 )] < ( 630 - size - size ) )
		{
			px = ( enemy[1 + ( i * 20 )] + size ) / 32;
			py = ( 16 - ( ( enemy[2 + ( i * 20 )] - ( y1 / 25 ) + 16 + 48  ) / 32 ) );

			/* 地面判定 */
			if ( ( ( map1[ px + ( ( py ) * 20 ) ] >= 100 ) && ( map1[ px + ( ( py ) * 20 ) ] <= 119 ) )
			  || ( ( map1[ px + ( ( py ) * 20 ) ] >= 200 ) && ( map1[ px + ( ( py ) * 20 ) ] <= 219 ) ) )
			{
				enemy[13+ ( i * 20 )] = -3;
				enemy[12+ ( i * 20 )] = 0;
			}
		}

	}
	if ( enemy[2 + ( i * 20 )] <= -14 )
	{
		enemy[0 + ( i * 20 )] = 0;
	}

}


/* 移動後の座標の?スを返す */
long CGpAct::map1_item_j( long x, long y )
{
	int px ;
	int py ;
	int i;
	int hr;
	long bx;
	long by;

	px = ( x ) / 32;
	py = ( MapInfo[1] - 1 - ( ( y ) / 32 ) );

	if ( py <= 0 )
	{
		py = 0;
	}

	hr = map1[ px + ( ( py ) * MapInfo[0] ) ];

	/* アイテ?とのあたり判定 */
	for ( i = 0; i < item_data[1]; ++i )
	{
		if ( item[( i * item_data[2] ) + 0 ] == 1 )
		{
			bx = item[3 + ( i * item_data[2] )] % 100 ;
			by = item[3 + ( i * item_data[2] )] / 100 ;
			/* プレイヤ?との当たり判定 */
			if ( ( ( (item[1 + ( i * item_data[2] )]  ) < ( x ) )	/* 自?とのあたり判定 */
				&& ( ( x ) < (item[1 + ( i * item_data[2] )] + ( item_data[0] - 1 ) ) )
				&& ( (item[2 + ( i * item_data[2] )] ) < ( y ) )
				&& ( ( y ) < ( item[2 + ( i * item_data[2] )] + item_data[0] ) ) ) )
			{
				if (
//				     ( by == 2 )
				     ( by == 3 )
				  || ( by == 6 )
				  || ( ( by == 10 ) && ( bx == 7 ) )
				   )
				{
					hr = 101;
					break;
				}
			}
		}

	}

	return( hr );
}



long CGpAct::map1_item_j_Isitem( long x, long y, long item_index )
{
	int px ;
	int py ;
	int i;
	int hr;
	long bx;
	long by;

	px = ( x ) / 32;
	py = ( MapInfo[1] - 1 - ( ( y ) / 32 ) );

	if ( py <= 0 )
	{
		py = 0;
	}

	hr = map1[ px + ( ( py ) * MapInfo[0] ) ];

	/* アイテ?とのあたり判定 */
	for ( i = 0; i < item_data[1]; ++i )
	{
		if ( ( item[( i * item_data[2] ) + 0 ] == 1 ) && ( item_index != i ) )
		{
			bx = item[3 + ( i * item_data[2] )] % 100 ;
			by = item[3 + ( i * item_data[2] )] / 100 ;
			/* プレイヤ?との当たり判定 */
			if ( ( ( (item[1 + ( i * item_data[2] )]  ) < ( x ) )	/* 自?とのあたり判定 */
				&& ( ( x ) < (item[1 + ( i * item_data[2] )] + ( item_data[0] - 1 ) ) )
				&& ( (item[2 + ( i * item_data[2] )] ) < ( y ) )
				&& ( ( y ) < ( item[2 + ( i * item_data[2] )] + item_data[0] ) ) ) )
			{
				if (
//				     ( by == 2 )
				     ( by == 3 )
				  || ( by == 6 )
				  || ( ( by == 10 ) && ( bx == 7 ) )
				   )
				{
					hr = 101;
					break;
				}
			}
		}

	}

	return( hr );
}



void CGpAct::kane_set( long x, long y )
{
	long i;

	for ( i = 0; i < 20; ++i )
	{
		if ( kane[0 + ( i * 10 )] == 0 )
		{
			kane[0 + ( i * 10 )] = 1;
			kane[1 + ( i * 10 )] = x;
			kane[2 + ( i * 10 )] = y;
			kane[4 + ( i * 10 )] = 0;
			kane[3 + ( i * 10 )] = 0;
			kane[5 + ( i * 10 )] = 0;
			kane[6 + ( i * 10 )] = 6;
			kane[7 + ( i * 10 )] = 0;
			kane[8 + ( i * 10 )] = 0;
			kane[9 + ( i * 10 )] = 0;
			break;
		}
	}
}

void CGpAct::kane_disp(  )
{
	long i;

	for ( i = 0; i < 20; ++i )
	{
		if ( kane[0 + ( i * 10 )] == 1 )
		{
			kane[8 + ( i * 10 )]++;
			if ( kane[8 + ( i * 10 )] >= 10 )
			{
				kane[8 + ( i * 10 )] = 0;
				kane[7 + ( i * 10 )]++;
				if ( kane[7 + ( i * 10 )] >= 4 )
				{
					kane[7 + ( i * 10 )] = 0;
				}
			}
			if ( ( ( kane[9 + ( i * 10 )] % 2 ) == 0 ) || ( kane[9 + ( i * 10 )] < 240 ) )
			{
				BltRect(m_vTex[12] , kane[1 + ( i * 10 )] - d_x, ( 0 - kane[2 + ( i * 10 )] ) + 480 - 32 - d_y, 32 * 4 , 0, 32, 32 );
			}

			kane[9 + ( i * 10 )]++;
			if ( kane[9 + ( i * 10 )] >= 300 )
			{
				kane[0 + ( i * 10 )] = 0;
			}
			kane[5 + ( i * 10 )]++;
			if ( kane[5 + ( i * 10 )] >= 10 )
			{
				kane[5 + ( i * 10 )] = 0;
			}

			k_jmp( i );
			/* とった */
			if ( ( ( (kane[1 + ( i * 10 )]  ) < (player[0] + 10 ) )	/* 自?とのあたり判定 */
				&& ( (player[0] + 22 ) < (kane[1 + ( i * 10 )] + 32 ) )
				&& ( (kane[2 + ( i * 10 )] ) < (player[1] + 32 ) )
				&& ( (player[1] + 5 ) < ( kane[2 + ( i * 10 )] + 32 ) ) ) )
			{
				se_wav( 15 );
				player[8]++;
				if ( player[8] > save_data[6] )
				{
					player[8] = save_data[6];
				}
				kane[0 + ( i * 10 )] = 0;
			}
		}
	}
}


/* ジャンプＹ位置計算 */
void CGpAct::k_jmp( long i )
{
	long y1;
	long px1 ;
	long px2 ;
	long py ;
	long py2 ;
	long py3 ;

	if ( kane[6 + ( i * 10 )] == 10 )
	{
		return;
	}

	if ( kane[5 + ( i * 10 )] == 0 )
	{
		kane[6 + ( i * 10 )] = kane[6 + ( i * 10 )] - 3;
		if ( ( kane[6 + ( i * 10 )] <= 2 ) && ( kane[6 + ( i * 10 )] > -2 ) )
		{
			kane[6 + ( i * 10 )] = -3;
		}
		if ( kane[6 + ( i * 10 )] < -8 )
		{
			kane[6 + ( i * 10 )] = -8;
		}
		/* 地面判定 */
	}

	/* 画面?で落ちるのを防? */
	if ( ( kane[1 + ( i * 10 )] < 0 ) || ( kane[1 + ( i * 10 )] > 610 ) )
	{
		kane[6 + ( i * 10 )] = 0;
	}
	/* 今回の位置 */
	y1 = ( ( 0 - kane[6 + ( i * 10 )] ) * ( 0 - kane[6 + ( i * 10 )] ) * ( 0 - kane[6 + ( i * 10 )] ) );

	px1 = ( kane[1 + ( i * 10 )] + 16 ) / 32;
	px2 = ( kane[1 + ( i * 10 )] + 16 ) / 32;
	py = ( 16 - ( ( kane[2 + ( i * 10 )] + 28 ) / 32 ) );
	py2 = ( 16 - ( ( kane[2 + ( i * 10 )] + 49 + 48 ) / 32 ) );
	kane[2 + ( i * 10 )] = kane[2 + ( i * 10 )] - ( y1 / 25 );
	py3 = ( 16 - ( ( kane[2 + ( i * 10 )] + 32 + 32 + 16 ) / 32 ) );

	if ( kane[2 + ( i * 10 )] > 480 )
	{
		return;
	}

	if ( kane[6 + ( i * 10 )] <= 0 ) 													/* 上り中は判定しない */
	{
		/* 地面判定 */
		if ( ( ( map1[ px1 + ( ( py ) * 20 ) ] >= 100 ) && ( map1[ px1 + ( ( py ) * 20 ) ] <= 299 ) )
		  || ( ( map1[ px2 + ( ( py ) * 20 ) ] >= 100 ) && ( map1[ px2 + ( ( py ) * 20 ) ] <= 299 ) )
		  || ( ( map1[ px1 + ( ( py ) * 20 ) ] >= 600 ) && ( map1[ px1 + ( ( py ) * 20 ) ] <= 619 ) )
		  || ( ( map1[ px2 + ( ( py ) * 20 ) ] >= 600 ) && ( map1[ px2 + ( ( py ) * 20 ) ] <= 619 ) ) )
		{
			kane[2 + ( i * 10 )] = ( ( 16 - py ) * 32 ) - 16;
			kane[6 + ( i * 10 )] = 10;
		}
	}
	else		/* 上昇中 */
	{
		/* 地面判定 */
		if ( ( ( map1[ px1 + ( ( py3 ) * 20 ) ] >= 100 ) && ( map1[ px1 + ( ( py3 ) * 20 ) ] <= 119 ) )
		  || ( ( map1[ px1 + ( ( py3 ) * 20 ) ] >= 200 ) && ( map1[ px1 + ( ( py3 ) * 20 ) ] <= 219 ) )
		  || ( ( map1[ px2 + ( ( py3 ) * 20 ) ] >= 100 ) && ( map1[ px2 + ( ( py3 ) * 20 ) ] <= 119 ) )
		  || ( ( map1[ px2 + ( ( py3 ) * 20 ) ] >= 200 ) && ( map1[ px2 + ( ( py3 ) * 20 ) ] <= 219 ) ) )
		{
			kane[6 + ( i * 10 )] = -1;
			kane[5 + ( i * 10 )] = 0;
		}
	}
	if ( kane[2 + ( i * 10 )] <= -14 )
	{
		kane[0 + ( i * 10 )] = 0;
	}

}

void CGpAct::p_jump_f_set( long x, long y )
{
	long i;

	for ( i = 0; i < 10; ++i )
	{
		if ( pjumpf[( i * 10 ) + 0 ] == 0 )
		{
			pjumpf[( i * 10 ) + 0 ] = 1;
			pjumpf[( i * 10 ) + 1 ] = x;
			pjumpf[( i * 10 ) + 2 ] = y;
			pjumpf[( i * 10 ) + 5 ] = 0;
			pjumpf[( i * 10 ) + 6 ] = 0;
			break;
		}
	}
}


void CGpAct::p_jump_f_disp()
{
	long i;

	for ( i = 0; i < 10; ++i )
	{
		if ( pjumpf[( i * 10 ) + 0 ] == 1 )
		{
			// Dust
			BltRect(m_vTex[5], pjumpf[( i * 10 ) + 1 ] - d_x, ( 0 - pjumpf[( i * 10 ) + 2 ] ) + MapInfo[3] - 32 - d_y , 128 + ( pjumpf[( i * 10 ) + 6 ] * 32 ), 0, 32, 32 );

			pjumpf[( i * 10 ) + 5 ]++;
			if ( pjumpf[( i * 10 ) + 5 ] >= 5 )
			{
				pjumpf[( i * 10 ) + 5 ] = 0;
				pjumpf[( i * 10 ) + 6 ]++;
				if ( pjumpf[( i * 10 ) + 6 ] >= 4 )
				{
					pjumpf[( i * 10 ) + 6 ] = 0;
					pjumpf[( i * 10 ) + 0 ] = 0;
				}
			}
		}
	}
}


void CGpAct::screen_BackupPlane()
{
}


/* メニュ?の?示 */
void CGpAct::window_disp()
{
	BltRect(m_vTex[61], 100, 72 + ( 32 * demo[0] ), ( demo[1] / 10 ) * 16, 0 , 16, 16 );
	Blt(m_vTex[60], 128, 72 );

	demo[1]++;
	if ( demo[1] >= 40 )
	{
		demo[1] = 0;
	}
}



// Popup Window
void CGpAct::window_keys()
{
	if ( g_pApp->IsPushKey( DGXKEY_UP ) )
	{
		DGX_SoundPlay( m_pSndSe[EN_SE_SELECT] );

		demo[0]--;
		if ( demo[0] < 0 )
		{
			demo[0] = 2;
		}
	}
	else if ( g_pApp->IsPushKey( DGXKEY_DOWN ) )
	{
		DGX_SoundPlay( m_pSndSe[EN_SE_SELECT] );
		demo[0]++;
		if ( demo[0] > 2 )
		{
			demo[0] = 0;
		}
	}


	if ( g_pApp->IsPushOKKey() )	// Return, Restrt, Exit
	{
		if ( demo[0] == 0 )
		{
			if ( player[9] != 0 )				 // Return Game
			{
				m_nSn = 5;
			}
			else
			{
				m_nSn = 1;
			}
		}

		else if ( demo[0] == 1 )				// Restart
		{
			SetSceneGameFlag1(71, 1);
			m_nSn = 10;
		}

		else if ( demo[0] == 2 )				// Exit
		{
			if ( GetSceneGameFlag1(129) != 0 )
			{
				SetSceneState(EN_SN_STAGE);
				Destroy();
			}
			else
			{
				SetSceneState(EN_SN_TITLE);
			}

			m_nSn = 10;
			m_bExit = 0;
			
		}
	}


	// FX: Cancel
	if ( g_pApp->IsPushCancelKey() )
	{
		if ( player[9] != 0 ) //回?中
		{
			m_nSn = 5;
		}
		else
		{
			m_nSn = 1;
		}
	}

}


/* ?ップビュ?でのキ??作 */
void CGpAct::mapview_keys()
{
	if ( g_pApp->IsPressKey( DGXKEY_UP ) )	//上?
	{
		player[1] = player[1] + 2;
	}
	if ( g_pApp->IsPressKey( DGXKEY_DOWN ) )	//下?
	{
		player[1] = player[1] - 2;
	}
	if ( g_pApp->IsPressKey( DGXKEY_LEFT ) )	//左?
	{
		player[0] = player[0] - 2;
	}
	if ( g_pApp->IsPressKey( DGXKEY_RIGHT ) )	//右?
	{
		player[0] = player[0] + 2;
	}

	if ( player[0] < 0 )	/* 画面左?判定 */
	{
		player[0] = 0;
	}
	if ( player[0] > ( MapInfo[2] - char_size[0] ) )	/* 画面右?判定 */
	{
		player[0] =  MapInfo[2] - char_size[0];
	}
	if ( player[1] <= 0 )	/* 画面下 */
	{
		player[1] = 0;
	}
	if ( player[1] >= ( MapInfo[3] - char_size[1] ) )	/* 画面上 */
	{
		player[1] = ( MapInfo[3] - char_size[1] );
	}


	if ( g_pApp->IsPushOKKey() || g_pApp->IsPushCancelKey() )		// FB, FX
	{
		SetSceneState(EN_SN_TITLE);
		m_nSn = 10;
		m_bExit =0;
	}
}


/* 絶対値を返す */
long CGpAct::labs( long para )
{
	long hr;

	hr = para;

	if ( para < 0 )
	{
		hr = para * -1;
	}
	return( hr );
}

/* 魔?生成 */
void CGpAct::p_mgc_set( long muki , long p3 )
{
	long i;
	long k;
	long ii;
	long rg;
	long max;

	rg = 0;

	if ( muki == 0 )
	{
		rg = ( 0 );
	}
	else if ( muki == 1 )
	{
		rg = ( 45 );
	}
	else if ( muki == 2 )
	{
		rg = ( 90 );
	}
	else if ( muki == 3 )
	{
		rg = ( 135 );
	}
	else if ( muki == 4 )
	{
		rg = ( 180 );
	}

	if ( p3 == 1 )
	{
		rg = rg * -1;
	}

	/* 発生位置X */
	/* 発生位置Y */

	max = 1;
	for ( i = 0; i < max; ++i )
	{

		k = 5;

		for ( ii = 0; ii < 40; ii++ )
		{
			if ( pmshot[ii * 20 + 2] == 0 )
			{
				pmshot[ii * 20 + 0] = funcSin( rg ) * k;			/* 弾速x */
				pmshot[ii * 20 + 1] = funcCos( rg ) * k;			/* 弾速y */
				pmshot[ii * 20 + 2] = 1;						/* 存在 */
				pmshot[ii * 20 + 3] = 0;						/* 種類 */
				pmshot[ii * 20 + 4] = 0 ;						/*  */
				pmshot[ii * 20 + 5] = ( player[0] ) << 16 ;			/* 初期位置の設定 */
				pmshot[ii * 20 + 6] = ( player[1] ) << 16 ;
				pmshot[ii * 20 + 7] = muki;						/* 方向 */

				pmshot[ii * 20 + 8] = 0;						/*  */
				pmshot[ii * 20 + 9] = 0 ;						/*  */
				pmshot[ii * 20 + 10] = 0 ;						/*  */
				break;
			}
		}
	}


}

void CGpAct::p_mgc_disp()
{
	long ii;
	long f;
	long b;

	for ( ii = 0; ii < 40; ii++ )
	{
		if ( pmshot[ii * 20 + 2] == 1 )
		{

			f = 1;
			b = 230;


			BltRect(m_vTex[4], ( pmshot[ii * 20 + 5] >> 16 ) - d_x, 480 - ( pmshot[ii * 20 + 6] >> 16 ) - 32 - d_y, 0, 96, 32, 32 );

			pmshot[ii * 20 + 5] = pmshot[ii * 20 + 0] + pmshot[ii * 20 + 5];		/* 弾速x */
			pmshot[ii * 20 + 6] = pmshot[ii * 20 + 1] + pmshot[ii * 20 + 6];		/* 弾速x */

			if ( ( ( pmshot[ii * 20 + 5] >> 16 ) > 640 ) || ( ( pmshot[ii * 20 + 5] >> 16 ) < -32 ) )
			{
				pmshot[ii * 20 + 2] = 0;				/* 存在無し */
			}
			if ( ( ( pmshot[ii * 20 + 6] >> 16 ) > 480 ) || ( ( pmshot[ii * 20 + 6] >> 16 ) < -32 ) )
			{
				pmshot[ii * 20 + 2] = 0;				/* 存在無し */
			}

			if ( ( ( map1_item_j( ( pmshot[ii * 20 + 5] >> 16 ) + 16 , ( pmshot[ii * 20 + 6] >> 16 ) + 16 ) >= 100 )
			    && ( map1_item_j( ( pmshot[ii * 20 + 5] >> 16 ) + 16 , ( pmshot[ii * 20 + 6] >> 16 ) + 16 ) <= 220 ) ) )
			{
				pmshot[ii * 20 + 2] = 0;				/* 存在無し */
				p_shot_f2_set( ( pmshot[5 + ii * 20] >> 16 ) + 15, ( pmshot[6 + ii * 20] >> 16 ) + 15, 0 );
				if ( pmshot[3 + ii * 20] == 2 )	/* スキルクラッシュショット */
				{
					p_shot_f_set( ( pmshot[5 + ii * 20] >> 16 ) + ( rand() % 32 ) - 16, ( pmshot[6 + ii * 20] >> 16 ) + ( rand() % 32 ) - 16, 0 );
					p_shot_f_set( ( pmshot[5 + ii * 20] >> 16 ) + ( rand() % 32 ) - 16, ( pmshot[6 + ii * 20] >> 16 ) + ( rand() % 32 ) - 16, 0 );
					p_shot_f_set( ( pmshot[5 + ii * 20] >> 16 ) + ( rand() % 32 ) - 16, ( pmshot[6 + ii * 20] >> 16 ) + ( rand() % 32 ) - 16, 0 );
				}
				else
				{
					p_shot_f_set( ( pmshot[5 + ii * 20] >> 16 ) , ( pmshot[6 + ii * 20] >> 16 ), 0 );
				}
			}


		}
	}

}


void CGpAct::replay_input_save()
{
	long input_keys;
	input_keys = 0;

	/* キ?処理は基?的にplayer[2]が何状態の時にキ?を入れたらどうなるを記述していく */
	if ( g_pApp->IsPressKey( DGXKEY_LEFT ) )
	{
		input_keys = input_keys + 1;
	}
	else if (g_pApp->IsPressKey( DGXKEY_RIGHT ) )
	{
		input_keys = input_keys + 10;
	}

	if ( g_pApp->IsPressKey( DGXKEY_UP ) )
	{
		input_keys = input_keys + 100;
	}
	else if ( g_pApp->IsPressKey( DGXKEY_DOWN ) )
	{
		input_keys = input_keys + 1000;
	}

	//	スペ?スキ?が押される
	if ( g_pApp->IsPressKey( DGXKEY_FA ) )
	{
		input_keys = input_keys + 10000;
	}

	//Bが押される
	if ( g_pApp->IsPressKey( DGXKEY_FX ) )
	{
		input_keys = input_keys + 100000;
	}

	//Bが押される
	if ( ( g_pApp->IsPushKey( DGXKEY_FX ) ) || ( g_pApp->IsPushKey( DGXKEY_UP ) && ( GetSceneGameFlag1(133) == 1 ) ) )
	{
		input_keys = input_keys + 1000000;
	}

	replay[replay_time] = input_keys;
}

void CGpAct::replay_input_load()
{
	long i;
	long input_keys;
	input_keys = 0;

	for ( i = 0; i < 10 ; ++i )
	{
		replay_load_key[i] = 0 ;
	}

	input_keys = replay[replay_time];

	if ( input_keys >= 1000000 )
	{
		input_keys = input_keys - 1000000;
		replay_load_key[6] = 1 ;
	}
	if ( input_keys >= 100000 )
	{
		input_keys = input_keys - 100000;
		replay_load_key[5] = 1 ;
	}
	if ( input_keys >= 10000 )
	{
		input_keys = input_keys - 10000;
		replay_load_key[4] = 1 ;
	}
	if ( input_keys >= 1000 )
	{
		input_keys = input_keys - 1000;
		replay_load_key[3] = 1 ;
	}
	if ( input_keys >= 100 )
	{
		input_keys = input_keys - 100;
		replay_load_key[2] = 1 ;
	}
	if ( input_keys >= 10 )
	{
		input_keys = input_keys - 10;
		replay_load_key[1] = 1 ;
	}
	if ( input_keys >= 1 )
	{
		input_keys = input_keys - 1;
		replay_load_key[0] = 1 ;
	}
}



void CGpAct::replay_file_save_w()
{
//	char	strbuf[260]={0};
//
//	sprintf(strbuf,"replay/%d/replay_data_w_%d.dat", (int)stage, (int)save_data[3] );
//	SaveFile( strbuf, &replay[0], sizeof(replay));
}


void CGpAct::replay_file_save( long type )
{
//	char	strbuf[260]={0};
//
//	if ( type == 0 )
//	{
//		sprintf(strbuf,"replay/%d/replay_data_%d.dat", (int)stage, (int)save_data[3] );
//	}
//	else
//	{
//		sprintf(strbuf,"replay/%d/replay_data_j%d.dat", (int)stage, (int)save_data[3] );
//	}
//
//	SaveFile( strbuf, &replay[0], sizeof(replay));
}


long CGpAct::replay_file_load()
{
	long	hr = 1;
	char	strbuf[260]={0};


	if ( GetSceneGameFlag1(125) == 0 )
	{
		sprintf( strbuf, "replay/%d/replay_data_%d.dat", (int)stage, (int)save_data[3] );
	}
	else
	{
		sprintf( strbuf, "replay/%d/replay_data_j%d.dat", (int)stage, (int)save_data[3] );
	}
	if ( LoadFile( strbuf, &replay[0], sizeof( replay ) ) )
	{
		hr = 0;
	}

	return( hr );
}


long CGpAct::GetKyori( long i1, long i2 )
{
	long hr = 0;

	hr = ( long )sqrt((double)(( i1 * i1 ) + ( i2 * i2 )));

	return hr;
}

void CGpAct::debugdisp()
{
	if ( 0 != GetSceneDebugDisp() )
	{
		BltNumericImage( player[32]  , 8, 10, 10, m_vTex[18], 0, 0, 10, 8 );
		BltNumericImage( snack_count , 8, 10, 20, m_vTex[18], 0, 0, 10, 8 );
		BltNumericImage( player[20]  , 8, 10, 30, m_vTex[18], 0, 0, 10, 8 );
		BltNumericImage( player[21]  , 8, 10, 40, m_vTex[18], 0, 0, 10, 8 );
		BltNumericImage( map_rot_info, 8, 10, 50, m_vTex[18], 0, 0, 10, 8 );
		BltNumericImage(funcTan2( player[30],player[31] ), 8, 10, 60, m_vTex[18], 0, 0, 10, 8 );

		BltNumericImage((long)(atan2((double)(player[30] * 256),(double)(player[31] * 256)) ), 8, 10, 70, m_vTex[18], 0, 0, 10, 8 );
	}
}



