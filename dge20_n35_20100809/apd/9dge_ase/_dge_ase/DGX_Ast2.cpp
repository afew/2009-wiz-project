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

void LnStr_Trim(char* sBuf);
void LnStr_Quot(char* sDst, const char* sSrc);




CDGX_Ast::AseMtl::AseMtl()
{
	memset(sTex, 0, sizeof sTex);
	pTex = NULL;
}

CDGX_Ast::AseMtl::~AseMtl()
{
	SAFE_DELETE(	pTex	);
}



CDGX_Ast::AseGeo::AseGeo()
{
	nMtlRef = -1;
	iNumVtx = 0;
	iNumFce = 0;
	iNumTvtx= 0;
	iNumTfce = 0;

	pLstVtx = NULL;
//	pLstNor	= NULL;
	pLstFce = NULL;

	pLstTvtx= NULL;
	pLstTfce= NULL;

	memset(sNodeCur, 0, sizeof sNodeCur);
	memset(sNodePrn, 0, sizeof sNodePrn);

	nNodePrn= -1;
	pGeoPrn	= NULL;
	m_iFce	= 0;
	m_iNvx	= 0;
	m_pIdx	= NULL;
	m_pVtx	= NULL;
	m_dFVF	= 0;
	m_dVtx	= 0;

//	strcpy(sNodePrn, "<NULL>");
}

CDGX_Ast::AseGeo::~AseGeo()
{
	SAFE_DELETE_ARRAY(	m_pIdx	);

	if(m_pVtx)
	{
		if(m_dFVF == (DWORD)AseVtx::FVF)
		{
			AseVtx* pVtx = (AseVtx*)m_pVtx;
			delete [] pVtx;
		}

//		if(m_dFVF == (DWORD)AseVtxN::FVF)
//		{
//			AseVtxN* pVtx = (AseVtxN*)m_pVtx;
//			delete [] pVtx;
//		}

		else if(m_dFVF == (DWORD)AseVtxUV::FVF)
		{
			AseVtxUV* pVtx = (AseVtxUV*)m_pVtx;
			delete [] pVtx;
		}

//		else if(m_dFVF == (DWORD)AseVtxNUV::FVF)
//		{
//			AseVtxNUV* pVtx = (AseVtxNUV*)m_pVtx;
//			delete [] pVtx;
//		}
	
		m_pVtx = NULL;
	}

	nNodePrn= -1;
	pGeoPrn	= NULL;
	m_iFce	= 0;
	m_iNvx	= 0;
	m_dFVF	= 0;
	m_dVtx	= 0;
}




enum	EAseKey
{
	SCENE,
	FRAME_FIRST,
	FRAME_LAST,
	FRAME_SPEED,
	FRAME_TICK,

	MTRL_LST	,
	MTRL_CNT	,
	MTRL_INF	,

	MTRL_MAPDIF	,
	MTRL_TEXDIF	,

	GEOOBJECT	,

	NODE_CUR	,
	NODE_PRN	,

	MTRL_REF	,

	NODE_TM		,
	TM_ROW0		,
	TM_ROW1		,
	TM_ROW2		,
	TM_ROW3		,
	TM_POS		,
	TM_ROT		,
	TM_RTA		,
	TM_SCL		,

	MESH_INFOS ,
	MESH_NUMVTX,
	MESH_NUMFCE,
	MESH_VTXLST,
	MESH_VTXREC,
	MESH_FCELST,
	MESH_FCEREC,
	
	MESH_NUMTVTX,
	MESH_TVTXLST,
	MESH_TVTXREC,
	
	MESH_NUMTFCE,
	MESH_TFCELST,
	MESH_TFCEREC,

	MESH_NORMAL,
	MESH_FCENRL,

	TM_ANIMATION,
	ROT_TRACK	,
	ROT_SAMPLE	,
	SCALE_TRACK	,
	SCALE_SAMPLE,
	POS_TRACK	,
	POS_SAMPLE	,

	ROT_TCB		,
	ROT_TCB_KEY	,
};



