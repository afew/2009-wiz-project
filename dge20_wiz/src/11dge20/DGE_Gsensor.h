// Copyright(C) Gamepark Holdings. All rights reserved.
// Dogma-G Game Studios In-House Library DGE
//
// G-Sensor.
//
////////////////////////////////////////////////////////////////////////////////


#if defined(_WIN32) || defined(WIN32)
	#if _MSC_VER > 1000
	#pragma once
	#endif
#endif


#ifndef _DGE_Gsensor_H_
#define _DGE_Gsensor_H_


#ifdef __cplusplus
extern "C" {
#endif


enum DGE_GSENSOR
{
	// Gravity Value
	DGE_GSN_GRAN2	= 2, // default
	DGE_GSN_GRAN4	= 4,
	DGE_GSN_GRAN8	= 8,

	// Gravity Resolution
	DGE_GSN_GRES8	= 8,	// 8-Bit
	DGE_GSN_GRES12	= 12,	// 12-Bit Default

	// Tap Frequency(Hz)
	DGE_GSN_TAB50	= 50,	// 50Hz
	DGE_GSN_TAB100	= 100,	// 100Hz
	DGE_GSN_TAB200	= 200,	// 200Hz
	DGE_GSN_TAB400	= 400,	// 400Hz Default


	// Screen Tilt Frequency(Hz)
	DGE_GSN_TILT1	= 1,
	DGE_GSN_TILT6	= 6,
	DGE_GSN_TILT12	= 12, // Default
	DGE_GSN_TILT50	= 50,

	// Tap Event
	DGE_GSN_FU	= 0x01,		// +Z positive tap detection
	DGE_GSN_FD	= 0x02,		// -Z negative tap detection
	DGE_GSN_UP	= 0x04,		// +Y positive tap detection 
	DGE_GSN_DO	= 0x08,		// -Y negative tap detection
	DGE_GSN_RI	= 0x10,		// +X positive tap detection
	DGE_GSN_LE	= 0x20,		// -X negative tap detection

	DGE_GSN_DEFAULT	= 0xFFFF,
};



// G-sensor Environment
typedef struct tagDGE_GSENSOR_ENV
{
	int Range		;		// Gravity Range. 2G, 4G, 8G
	int Resolution	;		// 8-bit , 12-bit
	int	TapHz		;		// 50, 100, 200, 400 Hz
	int	TiltHz		;		// 1, 6, 12, or 50
	int	TiltTimer	;		// [0, 255] int
}DGE_GSENSOR_ENV;


// Read From G-sensor
typedef struct tagDGE_GSENSOR_VAL
{
	int x, y, z;			// Gravity force values on the X, Y, and Z axes. no value = 0xFFFF
	int TapMod;				// Tab Mode	= +/-
	int TapDir;				// Tap Direction. no event = DGE_GSN_DEFAULT

}DGE_GSENSOR_VAL;


int		DGE_GsensorOpen();							// G-sensor 사용 초기화
int		DGE_GsensorClose();							// G-sensor 사용 해제

int		DGE_GsensorSetEnv(DGE_GSENSOR_ENV* pIn);	// Setup Environment
int		DGE_GsensorRead(DGE_GSENSOR_VAL* pOut);		// Read data from g-sensor


#ifdef __cplusplus
}
#endif


#endif //_DGE_Gsensor_H_


