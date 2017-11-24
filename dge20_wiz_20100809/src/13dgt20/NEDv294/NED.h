/*
***************************************************************************************************
Project		: NED Ver 2.9
Description	: NED API Function Define

History 	: 2004.04.14 - 최초 작성 (by MrAws)
		  2004.08.31 - NSEL부분 수정 (by MrAws)
		  2004.08.31 - TCC72x 환경에 맞게 수정 (by shell)
		  2004.09.09 - 인증서부분 빼고 고유ID로 처리하도록 수정 (by shell)
		  2006.07.05 - 버전별 TYPE별 Define관리 하도록 수정 (by Felix.Kim)
		  2006.10.24 - NED lice_info struct ServicRule 변수 추가 NEDv2.91 (by Felix.Kim)
		  2006.12.?? - ND 추가 NEDv2.92 (by Felix.Kim)
		  2007.06.?? - License Data 64 -> 512 확장  (by Felix.Kim)
		  2007.07.?? - LMS 추가 NEDv2.94 (by CyclonPark)

Copyright (C) 2003 ~ 2007 Inka Entwork Corp. <www.inka.co.kr>
All Rights Reserved.
***************************************************************************************************
*/

#ifndef _NED_H
#define _NED_H

//#include "../NED_TYPE/NED_Type.h"
#include "NED_Type.h"

/* Version Definition  */
#define	NED_VERSION		0x0294

/* NED Definition */
#define NED_HEADER			512

#if (NED_VERSION >= 0x0293)
	#define NED_LICENSE			512
#else
	#define NED_LICENSE			64
#endif /* (NED_VERSION >= 0x0293) */

#define NED_HIDDEN_LICENSE	64
#define NED_BLOCK			512		
#define NEM_BLOCK			1024
#define NED_AES				1
#define NED_RC4_2			2
#define NED_RC4_8			3
#define NED_STMP			5
#define NED_NEXTDISC		6
#define NED_7BIT_BLOCK		448
#define MAX_MULTI			4

/* LICENSE TYPE Definition */
#define	SERIAL_TYPE
//#define HIDDEN_TYPE


#define OUT_OF_SERIAL_RANGE	// 090429 roy - for robustness out of serial range


/* Service Rule Definition */
#define META_SERVICE	// 메타 Data 서비스

#if (NED_VERSION >= 0x0290)
#define MONTHLY_RULE	// 월정액 서비스
#define TIME_RULE	// 기간제 서비스
//#define COUNT_RULE	// 횟수제한 서비스
#endif /* (NED_VERSION >= 0x0290) */

/* NED Service Flag Definition */
#if (NED_VERSION >= 0x0291)
	#define V291_COUNT_RULE		1
	#define V291_MONTHLY_RULE		2
	#define V291_TIME_RULE			4
#endif /* (NED_VERSION >= 0x0291) */

#if (NED_VERSION >= 0x0292)
	#define NEXT_DISC
#endif /* (NED_VERSION >= 0x0292) */

#if (NED_VERSION >= 0x0293)
 	/* 디큐 T43/V43 set 일경우 메가스터디 횟수 카운터 독립 API 운용 */
	//#define V43T43_COUNT_RULE
#endif /* (NED_VERSION >= 0x0292) */

#if (NED_VERSION >= 0x0294)
//	#define NED_LMS		// LMS 서비스
#endif /* (NED_VERSION >= 0x0294) */


/* NED Meta definition */
#ifdef META_SERVICE
	#define NEM_TITLE		1
	#define NEM_ARTIST		2
	#define NEM_ALBUM		3
	#define NEM_GENRE		4
	#define NEM_COMMENT		5
	#define NEM_COMPOSER		6
	#define NEM_ORIARTIST		7
	#define NEM_COPYRIGHT		8
	#define NEM_ENCODEDBY		9
	#define NEM_TRACK		10
	#define NEM_YEAR		11
	#define NEM_TYPE		12
	#define NEM_LAYER		13
	#define NEM_BITRATE		14
	#define NEM_FREQUENCY		15
	#define NEM_MODE		16
	#define NEM_PLAYTIME		17
#endif /* META_SERVICE */


/* NED Permission definition  */ 
#define RES_NOLIMIT		0
#define RES_TIME		1
#define RES_COUNT		2
#define RES_BELL			4


#ifdef 	MONTHLY_RULE
	#define RES_MONTHLY		8		// supported by v2.8 above
	#define MAX_SID				128		// Max Site License Table
#endif /* MONTHLY_RULE */

	#define MAX_LICENSE			500		// Max CID Record Count