// Parsing Keyword
CDGX_Ast::_AseKey Keywords[] = 
{
	{	"*SCENE {"				,	strlen("*SCENE {"			)	},	// SCENE
	{	"*SCENE_FIRSTFRAME"		,	strlen("*SCENE_FIRSTFRAME"	)	},	// FRAME_FIRST
	{	"*SCENE_LASTFRAME"		,	strlen("*SCENE_LASTFRAME"	)	},	// FRAME_LAST
	{	"*SCENE_FRAMESPEED"		,	strlen("*SCENE_FRAMESPEED"	)	},	// FRAME_SPEED
	{	"*SCENE_TICKSPERFRAME"	,	strlen("*SCENE_TICKSPERFRAME")	},	// FRAME_TICK

	{	"*MATERIAL_LIST {"		,	strlen("*MATERIAL_LIST {"	)	},	// MTRL_LST
	{	"*MATERIAL_COUNT"		,	strlen("*MATERIAL_COUNT"	)	},	// MTRL_CNT
	{	"*MATERIAL "			,	strlen("*MATERIAL "			)	},	// MTRL_INF

	{	"*MAP_DIFFUSE {"		,	strlen("*MAP_DIFFUSE {"		)	},	// MTRL_MAPDIF
	{	"*BITMAP"				,	strlen("*BITMAP"			)	},	// MTRL_TEXDIF

	{	"*GEOMOBJECT {"			,	strlen("*GEOMOBJECT {"		)	},	// GEOOBJECT

	{	"*NODE_NAME"			,	strlen("*NODE_NAME"			)	},	// NODE_CUR
	{	"*NODE_PARENT"			,	strlen("*NODE_PARENT"		)	},	// NODE_PRN

	{	"*MATERIAL_REF"			,	strlen("*MATERIAL_REF"		)	},	// MTRL_REF

	{	"*NODE_TM {"			,	strlen("*NODE_TM {"			)	},	// NODE_TM
	{	"*TM_ROW0"				,	strlen("*TM_ROW0"			)	},	// TM_ROW0
	{	"*TM_ROW1"				,	strlen("*TM_ROW1"			)	},	// TM_ROW1
	{	"*TM_ROW2"				,	strlen("*TM_ROW2"			)	},	// TM_ROW2
	{	"*TM_ROW3"				,	strlen("*TM_ROW3"			)	},	// TM_ROW3
	{	"*TM_POS"				,	strlen("*TM_POS"			)	},	// TM_POS
	{	"*TM_ROTAXIS"			,	strlen("*TM_ROTAXIS"		)	},	// TM_ROT
	{	"*TM_ROTANGLE"			,	strlen("*TM_ROTANGLE"		)	},	// TM_RTA
	{	"*TM_SCALE"				,	strlen("*TM_SCALE"			)	},	// TM_SCL
	
	{	"*MESH {"				,	strlen("*MESH {"			)	},	// MESH_INFOS
	{	"*MESH_NUMVERTEX"		,	strlen("*MESH_NUMVERTEX"	)	},	// MESH_NUMVTX
	{	"*MESH_NUMFACES"		,	strlen("*MESH_NUMFACES"		)	},	// MESH_NUMFCE
	{	"*MESH_VERTEX_LIST {"	,	strlen("*MESH_VERTEX_LIST {")	},	// MESH_VTXLST
	{	"*MESH_VERTEX"			,	strlen("*MESH_VERTEX"		)	},	// MESH_VTXREC
	{	"*MESH_FACE_LIST {"		,	strlen("*MESH_FACE_LIST {"	)	},	// MESH_FCELST
	{	"*MESH_FACE"			,	strlen("*MESH_FACE"			)	},	// MESH_FCEREC
	
	{	"*MESH_NUMTVERTEX"		,	strlen("*MESH_NUMTVERTEX"	)	},	// MESH_NUMTVTX
	{	"*MESH_TVERTLIST {"		,	strlen("*MESH_TVERTLIST {"	)	},	// MESH_TVTXLST
	{	"*MESH_TVERT"			,	strlen("*MESH_TVERT"		)	},	// MESH_TVTXREC

	{	"*MESH_NUMTVFACES"		,	strlen("*MESH_NUMTVFACES"	)	},	// MESH_NUMTFCE
	{	"*MESH_TFACELIST {"		,	strlen("*MESH_TFACELIST {"	)	},	// MESH_TFCELST
	{	"*MESH_TFACE"			,	strlen("*MESH_TFACE"		)	},	// MESH_TFCEREC

	{	"*MESH_NORMALS {"		,	strlen("*MESH_NORMALS {"	)	},	// MESH_NORMAL
	{	"*MESH_FACENORMAL"		,	strlen("*MESH_FACENORMAL"	)	},	// MESH_FCENRL

	{	"*TM_ANIMATION {"		,	strlen("*TM_ANIMATION {"		)	},	// TM_ANIMATION
	{	"*CONTROL_ROT_TRACK {"	,	strlen("*CONTROL_ROT_TRACK {"	)	},	// ROT_TRACK	
	{	"*CONTROL_ROT_SAMPLE"	,	strlen("*CONTROL_ROT_SAMPLE"	)	},	// ROT_SAMPLE	
	{	"*CONTROL_SCALE_TRACK {",	strlen("*CONTROL_SCALE_TRACK {"	)	},	// SCALE_TRACK	
	{	"*CONTROL_SCALE_SAMPLE"	,	strlen("*CONTROL_SCALE_SAMPLE"	)	},	// SCALE_SAMPLE
	{	"*CONTROL_POS_TRACK {"	,	strlen("*CONTROL_POS_TRACK {"	)	},	// POS_TRACK	
	{	"*CONTROL_POS_SAMPLE"	,	strlen("*CONTROL_POS_SAMPLE"	)	},	// POS_SAMPLE	
	
	{	"*CONTROL_ROT_TCB {"	,	strlen("*CONTROL_ROT_TCB {"		)	},	// ROT_TCB
	{	"*CONTROL_TCB_ROT_KEY"	,	strlen("*CONTROL_TCB_ROT_KEY"	)	},	// ROT_TCB_KEY
};



INT CDGX_Ast::ParseScene(FILE* fp)
{
	// Scene파싱
	char	sLine[MAX_PARSE_LINE];

	while(!feof(fp))
	{
		fgets(sLine, MAX_PARSE_LINE, fp);
		LnStr_Trim(sLine);

		if(0 == DgeStr_Strnicmp(sLine, Keywords[SCENE].sKey, Keywords[SCENE].iKey) )
		{
			while(!feof(fp))
			{
				fgets(sLine, MAX_PARSE_LINE, fp);
				LnStr_Trim(sLine);

				if('}' == sLine[0])
				{
					return DGE_OK;
//					break;
				}
					

				if(0 == DgeStr_Strnicmp(sLine, Keywords[FRAME_FIRST].sKey, Keywords[FRAME_FIRST].iKey) )
				{
					INT		nFirst;
					sscanf(sLine, "%*s %d", &nFirst);
					m_Info.nFrmF = nFirst;
				}

				if(0 == DgeStr_Strnicmp(sLine, Keywords[FRAME_LAST].sKey, Keywords[FRAME_LAST].iKey) )
				{
					INT		nLast;
					sscanf(sLine, "%*s %d", &nLast);
					m_Info.nFrmL = nLast;
				}

				if(0 == DgeStr_Strnicmp(sLine, Keywords[FRAME_SPEED].sKey, Keywords[FRAME_SPEED].iKey) )
				{
					INT		nSpeed;
					sscanf(sLine, "%*s %d", &nSpeed);
					m_Info.nFrmS = nSpeed;
				}

				if(0 == DgeStr_Strnicmp(sLine, Keywords[FRAME_TICK].sKey, Keywords[FRAME_TICK].iKey) )
				{
					INT		nTick;
					sscanf(sLine, "%*s %d", &nTick);
					m_Info.nFrmT = nTick;
				}

			}
		}

	}

	return DGE_OK;
}

