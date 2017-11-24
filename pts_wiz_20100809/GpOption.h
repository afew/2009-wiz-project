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

	int		m_nMode;		//뙸띪멗묖궠귢궲궋귡?뽞	괥갌괽?굃괺굍굎?굌굎?괦갌굈굊굎괿굈굆?괧갌괺굓괿굎
	int		m_nAg;
	int		m_nSelct[15];
	int		m_nBak_scl[64];
	int		m_nBak_count[64];
	int		m_nA[2];
	int		m_nB[2];
	int		m_nTolal_time[5];
	int		m_nTolal_time2[5];
	int		m_nTolal_time3[5];

	PDGE_TEXTURE	m_vTex[OPTION_IMAGE_MAX];	// 125는 장면을 저장하기 위한 렌더링 타겟

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

