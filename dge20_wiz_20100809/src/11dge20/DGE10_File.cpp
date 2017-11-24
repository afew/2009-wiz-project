// Implementation of the DGE File 1.0.
//
////////////////////////////////////////////////////////////////////////////////

#if defined(_WIN32) || defined(WIN32)
	#if _MSC_VER >= 1200
	#pragma warning(disable: 4996)
	#endif

	#include <io.h>
	#include <direct.h>

#else

	#include <unistd.h>
	#include <sys/stat.h>

#endif


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "DGE_Type.h"
#include "DGE_Util.h"



_FileINFO::_FileINFO()
{
	pbData = NULL;
	nLength = 0;
}

_FileINFO::~_FileINFO()
{
	if(pbData != NULL)
	{
		delete[] pbData;
		pbData = NULL;
	}
	nLength = 0;
}


class CDGE_File : public IDGE_File
{
public:
	static CDGE_File* g_cFile;

public:
	CDGE_File();
	virtual ~CDGE_File();

	virtual void ChangeIndex ( int iIndex );
	virtual int  Open( char *szFileName, char *szOption );
	virtual int  Close ( void );
	virtual int  GetLength ( char *szFileName );
	virtual int  Read ( unsigned char *pbData, int iSize );
	virtual int  Write ( unsigned char *pbData, int iSize );
	virtual int  Seek ( int iOffset, int iPosition );

	virtual BTC_INFO*	GetDataFromBFC ( char *szBfcName, char *szLoadFileName );
	virtual FILE*		GetFPFromBFC ( char *szBfcName, char *szLoadFileName );
	virtual char*		MakeFileFromBFC ( char *szBfcName, char *szLoadFileName );
	virtual int			ClearTempFile( char *szClearFileName );

protected:
	FILE*	m_FILE_dge [ MAX_OPEN_FILE ];
	int		m_iFileCurrent;
};



CDGE_File* CDGE_File::g_cFile	= NULL;

IDGE_File* DGE_File()
{
	if(NULL == CDGE_File::g_cFile)
		CDGE_File::g_cFile = new CDGE_File;


	return CDGE_File::g_cFile;
}




#if defined(_WIN32) || defined(WIN32)
const char* g_cTempFolder = "c:/windows/temp/";
#else
//char* g_cTempFolder = "/tmp/";
const char* g_cTempFolder = "/mnt/sd/temp/";

#endif





CDGE_File::CDGE_File()
{
	int iShit;

	m_iFileCurrent = 0;

	for ( iShit = 0; MAX_OPEN_FILE > iShit; iShit++ )
	{
		m_FILE_dge [ iShit ] = NULL;
	}

	if(DGE_LogGetState())
		DGE_Log()->Out("DGE_File :: CDGE_File done. _[%s][%d]\r\n", __FILE__, __LINE__);
}


/*------------------------------------------------------------------------------
 Function Name :: ~CDGE_File
 Return type   :: ...
 Return value  :: ...
 Input Value   :: ...
 Description   :: Destructor
------------------------------------------------------------------------------*/
CDGE_File::~CDGE_File()
{
	int iShit = 0;

	for ( iShit = 0; MAX_OPEN_FILE > iShit; iShit++ )
	{
		if ( NULL != m_FILE_dge [ iShit ] )
		{
			fclose ( m_FILE_dge [ iShit ] );
			m_FILE_dge [ iShit ] = NULL;
		}
	}

	if(DGE_LogGetState())
		DGE_Log()->Out("DGE_File :: ~CDGE_File done. _[%s][%d]\r\n", __FILE__, __LINE__);
}


/*------------------------------------------------------------------------------
Function Name :: DGE_Open
Return type   :: ...
Return value  :: ...
Input Value   :: ...
Description   :: 사용할 파일 배열 번호 설정
------------------------------------------------------------------------------*/
void CDGE_File::ChangeIndex ( int iIndex )
{
	if ( 0 > iIndex || MAX_OPEN_FILE <= iIndex )
	{
		if(DGE_LogGetState())
			DGE_Log()->Out("DGE_File :: ChangeIndex over range. _[%s][%d]\r\n", __FILE__, __LINE__);

		return;
	}

	m_iFileCurrent = iIndex;
}


/*------------------------------------------------------------------------------
 Function Name :: Open
 Return type   :: ...
 Return value  :: ...
 Input Value   :: ...
 Description   :: Open File.
------------------------------------------------------------------------------*/
int CDGE_File::Open( char *szFileName, char *szOption )
{
	if ( NULL != m_FILE_dge [ m_iFileCurrent ] )
	{
		return DGE_FILE_ALREADY_OPEN;
	}

	m_FILE_dge [ m_iFileCurrent ] = fopen ( szFileName, szOption );

	if ( NULL == m_FILE_dge [ m_iFileCurrent ] )
	{
		return DGE_FILE_CANT_ACCESS;
	}

	if(DGE_LogGetState())
		DGE_Log()->Out("DGE_File :: DGE_Open file opened. _[%s][%d]\r\n", __FILE__, __LINE__);


	return DGE_FILE_OK;
}


