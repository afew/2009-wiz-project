//
// Gravity Sensor Example.
//
////////////////////////////////////////////////////////////////////////////////


#if defined(_WIN32)
	#pragma comment(linker, "/subsystem:console")
	#pragma comment(lib, "freetype2311MT_D.lib")

	#pragma comment(lib, "dge20_.lib")
	#pragma comment(lib, "dgx20_.lib")

	#pragma comment(lib, "zImgJpg_.lib")
	#pragma comment(lib, "png124_.lib")
	#pragma comment(lib, "zlib123_.lib")

	#pragma comment(lib, "libgles_cm.lib")

	#include <windows.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include <DGE_Type.h>
#include <DGE_System.h>
#include <DGE_Time.h>
#include <DGE_Math.h>
#include <DGE_Base.h>
#include <DGE_Input20.h>
#include <DGX_Input.h>
#include <DGX_Font.h>

// 진동 기능 사용
#include <DGE_Haptic.h>


#define MEDIA_DIR	"../../media/font/"

#define DGE_DISPLAY_DEFAULT_WIDTH	320


DGE_HANDLE		m_hWnd;					// Window 핸들
PDGE_DEVICE		m_pDev	= NULL;			// Device
PDGE_SPRITE		m_pSprite= NULL;		// 2D Sprite
PDGX_INPUT		m_pInput= NULL;		// Input

PDGX_FONT		m_pFont	= NULL;			// Font
DGE_COLORF		m_FontColor(1,1,0,1);	// Font Color
int				m_FontHeight = 10;		// 글꼴 높이


// 진동 기본 작동 시간( 단위 1 / 1000 초 )
const int basisActivateTime = 1000;

// 진동 동작 기록 저장 공간
vibration_act_t vibrationRecord[DGE_VIB_MAX_ACTION];

// 진동 동작 기록 시간( 단위 1 / 1000 초, 절대 시간 )
int recordTime = 0;

// 진동 동작 기록 위치
int recordPosition = 0;

// 진동 세기
enum VIBRATION_POWER
{
	VIBRATION_POWER_ZERO = 0,
	VIBRATION_POWER_WEAK = 40,
	VIBRATION_POWER_MIDDLE = 80,
	VIBRATION_POWER_STRONG = DGE_VIB_STRENGTH_MAX,
};

// 이전 진동 동작 정지
void VibrationStop()
{
	// 현재 진동 장치 상태 확인
	if(DGE_VIB_STATUS_BUSY == DGE_HapticStatus())
	{
		// 작동 중

		// 진동 정지
		DGE_HapticStop();
	}
}

// 진동 동작 기록 초기화
void InitializeVibrationRecord()
{
	// 진동 동작 기록 저장 공간 크기만큼 반복
	for(int count = 0; count != DGE_VIB_MAX_ACTION; ++count)
	{
		// 진동 동작 기록 초기화
		vibrationRecord[count].time_line = 0;
		vibrationRecord[count].vib_strength = VIBRATION_POWER_ZERO;
	}

	// 진동 동작 기록 시간 초기화
	recordTime = 0;

	// 진동 동작 기록 위치 초기화
	recordPosition = 0;
}

// 진동 동작 기록( 패턴 생성 )
void RecordVibrationPlay(int playTime, int strength)
{
	// 진동 동작 기록 위치 범위 확인
	// ( 최대 개수, 종료 처리 사용 - 1, 배열 인덱스 사용 - 1)
	if((0 > recordPosition) || ( DGE_VIB_MAX_ACTION - 2 < recordPosition))
	{
		// 허용 범위 이외( 기록 불가능 )
		return;
	}

	// 허용 범위 이내( 기록 가능 )

	// 진동 동작 기록
	vibrationRecord[recordPosition].time_line = (short)recordTime;
	vibrationRecord[recordPosition].vib_strength = (short)strength;

	// 다음 진동 동작 기록 시간 설정
	recordTime += playTime;

	// 다음 진동 동작 기록 위치 설정
	++recordPosition;	
}

