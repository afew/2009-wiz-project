// Implementation of the DGE Haptic moter.
//
////////////////////////////////////////////////////////////////////////////////


#if defined(_WIN32) || defined(WIN32)
	#if _MSC_VER >= 1200
	#pragma warning(disable: 4996)
	#endif

#else

	#include <unistd.h>
	#include <fcntl.h>

	#include <sys/types.h>
	#include <sys/stat.h>
	#include <sys/ioctl.h>

	#define HAPTIC_IOCTL_MAGIC	'I'

	//ioctl() commands... 
	#define IOCTL_MOTOR_DRV_ENABLE	_IO(HAPTIC_IOCTL_MAGIC, 0) 
	#define IOCTL_MOTOR_DRV_DISABLE	_IO(HAPTIC_IOCTL_MAGIC, 1) 

	/* user application interface */
	#define IOCTL_FFLUSH_JOB		_IO(HAPTIC_IOCTL_MAGIC, 2)
	#define IOCTL_JOB_STATUS		_IOR(HAPTIC_IOCTL_MAGIC, 3, unsigned int)
	#define IOCTL_PLAY_PATTERN		_IOW(HAPTIC_IOCTL_MAGIC, 4, pattern_data_t)

	//added command for hardware test by lars 2010-06-18...
	#define IOCTL_INDIVIDUAL_MODE   _IOW(HAPTIC_IOCTL_MAGIC, 5, unsigned int)	// 1:enable 0:disable
	#define IOCTL_ISA1200A_ENABLE   _IO(HAPTIC_IOCTL_MAGIC, 6)
	#define IOCTL_ISA1200B_ENABLE   _IO(HAPTIC_IOCTL_MAGIC, 7)
	/* Vibration Level Related Commands  */
	#define IOCTL_GET_VIB_LEVEL		_IOR(HAPTIC_IOCTL_MAGIC, 8, unsigned int)
	#define IOCTL_SET_VIB_LEVEL		_IOW(HAPTIC_IOCTL_MAGIC, 9, unsigned int)
	#define IOCTL_HAPTIC_MAXNR		10

	#define DEVICE_FILENAME "/dev/isa1200"

#endif


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>


// Return Value
#ifndef DGE_SUCCEEDED
#define DGE_SUCCEEDED(hr) ((HRESULT)(hr) >= 0)
#define DGE_FAILED(hr) ((HRESULT)(hr) < 0)
#endif

#define DGE_DEFAULT	((UINT) -1)
#define DGE_OK						0x00000000
#define DGE_EFAIL					-1
#define DGE_EINVALIDATE_CALL		0XF0000001
#define DGE_ECANNOTALLOCATED		0XF0000002
#define DGE_ECANNOTFIND_RESOURCE	0XF0000003
#define DGE_ENOTIMPLEMENTED			0XF0000004
#define DGE_ECANNOTACQUIRE_DEVICE	0XF0000005
#define DGE_INVALID_DEVICE			-1


#include "DGE_Haptic.h"



static int g_fdDgeHaptic= DGE_INVALID_DEVICE;



int DGE_HapticOpen()
{
#if defined(_WIN32) || defined(WIN32)
	
	printf("Not Implemented in this Device\n");
	return DGE_INVALID_DEVICE;

#else
	g_fdDgeHaptic = open(DEVICE_FILENAME, O_RDWR|O_NDELAY);

	if(g_fdDgeHaptic <= 0)
	{
	   	printf("Haptic Device Open Failed\n");
	   	return DGE_EFAIL;
	}

	printf("Haptic Device Open Success\n");
#endif

	return DGE_OK;
}

int DGE_HapticClose()
{
#if defined(_WIN32) || defined(WIN32)

	printf("Not Implemented in this Device\n");
	return DGE_INVALID_DEVICE;

#else
	if( DGE_INVALID_DEVICE == g_fdDgeHaptic)
		return DGE_OK;

	close(g_fdDgeHaptic);
	g_fdDgeHaptic = DGE_INVALID_DEVICE;
#endif

	return DGE_OK;
}




