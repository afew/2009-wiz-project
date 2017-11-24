

#include "_StdAfx.h"


extern char* g_sSndBgm[8];
extern char* g_sSndSe[20];


CGpEnding::CGpEnding()
{
	m_bExit	= 0;
	memset(m_nDemo, 0, sizeof(m_nDemo));
	memset(m_nTargetSave, 0, sizeof(m_nTargetSave));
	memset(m_vBgt, 0, sizeof(m_vBgt));
	memset(m_vMst, 0, sizeof(m_vMst));
	
	m_iEndProcess		= 0;
	m_iEndProcessSub	= 0;
	m_iEndTimeCounter	= 0;
	m_iEndAlphaCounter	= 0;
	
	m_pSndBg = NULL;
}


CGpEnding::~CGpEnding()
{
}



int CGpEnding::Init()
{
	int stage_hosei;
	int x, y;
	int i;
	int stage_no;
	int tergetnam;

	unsigned int dColorKey = 0xFF106339;

	m_bExit = 1;
	
	tergetnam = 0;
	stage_hosei = 0;

	
	if ( GetSceneGameFlag1(126) == 1 )
	{
		stage_hosei = 50;
	}



	memset( m_nTargetSave, 0, sizeof( m_nTargetSave ) );
	memset( m_nDemo, 0, sizeof( m_nDemo ) );
	
	
	LoadFile( "save/target", &m_nTargetSave[0], sizeof( m_nTargetSave ) );
	
	tergetnam = 0;
	for ( x = 0; x < 5; x++ )
	{
		for ( y = 0; y < 10; y++ )
		{
			stage_no = ( ( x ) * 10 ) + ( y + 1 );
			//トロフィ?の?示
			//?イ?
			if ( m_nTargetSave[200 + stage_no + stage_hosei] >= GetSceneGameFlag1(200 + stage_no + stage_hosei) )
			{
				//				tergetnam++;
			}
			//回?
			if ( m_nTargetSave[300 + stage_no + stage_hosei] >= GetSceneGameFlag1(300 + stage_no + stage_hosei) )
			{
				//				tergetnam++;
			}
			//隠し
			if ( GetSceneGameFlag1(400 + stage_no + stage_hosei) != 0 )
			{
				tergetnam++;
			}
		}
	}


	SetSceneGameFlag1(100, 0);
	


	// initialize.
	m_iEndProcess      = 0;
	m_iEndProcessSub   = 0;
	m_iEndTimeCounter  = 0;
	m_iEndAlphaCounter = 0;
	
	
	if(NULL == m_vBgt[ 0].pTex)	LoadImage2(&m_vBgt[ 0].pTex, (char*)"image/end/end_0.png", dColorKey );
	if(NULL == m_vBgt[ 1].pTex)	LoadImage2(&m_vBgt[ 1].pTex, (char*)"image/end/end_2.png", dColorKey );
	if(NULL == m_vBgt[ 2].pTex)	LoadImage2(&m_vBgt[ 2].pTex, (char*)"image/end/end_3.png", dColorKey );
	if(NULL == m_vBgt[ 4].pTex)	LoadImage2(&m_vBgt[ 4].pTex, (char*)"image/end/end_4.png", dColorKey );
	if(NULL == m_vBgt[ 5].pTex)	LoadImage2(&m_vBgt[ 5].pTex, (char*)"image/end/end_5.png", dColorKey );

	if(NULL == m_vMst[ 0].pTex)	LoadImage2(&m_vMst[ 0].pTex, (char*)"image/end/2-1.png", dColorKey );
	if(NULL == m_vMst[ 1].pTex)	LoadImage2(&m_vMst[ 1].pTex, (char*)"image/end/2-2.png", dColorKey );
	if(NULL == m_vMst[ 2].pTex)	LoadImage2(&m_vMst[ 2].pTex, (char*)"image/end/2-3.png", dColorKey );
	if(NULL == m_vMst[ 3].pTex)	LoadImage2(&m_vMst[ 3].pTex, (char*)"image/end/2-4.png", dColorKey );
	if(NULL == m_vMst[ 4].pTex)	LoadImage2(&m_vMst[ 4].pTex, (char*)"image/end/2-5.png", dColorKey );
	if(NULL == m_vMst[ 5].pTex)	LoadImage2(&m_vMst[ 5].pTex, (char*)"image/end/2-6.png", dColorKey );
	if(NULL == m_vMst[ 6].pTex)	LoadImage2(&m_vMst[ 6].pTex, (char*)"image/end/2-7.png", dColorKey );
	if(NULL == m_vMst[ 7].pTex)	LoadImage2(&m_vMst[ 7].pTex, (char*)"image/end/2-8.png", dColorKey );
	if(NULL == m_vMst[ 8].pTex)	LoadImage2(&m_vMst[ 8].pTex, (char*)"image/end/2-9.png", dColorKey );
	if(NULL == m_vMst[ 9].pTex)	LoadImage2(&m_vMst[ 9].pTex, (char*)"image/end/3-1.png", dColorKey );
	if(NULL == m_vMst[10].pTex)	LoadImage2(&m_vMst[10].pTex, (char*)"image/end/3-2.png", dColorKey );
	if(NULL == m_vMst[11].pTex)	LoadImage2(&m_vMst[11].pTex, (char*)"image/end/3-3.png", dColorKey );
	if(NULL == m_vMst[12].pTex)	LoadImage2(&m_vMst[12].pTex, (char*)"image/end/3-4.png", dColorKey );
	if(NULL == m_vMst[13].pTex)	LoadImage2(&m_vMst[13].pTex, (char*)"image/end/3-5.png", dColorKey );
	if(NULL == m_vMst[14].pTex)	LoadImage2(&m_vMst[14].pTex, (char*)"image/end/3-6.png", dColorKey );
	if(NULL == m_vMst[15].pTex)	LoadImage2(&m_vMst[15].pTex, (char*)"image/end/3-7.png", dColorKey );
	if(NULL == m_vMst[16].pTex)	LoadImage2(&m_vMst[16].pTex, (char*)"image/end/3-8.png", dColorKey );
	if(NULL == m_vMst[17].pTex)	LoadImage2(&m_vMst[17].pTex, (char*)"image/end/3-9.png", dColorKey );
	if(NULL == m_vMst[18].pTex)	LoadImage2(&m_vMst[18].pTex, (char*)"image/end/3-10.png", dColorKey);


	for(i=0; i< END_IMAGE_MAX; ++i)
		m_vBgt[i].SetAlpha(0);


	for(i=0; i< END_IMAGE_MAX; ++i)
		m_vMst[i].SetAlpha(0);


	DGX_DestroySound(&g_pApp->m_pSndBg);

	if(NULL == m_pSndBg)
		DGX_CreateSound(NULL, &m_pSndBg, g_sSndBgm[EN_BGM_GAME07]);

	DGX_SoundPlay( m_pSndBg );
	
	return 0;
}


