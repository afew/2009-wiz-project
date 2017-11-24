// Implementation of the IDGE_Image.
//
////////////////////////////////////////////////////////////////////////////////


#if defined(_WIN32) || defined(WIN32)
	#if _MSC_VER >= 1200
	#pragma warning(disable: 4996)
	#endif

	#include "ImgJpg.h"

#endif


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <DGE_Util.h>

#include "DGE_Base.h"
#include "ImgBmp.h"
#include "ImgTga.h"
#include "ImgPng.h"

#include "ImgGpt.h"


class CDGE_Image : public IDGE_Image
{
protected:
	UINT	m_RscType;				// Source Type
	UINT	m_Format;				// Pixel Format
	UINT	m_Type	;				// Pixel Type

	UINT	m_ImgW	;				// Image Width
	UINT	m_ImgH	;				// Image Height
	UINT	m_ImgD	;				// Image Depth
	UINT	m_ImgC	;				// Image Color Key

	BYTE*	m_pPxl	;				// Pixel Data

public:
	CDGE_Image();
	virtual ~CDGE_Image();

public:
	INT		CreateFromFile(DGE_HANDLE sFile, UINT colorKey=0x0);
	
	virtual UINT	GetRscType(){	return m_RscType;}
	virtual UINT	GetFormat(){	return m_Format;}
	virtual UINT	GetType() {		return m_Type;	}

	virtual UINT	GetImgW() {		return m_ImgW;	}
	virtual UINT	GetImgH() {		return m_ImgH;	}
	virtual UINT	GetImgD() {		return m_ImgD;	}
	virtual UINT	GetImgC() {		return m_ImgC;	}

	virtual BYTE*	GetPixel(){		return m_pPxl;	}

	virtual INT		SaveToFile(char* sFile			// Pixel data Save to TGA or GPT
							, INT ImgType=DGE_IMG_GPT);
};


void	SetupBGRtoRGBA(BYTE* pPxlDst, const BYTE* pPxlSrc, INT ImgW, INT ImgH, INT ImgD, BOOL bInv=FALSE);
void	SetupRGBtoRGBA(BYTE* pPxlDst, const BYTE* pPxlSrc, INT ImgW, INT ImgH, INT ImgD, BOOL bInv=FALSE);


typedef int				lc_int;
typedef unsigned int	lc_uint;
typedef unsigned char	lc_byte;
typedef unsigned long	lc_ulong;

int	LcImg_CreateImageFromFile(lc_byte** ppPxl		// Output Pixel

							, lc_uint* pnRscType	// Output nRscType
							, lc_uint* pnFormat		// Output Pixel Format
							, lc_uint* pnType		// Output Pixel Type

							, lc_uint* pnImgW		// Output Image Width
							, lc_uint* pnImgH		// Output Image Height
							, lc_uint* pnImgD		// Output Depth(byte)
							, lc_uint* pnImgC		// Output Color Key

							, char*	sFile			// Source FileName
					  )
{
	lc_int		hr		= -1;

	lc_int		nRscType= DGE_IMG_UNKNOWN;	// Resource Type
	lc_int		nFormat	= 0x0;			// Pixel Format
	lc_int		nType	= 0x0;			// Pixel Type

	lc_int		nImgW	= 0;
	lc_int		nImgH	= 0;
	lc_int		nImgD	= 0;			// Channel(byte)
	lc_int		nImgC	= 0x0;			// Color Key

	lc_byte		nBgR	= 0;
	lc_byte		nBgG	= 0;
	lc_byte		nBgB	= 0;
	lc_byte*	pPxlS	= NULL;			// Pixel Data


	char Ext[16]={0};
	char* p  = ::strrchr(sFile, '.' );
	if(p)
		strcpy(Ext, p+1);

	p = Ext;
	for(; 0 != *p; ++p)
	{
		if('A'<=*p && *p<='Z')
			*p += ('a'-'A');
	}


	if	   (0== DgeStr_Stricmp(Ext, "bmp" ))	nRscType = DGE_IMG_BMP;
	else if(0== DgeStr_Stricmp(Ext, "tga" ))	nRscType = DGE_IMG_TGA;
	else if(0== DgeStr_Stricmp(Ext, "png" ))	nRscType = DGE_IMG_PNG;
	else if(0== DgeStr_Stricmp(Ext, "gptf"))	nRscType = DGE_IMG_GPT;

#if defined(_WIN32) || defined(WIN32)
	else if(0== DgeStr_Stricmp(Ext, "jpg" ))	nRscType = DGE_IMG_JPG;
#endif

	else									
		return DGE_ECANNOTFIND_RESOURCE;



	if	   (nRscType == DGE_IMG_BMP)	hr = Bmp_FileRead(&pPxlS, &nImgW, &nImgH, &nImgD, sFile);
	else if(nRscType == DGE_IMG_TGA)	hr = Tga_FileRead(&pPxlS, &nImgW, &nImgH, &nImgD, sFile);
	else if(nRscType == DGE_IMG_PNG)	hr = Png_FileRead(&pPxlS, (lc_ulong*)&nImgW, (lc_ulong*)&nImgH, (lc_ulong*)&nImgD, &nBgR, &nBgG, &nBgB, sFile);
	else if(nRscType == DGE_IMG_GPT)	hr = Gpt_FileRead(&pPxlS, &nFormat, &nType, &nImgW, &nImgH, &nImgD, &nImgC, sFile);

#if defined(_WIN32) || defined(WIN32)
	else if(nRscType == DGE_IMG_JPG)	hr = Jpg_FileRead(&pPxlS, &nImgW, &nImgH, &nImgD, sFile);
#endif



	if(hr<0)
	{
		printf("Err: %d, %s \t", __LINE__, __FILE__);
		printf("Failed LcImg_CreateImageFromFile: %s\n", sFile);
		return DGE_ECANNOTALLOCATED;
	}


	*ppPxl		= pPxlS;
	*pnRscType	= nRscType;
	*pnImgW		= nImgW;
	*pnImgH		= nImgH;
	*pnImgD		= nImgD;
	*pnFormat	= nFormat;
	*pnType		= nType;
	*pnImgC		= nImgC;

	return DGE_OK;
}






