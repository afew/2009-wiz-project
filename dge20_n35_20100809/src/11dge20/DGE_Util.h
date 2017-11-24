// Copyright(C) Gamepark Holdings. All rights reserved.
// Dogma-G Game Studios In-House Library DGE
//
// DGE SDK Auxiliary Program
//
////////////////////////////////////////////////////////////////////////////////


#if defined(_WIN32) || defined(WIN32)
	#if _MSC_VER > 1000
	#pragma once
	#endif
#endif


#ifndef _DGE_Util_H_
#define _DGE_Util_H_

#include "DGE_Type.h"



// Utilty Macro

#define SAFE_FREE(p)				\
{ if(p) {							\
		free(p); (p) = NULL;		\
} }

#define SAFE_DELETE(p)				\
{ if(p) {							\
		delete (p);	(p) = NULL;		\
} }

#define SAFE_DELETE_ARRAY(p)		\
{ if(p) {							\
		delete [] (p); (p) = NULL;	\
} }

#define SAFE_NEWCREATE1(p, CLASSTYPE, P1)				\
{ if(!(p)) {											\
		p = new CLASSTYPE;								\
		if(!(p)) {	return -1;	}						\
														\
		if(DGE_FAILED(((CLASSTYPE *)p)->Create(P1)))	\
		{												\
			delete p; p=(NULL); return -1;				\
		}												\
} }

#define SAFE_NEWCREATE2(p, CLASSTYPE, P1, P2)				\
{ if(!(p)) {												\
		p = new CLASSTYPE;									\
		if(!(p)) {	return -1;	}							\
															\
		if(DGE_FAILED(((CLASSTYPE *)p)->Create(P1, P2)))	\
		{													\
			delete p; p=(NULL); return -1;					\
		}													\
} }

#define SAFE_NEWCREATE3(p, CLASSTYPE, P1, P2, P3)				\
{ if(!(p)) {													\
		p = new CLASSTYPE;										\
		if(!(p)) {	return -1;	}								\
																\
		if(DGE_FAILED(((CLASSTYPE *)p)->Create(P1, P2, P3)))	\
		{														\
			delete p; p=(NULL); return -1;						\
		}														\
} }

#define SAFE_NEWCREATE4(p, CLASSTYPE, P1, P2, P3, P4)				\
{ if(!(p)) {														\
		p = new CLASSTYPE;											\
		if(!(p)) {	return -1;	}									\
																	\
		if(DGE_FAILED(((CLASSTYPE *)p)->Create(P1, P2, P3, P4)))	\
		{															\
			delete p; p=(NULL); return -1;							\
		}															\
} }



////////////////////////////////////////////////////////////////////////////////
// DGE Memory

void*	DgeMem_Allock(int BuffSize,int Count,int InitSetVal=0);	// malloc + memset(InitSetVal)
void	DgeMem_Free(void** v);									// free(*v) + *v = NULL;


////////////////////////////////////////////////////////////////////////////////
// DGE String

inline int DgeStr_tolower(int c);								// Redefine tolower()
inline int DgeStr_toupper(int c);								// Redefine toupper()

int		DgeStr_Stricmp (const char* s1, const char* s2);			// Redefine _stricmp()
int		DgeStr_Strnicmp(const char* s1, const char* s2, size_t n);	// Redefine _strnicmp()

void	DgeStr_SplitPath(						// Redefine _splitpath()
					  const char *path			// Input Path
					,	char *drive				// split drive Need 260 bytes
					,	char *dir				// split directory
					,	char *fname				// split file name
					,	char *ext				// split extension
					);



////////////////////////////////////////////////////////////////////////////////
// DGE File
enum
{
	DGE_TYPE_FOLDER	= 0X10,
	DGE_TYPE_FILE	= 0X20,
};

typedef struct tagTDGE_FINDDATA
{
    unsigned int	attrib;
    long			time_create;    /* -1 for FAT file systems */
    long			time_access;    /* -1 for FAT file systems */
    long			time_write;
    unsigned long	size;
    char			name[260];
}TDGE_FINDDATA;


typedef struct tagTDGE_FINF
{
	int		nType;		// Folder: 0x10, File: 0x20
	long	lDate;		// Make Date
	long	lBuf;		// Length of File Buffer
	long	lBufB;		// Start Buffer in Merge File
	long	lt1;		// temp1
	long	lt2;		// temp2
	long	lt3;		// temp3
	long	lt4;		// temp4
	long	iname;		// Length of File Name
	char*	name;		// File Name

	tagTDGE_FINF*	pNext;
}TDGE_FINF;


