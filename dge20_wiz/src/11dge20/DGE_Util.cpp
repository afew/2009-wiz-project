	// Implementation of the DGE System.
//
////////////////////////////////////////////////////////////////////////////////

#if defined(_WIN32) || defined(WIN32)
	#if _MSC_VER >= 1200
	#pragma warning(disable: 4996)
	#endif

	#include <io.h>
	#include <direct.h>

#else

	#include <unistd.h>
	#include <sys/stat.h>

#endif


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "DGE_Type.h"
#include "DGE_Util.h"



////////////////////////////////////////////////////////////////////////////////
// Memory

void* DgeMem_Allock(int BufferSize, int Count, int bInitSetValue)
{
	void* pOut = NULL;
	int	Size =BufferSize * Count;

	pOut = malloc(BufferSize * Count);
	memset(pOut, bInitSetValue, Size);
	return pOut;
}

void DgeMem_Free(void** v)
{
	if(*v)
	{
		free(*v);
		*v = NULL;
	}
}


////////////////////////////////////////////////////////////////////////////////
// String

inline int DgeStr_tolower(int c)
{
	if('A' <= c && c<='Z')
		return c + 'a' - 'A';

	return c;
}

inline int DgeStr_toupper(int c)
{
	if('a' <= c && c<='a')
		return c - 'a' + 'A';

	return c;
}


int DgeStr_Stricmp (const char* str1, const char* str2)
{
    int s1, s2;

    do
	{
		if ( ((s1 = (unsigned char)(*(str1++))) >= 'A') && (s1 <= 'Z') )
			s1 -= 'A' - 'a';

		if ( ((s2 = (unsigned char)(*(str2++))) >= 'A') && (s2 <= 'Z') )
            s2 -= 'A' - 'a';

	} while ( s1 && (s1 == s2) );

    return(s1 - s2);
}



int DgeStr_Strnicmp(const char* str1, const char* str2, size_t count)
{
    int s1, s2;

    do
	{
		if ( ((s1 = (unsigned char)(*(str1++))) >= 'A') && (s1 <= 'Z') )
			s1 -= 'A' - 'a';

		if ( ((s2 = (unsigned char)(*(str2++))) >= 'A') && (s2 <= 'Z') )
			s2 -= 'A' - 'a';

	} while ( --count && s1 && (s1 == s2) );

    return ( s1 - s2 );
}


void DgeStr_SplitPath(const char *path, char *drive, char *dir, char *fname, char *ext)
{
	register char *p;
	char *last_slash = NULL, *dot = NULL;
	unsigned len;


	if ((strlen(path) >= (DGE_MAX_DRIVE - 2)) && (*(path + DGE_MAX_DRIVE - 2) == ':'))
	{
		if (drive)
		{
			strncpy(drive, path, DGE_MAX_DRIVE - 1);
			*(drive + DGE_MAX_DRIVE-1) = '\0';
		}

		path += DGE_MAX_DRIVE - 1;
	}

	else if (drive)
	{
		*drive = '\0';
	}

	/* extract path string, if any.  Path now points to the first character
	* of the path, if any, or the filename or extension, if no path was
	* specified.  Scan ahead for the last occurence, if any, of a '/' or
	* '\' path separator character.  If none is found, there is no path.
	* We will also note the last '.' character found, if any, to aid in
	* handling the extension.
	*/

	for (last_slash = NULL, p = (char *)path; *p; p++)
	{

		if (*p == '/' || *p == '\\')
			/* point to one beyond for later copy */
			last_slash = p + 1;
		else if (*p == '.')
			dot = p;
	}

	if (last_slash)
	{

		/* found a path - copy up through last_slash or max. characters
		* allowed, whichever is smaller
		*/

		if (dir)
		{
			len = __min((unsigned)(((char *)last_slash - (char *)path) / sizeof(char)),
				(DGE_MAX_DIR - 1));
			strncpy(dir, path, len);
			*(dir + len) = '\0';
		}
		path = last_slash;
	}

	else if (dir)
	{

		/* no path found */

		*dir = '\0';
	}

	/* extract file name and extension, if any.  Path now points to the
	* first character of the file name, if any, or the extension if no
	* file name was given.  Dot points to the '.' beginning the extension,
	* if any.
	*/

	if (dot && (dot >= path))
	{
		/* found the marker for an extension - copy the file name up to
		* the '.'.
		*/
		if (fname)
		{
			len = __min((unsigned)(((char *)dot - (char *)path) / sizeof(char)),
				(DGE_MAX_FNAME - 1));
			strncpy(fname, path, len);
			*(fname + len) = '\0';
		}
		/* now we can get the extension - remember that p still points
		* to the terminating nul character of path.
		*/
		if (ext)
		{
			len = __min((unsigned)(((char *)p - (char *)dot) / sizeof(char)),
				(DGE_MAX_EXT - 1));
			strncpy(ext, dot, len);
			*(ext + len) = '\0';
		}
	}
	else
	{
		/* found no extension, give empty extension and copy rest of
		* string into fname.
		*/
		if (fname)
		{
			len = __min((unsigned)(((char *)p - (char *)path) / sizeof(char)),
				(DGE_MAX_FNAME - 1));
			strncpy(fname, path, len);
			*(fname + len) = '\0';
		}
		if (ext)
		{
			*ext = '\0';
		}
	}
}



