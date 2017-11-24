

#if defined(_WIN32) || defined(WIN32)
	#if _MSC_VER >= 1200
	#pragma warning(disable: 4996)
	#endif
#endif

#include <vector>

#include <malloc.h>


#include <gles/gl.h>

#include <DGE_Type.h>
#include <DGE_Math.h>
#include <DGE_Base.h>


#include "Automata.h"

#include "../DGT_VKB.h"
#include "VirtualKeyboard.h"



VirtualKeyboard::VirtualKeyboard()
{
	m_AniType = DGT_VKB_FADE;
	m_AnimationState = DGT_VKB_APPEAR;
	m_bNoneuse = FALSE;
	m_pFinish = NULL;
	m_bChange = TRUE;
	m_bBackspace = FALSE;
	m_bCapsLock = FALSE;
	m_bShift = FALSE;
	m_bLanguage = FALSE;
	m_bOK = FALSE;
	m_bQUIT = FALSE;
	m_bDefault = FALSE;
	m_bOK = FALSE;
	m_LimitEng = 18;
	m_LimitKor = 20;
	m_AnimationSeed = 0;
	m_fAniSpeed = 1.0f;
	memset(m_DefaultBuffer, 0, sizeof(BYTE) * 256);
	memset(m_InputBuffer, 0, sizeof(BYTE) * 256);
	memset(m_ConvertBuffer, 0, sizeof(BYTE) * 512);
	memset(m_LangCode, 0, sizeof(BYTE) * 256);
	m_BackPosition = 0;
	m_nTex = 0;

	m_sDstStr = NULL;


	KeyCodeSetup();
	KeyRectSetup();
	KeyPickSetup();
	KeyStateSetup();
}


VirtualKeyboard::~VirtualKeyboard()
{
	Destroy();
}


INT VirtualKeyboard::Create(DGE_HANDLE p1, DGE_HANDLE p2, DGE_HANDLE p3, DGE_HANDLE p4)
{
	if(NULL == p1)
		return DGE_EFAIL;

	m_nTex = *((UINT*)p1);

	if(0>= m_nTex)
		return DGE_EFAIL;

	KeyCodeSetup();
	KeyRectSetup();
	KeyPickSetup();
	KeyStateSetup();

	ConvertString();

	return DGE_OK;
}


void VirtualKeyboard::ProcessVK(INT x, INT y, BOOL click)
{
	INT	i;

	*(m_FunKey[3].m_pPushed) = FALSE;

	for(i = 0; i < 46; i++)
	{
		m_KeyBoard[i].m_iPushed = 0;
	}

	// 코드가 있는 자판의 처리 우선
	for(i = 0; i < 46; i++)
	{
		if(m_KeyBoard[i].CheckInner(x, y))
		{
			if(click)
			{
				m_bChange = TRUE;
				m_bDefault = FALSE;
				m_KeyBoard[i].m_iPushed = 1;
				if(m_bLanguage)
				{
					if(m_KeyBoard[i].m_bKorShiftCode)
					{
						Pushback(m_KeyBoard[i].m_Code[0], m_KeyBoard[i].m_bSpecial[m_bShift]);
					}
					else
					{
						Pushback(m_KeyBoard[i].m_Code[m_bShift], m_KeyBoard[i].m_bSpecial[m_bShift]);
					}
				} else
				{
					if(m_bCapsLock && m_KeyBoard[i].m_bSpecial[0] == FALSE)
					{
						Pushback(m_KeyBoard[i].m_Code[1], m_KeyBoard[i].m_bSpecial[m_bShift]);
					} else
					{
						Pushback(m_KeyBoard[i].m_Code[m_bShift], m_KeyBoard[i].m_bSpecial[m_bShift]);
					}
				}
			} else
			{
				m_bChange = TRUE;
				m_KeyBoard[i].m_iPushed = 0;
			}
			if(m_FunKey[1].GetPushed() == TRUE)
			{
				m_FunKey[1].ChangePushed();
			}
			break;
		}
	}
	// 각종 기능키의 처리를 하자!
	if(m_FunKey[0].CheckInner(x, y) && click)
	{
		m_FunKey[0].ChangePushed();
		if(m_FunKey[1].GetPushed() == TRUE)
		{
			m_FunKey[1].ChangePushed();
		}
		m_bChange = TRUE;
	}
	if(m_FunKey[1].CheckInner(x, y) && click)
	{
		m_FunKey[1].ChangePushed();
		if(m_FunKey[0].GetPushed() == TRUE)
		{
			m_FunKey[0].ChangePushed();
		}
		m_bChange = TRUE;
	}
	if(m_FunKey[2].CheckInner(x, y) && click)
	{
		m_FunKey[2].ChangePushed();
		m_bChange = TRUE;
	}
	if(m_FunKey[3].CheckInner(x, y) && click)
	{
		m_FunKey[3].ChangePushed();
		m_bChange = TRUE;
	}
	if(*(m_FunKey[3].m_pPushed))
	{
		Deleteback();
	}
	if(m_FunKey[5].CheckInner(x, y) && click)
	{
		m_AnimationState = DGT_VKB_DISAPPEAR;
		m_bShift = FALSE;
		m_bCapsLock = FALSE;
		m_bLanguage = FALSE;
		m_bOK = TRUE;
		m_FunKey[5].ChangePushed();
		m_bChange = TRUE;
	}
	if(m_FunKey[6].CheckInner(x, y) && click)
	{
		m_AnimationState = DGT_VKB_DISAPPEAR;
		m_bShift = FALSE;
		m_bCapsLock = FALSE;
		m_bLanguage = FALSE;
		ClearBuffer();
		m_FunKey[6].ChangePushed();
		m_bChange = TRUE;
	}
}

void VirtualKeyboard::Deleteback()
{
	if(m_BackPosition > 0)
	{
		m_InputBuffer[m_BackPosition-1] = 0;
		m_LangCode[m_BackPosition-1] = FALSE;
		m_BackPosition--;
	}
}

void VirtualKeyboard::ClearBuffer()
{
	memset(m_InputBuffer, 0, sizeof(BYTE) * 256);
	memset(m_LangCode, 0, sizeof(BYTE) * 256);
	memset(m_ConvertBuffer, 0, sizeof(BYTE) * 512);
	m_BackPosition = 0;
	m_bOK = FALSE;
	m_bQUIT = FALSE;
	m_bCapsLock = FALSE;
	m_bShift = FALSE;
	m_bBackspace = FALSE;
	m_bNoneuse = FALSE;
	m_bChange = TRUE;
	m_bDefault = TRUE;
	m_bOK = FALSE;
	ConvertString();
}

void VirtualKeyboard::Pushback(char Code, BOOL value)
{
	if(((UINT)m_BackPosition != strlen((char*)m_ConvertBuffer) && strlen((char*)m_ConvertBuffer) <= m_LimitKor) || strlen((char*)m_ConvertBuffer) < m_LimitEng)
	{
		m_InputBuffer[m_BackPosition] = Code;
		if(value)
		{
			m_LangCode[m_BackPosition] = 0;
		} else
		{
			m_LangCode[m_BackPosition] = m_bLanguage;
		}
		m_BackPosition++;
	}
}

