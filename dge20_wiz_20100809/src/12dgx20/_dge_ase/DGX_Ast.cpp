// Implementation of the CDGX_Ast class.
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


#define MAX_PARSE_LINE	512


CDGX_Ast::CDGX_Ast()
{
	m_pDev	= NULL;

	m_pMtl	= NULL;
	m_pGeo	= NULL;

	m_dFrmCur = 0;
	m_dTimeCur= 0;
	m_dFrmBgn = 0;
	m_dFrmEnd = 0;

	m_mtWld.Identity();
}


CDGX_Ast::~CDGX_Ast()
{
	Destroy();
}


INT CDGX_Ast::Create(void* p1, void* p2, void* p3, void* p4)
{
	m_pDev = (PDGE_DEVICE)p1;

	strcpy(m_sFile, (char*)p2);

	if(DGE_FAILED(Load()))
	{
		printf("Err: %d, %s \t", __LINE__, __FILE__);
		printf("Cannot Read Model.\n");
		return DGE_ECANNOTFIND_RESOURCE;
	}


	if(DGE_FAILED(SetupRenderData()))
	{
		printf("Err: %d, %s \t", __LINE__, __FILE__);
		printf("Cannot Setup Rendering Data.\n");
		return DGE_ECANNOTALLOCATED;
	}
	

#if defined(_WIN32) || defined(WIN32)
	Confirm();

	SaveToAsmBin();
	SaveToAsmTxt();
#endif


	m_dFrmBgn = m_Info.nFrmF;		// 애니메이션 루프의 시작 프레임
	m_dFrmEnd = m_Info.nFrmL;		// 애니메이션 루프의 마지막 프레임

	return DGE_OK;
}


void CDGX_Ast::Destroy()
{
	SAFE_DELETE_ARRAY(	m_pGeo	);
	SAFE_DELETE_ARRAY(	m_pMtl	);
}



INT CDGX_Ast::FrameMove()
{
	INT		i = 0;
	INT		nFrame	=0;

	// Frame = FrameSpeed * Time;
	m_dFrmCur = m_Info.nFrmS * m_dTimeCur;

	nFrame	= INT(m_dFrmCur);

	if(nFrame>= m_Info.nFrmL)
	{
		// 나머지 시간을 현재시간으로 설정한다.
		m_dTimeCur = m_dFrmCur - nFrame;
	}

	for(i=0; i<m_Info.nGeo; ++i)
	{
		AseGeo*		pGeo = &m_pGeo[i];
		
		this->GetAniTrack(&pGeo->mtL, i, m_dFrmCur);

		// 부모의 월드 행렬을 곱해 자신의 월드 행렬을 완성한다.
		DGXMATRIX	mtPrn =DGXMATRIX(1,0,0,0,  0,1,0,0,  0,0,1,0,  0,0,0,1);
	
		if(0 <= pGeo->nNodePrn)
			mtPrn	= m_pGeo[pGeo->nNodePrn].mtW;

		pGeo->mtW = pGeo->mtL * mtPrn;
	}

	return DGE_OK;
}




void CDGX_Ast::Render()
{
	if(!m_pGeo)
		return;

	INT			i=0;
	DGXMATRIX	mtW;


	for(i=0; i<m_Info.nGeo; ++i)
	{
		AseGeo*		pGeo = &m_pGeo[i];

		if(NULL == pGeo->m_pVtx)
			continue;

		PDGE_TEXTURE pTx=NULL;

		if(pGeo->nMtlRef>=0)
			pTx = m_pMtl[pGeo->nMtlRef].pTex;
		
		if(NULL == pTx)
			continue;


		mtW = pGeo->mtW * m_mtWld;

		m_pDev->SetTexture(0, pTx);

		m_pDev->SetTransform(DGE_TS_WORLD, &mtW);
		m_pDev->SetFVF(pGeo->m_dFVF);
		m_pDev->DrawIndexedPrimitiveUPf(DGE_PT_TRIANGLE_LIST, pGeo->m_iFce*3, pGeo->m_pIdx, pGeo->m_pVtx, pGeo->m_dVtx);

		m_pDev->SetTexture(0, 0);
	}

	m_pDev->SetTransformIdentity(DGE_TS_WORLD);
}


