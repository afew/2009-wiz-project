// Merge Example
//
////////////////////////////////////////////////////////////////////////////////


#if defined(_WIN32) || defined(WIN32)
	#pragma comment(lib, "dge20_.lib")
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#include "DGE_Util.h"


#define MEDIA_DIR	"../../media/"



// for Window Application
void MakeMergeFile()
{
	TDGE_FINF*	pRoot = NULL;
	TDGE_FINF*	pNode = NULL;

	long	CntFoler = 0;
	long	CntFile = 0;
	long	OffsetFolerLst=0;
	long	OffsetFiles	=0;
	long	OffsetFileLst =0;

	FILE*	f = NULL;

	DgeFile_GatherAllFiles(&pRoot, MEDIA_DIR"test_folder");


	fprintf(stdout, "\nFolder List-------------------------\n");
	pNode = pRoot;
	while(pNode)
	{
		if(DGE_TYPE_FOLDER == pNode->nType)
		{
//			fprintf(stdout, " %.24s %9ld	%-64s\n", ctime(&pNode->lDate), pNode->lBuf, pNode->name);
			CntFoler++;
		}

		pNode= pNode->pNext;
	}

	fprintf(stdout, "\nFile List-------------------------\n");
	pNode = pRoot;
	while(pNode)
	{
		if(DGE_TYPE_FILE == pNode->nType)
		{
//			fprintf(stdout, " %.24s %9ld	%-64s\n", ctime(&pNode->lDate), pNode->lBuf, pNode->name);
			CntFile++;
		}

		pNode= pNode->pNext;
	}



	fprintf(stdout, "\nWrite Folder List-------------------------\n");



	f = fopen("zmerge.bin", "wb");			// Merge ���� ����

	fseek(f, 64, SEEK_SET);					// ���(64 BYTE) ��ŭ �̵�

	// ���� ����Ʈ ����
	OffsetFolerLst = ftell(f);				// Setup Start Folder List Position in Merge File

	pNode = pRoot;
	while(pNode)
	{
		if(DGE_TYPE_FOLDER == pNode->nType)
		{
			char* name = pNode->name;
			long iLen = pNode->iname;
			fwrite(&iLen, sizeof(long), 1, f);
			fwrite(name , sizeof(char), iLen, f);
		}
		pNode= pNode->pNext;
	}


	fprintf(stdout, "\nWrite Files-------------------------\n");


	// Write File Data
	OffsetFiles = ftell(f);						// Setup Files Position in Merge File

	pNode = pRoot;
	FILE*	fr = NULL;
	char	sBuf[1024]={0};
	size_t	iRead;

	while(pNode)
	{
		if(DGE_TYPE_FILE == pNode->nType)
		{
			fr = fopen(pNode->name, "rb");

			if(fr)
			{
				long lOff = ftell(f);			// File Pointer�� ��ġ�� �о 
				pNode->lBufB = lOff;

				while(1)						// ���� ���
				{
					iRead = fread(sBuf,1,1024,fr);

					if(0>=iRead)
						break;

					fwrite(sBuf, 1, iRead, f);
				}

				fclose(fr);
			}
		}
		
		pNode= pNode->pNext;
	}


	fprintf(stdout, "\nWrite File List-------------------------\n");


	// Write File List
	OffsetFileLst = ftell(f);					// Setup File List Position in Merge File

	pNode = pRoot;
	while(pNode)
	{
		if(DGE_TYPE_FILE == pNode->nType)
		{
			long	lDate	= pNode->lDate	;	// Make Date
			long	lBuf	= pNode->lBuf	;	// Length of File Buffer
			long	lBufB	= pNode->lBufB	;	// Start Buffer in Merge File
			long	iname	= pNode->iname	;	// Length of File Name
			char*	name	= pNode->name	;	// File Name

			fwrite(&lDate, sizeof(long), 1, f);
			fwrite(&lBuf , sizeof(long), 1, f);
			fwrite(&lBufB, sizeof(long), 1, f);
			fwrite(&iname, sizeof(long), 1, f);
			fwrite(name  , sizeof(char), iname, f);
		}
		pNode= pNode->pNext;
	}


	// Release Node
	DgeFile_GatherFree(&pRoot);



	fseek(f, 0, SEEK_SET);							// Move the File Pointer to Start Position.
	// Write Header
	fwrite(&CntFoler		, sizeof(long), 1,f);	// Write Folder List Number
	fwrite(&CntFile			, sizeof(long), 1,f);	// Write File List Number
	fwrite(&OffsetFolerLst	, sizeof(long), 1,f);	// Write Folder List Offset
	fwrite(&OffsetFiles		, sizeof(long), 1,f);	// Write Files Offset
	fwrite(&OffsetFileLst	, sizeof(long), 1,f);	// Write File List Offset

	fclose(f);
}


