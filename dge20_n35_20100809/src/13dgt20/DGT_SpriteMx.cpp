// Implementation of the IDGT_SpriteMx.
//
////////////////////////////////////////////////////////////////////////////////


#include <vector>

#include <gles/gl.h>

#include <DGE_Math.h>

#include <DGE_Base.h>

#include "../11dge20/DGE_Texture.h"
#include "DGT_SpriteMx.h"


using namespace std;


class CDGT_SpriteMx : public IDGT_SpriteMx
{
public:
	struct TDGT_LAYER_QUAD
	{
		DGXVECTOR2 	p;		// Position
		DGXVECTOR2 	t;		// Texture
	};

	struct TDGT_LAYER
	{
		PDGE_TEXTURE		pTex;

		vector<DGXVECTOR2 >	vVtxP;		// Position
		vector<DGXCOLORb  >	vVtxC;		// Color
		vector<DGXVECTOR2 >	vVtxT;		// Texture

		TDGT_LAYER() : pTex(NULL){}
		TDGT_LAYER(PDGE_TEXTURE _pTex) : pTex(_pTex){}

		void AddQuad(DGXVECTOR2* p, DGXVECTOR2* t, DGXCOLORb c)		// 사각형 이미지 영역을 받아서 6개의 정점을 생성.
		{
			TDGT_LAYER_QUAD	vtx[6];

 			vtx[0].p = p[0];	vtx[0].t = t[0];
			vtx[1].p = p[1];	vtx[1].t = t[1];
			vtx[2].p = p[2];	vtx[2].t = t[2];
			vtx[3].p = p[0];	vtx[3].t = t[0];
			vtx[4].p = p[2];	vtx[4].t = t[2];
			vtx[5].p = p[3];	vtx[5].t = t[3];

			for(int i=0; i<6; ++i)
			{
				vVtxP.push_back(vtx[i].p);
				vVtxC.push_back(c);
				vVtxT.push_back(vtx[i].t);
			}
		}
	};

protected:
	IDGE_Device*	m_pDev;

	FLOAT			m_fScnW;
	FLOAT			m_fScnH;

	FLOAT			m_mtPrj[20];								// 3D 환경의 Projection 행렬
	FLOAT			m_mtViw[20];								// 3D 환경의 View 행렬

	std::vector<TDGT_LAYER >	m_vLayer;

public:
	CDGT_SpriteMx();
	virtual ~CDGT_SpriteMx();

	virtual INT		Begin(DWORD dMode=0);						// 2D 렌더링 전에 3D 파이프라인의 환경을 저장
	virtual INT		End();										// 3D 환경을 복원


	// Assemble and Construction Layer. 색상과 위치만 설정할
	virtual INT		Add(										// 무조건 레이어 추가. 만약 마지막 텍스어와 추가되는 텍스처 같으면 마지막 텍스처에 이미지 영역을 추가.
								PDGE_TEXTURE		pTexture	// 텍스처 포인터
							,	const DGE_RECT*		pImgRc		// Image rect
							,	const DGE_FLOAT2*	 vcTrn		// Position
							,	const DGE_COLORF*	Color=NULL	// color
						);

	virtual INT		AddEx(
								PDGE_TEXTURE		pTexture	// DGE_Texture Pointer
							,	const DGE_RECT*		pImgRc		// Image rect
							,	const DGE_FLOAT2*	vcScl		// Scaling
							,	const DGE_FLOAT2*	vcRot		// Rotation Center
							,	FLOAT				fRot		// Angle(Radian)
							,	const DGE_FLOAT2*	vcTrn		// Position
							,	const DGE_COLORF*	Color=NULL	// color
						);



	virtual INT		AddtoExist(									// 추가되는 텍스처가 이미 존재한다면 해당 텍스처에 이미지 영역을 추가함. 없다면 새로 만듦
								PDGE_TEXTURE		pTexture	// DGE_Texture Pointer
							,	const DGE_RECT*		pImgRc		// Image rect
							,	const DGE_FLOAT2*	 vcTrn		// Position
							,	const DGE_COLORF*	Color=NULL	// color
							);

	virtual INT		AddtoExistEx(
								PDGE_TEXTURE		pTexture	// DGE_Texture Pointer
							,	const DGE_RECT*		pImgRc		// Image rect
							,	const DGE_FLOAT2*	vcScl		// Scaling
							,	const DGE_FLOAT2*	vcRot		// Rotation Center
							,	FLOAT				fRot		// Angle(Radian)
							,	const DGE_FLOAT2*	vcTrn		// Position
							,	const DGE_COLORF*	Color=NULL	// color
							);