CDGE_Image::CDGE_Image()
{
	m_RscType	= 0;
	m_Format	= 0;
	m_Type		= 0;

	m_ImgW = 0;
	m_ImgH = 0;
	m_ImgD = 0;
	m_ImgC = 0;
	m_pPxl = NULL;
}


CDGE_Image::~CDGE_Image()
{
	SAFE_FREE(	m_pPxl	);
}



// 채널을 리턴.
// 내부에서 32bit 픽셀을 만든다.
INT CDGE_Image::CreateFromFile(DGE_HANDLE sFile, UINT colorkey)
{
	INT		hr		= -1;
	BYTE*	pPxlS	= NULL;

	char tFile[DGE_MAX_PATH ]={0};
	char drive[DGE_MAX_DRIVE]={0};
	char dir  [DGE_MAX_DIR  ]={0};
	char fname[DGE_MAX_FNAME]={0};
	char ext  [DGE_MAX_EXT  ]={0};



#if !defined(_WIN32) && !defined(WIN32)

	// gptf로 변환된 파일을 찾는다.
	DgeStr_SplitPath((char*)sFile, drive, dir, fname, ext);
	sprintf(tFile, "%s%s%s%s", drive, dir, fname, ".gptf");

	hr = LcImg_CreateImageFromFile((lc_byte**)&pPxlS
							  , (unsigned int*)&m_RscType
							  , (unsigned int*)&m_Format
							  , (unsigned int*)&m_Type

							  , (unsigned int*)&m_ImgW
							  , (unsigned int*)&m_ImgH
							  , (unsigned int*)&m_ImgD
							  , (unsigned int*)&m_ImgC

							  , tFile
							  );

#endif


	// 변환된 gptf파일이 없으면 원 파일을 찾는다.
	if(DGE_FAILED(hr))
	{
		hr = LcImg_CreateImageFromFile((lc_byte**)&pPxlS
							  , (unsigned int*)&m_RscType
							  , (unsigned int*)&m_Format
							  , (unsigned int*)&m_Type

							  , (unsigned int*)&m_ImgW
							  , (unsigned int*)&m_ImgH
							  , (unsigned int*)&m_ImgD
							  , (unsigned int*)&m_ImgC

							  , (char*)sFile
							  );
	}

	if(DGE_FAILED(hr))
	{
		printf("Err: %d, %s \t", __LINE__, __FILE__);
		printf("Image Failed: %s\n", (char*)sFile);
		return DGE_ECANNOTFIND_RESOURCE;
	}



	if(0x0 == m_ImgC && colorkey)
		m_ImgC = colorkey;



	// is not GPT format. convert, save, reload pixel
	if(DGE_IMG_GPT != m_RscType)
	{
		BYTE*	pPxlT = NULL;
		UINT	RscType=m_RscType;
		UINT	Format=m_Format;
		UINT	Type = m_Type;
		UINT	ImgW = m_ImgW;
		UINT	ImgH = m_ImgH;
		UINT	ImgD = m_ImgD;
		UINT	ImgC = m_ImgC;



		// Make and Convert 32bit RGBA Pixel

		pPxlT	= (BYTE*)malloc(m_ImgW * m_ImgH * 4);

		if(DGE_IMG_BMP == m_RscType)		SetupBGRtoRGBA(pPxlT, pPxlS, ImgW, ImgH, ImgD);
		else if(DGE_IMG_TGA == m_RscType)	SetupBGRtoRGBA(pPxlT, pPxlS, ImgW, ImgH, ImgD);
		else if(DGE_IMG_PNG == m_RscType)	SetupRGBtoRGBA(pPxlT, pPxlS, ImgW, ImgH, ImgD, TRUE);

#if defined(_WIN32) || defined(WIN32)
		else if(DGE_IMG_JPG == m_RscType)	SetupRGBtoRGBA(pPxlT, pPxlS, ImgW, ImgH, ImgD, TRUE);
#endif

		// free original source pixel from file
		SAFE_FREE(	pPxlS	);




		// Make 16bit pixel
		pPxlS = (BYTE*)malloc(m_ImgW * m_ImgH * sizeof(WORD));


		// convert 32bit to 16 bit pixel and set up format, type.
		hr = DGE_Convert32to16Color((WORD*)pPxlS, &Format, &Type, pPxlT, ImgW, ImgH, ImgD, ImgC);

		// free 32bit temp pixel
		SAFE_FREE(	pPxlT	);

		if(DGE_FAILED(hr))
		{
			SAFE_FREE(	pPxlS	);
			return DGE_EFAIL;
		}


		// setting depth to 2(16 bit)
		ImgD = 2;



//// save 16bit pixel to gptf file format and reload gptf in Windows system
#if defined(_WIN32) || defined(WIN32)		

		// setting file name
		DgeStr_SplitPath((char*)sFile, drive, dir, fname, ext);
		sprintf(tFile, "%s%s%s%s", drive, dir, fname, ".gptf");

		::Gpt_FileWrite(pPxlS, Format, Type, ImgW, ImgH, ImgD, ImgC, tFile);


		// free 16bit pixel
		SAFE_FREE(	pPxlS	);


		// reload gptf file
		hr = LcImg_CreateImageFromFile((lc_byte**)&pPxlS
						  , &RscType
						  , &Format
						  , &Type

						  , &ImgW
						  , &ImgH
						  , &ImgD
						  , &ImgC

						  , tFile
						  );

		if(hr<0)
		{
			printf("Err: %d, %s \t", __LINE__, __FILE__);
			printf("Image Failed: %s\n", (char*)sFile);
			return DGE_ECANNOTFIND_RESOURCE;
		}

#endif

		m_RscType= RscType;
		m_Format= Format;
		m_Type	= Type;
		m_ImgW	= ImgW;
		m_ImgH	= ImgH;
		m_ImgD	= ImgD;
		m_ImgC	= ImgC;
	}


	// Set pixel pointer.
	m_pPxl = pPxlS;


	return m_ImgD;
}



