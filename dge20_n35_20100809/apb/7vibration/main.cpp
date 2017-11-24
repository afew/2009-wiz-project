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

// ���� ��� ���
#include <DGE_Haptic.h>


#define MEDIA_DIR	"../../media/font/"

#define DGE_DISPLAY_DEFAULT_WIDTH	320


DGE_HANDLE		m_hWnd;					// Window �ڵ�
PDGE_DEVICE		m_pDev	= NULL;			// Device
PDGE_SPRITE		m_pSprite= NULL;		// 2D Sprite
PDGX_INPUT		m_pInput= NULL;		// Input

PDGX_FONT		m_pFont	= NULL;			// Font
DGE_COLORF		m_FontColor(1,1,0,1);	// Font Color
int				m_FontHeight = 10;		// �۲� ����


// ���� �⺻ �۵� �ð�( ���� 1 / 1000 �� )
const int basisActivateTime = 1000;

// ���� ���� ��� ���� ����
vibration_act_t vibrationRecord[DGE_VIB_MAX_ACTION];

// ���� ���� ��� �ð�( ���� 1 / 1000 ��, ���� �ð� )
int recordTime = 0;

// ���� ���� ��� ��ġ
int recordPosition = 0;

// ���� ����
enum VIBRATION_POWER
{
	VIBRATION_POWER_ZERO = 0,
	VIBRATION_POWER_WEAK = 40,
	VIBRATION_POWER_MIDDLE = 80,
	VIBRATION_POWER_STRONG = DGE_VIB_STRENGTH_MAX,
};

// ���� ���� ���� ����
void VibrationStop()
{
	// ���� ���� ��ġ ���� Ȯ��
	if(DGE_VIB_STATUS_BUSY == DGE_HapticStatus())
	{
		// �۵� ��

		// ���� ����
		DGE_HapticStop();
	}
}

// ���� ���� ��� �ʱ�ȭ
void InitializeVibrationRecord()
{
	// ���� ���� ��� ���� ���� ũ�⸸ŭ �ݺ�
	for(int count = 0; count != DGE_VIB_MAX_ACTION; ++count)
	{
		// ���� ���� ��� �ʱ�ȭ
		vibrationRecord[count].time_line = 0;
		vibrationRecord[count].vib_strength = VIBRATION_POWER_ZERO;
	}

	// ���� ���� ��� �ð� �ʱ�ȭ
	recordTime = 0;

	// ���� ���� ��� ��ġ �ʱ�ȭ
	recordPosition = 0;
}

// ���� ���� ���( ���� ���� )
void RecordVibrationPlay(int playTime, int strength)
{
	// ���� ���� ��� ��ġ ���� Ȯ��
	// ( �ִ� ����, ���� ó�� ��� - 1, �迭 �ε��� ��� - 1)
	if((0 > recordPosition) || ( DGE_VIB_MAX_ACTION - 2 < recordPosition))
	{
		// ��� ���� �̿�( ��� �Ұ��� )
		return;
	}

	// ��� ���� �̳�( ��� ���� )

	// ���� ���� ���
	vibrationRecord[recordPosition].time_line = (short)recordTime;
	vibrationRecord[recordPosition].vib_strength = (short)strength;

	// ���� ���� ���� ��� �ð� ����
	recordTime += playTime;

	// ���� ���� ���� ��� ��ġ ����
	++recordPosition;	
}

// ���� ���� ��� ���
void PlayVibrationRecord()
{
	// ���� ���� ��� ��ġ ���� Ȯ��
	if(0 >= recordPosition)
	{
		// ��� ���� �̿�( ��� �Ұ���, ���� ���� )
		return;
	}

	// ���� ���� ���� ����
	VibrationStop();

	// ���� ���� ��� ���� ó��
	vibrationRecord[recordPosition].time_line = (short)recordTime;
	vibrationRecord[recordPosition].vib_strength = (short)VIBRATION_POWER_ZERO;

	// ���� ����
	pattern_data_t vibrationPattern;

	// ���� ����

	// ���� ���� ��� ���� ����( �迭 �ε��� ��� + 1 )
	vibrationPattern.act_number = recordPosition + 1;

	// ���� ���� ��� ���� ���� ũ�⸸ŭ �ݺ�
	for(int count = 0; count != DGE_VIB_MAX_ACTION; ++count)
	{
		// ���� ���� ��� ���� ����
		vibrationPattern.vib_act_array[count].time_line = vibrationRecord[count].time_line;
		vibrationPattern.vib_act_array[count].vib_strength = vibrationRecord[count].vib_strength;
	}

	// ���� ���� ��� ���
	DGE_HapticPlayPattern(&vibrationPattern);
}




