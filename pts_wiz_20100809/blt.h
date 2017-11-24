//
//
////////////////////////////////////////////////////////////////////////////////

#ifndef __BltRc_H__
#define __BltRc_H__


int		LoadImage(PDGE_TEXTURE* ppTex, char *fname, unsigned int colorkey);
int		LoadImage2(PDGE_TEXTURE* ppTex, char* fname, unsigned int dColorKey = 0xFF106342);
void	ReleaseImage(PDGE_TEXTURE* ppTex);

void	Blt(PDGE_TEXTURE pTex, int dstX, int dstY, unsigned int dColor = 0xFFFFFFFF);
void	BltRect(PDGE_TEXTURE pTex, int srcX, int srcY, int dstX, int dstY, int width, int height, unsigned int dColor = 0xFFFFFFFF);


void	BltNumericImage( long value, long length, long x, long y, PDGE_TEXTURE plane, long num_stpos_x, long num_stpos_y, long num_width, long num_height );
void	BltNumericImage2( long value, long length, long x, long y, PDGE_TEXTURE plane, long num_stpos_x, long num_stpos_y, long num_width, long num_height );
long	get2keta( long val, long st );

void	drawGRPline(int x1, int y1, int x2, int y2, unsigned int color);



struct TFadeTex
{
	PDGE_TEXTURE	pTex;
	DGXCOLOR		d;

	void SetAlpha(int a)
	{
		d = DGXCOLOR(1,1,1, float(a)/255.5F);
	}

	TFadeTex()
	{
		pTex = NULL;
		d    = DGXCOLOR(1,1,1, 0);
	}
};



DGE_INLINE void SetAlpha(TFadeTex* p, int alpha)
{
	if (NULL == p || NULL == p->pTex)
		return;


	p->SetAlpha(alpha);
}

DGE_INLINE void draw_fix(TFadeTex* p, int iX, int iY)
{
	unsigned int dColor = 0;

	if (NULL == p || NULL == p->pTex)
		return;
	
	dColor = (DWORD)p->d;
	Blt(p->pTex, iX, iY, dColor);
}


#endif


