// Implementation of the Tga.
//
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ImgTga.h"


//void MergeByte(tga_byte* pxl, unsigned char *src,int bytes)
//{
//	// R: pxl[0]
//	// G: pxl[1]
//	// B: pxl[2]
//	// A: pxl[3]
//
//	if (bytes == 4)
//	{
//		pxl[0] = src[0];
//		pxl[1] = src[1];
//		pxl[2] = src[2];
//		pxl[3] = src[3];
//	}
//	else if (bytes == 3)
//	{
//		pxl[0] = src[0];
//		pxl[1] = src[1];
//		pxl[2] = src[2];
//		pxl[3] = 0xFF;
//	}
//	else if (bytes == 2)
//	{
//		pxl[0] = (src[1] & 0x7c) << 1;
//		pxl[1] = ((src[1] & 0x03) << 6) | ((src[0] & 0xe0) >> 2);
//		pxl[2] = (src[0] & 0x1f) << 3;
//		pxl[3] = (src[1] & 0x80);
//	}
//}






tga_int	Tga_FileRead(tga_byte** pOutPxl		// Output Pixel
				,	tga_int*	pOutImgW	// Output Image Width
				,	tga_int*	pOutImgH	// Output Image Height
				,	tga_int*	pOutImgC	// Output Image Channel(byte)
				,	char* sFile				// Source File
				)
{
	FILE*		fp =NULL;

	// Header
	tga_byte	IDLength	=0;		// ID Length
	tga_byte	ColorMapType=0;		// Color Map Type
	tga_byte	ImageType	=0;		// Image type


	// Color Map Specification
	tga_ushort	OffsetMapTable=0;
	tga_ushort	ColorMapLength=0;
	tga_byte	ColorBits=0;


	// Image dimensions and format
	tga_ushort	x_org =0;			// absolute coordinate of lower-left corner for displays where origin is at the lower left
	tga_ushort	y_org =0;			// as for X-origin
//	tga_ushort	nImgW =0;			// Image Width
//	tga_ushort	nImgH =0;			// Image Height
	tga_byte	nDepth=0;			// Pixel depth: bits per pxl
	tga_byte	ImgDsc=0;			// Image descriptor (1 byte): bits 3-0 give the alpha channel depth, bits 5-4 give direction



	// For Final Targa Data
	tga_ushort	nImgW =0;			// Image Width
	tga_ushort	nImgH =0;			// Image Height
	tga_byte	nImgC =0;			// Channel Count
	long		nImgSize=0;			// size of TGA image
	tga_byte*	pPxlS = NULL;		// Dest Pixel
	tga_byte*	pPxlT = NULL;		// Temp Pixel


	unsigned char src[8]={0};
	int n=0, i=0, j=0;


	// open the TGA file
	fp = fopen(sFile, "rb" );

	if (!fp)
	{
		printf("Err: %d, %s \t", __LINE__, __FILE__);
		printf("TGA File Open Err:%s\n", (char*)sFile);
		return -1;
	}
	
	// Read 3 bytes
	fread(&IDLength		, 1, 1, fp);	// Length of the image Id field
	fread(&ColorMapType	, 1, 1, fp);	// Whether a color map is included
	fread(&ImageType	, 1, 1, fp);	// Compression and color types

	// Read Color Map Specification
	fread(&OffsetMapTable, 2, 1, fp);	// First entry index (2 bytes): Offset into the color map table
	fread(&ColorMapLength, 2, 1, fp);	// Color map length (2 bytes): number of entries
	fread(&ColorBits     , 1, 1, fp);	// Color map entry size (1 byte): number of bits per pxl

	// Read Image Specification
	fread(&x_org  , 2, 1, fp);			// X-origin (2 bytes): absolute coordinate of lower-left corner for displays where origin is at the lower left
	fread(&y_org  , 2, 1, fp);			// Y-origin (2 bytes): as for X-origin
	fread(&nImgW  , 2, 1, fp);			// Image width (2 bytes): width in pixels
	fread(&nImgH  , 2, 1, fp);			// Image height (2 bytes): height in pixels
	fread(&nDepth , 1, 1, fp);			// Pixel depth (1 byte): bits per pxl
	fread(&ImgDsc , 1, 1, fp);			// Image descriptor (1 byte): bits 3-0 give the alpha channel depth, bits 5-4 give direction


	//	ImageType:
	//	0 no image data is present,
	//	1 uncompressed, color-mapped image,
	//	2 uncompressed, true-color image,
	//	3 uncompressed, black-and-white image,
	//	9 run-length encoded, color-mapped Image,
	//	10 run-length encoded, true-color image and,
	//	11 run-length encoded, black-and-white Image
	if( !(2 == ImageType || 10 == ImageType))
	{
		printf("Err: %d, %s \t", __LINE__, __FILE__);
		printf("TGA Err: We can only support only true-color(2 or 10).\n");
		fclose(fp);
		return -1;
	}


	fseek(fp, IDLength + ColorMapType * ColorMapLength, SEEK_CUR);


	// colormode -> 3 = BGR, 4 = BGRA
	nImgC		= nDepth>>3;
	nImgSize	= nImgW * nImgH * nImgC;
	pPxlS		= (tga_byte*)malloc(nImgSize);


	// Uncompressed
	if(2 == ImageType)
	{
		fread(pPxlS, sizeof(tga_byte), nImgSize, fp);
	}

	// Compressed
	else if(10 == ImageType)
	{
		pPxlT	= pPxlS;

		while (n < nImgW * nImgH)
		{
			
			if (fread(src, 1, nImgC+1, fp) != (size_t)(nImgC+1))
				break;

			j = src[0] & 0x7f;

			memcpy(&pPxlT[n*nImgC], &src[1], nImgC);
			++n;

			// RLE chunk
			if (src[0] & 0x80)
			{
				for (i=0;i<j;++i)
				{
					memcpy(&pPxlT[n*nImgC], &src[1], nImgC);
					++n;
				}
			}

			// Normal chunk
			else
			{
				for (i=0;i<j;++i)
				{
					if (fread(src, 1, nImgC, fp) != nImgC)
						break;

					memcpy( &pPxlT[n*nImgC], src, nImgC);
					++n;
				}
			}
			
		}// while

	}

	fclose(fp);


	// Setting Pixel and Pixel Info
	*pOutPxl  = pPxlS;
	*pOutImgW = nImgW;
	*pOutImgH = nImgH;
	*pOutImgC = nImgC;

	return 0;
}