// ���� ǥ��( �������̽�, ���� ���� ��� )
void DisplayInformation()
{
	// ���� ��� ���� �ʱ�ȭ
	char sbuf[128]={0};
	DGXVECTOR2 vcPos;

	// �۲� ��� ��ġ
	int positionX = 20;
	int positionY = 20;

	// ��ư ��� �뵵 ���

	// A ��ư ��� �뵵 ���
	sprintf(sbuf, "A Button : Strength Zero");
	vcPos = DGXVECTOR2((float)positionX, (float)positionY);
	m_pFont->SetString(sbuf);
	m_pFont->SetPos(&vcPos);
	m_pFont->SetColor(&m_FontColor);
	m_pFont->DrawTxt();

	// ���� ���� ��� ��ġ ����
	positionY += m_FontHeight;
	vcPos = DGXVECTOR2((float)positionX, (float)positionY);

	// Y ��ư ��� �뵵 ���
	sprintf(sbuf, "Y Button : Strength Weak");
	vcPos = DGXVECTOR2((float)positionX, (float)positionY);
	m_pFont->SetString(sbuf);
	m_pFont->SetPos(&vcPos);
	m_pFont->SetColor(&m_FontColor);
	m_pFont->DrawTxt();


	// ���� ���� ��� ��ġ ����
	positionY += m_FontHeight;
	vcPos = DGXVECTOR2((float)positionX, (float)positionY);

	// B ��ư ��� �뵵 ���
	sprintf(sbuf, "B Button : Strength Middle");
	m_pFont->SetString(sbuf);
	m_pFont->SetPos(&vcPos);
	m_pFont->SetColor(&m_FontColor);
	m_pFont->DrawTxt();




	// ���� ���� ��� ��ġ ����
	positionY += m_FontHeight;
	vcPos = DGXVECTOR2((float)positionX, (float)positionY);

	// X ��ư ��� �뵵 ���
	sprintf(sbuf, "X Button : Strength Strong");
	m_pFont->SetString(sbuf);
	m_pFont->SetPos(&vcPos);
	m_pFont->SetColor(&m_FontColor);
	m_pFont->DrawTxt();


	// ���� ���� ��� ��ġ ����
	positionY += m_FontHeight;
	vcPos = DGXVECTOR2((float)positionX, (float)positionY);

	// L ��ư ��� �뵵 ���
	sprintf(sbuf, "L Button : Initialize Vibration Record");
	m_pFont->SetString(sbuf);
	m_pFont->SetPos(&vcPos);
	m_pFont->SetColor(&m_FontColor);
	m_pFont->DrawTxt();
	

	// ���� ���� ��� ��ġ ����
	positionY += m_FontHeight;
	vcPos = DGXVECTOR2((float)positionX, (float)positionY);

	// R ��ư ��� �뵵 ���
	sprintf(sbuf, "R Button : Play Vibration Record");
	m_pFont->SetString(sbuf);
	m_pFont->SetPos(&vcPos);
	m_pFont->SetColor(&m_FontColor);
	m_pFont->DrawTxt();


	// ���� ���� ��� ��ġ ����
	positionY += m_FontHeight;
	vcPos = DGXVECTOR2((float)positionX, (float)positionY);

	// ��� ǥ�� ����
	int space = 45;

	// ���� ���� ��� ���

	// ���� ���� ��� ������ŭ �ݺ�
	for(int count = 0; count != recordPosition; ++count)
	{
		vcPos = DGXVECTOR2((float)positionX, (float)positionY);
		m_pFont->SetPos(&vcPos);
		m_pFont->SetColor(&m_FontColor);

		// ���� ���� ���� Ȯ��
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
				// ���� �߻�
				break;
			}
		}

		// ���� ���� ���� ���� ǥ�� ��ġ ����
		positionX += space;

		// �� ���� �ʿ� ���� Ȯ��
		if(DGE_DISPLAY_DEFAULT_WIDTH - space <= positionX)
		{
			// �� ���� �ʿ�

			// ���� ���� ���� ���� ǥ�� ��ġ ����
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


	if(m_pInput->KeyDown(DGEKEY_MENU))	// ���� ��û
		return -1;


		
	// ���� ���� ����
	bool isChangeInformation = false;

	// ���� ���� ��� ����
	bool isRecord = false;

	// ���� ����
	int vibrationStrength = VIBRATION_POWER_ZERO;

	// ���� ��û Ȯ��
	if(m_pInput->KeyDown(DGEKEY_FA))
	{
		// ���� ���� ����
		vibrationStrength = VIBRATION_POWER_ZERO;

		// ���� ���� ���
		isRecord = true;
	}
	if(m_pInput->KeyDown(DGEKEY_FY))
	{
		// ���� ���� ��
		vibrationStrength = VIBRATION_POWER_WEAK;

		// ���� ���� ���
		isRecord = true;
	}
	if(m_pInput->KeyDown(DGEKEY_FB))
	{
		// ���� ���� �߰�
		vibrationStrength = VIBRATION_POWER_MIDDLE;

		// ���� ���� ���
		isRecord = true;
	}
	if(m_pInput->KeyDown(DGEKEY_FX))
	{
		// ���� ���� ��
		vibrationStrength = VIBRATION_POWER_STRONG;

		// ���� ���� ���
		isRecord = true;
	}

	// ���� ���� ��� ��� ��û ���� Ȯ��
	if(m_pInput->KeyDown(DGEKEY_FR))
	{
		// ���� ���� ��� ���
		PlayVibrationRecord();
	}

	// ���� ���� ��� �ʱ�ȭ ��û ���� Ȯ��
	if(m_pInput->KeyDown(DGEKEY_FL))
	{
		// ���� ���� ��� �ʱ�ȭ
		InitializeVibrationRecord();

		// ���� ����
		isChangeInformation = true;
	}

	// ���� ���� ��� ���� Ȯ��
	if(isRecord)
	{
		// ���� ���� ���� ����
		VibrationStop();

		// ���� ���� ���
		DGE_HapticPlay(basisActivateTime, vibrationStrength);

		// ���� ���� ���
		RecordVibrationPlay(basisActivateTime, vibrationStrength);

		// ���� ����
		isChangeInformation = true;
	}



	m_pDev->BeginScene();	// Prepare Rendering...

	m_pDev->Clear(DGE_CLEAR_COLOR_BUFFER | DGE_CLEAR_DEPTH_BUFFER);	// Clear Backbuffer

	m_pSprite->Begin();		// Sprite Begin




	// ���� ���� ���� Ȯ��
	if(isChangeInformation)
	{
		// ���� ����		
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
	
	
	// DGE �ʱ�ȭ
	if(DGE_FAILED(DGE_Init()))
		return 0;

	// Main Procedure �Լ� ����
	if(DGE_FAILED(DGE_SetMainRunFunc(Run)))
		goto End;

	
	// Window ����
	m_hWnd = DGE_CreateWindow(WndProc, "DGE_Tutorial");
	if(NULL == m_hWnd)
		goto End;

	// Device ����
	if(DGE_FAILED(DGE_CreateDevice(NULL, &m_pDev, m_hWnd, NULL)))
		goto End;


	// Sprite ����
	if(DGE_FAILED(DGE_CreateSprite(NULL, &m_pSprite, m_pDev)))
		goto End;


	// Input ����
	if(DGE_FAILED(DGX_CreateInput(NULL, &m_pInput, m_pDev, m_hWnd)))
		goto End;

	
	// Font ���̺귯�� ����
	if(DGE_FAILED(DGX_TFFontOpen()))
		goto End;

	printf("DGX_TFFontOpen Success\n");

	// Font ����
	if(DGE_FAILED(DGX_CreateFont(NULL, &m_pFont, &tFont, m_pSprite)))
		goto End;

	printf("DGX_CreateFont Success\n");



	// ���� ��ġ �ʱ�ȭ
	if(DGE_FAILED(DGE_HapticOpen()))
		goto End;

	printf("DGE_HapticOpen Success\n");

	// ���� ��ġ Ȱ��ȭ
	if(DGE_FAILED(DGE_HapticEnable(1)))
		goto End;

	printf("DGE_HapticEnable Success\n");

	// ���� ���� ��� �ʱ�ȭ
	InitializeVibrationRecord();

	// ���α׷� ����
	while(1)
	{
		if(DGE_FAILED(DGE_Run()))
			break;

		// Flipping
		m_pDev->Present(0,0,0,0);
	}

End:

	DGE_HapticClose();				// ���� ��ġ ����

	DGX_DestroyFont(&m_pFont);		// Font ��ü ����
	DGX_TFFontClose();				// Font ���̺귯�� ����

	DGX_DestroyInput(&m_pInput);	// Input ����
	DGE_DestroySprite(&m_pSprite);	// Sprite ����
	DGE_DestroyDevice(&m_pDev);		// Device ����
	DGE_DestroyWindow(m_hWnd);		// Window ����
	DGE_Close();					// DGE ����

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

