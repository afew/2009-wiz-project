//
//
////////////////////////////////////////////////////////////////////////////////

#ifndef __GpDemo_H__
#define __GpDemo_H__


// by Rupaus
enum
{
	DEMO_IMAGE_MAX = 40,
};


class CGpDemo
{
protected:
	int				m_bExit;
	int				m_nDemo;

	PDGE_TEXTURE	m_vTex[2];

	TFadeTex		m_vBgt[ DEMO_IMAGE_MAX ];
	TFadeTex		m_vMst[ DEMO_IMAGE_MAX ];

	int				m_iDemoProcess;
	int				m_iDemoProcessSub;
	int				m_iDemoTimeCounter;
	int				m_iDemoAlphaCounter;
	int				m_aiDemoAlphaCounter [ 8 ];

public:
	CGpDemo();
	virtual ~CGpDemo();

	int		Init();
	void	Destroy();
	int		Update();
	void	Render();
};


#endif



