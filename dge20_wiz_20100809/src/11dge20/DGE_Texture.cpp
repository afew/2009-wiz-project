// Implementation of the IDGE_Texture.
//
////////////////////////////////////////////////////////////////////////////////


#if defined(_WIN32) || defined(WIN32)
	#if _MSC_VER >= 1200
	#pragma warning(disable: 4996)
	#endif

	#include <windows.h>
	#include "ImgGpt.h"

#endif


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <gles/gl.h>

#include <DGE_Type.h>

#include "DGE_Base.h"
#include "DGE_Texture.h"


DGE_INLINE int Make2Power(int v)
{
	int t=v, n=0;
	for(; t >>= 1 ;++n){};
	if( v ^ 1<<n)
		n++;

	return 1<<n;
}


CDGE_Texture::CDGE_Texture()
{
	m_nTex	= 0;
	m_Format= 0x0;
	m_Type	= 0x0;
	m_ImgW	= 0;
	m_ImgH	= 0;
	m_ImgD	= 0;
	m_ImgC	= 0x0;

	m_pOwn	= NULL;
	
	memset(m_sName, 0, sizeof m_sName);
}

CDGE_Texture::~CDGE_Texture()
{
	Destroy();
}


void CDGE_Texture::Destroy()
{
	if(0 == m_nTex)
		return;

	glDeleteTextures (1, &m_nTex);
	m_nTex = 0;
}


INT CDGE_Texture::Create(  DGE_HANDLE p1	// File Name
						 , DGE_HANDLE p2	// Buffer Address
						 , DGE_HANDLE p3	// Color Key or Image Width
						 , DGE_HANDLE p4	// NULL or Image Height
						 )
{
#define CREATE_FROM_FILE		1
#define CREATE_FROM_BUFFER		2
#define CREATE_RENDER_COPY		3


	INT			hr		= 0;
	BYTE*		pPxlDst = NULL;
	PDGE_IMAGE	pImg	= NULL;

	INT			nImgR	= 0;		// Image Resource Type
	UINT		nImgC	= 0;		// Pixel Color Key
	INT			nLoad	= 0;		// 1: File, 2: Buffer


	// Load 방법 설정
	// 파일 이름이 있으면
	if(p1)
		nLoad = CREATE_FROM_FILE;

	// 파일 이름이 없고 버퍼 p2가 있으면
	else if(NULL == p1 && p2)
		nLoad = CREATE_FROM_BUFFER;

	// 파일 이름이 없고 버퍼도 없고 p3와 p4가 있으면
	// Rendering copy용 텍스처. 여기서 p3는 Color Key 대신 이미지 Width가 됨.
	else if(NULL == p1 && NULL == p2 && p3 && p4)
		nLoad = CREATE_RENDER_COPY;

	else
		return DGE_ECANNOTALLOCATED;



	// Color Key 설정
	if(p3)
		nImgC = *((UINT*)p3);




	// Load From File
	if(CREATE_FROM_FILE == nLoad)
	{
		hr = DGE_CreateImage(NULL, &pImg, p1, NULL, p3);
		if( DGE_FAILED(hr))
		{
			printf("Err: %d, %s \t", __LINE__, __FILE__);
			printf("Load Texture Failed\n");
			return DGE_ECANNOTFIND_RESOURCE;
		}

		nImgR	= pImg->GetRscType();
		m_Format= pImg->GetFormat();
		m_Type	= pImg->GetType();
		m_ImgW	= pImg->GetImgW();
		m_ImgH	= pImg->GetImgH();
		m_ImgD	= pImg->GetImgD();
		m_ImgC	= pImg->GetImgC();
		pPxlDst = pImg->GetPixel();
	}


	// Load From Buffer: 버퍼에서 지정한 것은 그대로 사용
	else if(CREATE_FROM_BUFFER == nLoad)
	{
		TDGE_IMAGE* pSrc =(TDGE_IMAGE*)p2;

		m_Format= pSrc->Format;
		m_Type	= pSrc->Type;

		m_ImgW	= pSrc->ImgW;
		m_ImgH	= pSrc->ImgH;
		m_ImgD	= pSrc->ImgD;
		m_ImgC	= pSrc->ImgC;

		pPxlDst	= pSrc->pPxl;
	}


	// Rendering Texture
	else if(CREATE_RENDER_COPY == nLoad)
	{
		m_Format= GL_RGB;
		m_Type	= GL_UNSIGNED_BYTE;

		m_ImgW	= *((INT*)p3);
		m_ImgH	= *((INT*)p4);
		m_ImgD	= 3;
		m_ImgC	= 0x0;

		pPxlDst	= NULL;
	}


	if(m_ImgW * m_ImgH >( DGE_IMG_MAX_WIDTH * DGE_IMG_MAX_HEIGHT) )
	{
		char* sFile = (char*)p1;
		printf("Warnning !!! %s File size is out of bounds.\n Only can be operating in PC.\n", sFile);
	}


	glGenTextures(1, &m_nTex);
	if(0 == m_nTex)
	{
		if(pImg)
			DGE_DestroyImage(&pImg);

		return DGE_ECANNOTALLOCATED;
	}

	glBindTexture(GL_TEXTURE_2D, m_nTex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, m_Format, m_ImgW, m_ImgH, 0, m_Format, m_Type, pPxlDst);

	glBindTexture(GL_TEXTURE_2D, 0);


	if(pImg)
		DGE_DestroyImage(&pImg);


	return DGE_OK;
}


INT CDGE_Texture::BindTexture(INT modulate, INT smp_addrS, INT smp_addrT, INT filter_S, INT filter_T)
{
	if(0 == modulate)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
		glDisable(GL_TEXTURE_2D);
		return DGE_OK;
	}

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_nTex);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, (GLfloat)modulate);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, smp_addrS);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, smp_addrT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter_S);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter_T);

	return DGE_OK;
}


INT CDGE_Texture::CopyTexImage2D()
{
	if(1>m_nTex)
		return DGE_EFAIL;

	glBindTexture(GL_TEXTURE_2D, this->GetId());
	glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 0, 0, m_ImgW, m_ImgH, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	return DGE_OK;
}





INT DGE_CreateTexture(char* sCmd				// Null is File, "Resouce" is Memory buffer. "Buffer"
					   , PDGE_TEXTURE* pData
					   , DGE_HANDLE p1			// "File Name"
					   , DGE_HANDLE p2			// Buffer Address Need(if p1 == NULL)
					   , DGE_HANDLE p3			// No Use
					   , DGE_HANDLE p4			// No Use
					 )
{
	INT	hr = 0;
	CDGE_Texture*	pObj = NULL;

	*pData	= NULL;
	
	pObj = new CDGE_Texture;

	hr = pObj->Create(p1, p2, p3, p4);

	if(DGE_FAILED(hr))
	{
		delete pObj;
		return hr;
	}


	*pData = pObj;
	return DGE_OK;
}





INT DGE_DestroyTexture(PDGE_TEXTURE* pData)
{
	if(NULL == *pData)
		return DGE_OK;


	if(NULL != (*pData)->GetOwner())	// 소유주가 활성화 되어 있으면 해제를 못하게 함.
		return DGE_EFAIL;

	delete *pData;
	(*pData) = NULL;
	return DGE_OK;
}



