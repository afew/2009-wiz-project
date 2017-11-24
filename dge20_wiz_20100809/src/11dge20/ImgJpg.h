// Interface for the Jpg File.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _ImgJpg_H_
#define _ImgJpg_H_

#ifdef __cplusplus
extern "C" {
#endif


typedef	int				jpg_int;
typedef	unsigned long	jpg_dword;
typedef	unsigned char	jpg_byte;

jpg_int Jpg_FileRead( jpg_byte** pOutPxl	// Output Pixel
					, jpg_int*	pOutImgW	// Image Width
					, jpg_int*	pOutImgH	// Image Height
					, jpg_int*	pOutImgC	// Image Channel(byte)
					, char*		sFile		// Image File Name
				);


#ifdef __cplusplus
}
#endif


#endif


