// Implementation of the IDGX_Font.
//
////////////////////////////////////////////////////////////////////////////////


#if defined(_WIN32) || defined(WIN32)
	#if _MSC_VER >= 1200
	#pragma warning(disable: 4996)
	#endif

	#include <windows.h>

#endif


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <ft2build.h>
#include <freetype/freetype.h>

#include <DGE_Type.h>
#include <DGE_Math.h>
#include <DGE_Base.h>

#include "../11dge20/DGE_Sprite.h"
#include "DGX_Font.h"


struct LHFTT_STR
{
	int		w;
	int		h;
	int		p;		// Pitch
	BYTE*	b;

	int		of_l;	// Offset Left
    int		of_t;	// Offset Top
	int		of_x;	// Offset Screen X

	LHFTT_STR* N;	// Next Pointer


	LHFTT_STR() : w(0), h(0), p(0), b(NULL), of_l(0), of_t(0), of_x(0), N(NULL){}

	LHFTT_STR(  int W, int H, int P, BYTE* B
				, int off_l, int off_t, int nOff)
				: w(W), h(H), p(P), b(B), of_l(off_l), of_t(off_t), of_x(nOff), N(NULL){}

	LHFTT_STR* FindTail()
	{
		if( N)
			return N->FindTail();

		return this;
	}


	void AddTail(LHFTT_STR* v)
	{
		LHFTT_STR* pTail = FindTail();

		pTail->Insert(v);
	}

	void Insert(LHFTT_STR* v)
	{
		LHFTT_STR* _t = N;

		this->N = v;

		v->N = _t;

	}
};



extern int	han2unicode(char *src, unsigned short *dest);
INT			DGE_SetupTTFImageChain(LHFTT_STR** pOut, WCHAR* sDst, void* pFontFace, INT FontSize);





class CDGX_Font : public IDGX_Font
{
protected:
	FT_FaceRec_*	m_ptFont;
	INT				m_nFntH;		// Font Height
	char*			m_sSrc;

	DGXCOLOR		m_Color;		// Color
	DGXVECTOR2		m_vcPos;		// Position
	CDGE_Sprite*	m_pSprite;

	PDGE_TEXTURE	m_pTex;

public:
	CDGX_Font();
	virtual ~CDGX_Font();

	virtual INT		SetString(const char* sMsg);
	virtual	INT		SetColor(const DGE_COLORF* v);
	virtual INT		SetPos(const DGE_FLOAT2*);
	virtual INT		DrawTxt();

public:
	INT		Create(DGE_HANDLE =0, DGE_HANDLE =0, DGE_HANDLE =0, DGE_HANDLE =0);
	void	Destroy();

public:
	static FT_LibraryRec_*	m_FTTontLib;
};




FT_Library	CDGX_Font::m_FTTontLib = NULL;



CDGX_Font::CDGX_Font()
{
	m_ptFont	= NULL;
	m_nFntH		= 0;
	m_sSrc		= NULL;
	m_Color		= DWORD(0XFFFFFFFF);		// Color
	m_vcPos		= DGXVECTOR2(0, 0);			// Position
	m_pSprite	= NULL;						// 2D Sprite

	m_pTex		= NULL;
}


CDGX_Font::~CDGX_Font()
{
	Destroy();
}


void CDGX_Font::Destroy()
{
	if(m_sSrc)
	{
		delete [] m_sSrc;
		m_sSrc = NULL;
	}

	if(m_pTex)
	{
		DGE_DestroyTexture(&m_pTex);
	}


	if(NULL == m_ptFont)
		return;

	m_ptFont = NULL;
	m_pSprite= NULL;

	FT_Done_Face( m_ptFont );
}



INT CDGX_Font::Create(DGE_HANDLE p1, DGE_HANDLE p2, DGE_HANDLE p3, DGE_HANDLE p4)
{
	if(NULL == p1 || NULL == p2)
		return DGE_EFAIL;



	TDGX_FONT*	pDgxFont =(TDGX_FONT*)p1;
	
	char*	sFont = pDgxFont->sName;
	INT		Height= pDgxFont->iHeight;
	INT		res_horz =96;	// Horizental Resolution
	INT		res_vert =96;	// Vertical Resolution


	m_pSprite= (CDGE_Sprite*)p2;
	
	if(p3)	res_horz = *((INT* )p3);
	if(p4)	res_vert = *((INT* )p4);


	if(DGE_FAILED(DGX_TFFontOpen()))
	{
		printf("Err: %d, %s \t", __LINE__, __FILE__);
		printf("DGX_TFFontOpen() Failed\n");
		return DGE_EFAIL;
	}


	//	Load Font Face
	if( 0 != FT_New_Face(CDGX_Font::m_FTTontLib, sFont, 0, &m_ptFont))
	{
		printf("Err: %d, %s \t", __LINE__, __FILE__);
		printf("FT_New_Face() Failed\n");
		return DGE_EFAIL;
	}


	int	FontSize	= Height;
	int FontHeight_f= Height * 64;


	// 크기 설정
	if( 0 != FT_Set_Char_Size(m_ptFont, 0, FontHeight_f, res_horz, res_vert))
	{
		printf("Err: %d, %s \t", __LINE__, __FILE__);
		printf("FT_Set_Char_Size() Failed\n");
		return DGE_EFAIL;
	}


	// Font Size를 다시 계산
	m_nFntH	= FontSize;

	return DGE_OK;
}