void VirtualKeyboard::KeyCodeSetup()
{
	m_KeyBoard[ 0].SetCodeNoShift('1');	m_KeyBoard[ 0].SetCodeShift	('!');	m_KeyBoard[ 0].SetSpecial(TRUE);	m_KeyBoard[ 0].SetSpecialShift(TRUE);
	m_KeyBoard[ 1].SetCodeNoShift('2');	m_KeyBoard[ 1].SetCodeShift	('@');	m_KeyBoard[ 1].SetSpecial(TRUE);	m_KeyBoard[ 1].SetSpecialShift(TRUE);
	m_KeyBoard[ 2].SetCodeNoShift('3');	m_KeyBoard[ 2].SetCodeShift	('#');	m_KeyBoard[ 2].SetSpecial(TRUE);	m_KeyBoard[ 2].SetSpecialShift(TRUE);
	m_KeyBoard[ 3].SetCodeNoShift('4');	m_KeyBoard[ 3].SetCodeShift	('$');	m_KeyBoard[ 3].SetSpecial(TRUE);	m_KeyBoard[ 3].SetSpecialShift(TRUE);
	m_KeyBoard[ 4].SetCodeNoShift('5');	m_KeyBoard[ 4].SetCodeShift	('%');	m_KeyBoard[ 4].SetSpecial(TRUE);	m_KeyBoard[ 4].SetSpecialShift(TRUE);
	m_KeyBoard[ 5].SetCodeNoShift('6');	m_KeyBoard[ 5].SetCodeShift	('^');	m_KeyBoard[ 5].SetSpecial(TRUE);	m_KeyBoard[ 5].SetSpecialShift(TRUE);
	m_KeyBoard[ 6].SetCodeNoShift('7');	m_KeyBoard[ 6].SetCodeShift	('&');	m_KeyBoard[ 6].SetSpecial(TRUE);	m_KeyBoard[ 6].SetSpecialShift(TRUE);
	m_KeyBoard[ 7].SetCodeNoShift('8');	m_KeyBoard[ 7].SetCodeShift	('*');	m_KeyBoard[ 7].SetSpecial(TRUE);	m_KeyBoard[ 7].SetSpecialShift(TRUE);
	m_KeyBoard[ 8].SetCodeNoShift('9');	m_KeyBoard[ 8].SetCodeShift	('(');	m_KeyBoard[ 8].SetSpecial(TRUE);	m_KeyBoard[ 8].SetSpecialShift(TRUE);
	m_KeyBoard[ 9].SetCodeNoShift('0');	m_KeyBoard[ 9].SetCodeShift	(')');	m_KeyBoard[ 9].SetSpecial(TRUE);	m_KeyBoard[ 9].SetSpecialShift(TRUE);
	m_KeyBoard[10].SetCodeNoShift('-');	m_KeyBoard[10].SetCodeShift ('_');	m_KeyBoard[10].SetSpecial(TRUE);	m_KeyBoard[10].SetSpecialShift(TRUE);
	m_KeyBoard[11].SetCodeNoShift('=');	m_KeyBoard[11].SetCodeShift	('+');	m_KeyBoard[11].SetSpecial(TRUE);	m_KeyBoard[11].SetSpecialShift(TRUE);

	m_KeyBoard[12].SetCodeNoShift('q');	m_KeyBoard[12].SetCodeShift	('Q');
	m_KeyBoard[13].SetCodeNoShift('w');	m_KeyBoard[13].SetCodeShift	('W');
	m_KeyBoard[14].SetCodeNoShift('e');	m_KeyBoard[14].SetCodeShift	('E');
	m_KeyBoard[15].SetCodeNoShift('r');	m_KeyBoard[15].SetCodeShift	('R');
	m_KeyBoard[16].SetCodeNoShift('t');	m_KeyBoard[16].SetCodeShift	('T');

	m_KeyBoard[17].SetCodeNoShift('y');	m_KeyBoard[17].SetCodeShift	('Y');	m_KeyBoard[17].SetKorShiftCode(TRUE);
	m_KeyBoard[18].SetCodeNoShift('u');	m_KeyBoard[18].SetCodeShift	('U');	m_KeyBoard[18].SetKorShiftCode(TRUE);
	m_KeyBoard[19].SetCodeNoShift('i');	m_KeyBoard[19].SetCodeShift	('I');	m_KeyBoard[19].SetKorShiftCode(TRUE);

	m_KeyBoard[20].SetCodeNoShift('o');	m_KeyBoard[20].SetCodeShift	('O');
	m_KeyBoard[21].SetCodeNoShift('p');	m_KeyBoard[21].SetCodeShift	('P');

	m_KeyBoard[22].SetCodeNoShift('[');	m_KeyBoard[22].SetCodeShift	('<');	m_KeyBoard[22].SetSpecial(TRUE);	m_KeyBoard[22].SetSpecialShift(TRUE);
	m_KeyBoard[23].SetCodeNoShift(']');	m_KeyBoard[23].SetCodeShift	('>');	m_KeyBoard[23].SetSpecial(TRUE);	m_KeyBoard[23].SetSpecialShift(TRUE);

	m_KeyBoard[24].SetCodeNoShift('a');	m_KeyBoard[24].SetCodeShift	('A');	m_KeyBoard[24].SetKorShiftCode(TRUE);
	m_KeyBoard[25].SetCodeNoShift('s');	m_KeyBoard[25].SetCodeShift	('S');	m_KeyBoard[25].SetKorShiftCode(TRUE);
	m_KeyBoard[26].SetCodeNoShift('d');	m_KeyBoard[26].SetCodeShift	('D');	m_KeyBoard[26].SetKorShiftCode(TRUE);
	m_KeyBoard[27].SetCodeNoShift('f');	m_KeyBoard[27].SetCodeShift	('F');	m_KeyBoard[27].SetKorShiftCode(TRUE);
	m_KeyBoard[28].SetCodeNoShift('g');	m_KeyBoard[28].SetCodeShift	('G');	m_KeyBoard[28].SetKorShiftCode(TRUE);
	m_KeyBoard[29].SetCodeNoShift('h');	m_KeyBoard[29].SetCodeShift	('H');	m_KeyBoard[29].SetKorShiftCode(TRUE);
	m_KeyBoard[30].SetCodeNoShift('j');	m_KeyBoard[30].SetCodeShift	('J');	m_KeyBoard[30].SetKorShiftCode(TRUE);
	m_KeyBoard[31].SetCodeNoShift('k');	m_KeyBoard[31].SetCodeShift	('K');	m_KeyBoard[31].SetKorShiftCode(TRUE);
	m_KeyBoard[32].SetCodeNoShift('l');	m_KeyBoard[32].SetCodeShift	('L');	m_KeyBoard[32].SetKorShiftCode(TRUE);
	m_KeyBoard[33].SetCodeNoShift(';');	m_KeyBoard[33].SetCodeShift	(':');	m_KeyBoard[33].SetSpecial(TRUE);	m_KeyBoard[33].SetSpecialShift(TRUE);

	m_KeyBoard[34].SetCodeNoShift('\'');m_KeyBoard[34].SetCodeShift	('\"');	m_KeyBoard[34].SetSpecial(TRUE);	m_KeyBoard[34].SetSpecialShift(TRUE);
	m_KeyBoard[35].SetCodeNoShift('z');	m_KeyBoard[35].SetCodeShift	('Z');	m_KeyBoard[35].SetKorShiftCode(TRUE);
	m_KeyBoard[36].SetCodeNoShift('x');	m_KeyBoard[36].SetCodeShift	('X');	m_KeyBoard[36].SetKorShiftCode(TRUE);
	m_KeyBoard[37].SetCodeNoShift('c');	m_KeyBoard[37].SetCodeShift	('C');	m_KeyBoard[37].SetKorShiftCode(TRUE);
	m_KeyBoard[38].SetCodeNoShift('v');	m_KeyBoard[38].SetCodeShift	('V');	m_KeyBoard[38].SetKorShiftCode(TRUE);
	m_KeyBoard[39].SetCodeNoShift('b');	m_KeyBoard[39].SetCodeShift	('B');	m_KeyBoard[39].SetKorShiftCode(TRUE);
	m_KeyBoard[40].SetCodeNoShift('n');	m_KeyBoard[40].SetCodeShift	('N');	m_KeyBoard[40].SetKorShiftCode(TRUE);
	m_KeyBoard[41].SetCodeNoShift('m');	m_KeyBoard[41].SetCodeShift	('M');	m_KeyBoard[41].SetKorShiftCode(TRUE);
	m_KeyBoard[42].SetCodeNoShift(',');	m_KeyBoard[42].SetCodeShift	('~');	m_KeyBoard[42].SetSpecial(TRUE);	m_KeyBoard[42].SetSpecialShift(TRUE);
	m_KeyBoard[43].SetCodeNoShift('.');	m_KeyBoard[43].SetCodeShift	('\\');	m_KeyBoard[43].SetSpecial(TRUE);	m_KeyBoard[43].SetSpecialShift(TRUE);
	m_KeyBoard[44].SetCodeNoShift('/');	m_KeyBoard[44].SetCodeShift	('?');	m_KeyBoard[44].SetSpecial(TRUE);	m_KeyBoard[44].SetSpecialShift(TRUE);
	m_KeyBoard[45].SetCodeNoShift(' ');	m_KeyBoard[45].SetCodeShift	(' ');	m_KeyBoard[45].SetSpecial(TRUE);	m_KeyBoard[45].SetSpecialShift(TRUE);
}