	// Draw 2D..
	virtual INT		DrawLayer(INT nFirstL=0, INT nLastL=-1);	// if nFirstL=0 and nLastL=-1 then Draw All Layers
	virtual INT		DrawLayer(PDGE_TEXTURE pTexture);			// pTexture와 일치하는 모든 레이어를 그린다.

	virtual	INT		Clear();									// vector 자료구조를 clear

public:
	INT		Create(DGE_HANDLE =NULL, DGE_HANDLE =NULL, DGE_HANDLE =NULL, DGE_HANDLE =NULL);
	void	Destroy();

protected:
	INT		FindLayler(PDGE_TEXTURE pTex);
	INT		DrawLayerIndex(INT nIdx);
};



CDGT_SpriteMx::CDGT_SpriteMx()
{
	m_pDev	= NULL;

	m_fScnW	= 320.F;
	m_fScnH	= 240.F;
}


CDGT_SpriteMx::~CDGT_SpriteMx()
{
	Destroy();
}


void CDGT_SpriteMx::Destroy()
{
	m_pDev = NULL;

	this->Clear();
}


INT CDGT_SpriteMx::Create(DGE_HANDLE p1, DGE_HANDLE, DGE_HANDLE, DGE_HANDLE)
{
	if(NULL == p1)
		return DGE_EINVALIDATE_CALL;

	m_pDev = (IDGE_Device*)p1;


	// 뷰포트에서 화면의 크기를 얻는다.
	FLOAT f[4]={0};
	glGetFloatv(GL_VIEWPORT, f);

	m_fScnW = f[2];
	m_fScnH = f[3];

	return DGE_OK;
}


INT CDGT_SpriteMx::Begin(DWORD dMode)
{
	glGetFloatv(GL_PROJECTION_MATRIX, (GLfloat*)m_mtPrj);
	glGetFloatv(GL_MODELVIEW_MATRIX, (GLfloat*)m_mtViw);
	glMatrixMode(GL_PROJECTION);	glLoadIdentity();

	glOrthof(	0.0000F, m_fScnW
			  , m_fScnH, 0.0000F
			  , 0.0000F, 1.0000F );


	glMatrixMode(GL_MODELVIEW);		glLoadIdentity();


	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE );
	glDisable(GL_LIGHTING);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_TEXTURE_2D);

	
	glActiveTexture(GL_TEXTURE0);
	glClientActiveTexture(GL_TEXTURE0);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);


	return DGE_OK;
}


INT CDGT_SpriteMx::End()
{
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);


	glMatrixMode(GL_PROJECTION);	glLoadMatrixf(m_mtPrj);
	glMatrixMode(GL_MODELVIEW);		glLoadMatrixf(m_mtViw);

	glColor4f(1.F, 1.F, 1.F, 1.F);

	return DGE_OK;
}



