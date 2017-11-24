

#include "_StdAfx.h"


extern char* g_sSndBgm[8];
extern char* g_sSndSe[20];


static long enm1_parameter[10 * 20] =
{
/*   HP */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 0뼟럊뾭 */
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
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0 	/* 20뼟럊뾭 */
};

static long enm2_parameter[10 * 20] =
{
/*   HP */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 0뼟럊뾭 */
	  1,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 1 */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 2 */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 3 */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 4 */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 5 */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 6 */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 7 */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 8 */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 9 */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0 	/* 20뼟럊뾭 */
};

static long enm3_parameter[10 * 20] =
{
/*   HP   뗠 뛘똼 뫌맜 몜맜 */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 0뼟럊뾭 */
	  1,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 1 */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 2 */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 3 */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 4 */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 5 */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 6 */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 7 */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 8 */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 9 */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0 	/* 20뼟럊뾭 */
};

static long enm4_parameter[10 * 20] =
{
/*   HP */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 0뼟럊뾭 */
	  7,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 1?긚 */
	  7,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 2 */
	 30,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 3 */
	 27,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 4 */
     42,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 5 */
     30,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 6 */
      1,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 7 */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 8 */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 9 */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0 	/* 20뼟럊뾭 */
};

static long item_data[3] = { 32, 50, 20 };			/* 귺귽긡?궻륃뺪?긖귽긛갂띍묈봹뭫뙿릶갂1긢??긫긞긲?릶 */
static long enm_data[3] = { 0, 30, 30 };			/* 밎궻륃뺪??뷈갂띍묈봹뭫뙿릶갂1긢??긫긞긲?릶 */
static long MapInfo[10] =
{
	20 * 5									/* 0:?긞긵궻x긖귽긛 */
,	15 * 5									/* 1:?긞긵궻y긖귽긛 */
,	( 20 * 5 ) * 32							/* 2:?긞긵궻x?렑긖귽긛 */
,	( 15 * 5 ) * 32							/* 3:?긞긵궻y?렑긖귽긛 */
,   20										/* 4:긶긞?긢??븫궻긢??릶 */
};
static long char_size[10] =
{
	32										/* char_size[0] 돘븴 */
,	32										/* char_size[1] 뛼궠 */
,	10										/* char_size[2] 뵽믦궢궶궋븴뜺걁뜺궔귞긤긞긣궳긇긂깛긣걂 */
,	( 32 - 10 )								/* char_size[3] 뵽믦궢궶궋븴덭걁뜺궔귞긤긞긣궳긇긂깛긣걂 */
,	8										/* char_size[4] 귺긦긽?긘깈깛긬??깛릶 */
};

static long player[50];									/* 긵깒귽깂?뾭긫긞긲? */
											/* player[0] X */
											/* player[1] Y */
											/* player[2] 륉뫴 */
											/* player[3] 뛀궖 */
											/* player[4] BMP볙궻?렑댧뭫X */
											/* player[5] BMP볙궻?렑댧뭫Y */
											/* player[6] 믉귒뭷궻댷벍뺚맫X */
											/* player[7] 믉귒뭷궻댷벍뺚맫Y */
											/* player[8] 뙸띪HP */
											/* player[9] 밎귩믉귪궳궋귡 */
											/* player[10] 귺긦긽?긘깈깛긲깒??긇긂깛? */
											/* player[11] 귺긦긽?긘깈깛긇긂깛? */
											/* player[12] 귺긦긽?긘깈깛긲깒??럚믦 */
											/* player[13] 긙긿깛긵긲깒??긇긂깛? */
											/* player[14] 긙긿깛긵긇긂깛? */
											/* player[15] ?긚궻뤾뜃궻X */
											/* player[16] ?긚궻뤾뜃궻Y */
											/* player[17] 뼰밎렄듩 */
											/* player[18] 뭶뭤긾?긘깈깛뾭긇긂깛? */
											/* player[19] 됷?됀?궔 */
											/* player[20] ?긞긵궻됷?둷뱗 */
											/* player[21] ?긞긵궻됷?둷뱗뽞뷭 */
											/* player[22] 됷?볺쀍궻긂긄귽긣 */
											/* player[23] 됷?둷뱗뜼빁 */
											/* player[24] secret item get ?렑렄듩  */
											/* player[25] ??깛귩궓궢궲긙긿깛긵궢궫긲깋긐 */
											/* player[26] 뮮렄듩뿇돷궢궫긲깋긐걁뭶뭤긲긃긏긣뾭걂 */
											/* player[27] 믉귪궬궴궖궸볺쀍궠귢궲궋궫긌? */
											/* player[28] 댷벍룿긾?긘깈깛 */
											/* player[29] 돘궽궺릟궖뷅귂뭷 */
											/* player[30] lastone?렑 */
											/* player[31] 긇긞긣귽깛궻?렑 */
											/* player[32] 긇긞긣귽깛궻롰쀞 */
											/* player[33] 귺귽긡?귩돓궢궫렄궻댷벍쀊 */
											/* player[34]  */
											/* player[35]  */
											/* player[36]  */
											/* player[37]  */
											/* player[38]  */
static long dp_x;									/* 긵깒귽깂?궻?렑댧뭫걁됪뽋볙궻몜뫮띆뷭걂 */
static long dp_y;									/* 긵깒귽깂?궻?렑댧뭫걁됪뽋볙궻몜뫮띆뷭걂 */
static long dp_x2 = 80;								/* 긵깒귽깂?궻?렑댧뭫걁됪뽋볙궻몜뫮띆뷭걂 */
static long demo[10];
static long map1[10200];								/* ( MapInfo[0] * MapInfo[1] ) + MapInfo[4] 봶똧뾭긫긞긲? 깒귽깂?1 */
static long map2[10200];							 	/* MapInfo[0] * MapInfo[1] 봶똧뾭긫긞긲? 깒귽깂?2 */
static long mapfile[10200];							/* MapInfo[0] * MapInfo[1] 봶똧뾭긫긞긲? 깒귽깂?2 */
static long map_data[20];							/* 긶긞?륃뺪 */
static long bak_cnt = 0;							/* 봶똧귺긦긽?긘깈깛뾭긇긂깛? */
static long bak_alldrow = 0;						/* 봶똧궻?됪귩긏깏긞긵궥귡궔 */
static long d_x = 0;								/* 봶똧?렑댧뭫 */
static long d_y = 0;								/* 봶똧?렑댧뭫 */
static long kamera = 0;

static long next_px = 0;							/* 됪뽋먛귟뫶궑렄궻긌긿깋댷벍뫮랉 */
static long next_py = 0;

static long map_rot_info = 0;							/* ?긞긵궻뛀궖 */
#ifdef GP2X
static const long atk_rr1 =30;						/* 쁱궻됷?뫊뱗 */
#else
static const long atk_rr1 =5;						/* 쁱궻됷?뫊뱗 */
#endif


static long stage = 0;								/* 긚긡?긙붥뜂 */
static long secretitemget = 0;						/* 덨궢귺귽긡?궻롦벦 */
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


static long pshot[10 * 10];							/* 긵깒귽깂?뛘똼뾭륃뺪 */
static long pshotf[10 * 40];						/* 긵깒귽깂?뛘똼뾭륃뺪 */
static Tparticle pshotf2[PARTICLE];					/* 긵깒귽깂?뛘똼뾭륃뺪 */


static long pmshot[20 * 40];						/* 긵깒귽깂?뛘똼뾭륃뺪 */
static long pjumpf[100];							/* 긵깒귽깂?뛘똼뾭륃뺪 */
static long item[20 * 50];							/* 귺귽긡?뾭긫긞긲? */
static long item_wk[5*100];							/* 뭤뽋 궩궻뫜궻?긞긵륃뺪 */

static long enemy[30 * 30];							/* enm_data[1] * enm_data[2] 밎륃뺪	*/

static long mgc_e[10 * 20] ;						/* MGC?렑륃뺪			*/
static long p_ef[1000] ;							/* 붍뾭긫긞긲?걁뫉먘뱳걂*/
static long kane[200];								/* 귺귽긡?뾭긫긞긲? */

static long Jump_counts = 0;
static long snack_count = 0;
static long all_snack_count = 0;
static long save_data[512];							/* 뺎뫔륃뺪 */
static long test[5];
static long rayer[5];								/* 봶똧긚긏깓?깑쀊 */
static long play_time[5];


static long replay[60 * 60 * 10];	/* 긲깒??걭뷳걭빁 */
static long replay_time = 1;
static long replay_time_MAX = 60 * 60 * 10;	/* 띍묈렄듩 */
static long replay_load_key[10];

static long replay_save_flag = 0;				/* 뺎뫔귩뛱궎궔 1:궢궶궋 */
static long rrkey[5];								/* 볺쀍긌?뺴뛀 */


static long one_event = 0;							/* 뢣궶궯궲뵯맯궥귡귽긹깛긣궻멟됷뢣궶궯궲궋궫궔궻긲깋긐 */


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


// 게임 플레이 직전 호출( 이벤트 > 게임 플레이, 게임 플레이 > 게임 플레이 ( 스테이지 이동 ) )
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
	bak_cnt = 0;							/* 봶똧귺긦긽?긘깈깛뾭긇긂깛? */
	bak_alldrow = 0;						/* 봶똧궻?됪귩긏깏긞긵궥귡궔 */
	d_x = 0;								/* 봶똧?렑댧뭫 */
	d_y = 0;								/* 봶똧?렑댧뭫 */
	next_px = 0;							/* 됪뽋먛귟뫶궑렄궻긌긿깋댷벍뫮랉 */
	next_py = 0;
	stage = 0;								/* 긚긡?긙붥뜂 */
	Jump_counts = 0;
	snack_count = 0;
	all_snack_count = 0;
	replay_time = 1;
	replay_time_MAX = 60 * 60 * 10;	/* 띍묈렄듩 */
	replay_save_flag = 0;				/* 뺎뫔귩뛱궎궔 1:궢궶궋 */
	one_event = 0;							/* 뢣궶궯궲뵯맯궥귡귽긹깛긣궻멟됷뢣궶궯궲궋궫궔궻긲깋긐 */
	map_rot_info = 0;							/* ?긞긵궻뛀궖 */
	secretitemget = 0;						/* 덨궢귺귽긡?궻롦벦 */

//#if FALSE
	memset( player, 0, sizeof( player ) );									/* 긵깒귽깂?뾭긫긞긲? */
	memset( demo, 0, sizeof( demo ) );
	memset( map1, 0, sizeof( map1 ) );								/* 봶똧뾭긫긞긲? 깒귽깂?1 */
	memset( map2, 0, sizeof( map2 ) );								/* 봶똧뾭긫긞긲? 깒귽깂?2 */
	memset( map_data, 0, sizeof( map_data ) );
	memset( pshot, 0, sizeof( pshot ) );							/* 긵깒귽깂?뛘똼뾭륃뺪 */
	memset( pshotf, 0, sizeof( pshotf ) );						/* 긵깒귽깂?뛘똼뾭륃뺪 */
	memset( pshotf2, 0, sizeof( pshotf2 ) );						/* 긵깒귽깂?뛘똼뾭륃뺪 */
	memset( pmshot, 0, sizeof( pmshot ) );						/* 긵깒귽깂?뛘똼뾭륃뺪 */
	memset( pjumpf, 0, sizeof( pjumpf ) );							/* 긵깒귽깂?뛘똼뾭륃뺪 */
	memset( item, 0, sizeof( item ) );							/* 귺귽긡?뾭긫긞긲? */
	memset( item_wk, 0, sizeof( item_wk ) );							/* 뭤뽋 궩궻뫜궻?긞긵륃뺪 */
	memset( enemy, 0, sizeof( enemy ) );								/* 밎륃뺪															*/
	memset( mgc_e, 0, sizeof( mgc_e ) ) ;						/* MGC?렑륃뺪														*/
	memset( p_ef, 0, sizeof( p_ef ) ) ;							/* 붍뾭긫긞긲?걁뫉먘뱳걂														*/
	memset( kane, 0, sizeof( kane ) );								/* 귺귽긡?뾭긫긞긲? */
	memset( save_data, 0, sizeof( save_data ) );							/* 뺎뫔륃뺪 */
	memset( test, 0, sizeof( test ) );
	memset( rayer, 0, sizeof( rayer ) );								/* 봶똧긚긏깓?깑쀊 */
	memset( play_time, 0, sizeof( play_time ) );
	memset( replay, 0, sizeof( replay ) );	/* 긲깒??걭뷳걭빁 */
	memset( replay_load_key, 0, sizeof( replay_load_key ) );
	memset( rrkey, 0, sizeof( rrkey ) );								/* 볺쀍긌?뺴뛀 */
	memset( target_save, 0, sizeof( target_save ) );