void VirtualKeyboard::KeyRectSetup()
{
	// 한글 no push / no shift
	// 첫줄											// 두번째줄
	m_KeyBoard[0].SetRectNPKor(0,0,21,21);			m_KeyBoard[12].SetRectNPKor(0,21,21,21);
	m_KeyBoard[1].SetRectNPKor(21,0,21,21);			m_KeyBoard[13].SetRectNPKor(21,21,21,21);
	m_KeyBoard[2].SetRectNPKor(42,0,21,21);			m_KeyBoard[14].SetRectNPKor(42,21,21,21);
	m_KeyBoard[3].SetRectNPKor(63,0,21,21);			m_KeyBoard[15].SetRectNPKor(63,21,21,21);
	m_KeyBoard[4].SetRectNPKor(84,0,21,21);			m_KeyBoard[16].SetRectNPKor(84,21,21,21);
	m_KeyBoard[5].SetRectNPKor(105,0,21,21);		m_KeyBoard[17].SetRectNPKor(105,21,21,21);
	m_KeyBoard[6].SetRectNPKor(126,0,21,21);		m_KeyBoard[18].SetRectNPKor(126,21,21,21);
	m_KeyBoard[7].SetRectNPKor(147,0,21,21);		m_KeyBoard[19].SetRectNPKor(147,21,21,21);
	m_KeyBoard[8].SetRectNPKor(168,0,21,21);		m_KeyBoard[20].SetRectNPKor(168,21,21,21);
	m_KeyBoard[9].SetRectNPKor(189,0,21,21);		m_KeyBoard[21].SetRectNPKor(189,21,21,21);
	m_KeyBoard[10].SetRectNPKor(210,0,21,21);		m_KeyBoard[22].SetRectNPKor(210,21,21,21);
	m_KeyBoard[11].SetRectNPKor(231,0,21,21);		m_KeyBoard[23].SetRectNPKor(231,21,21,21);
	// 세번째줄										// 네번째줄
	m_KeyBoard[24].SetRectNPKor(0,42,21,21);		m_KeyBoard[35].SetRectNPKor(0,63,21,21);
	m_KeyBoard[25].SetRectNPKor(21,42,21,21);		m_KeyBoard[36].SetRectNPKor(21,63,21,21);
	m_KeyBoard[26].SetRectNPKor(42,42,21,21);		m_KeyBoard[37].SetRectNPKor(42,63,21,21);
	m_KeyBoard[27].SetRectNPKor(63,42,21,21);		m_KeyBoard[38].SetRectNPKor(63,63,21,21);
	m_KeyBoard[28].SetRectNPKor(84,42,21,21);		m_KeyBoard[39].SetRectNPKor(84,63,21,21);
	m_KeyBoard[29].SetRectNPKor(105,42,21,21);		m_KeyBoard[40].SetRectNPKor(105,63,21,21);
	m_KeyBoard[30].SetRectNPKor(126,42,21,21);		m_KeyBoard[41].SetRectNPKor(126,63,21,21);
	m_KeyBoard[31].SetRectNPKor(147,42,21,21);		m_KeyBoard[42].SetRectNPKor(147,63,21,21);
	m_KeyBoard[32].SetRectNPKor(168,42,21,21);		m_KeyBoard[43].SetRectNPKor(168,63,21,21);
	m_KeyBoard[33].SetRectNPKor(189,42,21,21);		m_KeyBoard[44].SetRectNPKor(189,63,21,21);
	m_KeyBoard[34].SetRectNPKor(210,42,21,21);		m_KeyBoard[45].SetRectNPKor(53,84,133,21);

	// 한글 no push / shift
	// 첫줄											// 두번째줄
	m_KeyBoard[0].SetRectNPKorShift(252,0,21,21);	m_KeyBoard[12].SetRectNPKorShift(252,21,21,21);
	m_KeyBoard[1].SetRectNPKorShift(273,0,21,21);	m_KeyBoard[13].SetRectNPKorShift(273,21,21,21);
	m_KeyBoard[2].SetRectNPKorShift(294,0,21,21);	m_KeyBoard[14].SetRectNPKorShift(294,21,21,21);
	m_KeyBoard[3].SetRectNPKorShift(315,0,21,21);	m_KeyBoard[15].SetRectNPKorShift(315,21,21,21);
	m_KeyBoard[4].SetRectNPKorShift(336,0,21,21);	m_KeyBoard[16].SetRectNPKorShift(336,21,21,21);
	m_KeyBoard[5].SetRectNPKorShift(357,0,21,21);	m_KeyBoard[17].SetRectNPKorShift(105,21,21,21);
	m_KeyBoard[6].SetRectNPKorShift(378,0,21,21);	m_KeyBoard[18].SetRectNPKorShift(126,21,21,21);
	m_KeyBoard[7].SetRectNPKorShift(399,0,21,21);	m_KeyBoard[19].SetRectNPKorShift(147,21,21,21);
	m_KeyBoard[8].SetRectNPKorShift(420,0,21,21);	m_KeyBoard[20].SetRectNPKorShift(357,21,21,21);
	m_KeyBoard[9].SetRectNPKorShift(441,0,21,21);	m_KeyBoard[21].SetRectNPKorShift(378,21,21,21);
	m_KeyBoard[10].SetRectNPKorShift(462,0,21,21);	m_KeyBoard[22].SetRectNPKorShift(399,21,21,21);
	m_KeyBoard[11].SetRectNPKorShift(483,0,21,21);	m_KeyBoard[23].SetRectNPKorShift(420,21,21,21);
	// 세번째줄										// 네번째줄
	m_KeyBoard[24].SetRectNPKorShift(0,42,21,21);	m_KeyBoard[35].SetRectNPKorShift(0,63,21,21);
	m_KeyBoard[25].SetRectNPKorShift(21,42,21,21);	m_KeyBoard[36].SetRectNPKorShift(21,63,21,21);
	m_KeyBoard[26].SetRectNPKorShift(42,42,21,21);	m_KeyBoard[37].SetRectNPKorShift(42,63,21,21);
	m_KeyBoard[27].SetRectNPKorShift(63,42,21,21);	m_KeyBoard[38].SetRectNPKorShift(63,63,21,21);
	m_KeyBoard[28].SetRectNPKorShift(84,42,21,21);	m_KeyBoard[39].SetRectNPKorShift(84,63,21,21);
	m_KeyBoard[29].SetRectNPKorShift(105,42,21,21);	m_KeyBoard[40].SetRectNPKorShift(105,63,21,21);
	m_KeyBoard[30].SetRectNPKorShift(126,42,21,21);	m_KeyBoard[41].SetRectNPKorShift(126,63,21,21);
	m_KeyBoard[31].SetRectNPKorShift(147,42,21,21);	m_KeyBoard[42].SetRectNPKorShift(210,63,21,21);
	m_KeyBoard[32].SetRectNPKorShift(168,42,21,21);	m_KeyBoard[43].SetRectNPKorShift(231,63,21,21);
	m_KeyBoard[33].SetRectNPKorShift(231,42,21,21);	m_KeyBoard[44].SetRectNPKorShift(252,63,21,21);
	m_KeyBoard[34].SetRectNPKorShift(252,42,21,21);	m_KeyBoard[45].SetRectNPKorShift(53,84,133,21);

	// 한글 push / no shift
	// 첫줄											// 두번째줄
	m_KeyBoard[0].SetRectPKor(0,105,20,20);			m_KeyBoard[12].SetRectPKor(0,125,20,20);
	m_KeyBoard[1].SetRectPKor(20,105,20,20);		m_KeyBoard[13].SetRectPKor(20,125,20,20);
	m_KeyBoard[2].SetRectPKor(40,105,20,20);		m_KeyBoard[14].SetRectPKor(40,125,20,20);
	m_KeyBoard[3].SetRectPKor(60,105,20,20);		m_KeyBoard[15].SetRectPKor(60,125,20,20);
	m_KeyBoard[4].SetRectPKor(80,105,20,20);		m_KeyBoard[16].SetRectPKor(80,125,20,20);
	m_KeyBoard[5].SetRectPKor(100,105,20,20);		m_KeyBoard[17].SetRectPKor(100,125,20,20);
	m_KeyBoard[6].SetRectPKor(120,105,20,20);		m_KeyBoard[18].SetRectPKor(120,125,20,20);
	m_KeyBoard[7].SetRectPKor(140,105,20,20);		m_KeyBoard[19].SetRectPKor(140,125,20,20);
	m_KeyBoard[8].SetRectPKor(160,105,20,20);		m_KeyBoard[20].SetRectPKor(160,125,20,20);
	m_KeyBoard[9].SetRectPKor(180,105,20,20);		m_KeyBoard[21].SetRectPKor(180,125,20,20);
	m_KeyBoard[10].SetRectPKor(200,105,20,20);		m_KeyBoard[22].SetRectPKor(200,125,20,20);
	m_KeyBoard[11].SetRectPKor(220,105,20,20);		m_KeyBoard[23].SetRectPKor(220,125,20,20);
	// 세번째줄										// 네번째줄
	m_KeyBoard[24].SetRectPKor(0,145,20,20);		m_KeyBoard[35].SetRectPKor(0,165,20,20);
	m_KeyBoard[25].SetRectPKor(20,145,20,20);		m_KeyBoard[36].SetRectPKor(20,165,20,20);
	m_KeyBoard[26].SetRectPKor(40,145,20,20);		m_KeyBoard[37].SetRectPKor(40,165,20,20);
	m_KeyBoard[27].SetRectPKor(60,145,20,20);		m_KeyBoard[38].SetRectPKor(60,165,20,20);
	m_KeyBoard[28].SetRectPKor(80,145,20,20);		m_KeyBoard[39].SetRectPKor(80,165,20,20);
	m_KeyBoard[29].SetRectPKor(100,145,20,20);		m_KeyBoard[40].SetRectPKor(100,165,20,20);
	m_KeyBoard[30].SetRectPKor(120,145,20,20);		m_KeyBoard[41].SetRectPKor(120,165,20,20);
	m_KeyBoard[31].SetRectPKor(140,145,20,20);		m_KeyBoard[42].SetRectPKor(140,165,20,20);
	m_KeyBoard[32].SetRectPKor(160,145,20,20);		m_KeyBoard[43].SetRectPKor(160,165,20,20);
	m_KeyBoard[33].SetRectPKor(180,145,20,20);		m_KeyBoard[44].SetRectPKor(180,165,20,20);
	m_KeyBoard[34].SetRectPKor(200,145,20,20);		m_KeyBoard[45].SetRectPKor(52,185,132,20);


	// 한글 push / shift
	// 첫줄											// 두번째줄
	m_KeyBoard[0].SetRectPKorShift(240,105,20,20);	m_KeyBoard[12].SetRectPKorShift(240,125,20,20);
	m_KeyBoard[1].SetRectPKorShift(260,105,20,20);	m_KeyBoard[13].SetRectPKorShift(260,125,20,20);
	m_KeyBoard[2].SetRectPKorShift(280,105,20,20);	m_KeyBoard[14].SetRectPKorShift(280,125,20,20);
	m_KeyBoard[3].SetRectPKorShift(300,105,20,20);	m_KeyBoard[15].SetRectPKorShift(300,125,20,20);
	m_KeyBoard[4].SetRectPKorShift(320,105,20,20);	m_KeyBoard[16].SetRectPKorShift(320,125,20,20);
	m_KeyBoard[5].SetRectPKorShift(340,105,20,20);	m_KeyBoard[17].SetRectPKorShift(100,125,20,20);
	m_KeyBoard[6].SetRectPKorShift(360,105,20,20);	m_KeyBoard[18].SetRectPKorShift(120,125,20,20);
	m_KeyBoard[7].SetRectPKorShift(380,105,20,20);	m_KeyBoard[19].SetRectPKorShift(140,125,20,20);
	m_KeyBoard[8].SetRectPKorShift(400,105,20,20);	m_KeyBoard[20].SetRectPKorShift(340,125,20,20);
	m_KeyBoard[9].SetRectPKorShift(400,105,20,20);	m_KeyBoard[21].SetRectPKorShift(360,125,20,20);
	m_KeyBoard[10].SetRectPKorShift(440,105,20,20);	m_KeyBoard[22].SetRectPKorShift(380,125,20,20);
	m_KeyBoard[11].SetRectPKorShift(460,105,20,20);	m_KeyBoard[23].SetRectPKorShift(400,125,20,20);
	// 세번째줄										// 네번째줄
	m_KeyBoard[24].SetRectPKorShift(0,145,20,20);	m_KeyBoard[35].SetRectPKorShift(0,165,20,20);
	m_KeyBoard[25].SetRectPKorShift(20,145,20,20);	m_KeyBoard[36].SetRectPKorShift(20,165,20,20);
	m_KeyBoard[26].SetRectPKorShift(40,145,20,20);	m_KeyBoard[37].SetRectPKorShift(40,165,20,20);
	m_KeyBoard[27].SetRectPKorShift(60,145,20,20);	m_KeyBoard[38].SetRectPKorShift(60,165,20,20);
	m_KeyBoard[28].SetRectPKorShift(80,145,20,20);	m_KeyBoard[39].SetRectPKorShift(80,165,20,20);
	m_KeyBoard[29].SetRectPKorShift(100,145,20,20);	m_KeyBoard[40].SetRectPKorShift(100,165,20,20);
	m_KeyBoard[30].SetRectPKorShift(120,145,20,20);	m_KeyBoard[41].SetRectPKorShift(120,165,20,20);
	m_KeyBoard[31].SetRectPKorShift(140,145,20,20);	m_KeyBoard[42].SetRectPKorShift(200,165,20,20);
	m_KeyBoard[32].SetRectPKorShift(160,145,20,20);	m_KeyBoard[43].SetRectPKorShift(220,165,20,20);
	m_KeyBoard[33].SetRectPKorShift(220,145,20,20);	m_KeyBoard[44].SetRectPKorShift(240,165,20,20);
	m_KeyBoard[34].SetRectPKorShift(240,145,20,20);	m_KeyBoard[45].SetRectPKorShift(52,185,132,20);

	// 영어 no push / no shift
	// 첫줄											// 두번째줄
	m_KeyBoard[0].SetRectNPEng(0,205,21,21);		m_KeyBoard[12].SetRectNPEng(0,226,21,21);
	m_KeyBoard[1].SetRectNPEng(21,205,21,21);		m_KeyBoard[13].SetRectNPEng(21,226,21,21);
	m_KeyBoard[2].SetRectNPEng(42,205,21,21);		m_KeyBoard[14].SetRectNPEng(42,226,21,21);
	m_KeyBoard[3].SetRectNPEng(63,205,21,21);		m_KeyBoard[15].SetRectNPEng(63,226,21,21);
	m_KeyBoard[4].SetRectNPEng(84,205,21,21);		m_KeyBoard[16].SetRectNPEng(84,226,21,21);
	m_KeyBoard[5].SetRectNPEng(105,205,21,21);		m_KeyBoard[17].SetRectNPEng(105,226,21,21);
	m_KeyBoard[6].SetRectNPEng(126,205,21,21);		m_KeyBoard[18].SetRectNPEng(126,226,21,21);
	m_KeyBoard[7].SetRectNPEng(147,205,21,21);		m_KeyBoard[19].SetRectNPEng(147,226,21,21);
	m_KeyBoard[8].SetRectNPEng(168,205,21,21);		m_KeyBoard[20].SetRectNPEng(168,226,21,21);
	m_KeyBoard[9].SetRectNPEng(189,205,21,21);		m_KeyBoard[21].SetRectNPEng(189,226,21,21);
	m_KeyBoard[10].SetRectNPEng(210,205,21,21);		m_KeyBoard[22].SetRectNPEng(210,226,21,21);
	m_KeyBoard[11].SetRectNPEng(231,205,21,21);		m_KeyBoard[23].SetRectNPEng(231,226,21,21);
	// 세번째줄										// 네번째줄
	m_KeyBoard[24].SetRectNPEng(0,247,21,21);		m_KeyBoard[35].SetRectNPEng(0,268,21,21);
	m_KeyBoard[25].SetRectNPEng(21,247,21,21);		m_KeyBoard[36].SetRectNPEng(21,268,21,21);
	m_KeyBoard[26].SetRectNPEng(42,247,21,21);		m_KeyBoard[37].SetRectNPEng(42,268,21,21);
	m_KeyBoard[27].SetRectNPEng(63,247,21,21);		m_KeyBoard[38].SetRectNPEng(63,268,21,21);
	m_KeyBoard[28].SetRectNPEng(84,247,21,21);		m_KeyBoard[39].SetRectNPEng(84,268,21,21);
	m_KeyBoard[29].SetRectNPEng(105,247,21,21);		m_KeyBoard[40].SetRectNPEng(105,268,21,21);
	m_KeyBoard[30].SetRectNPEng(126,247,21,21);		m_KeyBoard[41].SetRectNPEng(126,268,21,21);
	m_KeyBoard[31].SetRectNPEng(147,247,21,21);		m_KeyBoard[42].SetRectNPEng(147,268,21,21);
	m_KeyBoard[32].SetRectNPEng(168,247,21,21);		m_KeyBoard[43].SetRectNPEng(168,268,21,21);
	m_KeyBoard[33].SetRectNPEng(189,247,21,21);		m_KeyBoard[44].SetRectNPEng(189,268,21,21);
	m_KeyBoard[34].SetRectNPEng(210,247,21,21);		m_KeyBoard[45].SetRectNPEng(53,84,133,21);


	// 영어 push / no shift
	// 첫줄											// 두번째줄
	m_KeyBoard[0].SetRectPEng(0,289,20,20);		m_KeyBoard[12].SetRectPEng(0,309,20,20);
	m_KeyBoard[1].SetRectPEng(20,289,20,20);	m_KeyBoard[13].SetRectPEng(20,309,20,20);
	m_KeyBoard[2].SetRectPEng(40,289,20,20);	m_KeyBoard[14].SetRectPEng(40,309,20,20);
	m_KeyBoard[3].SetRectPEng(60,289,20,20);	m_KeyBoard[15].SetRectPEng(60,309,20,20);
	m_KeyBoard[4].SetRectPEng(80,289,20,20);	m_KeyBoard[16].SetRectPEng(80,309,20,20);
	m_KeyBoard[5].SetRectPEng(100,289,20,20);	m_KeyBoard[17].SetRectPEng(100,309,20,20);
	m_KeyBoard[6].SetRectPEng(120,289,20,20);	m_KeyBoard[18].SetRectPEng(120,309,20,20);
	m_KeyBoard[7].SetRectPEng(140,289,20,20);	m_KeyBoard[19].SetRectPEng(140,309,20,20);
	m_KeyBoard[8].SetRectPEng(160,289,20,20);	m_KeyBoard[20].SetRectPEng(160,309,20,20);
	m_KeyBoard[9].SetRectPEng(180,289,20,20);	m_KeyBoard[21].SetRectPEng(180,309,20,20);
	m_KeyBoard[10].SetRectPEng(200,289,20,20);	m_KeyBoard[22].SetRectPEng(200,309,20,20);
	m_KeyBoard[11].SetRectPEng(220,289,20,20);	m_KeyBoard[23].SetRectPEng(220,309,20,20);
	// 세번째줄										// 네번째줄
	m_KeyBoard[24].SetRectPEng(0,329,20,20);	m_KeyBoard[35].SetRectPEng(0,349,20,20);
	m_KeyBoard[25].SetRectPEng(20,329,20,20);	m_KeyBoard[36].SetRectPEng(20,349,20,20);
	m_KeyBoard[26].SetRectPEng(40,329,20,20);	m_KeyBoard[37].SetRectPEng(40,349,20,20);
	m_KeyBoard[27].SetRectPEng(60,329,20,20);	m_KeyBoard[38].SetRectPEng(60,349,20,20);
	m_KeyBoard[28].SetRectPEng(80,329,20,20);	m_KeyBoard[39].SetRectPEng(80,349,20,20);
	m_KeyBoard[29].SetRectPEng(100,329,20,20);	m_KeyBoard[40].SetRectPEng(100,349,20,20);
	m_KeyBoard[30].SetRectPEng(120,329,20,20);	m_KeyBoard[41].SetRectPEng(120,349,20,20);
	m_KeyBoard[31].SetRectPEng(140,329,20,20);	m_KeyBoard[42].SetRectPEng(140,349,20,20);
	m_KeyBoard[32].SetRectPEng(160,329,20,20);	m_KeyBoard[43].SetRectPEng(160,349,20,20);
	m_KeyBoard[33].SetRectPEng(180,329,20,20);	m_KeyBoard[44].SetRectPEng(180,349,20,20);
	m_KeyBoard[34].SetRectPEng(200,329,20,20);	m_KeyBoard[45].SetRectPEng(52,185,132,20);

	// 영어 no push / shift
	// 첫줄												// 두번째줄
	m_KeyBoard[0].SetRectNPEngShift(252,205,21,21);		m_KeyBoard[12].SetRectNPEngShift(252,226,21,21);
	m_KeyBoard[1].SetRectNPEngShift(273,205,21,21);		m_KeyBoard[13].SetRectNPEngShift(273,226,21,21);
	m_KeyBoard[2].SetRectNPEngShift(294,205,21,21);		m_KeyBoard[14].SetRectNPEngShift(294,226,21,21);
	m_KeyBoard[3].SetRectNPEngShift(315,205,21,21);		m_KeyBoard[15].SetRectNPEngShift(315,226,21,21);
	m_KeyBoard[4].SetRectNPEngShift(336,205,21,21);		m_KeyBoard[16].SetRectNPEngShift(336,226,21,21);
	m_KeyBoard[5].SetRectNPEngShift(357,205,21,21);		m_KeyBoard[17].SetRectNPEngShift(357,226,21,21);
	m_KeyBoard[6].SetRectNPEngShift(378,205,21,21);		m_KeyBoard[18].SetRectNPEngShift(378,226,21,21);
	m_KeyBoard[7].SetRectNPEngShift(399,205,21,21);		m_KeyBoard[19].SetRectNPEngShift(399,226,21,21);
	m_KeyBoard[8].SetRectNPEngShift(420,205,21,21);		m_KeyBoard[20].SetRectNPEngShift(420,226,21,21);
	m_KeyBoard[9].SetRectNPEngShift(441,205,21,21);		m_KeyBoard[21].SetRectNPEngShift(441,226,21,21);
	m_KeyBoard[10].SetRectNPEngShift(462,205,21,21);	m_KeyBoard[22].SetRectNPEngShift(462,226,21,21);
	m_KeyBoard[11].SetRectNPEngShift(483,205,21,21);	m_KeyBoard[23].SetRectNPEngShift(483,226,21,21);
	// 세번째줄											// 네번째줄
	m_KeyBoard[24].SetRectNPEngShift(231,247,21,21);	m_KeyBoard[35].SetRectNPEngShift(210,268,21,21);
	m_KeyBoard[25].SetRectNPEngShift(252,247,21,21);	m_KeyBoard[36].SetRectNPEngShift(231,268,21,21);
	m_KeyBoard[26].SetRectNPEngShift(273,247,21,21);	m_KeyBoard[37].SetRectNPEngShift(252,268,21,21);
	m_KeyBoard[27].SetRectNPEngShift(294,247,21,21);	m_KeyBoard[38].SetRectNPEngShift(273,268,21,21);
	m_KeyBoard[28].SetRectNPEngShift(315,247,21,21);	m_KeyBoard[39].SetRectNPEngShift(294,268,21,21);
	m_KeyBoard[29].SetRectNPEngShift(336,247,21,21);	m_KeyBoard[40].SetRectNPEngShift(315,268,21,21);
	m_KeyBoard[30].SetRectNPEngShift(357,247,21,21);	m_KeyBoard[41].SetRectNPEngShift(336,268,21,21);
	m_KeyBoard[31].SetRectNPEngShift(378,247,21,21);	m_KeyBoard[42].SetRectNPEngShift(357,268,21,21);
	m_KeyBoard[32].SetRectNPEngShift(399,247,21,21);	m_KeyBoard[43].SetRectNPEngShift(378,268,21,21);
	m_KeyBoard[33].SetRectNPEngShift(420,247,21,21);	m_KeyBoard[44].SetRectNPEngShift(399,268,21,21);
	m_KeyBoard[34].SetRectNPEngShift(441,247,21,21);	m_KeyBoard[45].SetRectNPEngShift(53,84,133,21);


	// 영어 push / shift
	// 첫줄											// 두번째줄
	m_KeyBoard[0].SetRectPEngShift(240,289,20,20);	m_KeyBoard[12].SetRectPEngShift(240,309,20,20);
	m_KeyBoard[1].SetRectPEngShift(260,289,20,20);	m_KeyBoard[13].SetRectPEngShift(260,309,20,20);
	m_KeyBoard[2].SetRectPEngShift(280,289,20,20);	m_KeyBoard[14].SetRectPEngShift(280,309,20,20);
	m_KeyBoard[3].SetRectPEngShift(300,289,20,20);	m_KeyBoard[15].SetRectPEngShift(300,309,20,20);
	m_KeyBoard[4].SetRectPEngShift(320,289,20,20);	m_KeyBoard[16].SetRectPEngShift(320,309,20,20);
	m_KeyBoard[5].SetRectPEngShift(340,289,20,20);	m_KeyBoard[17].SetRectPEngShift(340,309,20,20);
	m_KeyBoard[6].SetRectPEngShift(360,289,20,20);	m_KeyBoard[18].SetRectPEngShift(360,309,20,20);
	m_KeyBoard[7].SetRectPEngShift(380,289,20,20);	m_KeyBoard[19].SetRectPEngShift(380,309,20,20);
	m_KeyBoard[8].SetRectPEngShift(400,289,20,20);	m_KeyBoard[20].SetRectPEngShift(400,309,20,20);
	m_KeyBoard[9].SetRectPEngShift(420,289,20,20);	m_KeyBoard[21].SetRectPEngShift(420,309,20,20);
	m_KeyBoard[10].SetRectPEngShift(440,289,20,20);	m_KeyBoard[22].SetRectPEngShift(440,309,20,20);
	m_KeyBoard[11].SetRectPEngShift(460,289,20,20);	m_KeyBoard[23].SetRectPEngShift(460,309,20,20);
	// 세번째줄										// 네번째줄
	m_KeyBoard[24].SetRectPEngShift(220,329,20,20);	m_KeyBoard[35].SetRectPEngShift(200,349,20,20);
	m_KeyBoard[25].SetRectPEngShift(240,329,20,20);	m_KeyBoard[36].SetRectPEngShift(220,349,20,20);
	m_KeyBoard[26].SetRectPEngShift(260,329,20,20);	m_KeyBoard[37].SetRectPEngShift(240,349,20,20);
	m_KeyBoard[27].SetRectPEngShift(280,329,20,20);	m_KeyBoard[38].SetRectPEngShift(260,349,20,20);
	m_KeyBoard[28].SetRectPEngShift(300,329,20,20);	m_KeyBoard[39].SetRectPEngShift(280,349,20,20);
	m_KeyBoard[29].SetRectPEngShift(320,329,20,20);	m_KeyBoard[40].SetRectPEngShift(300,349,20,20);
	m_KeyBoard[30].SetRectPEngShift(340,329,20,20);	m_KeyBoard[41].SetRectPEngShift(320,349,20,20);
	m_KeyBoard[31].SetRectPEngShift(360,329,20,20);	m_KeyBoard[42].SetRectPEngShift(340,349,20,20);
	m_KeyBoard[32].SetRectPEngShift(380,329,20,20);	m_KeyBoard[43].SetRectPEngShift(360,349,20,20);
	m_KeyBoard[33].SetRectPEngShift(400,329,20,20);	m_KeyBoard[44].SetRectPEngShift(380,349,20,20);
	m_KeyBoard[34].SetRectPEngShift(420,329,20,20);	m_KeyBoard[45].SetRectPEngShift(52,185,132,20);

	m_FunKey[0].SetNPRect(273,42,42,21);
	m_FunKey[0].SetPRect(260,145,41,20);
	m_FunKey[1].SetNPRect(273,63,55,21);
	m_FunKey[1].SetPRect(260,165,54,20);
	m_FunKey[2].SetNPRect(0,84,53,21);
	m_FunKey[2].SetPRect(0,185,52,20);
	m_FunKey[3].SetNPRect(186,84,53,21);
	m_FunKey[3].SetPRect(184,185,52,20);
	m_FunKey[4].SetNPRect(0,400,244,28);
	m_FunKey[4].SetPRect(0,400,244,28);
	m_FunKey[5].SetNPRect(163,369,55,31);
	m_FunKey[5].SetPRect(109,369,54,30);
	m_FunKey[6].SetNPRect(54,369,55,31);
	m_FunKey[6].SetPRect(0,369,54,30);

}

