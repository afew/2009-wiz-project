

/*==========================================================================
 *
 *  Copyright (C) 1998 Jumpei Isshiki. All Rights Reserved.
 *
 *  File	:dconv.h
 *  Content	:デ??変換定?
 *	Program	:T.Sato / J.Issiki
 *	Date	:1998/5/13
 *	UpDate	:2002/11/14
 *
 ==========================================================================*/

#ifndef	_DCONV_INCLUDED_
#define	_DCONV_INCLUDED_

typedef int				BOOL;
typedef int				INT;
typedef unsigned int	UINT;
typedef unsigned char	BYTE;
typedef signed short	SHORT;
typedef unsigned short	USHORT;

typedef long			LONG;
typedef unsigned long	ULONG;

/*----------------------------------------------------------------------*/
/*	定数の定?															*/
/*----------------------------------------------------------------------*/


/*----------------------------------------------------------------------*/
/*	?造体の宣言														*/
/*----------------------------------------------------------------------*/


/*----------------------------------------------------------------------*/
/*	外部参照変数の宣言													*/
/*----------------------------------------------------------------------*/


/*----------------------------------------------------------------------*/
/*	外部参照関数の宣言													*/
/*----------------------------------------------------------------------*/
extern	USHORT	DCNVrand( USHORT );					/* 指定範囲の乱数を取得する			*/
extern	void	DCNVinitRand( USHORT );				/* 乱数の発生系列初期化				*/
extern	void	DCNVshuffleDim( int,USHORT * );		/* テ?ブルシャッフル				*/
extern	void	DCNVshuffleMain( int,USHORT * );	/* テ?ブルシャッフル?体			*/
extern	INT	MOTsin( int );					/* sin(a)を計算する					*/
extern	INT	MOTcos( int );					/* cos(a)を計算する					*/
extern	SHORT	MOTatan( INT,INT );			/* (posX,posY)への角度を計算する	*/


/*----------------------------------------------------------------------*/
#endif					/* end of Dconv.h	*/
/*----------------------------------------------------------------------*/