// 진동 동작 기록 재생
void PlayVibrationRecord()
{
	// 진동 동작 기록 위치 범위 확인
	if(0 >= recordPosition)
	{
		// 허용 범위 이외( 재생 불가능, 내용 없음 )
		return;
	}

	// 이전 진동 동작 정지
	VibrationStop();

	// 진동 동작 기록 종료 처리
	vibrationRecord[recordPosition].time_line = (short)recordTime;
	vibrationRecord[recordPosition].vib_strength = (short)VIBRATION_POWER_ZERO;

	// 패턴 생성
	pattern_data_t vibrationPattern;

	// 패턴 설정

	// 진동 동작 기록 개수 설정( 배열 인덱스 사용 + 1 )
	vibrationPattern.act_number = recordPosition + 1;

	// 진동 동작 기록 저장 공간 크기만큼 반복
	for(int count = 0; count != DGE_VIB_MAX_ACTION; ++count)
	{
		// 진동 동작 기록 정보 복사
		vibrationPattern.vib_act_array[count].time_line = vibrationRecord[count].time_line;
		vibrationPattern.vib_act_array[count].vib_strength = vibrationRecord[count].vib_strength;
	}

	// 진동 동작 기록 재생
	DGE_HapticPlayPattern(&vibrationPattern);
}




// 정보 표시( 인터페이스, 진동 동작 기록 )
void DisplayInformation()
{
	// 이전 출력 내용 초기화
	char sbuf[128]={0};
	DGXVECTOR2 vcPos;

	// 글꼴 출력 위치
	int positionX = 20;
	int positionY = 20;

	// 버튼 사용 용도 출력

	// A 버튼 사용 용도 출력
	sprintf(sbuf, "A Button : Strength Zero");
	vcPos = DGXVECTOR2((float)positionX, (float)positionY);
	m_pFont->SetString(sbuf);
	m_pFont->SetPos(&vcPos);
	m_pFont->SetColor(&m_FontColor);
	m_pFont->DrawTxt();

	// 다음 문장 출력 위치 설정
	positionY += m_FontHeight;
	vcPos = DGXVECTOR2((float)positionX, (float)positionY);

	// Y 버튼 사용 용도 출력
	sprintf(sbuf, "Y Button : Strength Weak");
	vcPos = DGXVECTOR2((float)positionX, (float)positionY);
	m_pFont->SetString(sbuf);
	m_pFont->SetPos(&vcPos);
	m_pFont->SetColor(&m_FontColor);
	m_pFont->DrawTxt();


	// 다음 문장 출력 위치 설정
	positionY += m_FontHeight;
	vcPos = DGXVECTOR2((float)positionX, (float)positionY);

	// B 버튼 사용 용도 출력
	sprintf(sbuf, "B Button : Strength Middle");
	m_pFont->SetString(sbuf);
	m_pFont->SetPos(&vcPos);
	m_pFont->SetColor(&m_FontColor);
	m_pFont->DrawTxt();




	// 다음 문장 출력 위치 설정
	positionY += m_FontHeight;
	vcPos = DGXVECTOR2((float)positionX, (float)positionY);

	// X 버튼 사용 용도 출력
	sprintf(sbuf, "X Button : Strength Strong");
	m_pFont->SetString(sbuf);
	m_pFont->SetPos(&vcPos);
	m_pFont->SetColor(&m_FontColor);
	m_pFont->DrawTxt();


	// 다음 문장 출력 위치 설정
	positionY += m_FontHeight;
	vcPos = DGXVECTOR2((float)positionX, (float)positionY);

	// L 버튼 사용 용도 출력
	sprintf(sbuf, "L Button : Initialize Vibration Record");
	m_pFont->SetString(sbuf);
	m_pFont->SetPos(&vcPos);
	m_pFont->SetColor(&m_FontColor);
	m_pFont->DrawTxt();
	

	// 다음 문장 출력 위치 설정
	positionY += m_FontHeight;
	vcPos = DGXVECTOR2((float)positionX, (float)positionY);

	// R 버튼 사용 용도 출력
	sprintf(sbuf, "R Button : Play Vibration Record");
	m_pFont->SetString(sbuf);
	m_pFont->SetPos(&vcPos);
	m_pFont->SetColor(&m_FontColor);
	m_pFont->DrawTxt();


	// 다음 문장 출력 위치 설정
	positionY += m_FontHeight;
	vcPos = DGXVECTOR2((float)positionX, (float)positionY);

	// 기록 표시 간격
	int space = 45;

	// 진동 동작 기록 출력

	// 진동 동작 기록 개수만큼 반복
	for(int count = 0; count != recordPosition; ++count)
	{
		vcPos = DGXVECTOR2((float)positionX, (float)positionY);
		m_pFont->SetPos(&vcPos);
		m_pFont->SetColor(&m_FontColor);

		// 진동 동작 세기 확인
		switch(vibrationRecord[count].vib_strength)
		{
		case VIBRATION_POWER_ZERO:
			{
				sprintf(sbuf, "Zero");
				m_pFont->SetString(sbuf);
				m_pFont->DrawTxt();

				break;
			}
		case VIBRATION_POWER_WEAK:
			{
				sprintf(sbuf, "Weak");
				m_pFont->SetString(sbuf);
				m_pFont->DrawTxt();

				break;
			}
		case VIBRATION_POWER_MIDDLE:
			{
				sprintf(sbuf, "Middle");
				m_pFont->SetString(sbuf);
				m_pFont->DrawTxt();
				break;
			}
		case VIBRATION_POWER_STRONG:
			{
				sprintf(sbuf, "Strong");
				m_pFont->SetString(sbuf);
				m_pFont->DrawTxt();

				break;
			}
		default:
			{
				// 에러 발생
				break;
			}
		}

		// 다음 진동 동작 세기 표시 위치 설정
		positionX += space;

		// 줄 개행 필요 여부 확인
		if(DGE_DISPLAY_DEFAULT_WIDTH - space <= positionX)
		{
			// 줄 개행 필요

			// 다음 진동 동작 세기 표시 위치 설정
			positionY += m_FontHeight;
			positionX = 0;
		}
	}
}



