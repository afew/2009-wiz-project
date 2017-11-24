// Implementation of the IDGE_Sprite.
//
////////////////////////////////////////////////////////////////////////////////


#include <gles/gl.h>

#include <DGE_Math.h>
#include "DGE_Base.h"
#include "DGE_Sprite.h"

#include "DGE_Texture.h"



DGXVECTOR2	CDGE_Sprite::m_VtxPos[4];	// Position
DGXVECTOR2	CDGE_Sprite::m_VtxTex[4];	// Texture Coordinate


CDGE_Sprite::CDGE_Sprite()
{
	m_pDev	= NULL;

	m_VtxPos[0] = DGXVECTOR2(-0.9F, -0.9F);
	m_VtxPos[1] = DGXVECTOR2( 0.9F, -0.9F);
	m_VtxPos[2] = DGXVECTOR2( 0.9F,  0.9F);
	m_VtxPos[3] = DGXVECTOR2(-0.9F,  0.9F);

	m_VtxTex[0] = DGXVECTOR2( 0.0F,  0.0F);
	m_VtxTex[1] = DGXVECTOR2( 1.0F,  0.0F);
	m_VtxTex[2] = DGXVECTOR2( 1.0F,  1.0F);
	m_VtxTex[3] = DGXVECTOR2( 0.0F,  1.0F);

	m_fScnW	= 320.F;
	m_fScnH	= 240.F;
}


CDGE_Sprite::~CDGE_Sprite()
{
	Destroy();
}


void CDGE_Sprite::Destroy()
{
	m_pDev = NULL;
}


INT CDGE_Sprite::Create(DGE_HANDLE p1, DGE_HANDLE, DGE_HANDLE, DGE_HANDLE)
{
	if(NULL == p1)
		return DGE_EINVALIDATE_CALL;

	m_pDev = (IDGE_Device*)p1;



	// 뷰포트에서 화면의 크기를 얻는다.
	FLOAT f[4]={0};
	glGetFloatv(GL_VIEWPORT, f);

	m_fScnW = f[2];
	m_fScnH = f[3];


	m_VtxPos[0] = DGXVECTOR2(0.0000F, m_fScnH);
	m_VtxPos[1] = DGXVECTOR2(m_fScnW, m_fScnH);
	m_VtxPos[2] = DGXVECTOR2(m_fScnW, 0.0000F);
	m_VtxPos[3] = DGXVECTOR2(0.0000F, 0.0000F);

	m_VtxTex[0] = DGXVECTOR2(0.0000F, 0.0000F);
	m_VtxTex[1] = DGXVECTOR2(1.0000F, 0.0000F);
	m_VtxTex[2] = DGXVECTOR2(1.0000F, 1.0000F);
	m_VtxTex[3] = DGXVECTOR2(0.0000F, 1.0000F);

	return DGE_OK;
}


INT CDGE_Sprite::Begin(DWORD dMode)
{
	glGetFloatv(GL_PROJECTION_MATRIX, (GLfloat*)m_mtPrj);
	glGetFloatv(GL_MODELVIEW_MATRIX, (GLfloat*)m_mtViw);
	glMatrixMode(GL_PROJECTION);	glLoadIdentity();

	glOrthof(	0.0000F, m_fScnW
			  , m_fScnH, 0.0000F
			  , 0.0000F, 1.0000F
			  );

	glMatrixMode(GL_MODELVIEW);		glLoadIdentity();


//	float mtPrj[4][4]={0};
//	glGetFloatv(GL_PROJECTION_MATRIX, &mtPrj[0][0]);

//	float mtViw[4][4]={0};
//	glGetFloatv(GL_MODELVIEW_MATRIX, &mtViw[0][0]);

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE );
	glDisable(GL_LIGHTING);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_TEXTURE_2D);
	
	glActiveTexture(GL_TEXTURE0);
	glClientActiveTexture(GL_TEXTURE0);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

//	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer  (2, GL_FLOAT,			0, m_VtxPos);
	glTexCoordPointer(2, GL_FLOAT,			0, m_VtxTex);

	return DGE_OK;
}


