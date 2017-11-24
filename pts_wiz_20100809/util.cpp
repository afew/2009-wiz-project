
#if defined(_WIN32) || defined(WIN32)
#pragma warning(disable: 4819 4996)
#endif



#include "_StdAfx.h"



int SaveFile( char *fn, long *buff, long size )
{
	int hr = 0;
	FILE *fp;

	if ( ( fp = fopen( fn, "wb" ) ) == NULL )
	{
//		printf("file open error!!\n");
		hr = -1;
	}
	else
	{
		fwrite( buff, 1, size, fp );
		fclose( fp );
#ifdef GP2X
		sync();
#endif
	}

	return hr;
}


int LoadFile( char *fn, long *buff, long size )
{
	int hr = 0;
	FILE *fp;

	if ( ( fp = fopen( fn, "rb" ) ) == NULL )
	{
//		printf("file open error!!\n");
		hr = -1;
	}
	else
	{
		fread( buff, 1, size, fp );
		fclose( fp );
#ifdef GP2X
		sync();
#endif
	}

	return hr;
}


long GetConfig( char* fn, char* cParam )
{
	FILE *fp;
	char *sp;
	char s[256];
	char s2[256];
	long hr;
	int iIsWhile;

	memset( s, '\0', sizeof( s ) );

	hr = 0;
	if ( ( fp = fopen( fn, "r" ) ) == NULL )
	{
		hr = 0;
	}
	else
	{
		iIsWhile = 1;

		while ( 1 == iIsWhile && fgets( s, 256, fp ) != NULL )
		{
			if ( strstr( s, cParam ) != NULL )
			{
				sp = NULL;

				sp = strstr( s, "=" );
				if ( sp != NULL )
				{
					sp++;
					memset( s2, '\0', sizeof( s ) );
					if ( ! ( ( *sp >= '0' && *sp <= '9' ) || ( *sp =='-' ) ) )
					{
						return 0;
					}
					while ( *sp >= '0' && *sp <= '9' )
					{
						hr = hr * 10 + ( *sp - '0' );
						sp++;
					}
				}
				iIsWhile = 0;
			}
			memset( s, '\0', sizeof( s ) );
		}
#ifdef GP2X
		sync();
#endif
	}

	return hr;
}


long LogFileWrite( char* fn, char* cParam )
{
	FILE *fp;
	long hr;

	hr = 0;
	if ( ( fp = fopen( fn, "w" ) ) == NULL )
	{
		hr = 0;
	}
	else
	{
		fputs( cParam, fp);
#ifdef GP2X
		sync();
#endif
	}
	return( hr );
}




long funcSin( long rdo )
{
	long ang = 0;
	long hr = 0;

	if ( ( rdo >= 0 ) && ( rdo < 180 ) )
	{
		ang = ( ( 65535 * rdo ) / 360 );
		hr = MOTsin( ang );
	}
	if ( ( rdo >= 180 ) && ( rdo < 360 ) )
	{
		rdo = rdo - 180;
		ang = ( ( 65535 * rdo ) / 360 );
		hr = MOTsin( ang );
		hr = hr * -1;
	}

	return( hr );
}


long funcCos( long rdo )
{
	long ang = 0;
	long hr = 0;

	if ( ( rdo >= 0 ) && ( rdo < 180 ) )
	{
		ang = ( ( 65535 * rdo ) / 360 );
		hr = MOTcos( ang );
	}
	if ( ( rdo >= 180 ) && ( rdo < 360 ) )
	{
		rdo = rdo - 180;
		ang = ( ( 65535 * rdo ) / 360 );
		hr = MOTcos( ang );
		hr = hr * -1;
	}

	return( hr );
}



long funcTan2( long posX, long posY )
{
	long hr = 0;

	hr = MOTatan( ( posX ) * 256, ( posY * -1 ) * 256 );

	return( hr );
}


long get2keta( long val, long st )
{
	long hr = 0;

	val = val / st;
	hr = val % 100;

	return( hr );
}