/* NED Video Restriction definition */
#if (NED_VERSION >= 0x0290)	
	#define VIDEO_NOLIMIT		0		
	#define VIDEO_AVOUT			1		
	#define VIDEO_WATERMARK	2		
	#define VIDEO_SCRSHOT		4
#endif /* (NED_VERSION >= 0x0290) */


typedef struct lice_info{
	
	NED_U8	StaCode;	/* Status Code ( 0x00 : NULL, 0x01 : License, 0x02 : Request ) */
	NED_U8	PID[8];		/* PD ID */
	NED_U8	PKey[16];	/* PD Key */
	
	#ifdef NEXT_DISC
		NED_U8	NDPID[8];
		NED_U8	NDAlbumKey[16];
		NED_U8	NDUniqueKey[16];
	#endif /* NEXT_DISC */

	#if (NED_VERSION >= 0x0293)
		NED_U8	DevSerial[32];	/* 서비스 사이트에서 사용될 NEW Device Unique ID */
	#endif /* (NED_VERSION >= 0x0293) */
	
	NED_U16	nErrCode;	//Error Code : No error		(0)
   				//PID Error 						(1)
   				//CRC Error 						(2) 
   				//Random Number Error  			(3)
   				//Encryption Flag Error				(4)
   				//Caption Error					(5)
   				//StaCode Error					(6)
   				//Decrypt Len Error				(7)
   				//Start Date Error					(10)
   				//End Date Error					(11)
} LICE_INFO, *PLICE_INFO;

typedef struct cont_info
{
	NED_U8	DrmFlag;		//DRM File(1)
	NED_U8	Ver[2];			//NED Version (major,minor) - 12.17추가 by shell
	NED_U8	CEK[16];		//Content Encryption Key
	NED_U8	EncFlag;		//Encryption Method Flag
	NED_U8	CapFlag;		//Caption Flag
	NED_U8	SamFlag;		//Sample Flag
	NED_U8	PerFlag;		//Permission Flag - 11.23일 추가 by shell (0:unlimited, 1:Time, 2:Count, 3:Bell)
	NED_U32	lCaplen;		//Caption Length
	NED_U32	lPadlen;		//Padding Length
	NED_U32	lContlen;		//Content Length ( Original File Size + Padding Size )
	NED_U32 TotalCount;		//Total Count
	NED_U32 AvailCount;		//Available Count
	NED_U8	DateInfo[16];		//Start Date(8), End Date(8) 2004.08.26
	NED_U8	DecFlag;		//Mp3 Decryption Flag(1), 2004.09.09
	
	#ifdef META_SERVICE
		NED_U8	NemFlag;	//NED Metadata Flag
	#endif /* META_SERVICE */
	
	#if (NED_VERSION >= 0x0290)
		NED_U8	SID[5];			//Service Site ID(4), + (1) add Null
		NED_U8	CID[32];		//Content ID
		NED_U8	VideoFlag;		//Video Flag ( 1:AVOut, 2:WaterMark, 4: )
		NED_U8	WMStr[64];		//WaterMark String Unicode 64byte
	#endif /* (NED_VERSION >= 0x0290) */
	
	#ifdef NEXT_DISC
		NED_U8 NDFlag;
	#endif
	
	#ifdef NED_LMS
		NED_U8	LMSFlag;		// LMS(1), else(0)
		NED_U8	GID[4]; 		// Study Group ID
	#endif /* NED_LMS */	
	
} CONT_INFO, *PCONT_INFO;


typedef struct _FILEINFO
{
	NED_U32		FileID;
	CONT_INFO	NEDCont;
}FILEINFO, *PFILEINFO;
	

#ifdef COUNT_RULE
	
	typedef struct cnt_info
	{
		NED_U8	CID[32];		//Mega CID
		NED_U32	Count;			//재생가능 횟수
	} CNT_INFO, *PCNT_INFO;

#endif /* COUNT_RULE */

#ifdef MONTHLY_RULE

	typedef struct site_info
	{
		NED_U8	SID[4];			// Service Site ID
		NED_U8	SDate[8];		// Start date/time
		NED_U8	EDate[8];		// Expire date/time
		NED_U32	State;			// Status
	} SITE_INFO, *PSITE_INFO;
	
#endif /* MONTHLY_RULE */


#ifdef NEXT_DISC
	typedef struct nextdisc_info
	{
		NED_U8 	VerifierKey[24];
		NED_U8 	SessionKey[16];
		NED_U8 	SessionFlag;
	}NEXTDISC_INFO, *PNEXTDISC_INFO;
#endif 

/* Inka CyclonPark  20070710 - MegaStudy Start */

