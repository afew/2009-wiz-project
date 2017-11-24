// Implementation of the CDGX_AsbIns class.
//
////////////////////////////////////////////////////////////////////////////////


#if defined(_WIN32) || defined(WIN32)
	#if _MSC_VER >= 1200
	#pragma warning(disable: 4996)
	#endif
#endif
	

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <DGE_Type.h>
#include <DGE_System.h>
#include <DGE_Util.h>
#include <DGE_Math.h>
#include <DGE_Base.h>

#include "../DGX_Mdl.h"
#include "DGX_Ast.h"
#include "DGX_Asb.h"
#include "DGX_AsbIns.h"


CDGX_AsbIns::TlinkTm::TlinkTm()
{
	nPrn	= -1;

	mtW.Identity();
	mtL.Identity();
}


CDGX_AsbIns::CDGX_AsbIns()
{
	m_pDev	= NULL;

	m_nMtl	= 0;
	m_pMtl	= NULL;
	m_nGeo	= 0;
	m_pGeo	= NULL;

	m_pOrg	= NULL;


	m_nFrmF	= 0;
	m_nFrmL	= 0;
	m_nFrmS	= 0;
	m_nFrmT	= 0;

	m_dFrmCur = 0;
	m_dTimeCur= 0;
	m_dFrmBgn = 0;
	m_dFrmEnd = 0;

	m_mtWld.Identity();
}

CDGX_AsbIns::~CDGX_AsbIns()
{
	Destroy();
}


INT CDGX_AsbIns::Create(void* p1, void* p2, void* p3, void* p4)
{
	CDGX_Ast::TInfo*	pInfo;
	m_pOrg	= (CDGX_Asb*)p1;

	pInfo	= (CDGX_Ast::TInfo*)m_pOrg->GetInfo();


	m_nFrmF	= pInfo->nFrmF;		// First Frame
	m_nFrmL	= pInfo->nFrmL;		// Last Frame
	m_nFrmS	= pInfo->nFrmS;		// Frame Speed
	m_nFrmT	= pInfo->nFrmT;		// Tick per Frame

	m_dFrmBgn = m_nFrmF;		// 애니메이션 루프의 시작 프레임
	m_dFrmEnd = m_nFrmL;		// 애니메이션 루프의 마지막 프레임
	
	m_nMtl	= pInfo->nMtl;
	m_nGeo	= pInfo->nGeo;

	m_pDev	= (PDGE_DEVICE)m_pOrg->GetDevice();
	m_pMtl	= m_pOrg->GetMtrl();
	m_pGeo	= m_pOrg->GetGeometry();


	m_pTM = new TlinkTm[m_nGeo]	;	// World and Animation Matrix


	// Original의 데이터 복사
	for(INT i=0; i<m_nGeo; ++i)
	{
		m_pTM[i].mtL = m_pGeo[i].mtL;
		m_pTM[i].mtW = m_pGeo[i].mtW;

		m_pTM[i].nPrn= m_pGeo[i].nPrn;
	}

	return DGE_OK;
}


void CDGX_AsbIns::Destroy()
{
	m_pOrg = NULL;

	SAFE_DELETE_ARRAY(	m_pTM	);
}






INT CDGX_AsbIns::FrameMove()
{
	INT		i = 0;
	INT		nFrame	=0;

	// Frame = FrameSpeed * Time;
	m_dFrmCur = m_nFrmS * m_dTimeCur;

	nFrame	= INT(m_dFrmCur);

	if(nFrame>= m_nFrmL)
	{
		// 나머지 시간을 현재시간으로 설정한다.
		m_dTimeCur = m_dFrmCur - nFrame;
	}

	for(i=0; i<m_nGeo; ++i)
	{
		TlinkTm*	pTM = &m_pTM[i];
		
		m_pOrg->GetAniTrack(&pTM->mtL, i, m_dFrmCur);

		// 부모의 월드 행렬을 곱해 자신의 월드 행렬을 완성한다.
		DGXMATRIX	mtPrn =DGXMATRIX(1,0,0,0,  0,1,0,0,  0,0,1,0,  0,0,0,1);

		if(0 <= pTM->nPrn)
			mtPrn	= m_pTM[pTM->nPrn].mtW;

		pTM->mtW = pTM->mtL * mtPrn;
	}


	return DGE_OK;
}




