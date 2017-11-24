// Implementation of the CMain class.
//
////////////////////////////////////////////////////////////////////////////////


#include "_StdAfx.h"


CMain*		g_pApp = NULL;
PDGE_DEVICE	g_pDevice	= NULL;
PDGE_SPRITE	g_pSprite	= NULL;




char* g_sSndBgm[8] =
{
	"sound/bg/bg01.wav",
	"sound/bg/bg02.wav",
	"sound/bg/bg03.wav",
	"sound/bg/bg04.wav",
	"sound/bg/bg05.wav",

	"sound/bg/bg06.wav",
	"sound/bg/bg07.wav",
	(char*)NULL,
};


char* g_sSndSe[20] =
{
	"sound/se/atk1.wav"		,
	"sound/se/damage.wav"	,
	"sound/se/l1.wav"		,
	"sound/se/landing.wav"	,
	"sound/se/msg.wav"		,

	"sound/se/select.wav"	,
	"sound/se/sw.wav"		,
	"sound/se/jump.wav"		,
	"sound/se/puwa.wav"		,
	"sound/se/se01.wav"		,

	"sound/se/se02.wav"		,
	"sound/se/se03.wav"		,
	"sound/se/se04.wav"		,
	"sound/se/se05.wav"		,
	"sound/se/se06.wav"		,

	"sound/se/se07.wav"		,
	"sound/se/se08.wav"		,
	"sound/se/se09.wav"		,
	"sound/se/se10.wav"		,
	(char*)NULL,
};



CMain::CMain()
{
	g_pApp		= this;
	
	m_pInput	= NULL;

	m_nScnSt	= 0;

	memset(m_nGameFlag1, 0, sizeof(m_nGameFlag1));
	memset(m_nGameFlag2, 0, sizeof(m_nGameFlag2));

	m_nDebugDisp = 0;
	m_nDebugStageProduct = 0;


	m_nTickPrv	= 0;
	m_nTickCur	= 0;
	m_dSoundVol	= 128;
	m_bReset	= 0;

	m_pSndBg = NULL;
}