//#endif

	/* 궔궚귞롦벦륃뺪 */
	ResetGameFlag2();				/* 긲?귽깑궶궢 */

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
	d_num = save_data[3]; 	/* 됪뽋 */


	SetSceneGameFlag1(120, d_num);


	player[20] = 0;
	player[21] = 0;
	player[22] = 1;


	/* 깒귽깂?괦 */
	ResetGameFlag2();
	sprintf(strbuf,"data/%d/%d_%d.map", ( int )stage , ( int )1, ( int )d_num );
	if ( 0 == LoadFile( strbuf, map1, sizeof( map1 ) ) )
	{
	}
	else
	{
		/* 긲?귽깑궕궶궋 */
		if ( 1 == GetSceneGameFlag1(132) )	/* 깏긵깒귽 */
		{
			SetSceneState(EN_SN_TITLE);	/* ?귽긣깑귉 */
		}
		else
		{
//			GetSceneGameFlag1(40) = 5;	/* 긄깛긢귻깛긐귉 */
//			SetSceneState(EN_SN_ENDING);	/* ?귽긣깑귉 */
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

	if ( 0 != GetSceneGameFlag1(128) )	//?긞긵긮깄?
	{
		item_set( 1, player[0], player[1], 0, d_num );
	}

	/* 깒귽깂?괧 */
	ResetGameFlag2();
	sprintf(strbuf,"data/%d/%d_%d.map", ( int )stage , ( int )2, ( int )d_num );
	LoadFile( strbuf, map2, sizeof( map2 ) );

	/* 귺귽긡?봹뭫 */
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
						//긌긿깋긏??
					}
					else
					{
						item_set( mapfile[x + ( y * MapInfo[0] )], x * 32, ( ( MapInfo[1] - 1 - y ) * 32 ), x + ( y * MapInfo[0] ), d_num );
					}
				}
			}
		}
	}



	ResetGameFlag2();				/* 긲?귽깑궶궢 */
	sprintf( strbuf,"data/%d/e%d_%d.map", ( int )stage , ( int )1, ( int )d_num );
	LoadFile( strbuf, mapfile, sizeof( mapfile ) );

	/* 밎봹뭫 */
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

	player[14] = 10;	/* 긙긿깛긵긇긂깛? */
	player[15] = player[0];
	player[16] = player[1];
	player[2] = 0;



	if ( 1 == GetSceneGameFlag1(132) )
	{
		if ( 1 != replay_file_load() )
		{
			/* 긲?귽깑궕벶귕궶궔궯궫 */
			SetSceneState(EN_SN_TITLE);	/* ?귽긣깑귉 */
			m_nSn = 10;
			return 0;
		}
	}
	else
	{
	}


	if ( 1== GetSceneGameFlag1(127) )	//긣??깑귺?긞긏
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
			if ( GetSceneGameFlag1(137) > GetSceneGameFlag1(135) )	//긣??깑귺?긞긏 긏깏귺렄듩
			{
				SetSceneGameFlag1(137, GetSceneGameFlag1(135));
			}
			if ( GetSceneGameFlag1(138) > GetSceneGameFlag1(136) )	//긣??깑귺?긞긏 긏깏귺긙긿깛긵
			{
				SetSceneGameFlag1(138, GetSceneGameFlag1(136));
			}
		}
	}


	//(E) 2010-08-05 Editor: AFEW
	//	sprintf(strbuf,"image/player/ri%d.png", ( int )GetSceneGameFlag1(122) );
	//	LoadImage(&m_vTex[1], strbuf, TRUE);					//긵깒?깛긥깛긫?괧궸긘긚긡?뾭괶굃굊귩벶귒뜛귔

	sprintf(strbuf,"image/map/map%d_1.png", ( int )stage );
	ReleaseImage(&m_vTex[10]);
	LoadImage(&m_vTex[10],strbuf,TRUE);					//긵깒?깛긥깛긫?괧궸긘긚긡?뾭괶굃굊귩벶귒뜛귔

	sprintf(strbuf,"image/map/map%d_2.png", ( int )stage );
	ReleaseImage(&m_vTex[11]);
	LoadImage(&m_vTex[11],strbuf,TRUE);					//긵깒?깛긥깛긫?괧궸긘긚긡?뾭괶굃굊귩벶귒뜛귔

	sprintf(strbuf,"image/map/item%d.png", ( int )stage );
	ReleaseImage(&m_vTex[12]);
	LoadImage(&m_vTex[12],strbuf,TRUE);					//긵깒?깛긥깛긫?괧궸긘긚긡?뾭괶굃굊귩벶귒뜛귔


	// Loading 0
	Loading(0);

	// Loading 1
	Loading(1);


	// Loading 2
	Loading(2);


	if ( 0 != GetSceneGameFlag1(128) )	//?긞긵긮깄?
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
		if(NULL == m_vTex[1])	LoadImage(&m_vTex[1], (char*)"image/player/ri0.png",TRUE);				//긵깒?깛긥깛긫?괧궸긘긚긡?뾭괶굃굊귩벶귒뜛귔
		if(NULL == m_vTex[4])	LoadImage(&m_vTex[4], (char*)"image/player/atk2.png",TRUE);				//긵깒?깛긥깛긫?괧궸긘긚긡?뾭괶굃굊귩벶귒뜛귔
		if(NULL == m_vTex[5])	LoadImage(&m_vTex[5], (char*)"image/player/atkf.png",TRUE);				//긵깒?깛긥깛긫?괧궸긘긚긡?뾭괶굃굊귩벶귒뜛귔
		if(NULL == m_vTex[6])	LoadImage(&m_vTex[6], (char*)"image/player/cutin.png",TRUE);			//긵깒?깛긥깛긫?괧궸긘긚긡?뾭괶굃굊귩벶귒뜛귔

		if(NULL == m_vTex[18])	LoadImage(&m_vTex[18], (char*)"image/sys/fonts2.png",TRUE);				//긵깒?깛긥깛긫?괧궸긘긚긡?뾭괶굃굊귩벶귒뜛귔
		if(NULL == m_vTex[40])	LoadImage(&m_vTex[40], (char*)"image/enm/e32.png",TRUE);				//긵깒?깛긥깛긫?괧궸긘긚긡?뾭괶굃굊귩벶귒뜛귔
		if(NULL == m_vTex[60])	LoadImage(&m_vTex[60], (char*)"image/sys/menu.png", TRUE);				//긵깒?깛긥깛긫?괧궸긘긚긡?뾭괶굃굊귩벶귒뜛귔
		if(NULL == m_vTex[61])	LoadImage(&m_vTex[61], (char*)"image/title/scl.png", TRUE);			//긵깒?깛긥깛긫?괧궸긘긚긡?뾭괶굃굊귩벶귒뜛귔
	}
	else if( 1 == n)
	{
		if(NULL == m_vTex[67])	LoadImage(&m_vTex[67], (char*)"image/sys/input.png", TRUE);			//긵깒?깛긥깛긫?괧궸긘긚긡?뾭괶굃굊귩벶귒뜛귔
		if(NULL == m_vTex[68])	LoadImage(&m_vTex[68], (char*)"image/sys/new1.png", TRUE);				//긵깒?깛긥깛긫?괧궸긘긚긡?뾭괶굃굊귩벶귒뜛귔
		if(NULL == m_vTex[69])	LoadImage(&m_vTex[69], (char*)"image/sys/new2.png", TRUE);				//긵깒?깛긥깛긫?괧궸긘긚긡?뾭괶굃굊귩벶귒뜛귔
		if(NULL == m_vTex[70])	LoadImage(&m_vTex[70], (char*)"image/sys/mini_map.png", TRUE);			//긵깒?깛긥깛긫?괧궸긘긚긡?뾭괶굃굊귩벶귒뜛귔

		if(NULL == m_vTex[71])	LoadImage(&m_vTex[71], (char*)"image/sys/stagestart.png", TRUE);		//긵깒?깛긥깛긫?괧궸긘긚긡?뾭괶굃굊귩벶귒뜛귔
		if(NULL == m_vTex[72])	LoadImage(&m_vTex[72], (char*)"image/bak/0.png", TRUE);				//긵깒?깛긥깛긫?괧궸긘긚긡?뾭괶굃굊귩벶귒뜛귔
		if(NULL == m_vTex[73])	LoadImage(&m_vTex[73], (char*)"image/sys/new3.png", TRUE);				//긵깒?깛긥깛긫?괧궸긘긚긡?뾭괶굃굊귩벶귒뜛귔
		if(NULL == m_vTex[74])	LoadImage(&m_vTex[74], (char*)"image/sys/new4.png", TRUE);				//긵깒?깛긥깛긫?괧궸긘긚긡?뾭괶굃굊귩벶귒뜛귔
		if(NULL == m_vTex[75])	LoadImage(&m_vTex[75], (char*)"image/sys/scor.png", TRUE);				//긵깒?깛긥깛긫?괧궸긘긚긡?뾭괶굃굊귩벶귒뜛귔
		if(NULL == m_vTex[76])	LoadImage(&m_vTex[76], (char*)"image/sys/houkou.png", TRUE);			//긵깒?깛긥깛긫?괧궸긘긚긡?뾭괶굃굊귩벶귒뜛귔

		if(NULL == m_vTex[110])	LoadImage(&m_vTex[110], (char*)"image/bak/1_256.png", FALSE);
		if(NULL == m_vTex[111])	LoadImage(&m_vTex[111], (char*)"image/bak/2_256.png", FALSE);
		if(NULL == m_vTex[112])	LoadImage(&m_vTex[112], (char*)"image/bak/3_256.png", FALSE);
		if(NULL == m_vTex[113])	LoadImage(&m_vTex[113], (char*)"image/bak/4_256.png", FALSE);
		if(NULL == m_vTex[114])	LoadImage(&m_vTex[114], (char*)"image/bak/5_256.png", FALSE);

		if(NULL == m_vTex[120])	LoadImage(&m_vTex[120], (char*)"image/color.png", FALSE);

		//(E) 2010-08-05 Editor: AFEW
		if(NULL == m_vTex[121])	LoadImage(&m_vTex[121], (char*)"image/title/stageselect.png", TRUE);		//긵깒?깛긥깛긫?괧궸긘긚긡?뾭괶굃굊귩벶귒뜛귔
		if(NULL == m_vTex[122])	LoadImage(&m_vTex[122], (char*)"image/title/potion_bak.png", FALSE );		//긵깒?깛긥깛긫?괦궸?귽긣깑됪뽋봶똧귩벶귒뜛귔
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
		replay_input_save();		/* 깏긵깒귽긢??뺎뫔 */
	}
	else
	{
		replay_input_load();		/* 깏긵깒귽긢??띋맯 */
	}
	replay_time++;
	if ( replay_time > replay_time_MAX )
	{
		replay_time = replay_time_MAX;	/* 띍묈렄듩귩뎭궑궫갂뺎뫔궢궶궋 */
		replay_save_flag = 1;			/* 뺎뫔궢궶궋 */
	}

	for ( i = 0; i < 5; ++i )
	{
		rrkey[i] = 0;						/* 볺쀍긌?뺴뛀 */
	}

	player[17]--;			/* 뼰밎렄듩 */
	if ( player[17] <= 0 )
	{
		player[17] = 0;
	}
	if ( player[9] == 0 )
	{
		jmp();
	}


	if ( ( item_up() != -1 ) && ( player[14] == 10 ) )	/* 귺귽긡?궻뤵궸뤸궯궲궋귡 */
	{
		player[1] = item_up();
	}

	player[19] = 0;	// 됷?됀?궔긲깋긐


	if ( player[2] == 31 )
	{
	}
	else
	{
		old_x = player[0];

		if ( player[9] == 1 )	//됷?뭷
		{
		}
		else
		{
			//(E) 2010-07-15 Editor: AFEW
			//	if ( ( ( g_pApp->IsPressKey( DGXKEY_LEFT ) ) && ( 0 == GetSceneGameFlag1(132) ) )		// 뜺
			//		|| ( ( replay_load_key[0] == 1 ) && ( 1 == GetSceneGameFlag1(132) ) ) )


			INT nLeft = g_pApp->IsPressKey(DGXKEY_LEFT) || g_pApp->IsPressKey(DGXKEY_UP_LEFT);
			INT nRight= g_pApp->IsPressKey(DGXKEY_RIGHT) || g_pApp->IsPressKey(DGXKEY_UP_RIGHT);

			if ( ( nLeft  && ( 0 == GetSceneGameFlag1(132) ) )		// 뜺
				  || ( ( replay_load_key[0] == 1 ) && ( 1 == GetSceneGameFlag1(132) ) ) )
			{

				player[3] = 1;	/* 뛀궖 */
				if ( player[2] == 0 )
				{
					player[10] = 0;	/* 귺긦긽?긘깈깛듩둼긲깒??먠믦 */
					player[11] = 0;	/* 귺긦긽?긘깈깛긇긂깛? */
					player[2] = 1;	/* 뺖궖 */
				}
				else if ( player[2] == 1 )
				{
					player[0] = player[0] - 2;	/* 긌긿깋긏??댷벍 */
				}
				else if ( player[2] == 21 )
				{
					player[0] = player[0] - 2;	/* 긌긿깋긏??댷벍 */
				}

			}
			//(E) 2010-07-15 Editor: AFEW
			//	else if ( ( ( g_pApp->IsPressKey( DGXKEY_RIGHT ) ) && ( 0 == GetSceneGameFlag1(132) ) )	// 덭
			//		|| ( ( replay_load_key[1] == 1 ) && ( 1 == GetSceneGameFlag1(132) ) ) )

			else if ( ( nRight && ( 0 == GetSceneGameFlag1(132) ) )	// 덭
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



		if ( player[28] != 0 )	/* 댷벍룿 */
		{
			player[0] = player[0] + player[28];
		}
		player[28] = 0;

		if ( player[29] > 0 )	/* 댷벍룿 */
		{
			player[0] = player[0] + ( player[29] * 1 );
			player[29] = player[29] - 1;
		}
		else if ( player[29] < 0 )
		{
			player[0] = player[0] + ( player[29] * 1 );
			player[29] = player[29] + 1;
		}

		/* 멟됷궻댧뭫궔귞댷벍궢궫 */
		if ( old_x > player[0] )
		{
			idou_l();	/* 뜺댷벍궻빮뵽믦 */
		}
		else if ( old_x < player[0] )
		{
			idou_r();	/* 덭댷벍궻빮뵽믦 */
		}
		player[33] = ( player[0] - old_x );



		//	긚긻?긚긌?궕돓궠귢귡
		if ( ( ( g_pApp->IsPressKey( DGXKEY_FA ) )  && ( GetSceneGameFlag1(132) == 0 ) ) 		/* 댷벍뫊뱗믟돷 */
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

					// 현재 진동 장치 상태 확인
					if(DGE_VIB_STATUS_BUSY == DGE_HapticStatus())
					{
						// 작동 중

						// 진동 정지
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
					player[2] = 2;		// 궰궔귒



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

		kakudosa = ( player[21] - player[20] );		// 됷?궕뢎뿹궢궫

		if ( kakudosa == 0 )		// 뜼궕궶궋뤾뜃궼됷궠궶궋
		{
			if ( player[9] == 1 )
			{
				Jump_counts++;
				DGX_SoundPlay( m_pSndSe[EN_SE_ATK1] );
				rotmap( player[21] );	// 됷?

				player[10] = 0;
				player[11] = 0;
				player[2] = 0;		// 튱걜吏

				player[14] = 0;		// 뿇돷
				player[13] = 0;

				player[1] = player[1] + 8;	// 궇궫귟뵽믦궕뮮뺴?궶궻궳븖궔궧귡

				m_nSn = 1;
				player[9] = 0;

				switch( player[21] )
				{
				case 90:
					map_rot_info = map_rot_info - 1;							/* ?긞긵궻뛀궖 */
					break;
				case 180:
					map_rot_info = map_rot_info + 2;							/* ?긞긵궻뛀궖 */
					break;
				case 270:
					map_rot_info = map_rot_info + 1;							/* ?긞긵궻뛀궖 */
					break;
				default:
					break;
				}
				if ( map_rot_info < 0 )	// 뮪궑궫
				{
					map_rot_info = map_rot_info + 4;
				}
				if ( map_rot_info > 3 )	// 뮪궑궫
				{
					map_rot_info = map_rot_info - 4;
				}

			}
		}
		else
		{
			if ( kakudosa == 0 )		// 뜼궕궶궋뤾뜃궼됷궠궶궋
			{
			}
			else if ( kakudosa < 0 ) // 뽞뷭둷뱗궸뫮궢궲뙸띪뭤궼긵깋긚
			{
				if ( -180 > kakudosa )  // 180뱗뮪궑궲궋귡뤾뜃궼땤됷?
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
			else if ( kakudosa > 0 ) // 뽞뷭둷뱗궸뫮궢궲뙸띪뭤궼?귽긥긚
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
			// 360뱗귩뎭궑궫뤾뜃궼0뱗궸긆긲긜긞긣
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
			if ( player[9] == 0 )	// 궰궔귪궳궋궶궋
			{
				if ( ( player[2] != 11 ) && ( player[2] != 31 ) && ( player[14] == 10 ) )	/* 뭤뤵궳뛘똼갂?긽?긙궣귗궶궋 */
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
						/* 귺귽긡?궸뤸궯궲궋궶궋뤾뜃궼궩궞궕깏긣깋귽댧뭫 */
						if ( item_up() == -1 )
						{
							player[15] = player[0];
							player[16] = player[1];
						}
						player[10] = 0;
						player[11] = 0;
						player[2] = 21;	/* 뗴뭷 */
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
				if ( ( player[14] > 0 ) && ( player[25] == 1 ) )	/* 뱑뭷궳뿇돷 */
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
	/* 12??깛?궔?괷궕돓궠귢궫 */
#if defined(GP2X_WIZ)
	int PopupKey = DGXKEY_SELECT;
#else
	int PopupKey = DGXKEY_HOME;
#endif


	if ( g_pApp->IsPushKey( PopupKey ) )
	{
		if ( m_nSn != 5 && m_nSn !=2 )	//됷?뭷궳궼궶궋
		{
			m_nSn = 4;
			demo[0] = 0;
			demo[1] = 0;
		}
	}




	if ( player[0] < 0 )	/* 됪뽋뜺?뵽믦 */
	{
		player[0] = 0;
		/*
		귽긹깛긣뭷궸save_data[9]귩먠믦궥귡궞궴궳갂덇렄밒궸긚긏깓?깑븉됀궴궥귡갃
		?긚먰궶궵궸럊뾭
		*/
		if ( save_data[9] == 1 )	/* 긚긏깓?깑븉됀 */
		{
		}

		else
		{
			if ( player[1] <= 460 )					/* 긌긿깋긏??뤵뺴뛀궕됪뽋볙 */
			{
				if ( map_data[4] == 1 )			/* 긚긏깓?깑륃뺪궇귟 */
				{
					wait_scl( 2, map_data[5] );	/* 긚긏깓?깑 */
				}
				else if ( map_data[4] == 2 )	/* 긚긡?긙댷벍륃뺪궇귟 */
				{
					end_scl( map_data[5] );		/* 긚긡?긙댷벍 */
				}
			}
		}
	}




	if ( player[0] > ( MapInfo[2] - char_size[0] ) )	/* 됪뽋덭?뵽믦 */
	{
		player[0] =  MapInfo[2] - char_size[0];
		if ( save_data[9] == 1 )	/* 긚긏깓?깑븉됀 */ 
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


	if ( player[1] <= 0 )	/* 됪뽋돷 */
	{
		if ( save_data[9] == 1 )	/* 긚긏깓?깑븉됀 */
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


	if ( player[1] >= ( MapInfo[3] - char_size[1] ) )	/* 됪뽋뤵 */
	{
		if ( save_data[9] == 1 )	/* 긚긏깓?깑븉됀 */
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
	if ( player[2] == 0 )	/* 긦깄?긣깋깑 */
	{
		player[12] = 10;
	}
	if ( player[2] == 1 )	/* 뺖궖 */
	{
		player[12] = 10;
	}
	if ( player[2] == 2 )	/* 궰궔귒 */
	{
		player[12] = 5;
	}
	if ( player[2] == 11 )	/* 뛘똼 */
	{
		player[12] = 2;
	}
	if ( player[2] == 21 )	/* 뗴뭷 */
	{
		player[12] = 5;
	}
	if ( player[2] == 31 )	/* 귘귞귢 */
	{
		player[12] = 10;
	}
	if ( player[2] == 33 )	/* 긏깏귺 */
	{
		player[12] = 10;
	}
	if ( player[2] == 61 )	/* 뤵뛀궖 */
	{
		player[12] = 10;
	}
}


/* 궥궋뭷궻뤾뜃궼긙긿깛긵쀍몵돿 */
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
	/* 릣뭷뵽믦 */

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

/* 긙긿깛긵굕댧뭫똶럁 */
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

	/* 긙긿깛긵긲깒??긇긂깛긣 */
	player[13]++;
	if ( player[13] >= 10 )
	{
		player[13] = 0;
	}

	if ( player[2] == 41 )	/* 궼궢궟뭷 */
	{
		player[18] = 0;			/* 궰궔귒궔귞긙긿깛긵 */
		player[28] = 0;			/* 뿬궠귢궲궋귡 */

		player[14] = 10;
		return;
	}

	/* 뜞됷궻댧뭫 */
	px = ( player[0] + ( char_size[0] / 2 ) ) / 32;
	px1 = ( player[0] + char_size[2] ) / 32;
	px2 = ( player[0] + char_size[3] ) / 32;
//		py = ( 16 - ( ( player[1] + ( char_size[1] - 5 ) ) / 32 ) );
	py = ( MapInfo[1] - ( ( player[1] + ( char_size[1] - 5 ) ) / 32 ) );

	if ( player[14] == 10 ) 	/* 뭤뤵 */
	{

		/* 100 ? 200궼뭤뽋 */
		/* 뫉뙰궕뭤뽋궳궼궶궋 */
		if ( ( ( !( ( map1[ px1 + ( ( py ) * MapInfo[0] ) ] >= 100 ) && ( map1[ px1 + ( ( py ) * MapInfo[0] ) ] <= 119 ) ) )
		  && ( !( ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] >= 100 ) && ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] <= 119 ) ) )
		  && ( !( ( map1[ px1 + ( ( py ) * MapInfo[0] ) ] >= 200 ) && ( map1[ px1 + ( ( py ) * MapInfo[0] ) ] <= 219 ) ) )
		  && ( !( ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] >= 200 ) && ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] <= 219 ) ) )
		  && ( !( ( map1[ px1 + ( ( py ) * MapInfo[0] ) ] >= 600 ) && ( map1[ px1 + ( ( py ) * MapInfo[0] ) ] <= 619 ) ) )
		  && ( !( ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] >= 600 ) && ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] <= 619 ) ) ) )
		  || ( ( ( player[1] ) % 32 ) != 0 ) )
		{
			if ( item_up() != -1 )	/* 귺귽긡?궻뤵궸뤸궯궲궋귡 */
			{
				player[1] = item_up();
				player[14] = 10;
				return;
			}

			/* 뺖궖뭷궶귞뗴뭷륉뫴귉댷뛱 */
			if ( ( player[2] == 0 )
			  || ( player[2] == 1 ) )
			{
				player[10] = 0;
				player[11] = 0;
				player[2] = 21;		/* 뗴뭷 */
			}
			player[14] = -1;			/* 뿇돷둎럑 */
			player[13] = 0;

			if ( player[2] == 31 )	/* ?긽?긙뭷 */
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
		/* 뺖궖뭷궶귞뗴뭷륉뫴귉댷뛱 */
		if ( ( player[2] == 0 )
		  || ( player[2] == 1 ) )
		{
			player[10] = 0;
			player[11] = 0;
			player[2] = 21;		/* 뗴뭷 */
		}
		player[22] = 0;					/* 뢿긇긂깛? */
	}

	/* 10긲깒??궸1됷Y띆뷭똶럁 */
	if ( player[13] == 0 )
	{
		player[14] = player[14] - 2;	/* 긙긿깛긵쀍뙵룺 */

		/* 뮯?븊뗟궼-1뿇돷둎럑궴궥귡 */
		if ( ( player[14] <= 2 ) && ( player[14] > -2 ) )
		{
			player[14] = -1;
		}

		if ( player[14] < -4 )	/* 띍뫊뿇돷귩먠믦 */
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

	/* 릣뭷뵽믦뱳궻봶똧궸귝궯궲뿇돷뫊뱗궕빾귦귡뤾뜃궼뵽믦궥귡 */
	/* 뜞됷궻댧뭫 */
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
		if ( player[14] > 0 ) /* 뤵뤈뭷 */
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

		player[1] = player[1] - ( y1 / 20 );	/* Y댷벍 */
	}


	/* 뿇돷갂뤵뤈됀?뵽믦 */
	/* 됪뽋둖궻뤾뜃궼뛱귦궶궋 */
	if ( player[1] >= ( MapInfo[3] - char_size[1] ) )
	{
		return;
	}
	py3 = ( MapInfo[1] - ( ( player[1] + char_size[1] + 32 ) / 32 ) );

	/* 뿇돷 */
	if ( player[14] <= 0 )													/* 뤵귟뭷궼뵽믦궢궶궋 */
	{
		/* 뭤뽋뵽믦 */
		if ( ( ( map1[ px1 + ( ( py ) * MapInfo[0] ) ] >= 100 ) && ( map1[ px1 + ( ( py ) * MapInfo[0] ) ] <= 119 ) )
		  || ( ( map1[ px1 + ( ( py ) * MapInfo[0] ) ] >= 200 ) && ( map1[ px1 + ( ( py ) * MapInfo[0] ) ] <= 219 ) )
		  || ( ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] >= 100 ) && ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] <= 119 ) )
		  || ( ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] >= 200 ) && ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] <= 219 ) )
		  || ( ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] >= 600 ) && ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] <= 619 ) ) )
		{
			/* 뭶뭤 */
			if ( player[8] > 0 )	/* HP궕궇귡뤾뜃궼뚼됈돶귩뼿귞궥 */
			{
				DGX_SoundPlay( m_pSndSe[EN_SE_LANDING] );
				se_wav( 9 );
			}
			if ( ( player[2] != 31 ) && ( player[2] != 32 ) )	/* ?긽?긙뭷궣귗궶궋 */
			{
				player[2] = 0;							/* 뿧궭륉뫴귉 */
				player[11] = 0;							/* 귺긦긽?긘깈깛긇긂깛?긏깏귺 */
			}
			player[1] = ( ( MapInfo[1] - py ) * 32 ); 		/* 뭶뭤궢궫?긚궻Y띆뷭궸뜃귦궧귡 */
			player[14] = 10;								/* 긙긿깛긵쀍귩뭤뤵궸먠믦 */

			player[18] = 0;			/* 궰궔귒궔귞긙긿깛긵 */
			player[28] = 0;			/* 뿬궠귢궲궋귡 */

			p_jump_f_set( player[0], player[1] );
		}
		else
		{
			if ( item_up() != -1 )						/* 귺귽긡?궻뤵궸뤸궯궲궋귡 */
			{
				DGX_SoundPlay( m_pSndSe[EN_SE_LANDING] );
				se_wav( 9 );
				if ( ( player[2] != 31 ) && ( player[2] != 32 ) )	/* ?긽?긙뭷궣귗궶궋 */
				{
					player[2] = 0;							/* 뭶뭤 */
					player[11] = 0;							/* 귺긦긽?긘깈깛긇긂깛?긏깏귺 */
				}
				player[1] = item_up();
				player[14] = 10;

				player[18] = 0;			/* 궰궔귒궔귞긙긿깛긵 */
				player[28] = 0;			/* 뿬궠귢궲궋귡 */

				p_jump_f_set( player[0], player[1] );
			}
		}
	}
	else		/* 뤵뤈뭷 */
	{
		/* 뭤뽋뵽믦 */
		if ( ( ( map1[ px1 + ( ( py3 ) * MapInfo[0] ) ] >= 100 ) && ( map1[ px1 + ( ( py3 ) * MapInfo[0] ) ] <= 119 ) )
		  || ( ( map1[ px1 + ( ( py3 ) * MapInfo[0] ) ] >= 200 ) && ( map1[ px1 + ( ( py3 ) * MapInfo[0] ) ] <= 219 ) )
		  || ( ( map1[ px2 + ( ( py3 ) * MapInfo[0] ) ] >= 100 ) && ( map1[ px2 + ( ( py3 ) * MapInfo[0] ) ] <= 119 ) )
		  || ( ( map1[ px2 + ( ( py3 ) * MapInfo[0] ) ] >= 200 ) && ( map1[ px2 + ( ( py3 ) * MapInfo[0] ) ] <= 219 ) ) )
		{
			/* 벆궕귆궰궔궯궫 */
			player[13] = 0;
			player[14] = -3;		/* 뿇돷 */
		}
		else
		{
			if ( item_up2() != -1 )	/* 귺귽긡?궸벆궕귆궰궔귡 */
			{
				player[1] = item_up2();
				player[13] = 0;
				player[14] = -3;
			}
		}
	}
	/* 됪뽋둖갂돷궸뛱궯궫 */
	if ( player[1] <= -14 )
	{
		if ( map_data[2] == 0 )		/* 긚긏깓?깑궢궶궋뤾뜃궼?긽?긙 */
		{
			if ( player[8] > 0 )			/* HP궕궇귡 */
			{
				if ( player[17] == 0 )	/* 뼰밎렄듩궕뼰궋 */
				{
					player[17] = 120;	/* 뼰밎렄듩 */
					player[8] = player[8] - 1;/* ?긽?긙 */
					se_wav( 1 );	/* ?긽?긙뚼됈돶 */
				}
				if ( player[8] > 0 )		/* HP궕궇귡 */
				{
					player[0] = player[15];	/* 깏긣깋귽댧뭫궸댷벍 */
					player[1] = player[16];
					wait_scl2( save_data[3] ,player[0], player[1] );	/* 댠?뽣귟 */

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

/* 뜺뺴뛀귉궻댷벍뵽믦 */
void CGpAct::idou_l()
{
	long px ;
	long py1 ;
	long py2 ;
	long bx ;
	long by ;

	long i;


	/* 뜞됷궻댧뭫 */
	/* player[29]돘긫긨릟궖뷅귂뺚맫 */
	px = ( player[0] + char_size[2] + player[29] ) / 32;
	py1 = ( MapInfo[1] - ( ( player[1] + 32 + ( char_size[1] / 2 )  ) / 32 ) );
	py2 = ( MapInfo[1] - ( ( player[1] + 32 + 5 ) / 32 ) ); 						/* 뫉귝귟괫긤긞긣뛼궋뤾룋귩뵽믦궥귡 */
	/* 됪뽋둖궼덇붥뤵궳뵽믦 */
	if ( player[1] >= ( MapInfo[3] - char_size[1] ) )
	{
		py1 = 0;
		py2 = 0;
	}

	/* 502궼궢궟뤵?501궼궢궟뭷 */
	/* 빮궸뻹귏궯궫뤾뜃궼빮띧궸댷벍 */
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
			/* 긵깒귽깂?궴궻뱰궫귟뵽믦 */
			if ( ( ( (item[1 + ( i * item_data[2] )]  ) < (player[0]  + player[29] + char_size[3] ) )	/* 렔?궴궻궇궫귟뵽믦 */
				&& ( (player[0] + player[29] + char_size[2] ) < (item[1 + ( i * item_data[2] )] + item_data[0] ) )
				&& ( (item[2 + ( i * item_data[2] )] ) < (player[1] + char_size[1] - 5 ) )
				&& ( (player[1] + 5 ) < ( item[2 + ( i * item_data[2] )] + item_data[0] ) ) ) )
			{
				if (
				     ( by == 3 ) /* 댷벍븉됀귺귽긡? */
				  || ( by == 6 ) /* 댷벍븉됀귺귽긡? */
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
/* 렔빁궻뜺덭궸댷벍됀?궔갎 */
void CGpAct::idou_r()
{
	long px ;
	long py1 ;
	long py2 ;
	long bx ;
	long by ;

	long i;

	/* 뜞됷궻댧뭫 */
	/* player[29]돘긫긨릟궖뷅귂뺚맫 */
	px = ( player[0] + char_size[3] + player[29] ) / 32;
	py1 = ( MapInfo[1] - ( ( player[1] + 32 + ( char_size[1] / 2 ) ) / 32 ) );
	py2 = ( MapInfo[1] - ( ( player[1] + 32 + 5 ) / 32 ) ); /* 뫉귝귟괫긤긞긣뛼궋뤾룋귩뵽믦궥귡 */
	/* 됪뽋둖궼덇붥뤵궳뵽믦 */
	if ( player[1] >= ( MapInfo[3] - char_size[1] ) )
	{
		py1 = 0;
		py2 = 0;
	}

	/* 502궼궢궟뤵?501궼궢궟뭷 */
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
			/* 긵깒귽깂?궴궻뱰궫귟뵽믦 */
			if ( ( ( (item[1 + ( i * item_data[2] )]  ) < (player[0] + player[29] + char_size[3] ) )	/* 렔?궴궻궇궫귟뵽믦 */
				&& ( (player[0] + player[29] + char_size[2] ) < (item[1 + ( i * item_data[2] )] + 32 ) )
				&& ( (item[2 + ( i * item_data[2] )] ) < (player[1] + char_size[1] - 5 ) )
				&& ( (player[1] + 5 ) < ( item[2 + ( i * item_data[2] )] + 32 ) ) ) )
			{
				if (
				     ( by == 3 ) /* 댷벍븉됀귺귽긡? */
				  || ( by == 6 ) /* 댷벍븉됀귺귽긡? */
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
		snack_counter_disp();		// 궓귘궰긇긂깛?
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
		snack_counter_disp(); // 궓귘궰긇긂깛?
		mapdisp();
		debugdisp();		/* 긢긫긞긐륃뺪 */
		stage_endj();

		break;

	case 2 :				// Stage Clear
		bakdisp1();
		bakdisp2();
		item_disp();


		item_line();
		g_pSprite->Begin();

		p_shot_f2_disp();

		snack_counter_disp(); // 궓귘궰긇긂깛?
		mapdisp();
		stage_claer();
		playerdisp();
		debugdisp();
		break;

	case 3 :		//긒??긆?긫?
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
		snack_counter_disp(); // 궓귘궰긇긂깛?
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
		snack_counter_disp(); // 궓귘궰긇긂깛?
		mapdisp();
		window_disp();
		debugdisp();
		break;

	case 5 :				// Rotation of Replay
		bak_rot();
		snack_counter_disp(); // 궓귘궰긇긂깛?
		mapdisp();
		debugdisp();		/* 긢긫긞긐륃뺪 */
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
		snack_counter_disp(); // 궓귘궰긇긂깛?
		mapdisp();
		debugdisp();		/* 긢긫긞긐륃뺪 */
		stage_endj();
		break;
	default :	//	궵궻륆뙊궸귖뼖궫궶궋뤾뜃

		/* 됪뽋먛귟뫶궑렄궻?렑뫮랉 */
		player[0] = next_px;
		player[1] = next_py;

		m_bExit = 0;
		break;
	}
}



/* 덇렄긲?귽깑뺎뫔 */
void CGpAct::save_file_w()
{
	long i;

	SaveGameFlag("save/config");


	ResetGameFlag2();
//	save_data[7] = player[7];	/* 긪?긣궻궔궚귞룋렃뙿릶 */
	save_data[5] = player[8];	/* HP */
	save_data[2] = stage;

	save_data[0] = player[0];	/* 굓 */
	save_data[1] = player[1];	/* 굕 */
	save_data[4] = player[3];	/* 뛀궖 */
//	save_data[8] = player[6];	/* 긚긌깑 */

	for ( i = 0; i < 512; ++i )
	{
		SetSceneGameFlag2(i, save_data[i] );
	}
	SaveGameFlag2( "save/work.sav");

	/* 귺귽긡?롦벦륃뺪 */
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
		/* 8긬??깛궳1긬??깛뽞궸뽣귡 */
		if ( player[11] >= char_size[4] )
		{
			player[11] = 0;
			if ( player[2] == 21 )	/* 뗴뭷 */
			{
				player[11] = ( char_size[4] - 1 - 3 );		/* 5궸뽣궥 */
			}
			if ( player[2] == 11 )	/* 뛘똼뢎뿹 */
			{
				player[2] = 0;
				if ( player[14] != 10 )	/* 뗴뭷 */
				{
					player[2] = 21;
				}
			}
			if ( player[2] == 31 )	/* ?긽?긙 */
			{
				player[2] = 0;
				if ( player[14] != 10 )	/* 뗴뭷 */
				{
					player[2] = 21;
				}
			}
			if ( player[2] == 32 )	/* ?긂깛긒??긆?긫? */
			{
				player[2] = 32;
				player[11] = ( char_size[4] - 1 );		/* 띍뢎긬??깛궻귏귏 */
			}
			if ( player[2] == 33 )	/* 긏깏귺 */
			{
				player[2] = 33;
				player[11] = ( char_size[4] - 1 - 3 );		/* 5궸뽣궥 */
			}
		}
	}

	fram_set();

	/* 됪뽋몜뫮띆뷭궳궻?렑댧뭫 */
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
	if ( player[18] > 0 )	/* 뭶뭤긾?긘깈깛?렑 */
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


	if ( player[2] == 1 )		/* 뺖궖 */
	{
		player[4] = 0;
		player[5] = 1;
	}
	if ( player[2] == 2 )		/* 궰궔귒 */
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
		if ( player[14] < 0 )	/* 뿇궭궲귡 */
		{
			player[5] = 7;
		}
	}
	if ( player[2] == 31 )	/* ?긽?긙 */
	{
		player[4] = 0;
		player[5] = 5;

	}
	if ( player[2] == 32 )	/* 긒??긆?긫? */
	{
		player[4] = 0;
		player[5] = 5;

	}
	if ( player[2] == 33 )	/* 긏깏귺 */
	{
		player[4] = 0;
		player[5] = 8;

	}

	if ( GetSceneGameFlag1(128) == 0 )	//?긞긵긮깄?궳궼궶궋
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

	//됪뽋봶똧귩됪뽋멣뫬궸?몭
	bak_cnt = bak_cnt + 1;
	if ( bak_cnt >= 40 )
	{
		bak_cnt = 0;
	}


	d_x = player[0] - dp_x2 + 16 ;

	d_y = ( MapInfo[3] - 240 ) + ( 120 - 16 ) - player[1];



	/* 봶똧귺긦긽?긘깈깛ON */

	int mapIdx = (save_data[3]+9)/10 -1;

	if(mapIdx<0)	mapIdx = 0;
	if(mapIdx>4)	mapIdx = 4;

	mapIdx += 110;

	Blt(m_vTex[mapIdx], 0, 0 );						/* 봶똧긚긏깓?깑뎶뢯 */
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

	/* stage13,14,17궼뫝뢣긚긏깓?깑 */
	/* 뭤뽋?렑 */
	for ( x = 0; x < MapInfo[1]; x++ )
	{
		for ( y = 0; y < MapInfo[1]; y++ )
		{

			if ( ( ( ( d_x - 32 ) <= ( x * 32 ) )
			  && ( ( d_y - 32 ) <= ( y * 32 ) )
			  && ( ( d_x + 320 + 32 ) >= ( x * 32 ) )
			  && ( ( d_y + 240 + 32 ) >= ( y * 32 ) ) )
			  || ( bak_alldrow == 1 )	 					/* 봶똧궻?됪귩긏깏긞긵궥귡궔 */
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
			  || ( bak_alldrow == 1 )	 					/* 봶똧궻?됪귩긏깏긞긵궥귡궔 */
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


	snack_counter_disp(); // 궓귘궰긇긂깛?
	mapdisp();
	debugdisp();		/* 긢긫긞긐륃뺪 */
	stage_endj();

	g_pSprite->End();
}




/* 굒?괿굎궰궖긚긏깓?깑 */
void CGpAct::wait_scl( long type, long d_num )
{
/*
	0:뤵	1:돷	2:뜺	3:덭
	귝귒궞귔긲?귽깑굆굈
*/
	long i;
	long x;
	long y;
	char	strbuf[260]={0};

	se_wav( 14 );
	screen_BackupPlane();

	/* 긫긞긲?긏깏귺 */
	for ( i = 0; i < 100; ++i )
	{
		p_ef[i * 5] = 0;						/* 뫔띪 */
	}
	for ( i = 0; i < 40; ++i )
	{
		pmshot[i * 20 + 2] = 0;						/* 뫔띪 */
	}
	for ( i = 0; i < 10; ++i )
	{
		pshot[i * 10 + 0] = 0 ;
	}
	for ( i = 0; i < 40; ++i )
	{
		pshotf[i * 10 + 0] = 0 ;
	}
	/* 긫긞긲?긏깏귺 */
	for ( i = 0; i < 50; ++i )
	{
		item[i * 10 + 0] = 0 ;
	}
	for ( i = 0; i < 20; ++i )
	{
		enemy[i * 20 + 0] = 0 ;					/* 뫔띪궢궲궶궋 */
	}
	for ( i = 0; i < 20; ++i )
	{
		mgc_e[i * 10 + 0] = 0 ;					/* 뫔띪궢궲궶궋 */
	}
	for ( i = 0; i < 20; ++i )
	{
		kane[i * 10 + 0] = 0 ;					/* 뫔띪궢궲궶궋 */
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
			LoadImage(&m_vTex[110 + i], strbuf, 0 );					//긵깒?깛긥깛긫?괧궸긘긚긡?뾭괶굃굊귩벶귒뜛귔
		}
		else
		{
			ReleaseImage(&m_vTex[110 + i]);
		}
	}



	/* 깒귽깂?괧 */
	ResetGameFlag2();
	sprintf(strbuf,"data/%d/%d_%d.map", (int)stage , (int)2, (int)d_num );
	if ( LoadGameFlag2(strbuf) == 0 )
	{
		for ( i = 0; i <= 319; ++i )
		{
			map2[i] = GetSceneGameFlag2(i);
		}
	}


	/* 귺귽긡?봹뭫 */
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


	ResetGameFlag2();				/* 긲?귽깑궶궢 */
	sprintf( strbuf,"data/%d/e%d_%d.map", (int)stage , (int)1, (int)d_num );
	LoadGameFlag2( strbuf );	/* 밎봹뭫 */
	/* 밎봹뭫 */
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

	/* 뤵긚긏깓?깑 */
	if ( type == 0 )
	{
		player[1] = 0;
	}
	/* 돷긚긏깓?깑 */
	if ( type == 1 )
	{
		player[1] = ( 480 - 32 - 16 );
	}
	/* 돘긚긏깓?깑 */
	if ( type == 3 )
	{
		player[0] = 0;
	}
	/* 돘긚긏깓?깑 */
	if ( type == 2 )
	{
		player[0] = ( 640 - 32 );
	}



	/* 깏긣깋귽뤾룋먠믦 */
	player[15] = player[0];
	player[16] = player[1];

	player[9] = 0;			/* 믉귪궳궋귡밎궼뤑궑귡 */

}

/* 굒?괿굎궰궖긚긏깓?깑 */
void CGpAct::wait_scl2( long d_num ,long init_x, long init_y )
{
/*
	0:뤵	1:돷	2:뜺	3:덭
	귝귒궞귔긲?귽깑굆굈
*/
	long i;
	long x;
	long y;
	char	strbuf[260]={0};

//	se_wav( 14 );
//	screen_BackupPlane();

	/* 긫긞긲?긏깏귺 */
	for ( i = 0; i < 100; ++i )
	{
		p_ef[i * 5] = 0;						/* 뫔띪 */
	}
	for ( i = 0; i < 40; ++i )
	{
		pmshot[i * 20 + 2] = 0;						/* 뫔띪 */
	}
	for ( i = 0; i < 10; ++i )
	{
		pshot[i * 10 + 0] = 0 ;
	}
	for ( i = 0; i < 40; ++i )
	{
		pshotf[i * 10 + 0] = 0 ;
	}
	/* 긫긞긲?긏깏귺 */
	for ( i = 0; i < 50; ++i )
	{
		item[i * 10 + 0] = 0 ;
	}
	for ( i = 0; i < 20; ++i )
	{
		enemy[i * 20 + 0] = 0 ;					/* 뫔띪궢궲궶궋 */
	}
	for ( i = 0; i < 20; ++i )
	{
		mgc_e[i * 10 + 0] = 0 ;					/* 뫔띪궢궲궶궋 */
	}
	for ( i = 0; i < 20; ++i )
	{
		kane[i * 10 + 0] = 0 ;					/* 뫔띪궢궲궶궋 */
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
			LoadImage(&m_vTex[110 + i], strbuf, 0 );					//긵깒?깛긥깛긫?괧궸긘긚긡?뾭괶굃굊귩벶귒뜛귔
		}
		else
		{
			ReleaseImage(&m_vTex[110 + i]);
		}
	}



	/* 깒귽깂?괧 */
	ResetGameFlag2();
	sprintf(strbuf,"data/%d/%d_%d.map", (int)stage , (int)2, (int)d_num );
	if ( LoadGameFlag2(strbuf) == 0 )
	{
		for ( i = 0; i <= 319; ++i )
		{
			map2[i] = GetSceneGameFlag2(i);
		}
	}


	/* 귺귽긡?봹뭫 */
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

	ResetGameFlag2();				/* 긲?귽깑궶궢 */
	sprintf( strbuf,"data/%d/e%d_%d.map", (int)stage , (int)1, (int)d_num );
	LoadGameFlag2( strbuf );	/* 밎봹뭫 */
	/* 밎봹뭫 */
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


	/* 깏긣깋귽뤾룋먠믦 */
	player[15] = player[0];
	player[16] = player[1];


}

/* 굒?괿굎궰궖긚긏깓?깑(reload먭뾭갂밎궻띋봹뭫귩뛱귦궶궋) */
void CGpAct::wait_scl3()
{
/*
	0:뤵	1:돷	2:뜺	3:덭
	귝귒궞귔긲?귽깑굆굈
*/
	long i;
	long x;
	long y;
	long d_num;
	char	strbuf[260]={0};

	d_num = save_data[3];


	/* 긫긞긲?긏깏귺 */
	for ( i = 0; i < 100; ++i )
	{
		p_ef[i * 10] = 0;						/* 뫔띪 */
	}
	for ( i = 0; i < 40; ++i )
	{
		pmshot[i * 20 + 2] = 0;						/* 뫔띪 */
	}
	for ( i = 0; i < 10; ++i )
	{
		pshot[i * 10 + 0] = 0 ;
	}
	for ( i = 0; i < 40; ++i )
	{
		pshotf[i * 10 + 0] = 0 ;
	}
	/* 긫긞긲?긏깏귺 */
	for ( i = 0; i < 50; ++i )
	{
		item[i * 10 + 0] = 0 ;
	}
	for ( i = 0; i < 20; ++i )
	{
		if ( enemy[0 + ( i * 20 )] == 1 )					/* 뫔띪궢궲궶궋 */
		{
			enemy[1 + ( i * 20 )] = enemy[14 + ( i * 20 )] ;					/* 뫔띪궢궲궶궋 */
			enemy[2 + ( i * 20 )] = enemy[15 + ( i * 20 )] ;					/* 뫔띪궢궲궶궋 */
		}
	}
	for ( i = 0; i < 20; ++i )
	{
		mgc_e[i * 10 + 0] = 0 ;					/* 뫔띪궢궲궶궋 */
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
			LoadImage(&m_vTex[110 + i], strbuf, 0 );					//긵깒?깛긥깛긫?괧궸긘긚긡?뾭괶굃굊귩벶귒뜛귔
		}
		else
		{
			ReleaseImage(&m_vTex[110 + i]);
		}
	}



	/* 깒귽깂?괧 */
	ResetGameFlag2();
	sprintf(strbuf,"data/%d/%d_%d.map", (int)stage , (int)2, (int)d_num );
	if ( LoadGameFlag2(strbuf) == 0 )
	{
		for ( i = 0; i <= 319; ++i )
		{
			map2[i] = GetSceneGameFlag2(i);
		}
	}


	/* 귺귽긡?봹뭫 */
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

	ResetGameFlag2();				/* 긲?귽깑궶궢 */
	sprintf( strbuf,"data/%d/e%d_%d.map", (int)stage , (int)1, (int)d_num );
	LoadGameFlag2( strbuf );	/* 밎봹뭫 */
	/* 밎봹뭫 */
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


	/* 깏긣깋귽뤾룋먠믦 */
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
	case 0:			// 댷벍뼰궢
	case 360:		// 댷벍뼰궢
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
	// 긵깒귽깂?궻띆뷭귩빾듂
	rotchange( player[0] + ( char_size[0] / 2 ), player[1] + ( char_size[1] / 2 ), rot, &wx, &wy );

	player[0] = wx - ( char_size[0] / 2 ) - 1;	//빮궸뻹귏궯궲궢귏궎궫귕뺚맫
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
			case 2:	// 뤵뺴뛀
			case 3:
			case 4:
				if ( item[7 + ( i * item_data[2] )] >= 0 )
				{
					k = item[7 + ( i * item_data[2] )];	// 럛?궻롦벦
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
			/* 밎궻긖귽긛롦벦 */
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
			if ( enemy[3 + ( i * enm_data[2] )] == 4 )	/* 4?긚 */
			{
				size = 32;
			}
			if ( enemy[3 + ( i * enm_data[2] )] == 5 )	/* 5?긚 */
			{
				size = 32;
			}
			if ( enemy[3 + ( i * enm_data[2] )] == 6 )	/* 6?긚 */
			{
				size = 32;
			}
			rotchange( enemy[( i * enm_data[2] ) + 1 ] + ( size / 2 ), enemy[( i * enm_data[2] ) + 2 ] + ( size / 2 ), rot, &wx, &wy );
			enemy[( i * enm_data[2] ) + 1 ] = wx - ( size / 2 );
			enemy[( i * enm_data[2] ) + 2 ] = wy - ( size / 2 );
		}
	}


	//긬?긡귻긏깑궻댷벍
	for ( i = 0; i < PARTICLE; ++i )
	{
		if( !pshotf2[i].bAv)
			continue;

		rotchange( ( pshotf2[i].psX >> 16 ) + 16, ( pshotf2[i].psY >> 16 ) + 16, rot, &wx, &wy );
		pshotf2[i].psX = wx << 16 ;	/* 룊딖댧뭫궻먠믦 */
		pshotf2[i].psY = wy << 16 ;
	}

#ifdef GP2X
	replay_time = replay_time + 15;
#endif

}

void CGpAct::rotchangemap( long x1, long y1, long deg, long *x2, long *y2 )
{
	long rad; // 됷?둷뱗(깋긙귺깛)

	long cx;
	long cy;

	long dx;
	long dy;

	long tmpX;
	long tmpY;


	rad = 360 - deg;

	cx = MapInfo[1] / 2; // ?긞긵궻뭷륲띆뷭(X)
	cy = MapInfo[1] / 2; // ?긞긵궻뭷륲띆뷭(Y)

	dx = x1 - cx; // 뭷륲궔귞궻떁뿣(X)
	dy = y1 - cy; // 뭷륲궔귞궻떁뿣(Y)

	tmpX = dx*funcCos(rad) - dy*funcSin(rad); // 됷?
	tmpY = dx*funcSin(rad) + dy*funcCos(rad);

	tmpX = tmpX + ( 1 << 15 );
	tmpY = tmpY + ( 1 << 15 );

	*x2 = ( cx + ( tmpX >> 16 ) ); // 뙰궻띆뷭궸긆긲긜긞긣궥귡
	*y2 = ( cy + ( tmpY >> 16 ) );

}

void CGpAct::rotchange( long x1, long y1, long deg, long *x2, long *y2 )
{
	long rad; // 됷?둷뱗(깋긙귺깛)

	long cx;
	long cy;

	long dx;
	long dy;

	long tmpX;
	long tmpY;

	rad = deg;

	cx = MapInfo[3] / 2; // ?긞긵궻뭷륲띆뷭(X)
	cy = MapInfo[3] / 2; // ?긞긵궻뭷륲띆뷭(Y)

	dx = x1 - cx; // 뭷륲궔귞궻떁뿣(X)
	dy = y1 - cy; // 뭷륲궔귞궻떁뿣(Y)

	tmpX = dx*funcCos(rad) - dy*funcSin(rad); // 됷?
	tmpY = dx*funcSin(rad) + dy*funcCos(rad);

	tmpX = tmpX + ( 1 << 15 );
	tmpY = tmpY + ( 1 << 15 );

	*x2 = ( cx + ( tmpX >> 16 ) ); // 뙰궻띆뷭궸긆긲긜긞긣궥귡
	*y2 = ( cy + ( tmpY >> 16 ) );

}


// 궓귘궰긇긂깛???렑
void CGpAct::snack_counter_disp()
{
	long px;
	long py;
	long x;
	long dx;
	long dy;
	long i;
	long old_count;
	// 궓귘궰긇긂깛긣

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
		//last one궻?렑
		player[30] = 180;
	}
	if ( ( old_count != snack_count ) && ( snack_count == 0 ) )
	{
		//last one궻?렑
		player[30] = 0;
	}
	// 뜺뤵
	px = 10;
	py = 18;
	// 빒럻긖귽긛
	dx = 10;
	dy = 8;
	// 'rest' 럄귟궓귘궰
	x = 0;


	BltRect(m_vTex[18], 105, 2+m_EpsY, 0, 72, 100, 8 );	/* replay */
	BltNumericImage2( snack_count, 2, 155, 2+m_EpsY, m_vTex[18], 0, 0, 10, 8 );
}


//?긦?긞긵궻?렑
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
	// 뜺뤵
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

	// 긵깒귽깂?
	x = px + 0      + ((player[0] / 32 + 0) * size);
	y = py + height - ((player[1] / 32 + 1) * size);
	BltRect(m_vTex[120], x, y, 127, 191, size, size );
	// 궓귘궰
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


//륃뺪?렑
void CGpAct::mapdisp()
{
	int stage_hosei;

	long wk;

	stage_hosei = 0;
	if ( stage == 2 )
	{
		stage_hosei = 50;
	}

	if ( GetSceneGameFlag1(128) != 0 )	//?긞긵긮깄?
	{
		BltRect(m_vTex[18], 10, 25+m_EpsY, 0, 136, 100, 8 * 1 );	/* mapview */
	}

	if ( GetSceneGameFlag1(132) == 1 )
	{
//		if ( stage != 0 )
//		{
//			BltRect(m_vTex[18], 10, 15, 0, 32, 100, 8 );	/* replay */
//		}

		/* 긌?볺쀍 */
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
		if ( GetSceneGameFlag1(127) == 1 )	//긣??깑귺?긞긏
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

		if ( GetSceneGameFlag1(127) == 1 )	//긣??깑귺?긞긏
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

		BltNumericImage( play_time[0], 2, 110, 230, m_vTex[18], 0, 0, 10, 8 );	/* 렄듩 */
		BltNumericImage( play_time[1], 2,  80, 230, m_vTex[18], 0, 0, 10, 8 );	/* 렄듩 */
		BltNumericImage( play_time[2], 2,  50, 230, m_vTex[18], 0, 0, 10, 8 );	/* 렄듩 */

		if ( GetSceneGameFlag1(127) == 1 )	//긣??깑귺?긞긏
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

	// 뺴뛀궻?렑
	BltRect(m_vTex[76], 280, 122, 0 + ( map_rot_info * 32 ), 0, 32, 32 );	/*  */

	//뒶맟뷼궻?렑
	BltRect(m_vTex[6], 240, 240 - 96, 0, 64 , 96, 96 );	/*  */
	if ( ( m_nSn == 1 ) || ( m_nSn == 5 ) || ( m_nSn == 4 ) )
	{
		if ( snack_count != all_snack_count )
		{
			BltRect(m_vTex[6], 240 + 32, 240 - 96 + 32, 0 + ( ( ( save_data[3] - 1 ) % 10 ) * 32 ), 160 + ( ( ( save_data[3] - 1 ) / 10 ) * 32 ) , 32 - ( ( snack_count * 100 ) / ( ( all_snack_count * 100 ) / 32 ) ), 32 );	/*  */
		}
	}

	//긇긞긣귽깛궻?렑
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



// se띋맯
void CGpAct::se_wav(long SeWavNo)
{

}



//둎럑
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

	if ( player[8] <= 0 )		/* 깋귽긲괥 */
	{

		player[2] = 32;	/* ?긂깛긾?긘깈깛 */
		player[10] = 0;	/* ?긂깛긾?긘깈깛 */
		player[11] = 0;	/* ?긂깛긾?긘깈깛 */

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

	if ( GetSceneGameFlag1(127) == 0 )	//긣??깑귺?긞긏
	{
		if ( ( GetSceneGameFlag1(300 + save_data[3] + stage_hosei) > Jump_counts ) )
		{
			if ( GetSceneGameFlag1(132) == 0 )
			{
				// 륷딯?
				Blt(m_vTex[74], 74, 18);
				Blt(m_vTex[69], 29, 188 );
				newrecode = 1;
			}
		}
		if ( ( GetSceneGameFlag1(200 + save_data[3] + stage_hosei) > play_time[4] ) )
		{
			if ( GetSceneGameFlag1(132) == 0 )
			{
				// 륷딯?
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
		//뽞뷭?귽?
		if ( target_save[200 + save_data[3] + stage_hosei] >= play_time[4] )
		{
			BltRect(m_vTex[61], 20, 138, 0, 128 , 20, 20 );
		}
		//뽞뷭됷?
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
			BltRect(m_vTex[18], 190, 170, 0, 176, 200, 8 );	/* ?귽? */
			BltRect(m_vTex[61], 20, 170, 0, 128 , 20, 20 );
		}
		else
		{
			BltRect(m_vTex[18], 190, 170, 0, 168, 200, 8 );	/* ?귽? */
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
	//뒶맟뷼궻롦벦1
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
			if ( GetSceneGameFlag1(127) == 1 )	//긣??깑귺?긞긏
			{
				SetSceneGameFlag1(135, play_time[4]);
			}
			else
			{
				replay_file_save_w();
				if ( GetSceneGameFlag1(200 + save_data[3] + stage_hosei) > play_time[4] )
				{
					SetSceneGameFlag1(200 + save_data[3] + stage_hosei, play_time[4]);	/* 긚긓귺뺎뫔 */

					replay_file_save( 0 );
				}

				if ( GetSceneGameFlag1(300 + save_data[3] + stage_hosei) > Jump_counts )
				{
					SetSceneGameFlag1(300 + save_data[3] + stage_hosei, Jump_counts);	/* 긚긓귺뺎뫔 */

					replay_file_save( 1 );
				}

				if ( secretitemget == 1 )
				{
					SetSceneGameFlag1(400 + save_data[3] + stage_hosei, 1);
				}
			}

			if ( GetSceneGameFlag1(129) != 0 )	//긚긡?긙긜깒긏긣궔귞둎럑
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
					if ( GetSceneGameFlag1(127) == 0 )	//긣??깑귺?긞긏궳궼궶궋
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
			if ( GetSceneGameFlag1(129) != 0 )	//긚긡?긙긜깒긏긣궔귞둎럑
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
			if ( ( GetSceneGameFlag1(124) == 1 ) || ( stage == 0 ) )	/* 깏긵깒귽굈굆괺 */
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
		if ( player[8] <= 0 )		/* 깋귽긲괥 */
		{
			long nState = GetSceneGameFlag1(136);
			++nState;
			SetSceneGameFlag1(136, nState);

			if ( GetSceneGameFlag1(136) > 999 )	/* ?긚긇긂깛긣 */
			{
				SetSceneGameFlag1(136, 999);
			}
		}
		if ( GetSceneGameFlag1(127) == 1 )	//긣??깑귺?긞긏
		{
			play_time[4] = 1000000 + ( play_time[2] * 10000 ) + ( play_time[1] * 100 ) + ( play_time[0] );
			SetSceneGameFlag1(135, play_time[4]);
		}

		SetSceneGameFlag1(71, 1);
		m_nSn = 10;
	}
}


/* ?긞긵궻?궸륢귢궲긚긡?긙댷벍 */
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
			pshot[( i * 10 ) + 3 ] = houkou;	/* 뜺덭 */
			pshot[( i * 10 ) + 4 ] = muki;	/* 뺴뛀 */
			pshot[( i * 10 ) + 5 ] = 0;
			pshot[( i * 10 ) + 6 ] = 0;
			pshot[( i * 10 ) + 7 ] = type;
			pshot[( i * 10 ) + 8 ] = 0;		/* 궇궫귟뵽믦띆뷭X */
			pshot[( i * 10 ) + 9 ] = 0;		/* 궇궫귟뵽믦띆뷭X */

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
			/* 댧뭫뺚맫 */
			pshot[( i * 10 ) + 1 ] = player[0];
			pshot[( i * 10 ) + 2 ] = player[1];

			if ( pshot[( i * 10 ) + 3 ] == 0 )
			{
				if ( pshot[( i * 10 ) + 4 ] == 0 )
				{
					pshot[( i * 10 ) + 1 ] = player[0] - 16;
					pshot[( i * 10 ) + 2 ] = player[1] + 16;
					pshot[( i * 10 ) + 8 ] = 0;		/* 궇궫귟뵽믦띆뷭X */
					pshot[( i * 10 ) + 9 ] = 0;		/* 궇궫귟뵽믦띆뷭X */
				}
				if ( pshot[( i * 10 ) + 4 ] == 1 )
				{
					pshot[( i * 10 ) + 1 ] = player[0] + 5;
					pshot[( i * 10 ) + 2 ] = player[1] + 10;
					pshot[( i * 10 ) + 8 ] = 0;		/* 궇궫귟뵽믦띆뷭X */
					pshot[( i * 10 ) + 9 ] = 0;		/* 궇궫귟뵽믦띆뷭X */
				}
				if ( pshot[( i * 10 ) + 4 ] == 2 )
				{
					pshot[( i * 10 ) + 1 ] = player[0] + 5;
					pshot[( i * 10 ) + 2 ] = player[1] - 16;
					pshot[( i * 10 ) + 8 ] = 0;		/* 궇궫귟뵽믦띆뷭X */
					pshot[( i * 10 ) + 9 ] = 0;		/* 궇궫귟뵽믦띆뷭X */
				}
				if ( pshot[( i * 10 ) + 4 ] == 3 )
				{
					pshot[( i * 10 ) + 1 ] = player[0] + 5;
					pshot[( i * 10 ) + 2 ] = player[1] - 43;
					pshot[( i * 10 ) + 8 ] = 0;		/* 궇궫귟뵽믦띆뷭X */
					pshot[( i * 10 ) + 9 ] = 0;		/* 궇궫귟뵽믦띆뷭X */
				}
				if ( pshot[( i * 10 ) + 4 ] == 4 )
				{
					pshot[( i * 10 ) + 1 ] = player[0] - 16;
					pshot[( i * 10 ) + 2 ] = player[1] - 43;
					pshot[( i * 10 ) + 8 ] = 0;		/* 궇궫귟뵽믦띆뷭X */
					pshot[( i * 10 ) + 9 ] = 0;		/* 궇궫귟뵽믦띆뷭X */
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
				pshotf2[ii].bAv = 0;				/* 뫔띪뼰궢 */
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
		//긚귽긞?궻?됪룈궼멟
		for ( i = 0; i < item_data[1]; ++i )
		{
			if ( item[( i * item_data[2] ) + 0 ] == 0 )
			{
				item[( i * item_data[2] ) + 0 ] = 1;
				item[( i * item_data[2] ) + 1 ] = x;
				item[( i * item_data[2] ) + 2 ] = y;
				item[( i * item_data[2] ) + 3 ] = type;
				item[( i * item_data[2] ) + 4 ] = 0;	// 럛?궔귞궻몜뫮댧뭫X
				item[( i * item_data[2] ) + 5 ] = 0;	// 럛?궔귞궻몜뫮댧뭫Y
				item[( i * item_data[2] ) + 6 ] = 0;	/* 댷벍긇긂깛? */
				item[( i * item_data[2] ) + 7 ] = -1;	/* 럛?궻?귽깛? */
				item[( i * item_data[2] ) + 8 ] = 0;	/* 댷벍쀊X */
				item[( i * item_data[2] ) + 9 ] = 0;	/* 댷벍쀊Y */
				item[( i * item_data[2] ) + 10 ] = -1;	/* 밎궻?귽깛? */


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
				item[( i * item_data[2] ) + 4 ] = 0;	// 럛?궔귞궻몜뫮댧뭫X
				item[( i * item_data[2] ) + 5 ] = 0;	// 럛?궔귞궻몜뫮댧뭫Y
				item[( i * item_data[2] ) + 6 ] = 0;	/* 댷벍긇긂깛? */
				item[( i * item_data[2] ) + 7 ] = -1;	/* 럛?궻?귽깛? */
				item[( i * item_data[2] ) + 8 ] = 0;	/* 댷벍쀊X */
				item[( i * item_data[2] ) + 9 ] = 0;	/* 댷벍쀊Y */
				item[( i * item_data[2] ) + 10 ] = -1;	/* 밎궻?귽깛? */


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
			  || ( bak_alldrow == 1 )	 					/* 봶똧궻?됪귩긏깏긞긵궥귡궔 */
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

			/* 긵깒귽깂?궴궻뱰궫귟뵽믦 */
			if ( ( ( (item[1 + ( i * item_data[2] )] + 0 ) <= (player[0] + char_size[3] ) )	/* 렔?궴궻궇궫귟뵽믦 */
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
					//돓궧귡긳깓긞긏
					//긌긿깋긏??궕뭤뽋궸궋귡
					if ( player[33] > 0 )
					{
						if ( ( player[14] == 10 ) && ( item[( i * item_data[2] ) + 4 ] == 10 ) )
						{
							/* 빮궣귗궶궔궯궫귞 */
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
						/* 빮궣귗궶궔궯궫귞 */
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
			if ( ( ( (item[1 + ( i * item_data[2] )] + 10 ) <= (player[0] + char_size[3] ) )	/* 렔?궴궻궇궫귟뵽믦 */
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
						player[2] = 2;		// 궰궔귒


						player[22] = 10;
						player[20] = player[21];
						//뤸궯궲궋귡귺귽긡?궸귝궯궲됷?뺴뛀귩뙂믦
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
					//뤵긫긨
					DGX_SoundPlay( m_pSndSe[EN_SE_JUMP] );
					/* 귺귽긡?궸뤸궯궲궋궶궋뤾뜃궼궩궞궕깏긣깋귽댧뭫 */
					if ( player[2] != 31 )
					{
						player[10] = 0;
						player[11] = 0;
						player[2] = 21;	/* 뗴뭷 */
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
					//돘긫긨
					DGX_SoundPlay( m_pSndSe[EN_SE_JUMP] );


					if ( ( by == 10 ) && ( bx == 4 ) )
					{
						player[29] = 20;	// 돘긫긨귅궖뷅귂쀍
					}
					else
					{
						player[29] = -20;	// 돘긫긨귅궖뷅귂쀍
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
				case 2:	// 뤵뺴뛀
				case 3:
				case 4:
					if ( item[( i * item_data[2] ) + 7 ] >= 0 )	// 럛?궕뫔띪궥귡
					{
						if ( item[6 + ( i * item_data[2] )] > 0 )
						{
							/* 긵깒귽깂?궴궻뱰궫귟뵽믦 */
							if ( ( ( (item[1 + ( i * item_data[2] )] + item[( i * item_data[2] ) + 8 ] ) <= (player[0] + char_size[3] ) )	/* 렔?궴궻궇궫귟뵽믦 */
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

							if ( item[6 + ( i * item_data[2] )] == 1 )	// 댷벍긲깒??릶궕믠?궻뤾뜃
							{
								k = item[7 + ( i * item_data[2] )];	// 럛?궻롦벦
								item[( i * item_data[2] ) + 1 ] = ( item[( k * item_data[2] ) + 1 ] + item[4 + ( i * item_data[2] )] ) ;
								item[( i * item_data[2] ) + 2 ] = ( item[( k * item_data[2] ) + 2 ] + item[5 + ( i * item_data[2] )] ) ;
								item[( i * item_data[2] ) + 6 ] = 0;
							}
							if ( item[( i * item_data[2] ) + 10 ] >= 0 )	// 밎궻?귽깛?궕뫔띪궥귡
							{
								k = item[10 + ( i * item_data[2] )];	// 럛?궻롦벦
								enemy[1 +( k * enm_data[2] )] = item[1 + ( i * item_data[2] )];
								enemy[2 +( k * enm_data[2] )] = item[2 + ( i * item_data[2] )];
							}
						}
					}
					else
					{
						if ( item[( i * item_data[2] ) + 7 ] == -1 )		// 룊됷뙚랊
						{
							//럛?귩뙚랊
							item[( i * item_data[2] ) + 7 ] = -2;	//뼰궢
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
											// 럛?궔귞궻몜뫮댧뭫귩뺎뫔
											item[( i * item_data[2] ) + 4 ] = item[( i * item_data[2] ) + 1 ] - item[( ii * item_data[2] ) + 1 ];	/* 벍띿뾭긫긞긲? */
											item[( i * item_data[2] ) + 5 ] = item[( i * item_data[2] ) + 2 ] - item[( ii * item_data[2] ) + 2 ];	/* 벍띿뾭긫긞긲? */
											item[( i * item_data[2] ) + 7 ] = ii;
										}
										break;
									default:
										break;
									}
									if ( item[( i * item_data[2] ) + 7 ] != -2 )
									{
										// 럛?궕뙥궰궔궯궫
										break;
									}
								}
							}
						}
						if ( by == 4 )	// 밎댷벍귺귽긡?
						{
							if ( item[( i * item_data[2] ) + 10 ] == -1 )		// 룊됷뙚랊
							{
								//럛?귩뙚랊
								item[( i * item_data[2] ) + 10 ] = -2;	//뼰궢
								for ( ii = 0; ii < enm_data[1]; ii++ )
								{
									if ( enemy[0 +( ii * enm_data[2] )] == 1 )
									{
										//벏궣띆뷭궸밎궕궋귡뤾뜃?귽깛?궻롦벦
										if (
										     ( enemy[1 +( ii * enm_data[2] )] == item[( i * item_data[2] ) + 1 ] )
										  && ( enemy[2 +( ii * enm_data[2] )] == item[( i * item_data[2] ) + 2 ] )
										   )
										{
											item[( i * item_data[2] ) + 10 ] = ii;	/* 벍띿뾭긫긞긲? */
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
						if ( GetSceneGameFlag1(128) == 0 )	//?긞긵긮깄?궳궼궶궋
						{
							//뵠
							item_jmp( i );
						}
					}
					break;
				case 5:
					// 긚귽긞?
					k = 0;
					if ( ( ( (item[1 + ( i * item_data[2] )] + 0 ) <= (player[0] + char_size[3] ) )	/* 렔?궴궻궇궫귟뵽믦 */
						&& ( (player[0] + char_size[2] ) < (item[1 + ( i * item_data[2] )] + item_data[0] - 0 ) )
						&& ( (item[2 + ( i * item_data[2] )]  + 0 ) < (player[1] + ( char_size[1] - 10 ) ) )
						&& ( (player[1] + 5 ) < ( item[2 + ( i * item_data[2] )] + item_data[0] - 0 ) ) )
						&& ( m_nSn == 1 ) )
					{
						// 긚귽긞?궕볺궯궲궋귡
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
									//뵠귩뙚랊궢궲뱰궫귟뵽믦귩뛱궎
									if ( ( ( (item[1 + ( i  * item_data[2] )] ) < ( item[1 + ( ii * item_data[2] )] + item_data[0] ) )	/* 렔?궴궻궇궫귟뵽믦 */
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
						// 긚귽긞?궕볺궯궲궋귡
						if ( item[4 + ( i * item_data[2] )] == 0 )
						{
							//멟됷궕돓궠귢궲궋궶궔궯궫
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
					//긚귽긞?궳뤑궑귡긳깓긞긏
					//긚귽긞?궕볺궯궲궋궶궋
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
									//긚귽긞?궕볺궯궲궋귡
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



/* 귺귽긡?궻굕띆뷭똶럁 */
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
		/* 뭤뽋뵽믦 */
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
			if ( item_up_Isitem( i ) != -1 )	/* 귺귽긡?궻뤵궸뤸궯궲궋귡 */
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
		/* 뭤뽋뵽믦 */
	}

	/* 됪뽋?궳뿇궭귡궻귩뻞? */
	if ( ( item[( i * item_data[2] ) + 1 ] < 0 ) || ( item[( i * item_data[2] ) + 1 ] > ( MapInfo[2] - 32 ) ) )
	{
		item[( i * item_data[2] ) + 4 ]  = 0;
	}
	/* 뜞됷궻댧뭫 */
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

	if ( item[( i * item_data[2] ) + 4 ]  <= 0 ) 													/* 뤵귟뭷궼뵽믦궢궶궋 */
	{
		/* 뭤뽋뵽믦 */
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
			if ( item_up_Isitem( i ) != -1 )	/* 귺귽긡?궻뤵궸뤸궯궲궋귡 */
			{
				item[( i * item_data[2] ) + 2 ] = item_up_Isitem( i );
				item[( i * item_data[2] ) + 4 ] = 10;
				return;
			}
		}
	}
	else		/* 뤵뤈뭷 */
	{
		/* 뭤뽋뵽믦 */
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


// 귺귽긡?벏럐궸멄귩
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
	harfsize = item_data[0] / 2;	// 뵾빁

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
			case 2:	// 뤵뺴뛀
			case 3:
			case 4:
				if ( item[7 + ( i * item_data[2] )] >= 0 )
				{
					k = item[7 + ( i * item_data[2] )];	// 럛?궻롦벦

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



//귺귽긡?궻뿇돷렄궸럊뾭
//릋볺븉됀귺귽긡?궕뫉뙰궸궇귡뤾뜃궼갂띆뷭귩뺅궥
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
			//렔빁궼뵽믦궢궶궋
			bx = item[3 + ( i * item_data[2] )] % 100 ;
			by = item[3 + ( i * item_data[2] )] / 100 ;

			if (
			     ( by == 2 )
			  || ( by == 3 )
			  || ( by == 6 )
			  || ( ( by == 10 ) && ( bx == 7 ) )
			   )
			{
				if ( ( ( (item[1 + ( i * item_data[2] )]  ) < ( px + item_data[0] - 5 ) )	/* 렔?궴궻궇궫귟뵽믦 */
					&& ( (px + 5) < (item[1 + ( i * item_data[2] )] + item_data[0] ) )
					&& ( (item[2 + ( i * item_data[2] )] + 27 ) < (py + 10 ) )
					&& ( (py - 1) < ( item[2 + ( i * item_data[2] )] + item_data[0] ) ) ) )
				{
					return( item[2 + ( i * item_data[2] )] + 32 );
				}
			}
		}
	}
	if ( ( ( (player[0] + 10  ) < ( px + item_data[0] ) )	/* 렔?궴궻궇궫귟뵽믦 */
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
				if ( ( ( (item[1 + ( i * item_data[2] )]  ) < (player[0] + 22 ) )	/* 렔?궴궻궇궫귟뵽믦 */
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
				if ( ( ( (item[1 + ( i * item_data[2] )]  ) < (player[0] + 22 ) )	/* 렔?궴궻궇궫귟뵽믦 */
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


/* 귺귽긡?궸뢣궶궯궲뤵궕돓궠귢궫렄궻귽긹깛긣 */
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

			/* 긵깒귽깂?궴궻뱰궫귟뵽믦 */
			if ( ( ( (item[1 + ( i * item_data[2] )]  ) < (player[0] + 22 ) )	/* 렔?궴궻궇궫귟뵽믦 */
				&& ( (player[0] + 10 ) < (item[1 + ( i * item_data[2] )] + 32 ) )
				&& ( (item[2 + ( i * item_data[2] )] ) < (player[1] + 32 ) )
				&& ( (player[1] + 5 ) < ( item[2 + ( i * item_data[2] )] + 32 ) ) )
				&& ( player[14] == 10 ) )
			{
				r_f = 1;
				player[18] = 0;	/* 뭶뭤긾?긘깈깛궴귌궯궫귞궔궢귺긦긽?긘깈깛궻됶룣 */

			}

			if ( ( r_f == 1 ) && ( item[( i * item_data[2] ) + 7 ] == 0 ) )
			{
				if ( ( item[( i * 10 ) + 3 ] >= 100 ) && ( item[( i * 10 ) + 3 ] <= 220 ) ) /* 듓붋 */
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


//밎띿맟
/* ?긞긵긲?귽깑궔귞맯맟궥귡뤾뜃 */
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
			enemy[6 + ( i * enm_data[2] )] = 0;				/* 귘귞귢긇긂깛? */
			enemy[7 + ( i * enm_data[2] )] = 0;				/* 댧뭫뺚맫 */
			enemy[8 + ( i * enm_data[2] )] = 0;				/* ?렑긬??깛 */
			enemy[9 + ( i * enm_data[2] )] = 0;				/* 뛀궖 */
			enemy[10+ ( i * enm_data[2] )] = 0;				/* ?렑굕 */
			enemy[11+ ( i * enm_data[2] )] = type;			/* 롰쀞 */
			enemy[12+ ( i * enm_data[2] )] = 0;				/* 긙긿깛긵긲깒??긇긂깛? */
			enemy[13+ ( i * enm_data[2] )] = 0;				/* 긙긿깛긵긇긂깛? */
			enemy[14+ ( i * enm_data[2] )] = x;				/* 띋봹뭫륃뺪X */
			enemy[15+ ( i * enm_data[2] )] = y;				/* 띋봹뭫륃뺪Y */
			enemy[16+ ( i * enm_data[2] )] = 0;				/* 뼰밎렄듩 */
			enemy[17+ ( i * enm_data[2] )] = 0;	/* ?긽?긙 */
			enemy[18+ ( i * enm_data[2] )] = 1;				/* 띋봹뭫귩뛱궎궔 */
			enemy[19+ ( i * enm_data[2] )] = 0;/* Gold */
			enemy[20+ ( i * enm_data[2] )] = 0;				/* 벍띿뾭긫긞긲? */
			enemy[21+ ( i * enm_data[2] )] = 0;				/* 벍띿뾭긫긞긲? */
			enemy[22+ ( i * enm_data[2] )] = 0;				/* 벍띿뾭긫긞긲? */
			enemy[23+ ( i * enm_data[2] )] = 0;				/* 벍띿뾭긫긞긲? */
			enemy[24+ ( i * enm_data[2] )] = 0;				/* 벍띿뾭긫긞긲? */
			enemy[25+ ( i * enm_data[2] )] = 0;				/* 벍띿뾭긫긞긲? */
			enemy[26+ ( i * enm_data[2] )] = 0;				/* 벍띿뾭긫긞긲? */
			enemy[27+ ( i * enm_data[2] )] = 0;				/* 벍띿뾭긫긞긲? */
			enemy[28+ ( i * enm_data[2] )] = 0;				/* 댷벍쀊X */
			enemy[29+ ( i * enm_data[2] )] = 0;				/* 댷벍쀊Y */

			if ( size != 4 )
			{
				all_snack_count++;
			}

			break;
		}
	}
}


//밎띿맟
/* 밎궔귞밎궕맯맟궠귢귡뤾뜃 */
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
			enemy[6 + ( i * enm_data[2] )] = 0;				/* 귘귞귢긇긂깛? */
			enemy[7 + ( i * enm_data[2] )] = 0;				/* 댧뭫뺚맫 */
			enemy[8 + ( i * enm_data[2] )] = 0;				/* ?렑긬??깛 */
			enemy[9 + ( i * enm_data[2] )] = muki;			/* 뛀궖 */
			enemy[10+ ( i * enm_data[2] )] = 0;				/* ?렑굕 */
			enemy[11+ ( i * enm_data[2] )] = type;			/* 롰쀞 */
			enemy[12+ ( i * enm_data[2] )] = 0;				/* 긙긿깛긵긲깒??긇긂깛? */
			enemy[13+ ( i * enm_data[2] )] = 0;				/* 긙긿깛긵긇긂깛? */
			enemy[14+ ( i * enm_data[2] )] = x;				/* 띋봹뭫륃뺪X */
			enemy[15+ ( i * enm_data[2] )] = y;				/* 띋봹뭫륃뺪Y */
			enemy[16+ ( i * enm_data[2] )] = 0;				/* 뼰밎렄듩 */
			enemy[17+ ( i * enm_data[2] )] = 0;	/* ?긽?긙 */
			enemy[18+ ( i * enm_data[2] )] = 0;				/* 띋봹뭫귩뛱궎궔 */
			enemy[19+ ( i * enm_data[2] )] = 0;/* Gold */
			enemy[20+ ( i * enm_data[2] )] = 0;				/* 벍띿뾭긫긞긲? */
			enemy[21+ ( i * enm_data[2] )] = 0;				/* 벍띿뾭긫긞긲? */
			enemy[22+ ( i * enm_data[2] )] = 0;				/* 벍띿뾭긫긞긲? */
			enemy[23+ ( i * enm_data[2] )] = 0;				/* 벍띿뾭긫긞긲? */
			enemy[24+ ( i * enm_data[2] )] = 0;				/* 벍띿뾭긫긞긲? */
			enemy[25+ ( i * enm_data[2] )] = 0;				/* 벍띿뾭긫긞긲? */
			enemy[26+ ( i * enm_data[2] )] = 0;				/* 벍띿뾭긫긞긲? */
			enemy[27+ ( i * enm_data[2] )] = 0;				/* 벍띿뾭긫긞긲? */
			enemy[28+ ( i * enm_data[2] )] = 0;				/* 벍띿뾭긫긞긲? */
			enemy[29+ ( i * enm_data[2] )] = 0;				/* 벍띿뾭긫긞긲? */

			break;
		}
	}
}



/* 밎궻괾굊귩먠믦걁e_set궳럊귦귢귡걂 */
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
	p_h = 32;	/* 긵깒귽깂?궻뱰궫귟뵽믦 */
	all = 1;
	size = 0;
	akt_size2 = 0;

	for ( i = 0; i < enm_data[1]; ++i )
	{
		if ( enemy[0 +( i * enm_data[2] )] == 1 )
		{
			if ( enemy[3 + ( i * enm_data[2] )] != 4 )	/* 4?긚 */
			{
				isclaer = 1;
			}
			all = 0;
			/* 뼰밎렄듩궕뫔띪궥귡뤾뜃궼긇긂깛긣 */
			if ( enemy[16 + ( i * enm_data[2] )] > 0 )
			{
				enemy[16 + ( i * enm_data[2] )]--;
			}

			/* 밎궻긖귽긛롦벦 */
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
			if ( enemy[3 + ( i * enm_data[2] )] == 4 )	/* 4?긚 */
			{
				size = 32;
			}
			if ( enemy[3 + ( i * enm_data[2] )] == 5 )	/* 5?긚 */
			{
				size = 32;
			}
			if ( enemy[3 + ( i * enm_data[2] )] == 6 )	/* 6?긚 */
			{
				size = 32;
			}

			size_hosei_x = 5;
			size_hosei_y = 10;

			/* 됪뽋볙궻밎궬궚?됪궥귡 */
			disp_x_j = enemy[1 + ( i * enm_data[2] )];
			disp_y_j = ( 0 - enemy[2 + ( i * enm_data[2] )] ) + MapInfo[3];

			if ( ( ( ( d_x - size ) <= ( disp_x_j ) )
			  && ( ( d_y - size ) <= ( disp_y_j  ) )
			  && ( ( d_x + 320 + size ) >= ( disp_x_j ) )
			  && ( ( d_y + 240 + size ) >= ( disp_y_j ) ) )
			  || ( bak_alldrow == 1 )	 					/* 봶똧궻?됪귩긏깏긞긵궥귡궔 */
			   )
			{

				if ( enemy[6 + ( i * enm_data[2] )] > 0 )	/* 귘귞귢 */
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
						if ( enemy[3 + ( i * enm_data[2] )] == 4 )	//덨궢귺귽긡?
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

			/* 됪뽋볙궻밎궬궚?됪궥귡 */
			if ( ( ( d_x - 320 - 64 ) <= ( disp_x_j ) )
			  && ( ( d_y - 240 - 64 ) <= ( disp_y_j  ) )
			  && ( ( d_x + 640 + 64 ) >= ( disp_x_j ) )
			  && ( ( d_y + 480 + 64 ) >= ( disp_y_j ) ) )
			{
				e_move( i );	/* 밎긌긿깋롰쀞빶벍띿 */
			}

			/* ?긚궼됪뽋둖귉댷벍궢궶궋 */
#if FALSE
			if ( enemy[3 + ( i * enm_data[2] )] >= 4 )	/* 5?긚 */
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
			/* 됪뽋둖귉댷벍궢궫뤾뜃궼뤑땸 */
			if ( ( enemy[1 + ( i * enm_data[2] )] >= ( MapInfo[2] + size ) )
			  || ( enemy[1 + ( i * enm_data[2] )] <= ( 0 - size ) )
			  || ( enemy[2 + ( i * enm_data[2] )] <= ( 0 - size ) )
			  || ( enemy[2 + ( i * enm_data[2] )] >= ( MapInfo[3] + size ) ) )
			{
			}

			/* 긵깒귽깂?궴궻뱰궫귟뵽믦 */
			if ( ( ( (enemy[1 + i * enm_data[2]] + size_hosei_x ) < (player[0] + char_size[3] ) )	/* 렔?궴궻궇궫귟뵽믦 */
				&& ( (player[0] + char_size[2] ) < (enemy[1 + i * enm_data[2]] + size - size_hosei_x ) )
				&& ( (enemy[2 + i * enm_data[2]] + size_hosei_y ) < (player[1] + p_h) )
				&& ( (player[1] + 5 ) < ( enemy[2 + i * enm_data[2]] + size - size_hosei_y - 10 ) ) )
				&& ( player[17] == 0 ) 					/* 뼰밎렄듩궕뼰궋 */
				&& ( enemy[6 + i * enm_data[2]] == 0 ) )			/* 밎궻뼰밎렄듩궕궶궋 */
			{
				if ( GetSceneGameFlag1(128) == 0 )	//?긞긵긮깄?궳궼궶궋
				{
					if ( enemy[3 + ( i * enm_data[2] )] == 4 )
					{
						if ( snack_count == 1 )
						{
							enemy[0 + i * enm_data[2]] = 0;		/* 뤑땸 */
							DGX_SoundPlay( m_pSndSe[EN_SE_L1] );
							p_shot_f2_set( ( enemy[1 + i * enm_data[2]] ) , ( enemy[2 + i * enm_data[2]] ), 0 );
							p_shot_f_set( 160 ,120, enemy[11 + i * enm_data[2]] );
							player[24] = 180;
							player[31] = 70; //긇긞긣귽깛
							player[32] = ( rand() % 3 ); //긇긞긣귽깛
							secretitemget = 1;						/* 덨궢귺귽긡?궻롦벦 */
						}
					}
					else
					{
						enemy[0 + i * enm_data[2]] = 0;		/* 뤑땸 */
						DGX_SoundPlay( m_pSndSe[EN_SE_L1] );

						p_shot_f2_set( ( enemy[1 + i * enm_data[2]] ) , ( enemy[2 + i * enm_data[2]] ), 0 );
						p_shot_f_set( 160 ,120, enemy[11 + i * enm_data[2]] );
						player[31] = 70; //긇긞긣귽깛
						player[32] = ( rand() % 3 ); //긇긞긣귽깛
					}
				}
			}

			/* ?궧궶궋벫빶궶밎걁릌뱳걂 */

//			if (
//			     ( ( enemy[11 + i * enm_data[2]] == 406 ) && ( ( enemy[8+ ( i * enm_data[2] )] == 1 ) || ( enemy[8+ ( i * enm_data[2] )] == 2 ) ) )		/* 6?긚 */
//			   )
//			{
//			}
//			else
			{
				/* 밎궴긆긳긙긃긏긣궻뱰궫귟뵽믦 */
				for ( k = 0; k < 40 ; k++ )
				{
					/* 긆긳긙긃긏긣궻긖귽긛 */
					size2 = 32;
					/* 긵깒귽깂?궻뭙궴궻뱰궫귟뵽믦 */
					if ( ( ( ( enemy[1 + i * enm_data[2]] + size_hosei_x ) < ( ( pmshot[5 + k * 20] >> 16 ) + size2 ) )
						&& ( ( ( pmshot[5 + k * 20] >> 16 ) + akt_size2 ) < ( enemy[1 + i * enm_data[2]] + size - size_hosei_x  ) )
						&& ( ( enemy[2 + i * enm_data[2]] + size_hosei_y ) < ( ( pmshot[6 + k * 20] >> 16 ) + size2 ) )
						&& ( ( ( pmshot[6 + k * 20] >> 16 ) + akt_size2 ) < ( enemy[2 + i * enm_data[2]] + size - size_hosei_y - 10  ) ) )
						&& ( pmshot[2 + k * 20] == 1 ) )
					{
						/* 뼰밎렄듩궕뫔띪궢궶궋 */
						if ( enemy[16 + ( i * enm_data[2] )] == 0 )
						{
							/* 뛘똼궕뚼궔궶궋벫빶궶밎 */
#if FALSE
							if (
							     ( ( enemy[11 + ( i * enm_data[2] )] == 114 ) && ( enemy[ 9 + ( i * enm_data[2] )] == 1 ) && ( pmshot[3 + k * 20] == 2 ) )	/* 긓긖긏깛 */
							  || ( ( enemy[11 + ( i * enm_data[2] )] == 114 ) && ( enemy[ 9 + ( i * enm_data[2] )] == 0 ) && ( pmshot[3 + k * 20] == 3 ) )	/* 긓긖긏깛 */
							  || ( ( enemy[11 + ( i * enm_data[2] )] == 114 ) && ( pmshot[3 + k * 20] == 1 ) )	/* 긓긖긏깛 */
							  || ( ( enemy[11 + ( i * enm_data[2] )] == 112 ) && ( enemy[8 + ( i * enm_data[2] )] == 0 ) )	/* 귺?깛 */
							  || ( ( enemy[11 + ( i * enm_data[2] )] == 112 ) && ( enemy[8 + ( i * enm_data[2] )] == 1 ) )	/* 귺?깛 */
							   )
							{
								pmshot[2 + k * 20] = 0;		/* 뭙뤑땸 */
								se_wav( 2 );
								/* 돷뛘똼궻뤾뜃궼긙긿깛긵 */
								if ( pmshot[3 + k * 20] == 1 )
								{
									/* 궼궺귡 */
									player[10] = 0;			/* 귺긦긽?긘깈깛긲깒??긇긂깛?궻긏깏귺 */
									player[11] = 0;			/* 귺긦긽?긘깈깛긇긂깛?궻긏깏귺 */
									player[2] = 21;			/* 뗴뭷륉뫴 */

									player[14] = 5;			/* 긙긿깛긵쀍궻먠믦갂궞귢궸귝궯궲뛼궠궕빾귦귡 1?9 */
									player[13] = 0;			/* 긙긿깛긵긲깒??긇긂깛?궻긏깏귺 */
			//						player[25] = 1;			/* ??깛귩돓궢궲긙긿깛긵궢궫긲깋긐 */
								}
							}
							else
							{
								/* 뛘똼긭긞긣뚼됈궻?렑귩봹뭫 */
								p_shot_f_set( ( pmshot[5 + k * 20] >> 16 ) , ( pmshot[6 + k * 20] >> 16 ), 0 );

								/* 밎HP귩뙵룺 */
								enemy[5 + ( i * enm_data[2] )] = enemy[5 + ( i * enm_data[2] )] - 1;

								/* 뛀궖먠믦 */
								if ( enemy[3 + ( i * enm_data[2] )] < 4 )	/* 4?긚궼빾귦귞궶궋 */
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

//								pmshot[2 + k * 20] = 0;				/* 뭙뤑땸 */
								if ( enemy[5 + ( i * enm_data[2] )] <= 0 )		/* ?궢궫 */
								{

									/* ?궢궫띧궻귽긹깛긣귩렳뛱 */
									/* ?긚댥둖궳귖뛱궎뤾뜃궼궞궞궻뵽뭚빒귩믁돿 */
									if ( enemy[3 + ( i * enm_data[2] )] >= 4 )	/* 4?긚 */
									{
										enemy[16 + ( i * enm_data[2] )] = 59;	/* 뼰밎렄듩궻먠믦 */
//										boss_dead( enemy[1 + ( i * enm_data[2] )], enemy[2 + ( i * enm_data[2] )], i );
//										event_set_enm( enemy[11 + ( i * enm_data[2] )] , i );
#if FALSE
										for ( l = 0; l < enm_data[1]; l++ )
										{
											enemy[5 + ( l * enm_data[2] )] = 0;
											enemy[6 + ( l * enm_data[2] )] = 60;		/* 뤑땸 */
											enemy[16 + ( l * enm_data[2] )] = 60;
										}
#endif
									}

									p_shot_f2_set( ( pmshot[5 + k * 20] >> 16 ) - 4, ( pmshot[6 + k * 20] >> 16 ) + 4, 0 );
									enemy[6 + ( i * enm_data[2] )] = 30;		/* ?긽?긙궘귞궋긾?긘깈깛?렑긲깒??릶 */
									enemy[16 + ( i * enm_data[2] )] = 60;	/* 뼰밎렄듩궻먠믦 */
									se_wav( 5 );
								}
								else
								{
									/* ?궢궲궶궋 */
									/* 뼰밎렄듩먠믦 */
									enemy[6 + ( i * enm_data[2] )] = 30;		/* 궻궚궪귟렄듩 */
									enemy[7 + ( i * enm_data[2] )] = 6;		/* 댧뭫뺚맫 */
									enemy[16 + ( i * enm_data[2] )] = 60;	/* 뼰밎렄듩 */
									se_wav( 4 );
									if ( enemy[3 + ( i * enm_data[2] )] >= 4 )	/* ?긚궻궴궖궼궻궚궪귟궕궶궋 */
									{
										enemy[6 + ( i * enm_data[2] )] = 0;		/* 궻궚궪귟렄듩 */
										enemy[7 + ( i * enm_data[2] )] = 0;		/* 댧뭫뺚맫 */
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
				enemy[7 + ( i * enm_data[2] )]--;					/* 댷벍뺚맫 */
				/* 빮궸뻹귏귞궶궋귝궎궸뵽믦 */
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

			/* ?긽?긙궘귞궋긾?긘깈깛 */
			if ( enemy[6 + ( i * enm_data[2] )] > 0 )
			{
				enemy[6 + ( i * enm_data[2] )]--;					/* 뤑궑귡귏궳긇긂깛? */
				if ( enemy[6 + ( i * enm_data[2] )] == 0 )
				{
					if ( enemy[5 + ( i * enm_data[2] )] <= 0 )		/* HP궕뼰궋뤾뜃 */
					{
						if ( enemy[3 + ( i * enm_data[2] )] >= 4 )	/* ?긚 */
						{
							se_wav( 18 );				/* ?긚귩?궢궫뚼됈돶 */

						}
						else
						{
#if FALSE
							if ( Rand( 5 ) == 0 )	/* 깋귽긲뢯뙸 */
							{
								se_wav( 7 );
								kane_set( enemy[1 + ( i * enm_data[2] )] + ( ( size / 2 ) - 16 ), enemy[2 + ( i * enm_data[2] )] , 0, enemy[19+ ( i * enm_data[2] )] );
							}
							else
							{
								se_wav( 7 );
								kane_set( enemy[1 + ( i * enm_data[2] )] + ( ( size / 2 ) - 16 ), enemy[2 + ( i * enm_data[2] )] , 1, enemy[19+ ( i * enm_data[2] )] );
							}
							/* 됪뽋둖궻뤾뜃궸띋봹뭫귩뛱궎 */
							if ( enemy[18 + ( i * enm_data[2] )] == 1 )
							{
								set_enmreset_tbl( enemy[14 + ( i * enm_data[2] )], enemy[15 + ( i * enm_data[2] )], enemy[11 + ( i * enm_data[2] )] );
							}
#endif
						}
						enemy[0 + ( i * enm_data[2] )] = 0;		/* 뤑땸 */

					}
				}
			}
		}
	}


	if ( ( isclaer == 0 ) )	/* ?긚궢궲궴궯궲귖긏깏귺 */
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
	if ( enemy[5 + ( i * enm_data[2] )] <= 0 )	/* ?궢궫 */
	{
		return;
	}

	enemy[8 + ( i * enm_data[2] )] = map_rot_info;		/* 귺긦긽?긘깈깛긬??깛 */
	enemy[9 + ( i * enm_data[2] )] = 0;		/* 귺긦긽?긘깈깛긬??깛 */
	enemy[14 + ( i * enm_data[2] )] = 0;

}



/* 밎긘깈긞긣맯맟 */

/* 긘깈긞긣댷벍 */
void CGpAct::e_shot_disp()
{
	long i;
	long p_h;
	long size ;

	p_h = 22;	/* 긵깒귽깂?궻뱰궫귟뵽믦 */
	size = 0;

	/* 뵯맯댧뭫X */
	/* 뵯맯댧뭫Y */
	for ( i = 0; i < 20; ++i )
	{
		if ( mgc_e[i * 10 + 0] == 1 )					/* 뫔띪궢궲궋귡 */
		{
			if ( mgc_e[i * 10 + 9] == 4010 ) 	/* 괦?긚 */
			{
				size = 32;
				BltRect(m_vTex[50], ( mgc_e[i * 10 + 1] >> 16 ) - d_x , ( 0 - ( mgc_e[i * 10 + 2] >> 16 ) ) + 480 - 32 - d_y, mgc_e[i * 10 + 3] * 32, 0 , 32, 32 );
				mgc_e[i * 10 + 1] = mgc_e[i * 10 + 1] + mgc_e[i * 10 + 4];		/* X */
				mgc_e[i * 10 + 2] = mgc_e[i * 10 + 2] + mgc_e[i * 10 + 5];		/* Y */
				mgc_e[i * 10 + 3]++;					/* 귺긦긽?긘깈깛긇긂깛? */
				if ( mgc_e[i * 10 + 3] >= 4 )
				{
					mgc_e[i * 10 + 3] = 0;
				}
			}

			/* 긵깒귽깂?궴궻뱰궫귟뵽믦 */
			if ( ( ( ( ( mgc_e[1 + i * 10] >> 16 ) ) < (player[0] + 22 ) )	/* 렔?궴궻궇궫귟뵽믦 */
				&& ( (player[0] + 10 ) < ( ( mgc_e[1 + i * 10] >> 16 ) + size ) )
				&& ( ( ( mgc_e[2 + i * 10] >> 16 ) ) < (player[1] + p_h) )
				&& ( (player[1] + 5  ) < ( ( mgc_e[2 + i * 10] >> 16 ) + size ) ) )
				&& ( player[17] == 0 ) )
			{
				player[10] = 0;
				player[11] = 0;
				player[12] = 4;
				player[13] = 0;
				player[2] = 31;	/* ?긽?긙 */
				player[17] = 120;	/* 뼰밎렄듩 */
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


/* 밎뾭긙긿깛긵 */
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
		/* 뜞됷궻댧뭫 */
		px = ( enemy[1 + ( i * 20 )] + 32 ) / 32;
		px1 = ( enemy[1 + ( i * 20 )] + size ) / 32;
		px2 = ( enemy[1 + ( i * 20 )] + size ) / 32;
		py = ( 16 - ( ( enemy[2 + ( i * 20 )] + 28 ) / 32 ) );
		/* 100 ? 200궼뭤뽋 */
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
		/* 뭤뽋뵽믦 */
	}


	/* 됪뽋?궳뿇궭귡궻귩뻞? */
	e10 = enemy[13 + ( i * 20 )];
	if (  enemy[1+ ( i * 20 )] > ( 630 - size - size ) )
	{
		if ( enemy[13+ ( i * 20 )] < 0 )	/* 뿇돷 */
		{
			e10 = 0;
		}
	}


	/* 뜞됷궻댧뭫 */
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

	if ( enemy[13 + ( i * 20 )] <= 0 )													/* 뤵귟뭷궼뵽믦궢궶궋 */
	{
		/* 뭤뽋뵽믦 */
		if ( ( ( map1[ px1 + ( ( py ) * 20 ) ] >= 100 ) && ( map1[ px1 + ( ( py ) * 20 ) ] <= 119 ) )
		  || ( ( map1[ px1 + ( ( py ) * 20 ) ] >= 200 ) && ( map1[ px1 + ( ( py ) * 20 ) ] <= 219 ) )
		  || ( ( map1[ px1 + ( ( py ) * 20 ) ] >= 600 ) && ( map1[ px1 + ( ( py ) * 20 ) ] <= 619 ) )
		  || ( ( map1[ px2 + ( ( py ) * 20 ) ] >= 600 ) && ( map1[ px2 + ( ( py ) * 20 ) ] <= 619 ) ) )
		{
			enemy[2 + ( i * 20 )] = ( ( 16 - py ) * 32 ) - 16;
			enemy[13 + ( i * 20 )] = 10;
		}
	}
	else		/* 뤵뤈뭷 */
	{
		if ( enemy[1+ ( i * 20 )] < ( 630 - size - size ) )
		{
			px = ( enemy[1 + ( i * 20 )] + size ) / 32;
			py = ( 16 - ( ( enemy[2 + ( i * 20 )] - ( y1 / 25 ) + 16 + 48  ) / 32 ) );

			/* 뭤뽋뵽믦 */
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


/* 댷벍뚣궻띆뷭궻?긚귩뺅궥 */
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

	/* 귺귽긡?궴궻궇궫귟뵽믦 */
	for ( i = 0; i < item_data[1]; ++i )
	{
		if ( item[( i * item_data[2] ) + 0 ] == 1 )
		{
			bx = item[3 + ( i * item_data[2] )] % 100 ;
			by = item[3 + ( i * item_data[2] )] / 100 ;
			/* 긵깒귽깂?궴궻뱰궫귟뵽믦 */
			if ( ( ( (item[1 + ( i * item_data[2] )]  ) < ( x ) )	/* 렔?궴궻궇궫귟뵽믦 */
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

	/* 귺귽긡?궴궻궇궫귟뵽믦 */
	for ( i = 0; i < item_data[1]; ++i )
	{
		if ( ( item[( i * item_data[2] ) + 0 ] == 1 ) && ( item_index != i ) )
		{
			bx = item[3 + ( i * item_data[2] )] % 100 ;
			by = item[3 + ( i * item_data[2] )] / 100 ;
			/* 긵깒귽깂?궴궻뱰궫귟뵽믦 */
			if ( ( ( (item[1 + ( i * item_data[2] )]  ) < ( x ) )	/* 렔?궴궻궇궫귟뵽믦 */
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
			/* 궴궯궫 */
			if ( ( ( (kane[1 + ( i * 10 )]  ) < (player[0] + 10 ) )	/* 렔?궴궻궇궫귟뵽믦 */
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


/* 긙긿깛긵굕댧뭫똶럁 */
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
		/* 뭤뽋뵽믦 */
	}

	/* 됪뽋?궳뿇궭귡궻귩뻞? */
	if ( ( kane[1 + ( i * 10 )] < 0 ) || ( kane[1 + ( i * 10 )] > 610 ) )
	{
		kane[6 + ( i * 10 )] = 0;
	}
	/* 뜞됷궻댧뭫 */
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

	if ( kane[6 + ( i * 10 )] <= 0 ) 													/* 뤵귟뭷궼뵽믦궢궶궋 */
	{
		/* 뭤뽋뵽믦 */
		if ( ( ( map1[ px1 + ( ( py ) * 20 ) ] >= 100 ) && ( map1[ px1 + ( ( py ) * 20 ) ] <= 299 ) )
		  || ( ( map1[ px2 + ( ( py ) * 20 ) ] >= 100 ) && ( map1[ px2 + ( ( py ) * 20 ) ] <= 299 ) )
		  || ( ( map1[ px1 + ( ( py ) * 20 ) ] >= 600 ) && ( map1[ px1 + ( ( py ) * 20 ) ] <= 619 ) )
		  || ( ( map1[ px2 + ( ( py ) * 20 ) ] >= 600 ) && ( map1[ px2 + ( ( py ) * 20 ) ] <= 619 ) ) )
		{
			kane[2 + ( i * 10 )] = ( ( 16 - py ) * 32 ) - 16;
			kane[6 + ( i * 10 )] = 10;
		}
	}
	else		/* 뤵뤈뭷 */
	{
		/* 뭤뽋뵽믦 */
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


/* 긽긦깄?궻?렑 */
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
		if ( player[9] != 0 ) //됷?뭷
		{
			m_nSn = 5;
		}
		else
		{
			m_nSn = 1;
		}
	}

}


/* ?긞긵긮깄?궳궻긌??띿 */
void CGpAct::mapview_keys()
{
	if ( g_pApp->IsPressKey( DGXKEY_UP ) )	//뤵?
	{
		player[1] = player[1] + 2;
	}
	if ( g_pApp->IsPressKey( DGXKEY_DOWN ) )	//돷?
	{
		player[1] = player[1] - 2;
	}
	if ( g_pApp->IsPressKey( DGXKEY_LEFT ) )	//뜺?
	{
		player[0] = player[0] - 2;
	}
	if ( g_pApp->IsPressKey( DGXKEY_RIGHT ) )	//덭?
	{
		player[0] = player[0] + 2;
	}

	if ( player[0] < 0 )	/* 됪뽋뜺?뵽믦 */
	{
		player[0] = 0;
	}
	if ( player[0] > ( MapInfo[2] - char_size[0] ) )	/* 됪뽋덭?뵽믦 */
	{
		player[0] =  MapInfo[2] - char_size[0];
	}
	if ( player[1] <= 0 )	/* 됪뽋돷 */
	{
		player[1] = 0;
	}
	if ( player[1] >= ( MapInfo[3] - char_size[1] ) )	/* 됪뽋뤵 */
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


/* 먥뫮뭠귩뺅궥 */
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

/* 뻷?맯맟 */
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

	/* 뵯맯댧뭫X */
	/* 뵯맯댧뭫Y */

	max = 1;
	for ( i = 0; i < max; ++i )
	{

		k = 5;

		for ( ii = 0; ii < 40; ii++ )
		{
			if ( pmshot[ii * 20 + 2] == 0 )
			{
				pmshot[ii * 20 + 0] = funcSin( rg ) * k;			/* 뭙뫊x */
				pmshot[ii * 20 + 1] = funcCos( rg ) * k;			/* 뭙뫊y */
				pmshot[ii * 20 + 2] = 1;						/* 뫔띪 */
				pmshot[ii * 20 + 3] = 0;						/* 롰쀞 */
				pmshot[ii * 20 + 4] = 0 ;						/*  */
				pmshot[ii * 20 + 5] = ( player[0] ) << 16 ;			/* 룊딖댧뭫궻먠믦 */
				pmshot[ii * 20 + 6] = ( player[1] ) << 16 ;
				pmshot[ii * 20 + 7] = muki;						/* 뺴뛀 */

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

			pmshot[ii * 20 + 5] = pmshot[ii * 20 + 0] + pmshot[ii * 20 + 5];		/* 뭙뫊x */
			pmshot[ii * 20 + 6] = pmshot[ii * 20 + 1] + pmshot[ii * 20 + 6];		/* 뭙뫊x */

			if ( ( ( pmshot[ii * 20 + 5] >> 16 ) > 640 ) || ( ( pmshot[ii * 20 + 5] >> 16 ) < -32 ) )
			{
				pmshot[ii * 20 + 2] = 0;				/* 뫔띪뼰궢 */
			}
			if ( ( ( pmshot[ii * 20 + 6] >> 16 ) > 480 ) || ( ( pmshot[ii * 20 + 6] >> 16 ) < -32 ) )
			{
				pmshot[ii * 20 + 2] = 0;				/* 뫔띪뼰궢 */
			}

			if ( ( ( map1_item_j( ( pmshot[ii * 20 + 5] >> 16 ) + 16 , ( pmshot[ii * 20 + 6] >> 16 ) + 16 ) >= 100 )
			    && ( map1_item_j( ( pmshot[ii * 20 + 5] >> 16 ) + 16 , ( pmshot[ii * 20 + 6] >> 16 ) + 16 ) <= 220 ) ) )
			{
				pmshot[ii * 20 + 2] = 0;				/* 뫔띪뼰궢 */
				p_shot_f2_set( ( pmshot[5 + ii * 20] >> 16 ) + 15, ( pmshot[6 + ii * 20] >> 16 ) + 15, 0 );
				if ( pmshot[3 + ii * 20] == 2 )	/* 긚긌깑긏깋긞긘깄긘깈긞긣 */
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

	/* 긌?룉뿚궼딈?밒궸player[2]궕돺륉뫴궻렄궸긌?귩볺귢궫귞궵궎궶귡귩딯뢲궢궲궋궘 */
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

	//	긚긻?긚긌?궕돓궠귢귡
	if ( g_pApp->IsPressKey( DGXKEY_FA ) )
	{
		input_keys = input_keys + 10000;
	}

	//B궕돓궠귢귡
	if ( g_pApp->IsPressKey( DGXKEY_FX ) )
	{
		input_keys = input_keys + 100000;
	}

	//B궕돓궠귢귡
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



