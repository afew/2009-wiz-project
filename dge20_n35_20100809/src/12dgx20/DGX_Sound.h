//	Copyright(C) Gamepark Holdings. All rights reserved.
//	Dogma-G Game Studios In-House Library DGE
//
// Interface for the IDGX_Sound class.
//
////////////////////////////////////////////////////////////////////////////////


#if defined(_WIN32) || defined(WIN32)
	#if _MSC_VER > 1000
	#pragma once
	#endif
#endif


#ifndef _DGX_Sound_H_
#define _DGX_Sound_H_

#include <DGE_Type.h>


enum EDGX_SOUND
{
	// TYPE
	DGX_SND_WAVE	= 0x01,
	DGX_SND_MIDI	= 0x02,
	DGX_SND_UNKNOWN	= 0xFFFFFFFF,

	// STATE
	DGX_SND_PLAY	= 0x03,
	DGX_SND_STOP	= 0x00,
	DGX_SND_RESET	= 0x01,
	DGX_SND_PAUSE	= 0x02,
	DGX_SND_INFINITE= 0xFFFFFFFF,	// Repeate Infinite
};


interface IDGX_Sound
{
	DGE_CLASS_DESTROYER(	IDGX_Sound	);

	virtual INT		Query(char* sCmd, void* pData)=0;
	virtual DWORD	GetType()=0;

	virtual void	Play()=0;
	virtual void	Stop()=0;
	virtual void	Reset()=0;
	virtual void	Pause()=0;
	virtual void	SetVolume(FLOAT fVol)=0;
	virtual FLOAT	GetVolume()=0;
	virtual void	SetRepeat(INT dRepeat= DGX_SND_INFINITE)=0;
	virtual INT		GetRepeat()=0;
	virtual INT		GetStatus()=0;
};


typedef IDGX_Sound*	PDGX_SOUND;



INT DGX_SoundDeviceOpen();		// Sound Device Open
INT	DGX_SoundDeviceClose();		// Sound Device Close


INT DGX_CreateSound(char* sCmd					// Create Sound Instance
				   , PDGX_SOUND* pData
				   , DGE_HANDLE p1				// Sound File Name
				   , DGE_HANDLE p2 = NULL		// User Data(Option)
				   , DGE_HANDLE p3 = NULL		// No Use
				   , DGE_HANDLE p4 = NULL		// No Use
					 );

INT DGX_DestroySound(PDGX_SOUND* pData);		// Sound Instance Release



DGE_INLINE void DGX_SoundPlay (PDGX_SOUND p){ if(p) p->Play (); }
DGE_INLINE void DGX_SoundStop (PDGX_SOUND p){ if(p) p->Stop (); }
DGE_INLINE void DGX_SoundReset(PDGX_SOUND p){ if(p) p->Reset(); }
DGE_INLINE void DGX_SoundPause(PDGX_SOUND p){ if(p) p->Pause(); }
DGE_INLINE void DGX_SoundRepeat(PDGX_SOUND p, INT dRepeat= DGX_SND_INFINITE){ if(p) p->SetRepeat(dRepeat); }


#endif


