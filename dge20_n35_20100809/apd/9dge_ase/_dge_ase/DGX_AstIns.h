// Interface for the CDGX_AstIns class.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _DGX_AstIns_H_
#define _DGX_AstIns_H_


#include <vector>


class CDGX_AstIns : public IDGX_Mdl
{
public:
	struct TlinkTm
	{
		DGXMATRIX	mtW		;		// World Matrix
		DGXMATRIX	mtL		;		// Local Matrix
		INT			nPrn	;		// Parent Node Index

		TlinkTm();
	};

protected:
	PDGE_DEVICE		m_pDev		;
	CDGX_Ast*		m_pOrg		;		// Original ASE Model Pointer

	INT				m_nFrmF		;		// First Frame
	INT				m_nFrmL		;		// Last Frame
	INT				m_nFrmS		;		// Frame Speed
	INT				m_nFrmT		;		// Tick per Frame

	INT					m_nMtl	;		// copy from Original
	CDGX_Ast::AseMtl*	m_pMtl	;
	INT					m_nGeo	;		// copy from Original
	CDGX_Ast::AseGeo*	m_pGeo	;


	DOUBLE			m_dFrmCur	;		// Current Frame
	DOUBLE			m_dTimeCur	;		// Current Time
	INT				m_dFrmBgn	;		// Animation Begin Frame
	INT				m_dFrmEnd	;		// Animation End Frame
	DGXMATRIX		m_mtWld		;		// World Matrix
	TlinkTm*		m_pTM		;		// World and Animation Matrix


public:
	CDGX_AstIns();
	virtual ~CDGX_AstIns();

	virtual INT		Create(void* p1=0, void* p2=0, void* p3=0, void* p4=0);
	virtual void	Destroy();

	virtual INT		FrameMove();
	virtual void	Render();

	virtual INT		SetAttrib(DWORD dCmd, void* pData);
	virtual INT		GetAttrib(DWORD dCmd, void* pData);
};


#endif



