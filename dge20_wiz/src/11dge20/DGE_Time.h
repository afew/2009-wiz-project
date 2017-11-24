// Copyright(C) Gamepark Holdings. All rights reserved.
// Dogma-G Game Studios In-House Library DGE
//
// for Date, Time, Timer....
//
////////////////////////////////////////////////////////////////////////////////


#if defined(_WIN32) || defined(WIN32)
	#if _MSC_VER > 1000
	#pragma once
	#endif
#endif


#ifndef _DGE_Time_H_
#define _DGE_Time_H_


#ifdef __cplusplus
extern "C" {
#endif


int				DGE_tzset();
unsigned int	DGE_GetTickCount();									// After Booting... return Millisecond time
int				DGE_Sleep(unsigned int Milliseconds);				// Sleep

unsigned int	DGE_GetTicks();
long			DGE_DateandTime(char *tmpbuf/*need 128byte*/);		// System Date, Time




#ifdef __cplusplus
}
#endif


#endif //_DGE_Time_H_



