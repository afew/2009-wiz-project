// Implementation of the Bmp.
//
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ImgBmp.h"


//	BMP Read
//	Offset Field Size	Brief
//		Contents
//
//
//	bmp_file -----------------------------------------------------------------------
//	0000h 2 byte    Identifier
//		The characters identifying the bitmap. The following entries are possible:
//		‘BM’ - Windows 3.1x, 95, NT, …
//		‘BA’ - OS/2 Bitmap Array
//		‘CI’ - OS/2 Color Icon
//		‘CP’ - OS/2 Color Pointer
//		‘IC’ - OS/2 Icon
//		‘PT’ - OS/2 Pointer
// 
//	0002h 4 byte(dword)    File Size
//		Complete file size in bytes.
// 
//	0006h 4 byte(dword)    Reserved
//		Reserved for later use.
// 
//	000Ah 4 byte(dword)	Bitmap Data Offset
//		Offset from beginning of file to the beginning of the bitmap data.
// 
//
//
//	bmp_info -----------------------------------------------------------------------
//	000Eh 4 byte(dword)	Bitmap Header Size
//		Length of the Bitmap Info Header used to describe the bitmap colors, compression, … The following sizes are possible:
//		28h - Windows 3.1x, 95, NT, …
//		0Ch - OS/2 1.x
//		F0h - OS/2 2.x
// 
//	0012h 4 byte(dword)	Width
//		Horizontal width of bitmap in pixels.
// 
//	0016h 4 byte(dword)	Height
//		Vertical height of bitmap in pixels.
// 
//	001Ah 2 byte(word)	Planes
//		Number of planes in this bitmap.
// 
//	001Ch 2 byte(word)	Bits Per Pixel
//		Bits per pixel used to store palette entry information. This also identifies in an indirect way the number of possible colors. Possible values are:
//		1 - Monochrome bitmap
//		4 - 16 color bitmap
//		8 - 256 color bitmap
//		16 - 16bit (high color) bitmap
//		24 - 24bit (true color) bitmap
//		32 - 32bit (true color) bitmap
// 
//	001Eh 4 byte(dword)	Compression
//		Compression specifications. The following values are possible:
//		0 - none (Also identified by BI_RGB)
//		1 - RLE 8-bit / pixel (Also identified by BI_RLE4)
//		2 - RLE 4-bit / pixel (Also identified by BI_RLE8)
//		3 - Bitfields  (Also identified by BI_BITFIELDS)
// 
//	0022h 4 byte(dword)	Bitmap Data Size
//		Size of the bitmap data in bytes. This number must be rounded to the next 4 byte boundary.
// 
//	0026h 4 byte(dword)	HResolution
//		Horizontal resolution expressed in pixel per meter.
// 
//	002Ah 4 byte(dword)	VResolution
//		Vertical resolution expressed in pixels per meter.
// 
//	002Eh 4 byte(dword)	Colors
//		Number of colors used by this bitmap. For a 8-bit / pixel bitmap this will be 100h or 256.
// 
//	0032h 4 byte(dword)	Important Colors
//		Number of important colors. This number will be equal to the number of colors when every color is important.
// 
//	0036h N * 4 byte	Palette
//		The palette specification. For every entry in the palette four bytes are used to describe the RGB values of the color in the following way:
//		1 byte for blue component
//		1 byte for green component
//		1 byte for red component
//		1 byte filler which is set to 0 (zero)
// 
//	0436h x bytes	Bitmap Data
//		Depending on the compression specifications, this field contains all the bitmap data bytes which represent indices in the color palette.