INT	CDGX_Ast::ParseMaterial(FILE* fp)
{
	// Material파싱


	char	sLine[MAX_PARSE_LINE];
	
	
	// 파일 포인터를 처음으로 옮긴다.
	fseek(fp, 0, SEEK_SET);

	
	// 머티리얼 숫자를 센다.
	m_Info.nMtl	= 0;


	while(!feof(fp))
	{
		fgets(sLine, MAX_PARSE_LINE, fp);
		LnStr_Trim(sLine);

		if(0 == DgeStr_Strnicmp(sLine, Keywords[MTRL_LST].sKey, Keywords[MTRL_LST].iKey) )
		{
			while(!feof(fp))
			{
				fgets(sLine, MAX_PARSE_LINE, fp);
				LnStr_Trim(sLine);

				if('}' == sLine[0])
					break;

				if(0 == DgeStr_Strnicmp(sLine, Keywords[MTRL_CNT].sKey, Keywords[MTRL_CNT].iKey) )
				{
					INT		iNmtl;
					sscanf(sLine, "%*s %d", &iNmtl);
					m_Info.nMtl = iNmtl;

					if(m_Info.nMtl>0)
						m_pMtl  = new CDGX_Ast::AseMtl[m_Info.nMtl];
				}

				if(0 == DgeStr_Strnicmp(sLine, Keywords[MTRL_INF].sKey, Keywords[MTRL_INF].iKey) )
				{
					INT	nMtl=-1;
					sscanf(sLine, "%*s %d", &nMtl);

					while(!feof(fp))
					{
						fgets(sLine, MAX_PARSE_LINE, fp);
						LnStr_Trim(sLine);

						if('}' == sLine[0])
							break;

						if(0 == DgeStr_Strnicmp(sLine, Keywords[MTRL_MAPDIF].sKey, Keywords[MTRL_MAPDIF].iKey) )
						{
							while(!feof(fp))
							{
								fgets(sLine, MAX_PARSE_LINE, fp);
								LnStr_Trim(sLine);

								if('}' == sLine[0])
									break;

								if(0 == DgeStr_Strnicmp(sLine, Keywords[MTRL_TEXDIF].sKey, Keywords[MTRL_TEXDIF].iKey) )
								{
									char	sFile[512];
									LnStr_Quot(sFile, sLine);

									char sTx[DGE_MAX_FNAME]={0};
									char dir[DGE_MAX_DIR  ]={0};
									char ext[DGE_MAX_EXT  ];
									
									DgeStr_SplitPath(sFile, NULL, dir, sTx, ext);

									sprintf(m_pMtl[nMtl].sTex, "%s%s", sTx, ext);
								}

							}// while
						}// if

					}// while
				}// if


			}// while
		}//if
	}// while

	return DGE_OK;
}


