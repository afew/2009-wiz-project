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

	// File ó�� ���� �Լ�
	// ���� ��� �ε����� �����Ѵ�. default = 0
	virtual void NED_FileChangeIndex ( int iIndex )=0;

	// ���� ���� ������ �����Ѵ�.
	// szOption�� Cǥ���� fopen �Լ��� �ɼ��� ������.
	// ���� ���� �� NED_FILE_OK ����
	virtual int  NED_FileOpen( char *szFileName, char *szOption )=0;

	// ���� �ִ� ���� �ڵ��� �ݴ´�.
	// ���� ���� �� NED_FILE_OK ����
	virtual int  NED_FileClose ( void )=0;

	// ������ ���̸� ��´�.
	// ���� ���� �� NED_FILE_OK ����
	virtual int  NED_FileGetLength ( char *szFileName )=0;

	// ���� �ִ� ������ �о���δ�.
	// ���� ���� �� NED_FILE_OK ����
	virtual int  NED_FileRead ( unsigned char *pbData, int iSize )=0;

	// Write �Լ� ����

	// ���� �ִ� ������ ������ ��ġ�� �����Ѵ�.
	// iOffset   : iPosition���κ����� ������
	// iPosition : ������ ����,
	// NED_FILE_BEGIN   - ó��
	// NED_FILE_END	    - ��
	// NED_FILE_CURRENT - ���� ��ġ
	// ���� ���� �� NED_FILE_OK ����
	virtual int  NED_FileSeek ( int iOffset, int iPosition )=0;

	
	// DRM ó�� ���� �Լ�
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