void VirtualKeyboard::KeyPickSetup()
{
	m_KeyBoard[0].SetPickArea(39,70,21,21);
	m_KeyBoard[1].SetPickArea(61,70,21,21);
	m_KeyBoard[2].SetPickArea(83,70,21,21);
	m_KeyBoard[3].SetPickArea(105,70,21,21);
	m_KeyBoard[4].SetPickArea(127,70,21,21);
	m_KeyBoard[5].SetPickArea(149,70,21,21);
	m_KeyBoard[6].SetPickArea(171,70,21,21);
	m_KeyBoard[7].SetPickArea(193,70,21,21);
	m_KeyBoard[8].SetPickArea(215,70,21,21);
	m_KeyBoard[9].SetPickArea(237,70,21,21);
	m_KeyBoard[10].SetPickArea(259,70,21,21);
	m_KeyBoard[11].SetPickArea(281,70,21,21);

	m_KeyBoard[12].SetPickArea(29,92,21,21);
	m_KeyBoard[13].SetPickArea(51,92,21,21);
	m_KeyBoard[14].SetPickArea(73,92,21,21);
	m_KeyBoard[15].SetPickArea(95,92,21,21);
	m_KeyBoard[16].SetPickArea(117,92,21,21);
	m_KeyBoard[17].SetPickArea(139,92,21,21);
	m_KeyBoard[18].SetPickArea(161,92,21,21);
	m_KeyBoard[19].SetPickArea(183,92,21,21);
	m_KeyBoard[20].SetPickArea(205,92,21,21);
	m_KeyBoard[21].SetPickArea(227,92,21,21);
	m_KeyBoard[22].SetPickArea(249,92,21,21);
	m_KeyBoard[23].SetPickArea(271,92,21,21);

	m_KeyBoard[24].SetPickArea(61,114,21,21);
	m_KeyBoard[25].SetPickArea(83,114,21,21);
	m_KeyBoard[26].SetPickArea(105,114,21,21);
	m_KeyBoard[27].SetPickArea(127,114,21,21);
	m_KeyBoard[28].SetPickArea(149,114,21,21);
	m_KeyBoard[29].SetPickArea(171,114,21,21);
	m_KeyBoard[30].SetPickArea(193,114,21,21);
	m_KeyBoard[31].SetPickArea(215,114,21,21);
	m_KeyBoard[32].SetPickArea(237,114,21,21);
	m_KeyBoard[33].SetPickArea(259,114,21,21);
	m_KeyBoard[34].SetPickArea(281,114,21,21);

	m_KeyBoard[35].SetPickArea(74,136,21,21);
	m_KeyBoard[36].SetPickArea(96,136,21,21);
	m_KeyBoard[37].SetPickArea(118,136,21,21);
	m_KeyBoard[38].SetPickArea(140,136,21,21);
	m_KeyBoard[39].SetPickArea(162,136,21,21);
	m_KeyBoard[40].SetPickArea(184,136,21,21);
	m_KeyBoard[41].SetPickArea(206,136,21,21);
	m_KeyBoard[42].SetPickArea(228,136,21,21);
	m_KeyBoard[43].SetPickArea(250,136,21,21);
	m_KeyBoard[44].SetPickArea(272,136,21,21);
	m_KeyBoard[45].SetPickArea(93,158,133,21);

	m_FunKey[0].SetPickArea(18,114,42,21);
	m_FunKey[1].SetPickArea(18,136,55,21);
	m_FunKey[2].SetPickArea(39,158,53,21);
	m_FunKey[3].SetPickArea(227,158,53,21);
	m_FunKey[4].SetPickArea(49,29,244,28);
	m_FunKey[5].SetPickArea(178,198,55,30);
	m_FunKey[6].SetPickArea(87,198,55,30);
}