// 무조건 레이어 추가. 단, 마지막 레이어의 텍스처와 새로 입력되는 텍스처가 같다면 이 레이어에 추가.
INT CDGT_SpriteMx::Add(IDGE_Texture*	pTexture	// DGE_Texture Pointer
					, const DGE_RECT*	pImgRc		// Image rect
					, const DGE_FLOAT2* pvcTrn		// Position
					, const DGE_COLORF*	pColor		// color
					)
{
	FLOAT	ImgW = 0;
	FLOAT	ImgH = 0;
	UINT	nTex = 0;

	if(NULL == pTexture)
		return DGE_ECANNOTFIND_RESOURCE;


	ImgW = (FLOAT)pTexture->GetImgW();
	ImgH = (FLOAT)pTexture->GetImgH();
	nTex = pTexture->GetId();

	if(0==nTex)
		return DGE_ECANNOTFIND_RESOURCE;




	// 크기를 레이어로 설정한다.
	INT	nLayer = m_vLayer.size();

	// 어떤 레이어도 없으면 새로 레이어를 추가.
	if(0==nLayer)
	{
		TDGT_LAYER	tLayer(pTexture);
		this->m_vLayer.push_back(tLayer);
	}
	else
	{
		// 인덱스를 마지막 레이어(size - 1)로 정한다.
		--nLayer;

		// 마지막 레이어의 텍스처와 비교해서 같지 않으면 레이어를 추가하고 인덱스를 올린다.
		if(pTexture != m_vLayer[nLayer].pTex)
		{
			TDGT_LAYER	tLayer(pTexture);
			this->m_vLayer.push_back(tLayer);

			++nLayer;
		}
	}



	FLOAT	DrwL=  0;	// Draw Region Left
	FLOAT	DrwT=  0;	// Draw Region Top
	FLOAT	DrwW=ImgW;	// Draw Region Width
	FLOAT	DrwH=ImgH;	// Draw Region Height

	DGXVECTOR2	pos[4];
	DGXVECTOR2	st0(0,0);
	DGXVECTOR2	st1(1,1);


	// 이미지 영역 설정
	if(pImgRc)
	{
		DrwL = FLOAT(pImgRc->left);
		DrwT = FLOAT(pImgRc->top );
		DrwW = FLOAT(pImgRc->right - pImgRc->left);
		DrwH = FLOAT(pImgRc->bottom- pImgRc->top );
	}


	// 이미지에 해당하는 텍스처 ST 설정
	if(DrwW > ImgW)		DrwW = ImgW;
	if(DrwH > ImgH)		DrwH = ImgH;

	st0.x = (DrwL +    0)/ImgW;
	st1.x = (DrwL + DrwW)/ImgW;
	st0.y = (ImgH - DrwT -    0)/ImgH;
	st1.y = (ImgH - DrwT - DrwH)/ImgH;



	// 화면에 대한 위치 설정
	if(pvcTrn)
	{
		pos[0].x = pvcTrn->x;
		pos[0].y = pvcTrn->y;
	}
	else
	{
		pos[0].x = 0;
		pos[0].y = 0;
	}

	// Setup Postion
	pos[1] = pos[0] + DGXVECTOR2(DrwW,    0);
	pos[2] = pos[0] + DGXVECTOR2(DrwW, DrwH);
	pos[3] = pos[0] + DGXVECTOR2(   0, DrwH);



	// 마지막으로 4개의 정점을 생성하고 색상 텍스처 ST를 설정
	DGXVECTOR2	tVtxPos[4];	// Position
	DGXVECTOR2	tVtxTex[4];	// Texture Coordinate
	DGXCOLORb	tVtxCol((DWORD)0XFFFFFFFF);

	tVtxPos[0] = DGXVECTOR2(pos[0]);
	tVtxPos[1] = DGXVECTOR2(pos[1]);
	tVtxPos[2] = DGXVECTOR2(pos[2]);
	tVtxPos[3] = DGXVECTOR2(pos[3]);
	
	tVtxTex[0] = DGXVECTOR2(st0.x, st0.y);
	tVtxTex[1] = DGXVECTOR2(st1.x, st0.y);
	tVtxTex[2] = DGXVECTOR2(st1.x, st1.y);
	tVtxTex[3] = DGXVECTOR2(st0.x, st1.y);


	// 색상
	if(pColor)
	{
		DWORD d = DGXCOLOR(*pColor);
		tVtxCol = d;
	}


	// Layer에 추가
	m_vLayer[nLayer].AddQuad(tVtxPos, tVtxTex, tVtxCol);


	return DGE_OK;
}


