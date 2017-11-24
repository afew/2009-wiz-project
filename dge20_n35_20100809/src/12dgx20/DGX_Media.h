//	Copyright(C) Gamepark Holdings. All rights reserved.
//	Dogma-G Game Studios In-House Library DGE
//
// Interface for the Media class.
//
////////////////////////////////////////////////////////////////////////////////


#if defined(_WIN32) || defined(WIN32)
	#if _MSC_VER > 1000
	#pragma once
	#endif
#endif


#ifndef _DGX_Media_H_
#define _DGX_Media_H_

#include <DGE_Type.h>



////////////////////////////////////////////////////////////////////////////////
// Mixer

enum EDGX_MIXER_CHANNEL
{
	// Media State
//	DGX_MIXER_VOLUME	= 0,	//             Head Volume
//	DGX_MIXER_HEADPHONE	= 0,	//             Head Volume
//	DGX_MIXER_PCM		= 4,	//             PCM    Volume
//	DGX_MIXER_SPEAKER	= 5,	//             Speaker Volume
//	DGX_MIXER_LINE		= 6,	//             Line   Volume
//	DGX_MIXER_MIC		= 7,	//             Microphone Volume
//	DGX_MIXER_CD		= 8,	//             CD     Volume
//	DGX_MIXER_ALTPCM	=10,	//             PCM2   Volume
//	DGX_MIXER_IGAIN		=12,	//             IGain  Volume
//	DGX_MIXER_LINE1		=14,	//             Line 1 Volume

	DGX_MIXER_VOLUME	= 0x0,	// Speaker
	DGX_MIXER_HEADPHONE	= 0x0,	// Speaker
	DGX_MIXER_BASS		= 0x1,	// Bass
	DGX_MIXER_TREBLE	= 0x2,	// Treble
	DGX_MIXER_PCM		= 0x4,	// PCM
	DGX_MIXER_LINE		= 0x6,	// Line
	DGX_MIXER_MIC		= 0x7,	// Microphone
	
	// _left : Left  or Minimum of Volume
	// _right: Right or Maximum of Volume
};


INT DGX_MixerOpen();											// Mixer Device Init
INT DGX_MixerClose();											// Mixer Device Release

INT	DGX_MixerGetVolumeRange(INT* Max,INT* Min);					// Get Mixer Device Volume Range. Max, Min value range is [0 ,127]
INT	DGX_MixerSetVolume(INT _channel, INT  _left, INT  _right);	// Set Mixer Device Volume
INT	DGX_MixerGetVolume(INT _channel, INT* _left, INT* _right);	// Get Mixer Device Volume


INT DGX_RecordingSound(char* pBuf);	// Recording:  need minimum 1024 byte. return Recorded size

enum
{
	// Battery state
	DGX_BATTERY_HIGH = 1,
	DGX_BATTERY_MID,
	DGX_BATTERY_LOW,
	DGX_BATTERY_EMPTY,
};

INT DGX_Battery();			// return Battery Remain


#endif


