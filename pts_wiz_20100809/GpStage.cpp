

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

	m_nMode = 0;		//���ݑI������Ă���?��	�O�F�f?�l�d�r�s?�q�s?�P�F�n�o�s�h�n�m?�Q�F�d�w�h�s
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

	//	����L?��������
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

			SetSceneGameFlag1(127, 0);	//�g??���A?�b�N
			SetSceneGameFlag1(123,-1);	//���v���C�I�����̃X�e?�W
			SetSceneGameFlag1(132, 0);		//���v���C
			SetSceneGameFlag1(70 , 1);
			SetSceneGameFlag1(128, 0);	//?�b�v�r��?
			SetSceneGameFlag1(129, 1);	//�X�e?�W�Z���N�g����J�n
			SaveGameFlag2( "save/work.sav");

			ResetGameFlag2();
			SaveGameFlag2( "save/item_wk.sav");

			SetSceneGameFlag1(40, 4);
			SetSceneState(EN_SN_ACT);
			m_bExit=0;

			return m_bExit;
		}
	}

	//	�L�����Z���L?��������
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

	//�����
	tergetnam = 0;
	for ( x = 0; x < 5; x++ )
	{
		for ( y = 0; y < 10; y++ )
		{
			stage_no = ( ( x ) * 10 ) + ( y + 1 );
			//�g���t�B?��?��
			//?�C?
			tergetnam = 0;
			if ( m_nTarget_save[200 + stage_no + stage_hosei] >= GetSceneGameFlag1(200 + stage_no + stage_hosei) )
			{
				tergetnam++;
			}
			//��?
			if ( m_nTarget_save[300 + stage_no + stage_hosei] >= GetSceneGameFlag1(300 + stage_no + stage_hosei) )
			{
				tergetnam++;
			}
			//�B��
			if ( GetSceneGameFlag1(400 + stage_no + stage_hosei) != 0 )
			{
				tergetnam++;
			}
			BltRect(m_vTex[2], 15 + ( x * 64 ) , 32 + ( y * 8 ), 0, 96 + ( tergetnam * 7 ) , 41 , 7 );	/* �B���x */
		}
	}

	Blt(m_vTex[0], 0, 0 );
	if ( m_nCsl[0] == 10 )
	{
		// exit
		BltRect(m_vTex[2], 0 + ( 2 * 64 ) , 32 + ( 10 * 8 ), ( m_nA[1] / 10 ) * 16, 0 , 16 , 16 );	/* �J??�� */
	}
	else
	{
		BltNumericImage( m_nCsl[1] + 1, 1, 174, 135, m_vTex[4], 0, 0, 10, 8 );	/*  */
		BltNumericImage( m_nCsl[0] + 1 + ( m_nCsl[1] * 10 ), 2, 192, 135, m_vTex[4], 0, 0, 10, 8 );	/*  */

		BltRect(m_vTex[2], 0 + ( m_nCsl[1] * 64 ) , 28 + ( m_nCsl[0] * 8 ), ( m_nA[1] / 10 ) * 16, 0 , 16 , 16 );	/* �J??�� */

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

		//�g���t�B?��?��
		//?�C?
		if ( m_nTarget_save[200 + stage_no + stage_hosei] >= GetSceneGameFlag1(200 + stage_no + stage_hosei) )
		{
			BltRect(m_vTex[2], 0, 138, 0, 64, 32, 32 );	/* ?�C? */
			BltRect(m_vTex[2], 0 + 5, 138 + 4, 32 + ( ( ( m_nA[0] / 10 ) % 2 ) * 5 ), 37 , 5 , 7 );	/* �J??�� */
			BltRect(m_vTex[2], 0 + 20, 138 + 14, 32 + ( ( ( m_nA[0] / 10 ) % 2 ) * 5 ), 37 , 5 , 7 );	/* �J??�� */
		}
		else
		{
			BltRect(m_vTex[2], 0, 138, 0, 32, 32, 32 );	/* �y�� */
		}
		//��?
		if ( m_nTarget_save[300 + stage_no + stage_hosei] >= GetSceneGameFlag1(300 + stage_no + stage_hosei) )
		{
			BltRect(m_vTex[2], 0, 170, 32, 64, 32, 32 );	/* ?�C? */
			BltRect(m_vTex[2], 0 + 5, 170 + 4, 32 + ( ( ( m_nA[0] / 10 ) % 2 ) * 5 ), 37 , 5 , 7 );	/* �J??�� */
			BltRect(m_vTex[2], 0 + 20, 170 + 14, 32 + ( ( ( m_nA[0] / 10 ) % 2 ) * 5 ), 37 , 5 , 7 );	/* �J??�� */
		}
		else
		{
			BltRect(m_vTex[2], 0, 170, 0, 32, 32, 32 );	/* �y�� */
		}
		//�B��
		if ( GetSceneGameFlag1(400 + stage_no + stage_hosei) != 0 )
		{
			BltRect(m_vTex[4], 190, 214, 0, 176, 200, 8 );	/* ?�C? */
			BltRect(m_vTex[2], 0, 202, 64, 64, 32, 32 );	/* ?�C? */
			BltRect(m_vTex[2], 0 + 5, 202 + 4, 32 + ( ( ( m_nA[0] / 10 ) % 2 ) * 5 ), 37 , 5 , 7 );	/* �J??�� */
			BltRect(m_vTex[2], 0 + 20, 202 + 14, 32 + ( ( ( m_nA[0] / 10 ) % 2 ) * 5 ), 37 , 5 , 7 );	/* �J??�� */
		}
		else
		{
			BltRect(m_vTex[4], 190, 214, 0, 168, 200, 8 );	/* ?�C? */
			BltRect(m_vTex[2], 0, 202, 0, 32, 32, 32 );	/* �y�� */
		}

	}

}


