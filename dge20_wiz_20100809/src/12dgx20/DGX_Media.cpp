// Implementation of the Mixer.
//
////////////////////////////////////////////////////////////////////////////////


#if defined(_WIN32) || defined(WIN32)
	#if _MSC_VER >= 1200
	#pragma warning(disable: 4996)
	#endif

	#include <windows.h>

#else

	#include <fcntl.h>
	#include <unistd.h>
	#include <stdarg.h>
	#include <time.h>
	#include <sys/ioctl.h>
	#include <linux/soundcard.h>

//	#include <fcntl.h>
	#define BATTERY_FNAME		"/dev/pollux_batt"

#endif


#include <stdio.h>
#include <stdlib.h>

#include <DGE_Type.h>

#include "DGX_Media.h"



////////////////////////////////////////////////////////////////////////////////
// Recording
INT DGX_RecordingSound(char* pBuf)	// 녹음: 1024byte 필요. 저장된 크기 반환
{
	printf("Not Implemented\n");
	return DGE_ENOTIMPLEMENTED;
}



////////////////////////////////////////////////////////////////////////////////
// Battery
INT DGX_Battery()
{
	// Battery Status
	unsigned short uBattery = (unsigned short)DGX_BATTERY_HIGH;

#if !(defined(_WIN32) || defined(WIN32))

	// Device Open
	int dev_fd = open(BATTERY_FNAME, O_RDONLY);

	// Open Failed.
	if(0>dev_fd)
	{
		printf("Battery Information Open Failed\n");
		return 0;
	}


//	// Success
//	printf("Battery Information Open Success!\n");


	// Read Device Data.
	read(dev_fd, &uBattery, sizeof(unsigned short));

	// Device Close
	close(dev_fd);
#endif

	return uBattery;
}



INT DGX_Wifi()
{
	printf("Not Implemented\n");
	return DGE_ENOTIMPLEMENTED;
}