INT CDGT_SpriteMx::AddEx(IDGE_Texture*	pTexture	// DGE_Texture Pointer
					, const DGE_RECT*	pImgRc		// Image rect
					, const DGE_FLOAT2*	pvcScl		// Scaling
					, const DGE_FLOAT2*	pvcRot		// Rotation Center
					, FLOAT				fRot		// Angle(Radian)
					, const DGE_FLOAT2* pvcTrn		// Position
					, const DGE_COLORF*	pColor		// color
					)
{
	FLOAT	ImgW = 0;
	FLOAT	ImgH = 0;
	UINT	nTex = 0;

	if(NULL == pTexture)
		return DGE_ECANNOTFIND_RESOURCE;


	ImgW = (FLOAT)pTexture->GetImgW();
	ImgH = (FLOAT)pTexture->GetImgH();
	nTex = pTexture->GetId();

	if(0==nTex)
		return DGE_ECANNOTFIND_RESOURCE;




	// 크기를 레이어로 설정한다.
	INT	nLayer = m_vLayer.size();

	// 어떤 레이어도 없으면 새로 레이어를 추가.
	if(0==nLayer)
	{
		TDGT_LAYER	tLayer(pTexture);
		this->m_vLayer.push_back(tLayer);
	}
	else
	{
		// 인덱스를 마지막 레이어(size - 1)로 정한다.
		--nLayer;

		// 마지막 레이어의 텍스처와 비교해서 같지 않으면 레이어를 추가하고 인덱스를 올린다.
		if(pTexture != m_vLayer[nLayer].pTex)
		{
			TDGT_LAYER	tLayer(pTexture);
			this->m_vLayer.push_back(tLayer);

			++nLayer;
		}
	}



	FLOAT	DrwL=  0;	// Draw Region Left
	FLOAT	DrwT=  0;	// Draw Region Top
	FLOAT	DrwW=ImgW;	// Draw Region Width
	FLOAT	DrwH=ImgH;	// Draw Region Height

	DGXVECTOR2	pos[4];
	DGXVECTOR2	st0(0,0);
	DGXVECTOR2	st1(1,1);


	// Final Data
	DGXVECTOR2	tVtxPos[4];	// Position
	DGXVECTOR2	tVtxTex[4];	// Texture Coordinate
	DGXCOLORb	tVtxCol((DWORD)0XFFFFFFFF);


	// Draw Region Width, Height
	if(pImgRc)
	{
		DrwL = FLOAT(pImgRc->left);
		DrwT = FLOAT(pImgRc->top );
		DrwW = FLOAT(pImgRc->right - pImgRc->left);
		DrwH = FLOAT(pImgRc->bottom- pImgRc->top );
	}


	// Setup UV
	if(DrwW > ImgW)		DrwW = ImgW;
	if(DrwH > ImgH)		DrwH = ImgH;

	st0.x = (DrwL +    0)/ImgW;
	st1.x = (DrwL + DrwW)/ImgW;
	st0.y = (ImgH - DrwT -    0)/ImgH;
	st1.y = (ImgH - DrwT - DrwH)/ImgH;



	// Setup Draw Position
	if(pvcTrn)
	{
		pos[0].x = pvcTrn->x;
		pos[0].y = pvcTrn->y;
	}
	else
	{
		pos[0].x = 0;
		pos[0].y = 0;
	}


	
	// Setup Postion
	if(NULL == pvcScl)
	{
		pos[1] = pos[0] + DGXVECTOR2(DrwW,     0);
		pos[2] = pos[0] + DGXVECTOR2(DrwW, DrwH);
		pos[3] = pos[0] + DGXVECTOR2(    0, DrwH);
	}

	else
	{
		FLOAT	fSclX = pvcScl->x;
		FLOAT	fSclY = pvcScl->y;

		if(fSclX>=0)
		{
			pos[1].x = pos[0].x + DrwW * fSclX;
			pos[2].x = pos[1].x;
			pos[3].x = pos[0].x;
		}
		else
		{
			pos[1].x = pos[0].x;
			pos[2].x = pos[1].x;
			pos[0].x = pos[1].x - DrwW * fSclX;
			pos[3].x = pos[0].x;
		}


		if(fSclY>=0)
		{
			pos[1].y = pos[0].y;
			pos[3].y = pos[0].y + DrwH * fSclY;
			pos[2].y = pos[3].y;			
		}
		else
		{
			pos[3].y = pos[0].y;
			pos[2].y = pos[3].y;
			pos[0].y = pos[3].y - DrwH * fSclY;
			pos[1].y = pos[0].y;
		}
	}


	// 회전 적용
	if(pvcRot)
	{
		DGXVECTOR2 vcR = DGXVECTOR2(pvcRot->x, pvcRot->y);
		DGXVECTOR2 d(0,0);

		FLOAT	fCos = (FLOAT)cos(-fRot);
		FLOAT	fSin = (FLOAT)sin(-fRot);

		for(INT i=0; i<4; ++i)
		{
			DGXVECTOR2 vcT = pos[i] - vcR;

			d.x = vcT.x * fCos + vcT.y * fSin;
			d.y =-vcT.x * fSin + vcT.y * fCos;

			tVtxPos[i].x = (vcR.x + d.x);
			tVtxPos[i].y = (vcR.y + d.y);
		}
	}
	else
	{
		tVtxPos[0] = DGXVECTOR2(pos[0]);
		tVtxPos[1] = DGXVECTOR2(pos[1]);
		tVtxPos[2] = DGXVECTOR2(pos[2]);
		tVtxPos[3] = DGXVECTOR2(pos[3]);
	}
	
	tVtxTex[0] = DGXVECTOR2(st0.x, st0.y);
	tVtxTex[1] = DGXVECTOR2(st1.x, st0.y);
	tVtxTex[2] = DGXVECTOR2(st1.x, st1.y);
	tVtxTex[3] = DGXVECTOR2(st0.x, st1.y);




	// 색상
	if(pColor)
	{
		DWORD d = DGXCOLOR(*pColor);
		tVtxCol = d;
	}


	// Layer에 추가
	m_vLayer[nLayer].AddQuad(tVtxPos, tVtxTex, tVtxCol);


	return DGE_OK;
}



