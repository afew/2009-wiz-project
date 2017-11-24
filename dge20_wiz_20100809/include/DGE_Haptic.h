// Copyright(C) Gamepark Holdings. All rights reserved.
// Dogma-G Game Studios In-House Library DGE
//
// Vibration Motor
//
////////////////////////////////////////////////////////////////////////////////


#if defined(_WIN32) || defined(WIN32)
	#if _MSC_VER > 1000
	#pragma once
	#endif
#endif


#ifndef _DGE_Haptic_H_
#define _DGE_Haptic_H_


#ifdef __cplusplus
extern "C" {
#endif


enum DGE_HAPTIC
{
	DGE_VIB_ALL				= 0,		// Left and Right Motor.
	DGE_VIB_LEFT			= 1,		// Left Motor. Not Supported
	DGE_VIB_RIGHT			= 2,		// Right Motor, Not Supported

	DGE_VIB_STATUS_IDLE		= 0,		// Motor Status Idle
	DGE_VIB_STATUS_BUSY		= 1,		// Motor Status Activating
	DGE_VIB_STRENGTH_MIN	= -126,		// Maximum Strength of Vibration
	DGE_VIB_STRENGTH_MAX	= 126,		// Minimum Strength of Vibration
	DGE_VIB_MAX_ACTION		= 120		// Mzsimum Action Map
};


#if defined(_WIN32) || defined(WIN32)

	#pragma pack(push, 2)
	struct _vibration_act
	{
		short time_line;			// millisecond base...
		short vib_strength;
	};
	#pragma pack(pop)

#else

	struct _vibration_act
	{
		short time_line;			// millisecond base...
		short vib_strength;
	}__attribute__ ((packed)) ;

#endif

typedef struct _vibration_act vibration_act_t;


struct _pattern_data
{
   	int act_number;					// include finish sequence and action number+1. action이 1이면 act_number=2
	vibration_act_t vib_act_array[DGE_VIB_MAX_ACTION];
};

typedef struct _pattern_data pattern_data_t;


int		DGE_HapticOpen();							// Vibration Motor 사용 초기화
int		DGE_HapticClose();							// Vibration Motor 사용 해제
int		DGE_HapticStatus();							// Vibration Motor Status busy = VIB_STATUS_BUSY, stop = VIB_STATUS_IDLE
int		DGE_HapticEnable(int v);					// Vibration Motor Enable=TRUE, Disable = FALSE

int		DGE_HapticPlay(int time_line /*millisecond*/, int strength);	// Vibration Motor Play One-Action

int		DGE_HapticPlayPattern(pattern_data_t*);		// Vibration Motor Play
int		DGE_HapticStop();							// Vibration Motor Stop



#ifdef __cplusplus
}
#endif


#endif //_DGE_Haptic_H_



