// Implementation of the IDGX_Sound.
//
////////////////////////////////////////////////////////////////////////////////


#if defined(_WIN32) || defined(WIN32)
	#if _MSC_VER >= 1200
	#pragma warning(disable: 4996)
	#endif

	#include <windows.h>
	#include <conio.h>

	#include <AL_win/al.h>
	#include <AL_win/alc.h>
	#include <AL_win/alut.h>

#else
	#include <AL/al.h>
	#include <AL/alc.h>
	#include <AL/alut.h>

#endif


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <math.h>

#include <DGE_Type.h>
#include <DGE_Base.h>


#include "DGX_Sound.h"


class CDGX_Sound : public IDGX_Sound
{
protected:
	ALuint		m_uiSource;
	ALuint		m_uiBuffer;

	ALsizei		m_uiSize;
	ALsizei		m_uiFreq;
	ALenum		m_iFormat;
	ALboolean	m_bLoop;

	INT			m_nType;
	INT			m_nState;
	INT			m_nRepeat;
	FLOAT		m_fVol;

public:
	CDGX_Sound();
	virtual ~CDGX_Sound();

	virtual INT		Query(char* sCmd, void* pData);
	virtual DWORD	GetType();

	virtual void	Play();
	virtual void	Stop();
	virtual void	Reset();
	virtual void	Pause();
	virtual void	SetVolume(FLOAT fVol);
	virtual FLOAT	GetVolume();
	virtual void	SetRepeat(INT dRepeat= -1/*INFINITE*/);
	virtual INT		GetRepeat();
	virtual INT		GetStatus();

public:
	INT		Create(void* =0, void* =0, void* =0, void* =0);
	void	Destroy();
};




ALCcontext*	g_pAlCtx	= NULL;
ALCdevice*	g_pAlDev	= NULL;


INT DGX_SoundDeviceOpen()
{
	if(g_pAlDev && g_pAlCtx)
		return DGE_OK;



#if defined(_WIN32) || defined(WIN32)
	g_pAlDev = alcOpenDevice((ALCubyte*)"DirectSound3D");
#else
	g_pAlDev = alcOpenDevice(NULL);
#endif

	if(NULL == g_pAlDev)
	{
		printf("Err: %d, %s \t", __LINE__, __FILE__);
		printf("Sound () Failed\n");
		return DGE_ECANNOTACQUIRE_DEVICE;
	}

	g_pAlCtx=alcCreateContext(g_pAlDev, NULL);	// Create context(s)

	if(!g_pAlCtx)
	{
		printf("Err: %d, %s \t", __LINE__, __FILE__);
		printf("DGX_SoundDeviceOpen() Failed\n");
		return DGE_ECANNOTACQUIRE_DEVICE;
	}


	alcMakeContextCurrent(g_pAlCtx);			// Set active context

	alGetError();								// Clear Error Code

	return DGE_OK;
}


INT	DGX_SoundDeviceClose()
{
	if(NULL == g_pAlDev && NULL == g_pAlCtx)
		return DGE_OK;

	g_pAlCtx=alcGetCurrentContext();			// Get active context
	g_pAlDev=alcGetContextsDevice(g_pAlCtx);	// Get device for active context

	alcDestroyContext(g_pAlCtx);				// Release context(s)
	alcCloseDevice(g_pAlDev);					// Close device
	
	g_pAlCtx = NULL;
	g_pAlDev = NULL;


	return  DGE_OK;
}




CDGX_Sound::CDGX_Sound()
{
	m_uiSource	= 0;
	m_uiBuffer	= 0;

	m_uiSize	= 0;
	m_uiFreq	= 0;
	m_iFormat	= 0;
	m_bLoop		= 0;

	m_nType		= DGX_SND_UNKNOWN;
	m_nRepeat	= -1;

	m_fVol		= 1.F;
}


CDGX_Sound::~CDGX_Sound()
{
	Destroy();
}


void CDGX_Sound::Destroy()
{
	// Sound ∞¥√º «ÿ¡¶
	alSourceStop(m_uiSource);
	alDeleteSources(1, &m_uiSource);
	alDeleteBuffers(1, &m_uiBuffer);
}