INT CDGX_Ast::ParseGeometry(FILE* fp)
{
	// Scene 파싱
	char	sLine[MAX_PARSE_LINE];


	// 파일 포인터를 처음으로 옮긴다.
	fseek(fp, 0, SEEK_SET);


	//Geometry의 숫자를 센다.
	m_Info.nGeo	= 0;

	while(!feof(fp))
	{
		fgets(sLine, MAX_PARSE_LINE, fp);
		LnStr_Trim(sLine);

		if(0 == DgeStr_Strnicmp(sLine, Keywords[GEOOBJECT].sKey, Keywords[GEOOBJECT].iKey) )
			++m_Info.nGeo;
	}

	if(0==m_Info.nGeo)
		return DGE_ECANNOTFIND_RESOURCE;

	// 파일 포인터를 처음으로 옮긴다.
	fseek(fp, 0, SEEK_SET);

	
	m_pGeo = new AseGeo[m_Info.nGeo];
	INT	nGeoIdx = -1;
	
	while(!feof(fp))
	{
		fgets(sLine, MAX_PARSE_LINE, fp);
		LnStr_Trim(sLine);


		if(0 == DgeStr_Strnicmp(sLine, Keywords[GEOOBJECT].sKey, Keywords[GEOOBJECT].iKey) )
		{
			++nGeoIdx;
			AseGeo* pGeo = &m_pGeo[nGeoIdx];

			while(!feof(fp))
			{
				fgets(sLine, MAX_PARSE_LINE, fp);
				LnStr_Trim(sLine);

				if('}' == sLine[0])
					break;


				if(0 == DgeStr_Strnicmp(sLine, Keywords[MTRL_REF].sKey, Keywords[MTRL_REF].iKey) )
				{
					INT		nMtl;
					sscanf(sLine, "%*s %d", &nMtl);
					pGeo->nMtlRef = nMtl;
				}

				if(0 == DgeStr_Strnicmp(sLine, Keywords[NODE_CUR].sKey, Keywords[NODE_CUR].iKey) )
				{
					char	sName[64];
					LnStr_Quot(sName, sLine);
					strcpy(pGeo->sNodeCur, sName);
				}

				if(0 == DgeStr_Strnicmp(sLine, Keywords[NODE_PRN].sKey, Keywords[NODE_PRN].iKey) )
				{
					char	sName[64];
					LnStr_Quot(sName, sLine);
					strcpy(pGeo->sNodePrn, sName);
				}


				if(0 == DgeStr_Strnicmp(sLine, Keywords[NODE_TM].sKey, Keywords[NODE_TM].iKey) )
				{
					// Node TM
					while(!feof(fp))
					{
						fgets(sLine, MAX_PARSE_LINE, fp);
						LnStr_Trim(sLine);

						if('}' == sLine[0])
							break;


						if(0 == DgeStr_Strnicmp(sLine, Keywords[TM_ROW0].sKey, Keywords[TM_ROW0].iKey) )
						{
							FLOAT	x=0.F, y=0.F, z=0.F, w=0.F;
							sscanf(sLine, "%*s %f %f %f", &x, &y, &z);

							pGeo->TmInf.mtW._11  = x;
							pGeo->TmInf.mtW._12  = y;
							pGeo->TmInf.mtW._13  = z;
							pGeo->TmInf.mtW._14  = w;
						}

						if(0 == DgeStr_Strnicmp(sLine, Keywords[TM_ROW1].sKey, Keywords[TM_ROW1].iKey) )
						{
							FLOAT	x=0.F, y=0.F, z=0.F, w=0.F;
							sscanf(sLine, "%*s %f %f %f", &x, &y, &z);

							pGeo->TmInf.mtW._21  = x;
							pGeo->TmInf.mtW._22  = y;
							pGeo->TmInf.mtW._23  = z;
							pGeo->TmInf.mtW._24  = w;
						}

						if(0 == DgeStr_Strnicmp(sLine, Keywords[TM_ROW2].sKey, Keywords[TM_ROW2].iKey) )
						{
							FLOAT	x=0.F, y=0.F, z=0.F, w=0.F;
							sscanf(sLine, "%*s %f %f %f", &x, &y, &z);

							pGeo->TmInf.mtW._31  = x;
							pGeo->TmInf.mtW._32  = y;
							pGeo->TmInf.mtW._33  = z;
							pGeo->TmInf.mtW._34  = w;
						}

						if(0 == DgeStr_Strnicmp(sLine, Keywords[TM_ROW3].sKey, Keywords[TM_ROW3].iKey) )
						{
							FLOAT	x=0.F, y=0.F, z=0.F;
							FLOAT	w=1.F;
							sscanf(sLine, "%*s %f %f %f", &x, &y, &z);

							pGeo->TmInf.mtW._41  = x;
							pGeo->TmInf.mtW._42  = y;
							pGeo->TmInf.mtW._43  = z;
							pGeo->TmInf.mtW._44  = w;
						}

						if(0 == DgeStr_Strnicmp(sLine, Keywords[TM_POS].sKey, Keywords[TM_POS].iKey) )
						{
							FLOAT	x=0.F, y=0.F, z=0.F;
							sscanf(sLine, "%*s %f %f %f", &x, &y, &z);

							pGeo->TmInf.Px  = x;
							pGeo->TmInf.Py  = y;
							pGeo->TmInf.Pz  = z;
						}


						if(0 == DgeStr_Strnicmp(sLine, Keywords[TM_ROT].sKey, Keywords[TM_ROT].iKey) )
						{
							FLOAT	x=0.F, y=0.F, z=0.F;
							sscanf(sLine, "%*s %f %f %f", &x, &y, &z);

							pGeo->TmInf.Rx  = x;
							pGeo->TmInf.Ry  = y;
							pGeo->TmInf.Rz  = z;
						}

						if(0 == DgeStr_Strnicmp(sLine, Keywords[TM_RTA].sKey, Keywords[TM_RTA].iKey) )
						{
							FLOAT	w=0.F;
							sscanf(sLine, "%*s %f", &w);

							pGeo->TmInf.Rw  = w;
						}

						if(0 == DgeStr_Strnicmp(sLine, Keywords[TM_SCL].sKey, Keywords[TM_SCL].iKey) )
						{
							FLOAT	x=0.F, y=0.F, z=0.F;
							sscanf(sLine, "%*s %f %f %f", &x, &y, &z);

							pGeo->TmInf.Sx  = x;
							pGeo->TmInf.Sy  = y;
							pGeo->TmInf.Sz  = z;
						}

					}// while NODE_TM
				}


				if(0 == DgeStr_Strnicmp(sLine, Keywords[MESH_INFOS].sKey, Keywords[MESH_INFOS].iKey) )
				{
					while(!feof(fp))
					{
						fgets(sLine, MAX_PARSE_LINE, fp);
						LnStr_Trim(sLine);

						if('}' == sLine[0])
							break;

						if(0 == DgeStr_Strnicmp(sLine, Keywords[MESH_NUMVTX].sKey, Keywords[MESH_NUMVTX].iKey) )
						{
							INT		iNVx;
							sscanf(sLine, "%*s %d", &iNVx);

							pGeo->iNumVtx = iNVx;

							if(iNVx>0)
								pGeo->pLstVtx = new CDGX_Ast::_AsePos[iNVx];
						}

						if(0 == DgeStr_Strnicmp(sLine, Keywords[MESH_NUMFCE].sKey, Keywords[MESH_NUMFCE].iKey) )
						{
							INT		iNIx;
							sscanf(sLine, "%*s %d", &iNIx);

							pGeo->iNumFce = iNIx;

							if(iNIx>0)
								pGeo->pLstFce = new CDGX_Ast::AseFce[iNIx];
						}


						if(0 == DgeStr_Strnicmp(sLine, Keywords[MESH_VTXLST].sKey, Keywords[MESH_VTXLST].iKey) )
						{
							while(!feof(fp))
							{
								fgets(sLine, MAX_PARSE_LINE, fp);
								LnStr_Trim(sLine);

								if('}' == sLine[0])
									break;

								if(0 == DgeStr_Strnicmp(sLine, Keywords[MESH_VTXREC].sKey, Keywords[MESH_VTXREC].iKey) )
								{
									INT		nIdx=0;
									FLOAT	x=0.F, y=0.F, z=0.F;
									sscanf(sLine, "%*s %d %f %f %f", &nIdx, &x, &y, &z);

									pGeo->pLstVtx[nIdx].x = x;
									pGeo->pLstVtx[nIdx].y = y;
									pGeo->pLstVtx[nIdx].z = z;
								}

							}
						}

						if(0 == DgeStr_Strnicmp(sLine, Keywords[MESH_FCELST].sKey, Keywords[MESH_FCELST].iKey) )
						{
							while(!feof(fp))
							{
								fgets(sLine, MAX_PARSE_LINE, fp);
								LnStr_Trim(sLine);

								if('}' == sLine[0])
									break;

								if(0 == DgeStr_Strnicmp(sLine, Keywords[MESH_FCEREC].sKey, Keywords[MESH_FCEREC].iKey) )
								{
									INT		nIdx=0;
									INT		a=0, b=0, c=0;

									//            *MESH_FACE    0:    A:    0   B:    1   C:    2
									sscanf(sLine, "%*s         %d:   %*s   %d  %*s   %d  %*s   %d"
												, &nIdx, &a, &b, &c);

									pGeo->pLstFce[nIdx].a = a;
									pGeo->pLstFce[nIdx].b = b;
									pGeo->pLstFce[nIdx].c = c;
								}

							}// while
						}// if == MESH_FACE_LIST


						if(0 == DgeStr_Strnicmp(sLine, Keywords[MESH_NUMTVTX].sKey, Keywords[MESH_NUMTVTX].iKey) )
						{
							INT		iNtvtx;
							sscanf(sLine, "%*s %d", &iNtvtx);
							pGeo->iNumTvtx = iNtvtx;
							pGeo->pLstTvtx = new CDGX_Ast::_AseTvtx[iNtvtx];

						}// if == *MESH_NUMTVERTEX


						if(0 == DgeStr_Strnicmp(sLine, Keywords[MESH_TVTXLST].sKey, Keywords[MESH_TVTXLST].iKey) )
						{
							while(!feof(fp))
							{
								fgets(sLine, MAX_PARSE_LINE, fp);
								LnStr_Trim(sLine);

								if('}' == sLine[0])
									break;

								if(0 == DgeStr_Strnicmp(sLine, Keywords[MESH_TVTXREC].sKey, Keywords[MESH_TVTXREC].iKey) )
								{
									INT		nIdx=0;
									FLOAT	u=0.F, v=0.F, w=0.F;
									sscanf(sLine, "%*s %d %f %f %f", &nIdx, &u, &v, &w);

									pGeo->pLstTvtx[nIdx].u = u;


									//(E) 2009-07-27 Editor: AFEW
									pGeo->pLstTvtx[nIdx].v = v;
									pGeo->pLstTvtx[nIdx].w = w;
								}


							}// while
						}// if == *MESH_TVERTLIST {


						if(0 == DgeStr_Strnicmp(sLine, Keywords[MESH_NUMTFCE].sKey, Keywords[MESH_NUMTFCE].iKey) )
						{
							INT		iNtfce;
							sscanf(sLine, "%*s %d", &iNtfce);
							pGeo->iNumTfce = iNtfce;
							pGeo->pLstTfce = new CDGX_Ast::AseFce[iNtfce];

						}// if == *MESH_NUMTVFACES


						if(0 == DgeStr_Strnicmp(sLine, Keywords[MESH_TFCELST].sKey, Keywords[MESH_TFCELST].iKey) )
						{
							while(!feof(fp))
							{
								fgets(sLine, MAX_PARSE_LINE, fp);
								LnStr_Trim(sLine);

								if('}' == sLine[0])
									break;

								if(0 == DgeStr_Strnicmp(sLine, Keywords[MESH_TFCEREC].sKey, Keywords[MESH_TFCEREC].iKey) )
								{
									INT		nIdx=0;
									INT		a=0, b=0, c=0;

									sscanf(sLine, "%*s %d %d %d %d", &nIdx, &a, &b, &c);

									pGeo->pLstTfce[nIdx].a = a;
									pGeo->pLstTfce[nIdx].b = b;
									pGeo->pLstTfce[nIdx].c = c;
								}


							}// while
						}// if == *MESH_TFACELIST {
						

						// Normal Vector
						if(0 == DgeStr_Strnicmp(sLine, Keywords[MESH_NORMAL].sKey, Keywords[MESH_NORMAL].iKey) )
						{
//							pGeo->pLstNor = new CDGX_Ast::_AseNor[pGeo->iNumVtx];
//
							while(!feof(fp))
							{
								fgets(sLine, MAX_PARSE_LINE, fp);
								LnStr_Trim(sLine);

								if('}' == sLine[0])
									break;

							}// while

						}// if == *MESH_NORMALS {


						
					}// while
				}// if


				if(0 == DgeStr_Strnicmp(sLine, Keywords[TM_ANIMATION].sKey, Keywords[TM_ANIMATION].iKey) )
				{
					while(!feof(fp))
					{
						fgets(sLine, MAX_PARSE_LINE, fp);
						LnStr_Trim(sLine);

						if('}' == sLine[0])
							break;

						if(0 == DgeStr_Strnicmp(sLine, Keywords[ROT_TRACK].sKey, Keywords[ROT_TRACK].iKey) )
						{
							while(!feof(fp))
							{
								fgets(sLine, MAX_PARSE_LINE, fp);
								LnStr_Trim(sLine);

								if('}' == sLine[0])
									break;

							}// while
						}// if == *CONTROL_ROT_TRACK {


						if(0 == DgeStr_Strnicmp(sLine, Keywords[POS_TRACK].sKey, Keywords[POS_TRACK].iKey) )
						{
							while(!feof(fp))
							{
								fgets(sLine, MAX_PARSE_LINE, fp);
								LnStr_Trim(sLine);

								if('}' == sLine[0])
									break;

							}// while
						}// if == *CONTROL_SCALE_TRACK {

						if(0 == DgeStr_Strnicmp(sLine, Keywords[SCALE_TRACK].sKey, Keywords[SCALE_TRACK].iKey) )
						{
							while(!feof(fp))
							{
								fgets(sLine, MAX_PARSE_LINE, fp);
								LnStr_Trim(sLine);

								if('}' == sLine[0])
									break;

							}// while
						}// if == *CONTROL_POS_TRACK {


						if(0 == DgeStr_Strnicmp(sLine, Keywords[ROT_TCB].sKey, Keywords[ROT_TCB].iKey) )
						{
							while(!feof(fp))
							{
								fgets(sLine, MAX_PARSE_LINE, fp);
								LnStr_Trim(sLine);

								if('}' == sLine[0])
									break;

							}// while
						}// if == *CONTROL_ROT_TCB {


					}// while
				}// if == *TM_ANIMATION {

				

			}// while
		}// if

		
	}// while

	return DGE_OK;
}