INT CDGX_Font::SetString(const char* sSrc)
{
	INT		hr = DGE_EFAIL;
	int		Len = 0;

//	char	sSrc[128]="갈릭Hello World 안녕^^0漢子";
	WCHAR*	sDst=NULL;


	// Null 또는 문자열 길이가 0인 경우
	if(NULL ==sSrc || 0 == (Len = strlen(sSrc) ) )
	{
		if(m_sSrc)
		{
			delete [] m_sSrc;
			m_sSrc = NULL;
		}

		if(m_pTex)
		{
			DGE_DestroyTexture(&m_pTex);
			m_pTex = NULL;
		}

		return DGE_OK;
	}


	// 이전의문자열과 같으면
	if( NULL != m_sSrc && 0 == strcmp(m_sSrc, sSrc))
		return DGE_OK;


	// 이전의 문자열 지운다.
	if(m_sSrc)
	{
		delete [] m_sSrc;
		m_sSrc = NULL;
	}


	Len = (7 + Len/4)*4;
	m_sSrc = new char[ Len ];	// 4의 배수로 만든다.
	memset(m_sSrc, 0, Len);
	strcpy(m_sSrc, sSrc);

	sDst = new WCHAR[Len];
	memset(sDst, 0, sizeof(WCHAR) * Len);


//	printf("%s\n", m_sSrc);

	// Multi Byte를 Unicode로 바꾼다.
	//
#if defined(_WIN32) || defined(WIN32)

	INT iLen = strlen(sSrc);
	MultiByteToWideChar( CP_ACP, 0, sSrc, -1, sDst, iLen );

#else

	han2unicode(m_sSrc, sDst);

#endif


	// Chain을 만든다.
	LHFTT_STR* pHead	= NULL;
	LHFTT_STR* pObj	= NULL;

	INT h_w = DGE_SetupTTFImageChain(&pHead, sDst, m_ptFont, m_nFntH);


	delete [] sDst;

	if(0>h_w)
		return DGE_EFAIL;


	// 문자열 버퍼를 생성
	INT MaxHeight= (0x00000FFF & h_w>>16);
	INT MaxWidth = (0x0000FFFF & h_w);
	INT	nOffy = 0;

	INT nBufHeight= ((MaxHeight+15)/4) * 4;			// 4의 배수로 만듦
	INT nBufWidth = ((MaxWidth +15)/4) * 4;			// 4의 배수로 만듦


#if defined(_WIN32) || defined(WIN32)
	nBufHeight= DGE_Quantum2Power(nBufHeight);		// 2의 승수로 만듦
	nBufWidth = DGE_Quantum2Power(nBufWidth );		// 4의 배수로 만듦
#endif

	INT nPxlBuf = nBufHeight * nBufWidth;


	nOffy = nBufHeight-MaxHeight-2;					// Offset Y


	// 텍스처의 픽셀을 만들기 위한 임시 버퍼
	BYTE* pPxlSrc = NULL;							// TTF에서 얻은 값으로 만든 픽셀
	BYTE* pPxlAnt = NULL;							// Anti-Aliasing이 적용된 픽셀
	BYTE* pPxlFnt = NULL;							// 텍스처에 전달될 픽셀

	pPxlSrc = new BYTE[nPxlBuf];					// 폰트 체인에서 얻은 픽셀을 저장할 임시 버퍼 생성
	memset(pPxlSrc, 0x00, sizeof(BYTE) * nPxlBuf);	// 0X0으로 초기화

	pPxlFnt	= pPxlSrc;								// 먼저 Anti-Aliasing이 적용된 픽셀을 폰트 픽셀로 선택 





	// Chain에서 폰트에 대한 색상을 가져오는 단계
	pObj = pHead->N;

	INT x, y, t;
	INT	nOffsetX, nOffsetY, nSrc;
	INT ColorDst;

	while(pObj)
	{
		int Color;
		int width, height, pitch;
		int	of_x;
		BYTE* buf;

		width = pObj->w;
		height= pObj->h;
		pitch = pObj->p;
		buf	  = pObj->b;

		of_x= pObj->of_x;


		// 한 글자에 대한 출력
		for(y=0;y<height; ++y)
		{
			for(x=0;x<width; ++x)
			{
				BYTE Mono = buf[y*pitch+ x/8];

				t = x%8;
				Color = (Mono >>(7-t)) & 0x01;
			
				if(0 == Color)
					continue;


				nOffsetX = of_x  + pObj->of_l + x;
				nOffsetY = nOffy + pObj->of_t - y;


				nSrc = nBufWidth * nOffsetY + nOffsetX;

				// Buffer 크기 밖에 있으면....
				if(nSrc<0 || nSrc >=nPxlBuf)
					continue;

				pPxlSrc[nSrc] = 0xFF;
			}
		}

		pObj = pObj->N;
	}




	// Font의 높이가 14이상이면 Anti-Aliasing을 적용
	if( m_nFntH>14)
	{
		pPxlAnt = new BYTE[nPxlBuf];
		memset(pPxlAnt, 0x00, sizeof(BYTE) * nPxlBuf);		// 0X0으로 초기화
		pPxlFnt	= pPxlAnt;									// 텍스처에 적용될 픽셀을 Anitialiasing으로 만든 픽셀를 선택

		for(y=1;y<nBufHeight-1; ++y)
		{
			for(x=1;x<nBufWidth-1; ++x)
			{
				nSrc = nBufWidth * y + x;

				ColorDst = pPxlSrc[nSrc];
				

				if(0x00 == ColorDst)
				{
					// 8-con sampling
					if( m_nFntH>18)
					{
						int _0 = pPxlSrc[nBufWidth * (y-1) + x-1];
						int _1 = pPxlSrc[nBufWidth * (y-1) + x+0];
						int _2 = pPxlSrc[nBufWidth * (y-1) + x+1];
						int _3 = pPxlSrc[nBufWidth * (y+0) + x-1];
						int _4 = pPxlSrc[nBufWidth * (y+0) + x+1];
						int _5 = pPxlSrc[nBufWidth * (y+1) + x-1];
						int _6 = pPxlSrc[nBufWidth * (y+1) + x+0];
						int _7 = pPxlSrc[nBufWidth * (y+1) + x+1];
						ColorDst =_0 + _1 +_2 +_3 +_4 +_5 +_6 +_7;
						ColorDst /=10;
					}
					// 4-con sampling
					else
					{
						int _1 = pPxlSrc[nBufWidth * (y-1) + x+0];
						int _3 = pPxlSrc[nBufWidth * (y+0) + x-1];
						int _4 = pPxlSrc[nBufWidth * (y+0) + x+1];
						int _6 = pPxlSrc[nBufWidth * (y+1) + x+0];

						ColorDst = _1 + _3 + _4  +_6;
						ColorDst = (ColorDst)/5;
					}
				}

				pPxlAnt[nSrc] = ColorDst;
			}
		}

	}



	// 텍스처를 만들기 위해 변수를 설정하고 텍스처를 만든다.
	PDGE_TEXTURE pTexNew = NULL;
	TDGE_IMAGE tex_inf=
	{
		0x1906				// GL_ALPHA
		, 0x1401			// GL_UNSIGNED_BYTE
		, nBufWidth
		, nBufHeight
		, 1
		, 0x0
		, pPxlFnt
	};


	hr = DGE_CreateTexture((char*)"Buffer", &pTexNew, NULL, &tex_inf);

	// 현재 만들어진 텍스처는 해제하고 새로 만든 텍스처로 할당한다.
	if(m_pTex)
		DGE_DestroyTexture(&m_pTex);

	m_pTex = pTexNew;





	// 임시 버퍼 Buffer 해제
	if(pPxlSrc)		delete [] pPxlSrc;
	if(pPxlAnt)		delete [] pPxlAnt;



	// Chain 삭제
	pObj = pHead->N;
	while(pObj)
	{
		LHFTT_STR* t = pObj;
		pObj = pObj->N;

		if(t->b)
			free(t->b);

		delete t;
	}

	delete pHead;

	return hr;
}


