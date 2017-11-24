/********************************************************************************

			Copyright(C) Gamepark Holdings. All rights reserved.
							Dogma-G Game Studios
							In-House Library DGE


						C++ compiler support with SDL
							(gcc-4.0.2-glibc-2.3.6)
							# not included SDL #

********************************************************************************/
#ifndef __AUTOMATA_H__
#define __AUTOMATA_H__


/* table_for_3 에서 사용될 flag: int type이 32bit 이상이어야 함 */
/* F_WC: wide character는 반드시 2바이트 조합형 코드(KSSM)로 표기해야 함 */
#define	F_F	0x010000                /* 초성 */
#define F_M	0x020000                /* 중성 */
#define F_L	0x040000                /* 종성 */
#define F_A	0x080000                /* ASCII */
#define F_WC    0x100000                /* wide(2 byte) character */


/* table_for_2 에서 사용될 flag */
#define	F_C_F	0x010000U		/* 자음 - 초성전용 */
#define F_C_L	0x020000U		/* 자음 - 종성: 종성전용 자음은 없음 */
#define F_C_C	0x030000U		/* 자음 - 초, 종성 겸용 */
#define F_V		0x040000U		/* 모음 */
/* ASCII문자는 공통으로 쓰임 */

/*(영문 입력) -> 완성형 코드 문자열
c : 영문 ASCII
-1 : 한영 toggle
-2 : 현재 구성중인 한글을 돌려 준다. flush.
buf : 완성된 글자의 KS C 5601 - 1992 코드
결과: buf 에 몇 바이트나 들어 갔는가
외부 참조: display_temp() : 현재 구성중인 한글을 화면에 그려 준다.
term->screen.keyboard : 자판 결정. 2 = 2벌식, 3 = 3벌식
term->screen.use_dvorak_layout : 영문자판배열. False = qwerty, True = dvorak
convert_3_to_ks() : 조합->완성 변환. 변환된 후 문자열 길이를
돌려 줘야 한다. 2 또는 8
show_status() : 한글 상태 인지 영문 상태인지 표시한다.
*/

#define push(x)	(stack[sp++] =(x))
#define pop()	(stack[--sp])

class Automata
{
public:
	Automata();
	~Automata();
	void GetHangul(unsigned char *szInputBuffer, unsigned char *szOutputBuffer);

private:
	int In_KS(int f, int m, int t);
	int Convert_3_to_KS(unsigned char f, unsigned char m, unsigned char l, unsigned char *des);

	int fcon(int c);
	int vow(int c);
	int lcon(int c);

	int comcon_qwerty(int k, int c);
	int comvow_qwerty(int v, int c);

	static unsigned char m_KSTABLE1[2350][3];
	static unsigned short m_KSTABLE2[40][4];
	static unsigned int m_Table_for_2_qwerty[];

	int m_iAutomataIsConvertRight;
};


#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

class FuntionKey
{
public:
	FuntionKey();
	~FuntionKey();
	// not pushed
	void SetNPRect(int x, int y, int w, int h);
	// pushed
	void SetPRect(int x, int y, int w, int h);
	void ChangePushed();
	int GetPushed();
	void SetPickArea(int x, int y, int w, int h);
	int CheckInner(int x, int y);
	void SetStatePtr(int* v);

	int		m_PickArea[4];
	int*	m_pPushed;
	float	m_KeyRect[2][4];
};

class KeyNode
{
public:
	KeyNode();
	~KeyNode();
	void SetKorShiftCode(int v);
	// 특수 문자 셋팅
	void SetSpecial(int v);
	void SetSpecialShift(int v);


	// 키의 코드를 입력한다.(한글 영문 상관없이 영어만 입력한다)
	void SetCodeNoShift(int Code);

	// shift 상태의 코드를 입력한다.(한글 영문 상관없이 영어만 입력한다)
	void SetCodeShift(int Code);

	// 피킹을 위한 위치와 너비 높이를 정의한다 이값은 드로잉시에 영향을 준다.
	void SetPickArea(int x, int y, int w, int h);
	// 각 상태별 텍스쳐의 rect값을 설정해준다.
	void SetRectNPEng(int x, int y, int w, int h);
	void SetRectNPEngShift(int x, int y, int w, int h);
	void SetRectNPKor(int x, int y, int w, int h);
	void SetRectNPKorShift(int x, int y, int w, int h);
	void SetRectPEng(int x, int y, int w, int h);
	void SetRectPEngShift(int x, int y, int w, int h);
	void SetRectPKor(int x, int y, int w, int h);
	void SetRectPKorShift(int x, int y, int w, int h);
	int CheckInner(int x, int y);

	// 1차원[0] = No push[1] = push
	// 2차원[0] = Eng Shift off,[1] = Eng Shift on[2] = Kor Shift off[3] = Kor Shift on
	// 3차원[0] = x,[1] = y,[2] = w,[3] = h 순임
	float m_KeyRect[2][4][4];
	// 키노드가 가지고 있는 문자 코드
	//[0] = Shift off,[1] = Shift on
	char m_Code[2];
	// x, y, w, h순
	int m_PickArea[4];
	// 눌린 상태 표현
	int m_iPushed;
	// 특수문자 표시
	int m_bSpecial[2];
	// 한글입력시 영문 대문자 무시 코드
	int m_bKorShiftCode;
};

#endif
