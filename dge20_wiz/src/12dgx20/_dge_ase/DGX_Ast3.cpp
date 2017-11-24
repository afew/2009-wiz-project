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


// 1. save Header
//    version
//    Scene Info

// 2. Save Material

// 3. Save Geometry

// 4. Animation Set


void CDGX_Ast::SaveToAsmBin()
{
	FILE*	fp=NULL;
	INT		n=0;
	INT		j=0;

	char drive[DGE_MAX_DRIVE]={0};
	char dir  [DGE_MAX_DIR  ]={0};
	char fname[DGE_MAX_FNAME]={0};
	char ext  [DGE_MAX_EXT  ]=".asb";

	DgeStr_SplitPath( m_sFile, drive, dir, fname, NULL );

	char	sFile[DGE_MAX_PATH]={0};

	sprintf(sFile, "%s%s%s%s", drive, dir, fname, ext);

	fp = fopen(sFile, "wb");

	
	
	
	//1. save Header
	fwrite(&m_Info, sizeof(CDGX_Ast::TInfo), 1, fp);	// Info
	fseek(fp, DGXM_HEADEAR, SEEK_SET);			// chunck 만큼 이동


	//2. Writing Material
	for(n=0; n<m_Info.nMtl; ++n)
	{
		AseMtl*	pDest	= &m_pMtl[n];
		fwrite(pDest->sTex, 1, DGXM_TEXNAME, fp);
	}


	//3. Writing Geometry Info
	for(n=0; n<m_Info.nGeo; ++n)
	{
		AseGeo*	pDest	= &m_pGeo[n];

		INT	nAniRot = pDest->vRot.size();
		INT	nAniTrs = pDest->vTrs.size();

		fwrite(pDest->sNodeCur , sizeof(char	), 32, fp);		// Current Node Name
		fwrite(&pDest->nNodePrn, sizeof(INT		),  1, fp);		// Parent Node Index
		fwrite(&pDest->nMtlRef , sizeof(INT		),  1, fp);		// Material Index

		fwrite(&pDest->m_iFce	, sizeof(INT	),  1, fp);		// Number of Index
		fwrite(&pDest->m_iNvx	, sizeof(INT	),  1, fp);		// Number of Vertex
		fwrite(&pDest->m_dFVF	, sizeof(DWORD	),  1, fp);		// FVF
		fwrite(&pDest->m_dVtx	, sizeof(DWORD	),  1, fp);		// Zero Stride

		fwrite(&pDest->mtW      , sizeof(FLOAT	), 16, fp);		// World Matrix
		fwrite(&pDest->mtL      , sizeof(FLOAT	), 16, fp);		// Local Matrix
		fwrite(&pDest->TmInf.mtL, sizeof(FLOAT	), 16, fp);		// Transform and Movement

		fwrite(&nAniRot			, sizeof(INT	),  1, fp);		// Rotaion Number of Animation
		fwrite(&nAniTrs			, sizeof(INT	),  1, fp);		// Translation Number of Animation
	}

	//4. Writing Index, Vertex Buffer
	for(n=0; n<m_Info.nGeo; ++n)
	{
		AseGeo*	pDest	= &m_pGeo[n];

		// Writing Index Buffer
		if(pDest->m_iFce)
			fwrite(pDest->m_pIdx, sizeof(AseFce), pDest->m_iFce, fp);

		// Writing Vertex Buffer
		if(pDest->m_iNvx)
			fwrite(pDest->m_pVtx, pDest->m_dVtx, pDest->m_iNvx, fp);
	}

	//5. Writing Animation. scaling은 제외 <-- biped Animation은 scaling이 없다.
	for(n=0; n<m_Info.nGeo; ++n)
	{
		AseGeo*	pDest	= &m_pGeo[n];

		INT	nAniRot = pDest->vRot.size();
		INT	nAniTrs = pDest->vTrs.size();

		// Writing Rotation
		for(j=0; j<nAniRot; ++j)
		{
			AseTrack* t	= &pDest->vRot[j];
			fwrite(t, sizeof(AseTrack), 1, fp);
		}

		// Writing Translation
		for(j=0; j<nAniTrs; ++j)
		{
			AseTrack* t	= &pDest->vTrs[j];
			fwrite(t, sizeof(AseTrack), 1, fp);
		}
	}

	fclose(fp);
}



