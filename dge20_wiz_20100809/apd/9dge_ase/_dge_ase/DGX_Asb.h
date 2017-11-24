// Interface for the CDGX_Asb class.
//
////////////////////////////////////////////////////////////////////////////////


#if defined(_WIN32) || defined(WIN32)
	#if _MSC_VER > 1000
	#pragma once
	#endif
#endif


#ifndef _DGX_Asb_H_
#define _DGX_Asb_H_


class CDGX_Asb : public IDGX_Mdl
{
public:

	struct Tmtl
	{
		char			sTex[DGXM_TEXNAME];
		PDGE_TEXTURE	pTex;

		Tmtl();
		~Tmtl();
	};


	// Face: 16-bit Triangle Index Stream
	#if defined(_WIN32) || defined(WIN32)

		#pragma pack(push, 2)
		struct Tidx
		{
			WORD a;	WORD b;	WORD c;
			Tidx() : a(0), b(1), c(2){}
		};
		#pragma pack(pop)

	#else

		typedef struct tagTidx
		{
			WORD a;	WORD b;	WORD c;
			tagTidx() : a(0), b(1), c(2){}
		} __attribute__((packed)) Tidx;

	#endif

	

	struct Tvtx
	{
		DGXVECTOR3	p;
		Tvtx() : p(0,0,0){}
		enum	{FVF = (DGE_FVF_XYZ),};
	};
		
	struct TvtxUV
	{
		DGXVECTOR3	p;
		FLOAT	u, v;

		TvtxUV() : p(0,0,0), u(0),v(0){}
		enum	{FVF = (DGE_FVF_XYZ|DGE_FVF_TEX1),};
	};

	struct Ttrack
	{
		INT		nF;																// Frame
		FLOAT	x;
		FLOAT	y;
		FLOAT	z;
		FLOAT	w;

		Ttrack() : nF(0), x(0), y(0), z(0), w(0){}
	};


	struct Tgeo
	{
		char		sName[32];			// Current Node Name
		INT			nPrn	;			// Parent Index
		INT			nMtl	;			// Material Index

		INT			iFce	;			// Number of Face
		INT			iNvx	;			// Number of Vertex
		Tidx*		pIdx	;			// indexed buffer
		void*		pVtx	;			// vertex buffer
		DWORD		dFVF	;			// Flexible Vertex Format
		DWORD		dVtx	;			// Zero Stride

		DGXMATRIX	mtTmL	;			// Tm Local
		DGXMATRIX	mtW		;			// World Matrix
		DGXMATRIX	mtL		;			// Local Matrix

		INT			nRot	;			// Rotation Number
		INT			nTrs	;			// Translation Number
		Ttrack*		vRot	;			// Rotation
		Ttrack*		vTrs	;			// Translation

		Tgeo();
		~Tgeo();
	};

protected:
	PDGE_DEVICE		m_pDev		;
	char			m_sFile[DGE_MAX_PATH];

	CDGX_Ast::TInfo	m_Info		;

	Tmtl*			m_pMtl		;
	Tgeo*			m_pGeo		;

	DOUBLE			m_dFrmCur	;		// Current Frame
	DOUBLE			m_dTimeCur	;		// Current Time
	INT				m_dFrmBgn	;		// Animation Begin Frame
	INT				m_dFrmEnd	;		// Animation End Frame

	DGXMATRIX		m_mtWld		;		// World Matrix


public:
	CDGX_Asb();
	virtual ~CDGX_Asb();

	virtual INT		Create(void* p1=0, void* p2=0, void* p3=0, void* p4=0);
	virtual void	Destroy();

	virtual INT		FrameMove();
	virtual void	Render();

	virtual INT		SetAttrib(DWORD dCmd, void* pData);
	virtual INT		GetAttrib(DWORD dCmd, void* pData);

public:
	const CDGX_Ast::TInfo* GetInfo() const{	return &m_Info; }

	Tmtl*	GetMtrl()	 const	{	return m_pMtl;	}
	Tgeo*	GetGeometry() const	{	return m_pGeo;	}
	INT		GetAniTrack(void* mtA, INT nGeo, FLOAT dFrame);

	void*	GetDevice()			{	return m_pDev;	}

protected:
	INT		Load();
};



#endif