bmp_int	Bmp_FileRead(bmp_byte** pOutPxl		// Output Pixel
				,	bmp_int*	pOutImgW	// Output Image Width
				,	bmp_int*	pOutImgH	// Output Image Height
				,	bmp_int*	pOutImgC	// Output Image Channel(byte)
				,	char* sFile				// Source File
				)
{
	FILE*		fp			;
	bmp_long	lSize		;
	bmp_int		nImgC		;		// Channel Count
	bmp_byte*	pPxlS = NULL;


	struct bmp_file		fh	= {0};
	struct bmp_info		ih	= {0};
	bmp_byte*			pPalette= NULL;

	int	nSize=0;
	int	i =0;

	fp= fopen(sFile, "rb" );

	if(NULL == fp)
		return -1;

	fseek(fp, 0, SEEK_END);
	lSize = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	if(lSize<40)
	{
		fclose(fp);
		return -1;
	}


//	fread(&fh.bfType		, 1, sizeof(bmp_word )		, fp );
//	fread(&fh.bfSize		, 1, sizeof(bmp_dword)		, fp );
//	fread(&fh.bfReserved1	, 1, sizeof(bmp_word )		, fp );
//	fread(&fh.bfReserved2	, 1, sizeof(bmp_word )		, fp );
//	fread(&fh.bfOffBits		, 1, sizeof(bmp_dword)		, fp );
	
//	fread(&ih				, 1, sizeof(struct bmp_info), fp );



	// File Header
	fread(&fh.bfType		, 1, 2, fp );	//	word    bfType		;
	fread(&fh.bfSize		, 1, 4, fp );	//	dword   bfSize		;
	fread(&fh.bfReserved1	, 1, 2, fp );	//	word    bfReserved1	;
	fread(&fh.bfReserved2	, 1, 2, fp );	//	word    bfReserved2	;
	fread(&fh.bfOffBits		, 1, 4, fp );	//	dword   bfOffBits	;

	
	// Bmp Info
	fread(&ih.biSize			, 1, 4, fp );	//	dword biSize			;
	fread(&ih.biWidth			, 1, 4, fp );	//	long  biWidth			;
	fread(&ih.biHeight			, 1, 4, fp );	//	long  biHeight			;

	fread(&ih.biPlanes			, 1, 2, fp );	//	word  biPlanes			;
	fread(&ih.biBitCount		, 1, 2, fp );	//	word  biBitCount		;
	fread(&ih.biCompression		, 1, 4, fp );	//	dword biCompression	;
	fread(&ih.biSizeImage		, 1, 4, fp );	//	dword biSizeImage		;

	fread(&ih.biXPelsPerMeter	, 1, 4, fp );	//	long  biXPelsPerMeter	;
	fread(&ih.biYPelsPerMeter	, 1, 4, fp );	//	long  biYPelsPerMeter	;
	fread(&ih.biClrUsed			, 1, 4, fp );	//	dword biClrUsed			;
	fread(&ih.biClrImportant	, 1, 4, fp );	//	dword biClrImportant	;


	nImgC	= ih.biBitCount>>3;
	nSize	= fh.bfSize;	

	
	// Read Palette
	if(1 >= nImgC)
	{
		int num_colors = ih.biClrImportant;
		if(0 == num_colors || num_colors >256)
			num_colors = 256;

		pPalette = (bmp_byte*)malloc(num_colors * 4);
		fread(pPalette, 4, num_colors, fp);
	}


	fseek(fp, fh.bfOffBits, SEEK_SET);

	// Read Data
	pPxlS = (bmp_byte*)malloc( nSize );				// fh.bfSize가 (*pOutImgW) * (*pOutImgH) * nImgB 보다 크다.
	fread(pPxlS, 1, nSize, fp);

	fclose(fp);


	// Palette 색상을 24 비트 색상으로 변경. 
	// 256 색상일 경우 읽은 바이트는 팔레트의 인덱스가 된다.
	if(1 >= nImgC)
	{
		bmp_byte*	pPxIdx = pPxlS;					// 인덱스로 변경
		int			nIdx  = 0;

		nImgC = 3;									// 24 비트로 설정
		pPxlS = (bmp_byte*)malloc(nSize * nImgC);	// 색상 재할당.

		for(i=0; i<nSize; ++i)						// Palette는 4 byte r,g,b,f로 구성되어 있음.
		{
			nIdx = pPxIdx[i];

			pPxlS[i*nImgC + 0] = pPalette[ 4*nIdx+0 ];
			pPxlS[i*nImgC + 1] = pPalette[ 4*nIdx+1 ];
			pPxlS[i*nImgC + 2] = pPalette[ 4*nIdx+2 ];
		}


		free(pPxIdx);							// 인덱스 해제
		free(pPalette);							// Palette 해제
	}


	*pOutImgW	= ih.biWidth;					// 출력 데이터 복사.
	*pOutImgH	= ih.biHeight;
	*pOutImgC	= nImgC;
	*pOutPxl	= pPxlS;

	return 0;
}


