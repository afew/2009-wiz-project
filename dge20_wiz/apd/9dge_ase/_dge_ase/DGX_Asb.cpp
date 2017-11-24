// Implementation of the CDGX_Asb class.
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


CDGX_Asb::Tmtl::Tmtl()
{
	memset(sTex, 0, sizeof sTex);
	pTex = NULL;
}

CDGX_Asb::Tmtl::~Tmtl()
{
	SAFE_DELETE(	pTex	);
}


CDGX_Asb::Tgeo::Tgeo()
{
	nMtl	= -1;

	memset(sName, 0, sizeof sName);

	nPrn	= -1;
	iFce	= 0;
	iNvx	= 0;
	pIdx	= NULL;
	pVtx	= NULL;
	dFVF	= 0;
	dVtx	= 0;

	mtTmL.Identity();
	mtW.Identity();
	mtL.Identity();
	
	nRot	= 0;
	nTrs	= 0;
	vRot	= NULL;
	vTrs	= NULL;
}

CDGX_Asb::Tgeo::~Tgeo()
{
	SAFE_DELETE_ARRAY(	pIdx	);

	if(pVtx)
	{
		if(dFVF == (DWORD)Tvtx::FVF)
		{
			Tvtx* p = (Tvtx*)pVtx;
			delete [] p;
		}

		else if(dFVF == (DWORD)TvtxUV::FVF)
		{
			TvtxUV* p = (TvtxUV*)pVtx;
			delete [] p;
		}

		pVtx = NULL;
	}

	nPrn	= -1;
	iFce	= 0;
	iNvx	= 0;
	dFVF	= 0;
	dVtx	= 0;

	SAFE_DELETE_ARRAY(	vRot	);
	SAFE_DELETE_ARRAY(	vTrs	);
}


CDGX_Asb::CDGX_Asb()
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

CDGX_Asb::~CDGX_Asb()
{
	Destroy();
}


INT CDGX_Asb::Create(void* p1, void* p2, void* p3, void* p4)
{
	m_pDev = (PDGE_DEVICE)p1;

	strcpy(m_sFile, (char*)p2);


	if(DGE_FAILED(Load()))
		return DGE_EFAIL;


	m_dFrmBgn = m_Info.nFrmF;		// 애니메이션 루프의 시작 프레임
	m_dFrmEnd = m_Info.nFrmL;		// 애니메이션 루프의 마지막 프레임


	return DGE_OK;
}


void CDGX_Asb::Destroy()
{
	SAFE_DELETE_ARRAY(	m_pMtl	);	
	SAFE_DELETE_ARRAY(	m_pGeo	);
}






INT CDGX_Asb::FrameMove()
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
		Tgeo*		pGeo = &m_pGeo[i];
		
		this->GetAniTrack(&pGeo->mtL, i, (FLOAT)m_dFrmCur);

		// 부모의 월드 행렬을 곱해 자신의 월드 행렬을 완성한다.
		DGXMATRIX	mtPrn =DGXMATRIX(1,0,0,0,  0,1,0,0,  0,0,1,0,  0,0,0,1);

		if(0 <= pGeo->nPrn)
			mtPrn	= m_pGeo[pGeo->nPrn].mtW;

		pGeo->mtW = pGeo->mtL * mtPrn;
	}


	return DGE_OK;
}




void CDGX_Asb::Render()
{
	if(!m_pGeo)
		return;

	INT			i=0;
	DGXMATRIX	mtW;


	for(i=0; i<m_Info.nGeo; ++i)
	{
		Tgeo*		pGeo = &m_pGeo[i];

		if(NULL == pGeo->pVtx)
			continue;

		PDGE_TEXTURE pTx=NULL;

		if( 0<= pGeo->nMtl)
			pTx = m_pMtl[pGeo->nMtl].pTex;
		
		if(NULL == pTx)
			continue;


		mtW = pGeo->mtW * m_mtWld;

		m_pDev->SetTexture(0, pTx);

		m_pDev->SetTransform(DGE_TS_WORLD, &mtW);
		m_pDev->SetFVF(pGeo->dFVF);
		m_pDev->DrawIndexedPrimitiveUPf(DGE_PT_TRIANGLE_LIST, pGeo->iFce*3, pGeo->pIdx, pGeo->pVtx, pGeo->dVtx);

		m_pDev->SetTexture(0, 0);
	}

	m_pDev->SetTransformIdentity(DGE_TS_WORLD);
}



INT CDGX_Asb::SetAttrib(DWORD dCmd, void* pData)
{
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

	return DGE_EFAIL;
}


INT CDGX_Asb::GetAttrib(DWORD dCmd, void* pData)
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




INT CDGX_Asb::GetAniTrack(void* mtOut, INT nGeo, FLOAT dFrame)
{
	INT			i=0;

	Tgeo*		pGeo	= &m_pGeo[nGeo];
	DGXMATRIX	mtA;

	INT			iSizeR = pGeo->nRot;
	INT			iSizeP = pGeo->nTrs;

	
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
		mtA = pGeo->mtTmL;
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
		mtA._41 = pGeo->mtTmL._41;
		mtA._42 = pGeo->mtTmL._42;
		mtA._43 = pGeo->mtTmL._43;
	}


	*((DGXMATRIX*) mtOut) = mtA;
	
	return DGE_OK;
}






