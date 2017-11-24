//	Copyright(C) Gamepark Holdings. All rights reserved.
//	Dogma-G Game Studios In-House Library DGE
//
// Interface for the Virtual Keyboard class.
//
////////////////////////////////////////////////////////////////////////////////


#if defined(_WIN32) || defined(WIN32)
	#if _MSC_VER > 1000
	#pragma once
	#endif
#endif


#ifndef _DGT_VKB_H_
#define _DGT_VKB_H_

#include <DGE_Type.h>


enum EVIRTUAL_KEYBOARD
{
	// Animation Type
	DGT_VKB_NOANI	=0,
	DGT_VKB_SCROLLV	,
	DGT_VKB_SCROLLH	,
	DGT_VKB_FADE	,

	// State
	DGT_VKB_APPEAR=0,
	DGT_VKB_NONE	,
	DGT_VKB_DISAPPEAR,
};


interface IDGT_VirtualKeyboard
{
	DGE_CLASS_DESTROYER(	IDGT_VirtualKeyboard	);

	virtual INT		FrameMove() =0;									// ��ü Update
	virtual void	Render() =0;									// Rendering

	virtual void	ProcessVK(INT x, INT y, BOOL bClick)=0;			// ����Ű���尡 Ȱ��ȭ �Ǿ����� ���콺 ��ǥ�� Ŭ�� ������ �Է�. x, y, Ŭ�� ���� (Buttondown = true, buttonup = false)
	virtual void	ConvertString() =0;								// ���� Ű���� ���ο� �Էµ� ������ ������ �ѱ� �Ǵ� �������� ��ȭ�����ش�.

	
	// ���� ���۸� �����Ѵ�.
	// �ѹ� ���ǰ� ���ڿ� ����Ű���带 �ٽ� ȣ���Ҷ� ���� ���۰� ���� ������ �ִ�.
	// �̹����� �ذ��ϱ� ���ؼ��� ClearBuffer�� ��ȣ�� ������ ������ �ָ� �ȴ�.
	virtual void ClearBuffer() =0;


	// ���� ���ۿ� ����� ������ �ܺη� ������ ���� �Լ�
	// �ѱ� ���ڿ��� �������� �ܺ� ���۷� �����ϴ� �������� ������ ���ڿ��� �������� �ѱ�������
	// ���� �ѱ��ڰ� ���ŵɼ��� �ִ�.
	virtual void CopyString(char *OutBuf,INT iLength) =0;			// ��� ���ڿ�, ������ ���ڿ� ����. �־��� ���̸�ŭ ����.
	virtual const char* const GetDestString() const =0;				// VKB�� ���ڿ� �ּҸ� ������. (���� �ʿ�)



	virtual void	SetFinishCode(BOOL* value) = 0;					// Ű���带 ȣ���� BOOL ���� ����. BOOL is INT. is not bool
	virtual void	SetAnimation(INT AniType) =0;					// Ű���� ����� ������ �ִϸ��̼� ����. ANIMATION_TYPE�� �ϳ�
	virtual void	SetFPS	(BOOL fps) =0;							// Ű���� �ִϸ��̼��� �ӵ� ����. TRUE = 60fps / FALSE = 30fps.
	virtual void	SetDefaultString(char* pString) =0;				// �⺻ ���ڿ� ����
	virtual void	SetLimit(BYTE EngLength, BYTE KorLength) =0;	// Ű���忡�� ������ �ִ� �Ѱ� ���� ����
	virtual INT		GetAnimationState() =0;
};


typedef	IDGT_VirtualKeyboard*	PDGT_VKB;


// Create VKB
INT DGT_CreateVKB(char* sCmd
				   , PDGT_VKB* pData
				   , DGE_HANDLE p1			// Texture ID from OpenGL GenTexture();
				   , DGE_HANDLE p2 = NULL	// No Use
				   , DGE_HANDLE p3 = NULL	// No Use
				   , DGE_HANDLE p4 = NULL	// No Use
					 );

// Destroy VKB
INT DGT_DestroyVKB(PDGT_VKB* pData);


#endif


