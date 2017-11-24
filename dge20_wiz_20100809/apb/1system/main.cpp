
#if defined(_WIN32)
	#pragma comment(lib, "dge20_.lib")

	#include <windows.h>

#endif

#include <stdio.h>

#include <limits.h>

#include <DGE_Type.h>
#include <DGE_System.h>
#include <DGE_Time.h>
#include <DGE_Math.h>


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
			SendMessage(hWnd, WM_DESTROY, 0, 0);
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

	// DGE�� �ƹ� ó���� �մϴ�. ���� ������� ���¸� ���߱⸸ �մϴ�.

	return DGE_OK;

#endif
}






INT DGE_CALLBACK Run(void*)
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

	Sleep(10);
#else


#endif
	
	static int c=0;
	++c;

	if(c>5000)
	{
		printf("Game Process Terminated\n");
		return -1;
	}

	printf("Run %d\n", c);

	return 0;
}


// Main Program
int main(int argc, char* argv[])
{
	DWORD	dVersion=0;
	DWORD	dDate=0;

	printf("Version: %x Date: %x\n", dVersion, dDate);

	// DGE �ʱ�ȭ
	if(DGE_FAILED(DGE_Init()))
		return -1;


	// DGE ���� Ȯ��
	DGE_Version(&dVersion, &dDate);
	printf("Version: %x Date: %x\n", dVersion, dDate);


	// Window ����
	DGE_HANDLE hWnd = DGE_CreateWindow(WndProc, "DGE_Tutorial");
	if(NULL == hWnd)
		return -1;


	DGE_SetMainRunFunc(Run);


	// ���α׷� ����
	while(1)
	{
		if(DGE_FAILED(DGE_Run()))
			break;
	}



	// Window ����
	DGE_DestroyWindow(hWnd);


	// DGE ����
	DGE_Close();


	return 0;
}


