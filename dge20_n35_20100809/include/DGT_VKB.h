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

	virtual INT		FrameMove() =0;									// 전체 Update
	virtual void	Render() =0;									// Rendering

	virtual void	ProcessVK(INT x, INT y, BOOL bClick)=0;			// 가상키보드가 활성화 되었을때 마우스 좌표와 클릭 정보를 입력. x, y, 클릭 상태 (Buttondown = true, buttonup = false)
	virtual void	ConvertString() =0;								// 가상 키보드 내부에 입력된 버퍼의 내용을 한글 또는 영문으로 변화시켜준다.

	
	// 내부 버퍼를 정리한다.
	// 한번 사용되고 난뒤에 가상키보드를 다시 호출할때 이전 버퍼가 남아 있을수 있다.
	// 이문제를 해결하기 위해서는 ClearBuffer를 재호출 이전에 실행해 주면 된다.
	virtual void ClearBuffer() =0;


	// 내부 버퍼에 저장된 내용을 외부로 꺼내기 위한 함수
	// 한글 문자열이 생성된후 외부 버퍼로 복사하는 과정에서 마지막 문자열이 영문인지 한글인지에
	// 따라서 한글자가 제거될수도 있다.
	virtual void CopyString(char *OutBuf,INT iLength) =0;			// 출력 문자열, 복사할 문자열 길이. 주어진 길이만큼 복사.
	virtual const char* const GetDestString() const =0;				// VKB의 문자열 주소를 가져옴. (복사 필요)



	virtual void	SetFinishCode(BOOL* value) = 0;					// 키보드를 호출할 BOOL 값을 설정. BOOL is INT. is not bool
	virtual void	SetAnimation(INT AniType) =0;					// 키보드 등장과 퇴장의 애니메이션 설정. ANIMATION_TYPE중 하나
	virtual void	SetFPS	(BOOL fps) =0;							// 키보드 애니메이션의 속도 설정. TRUE = 60fps / FALSE = 30fps.
	virtual void	SetDefaultString(char* pString) =0;				// 기본 문자열 설정
	virtual void	SetLimit(BYTE EngLength, BYTE KorLength) =0;	// 키보드에서 받을수 있는 한계 숫자 설정
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


