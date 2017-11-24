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
	DGE_Close();					// DGE 해제
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


	// DRM 초기화
	if(0 != m_pDRM->InitialNED())
	{
		printf("Init DRM Failed.\n");
		return -1;
	}


	// 파일 열기( 대상 파일 고정 )
	hr = m_pDRM->NED_FileOpen("version.bfc", "rb");

	if(NED_FILE_OK !=hr)
	{
		printf("NED_FileOpen Failed.\n");
		return -1;
	}


	version = (BYTE*)malloc(sizeof(BYTE) * 128);			// 버전 정보 저장 공간 생성 --> ( 2010-05-24 )
	memset(version, 0, sizeof(BYTE) * 128);					// 버전 정보 저장 공간 초기화

	hr = m_pDRM->NED_FileRead((BYTE*)version,iLen);	// 버전 읽기
	if(NED_FILE_OK != hr)
	{
		hr = DGE_EFAIL;
		goto End;
	}


	if(0 == strcmp((char*)version, sVer))		// 버전 확인
	{
		printf("Drm Check OK.\n");
		hr = DGE_OK;							// DRM 확인 성공
	}
	else
	{
		hr = DGE_EFAIL;							// 버전 불일치, DRM 확인 실패
		printf("Drm Fail: Version does not match.\n");
	}

End:
	if(version)									// 버전 정보 저장 공간 해제
		free(version);

	m_pDRM->NED_FileClose();					// 파일 닫기

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
	DGT_DestroyDRM(&m_pDRM);		// DRM 종료 처리

	return hr;

End:
	DGE_Close();					// DGE 해제
	return 0;
}


#endif