INT CDGE_Sprite::End()
{
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	glMatrixMode(GL_PROJECTION);	glLoadMatrixf(m_mtPrj);
	glMatrixMode(GL_MODELVIEW);		glLoadMatrixf(m_mtViw);

	glColor4f(1.F, 1.F, 1.F, 1.F);

	return DGE_OK;
}



INT CDGE_Sprite::Draw(IDGE_Texture*		pTexture	// DGE_Texture Pointer
					, const DGE_RECT*	pImgRc		// Image rect
					, const DGE_FLOAT2* pvcTrn		// Position
					, const DGE_COLORF*	pColor		// color
					)
{
	FLOAT	ImgW = 0;
	FLOAT	ImgH = 0;
	UINT	nTex = 0;

	if(NULL == pTexture)
	{
		// for Operation of Sprite Test...
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		return DGE_ECANNOTFIND_RESOURCE;
	}

	glEnableClientState(GL_TEXTURE_COORD_ARRAY);


	ImgW = (FLOAT)pTexture->GetImgW();
	ImgH = (FLOAT)pTexture->GetImgH();


	nTex = pTexture->GetId();

	if(0==nTex)
		return DGE_ECANNOTFIND_RESOURCE;



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
	pos[1] = pos[0] + DGXVECTOR2(DrwW,    0);
	pos[2] = pos[0] + DGXVECTOR2(DrwW, DrwH);
	pos[3] = pos[0] + DGXVECTOR2(   0, DrwH);


	// Final...
	m_VtxPos[0] = DGXVECTOR2(pos[0]);
	m_VtxPos[1] = DGXVECTOR2(pos[1]);
	m_VtxPos[2] = DGXVECTOR2(pos[2]);
	m_VtxPos[3] = DGXVECTOR2(pos[3]);
	
	m_VtxTex[0] = DGXVECTOR2(st0.x, st0.y);
	m_VtxTex[1] = DGXVECTOR2(st1.x, st0.y);
	m_VtxTex[2] = DGXVECTOR2(st1.x, st1.y);
	m_VtxTex[3] = DGXVECTOR2(st0.x, st1.y);


	glBindTexture(GL_TEXTURE_2D, nTex);
//	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


	// 색상
	if(pColor)	glColor4f(pColor->r, pColor->g, pColor->b, pColor->a);
	else		glColor4f(1.F, 1.F, 1.F, 1.F);

	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	return DGE_OK;
}


INT CDGE_Sprite::DrawEx(IDGE_Texture*	pTexture	// DGE_Texture Pointer
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

			m_VtxPos[i].x = (vcR.x + d.x);
			m_VtxPos[i].y = (vcR.y + d.y);
		}
	}
	else
	{
		m_VtxPos[0] = DGXVECTOR2(pos[0]);
		m_VtxPos[1] = DGXVECTOR2(pos[1]);
		m_VtxPos[2] = DGXVECTOR2(pos[2]);
		m_VtxPos[3] = DGXVECTOR2(pos[3]);
	}
	
	m_VtxTex[0] = DGXVECTOR2(st0.x, st0.y);
	m_VtxTex[1] = DGXVECTOR2(st1.x, st0.y);
	m_VtxTex[2] = DGXVECTOR2(st1.x, st1.y);
	m_VtxTex[3] = DGXVECTOR2(st0.x, st1.y);


	glBindTexture(GL_TEXTURE_2D, nTex);
//	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


	// 색상
	if(pColor)	glColor4f(pColor->r, pColor->g, pColor->b, pColor->a);
	else		glColor4f(1.F, 1.F, 1.F, 1.F);

	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	return DGE_OK;
}