////////////////////////////////////////////////////////////////////////////////
// File

long DgeFile_FindFirst(TDGE_FINDDATA* fd, const char* sSearchPath)
{
#if defined(_WIN32) || defined(WIN32)
	long handle;
	handle=_findfirst(sSearchPath, (struct _finddata_t*)fd);
	return handle;
#else
	return DGE_ENOTIMPLEMENTED;
#endif
}

int DgeFile_FindNext(long handle, TDGE_FINDDATA* pFindData)
{
#if defined(_WIN32) || defined(WIN32)
	int hr =_findnext(handle, (struct _finddata_t*)pFindData);
	return hr;
#else
	return DGE_ENOTIMPLEMENTED;
#endif
}

int DgeFile_FindClose(long handle)
{
#if defined(_WIN32) || defined(WIN32)
	return _findclose(handle);
#else
	return DGE_ENOTIMPLEMENTED;
#endif
}



inline int t_Multiple4(int v){ return ((v + 7)/4 )*4; }

void t_DgeFile_Gather(TDGE_FINF** pCur, const char* sDir)
{
	char sSearchPath[260]={0};

	TDGE_FINDDATA fd;
	long handle;

	int result=1;

	sprintf(sSearchPath,"%s/*.*", sDir);

	handle= DgeFile_FindFirst(&fd, sSearchPath);

	if (handle == -1)
		return;

	while (result != -1)
	{
		// Folder
		if( (fd.attrib & 0x10) && (fd.name[0] !='.'))
		{
//			time_t	t = fd.time_write;
//
//			char	sTime[160]={0};
//			strcpy(sTime, ctime(&t) );
//			struct tm *gmt = gmtime(&t);
//			struct tm *lcl = localtime(&t);

			char	tNode[260]={0};
			int		iLen = 0;
			sprintf(tNode, "%s/%s", sDir, fd.name);
			iLen	= strlen(tNode);
			iLen	= t_Multiple4(iLen);

			TDGE_FINF*	pNode = (TDGE_FINF*)DgeMem_Allock(sizeof(TDGE_FINF), 1, 0x0);
			pNode->nType	= 0x10;				// Folder: 0x10
			pNode->iname	= iLen;				// Length of File Name
			pNode->name		= (char*)DgeMem_Allock(1, iLen, 0x0);
			strcpy(pNode->name, tNode);

			pNode->lDate	= fd.time_write;
			pNode->lBuf		= fd.size;

			(*pCur)->pNext = pNode;
			*pCur = pNode;
			t_DgeFile_Gather(pCur, pNode->name);
		}


		// File
		if( (fd.attrib & 0x20) && (fd.name[0] !='.'))
		{
			char	tNode[260]={0};
			int		iLen;
			sprintf(tNode, "%s/%s", sDir, fd.name);
			iLen	= strlen(tNode);
			iLen	= t_Multiple4(iLen);

			TDGE_FINF*	pNode = (TDGE_FINF*)DgeMem_Allock(sizeof(TDGE_FINF), 1, 0x0);
			pNode->nType	= 0x20;				// File: 0x20
			pNode->iname	= iLen;				// Length of File Name
			pNode->name		= (char*)DgeMem_Allock(1, iLen, 0x0);
			strcpy(pNode->name, tNode);

			pNode->lDate	= fd.time_write;
			pNode->lBuf		= fd.size;
			(*pCur)->pNext = pNode;
			*pCur = pNode;
		}

		result= DgeFile_FindNext(handle, &fd);
	}

	DgeFile_FindClose(handle);
}




void DgeFile_GatherAllFiles(TDGE_FINF** pOut, const char* sRoot)
{
	TDGE_FINF*	pRoot = (TDGE_FINF*)DgeMem_Allock(sizeof(TDGE_FINF), 1, 0x0);
	TDGE_FINF*	pCur = pRoot;
	int			iLen = strlen(sRoot);
	iLen			= t_Multiple4(iLen);

	pRoot->nType	= 0x10;
	pRoot->iname	= iLen;
	pRoot->name		= (char*)DgeMem_Allock(1, iLen, 0x0);
	strcpy(pRoot->name, sRoot);

	t_DgeFile_Gather(&pCur, pRoot->name);

	*pOut = pRoot;
}


void DgeFile_GatherFree(TDGE_FINF** pIn)
{
	TDGE_FINF*	pNode = *pIn;
	TDGE_FINF*	pNext = NULL;

	while(pNode)
	{
		pNext= pNode->pNext;

		if(pNode->name)
			free(pNode->name);

		free(pNode);
		pNode= pNext;
	}

	*pIn = NULL;
}


int DgeFile_mkdir(const char* sFolder, unsigned int mod)
{
#if defined(_WIN32) || defined(WIN32)
	return _mkdir(sFolder);
#else
	return mkdir(sFolder, mod);
#endif

}

int DgeFile_rmdir(const char* sFolder)
{
#if defined(_WIN32) || defined(WIN32)
	return _rmdir(sFolder);
#else
	return rmdir(sFolder);
#endif
}