INT CDGE_Image::SaveToFile(char* sFile, INT ImgType)
{
	if(DGE_IMG_GPT == ImgType)
	{
		return ::Gpt_FileWrite(m_pPxl, m_Format, m_Type, m_ImgW, m_ImgH, m_ImgD, m_ImgC, sFile);
	}
	else if(DGE_IMG_TGA == ImgType)
	{
	}

	return DGE_OK;
}



INT DGE_CreateImage(char* sCmd					// Null is File, "Resouce" is Memory buffer. "Buffer"
				   , PDGE_IMAGE* pData
				   , DGE_HANDLE p1				// sCmd => NULL →File Name, "Resource" →Resource ID, "Buffer" → Buffer Width
				   , DGE_HANDLE p2				// "Buffer" → Buffer Height
				   , DGE_HANDLE p3				// Color Key
				   , DGE_HANDLE p4				// No Use
					 )
{
	INT	hr = 0;
	CDGE_Image*	pObj = NULL;
	UINT		nImgC= 0;		// Pixel Color Key

	*pData	= NULL;


	if(p3)
		nImgC = *((UINT*)p3);

	
	pObj = new CDGE_Image;

	if(NULL == sCmd)
	{
		hr = pObj->CreateFromFile(p1, nImgC);
	}
	else if( 0 == DgeStr_Stricmp(sCmd, "Resource"))
	{
		hr = DGE_ENOTIMPLEMENTED;
	}
	else if( 0 == DgeStr_Stricmp(sCmd, "Buffer"))
	{
		hr = DGE_ENOTIMPLEMENTED;
	}
	else
	{
		hr = DGE_EINVALIDATE_CALL;
	}


	if(DGE_FAILED(hr))
	{
		delete pObj;
		return hr;
	}


	*pData = pObj;
	return DGE_OK;
}



