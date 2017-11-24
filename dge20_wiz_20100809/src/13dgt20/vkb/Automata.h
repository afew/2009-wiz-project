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


/* table_for_3 ���� ���� flag: int type�� 32bit �̻��̾�� �� */
/* F_WC: wide character�� �ݵ�� 2����Ʈ ������ �ڵ�(KSSM)�� ǥ���ؾ� �� */
#define	F_F	0x010000                /* �ʼ� */
#define F_M	0x020000                /* �߼� */
#define F_L	0x040000                /* ���� */
#define F_A	0x080000                /* ASCII */
#define F_WC    0x100000                /* wide(2 byte) character */


/* table_for_2 ���� ���� flag */
#define	F_C_F	0x010000U		/* ���� - �ʼ����� */
#define F_C_L	0x020000U		/* ���� - ����: �������� ������ ���� */
#define F_C_C	0x030000U		/* ���� - ��, ���� ��� */
#define F_V		0x040000U		/* ���� */
/* ASCII���ڴ� �������� ���� */

/*(���� �Է�) -> �ϼ��� �ڵ� ���ڿ�
c : ���� ASCII
-1 : �ѿ� toggle
-2 : ���� �������� �ѱ��� ���� �ش�. flush.
buf : �ϼ��� ������ KS C 5601 - 1992 �ڵ�
���: buf �� �� ����Ʈ�� ��� ���°�
�ܺ� ����: display_temp() : ���� �������� �ѱ��� ȭ�鿡 �׷� �ش�.
term->screen.keyboard : ���� ����. 2 = 2����, 3 = 3����
term->screen.use_dvorak_layout : �������ǹ迭. False = qwerty, True = dvorak
convert_3_to_ks() : ����->�ϼ� ��ȯ. ��ȯ�� �� ���ڿ� ���̸�
���� ��� �Ѵ�. 2 �Ǵ� 8
show_status() : �ѱ� ���� ���� ���� �������� ǥ���Ѵ�.
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
	// Ư�� ���� ����
	void SetSpecial(int v);
	void SetSpecialShift(int v);


	// Ű�� �ڵ带 �Է��Ѵ�.(�ѱ� ���� ������� ��� �Է��Ѵ�)
	void SetCodeNoShift(int Code);

	// shift ������ �ڵ带 �Է��Ѵ�.(�ѱ� ���� ������� ��� �Է��Ѵ�)
	void SetCodeShift(int Code);

	// ��ŷ�� ���� ��ġ�� �ʺ� ���̸� �����Ѵ� �̰��� ����׽ÿ� ������ �ش�.
	void SetPickArea(int x, int y, int w, int h);
	// �� ���º� �ؽ����� rect���� �������ش�.
	void SetRectNPEng(int x, int y, int w, int h);
	void SetRectNPEngShift(int x, int y, int w, int h);
	void SetRectNPKor(int x, int y, int w, int h);
	void SetRectNPKorShift(int x, int y, int w, int h);
	void SetRectPEng(int x, int y, int w, int h);
	void SetRectPEngShift(int x, int y, int w, int h);
	void SetRectPKor(int x, int y, int w, int h);
	void SetRectPKorShift(int x, int y, int w, int h);
	int CheckInner(int x, int y);

	// 1����[0] = No push[1] = push
	// 2����[0] = Eng Shift off,[1] = Eng Shift on[2] = Kor Shift off[3] = Kor Shift on
	// 3����[0] = x,[1] = y,[2] = w,[3] = h ����
	float m_KeyRect[2][4][4];
	// Ű��尡 ������ �ִ� ���� �ڵ�
	//[0] = Shift off,[1] = Shift on
	char m_Code[2];
	// x, y, w, h��
	int m_PickArea[4];
	// ���� ���� ǥ��
	int m_iPushed;
	// Ư������ ǥ��
	int m_bSpecial[2];
	// �ѱ��Է½� ���� �빮�� ���� �ڵ�
	int m_bKorShiftCode;
};

#endif