INT VirtualKeyboard::FrameMove()
{
	if(m_VertexArray.empty() || m_bChange)
	{
		GenVertex();
	}


	if(DGT_VKB_SCROLLV == m_AniType)
	{
		if(m_AnimationState == DGT_VKB_APPEAR)
		{
			if(m_AnimationSeed < 240)
				m_AnimationSeed += (INT)(24 * m_fAniSpeed);
			else
				m_AnimationState = DGT_VKB_NONE;
		}

		else if(m_AnimationState == DGT_VKB_DISAPPEAR)
		{
			if(m_AnimationSeed > 0)
			{
				m_AnimationSeed -= (INT)(24 * m_fAniSpeed);
			}
			else
			{
				m_AnimationState = DGT_VKB_APPEAR;

				if(m_pFinish)
					*m_pFinish = FALSE;
			}
		}
	}

	else if(DGT_VKB_SCROLLH == m_AniType)
	{
		if(m_AnimationState == DGT_VKB_APPEAR)
		{
			if(m_AnimationSeed < 320)
				m_AnimationSeed += (INT)(32 * m_fAniSpeed);
			else
				m_AnimationState = DGT_VKB_NONE;
		}

		else if(m_AnimationState == DGT_VKB_DISAPPEAR)
		{
			glTranslatef(320.0f - m_AnimationSeed, 0.0f, 0.0f);
			if(m_AnimationSeed > 0)
			{
				m_AnimationSeed -= (INT)(32 * m_fAniSpeed);
			}
			else
			{
				m_AnimationState = DGT_VKB_APPEAR;

				if(m_pFinish)
					*m_pFinish = FALSE;
			}
		}
	}

	else if(DGT_VKB_FADE == m_AniType)
	{
		if(m_AnimationState == DGT_VKB_APPEAR)
		{
			if(m_AnimationSeed < 100)
				m_AnimationSeed += (INT)(10 * m_fAniSpeed);
			else
				m_AnimationState = DGT_VKB_NONE;
		}

		else if(m_AnimationState == DGT_VKB_DISAPPEAR)
		{
			if(m_AnimationSeed > 0)
			{
				m_AnimationSeed -= (INT)(10 * m_fAniSpeed);
			}
			else
			{
				m_AnimationState = DGT_VKB_APPEAR;
				m_bNoneuse = FALSE;
				m_bChange = TRUE;
				m_bBackspace = FALSE;
				m_bCapsLock = FALSE;
				m_bShift = FALSE;
				m_bLanguage = FALSE;
				m_bOK = FALSE;
				m_bQUIT = FALSE;

				if(m_pFinish)
					*m_pFinish = FALSE;
			}
		}
	}

	else if(DGT_VKB_NOANI == m_AniType)
	{
		if(m_AnimationState == DGT_VKB_APPEAR)
		{
			m_AnimationState = DGT_VKB_NONE;
		}

		else if(m_AnimationState == DGT_VKB_DISAPPEAR)
		{
			m_AnimationState = DGT_VKB_APPEAR;
			m_bNoneuse = FALSE;
			m_bChange = TRUE;
			m_bBackspace = FALSE;
			m_bCapsLock = FALSE;
			m_bShift = FALSE;
			m_bLanguage = FALSE;
			m_bOK = FALSE;
			m_bQUIT = FALSE;

			if(m_pFinish)
				*m_pFinish = FALSE;
		}
	}

	if(m_bQUIT)
		this->ClearBuffer();

	return DGE_OK;
}



