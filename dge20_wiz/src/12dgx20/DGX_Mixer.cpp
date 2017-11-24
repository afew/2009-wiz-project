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

	#define MIXER_DEVICE	"/dev/mixer"

#endif


#include <stdio.h>
#include <stdlib.h>

#include <DGE_Type.h>

#include "DGX_Media.h"



#if defined(_WIN32) || defined(WIN32)

class CDGX_Mixer
{
protected:
	UINT		m_nMixer;
	HMIXER		m_hMixer;
	MIXERCAPS	m_mxcaps;

public:
	DWORD		m_dMin;
	DWORD		m_dMax;
	DWORD		m_dCtlID;

public:
	CDGX_Mixer();
	virtual ~CDGX_Mixer();

	INT Open();
	INT Close();
	INT GetMasterVolumeControl();
	INT GetMasterVolumeValue(DWORD* dwVal) const;
	INT SetMasterVolumeValue(DWORD dwVal) const;
};

#endif





#if defined(_WIN32) || defined(WIN32)
	static CDGX_Mixer*		g_pDevMixer = NULL;
#else
	static DGE_DEVICE		g_pDevMixer = -1;
#endif




// Master Volume 장치 사용 권한 얻기
INT DGX_MixerOpen()
{
#if defined(_WIN32) || defined(WIN32)
	if(g_pDevMixer)
		return DGE_OK;


	g_pDevMixer = new CDGX_Mixer;


	if(FAILED(g_pDevMixer->Open()))
	{
		delete g_pDevMixer;
		g_pDevMixer = NULL;
		return DGE_INVALID_DEVICE;
	}

	// Test...
	DWORD volume = 0;
	if(FAILED(g_pDevMixer->GetMasterVolumeValue(&volume)))
	{
		delete g_pDevMixer;
		g_pDevMixer = NULL;
		return DGE_ECANNOTACQUIRE_DEVICE;
	}

#else

	if(DGE_SUCCEEDED(g_pDevMixer))
		return DGE_OK;

	if(0 != access(MIXER_DEVICE, W_OK))
	{
		printf("Err: %d, %s \t", __LINE__, __FILE__);
		printf( "Mixer Access() Failed\n");
		return DGE_ECANNOTACQUIRE_DEVICE;
	}


	g_pDevMixer = open(MIXER_DEVICE, O_RDWR | O_NDELAY);
	if(DGE_FAILED(g_pDevMixer))
	{
		printf("Err: %d, %s \t", __LINE__, __FILE__);
		printf( "Mixer Open() Failed\n");
		return DGE_ECANNOTACQUIRE_DEVICE;
	}
#endif

	return DGE_OK;
}


// Master Volume 장치 닫기
INT DGX_MixerClose()
{
#if defined(_WIN32) || defined(WIN32)

	if(g_pDevMixer)
	{
		delete g_pDevMixer;
		g_pDevMixer = NULL;
	}

#else
	if(DGE_SUCCEEDED(g_pDevMixer))
	{
		::close(g_pDevMixer);
		g_pDevMixer = -1;
	}

#endif
	

	return DGE_OK;
}



// Master Volume 장치의 볼륨 최소값, 최대 값 얻기
INT	DGX_MixerGetVolumeRange(INT* Max,INT* Min)
{
#if defined(_WIN32) || defined(WIN32)
	*Max = g_pDevMixer->m_dMax/516;
	*Min = g_pDevMixer->m_dMin;
#else
	*Max = 127;
	*Min = 0;
#endif

	return DGE_OK;
}



//Mixer 장치의 볼륨(전체 볼륨) 설정
INT	DGX_MixerSetVolume(INT _channel, INT left, INT right)
{
	DWORD volume = 0;

#if defined(_WIN32) || defined(WIN32)
	if(0>left)		left = 0;
	if(127<left)	left = 127;
	if(0>right)		right = 0;
	if(127<right)	right = 127;

	volume = max(left, right);
	volume *= 516;
	g_pDevMixer->SetMasterVolumeValue(volume);

#else
	_channel |= 0xC0044D00;

	INT hr= 0;
	int ch = MIXER_WRITE(_channel);

	if(0  >left)	left = 0;
	if(120<left)	left  = 120;

	if(0  >right)	right = 0;
	if(120<right)	right = 120;

	volume = 256 * right + left;
	
	hr= ioctl(g_pDevMixer, ch, &volume);
	if(DGE_FAILED(hr))
	{
		printf("Err: %d, %s \t", __LINE__, __FILE__);
		printf( "Write volume() Failed\n");
	}

#endif
	
	return	DGE_OK;
}


INT	DGX_MixerGetVolume(INT _channel, INT* left, INT* right)
{
	DWORD volume = 0;

#if defined(_WIN32) || defined(WIN32)
	if(FAILED(g_pDevMixer->GetMasterVolumeValue(&volume)))
		return -1;

	*left = volume;
	*right= volume;
#else
	_channel |= 0xC0044D00;

	int ch = MIXER_READ(_channel);
	if(DGE_FAILED(ioctl(g_pDevMixer, ch, &volume)))
	{
		printf("Err: %d, %s \t", __LINE__, __FILE__);
		printf( "Read volume() Failed\n");
	}

	*left =  volume & 0x000000FF;
	*right= (volume>>8) & 0x000000FF;
#endif
	
	return	volume;
}












// Window Mixer
//////////////////////////////////////////////////////////////////////////////