INT CDGX_Ast::SetAttrib(DWORD dCmd, void* pData)
{
	INT hr = DGE_OK;
	
	if( dCmd == DGXM_ADVANCE_TIME)
	{
		DOUBLE fElapsedTime = *((DOUBLE*)pData);

		m_dTimeCur += fElapsedTime;

		// 만약 더한 시간이 마지막 프레임 시간 보다 크거나 시작 프레임보다 작으면
		// 시간을 시작 프레임 시간으로 설정
		INT	 nFrame	= INT(m_Info.nFrmS * m_dTimeCur);
		if( nFrame>= (m_dFrmEnd+1)  ||nFrame< (m_dFrmBgn))
			m_dTimeCur = DOUBLE(m_dFrmBgn+0.00001)/DOUBLE(m_Info.nFrmS+0.0000001);

		return DGE_OK;
	}

	else if( dCmd == DGXM_CURRENT_TIME)
	{
		DOUBLE fTime = *((DOUBLE*)pData);
		m_dTimeCur = fTime;
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

		if(m_dFrmBgn < m_Info.nFrmF)	m_dFrmBgn = m_Info.nFrmF;
		if(m_dFrmBgn > m_Info.nFrmL)	m_dFrmBgn = m_Info.nFrmL;

		if(m_dFrmEnd < m_dFrmBgn)		m_dFrmEnd = m_dFrmBgn;
		if(m_dFrmEnd > m_Info.nFrmL)	m_dFrmEnd = m_Info.nFrmL;

		return DGE_OK;
	}

	else if( dCmd == DGXM_EXEC_TEXTURE_LOAD)
	{
		DWORD ColorKey = *(DWORD*)pData;
		hr = LoadTextureList(ColorKey);
		return hr;
	}


	return DGE_EFAIL;
}