void VirtualKeyboard::Render()
{
	if(m_nTex == 0)
		return;


	// 월드 메트릭스의 초기화
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();


	if(DGT_VKB_SCROLLV == m_AniType)
	{
		DrawColorBox(0,0,320,m_AnimationSeed,128, 10, 10, 10);
	}

	else if(DGT_VKB_SCROLLH == m_AniType)
	{
		DrawColorBox(0,0,m_AnimationSeed,240,128,10,10,10);
		if(m_AnimationState == DGT_VKB_APPEAR)
		{
			glTranslatef(320.0f - m_AnimationSeed, 0.0f, 0.0f);
		}
		else if(m_AnimationState == DGT_VKB_DISAPPEAR)
		{
			glTranslatef(320.0f - m_AnimationSeed, 0.0f, 0.0f);
		}
	}

	else if(DGT_VKB_FADE == m_AniType)
	{
		if(m_AnimationState == DGT_VKB_APPEAR)
		{
			DrawColorBox((INT)(160 -(320 *(m_AnimationSeed / 200.0f))), (INT)(120 -(240 *(m_AnimationSeed / 200.0f)))
				, (INT)(320 *(m_AnimationSeed / 100.0f)), (INT)(240 *(m_AnimationSeed / 100.0f)), 128, 10, 10, 10);

			glTranslatef(160 -(320 *(m_AnimationSeed / 200.0f)), 120 -(240 *(m_AnimationSeed / 200.0f)), 0.0f);
			glScalef(m_AnimationSeed / 100.0f, m_AnimationSeed / 100.0f, 0.0f);
		}
		else if(m_AnimationState == DGT_VKB_DISAPPEAR)
		{
			DrawColorBox((INT)(160 -(320 *(m_AnimationSeed / 200.0f))), (INT)(120 -(240 *(m_AnimationSeed / 200.0f)))
				, (INT)(320 *(m_AnimationSeed / 100.0f)), (INT)(240 *(m_AnimationSeed / 100.0f)), 128, 10, 10, 10);
			glTranslatef(160 -(320 *(m_AnimationSeed / 200.0f)), 120 -(240 *(m_AnimationSeed / 200.0f)), 0.0f);
			glScalef(m_AnimationSeed / 100.0f, m_AnimationSeed / 100.0f, 0.0f);
		}
		else
		{
			DrawColorBox(0, 0, 320, 240, 128, 10, 10, 10);
		}
	}

	else if(DGT_VKB_NOANI == m_AniType)
	{
	}


	// 텍스쳐를 활성화 시켜서 랜더링 준비
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);

