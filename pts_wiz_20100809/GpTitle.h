//
//
////////////////////////////////////////////////////////////////////////////////

#ifndef __GpTitle_H__
#define __GpTitle_H__

class CGpTitle
{
protected:
	int		m_bExit;
	int		m_nMode;					//Œ»İ‘I‘ğ‚³‚ê‚Ä‚¢‚é?–Ú	‚OF‚f?‚l‚d‚r‚s?‚q‚s?‚PF‚n‚o‚s‚h‚n‚m?‚QF‚d‚w‚h‚s
	int		m_nA[2];
	int		m_nB[2];
	int		m_nCaslanm ;
	int		m_nKane[200];				/* ƒAƒCƒe?—pƒoƒbƒt? */
	int		m_nUracount;

	int		m_nTitle;

	PDGE_TEXTURE	m_vTex[BMPBUFF_MAX];


public:
	CGpTitle();
	virtual ~CGpTitle();

	int		Init();
	void	Destroy();
	int		Update();
	void	Render();

	void	ReleseTexture();


protected:
	void title_init_save_data();
	void title_kane_set( int x, int y );
	void title_kane_disp();
	void title_k_jmp( int i );

	int replay_file_find();
	int replay_file_find2();
};


#endif


