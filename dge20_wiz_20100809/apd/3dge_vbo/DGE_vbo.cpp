// Implementation of the DGX Vertex Buffer Object.
//
////////////////////////////////////////////////////////////////////////////////


#if defined(_WIN32) || defined(WIN32)
	#if _MSC_VER >= 1200
	#pragma warning(disable: 4996)
	#endif

	#include <windows.h>

#endif


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <gles/gl.h>

#include <DGE_Type.h>
#include <DGE_Base.h>


#include "DGE_vbo.h"


class CDGE_VB : public IDGE_VB
{
protected:
	PDGE_DEVICE		m_pDev;
	UINT			m_nID;

	DWORD			m_dFVF;

	void*			m_pOwner;				// Owner
	
public:
	CDGE_VB();
	virtual ~CDGE_VB();

	virtual INT		Fill(DGE_HANDLE pBuf, INT nBufSize, BOOL bReCreateVB=FALSE);
	virtual INT		Bind(BOOL bBind=FALSE);

	virtual	void	SetOwner(DGE_HANDLE p){	m_pOwner = p;	}
	virtual	void*	GetOwner()		{	return m_pOwner;}



public:
	INT		Create(DGE_HANDLE =NULL, DGE_HANDLE =NULL, DGE_HANDLE =NULL, DGE_HANDLE =NULL);
	void	Destroy();
};



CDGE_VB::CDGE_VB()
{
	m_pDev		= NULL;
	m_nID		= 0;
	m_dFVF		= 0;

	m_pOwner	= NULL;
}


CDGE_VB::~CDGE_VB()
{
	Destroy();
}

void CDGE_VB::Destroy()
{
	if(0 == m_nID)
		return;

	glDeleteBuffers(1, &m_nID);
	m_nID = 0;
}


INT CDGE_VB::Create(void* p1, void* p2, void* p3, void* p4)
{
	char*	pBuf = NULL;
	INT		nBuf = 0;

	if(NULL ==p1)
		return DGE_ECANNOTALLOCATED;


	m_pDev = (PDGE_DEVICE)p1;

	pBuf = (char*)p2;

	if(p3)
		nBuf = *(INT*)p3;

	
	glGenBuffers(1, &m_nID);

	if(0 == m_nID)
		return DGE_ECANNOTALLOCATED;


	return Fill(pBuf, nBuf);
}




INT CDGE_VB::FillBuffer(void* pBuf, int nBufSize, BOOL bReCreateVB)
{
	UINT	nID = m_nID;

	if(FALSE == bReCreateVB)
	{
		if(0 == nID)
			return DGE_ECANNOTALLOCATED;
	}
	else
	{
		glGenBuffers(1, &nID);
	}


	glBindBuffer(GL_ARRAY_BUFFER, nID);								// VBO 연결 시작


	if(pBuf)
	{
		glBufferData(GL_ARRAY_BUFFER, nBufSize, pBuf, GL_STATIC_DRAW);		// 시스템 메모리에 저장된 정점 데이터를 VBO에 연결

	//	int nSize = 0;
	//	glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &nSize);

	}


	if(bReCreateVB)
	{
		if(m_nID)
			glDeleteBuffers(1, &m_nID);

		m_nID = nID;
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0);								// VBO 연결 해제

	return DGE_OK;
}



INT CDGE_VB::BindBuffer(BOOL bBind)
{
	if(bBind)
		glBindBuffer(GL_ARRAY_BUFFER, m_nID);
	else
		glBindBuffer(GL_ARRAY_BUFFER, 0);

	return DGE_OK;
}




INT DGE_CreateVB(char* sCmd
			   , PDGE_VB* pData
			   , DGE_HANDLE p1		// PDGE_DEVICE
			   , DGE_HANDLE p2		// FVF
			   , DGE_HANDLE p3		// Input Buffer
			   , DGE_HANDLE p4		// Input Buffer Size(Byte)
				)
{
	INT			hr = 0;
	CDGE_VB*	pObj = NULL;

	*pData	= NULL;
	pObj	= new CDGE_VB;

	hr = pObj->Create(p1, p2, p3, p4);

	if(DGE_FAILED(hr))
	{
		delete pObj;
		return hr;
	}

	*pData = pObj;
	return DGE_OK;
}


INT DGE_DestroyVB(PDGE_VB* pData)
{
	if(NULL == *pData)
		return DGE_OK;


	if(NULL != (*pData)->GetOwner())	// 소유주가 활성화 되어 있으면 해제를 못하게 함.
		return DGE_EFAIL;

	delete *pData;
	(*pData) = NULL;
	return DGE_OK;
}