INT	CMain::Init()
{
	g_pDevice = m_pDev;
	g_pSprite = m_pSprite;

	// Input »ý¼º
	if(DGE_FAILED(DGX_CreateInput(NULL, &m_pInput, m_pDev, m_hWnd)))
		return DGE_EFAIL;
	


	// Main Init Config
	int i;
	i = 0;

	if( LoadGameFlag("save/config") )
	{
		/* ƒt?ƒCƒ‹‚ª‘¶Ý‚µ‚È‚¢ê‡‚Ì‰Šú’lÝ’è */
		ResetGameFlag();

		m_nGameFlag1[60] = 128;	//‰¹—Ê

		m_nGameFlag1[70] = 1;	//?ƒCƒgƒ‹‰æ–Ê‚©‚ç—ˆ‚½
		m_nGameFlag1[71] = 1;	//ƒŠƒgƒ‰ƒC‚ð‘I‘ð‚µ‚½


		m_nGameFlag1[100] = 0;	//ƒNƒŠƒAƒtƒ‰ƒO

		m_nGameFlag1[107] = 0;	//play time s
		m_nGameFlag1[108] = 0;	//play time s
		m_nGameFlag1[109] = 0;	//play time m
		m_nGameFlag1[110] = 0;	//play time h
		m_nGameFlag1[111] = 0;	//CLEAR time s
		m_nGameFlag1[112] = 0;	//CLEAR time m
		m_nGameFlag1[113] = 0;	//CLEAR time h


		m_nGameFlag1[120] = 1;	//ƒXƒe?ƒWƒZƒŒƒNƒg
		m_nGameFlag1[121] = 1;	//“ž’BƒXƒe?ƒW
		m_nGameFlag1[122] = 0;	//ƒLƒƒƒ‰ƒZƒŒƒNƒg
		m_nGameFlag1[123] = -1;	//ƒŠƒvƒŒƒC‘I‘ðŽž‚ÌƒXƒe?ƒW
		m_nGameFlag1[124] = 0;	//ƒŠƒvƒŒƒC?‚k‚kA‚n‚m‚d
		m_nGameFlag1[125] = 0;	//ƒŠƒvƒŒƒCjamp
		m_nGameFlag1[126] = 0;	//— –Ê
		m_nGameFlag1[127] = 0;	//ƒg??ƒ‹ƒA?ƒbƒN
		m_nGameFlag1[128] = 0;	//?ƒbƒvƒrƒ…?
		m_nGameFlag1[129] = 0;	//ƒXƒe?ƒWƒZƒŒƒNƒg‚©‚çŠJŽn

		m_nGameFlag1[132] = 0;	//ƒŠƒvƒŒƒC
		m_nGameFlag1[133] = 1;	//up key use
		m_nGameFlag1[134] = 0;	//ŠJŽn‰‰o‚Ì—L–³

		m_nGameFlag1[135] = 0;	//ƒg??ƒ‹ƒA?ƒbƒN ŽžŠÔ					[130]>[135]
		m_nGameFlag1[136] = 0;	//ƒg??ƒ‹ƒA?ƒbƒN ?ƒX				[131]>[136]
		m_nGameFlag1[137] = 1595959;	//ƒg??ƒ‹ƒA?ƒbƒN ƒNƒŠƒAŽžŠÔ	[132]>[137]
		m_nGameFlag1[138] = 999;	//ƒg??ƒ‹ƒA?ƒbƒN ƒNƒŠƒA?ƒX	[133]>[138]

		for ( i = 0; i <= 99; i++ )
		{
			m_nGameFlag1[200 + i] = 1105959;
		}
		for ( i = 0; i <= 99; i++ )
		{
			m_nGameFlag1[300 + i] = 99;
		}
		for ( i = 0; i <= 99; i++ )
		{
			m_nGameFlag1[400 + i] = 0;
		}
	}


	m_nGameFlag1[ 0] = DGXKEY_UP;		//	Up
	m_nGameFlag1[ 1] = DGXKEY_DOWN;		//	Down
	m_nGameFlag1[ 2] = DGXKEY_LEFT;		//	Left
	m_nGameFlag1[ 3] = DGXKEY_RIGHT;	//	Right
	m_nGameFlag1[ 4] = DGXKEY_FA;		//	Z
	m_nGameFlag1[ 5] = DGXKEY_FX;		//	X
	m_nGameFlag1[ 6] = DGXKEY_FY;		//	C
	m_nGameFlag1[ 7] = DGXKEY_FB;		//	S
	m_nGameFlag1[ 8] = DGXKEY_FL;		//	S
	m_nGameFlag1[ 9] = DGXKEY_FR;		//	S
	m_nGameFlag1[10] = DGXKEY_START;	//	S
	m_nGameFlag1[11] = DGXKEY_SELECT;	//	S


	m_nGameFlag1[121] = 50;	//“ž’BƒXƒe?ƒW

	m_nDebugDisp 			= GetConfig( CONFIGFILE_NAME , "DebugDisp" );
	m_nDebugStageProduct 	= GetConfig( CONFIGFILE_NAME , "DebugStageProduction" );


	// set Volume
#if defined(GP2X_WIZ)
	long vol = GetSceneGameFlag1(60);
	DGX_MixerSetVolume(DGX_MIXER_VOLUME, vol, vol);
#endif




	// Background Sound Create
	if(NULL == m_pSndBg)
	{
		DGX_CreateSound(NULL, &m_pSndBg, g_sSndBgm[EN_BGM_GAME01]);
		DGX_SoundRepeat(m_pSndBg);
	}



	// Main Init

#if defined(_WIN32) || defined(WIN32)
	SetSceneState(EN_SN_LOGO);
	m_pGpLogo.Init();
#else
	SetSceneState(EN_SN_LOGO);
	m_pGpLogo.Init();
#endif

	return DGE_OK;
}


INT	CMain::Destroy()
{
	printf("Destroy Logo\n");
	m_pGpLogo.Destroy();

	printf("Destroy Act\n");
	m_pGpAct.Destroy();
	m_pGpAct.ReleseSound();
	m_pGpAct.ReleseTexture();

	printf("Destroy Ending\n");
	m_pGpEnding.Destroy();

	printf("Destroy Stage\n");
	m_pGpStage.Destroy();

	printf("Destroy Demo\n");
	m_pGpDemo.Destroy();

	printf("Destroy Option\n");
	m_pGpOption.Destroy();

	printf("Destroy Title\n");
	m_pGpTitle.Destroy();
	m_pGpTitle.ReleseTexture();

	printf("Destroy Sound\n");
	DGX_DestroySound(&m_pSndBg);

	printf("Destroy Input\n");
	DGX_DestroyInput(&m_pInput);
	
	return DGE_OK;
}