INT CDGX_Ast::ParseAnimation(FILE* fp)
{
	// Scene 파싱
	char	sLine[MAX_PARSE_LINE];


	// 파일 포인터를 처음으로 옮긴다.
	fseek(fp, 0, SEEK_SET);



	while(!feof(fp))
	{
		fgets(sLine, MAX_PARSE_LINE, fp);
		LnStr_Trim(sLine);

		// TM_ANIMATION
		if(0 == DgeStr_Strnicmp(sLine, Keywords[TM_ANIMATION].sKey, Keywords[TM_ANIMATION].iKey) )
		{
			AseGeo* pGeo = NULL;

			while(!feof(fp))
			{
				fgets(sLine, MAX_PARSE_LINE, fp);
				LnStr_Trim(sLine);

				if('}' == sLine[0])
					break;

				// NODE_NAME
				if(0 == DgeStr_Strnicmp(sLine, Keywords[NODE_CUR].sKey, Keywords[NODE_CUR].iKey) )
				{
					char	sName[64];
					LnStr_Quot(sName, sLine);

					// Node의 이름과 같은 지오메트리를 찾는다.
					for(INT i=0; i<m_Info.nGeo; ++i)
					{
						AseGeo*	pGeoCur = &m_pGeo[i];

						if(0==DgeStr_Stricmp(pGeoCur->sNodeCur, sName))
						{
							pGeo = pGeoCur;
							break;
						}
					}


				}

				// CONTROL_POS_TRACK
				if(0 == DgeStr_Strnicmp(sLine, Keywords[POS_TRACK].sKey, Keywords[POS_TRACK].iKey) )
				{
					while(!feof(fp))
					{
						fgets(sLine, MAX_PARSE_LINE, fp);
						LnStr_Trim(sLine);

						if('}' == sLine[0])
							break;


						if(0 == DgeStr_Strnicmp(sLine, Keywords[POS_SAMPLE].sKey, Keywords[POS_SAMPLE].iKey) )
						{
							INT		nTrck;
							FLOAT	x=0.F, y=0.F, z=0.F;
							sscanf(sLine, "%*s %d %f %f %f", &nTrck, &x, &y, &z);

							nTrck /= m_Info.nFrmT;
							
							AseTrack	trck(nTrck, x, y, z, 0);
							pGeo->vTrs.push_back(trck);

						}// if

					}// while CONTROL_POS_TRACK
				}// if

				// CONTROL_ROT_TRACK
				if(0 == DgeStr_Strnicmp(sLine, Keywords[ROT_TRACK].sKey, Keywords[ROT_TRACK].iKey) )
				{
					while(!feof(fp))
					{
						fgets(sLine, MAX_PARSE_LINE, fp);
						LnStr_Trim(sLine);

						if('}' == sLine[0])
							break;


						if(0 == DgeStr_Strnicmp(sLine, Keywords[ROT_SAMPLE].sKey, Keywords[ROT_SAMPLE].iKey) )
						{
							DGXQUATERNION	q1;
							
							INT		nTrck;
							FLOAT	x=0.F, y=0.F, z=0.F, w=0.F;
							sscanf(sLine, "%*s %d %f %f %f %f", &nTrck, &x, &y, &z, &w);

							nTrck /= m_Info.nFrmT;

							q1.x = sinf(w/2.f) * x;
							q1.y = sinf(w/2.f) * y;
							q1.z = sinf(w/2.f) * z;
							q1.w = cosf(w/2.f);

							INT iSize = pGeo->vRot.size();

							if(0==iSize)
							{
								AseTrack	trck(nTrck, q1.x, q1.y, q1.z, q1.w);
								pGeo->vRot.push_back(trck);
							}
							else
							{
								DGXQUATERNION	q2;
								DGXQUATERNION	q3;

								AseTrack* ptrck = &pGeo->vRot[iSize-1];

								q2.x = ptrck->x;
								q2.y = ptrck->y;
								q2.z = ptrck->z;
								q2.w = ptrck->w;

								//D3DXQuaternionMultiply(&q3, &q2, &q1); ==> q3 = q1 * q2임 D3DXQuaternionMultiply함수는 오른손 법칙을 따름
								q3	= q2 * q1;		// <== Direc3D는 왼손 좌표계로 행렬을 오른쪽 방향으로 곱셈을 수행함. 따라서 q1이 먼저와야 한다.
								

								AseTrack	trck(nTrck, q3.x, q3.y, q3.z, q3.w);
								pGeo->vRot.push_back( trck );
							}

						}// if

					}// while CONTROL_ROT_TRACK
				}// if


				// CONTROL_SCALE_TRACK
				if(0 == DgeStr_Strnicmp(sLine, Keywords[SCALE_TRACK].sKey, Keywords[SCALE_TRACK].iKey) )
				{
					while(!feof(fp))
					{
						fgets(sLine, MAX_PARSE_LINE, fp);
						LnStr_Trim(sLine);

						if('}' == sLine[0])
							break;


						if(0 == DgeStr_Strnicmp(sLine, Keywords[SCALE_SAMPLE].sKey, Keywords[SCALE_SAMPLE].iKey) )
						{
							INT		nTrck;
							FLOAT	x=0.F, y=0.F, z=0.F;
							sscanf(sLine, "%*s %d %f %f %f", &nTrck, &x, &y, &z);

							nTrck /= m_Info.nFrmT;
							
							AseTrack	trck(nTrck, x, y, z, 0);
							pGeo->vScl.push_back(trck);

						}// if

					}// while CONTROL_SCALE_TRACK
				}// if


			}// while
		}// if TM_ANIMATION

		
	}// while

	return DGE_OK;
}




