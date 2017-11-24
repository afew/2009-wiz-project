/*
***************************************************************************************************
Project		: NED Ver 2.9
Description	: NED TYPE Define

History 	: 2007.07.23 ( Felix.Kim NED TYPE 분리 )


Copyright (C) 2003 ~ 2007 Inka Entwork Corp. <www.inka.co.kr>
All Rights Reserved.
***************************************************************************************************
*/



#ifndef _NED_TYPE_H
#define _NED_TYPE_H

/* Type Definition */
typedef void			NED_Viod;
typedef char 		NED_8;
typedef NED_8			NED_Bool;
typedef char* 		NED_P8;
typedef unsigned char 	NED_U8;
typedef unsigned char	BYTE;

typedef unsigned char*	NED_PU8;
typedef short		NED_16;
typedef short*		NED_P16;
typedef unsigned short	NED_U16;
typedef unsigned short	WORD;

typedef unsigned short*	NED_PU16;
typedef int		NED_INT;
typedef int*		NED_PINT;
typedef unsigned int	NED_UINT;
typedef unsigned int*	NED_PUINT;
typedef long		NED_32;
typedef long*		NED_P32;
typedef unsigned long	NED_U32;
typedef unsigned long*	NED_PU32;
//typedef long long		NED_64;
//typedef long long*		NED_P64;
//typedef unsigned long long		NED_U64;
//typedef unsigned long long*		NED_PU64;

typedef void* HANDLE;	//업체 핸들에 맞추어 전달

#ifndef NED_FALSE
#define NED_FALSE	0
#endif	//NED_FALSE

#ifndef NED_TRUE
#define NED_TRUE	1
#endif	//NED_TRUE



#endif /* _NED_TYPE_H */
