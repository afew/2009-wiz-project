// Particle.cpp: implementation of the CParticle class.
//
//////////////////////////////////////////////////////////////////////


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <DGE_Type.h>
#include <DGE_Util.h>
#include <DGE_Math.h>
#include <DGE_Base.h>


#include "Particle.h"


#define MEDIA_DIR	"../../media/"


CParticle::CParticle()
{
	m_pDev		= NULL;
	m_pTex		= NULL;

	m_nPrt		= 40;
	m_pPrt		= NULL;
}

CParticle::~CParticle()
{
	Destroy();
}

void CParticle::Destroy()
{
	SAFE_DELETE_ARRAY(	m_pPrt	);

	DGE_DestroyTexture(&m_pTex);
}

INT CParticle::Create(PDGE_DEVICE pDev)
{
	INT hr;

	m_pDev = pDev;

	hr = DGE_CreateTexture(NULL, &m_pTex, (void*)MEDIA_DIR"tex/star.bmp");
	if(DGE_FAILED(hr))
		return DGE_ECANNOTALLOCATED;
	


	// Create The Particle
	m_pPrt = new TPart[m_nPrt];

	for(int i=0; i<m_nPrt; ++i)
		PartSetup(i);

	return DGE_OK;
}


INT CParticle::FrameMove()
{
	INT i=0;

	for(i=0; i<m_nPrt; ++i)
	{
		m_pPrt[i].a += .8F;
		m_pPrt[i].r -= 0.06f;

		if(m_pPrt[i].r<0.0f)
			PartReset(i);
	}
	

	return DGE_OK;
}


void CParticle::Render()
{
	int i;
	VtxUV1	pVtx[4];
	DGXMATRIX	mtW;
	DGXMATRIX	mtT;
	DGXMATRIX	mtS;

	DGXMATRIX	mtV;
	DGXMATRIX	mtB;
	DGXMATRIX	mtR;

	DGXVECTOR3	vcRot;


	m_pDev->GetTransform(DGE_TS_VIEW, &mtV);

	// ������� ����Ŀ� _41, _42, _43 ������ �ϸ� ������ ����� �ȴ�.
	mtB.Inverse(&mtV, FALSE);
	mtB._41 = 0;
	mtB._42 = 0;
	mtB._43 = 0;

	// ȸ���� �� ��� OpenGL�� y���� �ϴ��� �ٶ󺸰� �ְ� (-z)���� ���� �����̹Ƿ�
	// �� ����� _13, _23, _33�� �̿��Ѵ�
	vcRot = -DGXVECTOR3(mtV._13, mtV._23, mtV._33);

	
	m_pDev->SetRenderState(DGE_RS_CULL_FACE, DGE_ST_DISABLE);
	m_pDev->SetRenderState(DGE_RS_DEPTH_TEST, DGE_ST_DISABLE);

	m_pDev->SetRenderState(DGE_RS_BLEND, DGE_ST_ENABLE);
	m_pDev->SetRenderState(DGE_RS_BLEND_SRC, DGE_ST_SRC_ALPHA);
	m_pDev->SetRenderState(DGE_RS_BLEND_DEST, DGE_ST_ONE);


// ������ ����� ������� ������ x, z ��鿡 ��ƼŬ�� ���� ��ġ�� �����.
//	pVtx[0] = VtxUV1(-1.0f, 0.0f, -1.0f,  0.0f,  0.0f);
//	pVtx[1] = VtxUV1( 1.0f, 0.0f, -1.0f,  1.0f,  0.0f);
//	pVtx[2] = VtxUV1( 1.0f, 0.0f,  1.0f,  1.0f,  1.0f);
//	pVtx[3] = VtxUV1(-1.0f, 0.0f,  1.0f,  0.0f,  1.0f);

	// OpenGL�� y���� �ϴ��� �ٶ󺸰� �����Ƿ� �����尡 ����Ƿ���
	// x, y ������� ��ƼŬ�� ���� ��ġ�� ������ �Ѵ�.
	pVtx[0] = VtxUV1(-1.0f, -1.0f, 0.0f,  0.0f,  0.0f);
	pVtx[1] = VtxUV1( 1.0f, -1.0f, 0.0f,  1.0f,  0.0f);
	pVtx[2] = VtxUV1( 1.0f,  1.0f, 0.0f,  1.0f,  1.0f);
	pVtx[3] = VtxUV1(-1.0f,  1.0f, 0.0f,  0.0f,  1.0f);


	m_pDev->SetTexture(0, m_pTex);
	m_pDev->SetTextureAddressS(0, DGE_TS_REPEAT);
	m_pDev->SetTextureAddressT(0, DGE_TS_REPEAT);
	m_pDev->SetTextureFilterMin(0, DGE_TS_LINEAR);
	m_pDev->SetTextureFilterMag(0, DGE_TS_LINEAR);

	m_pDev->SetFVF(VtxUV1::FVF);
	m_pDev->SetTexture(0, m_pTex);
	

	mtS.SetupScaling(13, 13, 13);


	for(i=0; i<m_nPrt; ++i)
	{
		FLOAT	fRadius = m_pPrt[i].r;
		FLOAT	fTheta = DGXToRadian(m_pPrt[i].a);
		FLOAT	fCos = (FLOAT)cos(fTheta);
		FLOAT	fSin = (FLOAT)sin(fTheta);

		DGXVECTOR3	pos(fRadius * fCos, -10 + (-2)*fRadius, fRadius * fSin);


		mtT.SetupTranslation( &pos);
		mtR.SetupRotationAxis(&vcRot, fTheta*2);

		mtW = mtB * mtS * mtR * mtT;

		m_pDev->SetColor((FLOAT*)&m_pPrt[i].d);
		m_pDev->SetTransform(DGE_TS_WORLD, &mtW);
		m_pDev->DrawPrimitiveUPf(DGE_PT_TRIANGLE_FAN, 0, 4, pVtx, sizeof(VtxUV1) );

	}

	
	m_pDev->SetColor(1,1,1,1);
	m_pDev->SetTexture(0, NULL);

	m_pDev->SetTransformIdentity(DGE_TS_WORLD);

	m_pDev->SetRenderState(DGE_RS_BLEND, DGE_ST_DISABLE);
	m_pDev->SetRenderState(DGE_RS_CULL_FACE, DGE_ST_ENABLE);
	m_pDev->SetRenderState(DGE_RS_DEPTH_TEST, DGE_ST_ENABLE);
}


void CParticle::PartSetup(INT nIdx)
{
	DGXCOLOR d( FLOAT(rand()%256), FLOAT(rand()%256), FLOAT(rand()%256), 255);
	d *= (1.F/255.F);

	m_pPrt[nIdx].a = 4 * 360 * nIdx/FLOAT(m_nPrt);
	
	m_pPrt[nIdx].r = 30 * nIdx/FLOAT(m_nPrt);
	m_pPrt[nIdx].d = d;
}

void CParticle::PartReset(INT nIdx)
{
	DGXCOLOR d( FLOAT(rand()%256), FLOAT(rand()%256), FLOAT(rand()%256), 255);
	d *= (1.F/255.F);

	m_pPrt[nIdx].a = 4 * 360 * nIdx/FLOAT(m_nPrt);
	m_pPrt[nIdx].r = 30;
	m_pPrt[nIdx].d = d;
}



