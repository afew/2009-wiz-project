// Start Program.
//
////////////////////////////////////////////////////////////////////////////////


#include "_StdAfx.h"


#if defined(_WIN32) || defined(WIN32)


int main(int argc, char* argv[])
{
	int		hr=0;
	CMain	mainApp;

	hr = mainApp.Create();
	if(DGE_FAILED(hr))
		goto End;

	hr = mainApp.Run();

	return hr;

End:
	DGE_Close();					// DGE ����
	return 0;
}


#else

PDGT_DRM		m_pDRM	= NULL;		// DRM

int InitDRM()
{
	INT		hr = DGE_EFAIL;
	BYTE*	version = NULL;
	char	sVer[] = "Build Date: 2010 08 18";
	INT		iLen = strlen(sVer);


	hr = DGT_CreateDRM(NULL, &m_pDRM);
	if(DGE_FAILED(hr))
		goto End;


	// DRM �ʱ�ȭ
	if(0 != m_pDRM->InitialNED())
	{
		printf("Init DRM Failed.\n");
		return -1;
	}


	// ���� ����( ��� ���� ���� )
	hr = m_pDRM->NED_FileOpen("version.bfc", "rb");

	if(NED_FILE_OK !=hr)
	{
		printf("NED_FileOpen Failed.\n");
		return -1;
	}


	version = (BYTE*)malloc(sizeof(BYTE) * 128);			// ���� ���� ���� ���� ���� --> ( 2010-05-24 )
	memset(version, 0, sizeof(BYTE) * 128);					// ���� ���� ���� ���� �ʱ�ȭ

	hr = m_pDRM->NED_FileRead((BYTE*)version,iLen);	// ���� �б�
	if(NED_FILE_OK != hr)
	{
		hr = DGE_EFAIL;
		goto End;
	}


	if(0 == strcmp((char*)version, sVer))		// ���� Ȯ��
	{
		printf("Drm Check OK.\n");
		hr = DGE_OK;							// DRM Ȯ�� ����
	}
	else
	{
		hr = DGE_EFAIL;							// ���� ����ġ, DRM Ȯ�� ����
		printf("Drm Fail: Version does not match.\n");
	}

End:
	if(version)									// ���� ���� ���� ���� ����
		free(version);

	m_pDRM->NED_FileClose();					// ���� �ݱ�

	return hr;
}


int main(int argc, char* argv[])
{
	int		hr=0;
	CMain	mainApp;

	if(DGE_FAILED(InitDRM()))
	{
		printf("Drm Init Failed.\n");
		goto End;
	}

	hr = mainApp.Create();
	if(DGE_FAILED(hr))
		goto End;

	hr = mainApp.Run();
	DGT_DestroyDRM(&m_pDRM);		// DRM ���� ó��

	return hr;

End:
	DGE_Close();					// DGE ����
	return 0;
}


#endif



