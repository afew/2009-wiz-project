
#if defined(_WIN32) || defined(WIN32)
#pragma warning(disable: 4819 4996)
#endif


#include "_StdAfx.h"


DGE_INLINE int IsInWinRect(int l, int t, int r, int b)
{
//	if(
//		(l<  0 && r<  0) ||
//		(l>320 && r>320) ||
//		(t<  0 && b<  0) ||
//		(t>240 && b>240)
//		)
//		return FALSE;
//
//	return TRUE;

	return !(l > 320 || r <0  || t >240 || b <0);
}


DGE_INLINE int IsNotInWinRect(int l, int t, int r, int b)
{
	return (l > 320 || r <0  || t >240 || b <0);
}



int LoadImage(PDGE_TEXTURE* pOut, char *fname, unsigned int colorkey)
{
	int hr = 0;
	DWORD	dColorKey = 0xFF10633E;

	if(colorkey)
		dColorKey = 0xFF10633E;
	else
		dColorKey = 0x0;

	hr = DGE_CreateTexture(NULL, pOut, fname, NULL, &dColorKey);

	if(DGE_FAILED(hr))
		printf("Err: DGE_CreateTexture, %s\n", fname);


	return hr;
}


int LoadImage2(PDGE_TEXTURE* pOut, char* sFile, unsigned int dColorKey)
{
	int hr = 0;
	hr = DGE_CreateTexture(NULL, pOut, sFile, NULL, &dColorKey);

	if(DGE_FAILED(hr))
		printf("Err: DGE_CreateTexture, %s\n", sFile);

	return hr;
}


void ReleaseImage(PDGE_TEXTURE* pTex)
{
	DGE_DestroyTexture(pTex);
}


void BltRect(PDGE_TEXTURE pTex, int dstX, int dstY, int srcX, int srcY, int width, int height, unsigned int dColor)
{
	DGE_RECT	rc;
	DGXVECTOR2	pos(0,0);
	DGXCOLOR	d = (DWORD)dColor;

	if(1.f<d.a)	d.a = 1.f;
	if(0.f>d.a)	d.a = 0.f;

	rc.left  = srcX;
	rc.top   = srcY;
	rc.right = srcX + width;
	rc.bottom= srcY + height;

	pos.x =(float)dstX;
	pos.y =(float)dstY;


	if(IsNotInWinRect(dstX, dstY, dstX+width, dstX+height))
		return;


	g_pSprite->Draw(pTex, &rc, &pos, &d);
}



void Blt(PDGE_TEXTURE pTex, int dstX, int dstY, unsigned int dColor)
{
	if(NULL == pTex)
		return;

	DGXVECTOR2	pos( (float)dstX, (float)dstY);
	DGXCOLOR	d = (DWORD)dColor;


	if(IsNotInWinRect(dstX, dstY, dstX+320, dstX+240))
		return;


	if(1.f<d.a)	d.a = 1.f;
	if(0.f>d.a)	d.a = 0.f;

	g_pSprite->Draw(pTex, NULL, &pos, &d);		/* 320 * 240 */
}



//// ラインの描画
void drawGRPline(int x1, int y1, int x2, int y2, unsigned int color)
{
	DGXVECTOR2	Line[2];

	Line[0] = DGXVECTOR2(float(x1), float(y1));
	Line[1] = DGXVECTOR2(float(x2), float(y2));


	glVertexPointer(2, GL_FLOAT, 0, Line);
	glDrawArrays(GL_LINES, 0, 2);	
}



void BltNumericImage( long value, long length, long x, long y, PDGE_TEXTURE plane, long num_stpos_x, long num_stpos_y, long num_width, long num_height )
{
	long blt_num;	// １桁の数値を格納する
	long i;			// 桁数分のforループで使用
	long dv;		// 割り算で使用する値

	// value が負の値の場合、正の値に置き換える
	if ( value < 0 )
	{
		value = value * -1;
	}

	// 最初の割り算で使用する値を求める
	dv = 1;
	for( i = 1; i < length; i++ )
	{
		dv = dv * 10;
	}

	// 指定された桁数分の数字画像を転送する
	for( i = 0; i < length; i++ )
	{
		// 表示する数字を求める
		blt_num = value / dv;
		value = value - blt_num * dv;
		if ( blt_num > 9 )
		{	// 表示したい１桁の数値にならなければ、１桁にする。
			blt_num = blt_num % 10;
		}
		// 数字画像転送
		BltRect( plane, x + (num_width * i), y, num_stpos_x + (num_width * blt_num), num_stpos_y, num_width, num_height );
		// 割り算で使用する値を10で割る
		dv = dv / 10;
	}

}


void BltNumericImage2( long value, long length, long x, long y, PDGE_TEXTURE plane, long num_stpos_x, long num_stpos_y, long num_width, long num_height )
{
	long blt_num;	// １桁の数値を格納する
	long i;			//
	long dv;		// 割り算で使用する値
	long x_hosei;	//右詰め補正値
	int buf = value;
	int t = 1;

	// value が負の値の場合、正の値に置き換える
	if ( value < 0 )
	{
		value = value * -1;
	}

	/* 2002.10.21 D.K start */
	while(TRUE)
	{
		t++;
		buf = buf / 10;
		if ( 0 <= buf )
		{
			break;
		}
	}
	x_hosei = t;
//	scanf(string[0],"%d",value);
//	x_hosei = StrLen( string[0] );
	if ( x_hosei == 0 )
	{
		x_hosei = 1;
	}
	x_hosei = length - x_hosei;
	x_hosei = x_hosei * num_width;
//	length = StrLen( string[0] );
	x = x + x_hosei;
	/* 2002.10.21 D.K end */

	// 最初の割り算で使用する値を求める
	dv = 1;
	for( i = 1; i < length; i++ )
	{
		dv = dv * 10;
	}

	// 指定された桁数分の数字画像を転送する
	for( i = 0; i < length; i++ )
	{
		// 表示する数字を求める
		blt_num = value / dv;
		value = value - blt_num * dv;
		if ( blt_num > 9 )
		{	// 表示したい１桁の数値にならなければ、１桁にする。
			blt_num = blt_num % 10;
		}
		// 数字画像転送
		BltRect( plane, x + (num_width * i), y, num_stpos_x + (num_width * blt_num), num_stpos_y, num_width, num_height );
		// 割り算で使用する値を10で割る
		dv = dv / 10;
	}
}