/*------------------------------------------------------------------------------
Function Name :: Close
Return type   :: ...
Return value  :: ...
Input Value   :: ...
Description   :: Close File.
------------------------------------------------------------------------------*/
int CDGE_File::Close ( void )
{
	if ( NULL == m_FILE_dge [ m_iFileCurrent ] )
	{
		return DGE_FILE_NOT_OPENED;
	}

	fclose ( m_FILE_dge [ m_iFileCurrent ] );
	m_FILE_dge [ m_iFileCurrent ] = NULL;


	if(DGE_LogGetState())
		DGE_Log()->Out("DGE_File :: DGE_Open file opened. _[%s][%d]\r\n", __FILE__, __LINE__);


	return DGE_FILE_OK;
}


/*------------------------------------------------------------------------------
Function Name :: GetLength
Return type   :: ...
Return value  :: ...
Input Value   :: ...
Description   :: return file size.
------------------------------------------------------------------------------*/
int CDGE_File::GetLength ( char *szFileName )
{
	FILE	*FILE_temp;
	int		iLength;

	FILE_temp = fopen ( szFileName, "rb" );
	if ( NULL == FILE_temp )
	{
		return DGE_FILE_GET_LENGTH_ERROR;
	}

	fseek ( FILE_temp, 0, SEEK_END );
	iLength = ftell ( FILE_temp );
	fclose ( FILE_temp );

	return iLength;
}


/*------------------------------------------------------------------------------
Function Name :: Read
Return type   :: ...
Return value  :: ...
Input Value   :: ...
Description   :: Read Data.
------------------------------------------------------------------------------*/
int CDGE_File::Read ( unsigned char *pbData, int iSize )
{
	if ( NULL == m_FILE_dge [ m_iFileCurrent ] )
	{
		return DGE_FILE_NOT_OPENED;
	}

	fread ( pbData, 1, iSize, m_FILE_dge [ m_iFileCurrent ] );

	return DGE_FILE_OK;
}

/*------------------------------------------------------------------------------
Function Name :: Write
Return type   :: ...
Return value  :: ...
Input Value   :: ...
Description   :: Write Data.
------------------------------------------------------------------------------*/
int CDGE_File::Write ( unsigned char *pbData, int iSize )
{
	if ( NULL == m_FILE_dge [ m_iFileCurrent ] )
	{
		return DGE_FILE_NOT_OPENED;
	}

	fwrite ( pbData, 1, iSize, m_FILE_dge [ m_iFileCurrent ] );

#ifndef _HOST_

	sync ();

#endif

	return DGE_FILE_OK;
}


/*------------------------------------------------------------------------------
Function Name :: Seek
Return type   :: ...
Return value  :: ...
Input Value   :: ...
Description   :: move file pointer.
------------------------------------------------------------------------------*/
int CDGE_File::Seek ( int iOffset, int iPosition )
{
	if ( NULL == m_FILE_dge [ m_iFileCurrent ] )
	{
		return DGE_FILE_NOT_OPENED;
	}

	switch ( iPosition )
	{
	case DGE_FILE_BEGIN:	fseek ( m_FILE_dge [ m_iFileCurrent ], iOffset, SEEK_SET );		break;
	case DGE_FILE_END:		fseek ( m_FILE_dge [ m_iFileCurrent ], iOffset, SEEK_END );		break;
	case DGE_FILE_CURRENT:	fseek ( m_FILE_dge [ m_iFileCurrent ], iOffset, SEEK_CUR );		break;
	}

	return DGE_FILE_OK;
}


/*------------------------------------------------------------------------------
Function Name :: GetDataFromBFC
Return type   :: ...
Return value  :: ...
Input Value   :: ...
Description   :: BFC파일에서 데이터를 뽑아 메모리에 올린 후 리턴
------------------------------------------------------------------------------*/
BTC_INFO* CDGE_File::GetDataFromBFC ( char *szBfcName, char *szLoadFileName )
{
	FILE			*FILE_bfc;
	int				iHeaderLength, iShit, iFileLength, iTotalLength;
	short			sFileAmount;
	char			szFileName [ 100 ];
	BTC_INFO		*btcINFO;
	btcINFO = new BTC_INFO;

	// bfc파일 오픈
	FILE_bfc = fopen ( szBfcName, "rb" );
	if ( FILE_bfc )
	{
		iTotalLength = 0;

		// 해더 길이 읽기
		fread ( &iHeaderLength, sizeof ( int ), 1, FILE_bfc );
		iTotalLength = iHeaderLength;

		// 파일 개수
		fread ( &sFileAmount, sizeof ( short ), 1, FILE_bfc );

		// 돌면서 확인
		for ( iShit = 0; sFileAmount > iShit; iShit++ )
		{
			// 이름 읽기
			fread ( szFileName, sizeof ( char ), 100, FILE_bfc );

			// 길이
			fread ( &iFileLength, sizeof ( int ), 1, FILE_bfc );

			if ( 0 == strcmp ( szFileName, szLoadFileName ) )
			{
				// 메모리 할당
				btcINFO->pbData = new unsigned char [ iFileLength ];

				// 읽어들이기
				fseek ( FILE_bfc, iTotalLength, SEEK_SET );
				fread ( btcINFO->pbData, sizeof ( unsigned char ), iFileLength, FILE_bfc );
				btcINFO->nLength = iFileLength;
				break;
			}

			// 길이 증가
			iTotalLength += iFileLength;
		}

		fclose ( FILE_bfc );
	}

	return btcINFO;
}