INT CDGX_Ast::SetupRenderData()
{
	INT i=0;
	INT j=0;

	// TM Processing
	// TmLocal = TmWorld * TmWorld(parent)-1

	for(i=0; i<m_Info.nGeo; ++i)
	{
		AseGeo*	pGeoCur = &m_pGeo[i];
		AseGeo*	pGeoPrn = NULL;

		// Find Parent
		for(j=0; j<m_Info.nGeo; ++j)
		{
			AseGeo*	pGeoT = &m_pGeo[j];

			if(0==DgeStr_Stricmp(pGeoCur->sNodePrn, pGeoT->sNodeCur))
			{
				pGeoPrn			= pGeoT;

				pGeoCur->nNodePrn= j;			//Setup Parent Index
				pGeoCur->pGeoPrn= pGeoT;		//Setup Parent Pointer
				break;
			}
		}

		if(pGeoPrn)
		{
			DGXMATRIX mtPrn = pGeoPrn->TmInf.mtW;
			DGXMATRIX mtPrnI;
			DGXMATRIX mtL;
			mtPrnI.Inverse(&mtPrn);
			
			pGeoCur->TmInf.mtL = pGeoCur->TmInf.mtW * mtPrnI;
		}
		else
		{
			pGeoCur->TmInf.mtL = pGeoCur->TmInf.mtW;
		}
	}

	// Vertex Inversion
	// v(local) = v(world)*TmWorld-1
	for(i=0; i<m_Info.nGeo; ++i)
	{
		AseGeo*	pGeoCur = &m_pGeo[i];

		DGXMATRIX mtWI;
		mtWI.Inverse(&pGeoCur->TmInf.mtW);
	
		INT		iNvtx = pGeoCur->iNumVtx;

		for(j=0; j<iNvtx; ++j)
		{
			DGXVECTOR3 vcI = *((DGXVECTOR3*)&(pGeoCur->pLstVtx[j]));
			DGXVECTOR3 vcO;

			mtWI.TransformCoord(&vcO, &vcI);

			*((DGXVECTOR3*)&(pGeoCur->pLstVtx[j])) = vcO;
		}
	}




	// Setup FVF
	for(i=0; i<m_Info.nGeo; ++i)
	{
		AseGeo*	pGeo = &m_pGeo[i];
		INT		iTfce = pGeo->iNumTfce;
		INT		nMtrl = pGeo->nMtlRef;

		if(pGeo->pLstVtx)
			pGeo->m_dFVF = AseVtx::FVF;
	
//		if(pGeo->pLstNor)
//			pGeo->m_dFVF |= DGE_FVF_NORMAL;

		if(iTfce >0 && nMtrl>=0)
			pGeo->m_dFVF |= DGE_FVF_TEX1;
	}

	// Setup Stride
	for(i=0; i<m_Info.nGeo; ++i)
	{
		AseGeo*	pGeo = &m_pGeo[i];
		
		if(pGeo->m_dFVF == (DWORD)AseVtx::FVF)
			pGeo->m_dVtx = sizeof(AseVtx);

//		else if(pGeo->m_dFVF == (DWORD)AseVtxN::FVF)
//			pGeo->m_dVtx = sizeof(AseVtxN);

		else if(pGeo->m_dFVF == (DWORD)AseVtxUV::FVF)
			pGeo->m_dVtx = sizeof(AseVtxUV);

//		else if(pGeo->m_dFVF == (DWORD)AseVtxNUV::FVF)
//			pGeo->m_dVtx = sizeof(AseVtxNUV);
	}


	// Setup Index Data and Vertex Number
	for(i=0; i<m_Info.nGeo; ++i)
	{
		AseGeo*	pGeo = &m_pGeo[i];

		if(pGeo->m_dFVF == (DWORD)AseVtx::FVF)	// || pGeo->m_dFVF == (DWORD)AseVtxN::FVF)
		{
			pGeo->m_iNvx	= pGeo->iNumVtx;	// 정점의 수
			pGeo->m_iFce	= pGeo->iNumFce;
			pGeo->m_pIdx	= new AseFce[pGeo->m_iFce];
			memcpy(pGeo->m_pIdx, pGeo->pLstFce, pGeo->m_iFce * sizeof(AseFce));
		}
		else if(pGeo->m_dFVF == (DWORD)AseVtxUV::FVF)	// || pGeo->m_dFVF == (DWORD)AseVtxNUV::FVF)
		{
			pGeo->m_iNvx	= pGeo->iNumTvtx;	// UV의 수
			pGeo->m_iFce	= pGeo->iNumTfce;
			pGeo->m_pIdx	= new AseFce[pGeo->m_iFce];
			memcpy(pGeo->m_pIdx, pGeo->pLstTfce, pGeo->m_iFce * sizeof(AseFce));


			// 인덱스 지정
			for(j=0; j<pGeo->m_iFce; ++j)
			{
				// 정점위치의 인덱스
				INT Va = pGeo->pLstFce[j].a;
				INT Vb = pGeo->pLstFce[j].b;
				INT Vc = pGeo->pLstFce[j].c;

				// UV의 인덱스
				INT Ta = pGeo->pLstTfce[j].a;
				INT Tb = pGeo->pLstTfce[j].b;
				INT Tc = pGeo->pLstTfce[j].c;

				// Tvtx인덱스에 있는 정점의 인덱스를 지정
				pGeo->pLstTvtx[Ta].nT = Va;
				pGeo->pLstTvtx[Tb].nT = Vb;
				pGeo->pLstTvtx[Tc].nT = Vc;
			}
		}
	}
	

	// Setup Vertex Buffer
	for(i=0; i<m_Info.nGeo; ++i)
	{
		AseGeo*	pGeo = &m_pGeo[i];

		if(pGeo->m_dFVF == (DWORD)AseVtx::FVF)
		{
			AseVtx* pVtx = new AseVtx[pGeo->m_iNvx];
			memcpy( pVtx, pGeo->pLstVtx, pGeo->m_iNvx * pGeo->m_dVtx);
			pGeo->m_pVtx = pVtx;
		}

//		if(pGeo->m_dFVF == (DWORD)AseVtxN::FVF)
//		{
//			AseVtxN* pVtx = new AseVtxN[pGeo->m_iNvx];
//
//			for(j=0; j<pGeo->m_iNvx; ++j)
//			{
//				pVtx[j].p.x = pGeo->pLstVtx[j].x;
//				pVtx[j].p.y = pGeo->pLstVtx[j].y;
//				pVtx[j].p.z = pGeo->pLstVtx[j].z;
//
//				pVtx[j].n.x = pGeo->pLstNor[j].x;
//				pVtx[j].n.y = pGeo->pLstNor[j].y;
//				pVtx[j].n.z = pGeo->pLstNor[j].z;
//			}
//
//			pGeo->m_pVtx = pVtx;
//		}

		else if(pGeo->m_dFVF == (DWORD)AseVtxUV::FVF)
		{
			AseVtxUV* pVtx = new AseVtxUV[pGeo->m_iNvx];

			// 인덱스를 통한 정점 설정
			for(j=0; j<pGeo->m_iNvx; ++j)
			{
				INT nT = pGeo->pLstTvtx[j].nT ;

				pVtx[j].p.x = pGeo->pLstVtx[nT].x;
				pVtx[j].p.y = pGeo->pLstVtx[nT].y;
				pVtx[j].p.z = pGeo->pLstVtx[nT].z;

				pVtx[j].u = pGeo->pLstTvtx[j].u;
				pVtx[j].v = pGeo->pLstTvtx[j].v;
			}

			pGeo->m_pVtx = pVtx;
		}

//		else if(pGeo->m_dFVF == (DWORD)AseVtxNUV::FVF)
//		{
//			AseVtxNUV* pVtx = new AseVtxNUV[pGeo->m_iNvx];
//
//			// 인덱스를 통한 정점 설정
//			for(j=0; j<pGeo->m_iNvx; ++j)
//			{
//				INT nT = pGeo->pLstTvtx[j].nT ;
//
//				pVtx[j].p.x = pGeo->pLstVtx[nT].x;
//				pVtx[j].p.y = pGeo->pLstVtx[nT].y;
//				pVtx[j].p.z = pGeo->pLstVtx[nT].z;
//
//				pVtx[j].n.x = pGeo->pLstNor[nT].x;
//				pVtx[j].n.y = pGeo->pLstNor[nT].y;
//				pVtx[j].n.z = pGeo->pLstNor[nT].z;
//
//				pVtx[j].u = pGeo->pLstTvtx[j].u;
//				pVtx[j].v = pGeo->pLstTvtx[j].v;
//			}
//
//			pGeo->m_pVtx = pVtx;
//		}
	}


	// Delete List Data
	for(i=0; i<m_Info.nGeo; ++i)
	{
		AseGeo*	pGeo = &m_pGeo[i];

		if(pGeo->pLstVtx)		delete [] pGeo->pLstVtx;
//		if(pGeo->pLstNor)		delete [] pGeo->pLstNor;
		if(pGeo->pLstFce)		delete [] pGeo->pLstFce;
		if(pGeo->pLstTvtx)		delete [] pGeo->pLstTvtx;
		if(pGeo->pLstTfce)		delete [] pGeo->pLstTfce;

		pGeo->iNumVtx	= 0;
		pGeo->iNumFce	= 0;

		pGeo->iNumTvtx	= 0;
		pGeo->iNumTfce	= 0;

		pGeo->pLstVtx	= NULL;
//		pGeo->pLstNor	= NULL;
		pGeo->pLstFce	= NULL;
		pGeo->pLstTvtx	= NULL;
		pGeo->pLstTfce	= NULL;
	}



	// Setup Matrix
	for(i=0; i<m_Info.nGeo; ++i)
	{
		AseGeo*		pGeo = &m_pGeo[i];
		pGeo->mtW = pGeo->TmInf.mtW;
		pGeo->mtL = pGeo->TmInf.mtL;
	}



	// Setup Texture
	DWORD	dColorKey		= 0xFF000000;

	for(i=0; i<m_Info.nMtl; ++i)
	{
		AseMtl*		pMtl = &m_pMtl[i];

		if(strlen(pMtl->sTex) <3)
			continue;

		char sFile	[DGE_MAX_PATH ]={0};
		char drive	[DGE_MAX_DRIVE]={0};
		char dir	[DGE_MAX_DIR  ]={0};
		char fname	[DGE_MAX_FNAME]={0};
		char ext	[DGE_MAX_EXT  ]={0};

		DgeStr_SplitPath( m_sFile, drive, dir, fname, ext );

		sprintf(sFile, "%s%s", dir, pMtl->sTex);


		PDGE_TEXTURE	pTex = NULL;
		if(DGE_FAILED(DGE_CreateTexture(NULL, &pTex, (DGE_HANDLE)sFile, &dColorKey)))
		{
			printf("Cannot Read Model Texture: %s\n", sFile);
			return DGE_ECANNOTFIND_RESOURCE;
		}

		pMtl->pTex = pTex;
	}


	return DGE_OK;

}