// for N35 Application
void ConfirmMergeFile()
{
	long i=0;
	
	////////////////////////////////////////////////////////////////////////////
	// Confirm

	long	nFoler	= 0;
	long	nFile	= 0;
	long	oFoler	= 0;
	long	oFiles	= 0;
	long	oFileL	= 0;

	long	lSeekCur	= 0;
	FILE*	fr  = NULL;
	FILE*	fw = NULL;

	char drv [DGE_MAX_DRIVE] = {0};
	char dir [DGE_MAX_FNAME] = {0};
	char file[DGE_MAX_FNAME] = {0};
	char ext [DGE_MAX_FNAME] = {0};


	fprintf(stdout, "\n\n Confirm-------------------------\n");

	fr = fopen("zmerge.bin", "rb");					// Open Merge File

	fread(&nFoler	, sizeof(long), 1,fr);			// Read Folder List Number
	fread(&nFile	, sizeof(long), 1,fr);			// Read File List Number
	fread(&oFoler	, sizeof(long), 1,fr);			// Read Folder List Offset
	fread(&oFiles	, sizeof(long), 1,fr);			// Read Files Offset
	fread(&oFileL	, sizeof(long), 1,fr);			// Read File List Offset


	fprintf(stdout, "\n File List-------------------------\n");

	fseek(fr, oFileL, SEEK_SET);					// Move the File Pointer to File List Start

	for(i=0; i<nFile; ++i)
	{
		long	lDate	= 0;
		long	lBuf	= 0;
		long	lBufB	= 0;
		long	iname	= 0;
		char name[260]	= {0};

		fread(&lDate, sizeof(long), 1, fr);
		fread(&lBuf , sizeof(long), 1, fr);
		fread(&lBufB, sizeof(long), 1, fr);
		fread(&iname, sizeof(long), 1, fr);
		fread(name  , sizeof(char), iname, fr);

		printf("File:%6ld  %s\n", lBuf, name);


		lSeekCur = ftell(fr);					// Save Current File Pointer


		DgeStr_SplitPath(name, drv, dir, file, ext);
		sprintf(name, "temp/%s%s", file, ext);

		void* buf = DgeMem_Allock(lBuf,1,0x0);

		DgeFile_mkdir("temp");
		
		fw = fopen(name, "wb");

		fseek(fr, lBufB, SEEK_SET);				// Move the File Pointer to Written Position

		////////////////////////////////////////////////////////////////////////
		// Read Written Data from Merge File
		fread(buf, 1, lBuf, fr);

		// Save Data...
		fwrite(buf, 1, lBuf, fw);
		//
		////////////////////////////////////////////////////////////////////////

		fclose(fw);
		DgeMem_Free(&buf);						// Release Temp Buffer

		fseek(fr, lSeekCur, SEEK_SET);			// Move the File Pointer to Current positon
	}


	fclose(fr );
}


int main(int argc, char* argv[])
{
	MakeMergeFile();

	ConfirmMergeFile();

	return 0;
}