//	glEnable(GL_ALPHA_TEST);
//	glAlphaFunc(GL_GREATER, 0);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBindTexture(GL_TEXTURE_2D, m_nTex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer		(3, GL_SHORT, 0, &(m_VertexArray.front()));
	glTexCoordPointer	(2, GL_FLOAT, 0, &(m_STArray.front()));

	glDrawArrays(GL_TRIANGLES, 0, m_VertexArray.size()/3);

	// 해제 코드
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);

	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);


//	glDisable(GL_ALPHA_TEST);
//	glDisable(GL_BLEND);

	//if(m_AnimationState == DGT_VKB_NONE)
	//{
	//	m_pFont->Flip();
	//}
}




void VirtualKeyboard::CopyString(char *Output, INT length)
{
	if(m_bDefault == FALSE)
	{
		for(INT i = 0; i < length; i++)
		{
			Output[i] = m_ConvertBuffer[i];
		}
	} else
	{
		for(INT i = 0; i < length; i++)
		{
			Output[i] = m_DefaultBuffer[i];
		}
	}
}

void VirtualKeyboard::GenVertex()
{
	INT	i=0;

	INT PushCode = 0, LangShiftCode = 0;
	m_STArray.clear();
	m_VertexArray.clear();
	if(m_bShift == FALSE && m_bLanguage == FALSE)
		LangShiftCode = 0;
	else if(m_bShift == TRUE && m_bLanguage == FALSE)
		LangShiftCode = 1;
	else if(m_bShift == FALSE && m_bLanguage == TRUE)
		LangShiftCode = 2;
	else if(m_bShift == TRUE && m_bLanguage == TRUE)
		LangShiftCode = 3;

	for(i = 0; i < 46 ; i++)
	{
		PushCode = m_KeyBoard[i].m_iPushed;
		if(m_bCapsLock != FALSE && m_bLanguage == FALSE && m_KeyBoard[i].m_bSpecial[0] == FALSE)
		{
			m_STArray.push_back(m_KeyBoard[i].m_KeyRect[PushCode][1][0]);
			m_STArray.push_back(m_KeyBoard[i].m_KeyRect[PushCode][1][1]);
			m_STArray.push_back(m_KeyBoard[i].m_KeyRect[PushCode][1][2]);
			m_STArray.push_back(m_KeyBoard[i].m_KeyRect[PushCode][1][1]);
			m_STArray.push_back(m_KeyBoard[i].m_KeyRect[PushCode][1][0]);
			m_STArray.push_back(m_KeyBoard[i].m_KeyRect[PushCode][1][3]);
			m_STArray.push_back(m_KeyBoard[i].m_KeyRect[PushCode][1][0]);
			m_STArray.push_back(m_KeyBoard[i].m_KeyRect[PushCode][1][3]);
			m_STArray.push_back(m_KeyBoard[i].m_KeyRect[PushCode][1][2]);
			m_STArray.push_back(m_KeyBoard[i].m_KeyRect[PushCode][1][1]);
			m_STArray.push_back(m_KeyBoard[i].m_KeyRect[PushCode][1][2]);
			m_STArray.push_back(m_KeyBoard[i].m_KeyRect[PushCode][1][3]);

		} else
		{
			m_STArray.push_back(m_KeyBoard[i].m_KeyRect[PushCode][LangShiftCode][0]);
			m_STArray.push_back(m_KeyBoard[i].m_KeyRect[PushCode][LangShiftCode][1]);
			m_STArray.push_back(m_KeyBoard[i].m_KeyRect[PushCode][LangShiftCode][2]);
			m_STArray.push_back(m_KeyBoard[i].m_KeyRect[PushCode][LangShiftCode][1]);
			m_STArray.push_back(m_KeyBoard[i].m_KeyRect[PushCode][LangShiftCode][0]);
			m_STArray.push_back(m_KeyBoard[i].m_KeyRect[PushCode][LangShiftCode][3]);
			m_STArray.push_back(m_KeyBoard[i].m_KeyRect[PushCode][LangShiftCode][0]);
			m_STArray.push_back(m_KeyBoard[i].m_KeyRect[PushCode][LangShiftCode][3]);
			m_STArray.push_back(m_KeyBoard[i].m_KeyRect[PushCode][LangShiftCode][2]);
			m_STArray.push_back(m_KeyBoard[i].m_KeyRect[PushCode][LangShiftCode][1]);
			m_STArray.push_back(m_KeyBoard[i].m_KeyRect[PushCode][LangShiftCode][2]);
			m_STArray.push_back(m_KeyBoard[i].m_KeyRect[PushCode][LangShiftCode][3]);
		}

		m_VertexArray.push_back((short)(m_KeyBoard[i].m_PickArea[0] + PushCode));
		m_VertexArray.push_back((short)(m_KeyBoard[i].m_PickArea[1] + PushCode));
		m_VertexArray.push_back(0);
		m_VertexArray.push_back((short)(m_KeyBoard[i].m_PickArea[2] + m_KeyBoard[i].m_PickArea[0]));
		m_VertexArray.push_back((short)(m_KeyBoard[i].m_PickArea[1] + PushCode));
		m_VertexArray.push_back(0);
		m_VertexArray.push_back((short)(m_KeyBoard[i].m_PickArea[0] + PushCode));
		m_VertexArray.push_back((short)(m_KeyBoard[i].m_PickArea[3] + m_KeyBoard[i].m_PickArea[1]));
		m_VertexArray.push_back(0);
		m_VertexArray.push_back((short)(m_KeyBoard[i].m_PickArea[0] + PushCode));
		m_VertexArray.push_back((short)(m_KeyBoard[i].m_PickArea[3] + m_KeyBoard[i].m_PickArea[1]));
		m_VertexArray.push_back(0);
		m_VertexArray.push_back((short)(m_KeyBoard[i].m_PickArea[2] + m_KeyBoard[i].m_PickArea[0]));
		m_VertexArray.push_back((short)(m_KeyBoard[i].m_PickArea[1] + PushCode));
		m_VertexArray.push_back(0);
		m_VertexArray.push_back((short)(m_KeyBoard[i].m_PickArea[2] + m_KeyBoard[i].m_PickArea[0]));
		m_VertexArray.push_back((short)(m_KeyBoard[i].m_PickArea[3] + m_KeyBoard[i].m_PickArea[1]));
		m_VertexArray.push_back(0);
	}

	for(i = 0; i < 7; i++)
	{
		PushCode = *(m_FunKey[i].m_pPushed);
		m_STArray.push_back(m_FunKey[i].m_KeyRect[PushCode][0]);
		m_STArray.push_back(m_FunKey[i].m_KeyRect[PushCode][1]);
		m_STArray.push_back(m_FunKey[i].m_KeyRect[PushCode][2]);
		m_STArray.push_back(m_FunKey[i].m_KeyRect[PushCode][1]);
		m_STArray.push_back(m_FunKey[i].m_KeyRect[PushCode][0]);
		m_STArray.push_back(m_FunKey[i].m_KeyRect[PushCode][3]);
		m_STArray.push_back(m_FunKey[i].m_KeyRect[PushCode][0]);
		m_STArray.push_back(m_FunKey[i].m_KeyRect[PushCode][3]);
		m_STArray.push_back(m_FunKey[i].m_KeyRect[PushCode][2]);
		m_STArray.push_back(m_FunKey[i].m_KeyRect[PushCode][1]);
		m_STArray.push_back(m_FunKey[i].m_KeyRect[PushCode][2]);
		m_STArray.push_back(m_FunKey[i].m_KeyRect[PushCode][3]);

		m_VertexArray.push_back((short)(m_FunKey[i].m_PickArea[0] + PushCode));
		m_VertexArray.push_back((short)(m_FunKey[i].m_PickArea[1] + PushCode));
		m_VertexArray.push_back(0);
		m_VertexArray.push_back((short)(m_FunKey[i].m_PickArea[2] + m_FunKey[i].m_PickArea[0]));
		m_VertexArray.push_back((short)(m_FunKey[i].m_PickArea[1] + PushCode));
		m_VertexArray.push_back(0);
		m_VertexArray.push_back((short)(m_FunKey[i].m_PickArea[0] + PushCode));
		m_VertexArray.push_back((short)(m_FunKey[i].m_PickArea[3] + m_FunKey[i].m_PickArea[1]));
		m_VertexArray.push_back(0);
		m_VertexArray.push_back((short)(m_FunKey[i].m_PickArea[0] + PushCode));
		m_VertexArray.push_back((short)(m_FunKey[i].m_PickArea[3] + m_FunKey[i].m_PickArea[1]));
		m_VertexArray.push_back(0);
		m_VertexArray.push_back((short)(m_FunKey[i].m_PickArea[2] + m_FunKey[i].m_PickArea[0]));
		m_VertexArray.push_back((short)(m_FunKey[i].m_PickArea[1] + PushCode));
		m_VertexArray.push_back(0);
		m_VertexArray.push_back((short)(m_FunKey[i].m_PickArea[2] + m_FunKey[i].m_PickArea[0]));
		m_VertexArray.push_back((short)(m_FunKey[i].m_PickArea[3] + m_FunKey[i].m_PickArea[1]));
		m_VertexArray.push_back(0);
	}
}