#ifdef NED_LMS
	typedef struct lms_log_info		// 32+8+2+2+4=48
	{
		NED_U8	ContentsID[32];		// Contents ID
		NED_U8	PlayDate[8];		// Play Date
		NED_U16	StartPos;		// Play Start Position
		NED_U16	EndPos; 		// Play End Position
		NED_U8	LogCRC[4];		// Record CRC
	} LMS_LOG_INFO, *PLMS_LOG_INFO;

	typedef struct lms_info
	{
		LMS_LOG_INFO	LLTable;		
		NED_U8		StartFlag;
		NED_32		LLRecCnt;
	}LMS_INFO, *PLMS_INFO;	
#endif  /* NED_LMS */


///////////////////////////////////////////////////////////////////////////////
////////////////////  _NED_CORE_API_  /////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

/* License API Definition */
#ifdef SERIAL_TYPE
	int NED_Init(PLICE_INFO pLicense, NED_U32 vid, NED_U32 pid, NED_PU8 pSerial, NED_INT nSerialLen);
	int NED_File(PLICE_INFO pLicense, NED_U32 vid, NED_U32 pid, NED_PU8 pVer, NED_U32 RandNum, NED_PU8 pDevTime, NED_PU8 pFile);
	int NED_LicSet(PLICE_INFO pLicense, NED_U32 nonce, NED_PU8 inData, NED_PU8 tmData);
#endif /* SERIAL_TYPE */

#ifdef HIDDEN_TYPE
	int NED_LicInit(PLICE_INFO pLicense, NED_PU32 pNonce, NED_PU8 inData);
	int NED_LicFile(PLICE_INFO pLicense, NED_U32 vid, NED_U32 pid, NED_PU8 pver, NED_U32 RandomNum, NED_PU8 pDevTime, NED_PU8 LicData, NED_PU8 outData);
	int NED_LicSet(PLICE_INFO pLicense, NED_U32 nonce, NED_PU8 inData, NED_PU8 outData, NED_PU8 tmData);
#endif /* HIDDEN_TYPE */


/* Count Control API Definition */
#ifdef COUNT_RULE
	int NED_LoadCount(PLICE_INFO pLicense, NED_PU8 pData, NED_INT size, NED_U32 RandNum, PCNT_INFO pCnt);
	int NED_GetCount(PCONT_INFO pContent, PCNT_INFO pCnt, NED_INT nRecord);
	int NED_UseCount(PCONT_INFO pContent, PCNT_INFO pCnt, NED_INT nRecord);
	int NED_SaveCount(PLICE_INFO pLicense, PCNT_INFO pCnt, NED_INT nRecord, NED_U32 RandNum, NED_PU8 pData);
#endif /* COUNT_RULE */


/* Monthly Control API Definition */
#ifdef MONTHLY_RULE
	int NED_LoadSTable(PLICE_INFO pLicense, NED_PU8 pData, NED_U32 size, NED_U32 RandNum, PSITE_INFO pSID);
	int NED_SaveSTable(PLICE_INFO pLicense, PSITE_INFO pSID, NED_INT nRecord, NED_U32 RandNum, NED_PU8 pData);
#endif /* MONTHLY_RULE */

/* Decryption API Definition */
int NED_CheckDrm(PLICE_INFO pLicense, PCONT_INFO pContent, NED_PU8 pData);
int NED_Decrypt(PLICE_INFO pLicense, PCONT_INFO pContent, NED_PU8 pData, NED_INT len);
unsigned long NED2_Random( NED_PU8 pSecureTime );


#ifdef NEXT_DISC
	void NDD_Encrypt( NED_PU8 pOutBuf, NED_PU8 pInBuf, NED_INT len, NED_PU8 pKey);
	void ND_CMDInit(NED_PU8 pIndata);
	void ND_CMDSetSession(NED_PU8 pIndata, NED_PU8 pVerKey);
	void ND_CMDInitRsp(NED_PU8 pIndata, NED_PU8 pSessionKey, NED_PU8 pVerKey);
	void ND_CMDCloseSession(NED_PU8 pIndata, NED_PU8 pSessionKey, NED_PU8 pVerKey);
	int ND_CMDSetSessionRsp(NED_PU8 pIndata, NED_PU8 pSessionKey, NED_PU8 pVerKey);
#endif /* NEXT_DISC */

#ifdef NED_LMS
	long NED_LoadLLTable_RecordCount(PLICE_INFO pLicense, NED_PU8 pHeaderBuf );
	void NED_SaveLLHeader( PLICE_INFO pLicense, NED_PU8 pHeaderBuf, NED_U32 lRecCnt );
	void NED_EncLLTable( PLICE_INFO pLicense, PLMS_LOG_INFO pLmsTable );
#endif /* NED_LMS */

int NED_LicCheck(PLICE_INFO pLicense, NED_U8* sLicData);

#endif /* _NED_H */

