// Interface for the Particle class.
//
////////////////////////////////////////////////////////////////////////////////


#if defined(_WIN32) || defined(WIN32)
	#if _MSC_VER > 1000
		#pragma once
	#endif
#endif


#ifndef _CParticle_H_
#define _CParticle_H_

class CParticle
{
public:
	struct VtxUV1 : public DGE3D::VxfUV1
	{
		VtxUV1()
		{
			p.x = 0; p.y = 0; p.z = 0;
			t.x = 0; t.y = 0;
		}

		VtxUV1(FLOAT X,FLOAT Y,FLOAT Z,FLOAT U,FLOAT V)
		{
			p.x = X; p.y = Y; p.z = Z;
			t.x = U; t.y = V;
		}
	};

	struct TPart
	{
		DGXCOLOR	d;	// Color
		FLOAT		a;	// Angle(Degree)
		FLOAT		r;	// Radius
	};


protected:
	PDGE_DEVICE		m_pDev	;			// DGE_DEVICE
	PDGE_TEXTURE	m_pTex	;			// Texture 0

	INT				m_nPrt	;
	TPart*			m_pPrt	;

public:
	CParticle();
	virtual ~CParticle();

	INT		Create(PDGE_DEVICE pDev);
	void	Destroy();
	INT		FrameMove();
	void	Render();

protected:
	void	PartSetup(INT nIdx);
	void	PartReset(INT nIdx);
};

#endif