INT CDGX_Asb::Load()
{
	FILE*	fp;
	INT		n=0;

	fp = fopen(m_sFile, "rb");
	
	if(NULL == fp)
		return DGE_ECANNOTFIND_RESOURCE;


	//1. Reading Header
	fread(&m_Info, sizeof(CDGX_Ast::TInfo), 1, fp);	// Scene Info

	fseek(fp, DGXM_HEADEAR, SEEK_SET);	// chunck 만큼 이동


	m_pMtl = new Tmtl[m_Info.nMtl];
	m_pGeo = new Tgeo[m_Info.nGeo];


	//2. Reading Material
	for(n=0; n<m_Info.nMtl; ++n)
	{
		Tmtl*	pDest	= &m_pMtl[n];
		fread(pDest->sTex, 1, DGXM_TEXNAME, fp);
	}


	//3. Reading Geometry Info
	for(n=0; n<m_Info.nGeo; ++n)
	{
		Tgeo*	pDest	= &m_pGeo[n];

		fread(pDest->sName	, sizeof(char ), 32, fp);		// Current Node Name
		fread(&pDest->nPrn	, sizeof(INT  ),  1, fp);		// Parent Node Index
		fread(&pDest->nMtl	, sizeof(INT  ),  1, fp);		// Material Index

		fread(&pDest->iFce	, sizeof(INT  ),  1, fp);		// Number of Index
		fread(&pDest->iNvx	, sizeof(INT  ),  1, fp);		// Number of Vertex
		fread(&pDest->dFVF	, sizeof(DWORD),  1, fp);		// FVF
		fread(&pDest->dVtx	, sizeof(DWORD),  1, fp);		// Zero Stride

		fread(&pDest->mtW	, sizeof(FLOAT), 16, fp);		// World Matrix
		fread(&pDest->mtL	, sizeof(FLOAT), 16, fp);		// Local Matrix
		fread(&pDest->mtTmL	, sizeof(FLOAT), 16, fp);		// Transform and Movement

		fread(&pDest->nRot	, sizeof(INT  ),  1, fp);		// Rotaion Number of Animation
		fread(&pDest->nTrs	, sizeof(INT  ),  1, fp);		// Translation Number of Animation
	}


	//4. Memory Alloc
	for(n=0; n<m_Info.nGeo; ++n)
	{
		Tgeo*	pDest	= &m_pGeo[n];

		if(pDest->iFce)
			pDest->pIdx = new Tidx[pDest->iFce];

		if(pDest->iNvx)
		{
			if(pDest->dFVF == (DWORD)Tvtx::FVF)
				pDest->pVtx = new Tvtx[pDest->iNvx];

			else if(pDest->dFVF == (DWORD)TvtxUV::FVF)
				pDest->pVtx = new TvtxUV[pDest->iNvx];
		}

		if(pDest->nRot)
			pDest->vRot = new Ttrack[pDest->nRot];

		if(pDest->nTrs)
			pDest->vTrs= new Ttrack[pDest->nTrs];
	}


	//5. Reading Vertex.
	for(n=0; n<m_Info.nGeo; ++n)
	{
		Tgeo*	pDest	= &m_pGeo[n];

		// Reading Index Buffer
		if(pDest->iFce)
			fread(pDest->pIdx, sizeof(Tidx), pDest->iFce, fp);
	
		if(pDest->iNvx)
			fread(pDest->pVtx, pDest->dVtx, pDest->iNvx, fp);
	}

	//6. Reading Animation.
	for(n=0; n<m_Info.nGeo; ++n)
	{
		Tgeo*	pDest	= &m_pGeo[n];

		// Reading Rotation
		if(0< pDest->nRot)
			fread(pDest->vRot, sizeof(Ttrack), pDest->nRot, fp);

		// Reading Translation
		if(0< pDest->nTrs)
			fread(pDest->vTrs, sizeof(Ttrack), pDest->nTrs, fp);
	}


	fclose(fp);



	//7. Load Texture
	DWORD	dColorKey = 0x0;

	char dir[DGE_MAX_DIR]={0};
	DgeStr_SplitPath( m_sFile, NULL, dir, NULL, NULL);

	for(n=0; n<m_Info.nMtl; ++n)
	{
		Tmtl*		pMtl = &m_pMtl[n];

		char sFile[DGE_MAX_PATH]={0};

		sprintf(sFile, "%s%s", dir, pMtl->sTex);

		if(DGE_FAILED(DGE_CreateTexture(NULL, &pMtl->pTex, (DGE_HANDLE)sFile, &dColorKey)))
		{
			//MessageBox(GetActiveWindow(), "Cannot Read Model Texture", "Error", 0);
			printf("Err: %d, %s \t", __LINE__, __FILE__);
			printf("Cannot Read Model Texture\n");
			return DGE_EFAIL;
		}
	}


	return DGE_OK;
}



