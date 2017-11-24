/********************************************************************************

                Copyright(C) Gamepark Holdings. All rights reserved.
                             Dogma-G Game Studios
                             In-House Library DGE


                         C++ compiler support with SDL
                           (gcc-4.0.2-glibc-2.3.6)

********************************************************************************/

#if defined(_WIN32) || defined(WIN32)
	#if _MSC_VER >= 1200
	#pragma warning(disable: 4996)
	#endif

	#include <windows.h>

#else

	#include <unistd.h>

#endif


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "drmcode/drmcode.h"
#include "NEDv294/NED.h"
#include "NEDv294/NED_WIZ.h"
#include "NEDv294/NED_FS.h"
#include "NEDv294/NED_Variable.h"
#include "NEDv294/NED_Service.h"
#include "NEDv294/NED_Type.h"
#include "NEDv294/NED_ND.h"

#include "DGT_DRM.h"
#include "DGE_Util.h"



class CDGT_DRM : public IDGT_DRM
{
public:
	static CDGT_DRM* g_cDRM;
protected:
	FILE	*m_FILE_NED [ NED_MAX_OPEN_FILE ];
	int		m_iFileCurrent;

public:
	CDGT_DRM();
	virtual ~CDGT_DRM();

	void NED_FileChangeIndex ( int iIndex );
	int  NED_FileOpen( char *szFileName, char *szOption );
	int  NED_FileClose ( void );
	int  NED_FileGetLength ( char *szFileName );
	int  NED_FileRead ( unsigned char *pbData, int iSize );
	int  NED_FileSeek ( int iOffset, int iPosition );
	
	int InitialNED();
	int TerminateNED();
	int InitialND();
	int TerminateND();

	NED_BTC_INFO* GetDataFromDrm ( char *szBfcName, char *szLoadFileName );
};



CDGT_DRM* CDGT_DRM::g_cDRM = NULL;



// Create DRM Handler
INT DGT_CreateDRM(char* sCmd
				   , PDGT_DRM* pData
				   , DGE_HANDLE p1
				   , DGE_HANDLE p2
				   , DGE_HANDLE p3
				   , DGE_HANDLE p4
					 )
{
	if(NULL == CDGT_DRM::g_cDRM)
		CDGT_DRM::g_cDRM = new CDGT_DRM;


	*pData = CDGT_DRM::g_cDRM;
	return DGE_OK;
}

// Destroy DRM Handler
INT DGT_DestroyDRM(PDGT_DRM* pData)
{
	if(CDGT_DRM::g_cDRM)
	{
		CDGT_DRM::g_cDRM->TerminateNED();
		
		delete CDGT_DRM::g_cDRM;
		CDGT_DRM::g_cDRM = NULL;
	}

	*pData = NULL;
	return DGE_OK;
}






/*------------------------------------------------------------------------------
 Function Name :: CDGT_DRM
 Return type   :: ...
 Return value  :: ...
 Input Value   :: ...
 Description   :: Constructor
------------------------------------------------------------------------------*/
CDGT_DRM::CDGT_DRM()
{
	int iShit;

	m_iFileCurrent = 0;

	for ( iShit = 0; NED_MAX_OPEN_FILE > iShit; iShit++ )
	{
		m_FILE_NED [ iShit ] = NULL;
	}

	if(DGE_LogGetState())
		DGE_Log()->Out("DGT_DRM :: CDGT_DRM done. _[%s][%d]\r\n", __FILE__, __LINE__);
}


/*------------------------------------------------------------------------------
 Function Name :: ~CDGT_DRM
 Return type   :: ...
 Return value  :: ...
 Input Value   :: ...
 Description   :: Destructor
------------------------------------------------------------------------------*/
CDGT_DRM::~CDGT_DRM()
{
	int iShit = 0;

	for ( iShit = 0; NED_MAX_OPEN_FILE > iShit; iShit++ )
	{
		if ( NULL != m_FILE_NED [ iShit ] )
		{
			NED_fclose ( m_FILE_NED [ iShit ] );
			m_FILE_NED [ iShit ] = NULL;
		}
	}

	if(DGE_LogGetState())
		DGE_Log()->Out("DGT_DRM :: ~CDGT_DRM done. _[%s][%d]\r\n", __FILE__, __LINE__);
}

// File 처리 관련 함수

