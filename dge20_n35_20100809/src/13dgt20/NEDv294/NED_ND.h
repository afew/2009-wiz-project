#ifndef _NED_NEXT_DISC_H_
#define _NED_NEXT_DISC_H_

#ifdef  __cplusplus
extern "C" {
#endif

#include "NED.h"
#include "NED_Variable.h"



    /* Cmd sending process - 080715 roy.song */
    typedef enum _ND_CMD_PROCESS
    {
	ND_CMD_INIT			= 101,
	ND_CMD_SETSESSION 	= 202,
	ND_CMD_GETKEY			= 301,
	ND_CMD_CLOSESESSION 	= 401
    }ND_CMD_PROCESS;


    /* ND CMD Result - 080715 roy.song */
    typedef enum _ND_CMD_PROCESS_RESULT
    {
	ND_SUCCESS							= 0,
	ND_FAIL								= -1,

	ND_CMD_INIT_READ_FAIL				= -1001,
	ND_CMD_INIT_WRITE_FAIL				= -1002,

	ND_CMD_SET_SESSION_READ_FAIL		= -2001,
	ND_CMD_SET_SESSION_WRITE_FAIL		= -2002,
	ND_SET_SESSION_RSP_ERROR				= -2003,

	ND_HEADER_IDENTIFIER_ERROR			= -3001,
	ND_HEADER_VERSION_ERROR				= -3002,

	ND_GETKEY_READ_FAIL					= -4001,

	ND_CMD_CLOSE_SESSION_READ_FAIL		= -5001,
	ND_CMD_CLOSE_SESSION_WRITE_FAIL	= -5002

    }ND_CMD_PROCESS_RESULT;




    /* NEXT_DISC_SD_IO_API */
    extern int ND_SD_Sector_Read( unsigned long address, unsigned char* pBuff );
    extern int ND_SD_Sector_Write( unsigned long address, unsigned char* pBuff );
    extern void ND_DEBUG( const char* _msg, ... );



    /* NED_NEXT_DISC_API */
    //void Delay( NED_U16 _interval );
    int ND_CMD( NED_PU8 pIndata,  ND_CMD_PROCESS _cmdSendProcess);
    int ND_Mount(void);
    int ND_GetKey(void);
    int ND_Close(void);
    void ND_UNMount(void);


    /* ND 카드를 Mount 하면, SD 카드의 mount call 이 후 호출 한다. ND 카드의 protected area내의 key정보를 얻는다.
       1. ND initialize process
       - Create session for connect to ND protected area and check ND autentificate
       2. ND right acquisition process
       - Get specific key
       3. ND session close process
       - Close the session that connected ND protected area, and create session for connect to general data area. 
     */
    int ND_Initialize(void);

    /* ND 카드를 Numount 하면, SD 카드의 unmount call 이 후 호출 한다. ND 카드 및 device내의 ND 키 정보를 초기화 한다.

       ND_terminate()
       - ND terminate process include to initialize key information.
     */
    void ND_Terminate(void);

#ifdef  __cplusplus
}
#endif


#endif /* _NED_NEXT_DISC_H_ */

