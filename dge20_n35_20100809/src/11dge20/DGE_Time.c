// Implementation of the DGE Time.
//
////////////////////////////////////////////////////////////////////////////////


#if defined(_WIN32) || defined(WIN32)
	#if _MSC_VER >= 1200
	#pragma warning(disable: 4996)
	#endif

	#include <Windows.h>

	#include <time.h>
	#include <stdio.h>
	#include <sys/types.h>
	#include <sys/timeb.h>
	#include <string.h>
#else

	#include <fcntl.h>
	#include <signal.h>
	#include <unistd.h>

	#include <time.h>
	#include <sys/time.h>


#endif


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>


#include "DGE_Time.h"



#ifndef DGE_INLINE
#define DGE_INLINE __inline
#endif


// Return Value
#ifndef DGE_SUCCEEDED
#define DGE_SUCCEEDED(hr) ((HRESULT)(hr) >= 0)
#define DGE_FAILED(hr) ((HRESULT)(hr) < 0)
#endif

#define DGE_DEFAULT	((UINT) -1)
#define DGE_OK						0x00000000
#define DGE_EFAIL					-1
#define DGE_ENOTIMPLEMENTED			0XF0000004



int	DGE_tzset()
{
#if defined(_WIN32) || defined(WIN32)
	_tzset();
#else
	tzset();
#endif
	
	return 0;
}



long DGE_DateandTime(char *tmpbuf/*need 128byte*/)
{
	time_t ltime;

	time( &ltime );
	sprintf(tmpbuf, "%s", ctime( &ltime ) );

	return ltime;
}

unsigned int DGE_GetTickCount()
{
	unsigned int ticks=0;

#if defined(_WIN32) || defined(WIN32)
	ticks = GetTickCount();
#else

	#if HAVE_CLOCK_GETTIME

		struct timespec now;
		clock_gettime(CLOCK_MONOTONIC,&now);
		ticks=(now.tv_sec-start.tv_sec)*1000+(now.tv_nsec-start.tv_nsec)/1000000;

	#else

		struct timeval now;
		gettimeofday( &now, NULL);

		ticks = now.tv_sec * 1000  +  now.tv_usec/1000;
		//ticks = (now.tv_sec-start.tv_sec) * 1000 + (now.tv_usec-start.tv_usec)/1000;

	#endif



#endif

	return ticks;
}

int DGE_Sleep(unsigned int Milliseconds)
{
#if defined(_WIN32) || defined(WIN32)
	Sleep(Milliseconds);
#else
	Milliseconds *= 1000;
    if (Milliseconds == 0)
        Milliseconds = 1;
    usleep( Milliseconds );
#endif

	return DGE_OK;
}

