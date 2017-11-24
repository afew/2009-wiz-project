//
//
////////////////////////////////////////////////////////////////////////////////

#ifndef __GpLogo_H__
#define __GpLogo_H__

class CGpLogo
{
protected:
	int				m_bExit;
	int				m_nDemo;
	PDGE_TEXTURE	m_pTex;

	int				m_dTimeBgn;
	int				m_dAlpVal;
	int				m_dAlpDir;

public:
	CGpLogo();
	virtual ~CGpLogo();

	int		Init();
	void	Destroy();
	int		Update();
	void	Render();

protected:
	void	logo_init_save_data();
};

#endif


