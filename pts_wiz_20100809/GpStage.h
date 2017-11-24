//
//
////////////////////////////////////////////////////////////////////////////////

#ifndef __GpStage_H__
#define __GpStage_H__


enum
{
	STAGE_IMAGE_MAX = 6,
};

class CGpStage
{
protected:
	int		m_bExit;

	int		m_nMode;
	int		m_nA[2];
	int		m_nCsl[2];

	long	m_nTarget_save[1024];

	PDGE_TEXTURE	m_vTex[STAGE_IMAGE_MAX];	// 125는 장면을 저장하기 위한 렌더링 타겟


public:
	CGpStage();
	virtual ~CGpStage();

	int		Init();
	void	Destroy();
	int		Update();
	void	Render();

protected:
	void	stageselect_init_save_data();
};


#endif