INT CDGX_Font::SetColor(const DGE_COLORF* v)
{
	m_Color =  DGXCOLOR((const FLOAT*)v);		// Color
	return DGE_OK;
}


INT CDGX_Font::SetPos(const DGE_FLOAT2* v)
{
	m_vcPos	= DGXVECTOR2((const FLOAT*)v);		// Position
	return DGE_OK;
}


INT CDGX_Font::DrawTxt()
{
	INT	hr = DGE_EFAIL;
	
	if(NULL == m_pTex)
		return hr;

	hr = m_pSprite->DrawFont(m_pTex, NULL, &m_vcPos, &m_Color);

	return hr;
}


// Create Font
INT DGX_CreateFont(char* sCmd
					, PDGX_FONT* pData
					, DGE_HANDLE p1			// IDGE_Device*
					, DGE_HANDLE p2			// No Use
					, DGE_HANDLE p3			// No Use
					, DGE_HANDLE p4			// No Use
					 )
{
	CDGX_Font* pObj = 0;
	*pData		= 0;

	pObj = new CDGX_Font();

	if(DGE_FAILED(pObj->Create(p1, p2, p3, p4)))
	{
		delete pObj;
		return DGE_ECANNOTALLOCATED;
	}

	*pData = pObj;
	return DGE_OK;
}


