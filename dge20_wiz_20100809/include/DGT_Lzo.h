// Lzo 2.03 App Interface.
// Lzo download --> http://www.oberhumer.com/
//
////////////////////////////////////////////////////////////////////////////////


#if defined(_WIN32) || defined(WIN32)
	#if _MSC_VER > 1000
	#pragma once
	#endif
#endif


#ifndef _DGT_Lzo_H_
#define _DGT_Lzo_H_


#ifdef __cplusplus
extern "C" {
#endif


int DgtLzo_Init();			// Lzo init
int DgtLzo_Close();			// Lzo release


// Memory Allocations of DgtLzo...() functions use malloc() functions. need free()
// All functions return >=0 if Success. failed return <0

int DgtLzo_CompressFile(								// Compress SrcFile to DstFile
						char* sDstFile					// Output Compress Data File Name
						, char* sSrcFile				// Source File Name
						);

int DgtLzo_DeCompressFile(char* sPath					// Output Decompress File Path. Out file ¡æ sPath/decompress file
						  , char* sSrcFile				// Compress Source File
						  );

int DgtLzo_DeCompressFromFile(							// get DeCompress Buffer from Compress File. need free(ppDstbuf)
							  unsigned char** bufOut	// DeCompress Data
							  , unsigned long* lsize	// DeCompress Data Size
							  , char* sSrcFile			// Compress Source File
							  );

int DgtLzo_CompressBuf(									// Compress Buffer to Buffer.
					   unsigned char** ppDstBuf			// Output Compress Buffer
					   , unsigned long* pSize			// Compress Size
					   , unsigned char* pSrc			// Source Data
					   , unsigned long iLenSrc			// Source Data Size
					   );

// malloc call. so you must be call free().
int DgtLzo_DeCompressBuf(								// DeCompress Buffer to Buffer
						 unsigned char** ppDstBuf		// Output Decompress Data
						 , unsigned long* pSize			// DeCompress Data Size
						 , unsigned char* pSrc			// Compress Source Data
						 , unsigned long iLenSrc		// Compress Source Data Size
						 );



#ifdef __cplusplus
}
#endif


#endif //_DGT_Lzo_H_



