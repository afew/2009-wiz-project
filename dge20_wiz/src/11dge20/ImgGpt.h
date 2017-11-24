//
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _ImgGpt_H_
#define _ImgGpt_H_

#ifdef __cplusplus
extern "C" {
#endif

enum
{
	GPT_FMT_VER				= 0x00020000,
	GPT_FMT_HEADER			= 64,
	GPT_FMT_ALPHA			= 0x1906,	// GL_ALPHA
	GPT_FMT_RGB				= 0x1907,	// GL_RGB
	GPT_FMT_RGBA			= 0x1908,	// GL_RGBA
	GPT_FMT_LUMINANCE		= 0x1909,	// GL_LUMINANCE
	GPT_FMT_LUMINANCE_ALPHA	= 0x190A,	// GL_LUMINANCE_ALPHA
	GPT_FMT_WORD_565		= 0x8363,	// GL_UNSIGNED_SHORT_5_6_5
	GPT_FMT_WORD_4444		= 0x8033,	// GL_UNSIGNED_SHORT_4_4_4_4
	GPT_FMT_WORD_5551		= 0x8034,	// GL_UNSIGNED_SHORT_5_5_5_1
};


typedef struct tag_gpt_header
{
	int		img_v;		// File Version
	int		img_f;		// Pixel Format	GL_RGB, RGBA, ....
	int		img_t;		// Pixel Type	GL_UNSIGNED_SHORT...

	int		img_w;		// Image Width
	int		img_h;		// Image Height
	int		img_d;		// Image Depth	1(byte), 2(byte), 3(byte), 4(byte)
	int		img_c;		// Image Color Key
}gpt_header;


int Gpt_FileRead(unsigned char** poPxl	// Output Pixel
				,	int*	poFormat	// Output Pixel Format
				,	int*	poType		// Output Pixel Type
				,	int*	poImgW		// Output Image Width
				,	int*	poImgH		// Output Image Height
				,	int*	poImgD		// Output Image Depth
				,	int*	poImgC		// Output Image Color Key
				,	char*	sFile		// Source File
					);

int Gpt_FileWrite(void*		pInPxl		// Input Pixel
				,	int		nFormat		// Input Pixel Format
				,	int		nType		// Input Pixel Type
				,	int		nImgW		// Input Image Width
				,	int		nImgH		// Input Image Height
				,	int		nImgD		// Input Image Depth
				,	int		nImgC		// Input Image Color Key
				,	char*	sFile		// Source File
					);


#ifdef __cplusplus
}
#endif


#endif