INT CDGX_Ast::GetAttrib(DWORD dCmd, void* pData)
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
	else if( dCmd == DGXM_WORLD_MATRIX_PT)
	{
		*((DGXMATRIX**)pData) = &m_mtWld;
		return DGE_OK;
	}

	else if( dCmd == DGXM_GEOMETRY_MATRIX)
	{
		struct _TT { INT n;	DGXMATRIX mtT; } *t = (_TT*)pData;
		INT		n = t->n;

		if(n<0 || n>=this->m_Info.nGeo)
			return DGE_ECANNOTFIND_RESOURCE;

		t->mtT = m_pGeo[n].mtW;
		return DGE_OK;
	}
	else if( dCmd == DGXM_GEOMETRY_MATRIX_PT)
	{
		struct _TT { INT n;	DGXMATRIX* mtT; } *t = (_TT*)pData;
		INT		n = t->n;

		if(n<0 || n>=this->m_Info.nGeo)
			return DGE_ECANNOTFIND_RESOURCE;

		t->mtT = &m_pGeo[n].mtW;
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


INT CDGX_Ast::GetNumVtx(INT nGeo)
{
	AseGeo* pGeo = &m_pGeo[nGeo];
	
	return pGeo->m_iNvx;
}

INT CDGX_Ast::GetNumFce(INT nGeo)
{
	AseGeo* pGeo = &m_pGeo[nGeo];
	
	return pGeo->m_iFce;
}

void*  CDGX_Ast::GetPtVtx(INT nGeo)
{
	AseGeo* pGeo = &m_pGeo[nGeo];
	
	return pGeo->m_pVtx;
}

void*  CDGX_Ast::GetPtFce(INT nGeo)
{
	AseGeo* pGeo = &m_pGeo[nGeo];

	return pGeo->m_pIdx;
}


INT CDGX_Ast::GetAniTrack(void* mtOut, INT nGeo, FLOAT dFrame)
{
	INT			i=0;

	AseGeo*		pGeo	= &m_pGeo[nGeo];
	DGXMATRIX	mtA;

	INT			iSizeR = pGeo->vRot.size();
	INT			iSizeP = pGeo->vTrs.size();

	
	mtA.Identity();

	
	if(iSizeR && pGeo->vRot[0].nF <=dFrame)
	{
//		INT nFrm = pGeo->vRot[0].nF;
		INT nIdx;

		if(1 == iSizeR)
		{
			DGXQUATERNION q;

			nIdx =0;

			q.x = pGeo->vRot[nIdx].x;
			q.y = pGeo->vRot[nIdx].y;
			q.z = pGeo->vRot[nIdx].z;
			q.w = pGeo->vRot[nIdx].w;

			q.RotationMatrix(&mtA, FALSE);
		}

		else if(pGeo->vRot[iSizeR-1].nF <=dFrame)
		{
			DGXQUATERNION q;

			nIdx = iSizeR-1;

			q.x = pGeo->vRot[nIdx].x;
			q.y = pGeo->vRot[nIdx].y;
			q.z = pGeo->vRot[nIdx].z;
			q.w = pGeo->vRot[nIdx].w;

			q.RotationMatrix(&mtA, FALSE);
		}

		else
		{
			for(i=0; i<iSizeR-1; ++i)
			{
				if(pGeo->vRot[i].nF <=dFrame && dFrame <pGeo->vRot[i+1].nF)
				{
					DGXQUATERNION q;
					DGXQUATERNION q1;
					DGXQUATERNION q2;

					nIdx = i;

					q1.x = pGeo->vRot[nIdx].x;
					q1.y = pGeo->vRot[nIdx].y;
					q1.z = pGeo->vRot[nIdx].z;
					q1.w = pGeo->vRot[nIdx].w;

					q2.x = pGeo->vRot[nIdx+1].x;
					q2.y = pGeo->vRot[nIdx+1].y;
					q2.z = pGeo->vRot[nIdx+1].z;
					q2.w = pGeo->vRot[nIdx+1].w;

					FLOAT	w = (dFrame - pGeo->vRot[i].nF)/(pGeo->vRot[i+1].nF- pGeo->vRot[i].nF);

					q.SLerp(&q1, &q2, w);
					q.RotationMatrix(&mtA, FALSE);

					break;
				}
			}
		}
	}

	else
	{
		mtA = pGeo->TmInf.mtL;
	}


	if(iSizeP && pGeo->vTrs[0].nF <=dFrame)
	{
		INT nIdx;

		if(1 == iSizeP)
		{
			DGXVECTOR3 p;

			nIdx =0;
			p.x = pGeo->vTrs[nIdx].x;
			p.y = pGeo->vTrs[nIdx].y;
			p.z = pGeo->vTrs[nIdx].z;

			mtA._41 = p.x;
			mtA._42 = p.y;
			mtA._43 = p.z;
		}

		else if(pGeo->vTrs[iSizeP-1].nF <=dFrame)
		{
			DGXVECTOR3 p;

			nIdx = iSizeP-1;
			p.x = pGeo->vTrs[nIdx].x;
			p.y = pGeo->vTrs[nIdx].y;
			p.z = pGeo->vTrs[nIdx].z;

			mtA._41 = p.x;
			mtA._42 = p.y;
			mtA._43 = p.z;
		}

		else
		{
			for(i=0; i<iSizeP-1; ++i)
			{
				if(pGeo->vTrs[i].nF <=dFrame && dFrame <pGeo->vTrs[i+1].nF)
				{
					DGXVECTOR3 p;
					DGXVECTOR3 p1;
					DGXVECTOR3 p2;

					nIdx = i;

					p1.x = pGeo->vTrs[nIdx].x;
					p1.y = pGeo->vTrs[nIdx].y;
					p1.z = pGeo->vTrs[nIdx].z;

					p2.x = pGeo->vTrs[nIdx+1].x;
					p2.y = pGeo->vTrs[nIdx+1].y;
					p2.z = pGeo->vTrs[nIdx+1].z;


					FLOAT	w = (dFrame- pGeo->vTrs[i].nF)/(pGeo->vTrs[i+1].nF- pGeo->vTrs[i].nF);

					p = p1  + w * (p2-p1);
					mtA._41 = p.x;	mtA._42 = p.y;	mtA._43 = p.z;
					break;
				}
			}
		}
	}
	else
	{
		mtA._41 = pGeo->TmInf.mtL._41;
		mtA._42 = pGeo->TmInf.mtL._42;
		mtA._43 = pGeo->TmInf.mtL._43;
	}


	*((DGXMATRIX*) mtOut) = mtA;
	
	return DGE_OK;
}



INT CDGX_Ast::Load()
{
	FILE*	fp;

	fp = fopen(m_sFile, "rt");
	
	if(NULL == fp)
		return DGE_ECANNOTFIND_RESOURCE;


	ParseScene(fp);
	ParseMaterial(fp);
	ParseGeometry(fp);
	ParseAnimation(fp);

	fclose(fp);

	return DGE_OK;
}