void CDGX_Ast::SaveToAsmTxt()
{
	INT		n=0;
	INT		j=0;

	char drive[DGE_MAX_DRIVE]={0};
	char dir  [DGE_MAX_DIR  ]={0};
	char fname[DGE_MAX_FNAME]={0};
	char ext  [DGE_MAX_EXT  ]=".ast";

	DgeStr_SplitPath( m_sFile, drive, dir, fname, NULL );

	char	sFile[DGE_MAX_PATH]={0};

	sprintf(sFile, "%s%s%s%s", drive, dir, fname, ext);

	FILE*	fp = fopen(sFile, "wt");

	//1. save Header
	fprintf(fp, "Version: %s\n", m_Info.sVer);
	fprintf(fp, "FrameBeginEndFpsTick: %3d %3d %3d %3d\n\n"
				, m_Info.nFrmF
				, m_Info.nFrmL
				, m_Info.nFrmS
				, m_Info.nFrmT
				);

	fprintf(fp, "MaterialGeometryNum: %3d %3d\n\n", m_Info.nMtl, m_Info.nGeo);



	//2. Writing Material
	for(n=0; n<m_Info.nMtl; ++n)
	{
		AseMtl*	pDest	= &m_pMtl[n];

		fprintf(fp, "\nMaterial: %3d\n", n);
		fprintf(fp, "	TextureDif: \"%s\"\n", pDest->sTex);
	}

	fprintf(fp, "\n\n");


	//3. Writing Geometry
	for(n=0; n<m_Info.nGeo; ++n)
	{
		AseGeo*	pDest	= &m_pGeo[n];

		fprintf(fp, "\nGeoIdxPrnMtl: %2d %2d %2d ", n, pDest->nNodePrn, pDest->nMtlRef);
		fprintf(fp, "\"%s\"	\"%s\"\n", pDest->sNodeCur, pDest->sNodePrn);

		fprintf(fp, "	FaceVtxFVFStride: %3d  %3d 0x%X %d\n", pDest->m_iFce, pDest->m_iNvx, pDest->m_dFVF, pDest->m_dVtx);

		// Writing Index Buffer
		if(pDest->m_iFce < 0)
			continue;


		fprintf(fp, "	Faces:\n");

		for(j=0; j<pDest->m_iFce; ++j)
		{
			fprintf(fp, "	%4d %4d %4d\n", pDest->m_pIdx[j].a, pDest->m_pIdx[j].b, pDest->m_pIdx[j].c);
		}

		fprintf(fp, "	Vertices:\n");

		for(j=0; j<pDest->m_iNvx; ++j)
		{
			if(AseVtx::FVF == pDest->m_dFVF)
			{
				AseVtx*	pVtx = (AseVtx*)pDest->m_pVtx;
				fprintf(fp, "	%10.5f %10.5f %10.5f\n", pVtx[j].p.x, pVtx[j].p.y, pVtx[j].p.z);
			}
			else if(AseVtxUV::FVF == pDest->m_dFVF)
			{
				AseVtxUV*	pVtx = (AseVtxUV*)pDest->m_pVtx;
				fprintf(fp, "	%10.5f %10.5f %10.5f   %10.5f %10.5f\n", pVtx[j].p.x, pVtx[j].p.y, pVtx[j].p.z, pVtx[j].u, pVtx[j].v);
			}
		}
	}

	fprintf(fp, "\n\n");
	
	//4. Writing Animation. scaling은 제외 <-- biped Animation은 scaling이 없다.
	for(n=0; n<m_Info.nGeo; ++n)
	{
		AseGeo*	pDest	= &m_pGeo[n];

		INT	nAniRot = pDest->vRot.size();
		INT	nAniTrs = pDest->vTrs.size();

		fprintf(fp, "AniGeoIdx_RotTransNum: %2d %3d %3d  ", n, nAniRot, nAniTrs);
		fprintf(fp, "\"%s\"\n", pDest->sNodeCur);

		fprintf(fp, "	WorldMatrix:\n");
		fprintf(fp, "		%12.6f %12.6f %12.6f %12.6f\n", pDest->mtW._11, pDest->mtW._12, pDest->mtW._13, pDest->mtW._14);
		fprintf(fp, "		%12.6f %12.6f %12.6f %12.6f\n", pDest->mtW._21, pDest->mtW._22, pDest->mtW._23, pDest->mtW._24);
		fprintf(fp, "		%12.6f %12.6f %12.6f %12.6f\n", pDest->mtW._31, pDest->mtW._32, pDest->mtW._33, pDest->mtW._34);
		fprintf(fp, "		%12.6f %12.6f %12.6f %12.6f\n", pDest->mtW._41, pDest->mtW._42, pDest->mtW._43, pDest->mtW._44);
		
		fprintf(fp, "	LocalMatrix:\n");
		fprintf(fp, "		%12.6f %12.6f %12.6f %12.6f\n", pDest->mtL._11, pDest->mtL._12, pDest->mtL._13, pDest->mtL._14);
		fprintf(fp, "		%12.6f %12.6f %12.6f %12.6f\n", pDest->mtL._21, pDest->mtL._22, pDest->mtL._23, pDest->mtL._24);
		fprintf(fp, "		%12.6f %12.6f %12.6f %12.6f\n", pDest->mtL._31, pDest->mtL._32, pDest->mtL._33, pDest->mtL._34);
		fprintf(fp, "		%12.6f %12.6f %12.6f %12.6f\n", pDest->mtL._41, pDest->mtL._42, pDest->mtL._43, pDest->mtL._44);

		fprintf(fp, "	TM:\n");
		fprintf(fp, "		%12.6f %12.6f %12.6f %12.6f\n", pDest->TmInf.mtL._11, pDest->TmInf.mtL._12, pDest->TmInf.mtL._13, pDest->TmInf.mtL._14);
		fprintf(fp, "		%12.6f %12.6f %12.6f %12.6f\n", pDest->TmInf.mtL._21, pDest->TmInf.mtL._22, pDest->TmInf.mtL._23, pDest->TmInf.mtL._24);
		fprintf(fp, "		%12.6f %12.6f %12.6f %12.6f\n", pDest->TmInf.mtL._31, pDest->TmInf.mtL._32, pDest->TmInf.mtL._33, pDest->TmInf.mtL._34);
		fprintf(fp, "		%12.6f %12.6f %12.6f %12.6f\n", pDest->TmInf.mtL._41, pDest->TmInf.mtL._42, pDest->TmInf.mtL._43, pDest->TmInf.mtL._44);

		fprintf(fp, "\n");

		fprintf(fp, "	Rotation:\n");

		// Writing Rotation
		for(j=0; j<nAniRot; ++j)
		{
			AseTrack* t	= &pDest->vRot[j];
			fprintf(fp, "	%4d %12.6f %12.6f %12.6f %12.6f", t->nF, t->x, t->y, t->z, t->w);
			fprintf(fp, "\n");
		}


		fprintf(fp, "	Translation:\n");

		// Writing Translation
		for(j=0; j<nAniTrs; ++j)
		{
			AseTrack* t	= &pDest->vTrs[j];
			fprintf(fp, "	%4d %12.6f %12.6f %12.6f", t->nF, t->x, t->y, t->z);
			fprintf(fp, "\n");
		}

		fprintf(fp, "\n");
	}


	fprintf(fp, "\n\n");



	fclose(fp);
}


