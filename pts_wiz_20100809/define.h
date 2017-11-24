//
//
////////////////////////////////////////////////////////////////////////////////

#ifndef __DEFINE_H__
#define __DEFINE_H__


typedef int				BOOL;
typedef int				INT;
typedef unsigned int	UINT;
typedef unsigned char	BYTE;
typedef signed short	SHORT;
typedef unsigned short	USHORT;

typedef long			LONG;
typedef unsigned long	ULONG;



enum{
	X,Y,Z,XYZ,XYZS,XY = Z,S = XYZ,SX = Z,SY = S
};

enum{
	PAD_DOWN = 0x01,
	PAD_LEFT = 0x02,
	PAD_RIGHT = 0x04,
	PAD_UP = 0x08,
	PAD_BUTTON1 = 0x10,
	PAD_BUTTON2 = 0x20,
	PAD_BUTTON3 = 0x40,
	PAD_BUTTON4 = 0x80,
	PAD_BUTTON5 = 0x100,
	PAD_BUTTON6 = 0x200,
	PAD_BUTTON7 = 0x400,
	PAD_BUTTON8 = 0x800,
	PAD_BUTTON9 = 0x1000,
	PAD_BUTTONA = 0x2000,
	PAD_BUTTONB = 0x4000,

	PAD_DIR = PAD_UP | PAD_DOWN | PAD_LEFT | PAD_RIGHT,
	PAD_BUTTON = PAD_BUTTON1 | PAD_BUTTON2 | PAD_BUTTON3 | PAD_BUTTON4 | PAD_BUTTON5 | PAD_BUTTON6 | PAD_BUTTON7 | PAD_BUTTON8 | PAD_BUTTON9 | PAD_BUTTONA | PAD_BUTTONB,
	PAD_ALL = PAD_DIR | PAD_BUTTON,

	JOYSTICK_AXIS = 16384,

	REP_MIN = 2,
	REP_MAX = 30
};

#ifndef NULL
#define NULL 0
#endif

#define FALSE 0
#define TRUE 1




#define WP 65536
#define WWP (WP*2)


//ê›íËÉt?ÉCÉãÇÃì‡óe
#define CONFIGFILE_NAME "debug.txt"

#define DISPLY_WIDTH (320)
#define DISPLY_HEIGHT (240)
#define DISPLY_WIDTH_WP (DISPLY_WIDTH*WP)
#define DISPLY_HEIGHT_WP (DISPLY_HEIGHT*WP)

#define BMPBUFF_MAX (128)



#define VOL_MAX (120)

enum
{
	EN_SN_EXIT = 0,
	EN_SN_TITLE,
	EN_SN_ACT,
	EN_SN_OPTION,
	EN_SN_ENDING,
	EN_SN_LOGO,
	EN_SN_STAGE,	// Stage Select
	EN_SN_DEMO,
};

enum {
	EN_BGM_GAME01 = 0,
	EN_BGM_GAME02,
	EN_BGM_GAME03,
	EN_BGM_GAME04,
	EN_BGM_GAME05,
	EN_BGM_GAME06,
	EN_BGM_GAME07,

	EN_BGM_END   ,
};
enum {
	EN_SE_ATK1 = 0,
	EN_SE_DAMEGE ,
	EN_SE_L1     ,
	EN_SE_LANDING,
	EN_SE_MSG    ,

	EN_SE_SELECT ,
	EN_SE_SW     ,
	EN_SE_JUMP   ,
	EN_SE_PAWA   ,
	EN_SE_CL1   ,

	EN_SE_CL2   ,
	EN_SE_CL3   ,
	EN_SE_CL4   ,
	EN_SE_CL5   ,

	EN_SE_CL21   ,
	EN_SE_CL22   ,
	EN_SE_CL23   ,
	EN_SE_CL24   ,
	EN_SE_CL25   ,

	EN_SE_END   ,
};



#endif



