//
//
////////////////////////////////////////////////////////////////////////////////

#ifndef __GpEnding_H__
#define __GpEnding_H__


// by Rupaus
enum
{
	END_IMAGE_MAX = 32,
};


class CGpEnding
{
protected:
	int			m_bExit;
	int			m_nDemo[10];
	long		m_nTargetSave[1024];

	TFadeTex	m_vBgt[ END_IMAGE_MAX ];
	TFadeTex	m_vMst[ END_IMAGE_MAX ];

	int			m_iEndProcess;
	int			m_iEndProcessSub;
	int			m_iEndTimeCounter;
	int			m_iEndAlphaCounter;

	PDGX_SOUND		m_pSndBg;

public:
	CGpEnding();
	virtual ~CGpEnding();

	int		Init();
	void	Destroy();
	int		Update();
	void	Render();
	
protected:
	void ending_init_save_data();
};


#endif


