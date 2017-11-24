/********************************************************************************

			Copyright(C) Gamepark Holdings. All rights reserved.
							Dogma-G Game Studios
							In-House Library DGE


						C++ compiler support with SDL
							(gcc-4.0.2-glibc-2.3.6)
								# included SDL #

********************************************************************************/

#if defined(_WIN32) || defined(WIN32)
	#if _MSC_VER >= 1200
	#pragma warning(disable: 4996)
	#endif

#endif


#ifndef _VirtualKeyboard_H__
#define _VirtualKeyboard_H__


#include <vector>


class VirtualKeyboard : public IDGT_VirtualKeyboard
{
protected:
	INT				m_AniType;
	INT				m_AnimationState;
	INT				m_AnimationSeed;
	float			m_fAniSpeed;

	Automata		m_cAutomata;

	INT				m_BackPosition;
	BYTE			m_LimitEng;
	BYTE			m_LimitKor;
	BOOL*			m_pFinish;

	// False = OFF, True = ON
	BOOL		m_bOK;
	BOOL		m_bQUIT;
	BOOL		m_bCapsLock;
	BOOL		m_bShift;
	BOOL		m_bChange;
	BOOL		m_bBackspace;
	BOOL		m_bNoneuse;

	BOOL		m_bDefault;

	// False = English, True = Korean
	BOOL		m_bLanguage;
	BYTE		m_InputBuffer[256];
	BYTE		m_DefaultBuffer[256];
	BYTE		m_ConvertBuffer[512];
	char*		m_sDstStr;

	// 0 = English, 1 = Korean
	BYTE		m_LangCode[256];

	KeyNode		m_KeyBoard[46];
	FuntionKey	m_FunKey[7];

	UINT		m_nTex;


	std::vector<short>	m_VertexArray;
	std::vector<float>	m_STArray;

public:
	VirtualKeyboard();
	virtual ~VirtualKeyboard();

	virtual INT		Create(DGE_HANDLE =NULL, DGE_HANDLE =NULL, DGE_HANDLE =NULL, DGE_HANDLE =NULL);
	virtual void	Destroy();			// 

	virtual INT		FrameMove();		// 전체 Update
	virtual void	Render();			// Rendering

	virtual void ProcessVK	(
					INT iX,				// X좌표
					INT iY,				// Y좌표
					BOOL bClick			// 클릭 상태 (Buttondown = true, buttonup = false)
					);
// =======================================================================================
/** \brief DGE_Font::ProcessVK()

	\remarks

	가상키보드가 활성화 되었을때 마우스 좌표와 클릭 정보를 입력한다.

	\warning

	없음

	@return

	없음 */
// =======================================================================================

	virtual void ConvertString();
// =======================================================================================
/** \brief DGE_Font::ConvertString()

	\remarks

	가상 키보드 내부에 입력된 버퍼의 내용을 한글 또는 영문으로 변화시켜준다.

	\warning

	없음

	@return

	없음 */
// =======================================================================================


	virtual void ClearBuffer();
// =======================================================================================
/** \brief DGE_Font::ClearBuffer()

	\remarks

	내부 버퍼를 정리한다.
	한번 사용되고 난뒤에 가상키보드를 다시 호출할때 이전 버퍼가 남아 있을수 있다
	이문제를 해결하기 위해서는 ClearBuffer를 재호출 이전에 실행해 주면 된다.

	\warning

	없음

	@return

	없음 */
// =======================================================================================

	virtual void CopyString	(
					char *OutBuffer,			// 문자열을 받기 위한 포인터
					INT iLength					// 복사할 문자열의 길이
					);
// =======================================================================================
/** \brief DGE_Font::CopyString()

	\remarks

	내부 버퍼에 저장된 내용을 외부로 꺼내기 위한 함수

	\warning

	한글 문자열이 생성된후 외부 버퍼로 복사하는 과정에서 마지막 문자열이 영문인지 한글인지에
	따라서 한글자가 제거될수도 있다.

	@return

	없음 */
// =======================================================================================

	virtual const char* const GetDestString() const {	return m_sDstStr;			}



	virtual void SetFinishCode	(
						BOOL *value				// 외부와 연동되는 변수의 포인터
						);
// =======================================================================================
/** \brief DGE_Font::CopyString()

	\remarks

	키보드를 호출할 BOOL 값을 설정해주기 위한 함수

	\warning

	없음

	@return

	없음 */
// =======================================================================================

	// Animation방식 설정
	virtual void SetAnimation(INT AniType)	// 애니메이션 종류를 설정한다. ANIMATION_TYPE중 하나
	{ m_AniType = AniType; }
// =======================================================================================
/** \brief DGE_Font::SetAnimation()

	\remarks

	키보드 등장과 퇴장의 애니메이션을 설정해준다.

	\warning

	없음

	@return

	없음 */
// =======================================================================================

	virtual void SetFPS	(
				BOOL fps		// FPS를 설정한다 true = 60fps / false = 30fps.
				);
// =======================================================================================
/** \brief DGE_Font::SetFPS()

	\remarks

	키보드 애니메이션의 속도를 설정한다. true = 60fps / false = 30fps.

	\warning

	없음

	@return

	없음 */
// =======================================================================================

	virtual void SetDefaultString	(
							char* pString		// 기본 문자열 설정
							);
// =======================================================================================
/** \brief DGE_Font::SetDefaultString()

	\remarks

	키보드 기본 문자열 설정

	\warning

	없음

	@return

	없음 */
// =======================================================================================

	virtual void SetLimit(BYTE EngLength, BYTE KorLength);
// =======================================================================================
/** \brief DGE_Font::SetLimit()

	\remarks

	키보드에서 받을수 있는 한계 숫자 설정

	\warning

	없음

	@return

	없음 */
// =======================================================================================

	virtual INT		GetAnimationState()	{	return m_AnimationState;	}


protected:
	void Deleteback();
	void Pushback(char Code, BOOL value);

	INT GetKorWordLength(INT front);
	INT GetEngWordLength(INT front);

	void KeyCodeSetup();
	void KeyRectSetup();
	void KeyPickSetup();
	void KeyStateSetup();
	void GenVertex();

	void DrawColorBox(INT x, INT y, INT w, INT h, unsigned char A, unsigned char R, unsigned char G, unsigned char B);
};



#endif //_VirtualKeyboard_H__
