// Implementation of the DGE System.
//
////////////////////////////////////////////////////////////////////////////////

#if defined(_WIN32) || defined(WIN32)
	#if _MSC_VER >= 1200
	#pragma warning(disable: 4996)
	#endif

	#include <windows.h>

#else

	#define	lf_linux
	#define	__int64	long long

	#include <unistd.h>
	#include <fcntl.h>
	#include <pollux_fb_ioctl.h>
	#include <OpenGLES/libogl.h>

	#include <sys/mman.h>
	#include <sys/types.h>
	#include <sys/stat.h>
	#include <sys/ioctl.h>
	#include <sys/time.h>

	//	#include <fcntl.h>


	#define VID_RGBFMT_R5G6B5   0x4432
	#define WIZ_3D	  0x11
	#define BOARD_WIZ 0xaa

	//	Wiz인지 F300인지 구분하기 위해 사용한다. 왜냐~ Wiz일 경우
	//	화면 티어링을 방지하기 위해 프레임버퍼를 240*320으로 셋팅해 줘야 하기 때문이다.
	//	F300은 프레임버퍼가 320*240이기 때문에 셋팅이 필요 없다. 여기서 define만 했고 실제로는
	//	커널에서 기기에 맞게 static 하게 셋팅되기 때문에 여기에 선언만 하면 된다.

	#define P_3DE		2
	#define DEV_NAME	"/dev/ga3d"
	#define MEM_NAME	"/dev/mem"
	#define PHYS_ADDR	0xc001a000

	// 아무래도 텍스처를 할당에 더 많은 메모리가 소요되기 때문에 2D를 좀 더 많이 할당 함.
	// 1D(Vertex Memory) 메모리를 4메가로 잡아 준다
	#define MEM1_PHYS	0x03000000
	#define mem1size	0x00400000  //4MB
	#define mem1virt	(void*)0xb1000000


	// 2D(Texture Memory) 메모리를 12메가로 설정해 준다
	#define MEM2_PHYS	 ( MEM1_PHYS + mem1size )
	#define mem2size	 ( mem1size + 0x00800000 ) //12MB
	#define mem2virt	 (void*)((unsigned int)mem1virt + mem1size)
	#define FB_DEV_PATH	 "/dev/fb0"

	#define DISPLAY__00	 0
	#define DISPLAY__90	 1
	#define DISPLAY_180	 2
	#define DISPLAY_270	 3
	#define SCALE	  1000


	#define	FBIO_DIRTFLAG	1
	#define FBIO_GET_3D_NUMBER	2


	void* DGE_OS_CreateWindow();


	unsigned int	DGE_OS_GetTickCount();

	void	GLESOAL_Sleep( unsigned long Milliseconds );
	void	DGE_OS_GetWindowSize(void*, int* width, int* height);
	void	DGE_OS_Sleep( unsigned int milliseconds );
	int		GLESOAL_GetDisplayDirection();
	int		GLESOAL_GetDisplayDirection();
	int		GLESOAL_Initalize( ___OAL_MEMORY_INFORMATION__* pMemoryInfomation, int FSAAEnb);
	void	GLESOAL_Finalize();
	void	GLESOAL_SwapBufferCallback();
	void	GLESOAL_SetWindow	( void* pNativeWindow  );
	void	GLESOAL_GetWindowSize( int* pWidth, int* pHeight );
	void	GLESOAL_WaitForDisplayAddressPatched();
	void	GLESOAL_SetDisplayAddress( const unsigned int DisplayBufferPhysicalAddress );
	void	GLESOAL_Sleep( unsigned long Milliseconds );
	unsigned int	DGE_OS_GetTickCount();

	void	GLESOAL_Sleep( unsigned long Milliseconds );
	void	DGE_OS_GetWindowSize(void*, int* width, int* height) ;
	void	DGE_OS_Sleep( unsigned int milliseconds );
	int		GLESOAL_GetDisplayDirection();
	int		GLESOAL_GetDisplayDirection();
	int		GLESOAL_Initalize( ___OAL_MEMORY_INFORMATION__* pMemoryInfomation, int FSAAEnb);
	void	GLESOAL_Finalize();
	void	GLESOAL_SwapBufferCallback();
	void	GLESOAL_SetWindow	( void* pNativeWindow  );
	void	GLESOAL_GetWindowSize( int* pWidth, int* pHeight );
	void	GLESOAL_WaitForDisplayAddressPatched();
	void	GLESOAL_SetDisplayAddress( const unsigned int DisplayBufferPhysicalAddress );
	void	GLESOAL_Sleep( unsigned long Milliseconds );

//	static int			fd_mem;
//	static int			fd_dev;
//
//	static void*		p3DE = NULL;
//	static int			len3DE;
//
//	static void*		mem1 = NULL;
//	static void*		mem2 = NULL;
//
//	static FB_RGBSET	rgbset;
//	static unsigned int	DevEnable[3];
//	static int			fb_fd;
//	static int			g_FSAAEnb = 0;