/*------------------------------------------------------------------------------
Function Name :: NED_FileChangeIndex
Return type   :: ...
Return value  :: ...
Input Value   :: ...
Description   :: 사용할 파일 배열 번호 설정
------------------------------------------------------------------------------*/
void CDGT_DRM::NED_FileChangeIndex ( int iIndex )
{
	if ( 0 > iIndex || NED_MAX_OPEN_FILE <= iIndex )
	{

		if(DGE_LogGetState())
			DGE_Log()->Out("DGT_DRM :: NED_FileChangeIndex over range. _[%s][%d]\r\n", __FILE__, __LINE__);

		return;
	}

	m_iFileCurrent = iIndex;
}

/*------------------------------------------------------------------------------
 Function Name :: NED_FileOpen
 Return type   :: ...
 Return value  :: ...
 Input Value   :: ...
 Description   :: Open File.
------------------------------------------------------------------------------*/
int CDGT_DRM::NED_FileOpen( char *szFileName, char *szOption )
{
	// 매개변수 유효성 확인
	if( NULL == szFileName || NULL == szOption )
	{
		return NED_FILE_CANT_ACCESS;
	}

	if ( NULL != m_FILE_NED [ m_iFileCurrent ] )
	{
		return NED_FILE_ALREADY_OPEN;
	}

	m_FILE_NED [ m_iFileCurrent ] = NED_fopen ( szFileName, szOption );

	if ( NULL == m_FILE_NED [ m_iFileCurrent ] )
	{
		return NED_FILE_CANT_ACCESS;
	}

	if(DGE_LogGetState())
		DGE_Log()->Out("DGT_DRM :: NED_FileOpen done. _[%s][%d]\r\n", __FILE__, __LINE__);

	return NED_FILE_OK;
}

/*------------------------------------------------------------------------------
Function Name :: NED_FileClose
Return type   :: ...
Return value  :: ...
Input Value   :: ...
Description   :: Close File.
------------------------------------------------------------------------------*/
int CDGT_DRM::NED_FileClose ( void )
{
	if ( NULL == m_FILE_NED [ m_iFileCurrent ] )
	{
		return NED_FILE_NOT_OPENED;
	}

	NED_fclose ( m_FILE_NED [ m_iFileCurrent ] );
	m_FILE_NED [ m_iFileCurrent ] = NULL;


	if(DGE_LogGetState())
		DGE_Log()->Out("DGT_DRM :: NED_FileClose done. _[%s][%d]\r\n", __FILE__, __LINE__);

	return NED_FILE_OK;
}

/*------------------------------------------------------------------------------
Function Name :: NED_FileGetLength
Return type   :: ...
Return value  :: ...
Input Value   :: ...
Description   :: return file size.
------------------------------------------------------------------------------*/
int CDGT_DRM::NED_FileGetLength ( char *szFileName )
{
	FILE	*FILE_temp;
	int		iLength;

	FILE_temp = NED_fopen ( szFileName, "rb" );
	if ( NULL == FILE_temp )
	{
		return NED_FILE_GET_LENGTH_ERROR;
	}

	NED_fseek ( FILE_temp, 0, SEEK_END );
	iLength = NED_ftell ( FILE_temp );
	NED_fclose ( FILE_temp );

	return iLength;
}

/*------------------------------------------------------------------------------
Function Name :: NED_FileRead
Return type   :: ...
Return value  :: ...
Input Value   :: ...
Description   :: Read Data.
------------------------------------------------------------------------------*/
int CDGT_DRM::NED_FileRead ( unsigned char *pbData, int iSize )
{
	// 매개변수 유효성 확인
	if( NULL == pbData || 0 > iSize )
	{
		return NED_FILE_CANT_ACCESS;
	}

	if ( NULL == m_FILE_NED [ m_iFileCurrent ] )
	{
		return NED_FILE_NOT_OPENED;
	}

	NED_fread ( pbData, 1, iSize, m_FILE_NED [ m_iFileCurrent ] );

	return NED_FILE_OK;
}

/*------------------------------------------------------------------------------
Function Name :: NED_FileSeek
Return type   :: ...
Return value  :: ...
Input Value   :: ...
Description   :: move file pointer.
------------------------------------------------------------------------------*/
int CDGT_DRM::NED_FileSeek ( int iOffset, int iPosition )
{
	if ( NULL == m_FILE_NED [ m_iFileCurrent ] )
	{
		return NED_FILE_NOT_OPENED;
	}

	switch ( iPosition )
	{
	case NED_FILE_BEGIN:	fseek ( m_FILE_NED [ m_iFileCurrent ], iOffset, SEEK_SET );		break;
	case NED_FILE_END:		fseek ( m_FILE_NED [ m_iFileCurrent ], iOffset, SEEK_END );		break;
	case NED_FILE_CURRENT:	fseek ( m_FILE_NED [ m_iFileCurrent ], iOffset, SEEK_CUR );		break;
	}

	return NED_FILE_OK;
}