FLOAT GetAppFrame();
LRESULT DGE_WINAPI WndProc(DGE_HWND, UINT, WPARAM, LPARAM);


INT DGE_CALLBACK Run(DGE_HANDLE)
{
#if defined(_WIN32)
	static MSG msg ={0};

	if(msg.message==WM_QUIT)
		return -1;

	if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
	{
		::TranslateMessage( &msg );
		::DispatchMessage( &msg );
	}
#else

	
#endif

	static INT c=0;
	++c;

//	if(c>20*60*20)
	if(c>20*60 *5)
	{
		printf("Game Process Terminated\n");
		return -1;
	}

	FLOAT fFrame = GetAppFrame();
	static INT n=0;
	++n;

	if(n>5)
	{
		printf("%f\n", fFrame);
		n = 0;
	}

	m_pInput->Update();					// Input Update


	if(m_pInput->KeyDown(DGEKEY_MENU))	// 종료 요청
		return -1;


		
	// 정보 변경 여부
	bool isChangeInformation = false;

	// 진동 동작 기록 여부
	bool isRecord = false;

	// 진동 세기
	int vibrationStrength = VIBRATION_POWER_ZERO;

	// 진동 요청 확인
	if(m_pInput->KeyDown(DGEKEY_FA))
	{
		// 진동 세기 없음
		vibrationStrength = VIBRATION_POWER_ZERO;

		// 진동 동작 기록
		isRecord = true;
	}
	if(m_pInput->KeyDown(DGEKEY_FY))
	{
		// 진동 세기 약
		vibrationStrength = VIBRATION_POWER_WEAK;

		// 진동 동작 기록
		isRecord = true;
	}
	if(m_pInput->KeyDown(DGEKEY_FB))
	{
		// 진동 세기 중간
		vibrationStrength = VIBRATION_POWER_MIDDLE;

		// 진동 동작 기록
		isRecord = true;
	}
	if(m_pInput->KeyDown(DGEKEY_FX))
	{
		// 진동 세기 강
		vibrationStrength = VIBRATION_POWER_STRONG;

		// 진동 동작 기록
		isRecord = true;
	}

	// 진동 동작 기록 재생 요청 여부 확인
	if(m_pInput->KeyDown(DGEKEY_FR))
	{
		// 진동 동작 기록 재생
		PlayVibrationRecord();
	}

	// 진동 동작 기록 초기화 요청 여부 확인
	if(m_pInput->KeyDown(DGEKEY_FL))
	{
		// 진동 동작 기록 초기화
		InitializeVibrationRecord();

		// 정보 변경
		isChangeInformation = true;
	}

	// 진동 동작 기록 여부 확인
	if(isRecord)
	{
		// 이전 진동 동작 정지
		VibrationStop();

		// 진동 동작 재생
		DGE_HapticPlay(basisActivateTime, vibrationStrength);

		// 진동 동작 기록
		RecordVibrationPlay(basisActivateTime, vibrationStrength);

		// 정보 변경
		isChangeInformation = true;
	}



	m_pDev->BeginScene();	// Prepare Rendering...

	m_pDev->Clear(DGE_CLEAR_COLOR_BUFFER | DGE_CLEAR_DEPTH_BUFFER);	// Clear Backbuffer

	m_pSprite->Begin();		// Sprite Begin




	// 정보 변경 여부 확인
	if(isChangeInformation)
	{
		// 정보 변경		
	}


	DisplayInformation();

	m_pSprite->End();		// Sprite End

	m_pDev->EndScene();		// Post Rendering...

	return 0;
}




