// Interface for the CDGX_Ast class.
//
////////////////////////////////////////////////////////////////////////////////


#if defined(_WIN32) || defined(WIN32)
	#if _MSC_VER > 1000
	#pragma once
	#endif
#endif


#ifndef _DGX_Ase_H_
#define _DGX_Ase_H_


#include <vector>
using namespace std;


class CDGX_Ast : public IDGX_Mdl
{
public:
	struct _AseKey
	{
		char	sKey[40];		// String Keword
		INT		iKey;			// String Size
	};

	
	// Face: 16-bit Triangle Index Stream
	#if defined(_WIN32) || defined(WIN32)

		#pragma pack(push, 2)
		struct AseFce
		{
			union{	struct{ WORD a; WORD b; WORD c;}; WORD m[3]; };

			AseFce() : a(0), b(1), c(2){}
			AseFce(WORD A,WORD B,WORD C) : a(A), b(B), c(C){}
			AseFce(const WORD* v)	{ a = v[0]; b = v[1]; c = v[2];	}
		
			operator WORD*()			{	return (WORD*)&a;		}
			operator const WORD*() const{	return (const WORD*)&a;	}

			enum { FVF = (DGE_FMT_INDEX16), };
		};
		#pragma pack(pop)

	#else

		typedef struct tagAseFce
		{
			WORD a;
			WORD b;
			WORD c;

			tagAseFce() : a(0), b(1), c(2){}
			tagAseFce(WORD A,WORD B,WORD C) : a(A), b(B), c(C){}

			operator WORD*()			{	return (WORD*)&a;		}
			operator const WORD*() const{	return (const WORD*)&a;	}

			enum { FVF = (DGE_FMT_INDEX16), };
		} __attribute__((packed)) AseFce;

	#endif


	struct _AsePos
	{
		FLOAT	x, y, z;
		_AsePos() : x(0), y(0), z(0){}
	};


	struct _AseNor
	{
		FLOAT	x, y, z;
		INT		a, b, c;
		_AseNor() : x(0), y(0), z(0), a(0), b(0), c(0){}
	};


	struct _AseTvtx
	{
		INT		nT;						// 배열에서 정점 또는 UV의 인덱스
		FLOAT	u, v, w;				// UVW좌표
		_AseTvtx() :nT(-1), u(0), v(0), w(0){}
	};


	struct AseMtl
	{
		char			sTex[DGE_MAX_PATH];
		PDGE_TEXTURE	pTex;

		AseMtl();
		~AseMtl();
	};


	struct AseVtx
	{
		DGXVECTOR3	p;
		AseVtx() : p(0,0,0){}
		enum	{FVF = (DGE_FVF_XYZ),};
	};
		
//	struct AseVtxN
//	{
//		DGXVECTOR3	p;
//		DGXVECTOR3	n;
//
//		AseVtxN() : p(0,0,0), n(0,0,0){}
//		enum	{FVF = (DGE_FVF_XYZ|DGE_FVF_NORMAL),};
//	};

	struct AseVtxUV
	{
		DGXVECTOR3	p;
		FLOAT	u, v;

		AseVtxUV() : p(0,0,0), u(0),v(0){}
		enum	{FVF = (DGE_FVF_XYZ|DGE_FVF_TEX1),};
	};

//	struct AseVtxNUV
//	{
//		DGXVECTOR3	p;
//		DGXVECTOR3	n;
//		FLOAT	u, v;
//
//		AseVtxNUV() : p(0,0,0), n(0,0,0), u(0),v(0){}
//		enum	{FVF = (DGE_FVF_XYZ|DGE_FVF_NORMAL|DGE_FVF_TEX1),};
//	};


	struct AseTM
	{
		DGXMATRIX	mtW;				// World Matrix
		DGXMATRIX	mtL;				// Local Matirx
		
		FLOAT	Px, Py, Pz;
		FLOAT	Rx, Ry, Rz, Rw;
		FLOAT	Sx, Sy, Sz;

		AseTM() : Px(0), Py(0), Pz(0)
				, Rx(0), Ry(0), Rz(0), Rw(0)
				, Sx(0), Sy(0), Sz(0){}
	};

	
	struct AseTrack
	{
		INT		nF;						// Frame
		FLOAT	x;
		FLOAT	y;
		FLOAT	z;
		FLOAT	w;