#endif


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "DGE_Type.h"
#include "DGE_System.h"
#include "DGE_Time.h"



// Global or Default Value

#if defined(_WIN32) || defined(WIN32)
	static INT	g_DGE_ScnW= 640;
	static INT	g_DGE_ScnH= 480;
#else
	static INT	g_DGE_ScnW= 320;
	static INT	g_DGE_ScnH= 240;
#endif


static INT	g_DGE_Active = FALSE;


INT (DGE_CALLBACK* g_pFUNC_Run)(DGE_HANDLE);

// Main Run Function
INT DGE_CALLBACK Default_Run(DGE_HANDLE){	return DGE_OK;}



// Version:
// 0x0000 0000
//	Major Minor
// 0x 0000   00    00
//    Year   Month Day

INT DGE_Version(DWORD* dVer, DWORD* dDate)
{
	if(dVer)	*dVer = DGE_SDK_VER;
	if(dDate)	*dDate= DGE_SDK_DATE;

	return DGE_OK;
}


// DGE System Init : Global and Environment Init
INT DGE_Init()
{
	g_DGE_Active = TRUE;
	g_pFUNC_Run	= Default_Run;


	// Deive Init

	// Timer Init
	DGE_tzset();


	return DGE_OK;
}

// DGE System Destroy
INT DGE_Close()
{
	g_DGE_Active = FALSE;

#if !(defined(_WIN32) || defined(WIN32))
	chdir("/usr/gp2x");

//	execl("/usr/gp2x/gp2xmenu", "/usr/gp2x/gp2xmenu", NULL);

	system("./gpid.gpu &");
	execlp("/usr/gp2x/gp2xmenu", "/usr/gp2x/gp2xmenu", "--disable-autorun", NULL, 0);
#endif

	return DGE_OK;
}


// Window 생성
DGE_HWND DGE_CreateWindow(pDGE_MsgProc WndProc, char* ClassName, INT ScreenW, INT ScreenH)
{
	DGE_HWND hRet = NULL;

#if defined(_WIN32) || defined(WIN32)
	HWND	hWnd = NULL;
	HINSTANCE	hInst = (HINSTANCE)GetModuleHandle(NULL);
	WNDCLASS wc=
	{
		CS_HREDRAW | CS_VREDRAW
		,	WndProc
		,	0L
		,	0L
		,	hInst
		,	LoadIcon(NULL, IDI_APPLICATION)
		,	LoadCursor(NULL, IDC_ARROW)
		,	(HBRUSH)GetStockObject(WHITE_BRUSH)
		,	NULL
		,	ClassName
	};

	if( 0==	RegisterClass(&wc))
		return NULL;

	if(0<ScreenW)	g_DGE_ScnW	= ScreenW;
	if(0<ScreenH)	g_DGE_ScnH	= ScreenH;


	DWORD dStyle=WS_VISIBLE | WS_CAPTION | WS_SYSMENU;
	RECT rc = {0,0, g_DGE_ScnW, g_DGE_ScnH};
	AdjustWindowRect(&rc, dStyle, FALSE);

	hWnd = CreateWindow(ClassName
						  , ClassName
						  , dStyle
						  , 1
						  , 1
						  , rc.right  - rc.left
						  , rc.bottom - rc.top
						  , NULL
						  , NULL
						  , hInst
						  , NULL);

	if (NULL == hWnd)
		return NULL;

	EnableWindow( hWnd, TRUE);
	SetForegroundWindow(hWnd);
	ShowWindow(hWnd, SW_SHOWNORMAL);

	hRet = hWnd;

#else
	hRet = DGE_OS_CreateWindow();
#endif

	printf("Creat Window Success\n");

	return hRet;
}


// Window 해제()
INT DGE_DestroyWindow(DGE_HANDLE hWnd)
{
#if defined(_WIN32) || defined(WIN32)

#else
	free(hWnd);
#endif

	return DGE_OK;
}

// Setup Main Run Function Pointer.  Callback Application Program
INT DGE_SetMainRunFunc(INT (DGE_CALLBACK*pFunc)(DGE_HANDLE) )
{
	g_pFUNC_Run = pFunc;
	return DGE_OK;
}

// Main Run Function
INT DGE_Run()
{
	if(!g_DGE_Active)
		return DGE_EFAIL;

	// Run Process

	return g_pFUNC_Run(NULL);
}


// Window Size
INT DGE_WindowSize(INT* pWidth, INT* pHeight )
{
    *pWidth  = g_DGE_ScnW;
    *pHeight = g_DGE_ScnH;
	return DGE_OK;
}


#if !(defined(_WIN32) || defined(WIN32))

void* DGE_OS_CreateWindow()
{
	return malloc( 16*1024);
}

#endif