// DRM 처리 관련 함수

int CDGT_DRM::InitialNED()
{
	int result = 0;
#ifndef _HOST_
	NED_U32 randnum = 0;
	unsigned char codeBuf[32] = {0,};
	unsigned char serialBuf[24] = {0,};
	unsigned char timeBuf[8] = {0,};
	unsigned char DRMCheck;
	unsigned char LICValue[512] = {0, };
	memset((void*)&gNEDLicense, 0, sizeof(gNEDLicense));
	memset((void*)&gND_Info, 0, sizeof(gND_Info));
	NED_U8 RemainNumber = 0;
	FILE* DRMFile;
	getcode(codeBuf);
	getserial(serialBuf);
	getrandnum((unsigned char*)&randnum);
	com_drm_time(timeBuf);
	result = NED_Initialize(randnum,timeBuf,WIZ_VID,WIZ_PID,codeBuf,sizeof(codeBuf));
#endif
	return result;
}

int CDGT_DRM::TerminateNED()
{
	return 0;
}

int CDGT_DRM::InitialND()
{
	int result = 0;
#ifndef _HOST_
	NED_U32 randnum = 0;
	unsigned char codeBuf[32] = {0,};
	unsigned char serialBuf[24] = {0,};
	unsigned char timeBuf[8] = {0,};
	unsigned char DRMCheck;
	unsigned char LICValue[512] = {0, };
	memset((void*)&gNEDLicense, 0, sizeof(gNEDLicense));
	memset((void*)&gND_Info, 0, sizeof(gND_Info));
	NED_U8 RemainNumber = 0;
	FILE* DRMFile;
	getcode(codeBuf);
	getserial(serialBuf);
	getrandnum((unsigned char*)&randnum);
	com_drm_time(timeBuf);
	result = NED_Initialize(randnum,timeBuf,WIZ_VID,WIZ_PID,codeBuf,sizeof(codeBuf));

	result = ND_Initialize();
#endif
	return result;
}

int CDGT_DRM::TerminateND()
{
	int result = 0;
#ifndef _HOST_
	ND_Terminate();
#endif
	return result;
}

NED_BTC_INFO* CDGT_DRM::GetDataFromDrm( char *szBfcName, char *szLoadFileName )
{
	FILE			*FILE_bfc;
	int				iHeaderLength, iShit, iFileLength, iTotalLength;
	short			sFileAmount;
	char			szFileName [ 100 ];
	NED_BTC_INFO	*btcINFO;
	btcINFO = new NED_BTC_INFO;

	// bfc파일 오픈

	FILE_bfc = NED_fopen ( szBfcName, "rb" );

	if ( FILE_bfc )
	{
		iTotalLength = 0;

		// 해더 길이 읽기

		NED_fread ( &iHeaderLength, sizeof ( int ), 1, FILE_bfc );

		iTotalLength = iHeaderLength;

		// 파일 개수
		NED_fread ( &sFileAmount, sizeof ( short ), 1, FILE_bfc );

		// 돌면서 확인
		for ( iShit = 0; sFileAmount > iShit; iShit++ )
		{
			// 이름 읽기
			NED_fread ( szFileName, sizeof ( char ), 100, FILE_bfc );
			NED_fread ( &iFileLength, sizeof ( int ), 1, FILE_bfc );


			if ( 0 == strcmp ( szFileName, szLoadFileName ) )
			{
				// 메모리 할당
				btcINFO->pbData = new unsigned char [ iFileLength ];

				// 읽어들이기
				NED_fseek ( FILE_bfc, iTotalLength, SEEK_SET );
				NED_fread ( btcINFO->pbData, sizeof ( unsigned char ), iFileLength, FILE_bfc );

				btcINFO->nLength = iFileLength;
				break;
			}

			// 길이 증가
			iTotalLength += iFileLength;
		}

		NED_fclose ( FILE_bfc );
	}

	return btcINFO;
}

// 내부 사용 구조체

_NED_FileINFO::_NED_FileINFO()
{
	pbData = NULL;
	nLength = 0;
}

_NED_FileINFO::~_NED_FileINFO()
{
	if(pbData != NULL)
	{
		delete[] pbData;
		pbData = NULL;
	}
	nLength = 0;
}