int DGE_HapticStatus()		// Haptic Motor Device Status busy = DGE_VIB_STATUS_BUSY, stop = DGE_VIB_STATUS_IDLE
{
#if defined(_WIN32) || defined(WIN32)
	printf("Not Implemented in this Device\n");
	return DGE_INVALID_DEVICE;

#else
	if( DGE_INVALID_DEVICE == g_fdDgeHaptic)
		return DGE_VIB_STATUS_IDLE;

	typedef enum {_IDLE, _BUSY} job_status_t;
	job_status_t	job_status;

	ioctl(g_fdDgeHaptic, IOCTL_JOB_STATUS, &(job_status));
	return job_status;
#endif
}


int DGE_HapticEnable(int v)	// Haptic Motor Device Enable=TRUE, Disable = FALSE
{
#if defined(_WIN32) || defined(WIN32)
	printf("Not Implemented in this Device\n");
	return DGE_INVALID_DEVICE;

#else
	if( DGE_INVALID_DEVICE == g_fdDgeHaptic)
		return DGE_INVALID_DEVICE;

	if(v)
	   	ioctl(g_fdDgeHaptic, IOCTL_MOTOR_DRV_ENABLE);
	else
	   	ioctl(g_fdDgeHaptic, IOCTL_MOTOR_DRV_DISABLE);

	return DGE_OK;
#endif
}



int DGE_HapticPlay(int time_line, int strength)
{
#if defined(_WIN32) || defined(WIN32)
	printf("Not Implemented in this Device\n");
	return DGE_INVALID_DEVICE;

#else
	if( DGE_INVALID_DEVICE == g_fdDgeHaptic)
		return DGE_INVALID_DEVICE;

	if(strength>DGE_VIB_STRENGTH_MAX)	strength = DGE_VIB_STRENGTH_MAX;
	if(strength<DGE_VIB_STRENGTH_MIN)	strength = DGE_VIB_STRENGTH_MIN;

	short input_strength = strength;
	short input_timeline = time_line;

	pattern_data_t action;
	
	action.act_number = 1+1;
	action.vib_act_array[0].time_line = 0;
	action.vib_act_array[0].vib_strength = input_strength;
	action.vib_act_array[1].time_line = input_timeline;
	action.vib_act_array[1].vib_strength = 0;

	ioctl(g_fdDgeHaptic, IOCTL_PLAY_PATTERN, &action);
	return DGE_OK;
#endif
}




int DGE_HapticPlayPattern(pattern_data_t* action)	// Haptic Motor Play
{
#if defined(_WIN32) || defined(WIN32)
	printf("Not Implemented in this Device\n");
	return DGE_INVALID_DEVICE;

#else
	if( DGE_INVALID_DEVICE == g_fdDgeHaptic)
		return DGE_INVALID_DEVICE;

	ioctl(g_fdDgeHaptic, IOCTL_PLAY_PATTERN, action);
	return DGE_OK;
#endif
}


int DGE_HapticStop()
{
#if defined(_WIN32) || defined(WIN32)
	printf("Not Implemented in this Device\n");
	return DGE_INVALID_DEVICE;

#else
	if( DGE_INVALID_DEVICE == g_fdDgeHaptic)
		return DGE_INVALID_DEVICE;

	// 현재 PLAY중인 pattern data를 stop.
	ioctl(g_fdDgeHaptic, IOCTL_FFLUSH_JOB);
	return DGE_OK;
#endif
}


enum
{
	DGE_VIB_LVL_OFF = 0,
	DGE_VIB_LVL_WEAK,
	DGE_VIB_LVL_NORMAL,
	DGE_VIB_LVL_MAX,
};



int DGE_HapticGetLevel()
{
#if defined(_WIN32) || defined(WIN32)
	return 0;
#else
	int level=0;
	ioctl(g_fdDgeHaptic, IOCTL_GET_VIB_LEVEL, &level);
	return level;
#endif
}


int DGE_HapticSetLevel(int level)
{
	int hr=0;

#if defined(_WIN32) || defined(WIN32)
	return 0;
#else
	if(level<0 || level>DGE_VIB_LVL_MAX)
		return -1;

	hr = ioctl(g_fdDgeHaptic, IOCTL_GET_VIB_LEVEL, &level);
	return hr;
#endif
}


