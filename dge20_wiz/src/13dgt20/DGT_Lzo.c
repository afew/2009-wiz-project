

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "./lzo/include/lzo/lzoconf.h"
#include "./lzo/include/lzo/lzo1x.h"


#include "DGT_Lzo.h"



int DgtLzo_Init()
{
	if (lzo_init() != LZO_E_OK)
		return -1;

	return 0;
}


int DgtLzo_Close()
{
	return 0;
}



int DgtLzo_CompressBuf(unsigned char** pOutBuf,unsigned long* pOutSize, unsigned char* pSrc, unsigned long iLenSrc)
{
	int hr;

	unsigned char* pDst;
	unsigned char* pOut;
	unsigned char* pTmp;
	unsigned long iLenDst;

//	unsigned long i=0;
//
//	char	sPwd[]="All that is necessary for the triumph of evil that good men to do nothing";
//	size_t	iLen =strlen(sPwd);


	iLenDst = iLenSrc + iLenSrc / 16 + 64 + 3;		// �ӽ� �۾������� ũ�⸦ ���Ѵ�.

	pDst = (unsigned char*) malloc(iLenDst);
	pTmp = (unsigned char*) malloc(LZO1X_1_MEM_COMPRESS);

	if (pSrc == NULL || pDst == NULL || pTmp == NULL)
		return -1;

	hr = lzo1x_1_compress(pSrc,iLenSrc, pDst, &iLenDst,pTmp);
	if (hr != LZO_E_OK)
		return -1;



//	// ������ ��ȣȭ
//	for(i=0; i<iLenDst; ++i)
//		pDst[i] = pDst[i] ^ sPwd[i%iLen];



	// ���� ���
	pOut	= (unsigned char*)malloc(iLenDst+8);
	memset(pOut, 0, iLenDst+8);
	memcpy(pOut, &iLenSrc, sizeof(iLenSrc));		// ���ҽ� ���
	memcpy(pOut+8, pDst, iLenDst);					// ���� ������ ���

	*pOutBuf	= pOut;
	*pOutSize	= iLenDst+8;						// 8����Ʈ�� ���ؼ� ���(���� 4����Ʈ�� ����)


	free(pDst);
	free(pTmp);

	return 0;
}



int DgtLzo_DeCompressBuf(unsigned char** pOutBuf, unsigned long* pOutSize, unsigned char* pSrc, unsigned long iLenSrc)
{
	int hr;

	unsigned char*	pDst	= NULL;
	unsigned char*	pSrcT	= NULL;
	unsigned long	iLenOut	= 0;

//	unsigned long	i=0;
//
//	char			sPwd[]="All that is necessary for the triumph of evil that good men to do nothing";
//	size_t			iLen =strlen(sPwd);


//	pSrcT = (unsigned char*)malloc( iLenSrc);

	memcpy(&iLenOut, pSrc, sizeof(iLenOut));		// ���ҽ� ���
	pSrc+=8;
	iLenSrc -= 8;


//	// ��ȣȭ ����
//	for(i=0; i<iLenSrc; ++i)
//	{
//		pSrcT[i] = pSrc[i] ^ sPwd[i%iLen];
//		pSrcT[i] = pSrc[i];
//	}

	pSrcT = pSrc;


	pDst = (unsigned char*)malloc(iLenOut);

	hr = lzo1x_decompress(pSrcT, iLenSrc, pDst, &iLenOut, NULL);
	if (hr != LZO_E_OK)
		return -1;

	*pOutBuf = pDst;
	*pOutSize= iLenOut;


//	free(pSrcT);

	return 0;
}



