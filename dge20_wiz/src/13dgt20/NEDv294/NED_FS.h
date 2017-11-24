#ifndef _NED_FS_API_H
#define _NED_FS_API_H

#ifdef  __cplusplus
extern "C" {
#endif

#include <string.h>
#include <stdio.h>

#define GPH_GP2X_WIZ

/* NED_FS API */

void InitFileInfo(void);
#ifdef GPH_GP2X_WIZ

	FILE* NED_fopen(char* _filename, char* _modes);	 
	void NED_fclose(FILE* _stream); 
	size_t NED_fread(void* _ptr, size_t _size, size_t _n, FILE* _stream); 
	int NED_fseek(FILE* _stream, long _off, int _whence); 
	long NED_ftell(FILE* _stream); 
	int 	NED_IsNed(FILE *_stream); 
	
#endif /* #ifdef GPH_GP2X_WIZ */
 


#ifdef  __cplusplus
}
#endif

#endif	// _NED_FS_API_H