void CDGX_Ast::Confirm()
{
	FILE*	fp;
	INT		i=0;

	char sCrnf	[DGE_MAX_FNAME]={0};
	char dir	[DGE_MAX_DIR  ]={0};
	char fname	[DGE_MAX_FNAME]={0};
	
	DgeStr_SplitPath(m_sFile, NULL, dir, fname, NULL);

	sprintf(sCrnf, "%s%sCnf.txt", dir, fname);

	fp= fopen(sCrnf, "wt");

	if(NULL == fp)
		return;

//
//	fprintf(fp, "%s\n", Keywords[MTRL_LST].sKey);
//	fprintf(fp, "	%s	%d\n", Keywords[MTRL_CNT].sKey, m_nMtl);
//
//	for(i=0; i<m_nMtl; ++i)
//	{
//		fprintf(fp, "	%s %d {\n", Keywords[MTRL_INF].sKey, i);
//		fprintf(fp, "		%s\n", Keywords[MTRL_MAPDIF].sKey);
//		
//		fprintf(fp, "			%s	\"%s\"\n", Keywords[MTRL_TEXDIF].sKey, m_pMtl[i].sTex);
//	
//		fprintf(fp, "		}\n");
//		fprintf(fp, "	}\n\n");
//	}
//	fprintf(fp, "}\n\n");

	

	// Geometry
	for(i=0; i<m_Info.nGeo; ++i)
	{
		AseGeo*	pGeo = &m_pGeo[i];

		fprintf(fp, "%s\n", Keywords[GEOOBJECT].sKey);
		fprintf(fp, "	%s	\"%s\"\n", Keywords[NODE_CUR].sKey, pGeo->sNodeCur);
		fprintf(fp, "	%s	\"%s\"\n", Keywords[NODE_PRN].sKey, pGeo->sNodePrn);
//		fprintf(fp, "	%s\n", Keywords[MESH_INFOS].sKey);
//		
//		fprintf(fp, "		%s	%d\n", Keywords[MESH_NUMVTX].sKey, pGeo->iNumVtx);
//		fprintf(fp, "		%s	%d\n", Keywords[MESH_NUMFCE].sKey, pGeo->iNumFce);
//
//		fprintf(fp, "		%s\n"	, Keywords[MESH_VTXLST].sKey);
//
//
//		INT iNumVtx = pGeo->iNumVtx;
//
//		for(j=0; j<iNumVtx; ++j)
//		fprintf(fp, "			%s	%f	%f	%f\n", Keywords[MESH_VTXREC].sKey
//										, pGeo->pLstVtx[j].x
//										, pGeo->pLstVtx[j].y
//										, pGeo->pLstVtx[j].z);
//
//		fprintf(fp, "		}\n\n");
//		
//		fprintf(fp, "		%s\n"	, Keywords[MESH_FCELST].sKey);
//
//		INT iNumFce = pGeo->iNumFce;
//
//		for(j=0; j<iNumFce; ++j)
//		fprintf(fp, "			%s	%u	%u	%u\n", Keywords[MESH_FCEREC].sKey
//										, pGeo->pLstFce[j].a
//										, pGeo->pLstFce[j].b
//										, pGeo->pLstFce[j].c);
//
//		fprintf(fp, "		}\n");
//
//		fprintf(fp, "	}\n");

		fprintf(fp, "}\n\n");
	}
	
	
	fclose(fp);
}




