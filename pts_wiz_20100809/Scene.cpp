// Implementation of the CMain class.
//
////////////////////////////////////////////////////////////////////////////////


#include "_StdAfx.h"


int	GetSceneState()
{
	return g_pApp->m_nScnSt;
}

void SetSceneState(int nState)
{
	g_pApp->m_nScnSt = nState;
}

long GetSceneDebugDisp()
{
	return g_pApp->m_nDebugDisp;
}

long GetSceneDebugStateProduct()
{
	return g_pApp->m_nDebugStageProduct;
}

long* GetSceneGameFlag1()
{
	return g_pApp->m_nGameFlag1;
}


long* GetSceneGameFlag2()
{
	return g_pApp->m_nGameFlag2;
}


long GetSceneGameFlag1(int nIdx)
{
	return g_pApp->m_nGameFlag1[nIdx];
}

void SetSceneGameFlag1(int nIdx, int v)
{
	if(nIdx == 5 || nIdx == 6)
	{
		int c;
		c=10;
	}

	g_pApp->m_nGameFlag1[nIdx] = v;
}

long GetSceneGameFlag2(int nIdx)
{
	return g_pApp->m_nGameFlag2[nIdx];
}

void SetSceneGameFlag2(int nIdx, int v)
{
	g_pApp->m_nGameFlag2[nIdx] = v;
}



void ResetGameFlag()
{
	memset( &g_pApp->m_nGameFlag1[0], 0, sizeof( g_pApp->m_nGameFlag1 ) );
}


int LoadGameFlag( char *fn )
{
	int hr = 0;
	FILE *fp;

	if ( ( fp = fopen( fn, "rb" ) ) == NULL )
	{
		hr = -1;
	}
	else
	{
		fread( &g_pApp->m_nGameFlag1[0], 1, sizeof( g_pApp->m_nGameFlag1 ), fp );
		fclose( fp );
#ifdef GP2X
		sync();
#endif
	}

	return hr;
}


int SaveGameFlag( char *fn )
{
	int hr = 0;
	FILE *fp;
	int size;

	if ( ( fp = fopen( fn, "wb" ) ) == NULL )
	{
		hr = -1;
	}
	else
	{
		size = (int)fwrite( &g_pApp->m_nGameFlag1[0], 1, sizeof( g_pApp->m_nGameFlag1 ), fp );
		fclose( fp );
#ifdef GP2X
		sync();
#endif
	}

	return hr;
}


void ResetGameFlag2()
{
	memset( &g_pApp->m_nGameFlag2[0], 0, sizeof( g_pApp->m_nGameFlag1 ) );
}


int LoadGameFlag2( char *fn )
{
	int hr = 0;
	FILE *fp;

	if ( ( fp = fopen( fn, "rb" ) ) == NULL )
	{
		hr = -1;
	}
	else
	{
		fread( &g_pApp->m_nGameFlag2[0], 1, sizeof( g_pApp->m_nGameFlag1 ), fp );
		fclose( fp );
#ifdef GP2X
		sync();
#endif
	}

	return hr;
}


int SaveGameFlag2( char *fn )
{
	int hr = 0;
	FILE *fp;

	if ( ( fp = fopen( fn, "wb" ) ) == NULL )
	{
		hr = -1;
	}
	else
	{
		fwrite( &g_pApp->m_nGameFlag2[0], 1, sizeof( g_pApp->m_nGameFlag1 ), fp );
		fclose( fp );
#ifdef GP2X
		sync();
#endif
	}

	return hr;
}