INT DGX_DestroyFont(PDGX_FONT* pData)
{
	if(0 == *pData)
		return DGE_OK;

	delete *pData;
	(*pData) = 0;

	return DGE_OK;
}



INT	 DGX_TFFontOpen()		// Free Type Font Library Open
{
	if(CDGX_Font::m_FTTontLib)
		return DGE_OK;

	if (FT_Init_FreeType(&CDGX_Font::m_FTTontLib))
		return DGE_ECANNOTALLOCATED;


	return DGE_OK;
}


INT DGX_TFFontClose()		// FreeTypeFont Liberay Close
{
	if(NULL == CDGX_Font::m_FTTontLib)
		return DGE_OK;

	FT_Done_FreeType(CDGX_Font::m_FTTontLib);
	CDGX_Font::m_FTTontLib = NULL;

	return DGE_OK;
}


// wcslen() 함수가 윈도우와 linux 차이가 있어 윈도우에 맞추어 새로 정의함
DGE_INLINE INT	DGE_wcslen(const WCHAR* wcs)
{
	const WCHAR *eos = wcs;
	while( *eos++ ) ;

	return( (INT)(eos - wcs - 1) );
}




INT DGE_SetupTTFImageChain(LHFTT_STR** pOut, WCHAR* sDst, void* pFontFace, INT FontSize)
{
	INT		hr;
	INT		n;
	UINT	index=0;
	INT		offsetX = 0;
	INT		MaxHeight= 0;

	INT		iLen = DGE_wcslen(sDst);

	FT_Face		 m_ptFont= (FT_Face)pFontFace;
	LHFTT_STR* pHead = NULL;


	if(iLen<1)
		return DGE_EFAIL;


	pHead = new LHFTT_STR;
	

	for(n=0; n<iLen; ++n)
	{
		// 글리프 인덱스 구함
		index = FT_Get_Char_Index(m_ptFont,sDst[n]);	// Error: index ==> 0


		// 글리프 로드(내부에서 m_ptFont->glyph->bitmap.buffer 메모리를 해제한다.)
//		hr=FT_Load_Glyph(m_ptFont,index,FT_LOAD_DEFAULT | FT_LOAD_NO_BITMAP | FT_LOAD_NO_AUTOHINT);
		hr=FT_Load_Glyph(m_ptFont,index,FT_LOAD_DEFAULT | FT_LOAD_MONOCHROME | FT_LOAD_NO_AUTOHINT);


		// 랜더링(내부에서 m_ptFont->glyph->bitmap.buffer 메모리를 malloc으로 생성한다.)
//		hr=FT_Render_Glyph(m_ptFont->glyph, FT_RENDER_MODE_NORMAL);
		hr=FT_Render_Glyph(m_ptFont->glyph, FT_RENDER_MODE_MONO);


		// 화면으로 출력
		int width, height;
		width =m_ptFont->glyph->bitmap.width;
		height=m_ptFont->glyph->bitmap.rows;

		MaxHeight = __max(MaxHeight, height);	// 최대 높이값 받아옴

		width += m_ptFont->glyph->bitmap_left;


		if(0 == width)		// 공백과 같은 문자는 메모리가 없다 그냥 width를 중가 한다.
			width = int(FontSize * .75);

		
		LHFTT_STR* pObj = new LHFTT_STR(m_ptFont->glyph->bitmap.width
											, m_ptFont->glyph->bitmap.rows
											, m_ptFont->glyph->bitmap.pitch
											, m_ptFont->glyph->bitmap.buffer
											, m_ptFont->glyph->bitmap_left
											, m_ptFont->glyph->metrics.horiBearingY/64
											, offsetX);
		pHead->AddTail(pObj);

		offsetX += width;						// Offset을 증가 시킨다.
		m_ptFont->glyph->bitmap.buffer = NULL;	// FT_Load_Glyph() 함수에서 메모리를 해제 하지 못하도록 NULL로 설정한다.
	}

	*pOut = pHead;

	return (0x0FFF0000 & MaxHeight<<16) + (0x0000FFFF & offsetX);	// Height, Offset 반환해서 전체 글자의 폭을 지정할 수 있게 한다.
}