INT CDGT_SpriteMx::AddtoExist(IDGE_Texture*	pTexture	// DGE_Texture Pointer
					, const DGE_RECT*	pImgRc		// Image rect
					, const DGE_FLOAT2* pvcTrn		// Position
					, const DGE_COLORF*	pColor		// color
					)
{
	FLOAT	ImgW = 0;
	FLOAT	ImgH = 0;
	UINT	nTex = 0;

	if(NULL == pTexture)
		return DGE_ECANNOTFIND_RESOURCE;


	ImgW = (FLOAT)pTexture->GetImgW();
	ImgH = (FLOAT)pTexture->GetImgH();
	nTex = pTexture->GetId();

	if(0==nTex)
		return DGE_ECANNOTFIND_RESOURCE;


	INT	nLayer = FindLayler(pTexture);

	if(-1==nLayer)
	{
		nLayer = m_vLayer.size();

		TDGT_LAYER	tLayer(pTexture);
		this->m_vLayer.push_back(tLayer);
	}

	FLOAT	DrwL=  0;	// Draw Region Left
	FLOAT	DrwT=  0;	// Draw Region Top
	FLOAT	DrwW=ImgW;	// Draw Region Width
	FLOAT	DrwH=ImgH;	// Draw Region Height

	DGXVECTOR2	pos[4];
	DGXVECTOR2	st0(0,0);
	DGXVECTOR2	st1(1,1);


	// Draw Region Width, Height
	if(pImgRc)
	{
		DrwL = FLOAT(pImgRc->left);
		DrwT = FLOAT(pImgRc->top );
		DrwW = FLOAT(pImgRc->right - pImgRc->left);
		DrwH = FLOAT(pImgRc->bottom- pImgRc->top );
	}

	// Setup UV
	st0.x = (DrwL +    0)/ImgW;
	st1.x = (DrwL + DrwW)/ImgW;
	st0.y = 1.0F - (DrwT +    0)/ImgH;
	st1.y = 1.0F - (DrwT + DrwH)/ImgH;

	// Setup Draw Position
	if(pvcTrn)
	{
		pos[0].x = pvcTrn->x;
		pos[0].y = pvcTrn->y;
	}
	else
	{
		pos[0].x = 0;
		pos[0].y = 0;
	}

	// Setup Postion
	pos[1] = pos[0] + DGXVECTOR2(DrwW,    0);
	pos[2] = pos[0] + DGXVECTOR2(DrwW, DrwH);
	pos[3] = pos[0] + DGXVECTOR2(   0, DrwH);


	// Final...
	DGXVECTOR2	tVtxPos[4];	// Position
	DGXVECTOR2	tVtxTex[4];	// Texture Coordinate
	DGXCOLORb	tVtxCol((DWORD)0XFFFFFFFF);

	tVtxPos[0] = DGXVECTOR2(pos[0]);
	tVtxPos[1] = DGXVECTOR2(pos[1]);
	tVtxPos[2] = DGXVECTOR2(pos[2]);
	tVtxPos[3] = DGXVECTOR2(pos[3]);
	
	tVtxTex[0] = DGXVECTOR2(st0.x, st0.y);
	tVtxTex[1] = DGXVECTOR2(st1.x, st0.y);
	tVtxTex[2] = DGXVECTOR2(st1.x, st1.y);
	tVtxTex[3] = DGXVECTOR2(st0.x, st1.y);


	// 색상
	if(pColor)
	{
		DWORD d = DGXCOLOR(*pColor);
		tVtxCol = d;
	}


	// Layer에 추가
	m_vLayer[nLayer].AddQuad(tVtxPos, tVtxTex, tVtxCol);


	return DGE_OK;
}