		AseTrack() : nF(0), x(0), y(0), z(0), w(0){}
		AseTrack(INT F,FLOAT X,FLOAT Y,FLOAT Z,FLOAT W):nF(F),x(X),y(Y),z(Z),w(W){}
	};


	struct AseGeo
	{
		char		sNodeCur[32];		// Current Node Name
		char		sNodePrn[32];		// Parent Node Name
		INT			nNodePrn;			// Parent Index

		INT			nMtlRef	;			// Material Index

		// for ASE Parsing
		INT			iNumVtx	;			// Number of Vertex
		INT			iNumFce	;			// Number of Index

		INT			iNumTvtx;			// Number of Vertex
		INT			iNumTfce;			// Number of Index

		_AsePos*	pLstVtx	;			// Vertex List
//		_AseNor*	pLstNor	;			// Normal List
		AseFce*		pLstFce	;			// Vertex Face List
		_AseTvtx*	pLstTvtx;			// UV List
		AseFce*		pLstTfce;			// UV Face

		AseGeo*			pGeoPrn;
		AseTM			TmInf;			// Transform and Movement
		vector<AseTrack > vRot;			// Rotation
		vector<AseTrack > vTrs;			// Translation
		vector<AseTrack > vScl;			// Scaling

		
		// Final Rendering Geometry Info
		DGXMATRIX	mtW		;			// World Matrix
		DGXMATRIX	mtL		;			// Local Matrix
		INT			m_iFce	;			// Number of Face
		INT			m_iNvx	;			// Number of Vertex
		AseFce*		m_pIdx	;			// for indexed buffer
		void*		m_pVtx	;			// for vertex buffer
		DWORD		m_dFVF	;
		DWORD		m_dVtx	;			// Zero Stride

		AseGeo();
		~AseGeo();
	};


	struct TInfo
	{
		char	sVer[16];				// For Converting Binary version
		INT		nFrmF	;				// First Frame
		INT		nFrmL	;				// Last Frame
		INT		nFrmS	;				// Frame Speed Per one scecond
		INT		nFrmT	;				// Tick per one Frame

		INT		nMtl	;				// Number of Material
		INT		nGeo	;				// Number of Geometry

		TInfo():nFrmF(0),nFrmL(0),nFrmS(0),nFrmT(0), nMtl(0),nGeo(0)
		{
			memset(sVer, 0, sizeof sVer);
			strcpy(sVer, "LcAsm00.01");
		}
	};


protected:
	char			m_sFile[DGE_MAX_PATH];

	PDGE_DEVICE		m_pDev		;

	CDGX_Ast::TInfo	m_Info		;
	AseMtl*			m_pMtl		;
	AseGeo*			m_pGeo		;

	DOUBLE			m_dFrmCur	;		// Current Frame
	DOUBLE			m_dTimeCur	;		// Current Time
	INT				m_dFrmBgn	;		// Animation Begin Frame
	INT				m_dFrmEnd	;		// Animation End Frame
	DGXMATRIX		m_mtWld		;		// World Matrix


public:
	CDGX_Ast();
	virtual ~CDGX_Ast();

	virtual INT		Create(void* =NULL, void* =NULL, void* =NULL, void* =NULL);
	virtual void	Destroy();

	virtual INT		FrameMove();
	virtual void	Render();

	virtual INT		SetAttrib(DWORD dCmd, void* pData);
	virtual INT		GetAttrib(DWORD dCmd, void* pData);

public:
	const CDGX_Ast::TInfo* GetInfo() const{	return &m_Info;	}
	AseMtl*	GetMtrl()	 const	{	return m_pMtl;	}
	AseGeo*	GetGeometry() const	{	return m_pGeo;	}
	INT		GetAniTrack(void* mtA, INT nGeo, FLOAT dFrame);
	void*	GetDevice()			{	return m_pDev;	}

protected:
	void	Confirm();

	INT		GetNumVtx(INT nGeo);
	INT		GetNumFce(INT nGeo);

	void*	GetPtVtx(INT nGeo);
	void*	GetPtFce(INT nGeo);

	INT		Load();
	INT		ParseScene(FILE* fp);
	INT		ParseMaterial(FILE* fp);
	INT		ParseGeometry(FILE* fp);
	INT		ParseAnimation(FILE* fp);

	INT		SetupRenderData();

protected:
	void	SaveToAsmBin();
	void	SaveToAsmTxt();
};


#endif