/***************************************************************************/
// NAME      = init_save_data
// FUNCTION  = �Z?�u�t?�C���̏����l��ݒ�
// NOTES     =
// DATE      =
// AUTHER    = koizumi
// HISTORY   =
// PARAMETER = �Ȃ�
// RETURN    = �Ȃ�
/***************************************************************************/
void CGpStage::stageselect_init_save_data()
{
	SetSceneGameFlag2(0, 8 * 32 );	/* �w */
	SetSceneGameFlag2(1, ( 2 * 32 ) - 16);	/* �x */

	if ( GetSceneGameFlag1(126) == 1 )
	{
		SetSceneGameFlag2(2, 2);	/* �X�e?�W */
	}
	else
	{
		SetSceneGameFlag2(2, 1);	/* �X�e?�W */
	}

	SetSceneGameFlag1(120, ( ( m_nCsl[1] ) * 10 ) + ( m_nCsl[0] + 1 )  );
	SetSceneGameFlag2( 3, GetSceneGameFlag1(120) );	/* ��ʂm�� */
	SetSceneGameFlag2( 4, 0);	/* ���� */
	SetSceneGameFlag2( 5, 3);	/* ���݂g�o */
	SetSceneGameFlag2( 6, 3);	/* �ő�g�o */
	SetSceneGameFlag2( 7, 0);	/* �n?�g�̂����珊���� */
	SetSceneGameFlag2( 8, 0);	/* ���ݐݒ�X�L�� */
	SetSceneGameFlag2( 9, 0);	/* �e��???�g�p�s�A�X�N��?���s�t���O */
	SetSceneGameFlag2(10, 0);	/* �e��???�g�p�s�t���O */

	SetSceneGameFlag2(20, 0); 	/* �� */
	SetSceneGameFlag2(21, 0); 	/* �� */
	SetSceneGameFlag2(22, 0); 	/* �b */

	SetSceneGameFlag2(30, 0);	/* �e��????�g�p */
	SetSceneGameFlag2(31, 0);	/* �e��????�X�e?�W */
	SetSceneGameFlag2(32, 0);	/* �e��????��ʂm�� */
	SetSceneGameFlag2(33, 0);	/* �e��????�w */
	SetSceneGameFlag2(34, 0);	/* �e��????�x */

	SetSceneGameFlag2(40, 0);	/* �擾�X�L���P */
	SetSceneGameFlag2(41, 0);	/* �擾�X�L���Q */
	SetSceneGameFlag2(42, 0);	/* �擾�X�L���R */
	SetSceneGameFlag2(43, 0);	/* �擾�X�L���S */

}



