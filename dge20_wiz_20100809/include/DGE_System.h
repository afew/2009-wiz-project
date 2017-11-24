// Copyright(C) Gamepark Holdings. All rights reserved.
// Dogma-G Game Studios In-House Library DGE
//
// 윈도우 생성, 주변 장치 등의 제어에 필요한 Interface.
//
//
////////////////////////////////////////////////////////////////////////////////


#if defined(_WIN32) || defined(WIN32)
	#if _MSC_VER > 1000
	#pragma once
	#endif
#endif


#ifndef _DGE_System_H_
#define _DGE_System_H_

#include "DGE_Type.h"



INT	DGE_Version(DWORD* dVer, DWORD* dDate);		// SDK 버전 정보: Version(Major(Hi-word), Minor(Low-word), Build-date
INT DGE_Init();									// Initialize DGE and system
INT DGE_Close();								// Release DGE and system


// Create/Destroy Window
typedef LRESULT (DGE_CALLBACK* pDGE_MsgProc)(DGE_HWND, UINT, WPARAM, LPARAM);
typedef INT (DGE_CALLBACK* pDGE_Run)(DGE_HANDLE);

DGE_HWND DGE_CreateWindow(pDGE_MsgProc, char* ClassName, INT ScreenW=0, INT ScreenH=0);
INT		DGE_DestroyWindow(DGE_HANDLE);

INT		DGE_SetMainRunFunc(pDGE_Run);					// Set Main Processing Run Function
INT		DGE_Run();										// Main Processing
INT		DGE_WindowSize(INT* pWidth, INT* pHeight );		// Window Size

#endif