INT CDGX_Sound::Create(void* p1, void* p2, void* p3, void* p4)
{
	INT		hr = 0;
	char*	sFile = (char*)p1;
	ALvoid*	pData = NULL;


	hr = DGX_SoundDeviceOpen();

	if(DGE_FAILED(hr))
		return hr;


	// Load Wave File
	alutLoadWAVFile(sFile, &m_iFormat, &pData, &m_uiSize, &m_uiFreq, &m_bLoop);
	hr = alGetError();
	if(AL_NO_ERROR != hr || NULL == pData)
	{
		printf("Err: %d, %s \t", __LINE__, __FILE__);
		printf("Load WAV File: %s\n", alGetString(hr));
	
		return DGE_ECANNOTACQUIRE_DEVICE;
	}

	// Generate Buffers
	alGenBuffers( 1, &m_uiBuffer );
	hr = alGetError();
	if(AL_NO_ERROR != hr)
	{
		printf("Err: %d, %s \t", __LINE__, __FILE__);
		printf("Generate Buffers: %s\n", alGetString(hr));
	
		return DGE_ECANNOTACQUIRE_DEVICE;
	}


	if(NULL == pData)
	{
		printf("Err: %d, %s \t", __LINE__, __FILE__);
		printf("Sound Format was not Supported.\n");
	
		return DGE_ECANNOTACQUIRE_DEVICE;
	}


//#if defined(_WIN32) || defined(WIN32)
//
//	char	sF[260]={0};
//	sprintf(sF, "%s.mcd", sFile);
//	FILE* fp = fopen(sF, "wb");
//	fwrite(pData, 1, m_uiSize, fp);
//	fclose(fp);
//
//#endif


	alBufferData(m_uiBuffer,m_iFormat,pData,m_uiSize,m_uiFreq);
	free(pData);
	hr = alGetError();
	if(AL_NO_ERROR != hr)
	{
		printf("Err: %d, %s \t", __LINE__, __FILE__);
		printf("Buffer Data: %s\n", alGetString(hr));
	
		return DGE_ECANNOTACQUIRE_DEVICE;
	}


	hr = alGetError();
	if(AL_NO_ERROR != hr)
	{
		printf("Err: %d, %s \t", __LINE__, __FILE__);
		printf("Buffer Data: %s\n", alGetString(hr));
	
		return DGE_ECANNOTACQUIRE_DEVICE;
	}


	// Generate a Source to playback the Buffer
	alGenSources( 1, &m_uiSource );
	hr = alGetError();

	alSourcei( m_uiSource, AL_BUFFER, m_uiBuffer );
	hr = alGetError();

	alSourcef(m_uiSource,AL_GAIN, m_fVol);			// Set volume
	hr = alGetError();

	alSourcei(m_uiSource,AL_LOOPING, AL_FALSE);		// Set looping
	hr = alGetError();

	m_nType		= DGX_SND_WAVE;

//	alSetError(AL_NO_ERROR);
//	hr = alGetError();

	return DGE_OK;
}


INT CDGX_Sound::Query(char* sCmd, void* pData)
{
	return DGE_EFAIL;
}

DWORD CDGX_Sound::GetType()
{
	return m_nType;
}


void CDGX_Sound::Play()
{
	m_nState = DGX_SND_PLAY;
	alSourcePlay( m_uiSource);
}

void CDGX_Sound::Stop()
{
	m_nState = DGX_SND_STOP;
	alSourceStop(m_uiSource);
}

void CDGX_Sound::Reset()
{
	m_nState = DGX_SND_RESET;
	alSourceRewind(m_uiSource);
}

void CDGX_Sound::Pause()
{
	m_nState = DGX_SND_PAUSE;
	alSourcePause(m_uiSource);
}

void CDGX_Sound::SetVolume(FLOAT fVol)
{
	if(fVol<0)
		return;

	m_fVol = fVol;
	alSourcef(m_uiSource,AL_GAIN, m_fVol);
}


FLOAT CDGX_Sound::GetVolume()
{
	return m_fVol;
}

void CDGX_Sound::SetRepeat(INT dRepeat)
{
	m_nRepeat = dRepeat;

	if(DGX_SND_INFINITE == m_nRepeat)
		alSourcei(m_uiSource, AL_LOOPING, AL_TRUE);		// Set looping
	else
		alSourcei(m_uiSource, AL_LOOPING, AL_FALSE);
}

INT CDGX_Sound::GetRepeat()
{
	return m_nRepeat;
}

INT CDGX_Sound::GetStatus()
{
	if(DGX_SND_PLAY == m_nState)
	{
		ALint st=0;
		alGetSourcei(m_uiSource, AL_SOURCE_STATE, &st);

		if(AL_STOPPED == st)
			m_nState = DGX_SND_STOP;
		else if(AL_PAUSED == st)
			m_nState = DGX_SND_PAUSE;
	}

	return m_nState;
}





INT DGX_CreateSound(char* sCmd
				   , PDGX_SOUND* pData
				   , DGE_HANDLE p1		// Sound File Name
				   , DGE_HANDLE p2		// User Data(Option)
				   , DGE_HANDLE p3		// No Use
				   , DGE_HANDLE p4		// No Use
					 )
{
	CDGX_Sound* pObj = NULL;
	*pData = NULL;

	pObj = new CDGX_Sound;
	if(DGE_FAILED(pObj->Create(p1, p2, p3, p4)))
	{
		delete pObj;
		return DGE_ECANNOTALLOCATED;
	}

	(*pData) = pObj;
	return DGE_OK;
}



INT DGX_DestroySound(PDGX_SOUND* pData)
{
	if(NULL == *pData)
		return DGE_OK;

	delete *pData;
	(*pData) = NULL;

	return DGE_OK;
}




