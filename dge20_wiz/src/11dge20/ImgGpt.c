// Implementation of the Gpt.
//
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ImgGpt.h"


int Gpt_FileRead(unsigned char** oPxl	// Output Pixel

				,	int*		oFormat	// Output Pixel Format
				,	int*		oType	// Output Pixel Type

				,	int*		oImgW	// Output Image Width
				,	int*		oImgH	// Output Image Height
				,	int*		oImgD	// Output Image Depth
				,	int*		oImgC	// Output Image Color Key

				,	char*		sFile	// Source File
					)
{
	gpt_header	header={0};
	FILE*		fp;
	int			iSize=0;
	void*		pPxlS=NULL;

	// open the GPT file
	fp = fopen(sFile, "rb" );

	if (!fp)
	{
		printf("Err: %d, %s \t", __LINE__, __FILE__);
		printf("GPT File Open Err:%s\n", (char*)sFile);
		return -1;
	}


	// read Header
	fread(&header, sizeof(gpt_header), 1, fp);

	iSize = header.img_w * header.img_h * header.img_d;		// Image Size = Image Width * Height * Depth

	if(0 == iSize)
	{
		fclose(fp);
		return -1;
	}

	// alloc pixel
	pPxlS = malloc(iSize);

	// sheet Header+ ес
	fseek(fp, GPT_FMT_HEADER, SEEK_SET);

	// Read pixel
	fread(pPxlS, 1, iSize, fp);
	fclose(fp);

	// Setting Pixel and Pixel Info
	*oPxl	 = (unsigned char*)pPxlS;
	*oFormat= header.img_f;
	*oType	= header.img_t;

	*oImgW	= header.img_w;
	*oImgH	= header.img_h;
	*oImgD	= header.img_d;
	*oImgC	= header.img_c;

	return 0;
}



int Gpt_FileWrite(void*		pPxlS		// Input Pixel
				,	int		nFormat		// Input Pixel Format
				,	int		nType		// Input Pixel Type

				,	int		nImgW		// Input Image Width
				,	int		nImgH		// Input Image Height
				,	int		nImgD		// Input Image Depth
				,	int		nImgC		// Input Image Color Key

				,	char*	sFile		// Source File
					)
{
	gpt_header	header={0};
	FILE*		fp;
	int			iSize=0;

	iSize = nImgW * nImgH * nImgD;		// Image Size = Image Width * Height * Depth

	if(0==iSize)
	{
		printf("Err: %d, %s \t", __LINE__, __FILE__);
		printf("GPT File Size 0.\n");
		return -1;
	}

	// open the GPT file
	fp = fopen(sFile, "wb" );

	if (!fp)
	{
		printf("Err: %d, %s \t", __LINE__, __FILE__);
		printf("GPT File Open Err:%s\n", (char*)sFile);
		return -1;
	}

	header.img_v = GPT_FMT_VER;
	header.img_f = nFormat;
	header.img_t = nType;

	header.img_w = nImgW;
	header.img_h = nImgH;
	header.img_d = nImgD;
	header.img_c = nImgC;


	// read Header
	fwrite(&header, sizeof(gpt_header), 1, fp);

	// sheet Header+ ес
	fseek(fp, GPT_FMT_HEADER, SEEK_SET);

	// Read pixel
	fwrite(pPxlS, 1, iSize, fp);
	fclose(fp);

	return 0;
}