INT DGE_DestroyImage(PDGE_IMAGE* pData)
{
	if(NULL == *pData)
		return DGE_OK;

	delete *pData;
	(*pData) = NULL;

	return DGE_OK;
}














void SetupBGRtoRGBA(BYTE* pPxlD, const BYTE* pPxlS, INT ImgW, INT ImgH, INT ImgD, BOOL bInv)
{
	INT	x=0, y=0;
	INT n1, n2;
	BYTE* pPxlT = NULL;
			
	BYTE B, G, R, A;

	// convert BGR or BGRA --> RGBA
	for(y=0; y<ImgH; ++y)
	{
		for(x=0; x<ImgW; ++x)
		{
			n1 = (y*ImgW + x)* ImgD;
			n2 = (y*ImgW + x)* 4;
			
			B = pPxlS[n1 +0];
			G = pPxlS[n1 +1];
			R = pPxlS[n1 +2];
			A = 0xFF;

			if(4 == ImgD)
				 A = pPxlS[n1 +3];

			pPxlD[n2+0] = R;
			pPxlD[n2+1] = G;
			pPxlD[n2+2] = B;
			pPxlD[n2+3] = A;
		}
	}


	// SDL에서는 이미지를 뒤집어야 한다.
	// Opengl에서는 이렇게 할 필요가 없다.
	if(bInv)
	{
		pPxlT	= (BYTE*)malloc(sizeof(BYTE) * ImgW * ImgH * 4);	// rgba
		memcpy(pPxlT, pPxlD, sizeof(BYTE) * ImgW * ImgH * 4);

		for(y=0; y < ImgH; ++y)
		{
			for(x=0; x < ImgW; ++x)
			{
				n1 =  ((       y) * ImgW + x) * 4;
				n2 =  ((ImgH-1-y) * ImgW + x) * 4;

				pPxlD[n1+0] = pPxlT[n2 + 0];
				pPxlD[n1+1] = pPxlT[n2 + 1];
				pPxlD[n1+2] = pPxlT[n2 + 2];
				pPxlD[n1+3] = pPxlT[n2 + 3];
			}
		}
	}

	SAFE_FREE(	pPxlT	);
}


void SetupRGBtoRGBA(BYTE* pPxlD, const BYTE* pPxlS, INT ImgW, INT ImgH, INT ImgD, BOOL bInv)
{
	INT x=0, y=0;

	INT n1, n2;
	
	BYTE R, G, B, A;

	// for 32 or 24 bit
	// PNG Order: R, G, B, A
	// Window, B, G, R

	for(y=0; y < ImgH; ++y)
	{
		for(x=0; x < ImgW; ++x)
		{
			// OpenGL에서 JPG, PNG, PNG는 뒤집어 주어야 한다.
			if(bInv)
			{
				n1 =  ((       y) * ImgW + x) * ImgD;
				n2 =  ((ImgH-1-y) * ImgW + x) * 4;
			}
			else
			{
				n1 = (y*ImgW + x)* ImgD;
				n2 = (y*ImgW + x)* 4;
			}
			
			R = pPxlS[n1 +0];
			G = pPxlS[n1 +1];
			B = pPxlS[n1 +2];
			A = 0xFF;

			if(4 == ImgD)
				 A = pPxlS[n1 +3];

			pPxlD[n2 +0] = R;
			pPxlD[n2 +1] = G;
			pPxlD[n2 +2] = B;
			pPxlD[n2 +3] = A;
		}
	}
}


