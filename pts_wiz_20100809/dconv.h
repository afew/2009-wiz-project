

/*==========================================================================
 *
 *  Copyright (C) 1998 Jumpei Isshiki. All Rights Reserved.
 *
 *  File	:dconv.h
 *  Content	:�f??�ϊ���?
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
/*	�萔�̒�?															*/
/*----------------------------------------------------------------------*/


/*----------------------------------------------------------------------*/
/*	?���̂̐錾														*/
/*----------------------------------------------------------------------*/


/*----------------------------------------------------------------------*/
/*	�O���Q�ƕϐ��̐錾													*/
/*----------------------------------------------------------------------*/


/*----------------------------------------------------------------------*/
/*	�O���Q�Ɗ֐��̐錾													*/
/*----------------------------------------------------------------------*/
extern	USHORT	DCNVrand( USHORT );					/* �w��͈̗͂������擾����			*/
extern	void	DCNVinitRand( USHORT );				/* �����̔����n�񏉊���				*/
extern	void	DCNVshuffleDim( int,USHORT * );		/* �e?�u���V���b�t��				*/
extern	void	DCNVshuffleMain( int,USHORT * );	/* �e?�u���V���b�t��?��			*/
extern	INT	MOTsin( int );					/* sin(a)���v�Z����					*/
extern	INT	MOTcos( int );					/* cos(a)���v�Z����					*/
extern	SHORT	MOTatan( INT,INT );			/* (posX,posY)�ւ̊p�x���v�Z����	*/


/*----------------------------------------------------------------------*/
#endif					/* end of Dconv.h	*/
/*----------------------------------------------------------------------*/