void CDGX_AsbIns::Render()
{
	if(!m_pGeo)
		return;

	INT			i=0;
	DGXMATRIX	mtW;


	for(i=0; i<m_nGeo; ++i)
	{
		CDGX_Asb::Tgeo*		pGeo = &m_pGeo[i];

		if(NULL == pGeo->pVtx)
			continue;

		PDGE_TEXTURE pTx=NULL;

		if(0 <= pGeo->nMtl)
			pTx = m_pMtl[pGeo->nMtl].pTex;
		
		if(NULL == pTx)
			continue;


		mtW = m_pTM[i].mtW * m_mtWld;

		m_pDev->SetTexture(0, pTx);

		m_pDev->SetTransform(DGE_TS_WORLD, &mtW);
		m_pDev->SetFVF(pGeo->dFVF);
		m_pDev->DrawIndexedPrimitiveUPf(DGE_PT_TRIANGLE_LIST, pGeo->iFce*3, pGeo->pIdx, pGeo->pVtx, pGeo->dVtx);

		m_pDev->SetTexture(0, 0);
	}

	m_pDev->SetTransformIdentity(DGE_TS_WORLD);
}




INT CDGX_AsbIns::SetAttrib(DWORD dCmd, void* pData)
{
	if( dCmd == DGXM_ADVANCE_TIME)
	{
		DOUBLE fElapsedTime = *((DOUBLE*)pData);

		m_dTimeCur += fElapsedTime;

		// 만약 더한 시간이 마지막 프레임 시간 보다 크거나 시작 프레임보다 작으면
		// 시간을 시작 프레임 시간으로 설정
		INT	 nFrame	= INT(m_nFrmS * m_dTimeCur);
		if( nFrame>= (m_dFrmEnd+1)  ||nFrame< (m_dFrmBgn))
			m_dTimeCur = DOUBLE(m_dFrmBgn+0.00001)/DOUBLE(m_nFrmS+0.0000001);

		return DGE_OK;
	}

	else if( dCmd == DGXM_WORLD_MATRIX)
	{
		DGXMATRIX* pTM = (DGXMATRIX*)pData;

		m_mtWld	= *pTM;
		return DGE_OK;
	}

	else if( dCmd == DGXM_LOOP_SECTION)
	{
		struct _TT { INT B; INT E; } *t =(_TT*)pData;

		m_dFrmBgn = t->B;
		m_dFrmEnd = t->E;

		if(m_dFrmBgn < m_nFrmF)		m_dFrmBgn = m_nFrmF;
		if(m_dFrmBgn > m_nFrmL)		m_dFrmBgn = m_nFrmL;

		if(m_dFrmEnd < m_dFrmBgn)	m_dFrmEnd = m_dFrmBgn;
		if(m_dFrmEnd > m_nFrmL)		m_dFrmEnd = m_nFrmL;

		return DGE_OK;
	}

	return DGE_EFAIL;
}


INT CDGX_AsbIns::GetAttrib(DWORD dCmd, void* pData)
{
	if( dCmd == DGXM_CURRENT_TIME)
	{
		*((DOUBLE*)pData) = m_dTimeCur;
		return DGE_OK;
	}
	else if( dCmd == DGXM_WORLD_MATRIX)
	{
		*((DGXMATRIX*)pData) = m_mtWld;
		return DGE_OK;
	}
	else if( dCmd == DGXM_WORLD_MATRIX_POINTER)
	{
		*((DGXMATRIX**)pData) = &m_mtWld;
		return DGE_OK;
	}
	else if( dCmd == DGXM_LOOP_SECTION)
	{
		struct _TT { INT B; INT E; } t = {m_dFrmBgn, m_dFrmEnd};
		*((_TT*)pData) = t;
		return DGE_OK;
	}
	
	return DGE_EFAIL;
}