void VirtualKeyboard::ConvertString()
{
	INT i;
	INT j;

	// m_ConvertBuffer을 위한 마지막 위치 포인트
	INT TaskPoint = 0;
	BYTE InputWord[256] = {0, };
	BYTE OutputWord[256] = {0, };
	if(m_bChange)
	{
		memset(m_ConvertBuffer, 0, sizeof(BYTE)*512);
		for(i = 0; i < m_BackPosition; i++)
		{
			if(m_LangCode[i] == 0)
			{
				INT WordTail = GetEngWordLength(i);
				// 측정된 부분을 InputWord에 복사한다.
				for(INT j = i; j < WordTail; j++)
				{
					m_ConvertBuffer[TaskPoint++] = m_InputBuffer[j];
				}
				// 한글로 변화하는데 까지 변환된 버퍼에 추가한다. 변환은 하지 않는다
				i = WordTail - 1;
			}
			else
			{
				INT WordTail = GetKorWordLength(i);
				// 측정된 부분을 InputWord에 복사한다.
				INT k = 0;

				for(j = i; j < WordTail; j++, k++)
				{
					InputWord[k] = m_InputBuffer[j];
				}
				InputWord[k] = 32;
				// 특수문자는 안됨
				m_cAutomata.GetHangul(InputWord, OutputWord);
				INT Korlen = strlen((char*)OutputWord);

				for(j = 0;j < Korlen; j++)
				{
					m_ConvertBuffer[TaskPoint++] = OutputWord[j];
				}
				// 영문으로 변화하는데까지 추출하여 변환한뒤 변환된 버퍼에 추가한다.
				i = WordTail - 1;
			}
			memset(InputWord, 0, sizeof(BYTE)*256);
			memset(OutputWord, 0, sizeof(BYTE)*256);
		}


		if(m_bDefault == FALSE)
			m_sDstStr = (char*)m_ConvertBuffer;
		else
			m_sDstStr = (char*)m_DefaultBuffer;

	}
}

INT VirtualKeyboard::GetKorWordLength(INT front)
{
	for(INT i = front; i < 256; i++)
	{
		if(m_LangCode[i] == 0)
		{
			return i;
		}
	}
	return 255;
}

INT VirtualKeyboard::GetEngWordLength(INT front)
{
	for(INT i = front; i < 256; i++)
	{
		if(m_LangCode[i] == 1)
		{
			return i;
		}
	}
	return 255;
}

void VirtualKeyboard::KeyStateSetup()
{
	m_FunKey[0].SetStatePtr(&m_bCapsLock);
	m_FunKey[1].SetStatePtr(&m_bShift);
	m_FunKey[2].SetStatePtr(&m_bLanguage);
	m_FunKey[3].SetStatePtr(&m_bBackspace);
	m_FunKey[4].SetStatePtr(&m_bNoneuse);
	m_FunKey[5].SetStatePtr(&m_bQUIT);
	m_FunKey[6].SetStatePtr(&m_bOK);
}

void VirtualKeyboard::SetFinishCode(BOOL* value)
{
	m_pFinish = value;
}

void VirtualKeyboard::SetFPS( BOOL fps )
{
	if(fps)
	{
		m_fAniSpeed = 1.0f;
	}
	else
	{
		m_fAniSpeed = 2.0f;
	}
}

void VirtualKeyboard::Destroy()
{
	m_STArray.clear();
	m_VertexArray.clear();
}


void VirtualKeyboard::SetDefaultString( char* pString )
{
	m_bDefault = TRUE;
	m_bChange = TRUE;
	memset(m_DefaultBuffer, 0, sizeof(m_DefaultBuffer));
	memcpy(m_DefaultBuffer, pString, strlen(pString));
	ConvertString();
}

void VirtualKeyboard::SetLimit( BYTE EngLength, BYTE KorLength )
{
	if(EngLength > 18)
	{
		m_LimitEng = 18;
	} else
	{
		m_LimitEng = EngLength;
	}
	if(KorLength > 20)
	{
		m_LimitKor = 20;
	} else
	{
		m_LimitKor = KorLength;
	}
}

void VirtualKeyboard::DrawColorBox(INT iX, INT iY, INT iW, INT iH, unsigned char A, unsigned char R, unsigned char G, unsigned char B)
{
	// 직교 행렬에 위치할 4각형을 설정한다.
	GLshort Vertexcrood[12] = { iX, iY, 0,
		iX + iW, iY, 0,
		iX, iY + iH, 0,
		iX + iW, iY + iH, 0 };
	// 사용자 정의 색을 입력해준다.
	GLubyte colorArray[16] = {	R, G, B, A,
		R, G, B, A,
		R, G, B, A,
		R, G, B, A	};


	// 원하는 좌표로 이동시킨다.
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();

	// 알파 블랜딩을 위한 설정
	if(A!= 255)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	} else
	{
		glDisable(GL_BLEND);
	}

	// 정점 버퍼를 설정한다.
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_SHORT, 0, Vertexcrood);

	// 사용자 정의 알파값을 위한 칼라 버퍼 설정
	glEnableClientState(GL_COLOR_ARRAY);
	glColorPointer(4, GL_UNSIGNED_BYTE, 0, colorArray);

	// 출력한다. 속도를 위하여 GL_TRIANGLE_STRIP를 사용한다.
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	// 해제 코드.
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisable(GL_BLEND);
}






// Create VKB
INT DGT_CreateVKB(char* sCmd
					, PDGT_VKB* pData
					, DGE_HANDLE p1			// IDGE_Device*
					, DGE_HANDLE p2			// No Use
					, DGE_HANDLE p3			// No Use
					, DGE_HANDLE p4			// No Use
					 )
{
	VirtualKeyboard* pObj = NULL;
	*pData		= NULL;

	pObj = new VirtualKeyboard;

	if(DGE_FAILED(pObj->Create(p1, p2, p3, p4)))
	{
		delete pObj;
		return DGE_ECANNOTALLOCATED;
	}

	*pData = pObj;
	return DGE_OK;
}


INT DGT_DestroyVKB(PDGT_VKB* pData)
{
	if(NULL == *pData)
		return DGE_OK;

	delete *pData;
	(*pData) = NULL;

	return DGE_OK;
}