INT CDGT_SpriteMx::AddtoExistEx(IDGE_Texture*	pTexture	// DGE_Texture Pointer
					, const DGE_RECT*	pImgRc		// Image rect
					, const DGE_FLOAT2*	pvcScl		// Scaling
					, const DGE_FLOAT2*	pvcRot		// Rotation Center
					, FLOAT				fRot		// Angle(Radian)
					, const DGE_FLOAT2* pvcTrn		// Position
					, const DGE_COLORF*	pColor		// color
					)
{
	FLOAT	ImgW = 0;
	FLOAT	ImgH = 0;
	UINT	nTex = 0;

	if(NULL == pTexture)
		return DGE_ECANNOTFIND_RESOURCE;


	ImgW = (FLOAT)pTexture->GetImgW();
	ImgH = (FLOAT)pTexture->GetImgH();
	nTex = pTexture->GetId();

	if(0==nTex)
		return DGE_ECANNOTFIND_RESOURCE;


	INT	nLayer = FindLayler(pTexture);

	if(-1==nLayer)
	{
		nLayer = m_vLayer.size();

		TDGT_LAYER	tLayer(pTexture);
		this->m_vLayer.push_back(tLayer);
	}

	FLOAT	DrwL=  0;	// Draw Region Left
	FLOAT	DrwT=  0;	// Draw Region Top
	FLOAT	DrwW=ImgW;	// Draw Region Width
	FLOAT	DrwH=ImgH;	// Draw Region Height

	DGXVECTOR2	pos[4];
	DGXVECTOR2	st0(0,0);
	DGXVECTOR2	st1(1,1);


	// Final Data
	DGXVECTOR2	tVtxPos[4];	// Position
	DGXVECTOR2	tVtxTex[4];	// Texture Coordinate
	DGXCOLORb	tVtxCol((DWORD)0XFFFFFFFF);


	// Draw Region Width, Height
	if(pImgRc)
	{
		DrwL = FLOAT(pImgRc->left);
		DrwT = FLOAT(pImgRc->top );
		DrwW = FLOAT(pImgRc->right - pImgRc->left);
		DrwH = FLOAT(pImgRc->bottom- pImgRc->top );
	}

	// Setup UV
	st0.x = (DrwL +    0)/ImgW;
	st1.x = (DrwL + DrwW)/ImgW;
	st0.y = 1.0F - (DrwT +    0)/ImgH;
	st1.y = 1.0F - (DrwT + DrwH)/ImgH;


	// Setup Draw Position
	if(pvcTrn)
	{
		pos[0].x = pvcTrn->x;
		pos[0].y = pvcTrn->y;
	}
	else
	{
		pos[0].x = 0;
		pos[0].y = 0;
	}


	
	// Setup Postion
	if(NULL == pvcScl)
	{
		pos[1] = pos[0] + DGXVECTOR2(DrwW,     0);
		pos[2] = pos[0] + DGXVECTOR2(DrwW, DrwH);
		pos[3] = pos[0] + DGXVECTOR2(    0, DrwH);
	}

	else
	{
		FLOAT	fSclX = pvcScl->x;
		FLOAT	fSclY = pvcScl->y;

		if(fSclX>=0)
		{
			pos[1].x = pos[0].x + DrwW * fSclX;
			pos[2].x = pos[1].x;
			pos[3].x = pos[0].x;
		}
		else
		{
			pos[1].x = pos[0].x;
			pos[2].x = pos[1].x;
			pos[0].x = pos[1].x - DrwW * fSclX;
			pos[3].x = pos[0].x;
		}


		if(fSclY>=0)
		{
			pos[1].y = pos[0].y;
			pos[3].y = pos[0].y + DrwH * fSclY;
			pos[2].y = pos[3].y;			
		}
		else
		{
			pos[3].y = pos[0].y;
			pos[2].y = pos[3].y;
			pos[0].y = pos[3].y - DrwH * fSclY;
			pos[1].y = pos[0].y;
		}
	}


	// 회전 적용
	if(pvcRot)
	{
		DGXVECTOR2 vcR = DGXVECTOR2(pvcRot->x, pvcRot->y);
		DGXVECTOR2 d(0,0);

		FLOAT	fCos = (FLOAT)cos(-fRot);
		FLOAT	fSin = (FLOAT)sin(-fRot);

		for(INT i=0; i<4; ++i)
		{
			DGXVECTOR2 vcT = pos[i] - vcR;

			d.x = vcT.x * fCos + vcT.y * fSin;
			d.y =-vcT.x * fSin + vcT.y * fCos;

			tVtxPos[i].x = (vcR.x + d.x);
			tVtxPos[i].y = (vcR.y + d.y);
		}
	}
	else
	{
		tVtxPos[0] = DGXVECTOR2(pos[0]);
		tVtxPos[1] = DGXVECTOR2(pos[1]);
		tVtxPos[2] = DGXVECTOR2(pos[2]);
		tVtxPos[3] = DGXVECTOR2(pos[3]);
	}
	
	tVtxTex[0] = DGXVECTOR2(st0.x, st0.y);
	tVtxTex[1] = DGXVECTOR2(st1.x, st0.y);
	tVtxTex[2] = DGXVECTOR2(st1.x, st1.y);
	tVtxTex[3] = DGXVECTOR2(st0.x, st1.y);




	// 색상
	if(pColor)
	{
		DWORD d = DGXCOLOR(*pColor);
		tVtxCol = d;
	}


	// Layer에 추가
	m_vLayer[nLayer].AddQuad(tVtxPos, tVtxTex, tVtxCol);


	return DGE_OK;
}