void LnStr_Trim(char* sBuf)
{
	INT iLen = 0;

	INT	i=0;
	INT iCnt=0;

	iLen = strlen(sBuf);

	if(iLen <1)
		return;


	// 문자 \r \n제거
	for(i=iLen-1; i>=0; --i)
	{
		char* p = sBuf + i;

		if( '\n' == *p || '\r' == *p)
		{
			*(sBuf + i) = '\0';
		}

		++iCnt;

		if(iCnt>2)
			break;
	}


	// 우측의 공백 제거
	iCnt = 0;
	iLen = strlen(sBuf);

	for(i=iLen-1; i>=0; --i)
	{
		char* p = sBuf + i;

		if( ' ' == *p || '\t' == *p)
			continue;

		*(sBuf + i+1) = '\0';
		break;
	}

	iLen = i+1 +1;

	// 좌측의 공백제거
	char sT[1024]={0};

	strncpy(sT, sBuf, iLen);
	
	for(i=0; i < iLen; ++i)
	{
		char* p = sT + i;

		if( ' ' == *p || '\t' == *p)
			continue;

		break;
	}

	strcpy(sBuf, sT+i);
}



void LnStr_Quot(char* sDst, const char* sSrc)
{
	INT	nBgn  =-1;
	INT bStrt =0;

	char* p = (char*)sSrc;

	while( 0 != *p)
	{
		if( '\"' == *p && 0 == bStrt)
			bStrt = 1;

		else if( '\"' == *p && 1 == bStrt)
		{
			*(sDst + nBgn) = 0;
			break;
		}

		if(nBgn>=0 && 1== bStrt)
			*(sDst + nBgn) = *p;

		if(1== bStrt)
			++nBgn;

		++p;
	}
}