// Main Program
INT main(INT argc, char* argv[])
{
	char		sFont[] = MEDIA_DIR"hyuin.ttf";
	TDGX_FONT	tFont(sFont, m_FontHeight);
	
	
	// DGE 초기화
	if(DGE_FAILED(DGE_Init()))
		return 0;

	// Main Procedure 함수 설정
	if(DGE_FAILED(DGE_SetMainRunFunc(Run)))
		goto End;

	
	// Window 생성
	m_hWnd = DGE_CreateWindow(WndProc, "DGE_Tutorial");
	if(NULL == m_hWnd)
		goto End;

	// Device 생성
	if(DGE_FAILED(DGE_CreateDevice(NULL, &m_pDev, m_hWnd, NULL)))
		goto End;


	// Sprite 생성
	if(DGE_FAILED(DGE_CreateSprite(NULL, &m_pSprite, m_pDev)))
		goto End;


	// Input 생성
	if(DGE_FAILED(DGX_CreateInput(NULL, &m_pInput, m_pDev, m_hWnd)))
		goto End;

	
	// Font 라이브러리 생성
	if(DGE_FAILED(DGX_TFFontOpen()))
		goto End;

	printf("DGX_TFFontOpen Success\n");

	// Font 생성
	if(DGE_FAILED(DGX_CreateFont(NULL, &m_pFont, &tFont, m_pSprite)))
		goto End;

	printf("DGX_CreateFont Success\n");



	// 진동 장치 초기화
	if(DGE_FAILED(DGE_HapticOpen()))
		goto End;

	printf("DGE_HapticOpen Success\n");

	// 진동 장치 활성화
	if(DGE_FAILED(DGE_HapticEnable(1)))
		goto End;

	printf("DGE_HapticEnable Success\n");

	// 진동 동작 기록 초기화
	InitializeVibrationRecord();

	// 프로그램 실행
	while(1)
	{
		if(DGE_FAILED(DGE_Run()))
			break;

		// Flipping
		m_pDev->Present(0,0,0,0);
	}

End:

	DGE_HapticClose();				// 진동 장치 종료

	DGX_DestroyFont(&m_pFont);		// Font 객체 해제
	DGX_TFFontClose();				// Font 라이브러리 해제

	DGX_DestroyInput(&m_pInput);	// Input 해제
	DGE_DestroySprite(&m_pSprite);	// Sprite 해제
	DGE_DestroyDevice(&m_pDev);		// Device 해제
	DGE_DestroyWindow(m_hWnd);		// Window 해제
	DGE_Close();					// DGE 해제

	return 0;

}


// Window Message Procedure
LRESULT DGE_WINAPI WndProc(DGE_HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
#if defined(_WIN32)
	switch (uMsg)
	{
		case WM_KEYDOWN:
		{
			if(VK_ESCAPE == wParam)
			{
				SendMessage(hWnd, WM_CLOSE, 0, 0);
				return 0;
			}
			break;
		}

		case WM_CLOSE:
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
#else

	return DGE_OK;

#endif
}



FLOAT GetAppFrame()
{
#if defined(_WIN32)
	static INT		MaxCount = 10;
#else
	static INT		MaxCount = 10;
#endif

	static DOUBLE  fFps = 0.;
	static INT     iCnt = 0;
	static DWORD   dBgn = ::DGE_GetTickCount();
	DWORD   dCur = ::DGE_GetTickCount();  // GetTickCount()

	++iCnt;

	if(iCnt>=MaxCount)
	{
		fFps = DOUBLE(dCur-dBgn);
		fFps = iCnt*1000./fFps;
		iCnt = 0;
		dBgn = dCur;
	}

	return (FLOAT)fFps;
}