INT	CMain::FrameMove()
{
	INT		hr=0;

	// Input Update
	m_pInput->Update();


	switch( m_nScnSt )
	{
		case EN_SN_LOGO:
		{
			hr = m_pGpLogo.Update();
			if(0 == hr)
			{
				m_pGpLogo.Destroy();
			}

			break;
		}

		case EN_SN_TITLE:
		{
			hr = m_pGpTitle.Update();
			if(0 == hr)
			{
				m_pGpTitle.Destroy();
			}

			break;
		}

		case EN_SN_ACT:
		{
			hr = m_pGpAct.Update();
			if(0 == hr)
			{
				m_pGpAct.Destroy();
			}

			break;
		}

		case EN_SN_OPTION:
		{
			hr = m_pGpOption.Update();
			if(0 == hr)
			{
				m_pGpOption.Destroy();
			}

			break;
		}

		case EN_SN_ENDING:
		{
			hr = m_pGpEnding.Update();
			if(0 == hr)
			{
				m_pGpEnding.Destroy();
			}

			break;
		}

		case EN_SN_STAGE:
		{
			hr = m_pGpStage.Update();
			if(0 == hr)
			{
				m_pGpStage.Destroy();
			}

			break;
		}

		case EN_SN_DEMO:
		{
			hr = m_pGpDemo.Update();
			if(0 == hr)
			{
				m_pGpDemo.Destroy();
			}

			break;
		}

		default:
			return -1;
			break;
	}


	// 0 == hrÀº ¿Ï·á¸¦ ÀÇ¹Ì
	if(0 == hr)
		m_bReset = 1;


	// Reset Process:
	// Input Reset ¡æ Game Stage Init ¡æ Game Stage Update ¡æ Input Update
	if(m_bReset)
	{
		m_pInput->Reset();

		switch( m_nScnSt )
		{
			case EN_SN_LOGO:	hr = m_pGpLogo.Init();		break;
			case EN_SN_TITLE:	hr = m_pGpTitle.Init();		break;
			case EN_SN_ACT:		hr = m_pGpAct.Init();		break;

			case EN_SN_OPTION:	hr = m_pGpOption.Init();	break;
			case EN_SN_ENDING:	hr = m_pGpEnding.Init();	break;
			case EN_SN_STAGE:	hr = m_pGpStage.Init();		break;
			case EN_SN_DEMO:	hr = m_pGpDemo.Init();		break;
		}


		switch( m_nScnSt )
		{
			case EN_SN_LOGO:	hr = m_pGpLogo.Update();	break;
			case EN_SN_TITLE:	hr = m_pGpTitle.Update();	break;
			case EN_SN_ACT:		hr = m_pGpAct.Update();		break;

			case EN_SN_OPTION:	hr = m_pGpOption.Update();	break;
			case EN_SN_ENDING:	hr = m_pGpEnding.Update();	break;
			case EN_SN_STAGE:	hr = m_pGpStage.Update();	break;
			case EN_SN_DEMO:	hr = m_pGpDemo.Update();	break;
		}

		m_pInput->Update();
		m_bReset = 0;
	}

	return DGE_OK;
}



INT	CMain::Render()
{
	m_pDev->BeginScene();

	DGXCOLOR	dColor(0,0,0,0);
	m_pDev->SetRenderState(DGE_RS_CLEAR_COLOR, &dColor);

	m_pDev->Clear(DGE_CLEAR_COLOR_BUFFER | DGE_CLEAR_DEPTH_BUFFER);
	

	m_pSprite->Begin();

	switch( m_nScnSt )
	{
		case EN_SN_LOGO:	m_pGpLogo.Render();		break;
		case EN_SN_TITLE:	m_pGpTitle.Render();	break;
		case EN_SN_ACT:		m_pGpAct.Render();		break;

		case EN_SN_OPTION:	m_pGpOption.Render();	break;
		case EN_SN_ENDING:	m_pGpEnding.Render();	break;
		case EN_SN_STAGE:	m_pGpStage.Render();	break;
		case EN_SN_DEMO:	m_pGpDemo.Render();		break;
	}


	m_pSprite->End();
	m_pDev->EndScene();


	int nExit = 0;

	this->FPSWait();

	nExit = g_pApp->system_keys();

	if(0 == nExit)
		return -1;


	return DGE_OK;
}