void CGpEnding::Destroy()
{
	int i;
	
	DGX_DestroySound(&m_pSndBg);
	
	
	for ( i = 0; i<END_IMAGE_MAX; ++i )
	{
		ReleaseImage(&m_vBgt[i].pTex );
		ReleaseImage(&m_vMst[i].pTex );
	}
}



int CGpEnding::Update()
{
	if( g_pApp->IsPushCancelKey() )
	{
		SetSceneState(EN_SN_TITLE);
		m_bExit=0;
		return m_bExit;
	}

	switch ( m_iEndProcess )
	{
	case 0:
		{
			// set alpha value.
			m_iEndAlphaCounter += 5;
			if ( 255 < m_iEndAlphaCounter )
				m_iEndAlphaCounter = 255;
			
			if ( 0 == m_iEndProcessSub )
			{
				SetAlpha(&m_vBgt[0], m_iEndAlphaCounter );
				if ( 255 == m_iEndAlphaCounter )	{	m_iEndProcessSub = 10;		m_iEndTimeCounter = 0;		m_iEndAlphaCounter = 0;	}
			}
			else if ( 10 == m_iEndProcessSub )
			{
				SetAlpha(&m_vMst[0], m_iEndAlphaCounter );
				
				if ( 255 <= m_iEndAlphaCounter )
				{
					m_iEndTimeCounter++;
					if ( 130 <= m_iEndTimeCounter )		{	m_iEndProcessSub = 20;		m_iEndTimeCounter = 0;		m_iEndAlphaCounter = 0;	}
				}
			}
			else if ( 20 == m_iEndProcessSub )
			{
				SetAlpha(&m_vMst[1], m_iEndAlphaCounter );
				
				if ( 255 <= m_iEndAlphaCounter )
				{
					m_iEndTimeCounter++;
					if ( 130 <= m_iEndTimeCounter )		{	m_iEndProcessSub = 30;		m_iEndTimeCounter = 0;		m_iEndAlphaCounter = 0;	}
				}
			}
			else if ( 30 == m_iEndProcessSub )
			{
				SetAlpha(&m_vMst[2], m_iEndAlphaCounter );
				
				if ( 255 <= m_iEndAlphaCounter )
				{
					m_iEndTimeCounter++;
					if ( 130 <= m_iEndTimeCounter )		{	m_iEndProcessSub = 40;		m_iEndTimeCounter = 0;		m_iEndAlphaCounter = 0;	}
				}
			}
			else if ( 40 == m_iEndProcessSub )
			{
				SetAlpha(&m_vMst[3], m_iEndAlphaCounter );
				
				if ( 255 <= m_iEndAlphaCounter )
				{
					m_iEndTimeCounter++;
					if ( 130 <= m_iEndTimeCounter )		{	m_iEndProcessSub = 50;		m_iEndTimeCounter = 0;		m_iEndAlphaCounter = 0;	}
				}
			}
			else if ( 50 == m_iEndProcessSub )
			{
				SetAlpha(&m_vMst[4], m_iEndAlphaCounter );
				
				if ( 255 <= m_iEndAlphaCounter )
				{
					m_iEndTimeCounter++;
					if ( 130 <= m_iEndTimeCounter )		{	m_iEndProcessSub = 60;		m_iEndTimeCounter = 0;		m_iEndAlphaCounter = 0;	}
				}
			}
			else if ( 60 == m_iEndProcessSub )
			{
				SetAlpha(&m_vMst[5], m_iEndAlphaCounter );
				
				if ( 255 <= m_iEndAlphaCounter )
				{
					m_iEndTimeCounter++;
					if ( 130 <= m_iEndTimeCounter )		{	m_iEndProcess = 1;	m_iEndProcessSub = 0;		m_iEndTimeCounter = 0;		m_iEndAlphaCounter = 0;	}
				}
			}
		}
		break;
		
	case 1:
		{
			// set alpha value.
			m_iEndAlphaCounter += 5;
			if ( 255 < m_iEndAlphaCounter )
				m_iEndAlphaCounter = 255;
			
			if ( 0 == m_iEndProcessSub )
			{
				SetAlpha(&m_vBgt[1], m_iEndAlphaCounter );
				if ( 255 == m_iEndAlphaCounter )	{	m_iEndProcessSub = 10;		m_iEndTimeCounter = 0;		m_iEndAlphaCounter = 0;	}
			}
			else if ( 10 == m_iEndProcessSub )
			{
				SetAlpha(&m_vMst[6], m_iEndAlphaCounter );
				
				if ( 255 <= m_iEndAlphaCounter )
				{
					m_iEndTimeCounter++;
					if ( 130 <= m_iEndTimeCounter )		{	m_iEndProcessSub = 20;		m_iEndTimeCounter = 0;		m_iEndAlphaCounter = 0;	}
				}
			}
			else if ( 20 == m_iEndProcessSub )
			{
				SetAlpha(&m_vMst[7], m_iEndAlphaCounter );
				
				if ( 255 <= m_iEndAlphaCounter )
				{
					m_iEndTimeCounter++;
					if ( 130 <= m_iEndTimeCounter )		{	m_iEndProcessSub = 30;		m_iEndTimeCounter = 0;		m_iEndAlphaCounter = 0;	}
				}
			}
			else if ( 30 == m_iEndProcessSub )
			{
				SetAlpha(&m_vMst[8], m_iEndAlphaCounter );
				
				if ( 255 <= m_iEndAlphaCounter )
				{
					m_iEndTimeCounter++;
					if ( 130 <= m_iEndTimeCounter )
					{
						m_iEndProcess = 2;	m_iEndProcessSub = 0;		m_iEndTimeCounter = 0;		m_iEndAlphaCounter = 0;
					}
				}
			}
			else if ( 40 == m_iEndProcessSub )
			{
				SetAlpha(&m_vMst[9], m_iEndAlphaCounter );
				
				if ( 255 <= m_iEndAlphaCounter )
				{
					m_iEndTimeCounter++;
					if ( 130 <= m_iEndTimeCounter )		{	m_iEndProcess = 10;	m_iEndProcessSub = 0;		m_iEndTimeCounter = 0;		m_iEndAlphaCounter = 0;		}
				}
			}
		}
		break;
		
	case 2:
		{
			// set alpha value.
			m_iEndAlphaCounter += 5;
			if ( 255 < m_iEndAlphaCounter )
				m_iEndAlphaCounter = 255;
			
			if ( 0 == m_iEndProcessSub )
			{
				SetAlpha(&m_vBgt[2], m_iEndAlphaCounter );
				if ( 255 == m_iEndAlphaCounter )	{	m_iEndProcessSub = 10;		m_iEndTimeCounter = 0;		m_iEndAlphaCounter = 0;	}
			}
			else if ( 10 == m_iEndProcessSub )
			{
				SetAlpha(&m_vMst[9], m_iEndAlphaCounter );
				
				if ( 255 <= m_iEndAlphaCounter )
				{
					m_iEndTimeCounter++;
					if ( 130 <= m_iEndTimeCounter )		{	m_iEndProcessSub = 20;		m_iEndTimeCounter = 0;		m_iEndAlphaCounter = 0;	}
				}
			}
			else if ( 20 == m_iEndProcessSub )
			{
				SetAlpha(&m_vMst[10], m_iEndAlphaCounter );
				
				if ( 255 <= m_iEndAlphaCounter )
				{
					m_iEndTimeCounter++;
					if ( 130 <= m_iEndTimeCounter )		{	m_iEndProcessSub = 30;		m_iEndTimeCounter = 0;		m_iEndAlphaCounter = 0;	}
				}
			}
			else if ( 30 == m_iEndProcessSub )
			{
				SetAlpha(&m_vMst[11], m_iEndAlphaCounter );
				
				if ( 255 <= m_iEndAlphaCounter )
				{
					m_iEndTimeCounter++;
					if ( 130 <= m_iEndTimeCounter )		{	m_iEndProcessSub = 40;		m_iEndTimeCounter = 0;		m_iEndAlphaCounter = 0;	}
				}
			}
			else if ( 40 == m_iEndProcessSub )
			{
				SetAlpha(&m_vMst[12], m_iEndAlphaCounter );
				
				if ( 255 <= m_iEndAlphaCounter )
				{
					m_iEndTimeCounter++;
					if ( 130 <= m_iEndTimeCounter )		{	m_iEndProcessSub = 50;		m_iEndTimeCounter = 0;		m_iEndAlphaCounter = 0;	}
				}
			}
			else if ( 50 == m_iEndProcessSub )
			{
				SetAlpha(&m_vMst[13], m_iEndAlphaCounter );
				
				if ( 255 <= m_iEndAlphaCounter )
				{
					m_iEndTimeCounter++;
					if ( 130 <= m_iEndTimeCounter )		{	m_iEndProcessSub = 60;		m_iEndTimeCounter = 0;		m_iEndAlphaCounter = 0;	}
				}
			}
			else if ( 60 == m_iEndProcessSub )
			{
				SetAlpha(&m_vMst[14], m_iEndAlphaCounter );
				
				if ( 255 <= m_iEndAlphaCounter )
				{
					m_iEndTimeCounter++;
					if ( 130 <= m_iEndTimeCounter )		{	m_iEndProcessSub = 70;		m_iEndTimeCounter = 0;		m_iEndAlphaCounter = 0;	}
				}
			}
			else if ( 70 == m_iEndProcessSub )
			{
				SetAlpha(&m_vMst[15], m_iEndAlphaCounter );
				
				if ( 255 <= m_iEndAlphaCounter )
				{
					m_iEndTimeCounter++;
					if ( 130 <= m_iEndTimeCounter )		{	m_iEndProcessSub = 80;		m_iEndTimeCounter = 0;		m_iEndAlphaCounter = 0;	}
				}
			}
			else if ( 80 == m_iEndProcessSub )
			{
				SetAlpha(&m_vMst[16], m_iEndAlphaCounter );
				
				if ( 255 <= m_iEndAlphaCounter )
				{
					m_iEndTimeCounter++;
					if ( 130 <= m_iEndTimeCounter )		{	m_iEndProcessSub = 90;		m_iEndTimeCounter = 0;		m_iEndAlphaCounter = 0;	}
				}
			}
			else if ( 90 == m_iEndProcessSub )
			{
				SetAlpha(&m_vMst[17], m_iEndAlphaCounter );
				
				if ( 255 <= m_iEndAlphaCounter )
				{
					m_iEndTimeCounter++;
					if ( 130 <= m_iEndTimeCounter )		{	m_iEndProcessSub = 100;		m_iEndTimeCounter = 0;		m_iEndAlphaCounter = 0;	}
				}
			}
			else if ( 100 == m_iEndProcessSub )
			{
				SetAlpha(&m_vMst[18], m_iEndAlphaCounter );
				
				if ( 255 <= m_iEndAlphaCounter )
				{
					m_iEndTimeCounter++;
					if ( 130 <= m_iEndTimeCounter )		{	m_iEndProcess = 10;	m_iEndProcessSub = 0;		m_iEndTimeCounter = 0;		m_iEndAlphaCounter = 0;		}
				}
			}
			
}
break;

case 10:		// staff, logo, end
	{
		if ( 0 == m_iEndProcessSub )
		{
			// set alpha value.
			m_iEndAlphaCounter += 5;
			if ( 255 < m_iEndAlphaCounter )
				m_iEndAlphaCounter = 255;
			
			SetAlpha(&m_vBgt[4], m_iEndAlphaCounter );
			
			if ( 255 <= m_iEndAlphaCounter )
			{
				m_iEndTimeCounter++;
				if ( 130 <= m_iEndTimeCounter )		{	m_iEndProcessSub = 10;		m_iEndTimeCounter = 0;		}
			}
		}
		else if ( 10 == m_iEndProcessSub )
		{
			// set alpha value.
			m_iEndAlphaCounter -= 5;
			if ( 0 > m_iEndAlphaCounter )
				m_iEndAlphaCounter = 0;
			
			SetAlpha(&m_vBgt[4], m_iEndAlphaCounter );
			if ( 0 == m_iEndAlphaCounter )	{	m_iEndProcessSub = 20;		m_iEndTimeCounter = 0;		m_iEndAlphaCounter = 0;	}
		}
		else if ( 20 == m_iEndProcessSub )
		{
			// set alpha value.
			m_iEndAlphaCounter += 5;
			if ( 255 < m_iEndAlphaCounter )
				m_iEndAlphaCounter = 255;
			
			SetAlpha(&m_vBgt[5], m_iEndAlphaCounter );
			
			if ( 255 <= m_iEndAlphaCounter )
			{
				m_iEndTimeCounter++;
				if ( 130 <= m_iEndTimeCounter )		{	m_iEndProcessSub = 30;		m_iEndTimeCounter = 0;		}
			}
		}
		else if ( 30 == m_iEndProcessSub )
		{
			// set alpha value.
			m_iEndAlphaCounter -= 5;
			if ( 0 > m_iEndAlphaCounter )
				m_iEndAlphaCounter = 0;
			
			SetAlpha(&m_vBgt[5], m_iEndAlphaCounter );
			if ( 0 == m_iEndAlphaCounter )	{	m_iEndProcess = 100;	}
		}
		
	}
	break;
	
default:
	{
		SetSceneState(EN_SN_TITLE);
		m_bExit=0;
	}
	break;
}


return m_bExit;
}



