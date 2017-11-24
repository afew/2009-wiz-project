//
//
////////////////////////////////////////////////////////////////////////////////

#ifndef __GpAct_H__
#define __GpAct_H__

class CGpAct
{
protected:
	int				m_bExit;
	int				m_nSn;					// 뤾뽋뾭빾릶궞귢귩빾궑귡궞궴궸귝궯궲?됪듫릶볙궻룉뿚귩빾궑귡

public:
	PDGE_TEXTURE	m_vTex[BMPBUFF_MAX];	// 125는 장면을 저장하기 위한 렌더링 타겟

	PDGX_SOUND		m_pSndSe[EN_SE_END];
	PDGX_SOUND		m_pSndBg;				// Background Sound
	int				m_nSndBg;

	int				m_bDemo;

public:
	CGpAct();
	virtual ~CGpAct();

	int		Init();
	void	Destroy();

	int		Update();
	void	Render();
	void	ReleseTexture();
	void	ReleseSound();

	void	Loading(int n);

protected:
	void act_keys();
	void fram_set();
	void jmp_st();
	void jmp();
	void idou_l();
	void idou_r();

	void save_file_w();
	void save_file();
	void clear_save_file();
	void playerdisp();
	void bg_disp();
	void bakdisp1();
	void bakdisp2();
	void bak_rot();
	void wait_scl( long type, long d_num );
	void wait_scl2( long d_num ,long init_x, long init_y );
	void wait_scl3();
	void snack_counter_disp();
	void minimap_disp();
	void mapdisp();
	void se_wav(long SeWavNo);
	void stage_start();
	void stage_endj();
	void stage_claer();
	void stage_end();
	void end_scl( long s_num );
	void p_shot_set( long type , long muki, long houkou );
	void p_shot_disp();
	void p_shot_f_set( long x, long y , long type );
	void p_shot_f_disp();
	void p_shot_f2_set( long x, long y , long muki );
	void p_shot_f2_disp();
	void item_set( long type, long x, long y, long iti, long g_num );
	long item_sonzai( long map1, long map2 );
	void item_disp();
	void item_jmp( int i );
	void item_line();
	long item_up_Isitem( long item_index );
	long item_up();
	long item_up2();
	long item_event();
	void init_event_set_enm( long event_no , long b_num );
	void init_event_set( long event_no , long b_num );
	void event_set( long event_no , long b_num );
	void event_set_enm( long event_no , long b_num );
	void event_disp();
	void event_save();
	void load_save_file();
	void event_kaihuku();
	void event_return();
	void event_warp();
	void enm_set( long type, long x, long y );
	void enm_set2( long type, long x, long y ,long muki );
	long e_hp( long type );
	void enm_disp();
	void e_move( long i );
	void e_shot_disp();
	void enmjmp( long i );
	long map1_item_j( long x, long y );
	long map1_item_j_Isitem( long x, long y, long item_index );
	void kane_set( long x, long y );
	void kane_disp(  );
	void k_jmp( long i );
	void p_jump_f_set( long x, long y );
	void p_jump_f_disp();
	void screen_BackupPlane();
	void window_disp();
	void window_keys();
	long labs( long para );
	void p_mgc_set( long muki , long p3 );
	void p_mgc_disp();
	void BlendExBltRectW( long plane_no, long x, long y, long sx, long sy, long hx, long hy, long func, long blend );
	void BlendExBltW( long plane_no, long x, long y, long func, long blend );
	void BlendExBltFastW( long plane_no, long x, long y, long func, long blend );
	void replay_input_save();
	void replay_input_load();
	void replay_file_save_w();
	void replay_file_save( long type );
	long replay_file_load();
	long GetKyori( long i1, long i2 );
	void rotmap( long rot );
	void rotchangemap( long x1, long y1, long deg, long *x2, long *y2 );
	void rotchange( long x1, long y1, long deg, long *x2, long *y2 );
	void debugdisp();
	void mapview_keys();

};


#endif