FILE* CDGE_File::GetFPFromBFC( char *szBfcName, char *szLoadFileName )
{
	FILE			*FILE_bfc;
	int				iHeaderLength, iShit, iFileLength, iTotalLength;
	short			sFileAmount;
	char			szFileName [ 100 ];
//	BTC_INFO		*btcINFO;
//	btcINFO = new BTC_INFO;

	// bfc파일 오픈
	FILE_bfc = fopen ( szBfcName, "rb" );
	if ( FILE_bfc )
	{
		iTotalLength = 0;

		// 해더 길이 읽기
		fread ( &iHeaderLength, sizeof ( int ), 1, FILE_bfc );
		iTotalLength = iHeaderLength;

		// 파일 개수
		fread ( &sFileAmount, sizeof ( short ), 1, FILE_bfc );

		// 돌면서 확인
		for ( iShit = 0; sFileAmount > iShit; iShit++ )
		{
			// 이름 읽기
			fread ( szFileName, sizeof ( char ), 100, FILE_bfc );

			// 길이
			fread ( &iFileLength, sizeof ( int ), 1, FILE_bfc );

			if ( 0 == strcmp ( szFileName, szLoadFileName ) )
			{
				// 메모리 할당
				//btcINFO->pbData = new unsigned char [ iFileLength ];

				// 읽어들이기
				fseek ( FILE_bfc, iTotalLength, SEEK_SET );
				//fread ( btcINFO->pbData, sizeof ( unsigned char ), iFileLength, FILE_bfc );
				//btcINFO->nLength = iFileLength;
				break;
			}

			// 길이 증가
			iTotalLength += iFileLength;
		}

		//fclose ( FILE_bfc );
	}

	return FILE_bfc;
}

char* CDGE_File::MakeFileFromBFC( char *szBfcName, char *szLoadFileName )
{
	FILE			*FILE_bfc, *FILE_Dest;
	int				iHeaderLength, iShit, iFileLength, iTotalLength;
	short			sFileAmount;
	char			szFileName [ 100 ] = { 0, };
	static char		szDestination[ 512 ] = { 0, };

	memset(szDestination, 0, 512);
	strcpy( szDestination, g_cTempFolder );
	strcat( szDestination, szLoadFileName );
	BTC_INFO		*btcINFO;
	btcINFO = new BTC_INFO;

	// bfc파일 오픈
	FILE_bfc = fopen ( szBfcName, "rb" );
	if ( FILE_bfc )
	{
		iTotalLength = 0;

		// 해더 길이 읽기
		fread ( &iHeaderLength, sizeof ( int ), 1, FILE_bfc );
		iTotalLength = iHeaderLength;

		// 파일 개수
		fread ( &sFileAmount, sizeof ( short ), 1, FILE_bfc );

		// 돌면서 확인
		for ( iShit = 0; sFileAmount > iShit; iShit++ )
		{
			// 이름 읽기
			fread ( szFileName, sizeof ( char ), 100, FILE_bfc );

			// 길이
			fread ( &iFileLength, sizeof ( int ), 1, FILE_bfc );

			if ( 0 == strcmp ( szFileName, szLoadFileName ) )
			{
				// 메모리 할당
				btcINFO->pbData = new unsigned char [ iFileLength ];

				// 읽어들이기
				fseek ( FILE_bfc, iTotalLength, SEEK_SET );
				fread ( btcINFO->pbData, sizeof ( unsigned char ), iFileLength, FILE_bfc );
				btcINFO->nLength = iFileLength;
				break;
			}

			// 길이 증가
			iTotalLength += iFileLength;
		}

		fclose ( FILE_bfc );
	}
	FILE_Dest = fopen( szDestination, "wb" );

	if (FILE_Dest == NULL)
	{

		if(DGE_LogGetState())
			DGE_Log()->Out("DGE_Render :: DGE_Render done. _[%s][%d]\r\n", __FILE__, __LINE__);

	} else
	{
		fwrite(btcINFO->pbData, btcINFO->nLength, 1, FILE_Dest);
		fclose(FILE_Dest);

		if(DGE_LogGetState())
			DGE_Log()->Out("DGE_Render :: DGE_Render done. _[%s][%d]\r\n", __FILE__, __LINE__);

		return szDestination;
	}
	return NULL;
}

int CDGE_File::ClearTempFile( char *szClearFileName )
{
	return DGE_FILE_OK;
}