// 색상 변경 32 ==> 16
//	Color Key: 0x00000000 → disable the colorkey
//	Channel == 3
//		Color Key enable  → GL_UNSIGNED_SHORT_5_6_5
//		Color Key disable → GL_UNSIGNED_SHORT_5_5_5_1
//	Channel == 4
//		regardless of Color Key → GL_UNSIGNED_SHORT_4_4_4_4
INT DGE_Convert32to16Color(WORD* pDst, UINT* oFormat, UINT* oType, const BYTE* pSrc, INT nImgW, INT nImgH, INT nImgD, DWORD dColorKey)
{
	INT		COLOR_BIT = 0;
	INT		x, y;

	INT		n1, n2;
	UINT	R, G, B, A;

	//	a		r	g	b;
	//	0xFF 0xFF 0xFF 0xFF;
//	UINT	dColorA = (dColorKey & 0xFF000000) >>24;
	UINT	dColorR = (dColorKey & 0x00FF0000) >>16;
	UINT	dColorG = (dColorKey & 0x0000FF00) >> 8;
	UINT	dColorB = (dColorKey & 0x000000FF) >> 0;


	// Setup Pixel Format;
	if(3 == nImgD)
	{
		if(0x0 == dColorKey)
			COLOR_BIT = DGE_FMT_WORD_565;
		else
			COLOR_BIT = DGE_FMT_WORD_5551;
	}
	else if(4 == nImgD)
	{
		COLOR_BIT = DGE_FMT_WORD_4444;
	}
	else
		return -1;


	if(DGE_FMT_WORD_565 == COLOR_BIT)
	{
		for(y=0; y<nImgH; ++y)
		{
			for(x=0; x<nImgW; ++x)
			{
				n1 = (y*nImgW + x)* 4;
				n2 = (y*nImgW + x);

				R = pSrc[n1+0];
				G = pSrc[n1+1];
				B = pSrc[n1+2];

				R >>= 3;
				G >>= 2;
				B >>= 3;
				pDst[n2] = (B<<0) | (G<<5) | (R<<11);
			}
		}
	}

	else if(DGE_FMT_WORD_5551 == COLOR_BIT)
	{
		for(y=0; y<nImgH; ++y)
		{
			for(x=0; x<nImgW; ++x)
			{
				n1 = (y*nImgW + x)* 4;
				n2 = (y*nImgW + x);

				R = pSrc[n1+0];
				G = pSrc[n1+1];
				B = pSrc[n1+2];

				//  색상이 일치하지 않으면 불투명
				if(	dColorR != R || dColorG != G || dColorB != B )
					A = 0xFF;
				else
					A = 0x00;

				R >>= 3;
				G >>= 3;
				B >>= 3;
				A >>= 7;
				pDst[n2] = (A<<0) | (B<<1) | (G<<6) | (R<<11);
			}
		}
	}

	else if(DGE_FMT_WORD_4444 == COLOR_BIT)
	{
		for(y=0; y<nImgH; ++y)
		{
			for(x=0; x<nImgW; ++x)
			{
				n1 = (y*nImgW + x)* 4;
				n2 = (y*nImgW + x);

				R = pSrc[n1+0];
				G = pSrc[n1+1];
				B = pSrc[n1+2];
				A = pSrc[n1+3];

				R >>= 4;
				G >>= 4;
				B >>= 4;
				A >>= 4;
				pDst[n2] = (A<<0) | (B<<4) | (G<<8) | (R<<12);
			}
		}
	}


	// Type 설정
	if(oType)
		*oType = COLOR_BIT;

	// 포맷 설정
	if(oFormat)
	{
		if	   (DGE_FMT_WORD_565  == COLOR_BIT)	*oFormat = DGE_FMT_RGB;
		else if(DGE_FMT_WORD_5551 == COLOR_BIT)	*oFormat = DGE_FMT_RGBA;
		else if(DGE_FMT_WORD_4444 == COLOR_BIT)	*oFormat = DGE_FMT_RGBA;
	}

	
	// Color Bit Format를 반환
	return COLOR_BIT;
}