//
// for Font
INT CDGE_Sprite::DrawFont(IDGE_Texture*		pTexture	// DGE_Texture Pointer
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


	DGXVECTOR2	pos[4];


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
	pos[1] = pos[0] + DGXVECTOR2(ImgW,    0);
	pos[2] = pos[0] + DGXVECTOR2(ImgW, ImgH);
	pos[3] = pos[0] + DGXVECTOR2(   0, ImgH);


	// Final...
	m_VtxPos[0] = DGXVECTOR2(pos[0]);
	m_VtxPos[1] = DGXVECTOR2(pos[1]);
	m_VtxPos[2] = DGXVECTOR2(pos[2]);
	m_VtxPos[3] = DGXVECTOR2(pos[3]);
	
	m_VtxTex[0] = DGXVECTOR2(0.0F, 1.0F);
	m_VtxTex[1] = DGXVECTOR2(1.0F, 1.0F);
	m_VtxTex[2] = DGXVECTOR2(1.0F, 0.0F);
	m_VtxTex[3] = DGXVECTOR2(0.0F, 0.0F);


	glBindTexture(GL_TEXTURE_2D, nTex);
//	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


	// 색상
	if(pColor)	glColor4f(pColor->r, pColor->g, pColor->b, pColor->a);
	else		glColor4f(1.F, 1.F, 1.F, 1.F);

	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	
	return DGE_OK;
}


INT CDGE_Sprite::DrawFontEx(IDGE_Texture*	pTexture	// DGE_Texture Pointer
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


	DGXVECTOR2	pos[4];


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
		pos[1] = pos[0] + DGXVECTOR2(ImgW,    0);
		pos[2] = pos[0] + DGXVECTOR2(ImgW, ImgH);
		pos[3] = pos[0] + DGXVECTOR2(   0, ImgH);
	}

	else
	{
		FLOAT	fSclX = pvcScl->x;
		FLOAT	fSclY = pvcScl->y;

		if(fSclX>=0)
		{
			pos[1].x = pos[0].x + ImgW * fSclX;
			pos[2].x = pos[1].x;
			pos[3].x = pos[0].x;
		}
		else
		{
			pos[1].x = pos[0].x;
			pos[2].x = pos[1].x;
			pos[0].x = pos[1].x - ImgW * fSclX;
			pos[3].x = pos[0].x;
		}


		if(fSclY>=0)
		{
			pos[1].y = pos[0].y;
			pos[3].y = pos[0].y + ImgH * fSclY;
			pos[2].y = pos[3].y;			
		}
		else
		{
			pos[3].y = pos[0].y;
			pos[2].y = pos[3].y;
			pos[0].y = pos[3].y - ImgH * fSclY;
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

			m_VtxPos[i].x = (vcR.x + d.x);
			m_VtxPos[i].y = (vcR.y + d.y);
		}
	}
	else
	{
		m_VtxPos[0] = DGXVECTOR2(pos[0]);
		m_VtxPos[1] = DGXVECTOR2(pos[1]);
		m_VtxPos[2] = DGXVECTOR2(pos[2]);
		m_VtxPos[3] = DGXVECTOR2(pos[3]);
	}
	
	m_VtxTex[0] = DGXVECTOR2(0.0F, 1.0F);
	m_VtxTex[1] = DGXVECTOR2(1.0F, 1.0F);
	m_VtxTex[2] = DGXVECTOR2(1.0F, 0.0F);
	m_VtxTex[3] = DGXVECTOR2(0.0F, 0.0F);


	glBindTexture(GL_TEXTURE_2D, nTex);
//	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


	// 색상
	if(pColor)	glColor4f(pColor->r, pColor->g, pColor->b, pColor->a);
	else		glColor4f(1.F, 1.F, 1.F, 1.F);

	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	return DGE_OK;
}




// Create Sprite
INT DGE_CreateSprite(char* sCmd
					, PDGE_SPRITE* pData
					, DGE_HANDLE p1			// IDGE_Device*
					, DGE_HANDLE p2			// No Use
					, DGE_HANDLE p3			// No Use
					, DGE_HANDLE p4			// No Use
					 )
{
	CDGE_Sprite* pObj = NULL;
	*pData		= NULL;

	pObj = new CDGE_Sprite();

	if(DGE_FAILED(pObj->Create(p1, p2, p3, p4)))
	{
		delete pObj;
		return DGE_ECANNOTALLOCATED;
	}

	*pData = pObj;
	return DGE_OK;
}


INT DGE_DestroySprite(IDGE_Sprite** pData)
{
	if(NULL == *pData)
		return DGE_OK;

	delete *pData;
	(*pData) = NULL;

	return DGE_OK;
}




