// Implementation of the CDGX_GeoGrid class.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _DGX_GeoGrid_H_
#define _DGX_GeoGrid_H_

class CDGX_GeoGrid : public IDGX_Entity
{
public:
	struct Vtx : public DGE3D::VxfD
	{
		Vtx()
		{
			p.x = 0;
			p.y = 0;
			p.z = 0;
			d   =	DGXCOLORb(DWORD(0xFFFFFFFF));
		}

		Vtx(FLOAT X, FLOAT Y, FLOAT Z, DWORD D=0xFFFFFFFF)
		{
			p.x = X;
			p.y = Y;
			p.z = Z;
			d   =	DGXCOLORb(DWORD(D));
		}
	};


protected:
	PDGE_DEVICE		m_pDev;
	Vtx				m_pLine[72];
	
public:
	CDGX_GeoGrid();
	virtual ~CDGX_GeoGrid();

	virtual INT		Create(void* =0, void* =0, void* =0, void* =0);
	virtual	void	Destroy()						{	return;		}
	virtual	INT		FrameMove()						{	return 0;	}
	
	virtual	void	Render();

	virtual INT		Query(char* sCmd, void* pData)	{	return 0;	}
};


#endif