INT CDGT_SpriteMx::DrawLayer(INT nFirstL, INT nLastL)
{
	INT		hr =0;
	INT		i =0;
	INT		iSize = m_vLayer.size();

	if(0> nFirstL)
		nFirstL = 0;

	if(0> nLastL || nLastL>iSize)
		nLastL = iSize;

	if(0>=nLastL || nLastL <= nFirstL)
		return DGE_EFAIL;


	for(i=nFirstL;i<nLastL; ++i)
		hr = DrawLayerIndex(i);

	return hr;
}


INT CDGT_SpriteMx::DrawLayer(PDGE_TEXTURE pTexture)
{
	INT nIdx = FindLayler(pTexture);

	if(DGE_FAILED(nIdx))
		return DGE_EFAIL;

	return DrawLayerIndex(nIdx);
}


INT CDGT_SpriteMx::	DrawLayerIndex(INT nIdx)
{
	TDGT_LAYER* pLayer = &m_vLayer[nIdx];
	INT			nTex = pLayer->pTex->GetId();
	INT			nVtx = pLayer->vVtxP.size();

	glBindTexture(GL_TEXTURE_2D, nTex);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


	glVertexPointer  (2, GL_FLOAT			, 0, &pLayer->vVtxP[0]);
	glColorPointer	 (4, GL_UNSIGNED_BYTE	, 0, &pLayer->vVtxC[0]);
	glTexCoordPointer(2, GL_FLOAT			, 0, &pLayer->vVtxT[0]);

	glDrawArrays(GL_TRIANGLES, 0, nVtx);


	return DGE_OK;
}


INT CDGT_SpriteMx::Clear()
{
	INT		i;
	INT		iSize = m_vLayer.size();
	
	for(i=0; i<iSize; ++i)
	{
		TDGT_LAYER* pLayer = &m_vLayer[i];

		pLayer->vVtxP.clear();
		pLayer->vVtxC.clear();
		pLayer->vVtxT.clear();

		pLayer->pTex = NULL;
	}

	m_vLayer.clear();

	return DGE_OK;
}


INT CDGT_SpriteMx::FindLayler(PDGE_TEXTURE pTex)
{
	INT nIdx = -1;
	INT iSize = m_vLayer.size();
	INT	i=0;

	for(i=0;i<iSize; ++i)
	{
		if(pTex == m_vLayer[i].pTex)
		{
			nIdx = i;
			break;
		}
	}

	return nIdx;
}



// Create Sprite
INT DGT_CreateSpriteMx(char* sCmd
					, PDGT_SPRITEMX* pData
					, DGE_HANDLE p1			// IDGE_Device*
					, DGE_HANDLE p2			// No Use
					, DGE_HANDLE p3			// No Use
					, DGE_HANDLE p4			// No Use
					 )
{
	CDGT_SpriteMx* pObj = NULL;
	*pData		= NULL;

	pObj = new CDGT_SpriteMx;

	if(DGE_FAILED(pObj->Create(p1, p2, p3, p4)))
	{
		delete pObj;
		return DGE_ECANNOTALLOCATED;
	}

	*pData = pObj;
	return DGE_OK;
}


INT DGT_DestroySpriteMx(PDGT_SPRITEMX* pData)
{
	if(NULL == *pData)
		return DGE_OK;

	delete *pData;
	(*pData) = NULL;

	return DGE_OK;
}




