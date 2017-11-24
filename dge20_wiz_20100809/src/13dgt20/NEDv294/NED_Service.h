#ifndef _NED_SERVICE_H_
#define _NED_SERVICE_H_

#ifdef  __cplusplus
extern "C" {
#endif

//#include "../NED_CORE/NED.h"
//#include "../NED_FS/NED_FS.h"
//#include "../NED_VARIABLE/NED_Variable.h"
#include "NED.h"
#include "NED_FS.h"
#include "NED_Variable.h"

#define CID_MAX_LOOP				100  	/* USB연결시 "NED_CID_xxxx.SYS" 파일을 탐색하는 파일 갯수 ( 많으면 문제가 될 듯 ) */

/* NED_SERVICE_API RETURN Definition */
#define NED_HIDDEN_UPDATE			1		/* (License issue)  hidden에 License 저장 필요상태  */
#define NED_TIME_UPDATE			2		/* (secureTime issue) hidden에 secureTime 저장 필요 */
#define NED_PERIOD_RULE			1		/* 정상 처리된 월정액/기간제 Contents */
#define NED_CID_RULE				2		/* 정상 처리된 횟수 contents */
#define NED_CID_DISCNT_OK			1		/* 정상 횟수 차감 */


/* NED_SERVICE_API ERRO Definition */
#define NED_SERIAL_ERROR			-1		/* Serial Number 의 범위 초과 혹은 길이 미달일 경우 */
#define NED_LIC_WERROR				-2		/* "NED_LIC.SYS" File write Error  */
#define NED_SID_WERROR				-3		/* "NED_SID.SYS" File write Error  */
#define NED_HIDDEN_CRC_ERROR		-4		/* Hidden에 저장된 License Data의 CRC Error인 경우 */
#define NED_EXPIRATION_ERROR		-5		/* 월정액/기간제 기간 만료 */
#define NED_CID_CNT_ERROR			-6		/* Count Rule의 횟수 만료 */


/* NED_File_IO_API */
/***************************************************************************************************
Function
	NED_FILE_READ()
	
Description
	NED System 폴더에 저장되어 있는 NED License 및 Right 파일을 size만큼 읽어 해당 Buffer에 입력한다. 
	Return Value는 실제 읽은 데이터 수이다.

Prototype
	extern int NED_FILE_READ ( char* fileName, unsigned char* pBuff, int size );

Parameter
	[in] fileName 		처리 대상이 되는 Right Files. NED로부터 넘겨 받아 처리한다.
	[in] pBuff		Right Files 처리 후 내용을 입력하기 위한 Buffer.
	[in] size		처리 단위 Size	  	  
			  
Return 
Return 
	>=0 			실제 읽어들인 Size
              
Note   : NED System file을 읽기 위한 함수로 NAND, HDD 영역에 파일 Access가 가능하도록 작성하여 export 하시기 바랍니다.
	     구현에 대한 예제는 가이드 문서 5.3.2의 Appendix. NED_FILE_READ Sample Code를 참고한다.
***************************************************************************************************/
int NED_FILE_READ ( char* fileName, unsigned char* pBuff, int size );



/***************************************************************************************************
Function
	NED_FILE_WRITE()
	
Description
	버퍼의 내용을 NED System 폴더에 저장되어 있는 NED License 및 Right 파일에 size만큼 입력한다. 
	Return Value는 실제 기록한 데이터 수이다.

Prototype
	extern int NED_FILE_WRITE ( char* fileName, unsigned char* pBuff, int size );

Parameter
	[in] fileName 		처리 대상이 되는 Right Files. NED로부터 넘겨 받아 처리한다.
	[in] pBuff			Right Files 처리 후 내용을 입력하기 위한 Buffer.
	[in] size			처리 단위 Size	  
			  
Return 
	>=0 			실제 쓰여진 Size
              
Note   : NED System file을 생성하기 위한 함수로 NAND, HDD 영역에 파일 Access가 가능하도록 작성하여 export 하시기 바랍니다.
	     구현에 대한 예제는 가이드 문서 5.3.2의 Appendix. NED_FILE_WRITE Sample Code를 참고한다.
***************************************************************************************************/
int NED_FILE_WRITE ( char* fileName, unsigned char* pBuff, int size );






/* NED_SERVICES_ API */
#ifdef SERIAL_TYPE
/***************************************************************************************************
Function
	NED_Initialize()
	
Description
	기기 부팅시 호출하여 " NED_LIC.SYS "파일을 읽어 secure time update 여부 판단과 NED 변수 및 License key를 초기화 한다.

Prototype
	int NED_Initialize( 
						NED_U32 randNum, 
						NED_PU8 pSecureTime, 
						NED_U32 vid, 
						NED_U32 pid, 
						NED_PU8 pSerial, 
						NED_INT nSerialLen 
	);

Parameter
	[in] randNum			System area에 저장된 NED Random 값, NED Contents 의 무결성 Check에 사용되는 값.
	[in / out] pSecureTime	NED Secure Time으로 변환된 unsigned char형 8byte 배열.
						Ex) 2008/06/30/10/15( year / month / day / minute / second )
						pSecuretime[] = { 0x20, 0x08, 0x06, 0x30, 0x10, 0x15, 0x00}
	[in] vid				Vendor ID
	[in] pid				Product ID
	[in] pSerial			Serial string		  
	[in] nSerialLen 	  	Serial Number Length
	
Return 
	0 					성공, " NED_LIC.SYS " 업데이트 내용이 없다
	2					성공, " NED_LIC.SYS " 파일이 업데이트 됨. secureTime 값 변경, System area의 secure
						Time 을 Update한다.
	<0					실패  
              
Note   : 월정제, 기간제 서비스를 지원하는 경우 Secure Time을 정확한 타입으로 전달해야 하며, 사용하지 않는 필드는 0으로 
	     초기화 한다. vid, pid, pSerial, nSerialLen은 Unique한 Key를 생성하기 위해 필요한 정보이므로 포멧을 지켜 정확하게 
	     넘겨주어야 한다.
***************************************************************************************************/
	int NED_Initialize( NED_U32 randNum, NED_PU8 pSecureTime, NED_U32 vid, NED_U32 pid, NED_PU8 pSerial, NED_INT nSerialLen );



/***************************************************************************************************
Function
	NED_USBConnect()
	
Description
	기기와 PC( DRM Server )간 USB 연결 시 호출하여 " NED_LIC.SYS " 및 " NED_SID.SYS "등과 같은 파일을 생성하고
	update한다.

Prototype
	int NED_USBConnect( NED_PU32 pRandNum, NED_U32 vid, NED_U32 pid, NED_PU8 pSecureTime );

Parameter
	[in] pRandNum 		System area에 저장된 NED Random 값, NED Contents 의 무결성 Check에 사용되는 값.
	[in] vid				Vendor ID
	[in] pid				Product ID
	[in] pSecureTime		NED Secure Time으로 변환된 unsigned char형 8byte 배열.
						Ex) 2008/06/30/10/15( year / month / day / minute / second )
						pSecuretime[] = { 0x20, 0x08, 0x06, 0x30, 0x10, 0x15, 0x00}
			  
Return 
	>=0 				성공
	<0					실패  
              
Note   : NED_USBConnect() 호출 후 인자로 전달한 Random Number 값은 변환 되므로 반드시 시스템 영역에 저장 및 Update
	     해 주어야 한다.
***************************************************************************************************/
	int NED_USBConnect( NED_PU32 pRandNum, NED_U32 vid, NED_U32 pid, NED_PU8 pSecureTime );




/***************************************************************************************************
Function
	NED_USBDisconnect()
	
Description
	USB 연결 해제시 호출한다.

Prototype
	int NED_USBDisconnect( NED_U32 randNum, NED_U32 vid, NED_U32 pid, NED_PU8 pSecureTime );

Parameter
	[in] randNum 			System area에 저장된 NED Random 값, NED Contents 의 무결성 Check에 사용되는 값.
	[in] vid				Vendor ID
	[in] pid				Product ID
	[in / out] pSecureTime	NED Secure Time으로 변환된 unsigned char형 8byte 배열.
						Ex) 2008/06/30/10/15( year / month / day / minute / second )
						pSecuretime[] = { 0x20, 0x08, 0x06, 0x30, 0x10, 0x15, 0x00} 
			  
Return 
	>=0 				성공
	2					" NED_LIC.SYS " 파일이 Update되었다. NED_USBDisconnect()의4번째 인자인 pSecureTime
						값이 변경되었다. System Area에 저장된 Secure Time을 Update한다.
	-1					실패  
              
Note   : Return Value가 2이면 Netsync Browser에서 Device Secure Time을 Check하여 현재 시간과 24시간 이상 차이가 발생
	     하였다고 판단하여 현재 시간을 발급한 상태이다. 
***************************************************************************************************/
	int NED_USBDisconnect( NED_U32 randNum, NED_U32 vid, NED_U32 pid, NED_PU8 pSecureTime );

#endif /* SERIAL_TYPE */








#ifdef HIDDEN_TYPE

/***************************************************************************************************
Function
	NED_Initialize()
	
Description
	기기 부팅시 호출하여 " NED_LIC.SYS "파일을 읽어 secure time update 여부 판단과 NED 변수 및 License key를 초기화 한다.

Prototype
	int NED_Initialize( NED_U32 randNum, NED_PU8 pSecureTime, NED_PU8 pHiddenData, NED_U32 vid, NED_U32 pid );

Parameter
	[in] randNum			System area에 저장된 NED Random 값, NED Contents 의 무결성 Check에 사용되는 값.
	[in / out] pSecureTime	NED Secure Time으로 변환된 unsigned char형 8byte 배열.
						Ex) 2008/06/30/10/15( year / month / day / minute / second )
						pSecuretime[] = { 0x20, 0x08, 0x06, 0x30, 0x10, 0x15, 0x00}
	[in /out] pHiddenData	System area내의 64byte License	
	[in] vid				Vendor ID
	[in] pid				Product ID
	  
Return 
	0 					성공, " NED_LIC.SYS " 업데이트 내용이 없다
	1					성공, " NED_LIC.SYS " 파일이 업데이트 됨. pHiddenData가 갱신됨. System area의 64byte인증서를
						update한다. 
	2					성공, " NED_LIC.SYS " 파일이 업데이트 됨. secureTime 값 변경, System area의 secure
						Time 을 Update한다.
	3					1, 2 모두 해당
	<0					실패  
              
Note   : 월정제, 기간제 서비스를 지원하는 경우 Secure Time을 정확한 타입으로 전달해야 하며, 사용하지 않는 필드는 0으로 
	     초기화 한다. 기기 고유의 Serial Key를 가지고 있지 않는 기기들은 NED 서버에 의해Key역할을 대치하는 License를 
	     발급 받는다. 서비스 유지를 위해 NED License 파일에 대한 처리를 적절하게 수행한다.
***************************************************************************************************/
	int NED_Initialize( NED_U32 randNum, NED_PU8 pSecureTime, NED_PU8 pHiddenData, NED_U32 vid, NED_U32 pid );



/***************************************************************************************************
Function
	NED_USBConnect()
	
Description
	기기와 PC( DRM Server )간 USB 연결 시 호출하여 " NED_LIC.SYS " 및 " NED_SID.SYS "등과 같은 파일을 생성하고
	update한다.

Prototype
	int NED_USBConnect( NED_PU32 pRandNum, NED_U32 vid, NED_U32 pid, NED_PU8 pSecureTime, NED_PU8 pHiddenData );

Parameter
	[in] pRandNum 		System area에 저장된 NED Random 값, NED Contents 의 무결성 Check에 사용되는 값.
	[in] vid				Vendor ID
	[in] pid				Product ID
	[in] pSecureTime		NED Secure Time으로 변환된 unsigned char형 8byte 배열.
						Ex) 2008/06/30/10/15( year / month / day / minute / second )
						pSecuretime[] = { 0x20, 0x08, 0x06, 0x30, 0x10, 0x15, 0x00}
	[in] pHiddenData		System Area에 저장되어 있는 64byte 인증서
			  
Return 
	>=0 				성공
	1					" NED_LIC.SYS " 파일이 Update되었다. NED_USBConnect()의 5번째 Argument  pHiddenData가 
						변경되었다. System Area에 저장되어 있는 64byte 인증서를 Update 한다. 
	<0					실패  
              
Note   : NED_USBConnect() 호출 후 인자로 전달한 Random Number 값은 변환 되므로 반드시 시스템 영역에 저장 및 Update
	     해 주어야 한다.
***************************************************************************************************/
	int NED_USBConnect( NED_PU32 pRandNum, NED_U32 vid, NED_U32 pid, NED_PU8 pSecureTime, NED_PU8 pHiddenData );



/***************************************************************************************************
Function
	NED_USBDisconnect()
	
Description
	USB 연결 해제시 호출한다.

Prototype
	int NED_USBDisconnect( NED_U32 randNum, NED_U32 vid, NED_U32 pid, NED_PU8 pSecureTime, NED_PU8 pHiddenData );

Parameter
	[in] randNum 			System area에 저장된 NED Random 값, NED Contents 의 무결성 Check에 사용되는 값.
	[in] vid				Vendor ID
	[in] pid				Product ID
	[in / out] pSecureTime	NED Secure Time으로 변환된 unsigned char형 8byte 배열.
						Ex) 2008/06/30/10/15( year / month / day / minute / second )
						pSecuretime[] = { 0x20, 0x08, 0x06, 0x30, 0x10, 0x15, 0x00} 
	[in /out]	pHiddenData	System Area에 저장되어 있는 64byte 인증서			
			  
Return 
	>=0 				성공
	1					" NED_LIC.SYS " 파일이 업데이트 됨. pHiddenData가 갱신됨. System area의 64byte인증서를
						update한다. 
	2					성공, " NED_LIC.SYS " 파일이 업데이트 됨. secureTime 값 변경, System area의 secure
						Time 을 Update한다.
	3					1, 2 모두 해당
	<0					실패  
              
Note   : Return Value가 1또는 2일 경우 Netsync Brower에서 License를 발급해 준 상태이므로 System Area의 License에 해당
	     하는 Data를 Update한다.  
***************************************************************************************************/
	int NED_USBDisconnect( NED_U32 randNum, NED_U32 vid, NED_U32 pid, NED_PU8 pSecureTime, NED_PU8 pHiddenData );

#endif /* HIDDEN_TYPE */




#ifdef COUNT_RULE

/***************************************************************************************************
Function
	NED_Playback()
	
Description
	Contents 재생 시 호출하여 Return value에 따라 재생 판단을 하고 적절한 Error 메시지를 Display한다.

Prototype
	int NED_Playback( NED_U32 randNum, NED_PU8 pSecureTime, NED_P16 pNAvail, NED_PU8 pVFlag, NED_PU8 pWMStr );

Parameter
	[in] randNum 			System area에 저장된 NED Random 값, NED Contents 의 무결성 Check에 사용되는 값.
	[in] pSecureTime		NED Secure Time으로 변환된 unsigned char형 8byte 배열.
	[out] pNAvail			횟수제한이 있는 컨텐츠일 경우 이용할 수 있는 횟수가 Return된다.
	[out] pVFlag			AVOUT, ScreenShot, Watermark Flag 정보가 Return된다.
						VFlag - Video_NOLIMIT : 0, VIDEO_AVOUT : 1, VIDEO_WATERMARK : 2, VIDEO_SCRSHOT : 4
	[out] pWMStr			Watermark Flag가 1일 경우 64byte의 char배열에 UNICODE를 Return한다.		  
			  
Return 
	0 					Rule이 없는 DRM Contents 또는 일반 컨텐츠
	2					횟수제 Rule이 적용된 정상적인 DRM 컨텐츠  
	-6					횟수제 Rule이 적용된 Contents의 횟수가 만료되었다.
              
Note   : 비디오 제어를 적용하는 경우 가이드 문서를 참고하여 비디오 인자들에 대한 처리를 한다.
***************************************************************************************************/
	int NED_Playback( NED_U32 randNum, NED_PU8 pSecureTime, NED_P16 pNAvail, NED_PU8 pVFlag, NED_PU8 pWMStr );


/***************************************************************************************************
Function
	NED_Discount()
	
Description
	Device 초기화시 호출하여 준다. Device의 VID, PID, Serial Number를 인자로 넘겨주어 SeedKey 값으로 사용하고,
	pLicense의 각 멤버 변수들을 초기화 한다.

Prototype
	int NED_Discount( NED_U32 randNum, NED_PINT pNAvail );

Parameter
	[in] randNum 		System area에 저장된 NED Random 값, NED Contents 의 무결성 Check에 사용되는 값.
	[out] pNAvail		횟수제한이 있는 컨텐츠일 경우 이용할 수 있는 횟수가 Return된다.	  
			  
Return 
	0 				차감이 필요 없는 Contents.
	1				1회 정상 차감 됨.
              
Note   : 횟수 제어를 적용할 경우 Discount 시나리오에 주의한다. 자세한 내용은 가이드 문서를 참고한다. 
***************************************************************************************************/
	int NED_Discount( NED_U32 randNum, NED_PINT pNAvail );

#else

/***************************************************************************************************
Function
	NED_Playback()
	
Description
	Device 초기화시 호출하여 준다. Device의 VID, PID, Serial Number를 인자로 넘겨주어 SeedKey 값으로 사용하고,
	pLicense의 각 멤버 변수들을 초기화 한다.

Prototype
	int NED_Playback( NED_U32 randNum, NED_PU8 pSecureTime,  NED_PU8 pVFlag, NED_PU8 pWMStr );

Parameter
	[in] randNum 			System area에 저장된 NED Random 값, NED Contents 의 무결성 Check에 사용되는 값.
	[in] pSecureTime		NED Secure Time으로 변환된 unsigned char형 8byte 배열.
	[out] pVFlag			AVOUT, ScreenShot, Watermark Flag 정보가 Return된다.
						VFlag - Video_NOLIMIT : 0, VIDEO_AVOUT : 1, VIDEO_WATERMARK : 2, VIDEO_SCRSHOT : 4
	[out] pWMStr			Watermark Flag가 1일 경우 64byte의 char배열에 UNICODE를 Return한다.	
			  
Return 
	0 					Rule이 없는 DRM Contents 또는 일반 컨텐츠
	1					월정제, 기간제 Rule이 적용된 정상적인 DRM 컨텐츠  
	-5					재생할 수 없는Contents이거나 월정제, 기간제 서비스 기간이 만료된 Contents.
***************************************************************************************************/
	int NED_Playback( NED_U32 randNum, NED_PU8 pSecureTime,  NED_PU8 pVFlag, NED_PU8 pWMStr);

#endif	// COUNT_RULE


/***************************************************************************************************
Function
	NED_InitLicense()
Description
	NED_LIC.SYS 파일로 부터 기기 키를 획득하여 키를 세팅한다.
Prototype
	int NED_InitLicense( NED_U8 *sLicData );
Parameter
	[in]		sLicData		License Data. 
						NED_LIC.SYS 파일로 부터 읽어 들인 버퍼(512byte)를 인자로 전달한다.
Return 
	0					NED_InitLicense Success.
       0<					NED_InitLicense Fail.
Note
	NED_fopen() 전에 DRM을 초기화 시 이 함수를 호출 한다. 이 함수는 NED_Initialize()의 역할을 하며, 기기키를 생성할 수 
	없는 게임 파일의 경우 이 함수를 이용하여 NED_LIC.SYS 파일로 부터 키를 획득한다.
***************************************************************************************************/
int NED_InitLicense(NED_U8 *sLicData);

#ifdef  __cplusplus
}
#endif


#endif /* _NED_SERVICE_H_ */
