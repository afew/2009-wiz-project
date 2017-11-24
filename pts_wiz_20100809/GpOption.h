//
//
////////////////////////////////////////////////////////////////////////////////

#ifndef __GpOption_H__
#define __GpOption_H__

enum
{
	OPTION_IMAGE_MAX = 6,
};

class CGpOption
{
protected:
	int		m_bExit;

	int		m_nMode;		//���ݑI������Ă���?��	�O�F�f?�l�d�r�s?�q�s?�P�F�n�o�s�h�n�m?�Q�F�d�w�h�s
	int		m_nAg;
	int		m_nSelct[15];
	int		m_nBak_scl[64];
	int		m_nBak_count[64];
	int		m_nA[2];
	int		m_nB[2];
	int		m_nTolal_time[5];
	int		m_nTolal_time2[5];
	int		m_nTolal_time3[5];

	PDGE_TEXTURE	m_vTex[OPTION_IMAGE_MAX];	// 125�� ����� �����ϱ� ���� ������ Ÿ��

	PDGX_SOUND		m_pSndSe1;
	PDGX_SOUND		m_pSndBg;


public:
	CGpOption();
	virtual ~CGpOption();

	int		Init();
	void	Destroy();
	int		Update();
	void	Render();

protected:
	void option_init_save_data();
	void option_kane_set( int x, int y );
	void option_kane_disp();
	void option_k_jmp( int i );
};


#endif