enum
{
#ifdef GP2X
	INTERVAL_BASE = 16,		//	INTERVAL_BASE = 8
#else
	INTERVAL_BASE = 16,
#endif
};




void CMain::FPSWait()
{
	int	 interval = INTERVAL_BASE;
	UINT leftTick;


	if(m_nTickPrv == 0)
		m_nTickPrv = DGE_GetTickCount();

	while (TRUE)
	{
	 	m_nTickCur = DGE_GetTickCount();
 		leftTick = m_nTickPrv + interval - m_nTickCur;
 		if(leftTick < 1 || leftTick > 9999)
 		{
			break;
		}
	}

	m_nTickPrv = m_nTickCur;

	SetSceneGameFlag1(107, GetSceneGameFlag1(107) + 1);

	if ( GetSceneGameFlag1(107) >= 60 )
	{
		SetSceneGameFlag1(107, 0);
		SetSceneGameFlag1(108, GetSceneGameFlag1(108) + 1);

		if ( GetSceneGameFlag1(108) >= 60 )
		{
			SetSceneGameFlag1(108, 0);
			SetSceneGameFlag1(109, GetSceneGameFlag1(109) + 1);

			if ( GetSceneGameFlag1(109) >= 60 )
			{
				SetSceneGameFlag1(109, 0);
				SetSceneGameFlag1(110, GetSceneGameFlag1(110) + 1);

				if ( GetSceneGameFlag1(110) >= 999 )
				{
					SetSceneGameFlag1(110, 999);
				}
			}
		}
	}

}

int CMain::system_keys()
{
	int hr;

	hr = 1;
#ifdef GP2X
	// çµ‚äº†
//	if ( ( m_pInput->KeyPress( DGXKEY_START ) ) && ( m_pInput->KeyPress( DGXKEY_SELECT ) ) )
//	if ( ( m_pInput->KeyPress( DGXKEY_START ) ) && ( m_pInput->KeyPress( DGXKEY_FL ) ) && ( m_pInput->KeyPress( DGXKEY_FR ) ) )
#else
//	if ( m_pInput->KeyPress(DGXKEY_START))
#endif

//	if(m_pInput->KeyPress( DGXKEY_START ) )
//	{
//		hr = 0;
//		SetSceneState(EN_SN_EXIT);
//	}


	// ?³é‡èª¿æ•´
	if ( m_pInput->KeyDown( DGXKEY_VOL_UP) )
	{
		SetSceneGameFlag1(60, GetSceneGameFlag1(60) + 10);

		if ( GetSceneGameFlag1(60) > VOL_MAX )
		{
			SetSceneGameFlag1(60, VOL_MAX);
		}

#if defined(GP2X_WIZ)
		long vol = GetSceneGameFlag1(60);
		DGX_MixerSetVolume(DGX_MIXER_VOLUME, vol, vol);
#endif

//		printf("Volume: %ld\n", vol);
	}

	if ( m_pInput->KeyDown( DGXKEY_VOL_DOWN ) )
	{
		SetSceneGameFlag1(60, GetSceneGameFlag1(60) - 10);

		if ( GetSceneGameFlag1(60) < 0 )
		{
			SetSceneGameFlag1(60, 0);
		}

#if defined(GP2X_WIZ)
		long vol = GetSceneGameFlag1(60);
		DGX_MixerSetVolume(DGX_MIXER_VOLUME, vol, vol);
#endif

//		printf("Volume: %ld\n", vol);
	}

	return hr;
}





int CMain::IsPressKey(INT nKey)
{
	int hr = 0;

	hr = m_pInput->KeyState(nKey);
	if ( DGXINPUT_KEYDOWN == hr || DGXINPUT_KEYPRESS == hr)
		return 1;

	return 0;
}

int CMain::IsPushKey( int keycode )
{
	int hr = 0;

	if ( m_pInput->KeyDown(keycode))
		hr = 1;


	return( hr );
}

int CMain::IsPushOKKey()
{
	int hr = 0;
	if ( m_pInput->KeyDown(DGXKEY_FB) )
		hr = 1;

	return hr;
}


int CMain::IsPushCancelKey()
{
	int hr = 0;

	if ( m_pInput->KeyDown(DGXKEY_FX) )
	{
		hr = 1;
	}

	return hr;
}



void CMain::Loading(int n)
{
	m_pGpAct.Loading(n);
}