int DgtLzo_CompressFile(char* sDstFile, char* sSrcFile)
{
	int hr;
	unsigned char*	pSrc;
	unsigned long	iLenSrc;

	unsigned char*	pDst;
	unsigned long	iLenDst;

	char			sType[32]="GaLic";
	unsigned long	iLenFile = strlen(sSrcFile);


	// 1.1 ��� ������ �д´�.
	FILE*	fp = NULL;

	fp = fopen(sSrcFile, "rb");
	if(NULL == fp)
		return -1;


	// ������ ũ�⸦ ����Ѵ�.
	fseek(fp, 0, SEEK_END);
	iLenSrc = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	// ������ �۾� ���ۿ� ����Ѵ�.
	pSrc = (unsigned char*)malloc(iLenSrc);
	fread(pSrc, 1, iLenSrc, fp);
	fclose(fp);


	hr = DgtLzo_CompressBuf(&pDst, &iLenDst, pSrc, iLenSrc);
	if(0>hr)
		return -1;


	// ������ ����Ѵ�.
	fp = fopen(sDstFile, "wb");

	fwrite(sType	, 1, 32						, fp);	// �ǹ̾��� ���
	fwrite(&iLenFile, 1, sizeof(unsigned long)	, fp);	// �� ���� �̸��� ���̸� ����Ѵ�.
	fwrite(sSrcFile	, 1, iLenFile				, fp);	// �� ���� �̸��� ����Ѵ�.
	fwrite(pDst		, 1, iLenDst				, fp);	// ����� �����͸� ����Ѵ�.

	fclose(fp);

	// �ӽ� ���۵��� �����.
	free(pSrc);
	free(pDst);

	pSrc	= NULL;
	pDst	= NULL;

	return 0;
}


int DgtLzo_DeCompressFile(char* sPath, char* sZipSrcFile)
{
	int hr;
	unsigned char* pFile=NULL;
	unsigned char* pSrc=NULL;
	unsigned long iLenSrc=0;

	unsigned char* pDst=NULL;
	unsigned long iLenDst=0;


	char			sType[32]= {0};
	unsigned long	iLenFile = 0;
	char			sSrcFile[260]={0};

	char		sFull[260];

	// 1. ����� ������ �д´�.
	FILE*	fp = NULL;

	fp = fopen(sZipSrcFile, "rb");

	if(NULL == fp)
		return -1;


	// ������ ũ�⸦ ����Ѵ�.
	fseek(fp, 0, SEEK_END);
	iLenSrc = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	pFile = (unsigned char*)malloc( iLenSrc );
	pSrc  = pFile;
	fread(pFile, 1, iLenSrc, fp);					// ����� ������ �б�
	fclose(fp);


	memcpy(sType		, pSrc, 32						);	pSrc += 32;
	memcpy(&iLenFile	, pSrc, sizeof(unsigned long)	);	pSrc += sizeof(unsigned long);
	memcpy(sSrcFile		, pSrc, iLenFile				);	pSrc += iLenFile;
//	memcpy(pDst			, pSrc, iLenDst					);	pSrc += iLenDst;

	iLenSrc = iLenSrc - (pSrc - pFile);


	hr = DgtLzo_DeCompressBuf(&pDst, &iLenDst, pSrc, iLenSrc);
	if(0>hr)
		return -1;

	// ���� ����
	sprintf(sFull, "%s%s", sPath, sSrcFile);
	fp = fopen(sFull, "wb");
	fwrite(pDst, 1, iLenDst, fp);
	fclose(fp);

	free(pDst);
	free(pFile);

	return 0;
}




int DgtLzo_DeCompressFromFile(unsigned char** bufOut, unsigned long* lsize, char* sZipSrcFile)
{
	int hr;
	unsigned char* pFile=NULL;
	unsigned char* pSrc=NULL;
	unsigned long iLenSrc=0;

	unsigned char* pDst=NULL;
	unsigned long iLenDst=0;


	char			sType[32]= {0};
	unsigned long	iLenFile = 0;
	char			sSrcFile[260]={0};

	// 1. ����� ������ �д´�.
	FILE*	fp = NULL;

	fp = fopen(sZipSrcFile, "rb");

	if(NULL == fp)
		return -1;


	// ������ ũ�⸦ ����Ѵ�.
	fseek(fp, 0, SEEK_END);
	iLenSrc = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	pFile = (unsigned char*)malloc( iLenSrc );
	pSrc  = pFile;
	fread(pFile, 1, iLenSrc, fp);					// ����� ������ �б�
	fclose(fp);


	memcpy(sType		, pSrc, 32						);	pSrc += 32;
	memcpy(&iLenFile	, pSrc, sizeof(unsigned long)	);	pSrc += sizeof(unsigned long);
	memcpy(sSrcFile		, pSrc, iLenFile				);	pSrc += iLenFile;

	iLenSrc = iLenSrc - (pSrc - pFile);


	hr = DgtLzo_DeCompressBuf(&pDst, &iLenDst, pSrc, iLenSrc);
	if(0>hr)
		return -1;

	free(pFile);

	*bufOut = pDst;
	*lsize = iLenDst;

	return 0;
}