long	DgeFile_FindFirst(TDGE_FINDDATA* pFindData, const char* sSearPath);		// Redefine _findfirst()
int		DgeFile_FindNext(long handle, TDGE_FINDDATA* pFindData);				// Redefine _findnext()
int		DgeFile_FindClose(long handle);											// Redefine _findClose()

void	DgeFile_GatherAllFiles(TDGE_FINF** pOut, const char* sStartRoot);
void	DgeFile_GatherFree(TDGE_FINF** pIn);

int		DgeFile_mkdir(const char* sFolder, unsigned int mod= 0777);				// Redefine mkdir()
int		DgeFile_rmdir(const char* sFolder);										// Redefine rmdir()





////////////////////////////////////////////////////////////////////////////////
// DGE 1.0 Log for Debugging
enum
{
	DGE_LOG_WAY_NO		= -1,		// can't write log.
	DGE_LOG_WAY_SERIAL	=  0,		// default.
	DGE_LOG_WAY_FILE	=  1,		// It will make a dge_log.txt with 'wb' option.
	DGE_LOG_WAY_MIX		=  2,		// not supported.
};


interface IDGE_Log
{
	DGE_CLASS_DESTROYER(	IDGE_Log	);

	virtual void Out(const char *szFormat, ...)=0;
	virtual void SetWay(int iWay)=0;
};


void		DGE_LogSetSate(int	v);	/*1(TRUE):Enable, 0(FALSE):Disable*/
int			DGE_LogGetState();
IDGE_Log*	DGE_Log();			// for DGE debugging. but you can it in your works. extern IDGE_Log*	g_cDGELog





////////////////////////////////////////////////////////////////////////////////
// DGE 1.0 File

enum
{
	DGE_FILE_OK					=	0x1,
	DGE_FILE_ALREADY_OPEN		=	0xF0,
	DGE_FILE_CANT_ACCESS		=	0xF1,
	DGE_FILE_NOT_OPENED			=	0XF2,
	DGE_FILE_GET_LENGTH_ERROR	=	-1,

	DGE_FILE_BEGIN				=	0,
	DGE_FILE_END				=	1,
	DGE_FILE_CURRENT			=	2,

	MAX_OPEN_FILE				=	10,
};

typedef struct _FileINFO
{
	unsigned char *	pbData;
	int				nLength;
 	_FileINFO();
	~_FileINFO();
} BTC_INFO;



#include <stdio.h>

interface IDGE_File
{
	DGE_CLASS_DESTROYER(	IDGE_File	);

	// ���� ��� �ε����� �����Ѵ�. default = 0
	virtual void ChangeIndex ( int iIndex )=0;

	// ���� ���� ������ �����Ѵ�.
	// szOption�� Cǥ���� fopen �Լ��� �ɼ��� ������.
	// ���� ���� �� DGE_FILE_OK ����
	virtual int  Open( char *szFileName, char *szOption )=0;

	// ���� �ִ� ���� �ڵ��� �ݴ´�.
	// ���� ���� �� DGE_FILE_OK ����
	virtual int  Close ( void )=0;

	// ������ ���̸� ��´�.
	// ���� ���� �� DGE_FILE_OK ����
	virtual int  GetLength ( char *szFileName )=0;

	// ���� �ִ� ������ �о���δ�.
	// ���� ���� �� DGE_FILE_OK ����
	virtual int  Read ( unsigned char *pbData, int iSize )=0;

	// ���� �ִ� ���Ͽ� �ۼ��Ѵ�.
	// ���� ���� �� DGE_FILE_OK ����
	virtual int  Write ( unsigned char *pbData, int iSize )=0;

	// ���� �ִ� ������ ������ ��ġ�� �����Ѵ�.
	// iOffset   : iPosition���κ����� ������
	// iPosition : ������ ����,
	// DGE_FILE_BEGIN   - ó��
	// DGE_FILE_END	    - ��
	// DGE_FILE_CURRENT - ���� ��ġ
	// ���� ���� �� DGE_FILE_OK ����
	virtual int  Seek ( int iOffset, int iPosition )=0;

	// �̻�� �Լ�
	virtual BTC_INFO* GetDataFromBFC ( char *szBfcName, char *szLoadFileName )=0;
	virtual FILE* GetFPFromBFC ( char *szBfcName, char *szLoadFileName )=0;
	virtual char* MakeFileFromBFC ( char *szBfcName, char *szLoadFileName )=0;
	virtual int ClearTempFile( char *szClearFileName )=0;
};


IDGE_File*	DGE_File();



#endif




