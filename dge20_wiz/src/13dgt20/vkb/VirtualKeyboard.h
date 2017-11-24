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

	virtual INT		FrameMove();		// ��ü Update
	virtual void	Render();			// Rendering

	virtual void ProcessVK	(
					INT iX,				// X��ǥ
					INT iY,				// Y��ǥ
					BOOL bClick			// Ŭ�� ���� (Buttondown = true, buttonup = false)
					);
// =======================================================================================
/** \brief DGE_Font::ProcessVK()

	\remarks

	����Ű���尡 Ȱ��ȭ �Ǿ����� ���콺 ��ǥ�� Ŭ�� ������ �Է��Ѵ�.

	\warning

	����

	@return

	���� */
// =======================================================================================

	virtual void ConvertString();
// =======================================================================================
/** \brief DGE_Font::ConvertString()

	\remarks

	���� Ű���� ���ο� �Էµ� ������ ������ �ѱ� �Ǵ� �������� ��ȭ�����ش�.

	\warning

	����

	@return

	���� */
// =======================================================================================


	virtual void ClearBuffer();
// =======================================================================================
/** \brief DGE_Font::ClearBuffer()

	\remarks

	���� ���۸� �����Ѵ�.
	�ѹ� ���ǰ� ���ڿ� ����Ű���带 �ٽ� ȣ���Ҷ� ���� ���۰� ���� ������ �ִ�
	�̹����� �ذ��ϱ� ���ؼ��� ClearBuffer�� ��ȣ�� ������ ������ �ָ� �ȴ�.

	\warning

	����

	@return

	���� */
// =======================================================================================

	virtual void CopyString	(
					char *OutBuffer,			// ���ڿ��� �ޱ� ���� ������
					INT iLength					// ������ ���ڿ��� ����
					);
// =======================================================================================
/** \brief DGE_Font::CopyString()

	\remarks

	���� ���ۿ� ����� ������ �ܺη� ������ ���� �Լ�

	\warning

	�ѱ� ���ڿ��� �������� �ܺ� ���۷� �����ϴ� �������� ������ ���ڿ��� �������� �ѱ�������
	���� �ѱ��ڰ� ���ŵɼ��� �ִ�.

	@return

	���� */
// =======================================================================================

	virtual const char* const GetDestString() const {	return m_sDstStr;			}



	virtual void SetFinishCode	(
						BOOL *value				// �ܺο� �����Ǵ� ������ ������
						);
// =======================================================================================
/** \brief DGE_Font::CopyString()

	\remarks

	Ű���带 ȣ���� BOOL ���� �������ֱ� ���� �Լ�

	\warning

	����

	@return

	���� */
// =======================================================================================

	// Animation��� ����
	virtual void SetAnimation(INT AniType)	// �ִϸ��̼� ������ �����Ѵ�. ANIMATION_TYPE�� �ϳ�
	{ m_AniType = AniType; }
// =======================================================================================
/** \brief DGE_Font::SetAnimation()

	\remarks

	Ű���� ����� ������ �ִϸ��̼��� �������ش�.

	\warning

	����

	@return

	���� */
// =======================================================================================

	virtual void SetFPS	(
				BOOL fps		// FPS�� �����Ѵ� true = 60fps / false = 30fps.
				);
// =======================================================================================
/** \brief DGE_Font::SetFPS()

	\remarks

	Ű���� �ִϸ��̼��� �ӵ��� �����Ѵ�. true = 60fps / false = 30fps.

	\warning

	����

	@return

	���� */
// =======================================================================================

	virtual void SetDefaultString	(
							char* pString		// �⺻ ���ڿ� ����
							);
// =======================================================================================
/** \brief DGE_Font::SetDefaultString()

	\remarks

	Ű���� �⺻ ���ڿ� ����

	\warning

	����

	@return

	���� */
// =======================================================================================

	virtual void SetLimit(BYTE EngLength, BYTE KorLength);
// =======================================================================================
/** \brief DGE_Font::SetLimit()

	\remarks

	Ű���忡�� ������ �ִ� �Ѱ� ���� ����

	\warning

	����

	@return

	���� */
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
