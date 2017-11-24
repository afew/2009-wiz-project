/********************************************************************************

                Copyright(C) Gamepark Holdings. All rights reserved.
                             Dogma-G Game Studios
                             In-House Library DGE


                         C++ compiler support with SDL
                           (gcc-4.0.2-glibc-2.3.6)
                             # not included SDL #

********************************************************************************/

#ifndef __DGT_DRM_H__
#define __DGT_DRM_H__


#include <DGE_Type.h>

enum
{
	NED_FILE_OK					= 0x1,
	NED_FILE_ALREADY_OPEN		= 0xF0,
	NED_FILE_CANT_ACCESS		= 0xF1,
	NED_FILE_NOT_OPENED			= 0XF2,
	NED_FILE_GET_LENGTH_ERROR	= -1,

	NED_FILE_BEGIN				= 0,
	NED_FILE_END				= 1,
	NED_FILE_CURRENT			= 2,

	NED_MAX_OPEN_FILE			= 10,
};



typedef struct _NED_FileINFO
{
	unsigned char *	pbData;
	int				nLength;
 	_NED_FileINFO();
	~_NED_FileINFO();

} NED_BTC_INFO;


interface IDGT_DRM
{
	DGE_CLASS_DESTROYER(	IDGT_DRM	);

	// File 처리 관련 함수
	// 파일 사용 인덱스를 설정한다. default = 0
	virtual void NED_FileChangeIndex ( int iIndex )=0;

	// 열고 싶은 파일을 선택한다.
	// szOption은 C표준의 fopen 함수의 옵션을 따른다.
	// 정상 동작 시 NED_FILE_OK 리턴
	virtual int  NED_FileOpen( char *szFileName, char *szOption )=0;

	// 열고 있는 파일 핸들을 닫는다.
	// 정상 동작 시 NED_FILE_OK 리턴
	virtual int  NED_FileClose ( void )=0;

	// 파일의 길이를 얻는다.
	// 정상 동작 시 NED_FILE_OK 리턴
	virtual int  NED_FileGetLength ( char *szFileName )=0;

	// 열고 있는 파일을 읽어들인다.
	// 정상 동작 시 NED_FILE_OK 리턴
	virtual int  NED_FileRead ( unsigned char *pbData, int iSize )=0;

	// Write 함수 제외

	// 열고 있는 파일의 오프셋 위치를 변경한다.
	// iOffset   : iPosition으로부터의 오프셋
	// iPosition : 시작점 설정,
	// NED_FILE_BEGIN   - 처음
	// NED_FILE_END	    - 끝
	// NED_FILE_CURRENT - 지금 위치
	// 정상 동작 시 NED_FILE_OK 리턴
	virtual int  NED_FileSeek ( int iOffset, int iPosition )=0;

	
	// DRM 처리 관련 함수
	virtual int InitialNED()=0;
	virtual int TerminateNED()=0;
	virtual int InitialND()=0;
	virtual int TerminateND()=0;
};


typedef IDGT_DRM*		PDGT_DRM;


// Create DRM Handler
INT DGT_CreateDRM(char* sCmd
				   , PDGT_DRM* pData
				   , DGE_HANDLE p1 = NULL	// No Use
				   , DGE_HANDLE p2 = NULL	// No Use
				   , DGE_HANDLE p3 = NULL	// No Use
				   , DGE_HANDLE p4 = NULL	// No Use
					 );

// Destroy DRM Handler
INT DGT_DestroyDRM(PDGT_DRM* pData);


#endif