#if defined(_WIN32) || defined(WIN32)

CDGX_Mixer::CDGX_Mixer()
{
	m_nMixer	= 0;
	m_hMixer	= NULL;
	m_dMin		= 0;
	m_dMax		= 0;
	m_dCtlID	= 0;
	memset(&m_mxcaps, 0, sizeof(MIXERCAPS));
}


CDGX_Mixer::~CDGX_Mixer()
{
	Close();
}


INT CDGX_Mixer::Open()
{
	MMRESULT hr = 0;

	if(m_nMixer && m_hMixer && m_dCtlID)
		return 0;


	m_nMixer = ::mixerGetNumDevs();

	if (m_nMixer != 0)
	{
		hr = ::mixerOpen(&m_hMixer, 0, NULL, NULL, MIXER_OBJECTF_MIXER | CALLBACK_WINDOW);
		if (MMSYSERR_NOERROR != hr)
			return -1;

		hr = ::mixerGetDevCaps(reinterpret_cast<UINT>(m_hMixer), &m_mxcaps, sizeof(MIXERCAPS));
		if (MMSYSERR_NOERROR != hr)
			return -1;
	}


	return GetMasterVolumeControl();
}


INT CDGX_Mixer::Close()
{
	if (!m_hMixer)
		return 0;

	MMRESULT hr = 0;
	hr = ::mixerClose(m_hMixer);
	
	m_hMixer = NULL;

	if(MMSYSERR_NOERROR == hr)
		return -1;

	return 0;
}

INT CDGX_Mixer::GetMasterVolumeControl()
{
	MMRESULT hr=0;

	if(!m_hMixer)
		return -1;


	// get dwLineID
	MIXERLINE mxl;
	mxl.cbStruct = sizeof(MIXERLINE);
	mxl.dwComponentType = MIXERLINE_COMPONENTTYPE_DST_SPEAKERS;
	hr = ::mixerGetLineInfo(reinterpret_cast<HMIXEROBJ>(m_hMixer),
						   &mxl,
						   MIXER_OBJECTF_HMIXER |
						   MIXER_GETLINEINFOF_COMPONENTTYPE);
	if (MMSYSERR_NOERROR != hr)
		return -1;

	// get dwControlID
	MIXERCONTROL mxc;
	MIXERLINECONTROLS mxlc;
	mxlc.cbStruct = sizeof(MIXERLINECONTROLS);
	mxlc.dwLineID = mxl.dwLineID;
	mxlc.dwControlType = MIXERCONTROL_CONTROLTYPE_VOLUME;
	mxlc.cControls = 1;
	mxlc.cbmxctrl = sizeof(MIXERCONTROL);
	mxlc.pamxctrl = &mxc;

	hr = ::mixerGetLineControls(reinterpret_cast<HMIXEROBJ>(m_hMixer),
							   &mxlc,
							   MIXER_OBJECTF_HMIXER |
							   MIXER_GETLINECONTROLSF_ONEBYTYPE);
	if (MMSYSERR_NOERROR != hr)
		return -1;

	// store dwControlID
	m_dMin = mxc.Bounds.dwMinimum;
	m_dMax = mxc.Bounds.dwMaximum;
	m_dCtlID = mxc.dwControlID;

	return 0;
}

INT CDGX_Mixer::GetMasterVolumeValue(DWORD* dwVal) const
{
	MMRESULT hr=0;

	if(!m_hMixer)
		return -1;


	MIXERCONTROLDETAILS_UNSIGNED mxcdVolume;
	MIXERCONTROLDETAILS mxcd;
	mxcd.cbStruct = sizeof(MIXERCONTROLDETAILS);
	mxcd.dwControlID = m_dCtlID;
	mxcd.cChannels = 1;
	mxcd.cMultipleItems = 0;
	mxcd.cbDetails = sizeof(MIXERCONTROLDETAILS_UNSIGNED);
	mxcd.paDetails = &mxcdVolume;

	hr = ::mixerGetControlDetails(reinterpret_cast<HMIXEROBJ>(m_hMixer),
								 &mxcd,
								 MIXER_OBJECTF_HMIXER |
								 MIXER_GETCONTROLDETAILSF_VALUE);
	if (MMSYSERR_NOERROR != hr)
		return -1;
	
	*dwVal = mxcdVolume.dwValue;

	return 0;
}

INT CDGX_Mixer::SetMasterVolumeValue(DWORD dwVal) const
{
	MMRESULT hr=0;

	if(!m_hMixer)
		return -1;

	MIXERCONTROLDETAILS_UNSIGNED mxcdVolume = { dwVal };
	MIXERCONTROLDETAILS mxcd;
	mxcd.cbStruct = sizeof(MIXERCONTROLDETAILS);
	mxcd.dwControlID = m_dCtlID;
	mxcd.cChannels = 1;
	mxcd.cMultipleItems = 0;
	mxcd.cbDetails = sizeof(MIXERCONTROLDETAILS_UNSIGNED);
	mxcd.paDetails = &mxcdVolume;

	hr = ::mixerSetControlDetails(reinterpret_cast<HMIXEROBJ>(m_hMixer),
								 &mxcd,
								 MIXER_OBJECTF_HMIXER |
								 MIXER_SETCONTROLDETAILSF_VALUE);
	if (MMSYSERR_NOERROR != hr)
		return -1;
	
	return 0;
}

#endif