void CGpEnding::Render()
{
	if ( 0 == m_iEndProcess )
	{
		if ( 0 <= m_iEndProcessSub )								draw_fix(&m_vBgt[0], 0, 0);
		
		if ( 10 <= m_iEndProcessSub && 20 > m_iEndProcessSub )		draw_fix(&m_vMst[0], ( 320 - m_vMst[0].pTex->GetImgW() ) / 2, 210);
		if ( 20 <= m_iEndProcessSub && 30 > m_iEndProcessSub )		draw_fix(&m_vMst[1], ( 320 - m_vMst[1].pTex->GetImgW() ) / 2, 210);
		if ( 30 <= m_iEndProcessSub && 40 > m_iEndProcessSub )		draw_fix(&m_vMst[2], ( 320 - m_vMst[2].pTex->GetImgW() ) / 2, 210);
		if ( 40 <= m_iEndProcessSub && 50 > m_iEndProcessSub )		draw_fix(&m_vMst[3], ( 320 - m_vMst[3].pTex->GetImgW() ) / 2, 210);
		if ( 50 <= m_iEndProcessSub && 60 > m_iEndProcessSub )		draw_fix(&m_vMst[4], ( 320 - m_vMst[4].pTex->GetImgW() ) / 2, 210);
		if ( 60 <= m_iEndProcessSub && 70 > m_iEndProcessSub )		draw_fix(&m_vMst[5], ( 320 - m_vMst[5].pTex->GetImgW() ) / 2, 210);
	}
	else if ( 1 == m_iEndProcess )
	{
		if ( 0 <= m_iEndProcessSub )								draw_fix(&m_vBgt[1], 0, 0);
		
		if ( 10 <= m_iEndProcessSub && 20 > m_iEndProcessSub )		draw_fix(&m_vMst[6], ( 320 - m_vMst[6].pTex->GetImgW() ) / 2, 210);
		if ( 20 <= m_iEndProcessSub && 30 > m_iEndProcessSub )		draw_fix(&m_vMst[7], ( 320 - m_vMst[7].pTex->GetImgW() ) / 2, 210);
		if ( 30 <= m_iEndProcessSub && 40 > m_iEndProcessSub )		draw_fix(&m_vMst[8], ( 320 - m_vMst[8].pTex->GetImgW() ) / 2, 210);
		if ( 40 <= m_iEndProcessSub && 50 > m_iEndProcessSub )		draw_fix(&m_vMst[9], ( 320 - m_vMst[9].pTex->GetImgW() ) / 2, 210);
	}
	else if ( 2 == m_iEndProcess )
	{
		if ( 0 <= m_iEndProcessSub )								draw_fix(&m_vBgt[2], 0, 0);
		
		if (  10 <= m_iEndProcessSub &&  20 > m_iEndProcessSub )	draw_fix(&m_vMst[ 9], ( 320 - m_vMst[ 9].pTex->GetImgW() ) / 2, 210);
		if (  20 <= m_iEndProcessSub &&  30 > m_iEndProcessSub )	draw_fix(&m_vMst[10], ( 320 - m_vMst[10].pTex->GetImgW() ) / 2, 210);
		if (  30 <= m_iEndProcessSub &&  40 > m_iEndProcessSub )	draw_fix(&m_vMst[11], ( 320 - m_vMst[11].pTex->GetImgW() ) / 2, 210);
		if (  40 <= m_iEndProcessSub &&  50 > m_iEndProcessSub )	draw_fix(&m_vMst[12], ( 320 - m_vMst[12].pTex->GetImgW() ) / 2, 210);
		if (  50 <= m_iEndProcessSub &&  60 > m_iEndProcessSub )	draw_fix(&m_vMst[13], ( 320 - m_vMst[13].pTex->GetImgW() ) / 2, 210);
		if (  60 <= m_iEndProcessSub &&  70 > m_iEndProcessSub )	draw_fix(&m_vMst[14], ( 320 - m_vMst[14].pTex->GetImgW() ) / 2, 210);
		if (  70 <= m_iEndProcessSub &&  80 > m_iEndProcessSub )	draw_fix(&m_vMst[15], ( 320 - m_vMst[15].pTex->GetImgW() ) / 2, 210);
		if (  80 <= m_iEndProcessSub &&  90 > m_iEndProcessSub )	draw_fix(&m_vMst[16], ( 320 - m_vMst[16].pTex->GetImgW() ) / 2, 210);
		if (  90 <= m_iEndProcessSub && 100 > m_iEndProcessSub )	draw_fix(&m_vMst[17], ( 320 - m_vMst[17].pTex->GetImgW() ) / 2, 210);
		if ( 100 <= m_iEndProcessSub && 110 > m_iEndProcessSub )	draw_fix(&m_vMst[18], ( 320 - m_vMst[18].pTex->GetImgW() ) / 2, 210);
	}
	else if ( 10 == m_iEndProcess )
	{
		if (   0 <= m_iEndProcessSub &&  20 > m_iEndProcessSub )	draw_fix(&m_vBgt[4], 0, 0);
		if (  20 <= m_iEndProcessSub &&  50 > m_iEndProcessSub )	draw_fix(&m_vBgt[5], 0, 0);
	}
	
}


