#ifndef _NED_VARIABLE_H_
#define _NED_VARIABLE_H_

#ifdef  __cplusplus
extern "C" {
#endif

//#include "../NED_CORE/NED.h"
#include "NED.h"

//#define LIBRARY_BUILD		// INKA Lib 제작시 사용

/* Heap Memory for NetsyncDRM */
/* Variable for DRM Information , Mandatory declaration */
#ifdef LIBRARY_BUILD
	extern LICE_INFO	gNEDLicense;
	extern FILEINFO		gNED_File[];
	extern NED_U8 		gNEDBuf[];
	extern NED_INT		gNED_FileIdx;
#else
	LICE_INFO	gNEDLicense;
	FILEINFO	gNED_File[MAX_MULTI];
	NED_U8 		gNEDBuf[NED_BLOCK];
	NED_INT		gNED_FileIdx;
#endif /* LIBRARY_BUILD */

/* Device F/W Version Definition , Mandatory declaration */
#ifdef LIBRARY_BUILD
	extern NED_U8	gFWver[];
#else
	NED_U8	gFWver[]= {0x01, 0x01, 0xFF, 0xFF };
#endif /* LIBRARY_BUILD */



/* Variable for Monthly Rule , Declare if apply monthly rule */
#ifdef MONTHLY_RULE

#ifdef LIBRARY_BUILD
	extern NED_U8		gSidBuf[];
	extern SITE_INFO 	gSTable[];
	extern NED_INT		gSTableCnt;
#else
	NED_U8		gSidBuf[24 * MAX_SID + 16];
	SITE_INFO 	gSTable[MAX_SID];
	NED_INT		gSTableCnt;
#endif /* LIBRARY_BUILD */
 
#endif /* MONTHLY_RULE */



/* Variable for Count Rule , Declare if apply count rule */
#ifdef COUNT_RULE

#ifdef LIBRARY_BUILD
	extern NED_U8		gCntBuf[];
	extern CNT_INFO 	gLicense[];
	extern NED_INT		gLicCnt;
#else
	NED_U8		gCntBuf[36 * MAX_LICENSE +16];
	CNT_INFO 	gLicense[MAX_LICENSE];
	NED_INT		gLicCnt;
#endif /* LIBRARY_BUILD */

#endif /* COUNT_RULE */



/* Variable for Next Disc , Declare if apply next disc */
#ifdef NEXT_DISC

#ifdef LIBRARY_BUILD
	extern NEXTDISC_INFO	gND_Info;
#else
	NEXTDISC_INFO	gND_Info;
#endif /* LIBRARY_BUILD */

#endif /* NEXT_DISC */



/* Variable for LMS */
#ifdef NED_LMS

#ifdef LIBRARY_BUILD
	extern LMS_INFO	gLMS_log;
#else
	LMS_INFO	gLMS_log;
#endif /* LIBRARY_BUILD */

#endif /* NED_LMS */



#ifdef  __cplusplus
}
#endif


#endif /* _NED_VARIABLE_H_ */
