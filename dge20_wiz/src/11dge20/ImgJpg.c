// Implementation of the Gpt.
//
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "jpeglib.h"

#include <setjmp.h>

#include "ImgJpg.h"


struct my_error_mgr
{
	struct jpeg_error_mgr pub;	/* "public" fields */

	jmp_buf setjmp_buffer;	/* for return to caller */
};


typedef struct my_error_mgr * my_error_ptr;



jpg_int Jpg_FileRead( jpg_byte**	pOutPxl		// Output Pixel
				,	jpg_int*		pOutImgW	// Image Width
				,	jpg_int*		pOutImgH	// Image Height
				,	jpg_int*		pOutImgC	// Image Channel(byte)
				,	char*		sFileName		// Image File Name
				)
{
	struct jpeg_decompress_struct cinfo;

	struct my_error_mgr jerr;
	/* More stuff */
	FILE * fp;		/* source file */
	int row_stride;		/* physical row width in output buffer */
	//	JSAMPARRAY buffer;	/* Output row buffer */

	int	lsize=0;
	unsigned char* pSrc;

	fp = fopen(sFileName, "rb");

	if(!fp)
	{
		fprintf(stderr, "can't open %s\n", sFileName);
		return -1;
	}


	cinfo.err = jpeg_std_error(&jerr.pub);
	jerr.pub.error_exit = NULL;


	if (setjmp(jerr.setjmp_buffer))
	{
		jpeg_destroy_decompress(&cinfo);
		fclose(fp);
		return -1;
	}
	jpeg_create_decompress(&cinfo);


	jpeg_stdio_src(&cinfo, fp);


	(void) jpeg_read_header(&cinfo, TRUE);
	(void) jpeg_start_decompress(&cinfo);


	row_stride = cinfo.output_width * cinfo.output_components;
//	buffer = (*cinfo.mem->alloc_sarray)((j_common_ptr) &cinfo, JPOOL_IMAGE, row_stride, 1);


	*pOutImgW = cinfo.output_width;
	*pOutImgH = cinfo.output_height;
	*pOutImgC = cinfo.output_components;

	lsize = (*pOutImgW) * (*pOutImgH) * (*pOutImgC);
	*pOutPxl = (unsigned char*)malloc( lsize);
	pSrc	 = *pOutPxl;

	memset(pSrc, 0, lsize);



	while (cinfo.output_scanline < cinfo.output_height)
	{
		(void) jpeg_read_scanlines(&cinfo, &pSrc, 1);

		/*put_scanline_someplace(buffer[0], row_stride);*/
		pSrc += row_stride;
	}
	


	(void) jpeg_finish_decompress(&cinfo);

	jpeg_destroy_decompress(&cinfo);

	fclose(fp);

	return 0;
}


