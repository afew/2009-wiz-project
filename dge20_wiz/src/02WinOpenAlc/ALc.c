/**
 * OpenAL cross platform audio library
 * Copyright (C) 1999-2000 by authors.
 * This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Library General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 *  License along with this library; if not, write to the
 *  Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 *  Boston, MA  02111-1307, USA.
 * Or go to http://www.gnu.org/copyleft/lgpl.html
 */

#pragma comment(lib, "winmm.lib")

#include <math.h>
#include <stdlib.h>
#include <memory.h>
#include "..\02WinOpenAlw\include\almain.h"
#include "AL_win\alc.h"
#include "AL_win\alu.h"
#include "..\02WinOpenAlw\include\alBuffer.h"

#include <stdio.h>
#include <assert.h>

#define SPEEDOFSOUNDMETRESPERSEC	(343.3f)

typedef struct ALCextension_struct
{
	ALubyte		*extName;
	ALvoid		*address;
} ALCextension;

typedef struct ALCfunction_struct
{
	ALubyte		*funcName;
	ALvoid		*address;
} ALCfunction;


static ALCextension alcExtensions[] = {	
	{ NULL,							(ALvoid *) NULL				} };

static ALCfunction  alcFunctions[] = {	
	{ NULL,							(ALvoid *) NULL				} };

// Error strings
static ALubyte alcNoError[] = "No Error";
static ALubyte alcErrInvalidDevice[] = "Invalid Device";
static ALubyte alcErrInvalidContext[] = "Invalid Context";
static ALubyte alcErrInvalidEnum[] = "Invalid Enum";
static ALubyte alcErrInvalidValue[] = "Invalud Value";

// Context strings
static ALubyte alcDefaultDeviceSpecifier[] = "DirectSound3D";
static ALubyte alcExtensionList[] = "";

static ALCint alcMajorVersion = 1;
static ALCint alcMinorVersion = 0;

static ALCcontext *Context=NULL;
static ALCuint ContextCount=0;
static ALCenum LastError=ALC_NO_ERROR;

static ALboolean bWaveShutdown = AL_FALSE;
static HANDLE g_hWaveHdrEvent = NULL;
static HANDLE g_hWaveThreadEvent = NULL;

static HANDLE g_hThread = NULL;
static ALuint g_ThreadID = 0;
ALint g_BuffersCommitted = 0;
CRITICAL_SECTION g_mutex;

// Multimedia Timer Callback function prototype
void CALLBACK TimerCallback(UINT uID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2);
DWORD WINAPI ThreadProc(LPVOID lpParameter);

// Update Context functions
void UpdateSource(ALCcontext *ALContext, ALsource *ALSource);
void UpdateListener(ALCcontext *ALContext);

// Call to update a particular Source
void ProcessSource(ALCcontext *ALContext, ALsource *ALSource);

ALuint		g_nTimerInterval;
ALuint		g_nTimerID;


ALCboolean alcIsContext(ALCcontext *context)
{
	ALCcontext *ALCContext;
	unsigned int i;
	
	ALCContext = Context;
	for (i = 0; i < ContextCount; i++)
	{
		if (ALCContext == context)
			return AL_TRUE;
		ALCContext = ALCContext->next;
	}

	return AL_FALSE;
}

ALCAPI ALCvoid ALCAPIENTRY alcSuspendContext(ALCcontext *context)
{
	EnterCriticalSection(&g_mutex);
}

ALCAPI ALCvoid ALCAPIENTRY alcProcessContext(ALCcontext *context)
{
	LeaveCriticalSection(&g_mutex);
}

ALCAPI ALCenum ALCAPIENTRY alcGetError(ALCdevice *device)
{
	ALCenum errorCode;

	errorCode=LastError;
	LastError=AL_NO_ERROR;
	return errorCode;
}

ALCAPI ALCvoid ALCAPIENTRY alcSetError(ALenum errorCode)
{
	LastError=errorCode;
}

ALCAPI ALCubyte* ALCAPIENTRY alcGetString(ALCdevice *device,ALCenum param)
{
	ALCcontext *Context;
	ALubyte *value = NULL;

	Context=alcGetCurrentContext();
	alcSuspendContext(Context);
	switch(param)
	{
		case ALC_NO_ERROR:
			value=alcNoError;
			break;
		case ALC_INVALID_ENUM:
			value=alcErrInvalidEnum;
			break;
		case ALC_INVALID_VALUE:
			value=alcErrInvalidValue;
			break;
		case ALC_INVALID_DEVICE:
			value=alcErrInvalidDevice;
			break;
		case ALC_INVALID_CONTEXT:
			value=alcErrInvalidContext;
			break;
		case ALC_DEFAULT_DEVICE_SPECIFIER:
			value = alcDefaultDeviceSpecifier;
		case ALC_DEVICE_SPECIFIER:
			if (!device)
				alcSetError(ALC_INVALID_DEVICE);
			else
				value = device->szDeviceName;
		case ALC_EXTENSIONS:
			value = alcExtensionList;
		default:
			alcSetError(ALC_INVALID_ENUM);
			break;
	}
	alcProcessContext(Context);
	return value;
}


/*
*/
ALCAPI ALCvoid ALCAPIENTRY alcGetIntegerv(ALCdevice *device,ALCenum param,ALCsizei size,ALCint *data)
{
	ALCcontext *Context;

	if ((size == 0) || (!data))
		return;

	Context=alcGetCurrentContext();
	alcSuspendContext(Context);
	switch (param)
	{
		case ALC_MAJOR_VERSION:
			if (size < sizeof(ALCint))
				alcSetError(ALC_INVALID_VALUE);
			else
				*data = alcMajorVersion;
			break;
		case ALC_MINOR_VERSION:
			if (size < sizeof(ALCint))
				alcSetError(ALC_INVALID_VALUE);
			else
				*data = alcMinorVersion;
			break;
		case ALC_ATTRIBUTES_SIZE:
			if (device)
			{
				if (size < sizeof(ALCint))
					alcSetError(ALC_INVALID_VALUE);
				else
					*data = strlen(alcExtensionList);
			}
			else
				alcSetError(ALC_INVALID_DEVICE);
			break;
		case ALC_ALL_ATTRIBUTES:
			if (device)
			{
				if (size < strlen(alcExtensionList))
					alcSetError(ALC_INVALID_VALUE);
				else
					strcpy((char*)data, alcExtensionList);
			}
			else
				alcSetError(ALC_INVALID_DEVICE);
			break;
		default:
			alcSetError(ALC_INVALID_ENUM);
			break;
	}
	alcProcessContext(Context);
}


static void CALLBACK alcWaveOutProc(HWAVEOUT hDevice,UINT uMsg,DWORD dwInstance,DWORD dwParam1,DWORD dwParam2)
{
	if (uMsg==WOM_DONE)
	{
		// Decrement number of buffers in use
		g_BuffersCommitted--;

		if (bWaveShutdown == AL_FALSE)
		{
			// Notify Wave Processor Thread that a Wave Header has returned
			PostThreadMessage(g_ThreadID,uMsg,0,dwParam1);
		}
		else
		{
			if (g_BuffersCommitted == 0)
			{
				// Signal Wave Buffers Returned event
				if (g_hWaveHdrEvent)
					SetEvent(g_hWaveHdrEvent);
				
				// Post 'Quit' Message to Wave Processor Thread
				PostThreadMessage(g_ThreadID,WM_QUIT,0,0);
			}
		}
	}
}

static void CALLBACK alcDirectSoundProc(UINT uID,UINT uReserved,DWORD dwUser,DWORD dwReserved1,DWORD dwReserved2)
{
	static DWORD OldWriteCursor=0;
	DWORD PlayCursor,WriteCursor;
	BYTE *WritePtr1,*WritePtr2;
	DWORD WriteCnt1,WriteCnt2;
	ALCcontext *ALContext;
	ALCdevice *ALDevice;
	DWORD BytesPlayed;
	HRESULT DSRes;

	ALDevice=(ALCdevice *)dwUser;
	IDirectSoundBuffer_GetCurrentPosition(ALDevice->DSsbuffer,&PlayCursor,&WriteCursor);
	if (!OldWriteCursor) OldWriteCursor=WriteCursor-PlayCursor;
	BytesPlayed=((((long)WriteCursor-(long)OldWriteCursor)<0)?((long)32768+(long)WriteCursor-(long)OldWriteCursor):((DWORD)WriteCursor-(DWORD)OldWriteCursor));
	DSRes=IDirectSoundBuffer_Lock(ALDevice->DSsbuffer,(OldWriteCursor+3528)&32767,BytesPlayed,&WritePtr1,&WriteCnt1,&WritePtr2,&WriteCnt2,0);
	if (DSRes==DSERR_BUFFERLOST)
	{
		IDirectSoundBuffer_Restore(ALDevice->DSsbuffer);
		IDirectSoundBuffer_Play(ALDevice->DSsbuffer,0,0,DSBPLAY_LOOPING);
		DSRes=IDirectSoundBuffer_Lock(ALDevice->DSsbuffer,(OldWriteCursor+3528)&32767,BytesPlayed,&WritePtr1,&WriteCnt1,&WritePtr2,&WriteCnt2,0);
	}
	if (DSRes==DS_OK)
	{
		ALContext=alcGetCurrentContext();
		if (ALContext)
		{
			alcSuspendContext(ALContext);
			if (WritePtr1)
				aluMixData(ALContext,WritePtr1,WriteCnt1,ALContext->Format);
			if (WritePtr2)
				aluMixData(ALContext,WritePtr2,WriteCnt2,ALContext->Format);
			alcProcessContext(ALContext);
		}
		else 
		{
			if (WritePtr1)
				memset(WritePtr1,0,WriteCnt1);
			if (WritePtr2)
				memset(WritePtr2,0,WriteCnt2);
		}
		IDirectSoundBuffer_Unlock(ALDevice->DSsbuffer,WritePtr1,WriteCnt1,WritePtr2,WriteCnt2);
	}
	OldWriteCursor=WriteCursor;
}

ALCAPI ALvoid ALCAPIENTRY alcInitContext(ALCcontext *context)
{
	TIMECAPS timeCaps;

	if (context)
	{
		//Lock context
		alcSuspendContext(context);
		//Initialise listener
		context->Listener.Gain=1.0f;
		context->Listener.Position[0]=0.0f;
		context->Listener.Position[1]=0.0f;
		context->Listener.Position[2]=0.0f;
		context->Listener.Velocity[0]=0.0f;
		context->Listener.Velocity[1]=0.0f;
		context->Listener.Velocity[2]=0.0f;
		context->Listener.Forward[0]=0.0f;
		context->Listener.Forward[1]=0.0f;
		context->Listener.Forward[2]=-1.0f;
		context->Listener.Up[0]=0.0f; 
		context->Listener.Up[1]=1.0f;
		context->Listener.Up[2]=0.0f;

		//Validate context
		context->LastError=AL_NO_ERROR;
		context->InUse=AL_FALSE;
		context->Valid=AL_TRUE;
		//Set output format
		context->Frequency=context->Device->Frequency;
		context->Channels=context->Device->Channels;
		context->Format=context->Device->Format;
		//Set globals
		context->DistanceModel=AL_INVERSE_DISTANCE_CLAMPED;
		context->DopplerFactor = 1.0f;
		context->DopplerVelocity = SPEEDOFSOUNDMETRESPERSEC;

		// Initialize update to set all the Listener parameters
		context->Listener.update1 = LPOSITION | LVELOCITY | LORIENTATION | LDOPPLERFACTOR | LDOPPLERVELOCITY | LDISTANCEMODEL;
		alcUpdateContext(context, ALLISTENER, 0);

		g_nTimerInterval = 100;
		g_nTimerID = 0;

		// Get the Timer Capabilities of the system
		timeGetDevCaps(&timeCaps, sizeof(TIMECAPS));

		// We want 100ms accuracy, if this is not possible, then just go with the best that we have
		if (timeCaps.wPeriodMin > g_nTimerInterval)
			g_nTimerInterval = timeCaps.wPeriodMin;

		// Begin Time Period
		timeBeginPeriod(g_nTimerInterval);
			
		//Unlock context
		alcProcessContext(context);
	}
}

ALCAPI ALCvoid ALCAPIENTRY alcExitContext(ALCcontext *context)
{
	unsigned int i;
	ALsource *ALSource;
	ALsource *ALTempSource;
#ifdef _DEBUG
	char szString[256];
#endif

	if (alcIsContext(context))
	{
		//Lock context
		alcSuspendContext(context);

		// Stop the multimedia timer
		if (g_nTimerID != 0)
			timeKillEvent(g_nTimerID);

		// End Timer Period
		timeEndPeriod(g_nTimerInterval);

#ifdef _DEBUG		
		if (context->SourceCount>0)
		{
			sprintf(szString,"ALwin32 : alcDestroyContext() %d Source(s) NOT deleted\n", context->SourceCount);
			OutputDebugString(szString);
		}
#endif

		// Free all the Sources still remaining
		ALSource = context->Source;
		for (i = 0; i < context->SourceCount; i++)
		{
			if (ALSource->uservalue1)
			{
				IDirectSoundBuffer_Stop((LPDIRECTSOUNDBUFFER)ALSource->uservalue1);
				if (ALSource->uservalue3)
				{
					IKsPropertySet_Release((LPKSPROPERTYSET)ALSource->uservalue3);
					ALSource->uservalue3 = NULL;
				}
				if (ALSource->uservalue2)
				{
					IDirectSound3DBuffer_Release((LPDIRECTSOUND3DBUFFER)ALSource->uservalue2);
					ALSource->uservalue2 = NULL;
				}
				IDirectSoundBuffer_Release((LPDIRECTSOUNDBUFFER)ALSource->uservalue1);
				ALSource->uservalue1=NULL;
			}

			ALTempSource = ALSource->next;
			memset(ALSource,0,sizeof(ALsource));
			free(ALSource);
			ALSource = ALTempSource;
		}

		//Invalidate context
		context->LastError=AL_NO_ERROR;
		context->InUse=AL_FALSE;
		context->Valid=AL_TRUE;

		//Unlock context
		alcProcessContext(context);
	}
	else
		alcSetError(ALC_INVALID_CONTEXT);
}


ALCAPI ALCcontext*ALCAPIENTRY alcCreateContext(ALCdevice *device,ALCint *attrList)
{
	ALCcontext *ALContext;

	if (!device)
	{
		alcSetError(ALC_INVALID_DEVICE);
		return NULL;
	}

	if (!Context)
    {
		Context=malloc(sizeof(ALCcontext));
		if (Context)
		{
			memset(Context,0,sizeof(ALCcontext));
			Context->Device=device;
			Context->Valid=AL_TRUE;
			alcInitContext(Context);
			ContextCount++;
		}
		ALContext=Context;
	}
	else
	{
		ALContext=Context;
		while (ALContext->next)
			ALContext=ALContext->next;
		if (ALContext)
		{
			ALContext->next=malloc(sizeof(ALCcontext));
			if (ALContext->next)
			{
				memset(ALContext->next,0,sizeof(ALCcontext));
				ALContext->next->previous=ALContext;
				ALContext->next->Device=device;
				ALContext->next->Valid=AL_TRUE;
				alcInitContext(ALContext);
				ContextCount++;
			}
			ALContext=ALContext->next;
		}
	}
	return ALContext;
}


ALCAPI ALCvoid ALCAPIENTRY alcDestroyContext(ALCcontext *context)
{
	ALCcontext *ALContext;

	if (alcIsContext(context))
	{
		// Lock context
		alcSuspendContext(context);
		ALContext=((ALCcontext *)context);
		alcExitContext(ALContext);
		if (ALContext->previous)
			ALContext->previous->next=ALContext->next;
		else
			Context=ALContext->next;
		if (ALContext->next)
			ALContext->next->previous=ALContext->previous;
		memset(ALContext,0,sizeof(ALCcontext));
		ContextCount--;
		// Unlock context
		alcProcessContext(context);
		// Free memory (MUST do this after ProcessContext)
		free(ALContext);
	}
	else
		alcSetError(ALC_INVALID_CONTEXT);
}


ALCAPI ALCcontext * ALCAPIENTRY alcGetCurrentContext(ALCvoid)
{
	ALCcontext *ALContext;

	ALContext=Context;
	while ((ALContext)&&(!ALContext->InUse))
		ALContext=ALContext->next;
	return ALContext;
}

ALCAPI ALCdevice* ALCAPIENTRY alcGetContextsDevice(ALCcontext *context)
{
	ALCdevice *ALDevice=NULL;
	ALCcontext *ALContext;

	ALContext=context;
	if (alcIsContext(ALContext))
	{
		alcSuspendContext(ALContext);
		ALDevice=ALContext->Device;
		alcProcessContext(ALContext);
	}
	else
		alcSetError(ALC_INVALID_CONTEXT);

	return ALDevice;
}

ALCAPI ALCboolean ALCAPIENTRY alcMakeContextCurrent(ALCcontext *context)
{
	ALCcontext *ALContext;
	
	// context must be a valid Context or NULL
	if ((!alcIsContext(context)) && (context != NULL))
	{
		alcSetError(ALC_INVALID_CONTEXT);
		return AL_FALSE;
	}

	if (ALContext=alcGetCurrentContext())
	{
		alcSuspendContext(ALContext);
		ALContext->InUse=AL_FALSE;
		alcProcessContext(ALContext);
	}

	if ((ALContext=context) && (ALContext->Device))
	{
		alcSuspendContext(ALContext);
		ALContext->InUse=AL_TRUE;
		alcProcessContext(ALContext);
	}
	
	return AL_TRUE;
}


void CALLBACK TimerCallback(UINT uID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2)
{
	ALuint i, loop;
	ALuint PlayCursor, WriteCursor, DataToLock;
	ALuint BufferID, DataSize;
	ALuint Part1Size, Part2Size;
	ALuint Data, BytesWritten, DataLeft;
	ALuint DataPlayed, DataCount;
	ALuint BytesPlayed, BufferSize;
	ALvoid *lpPart1, *lpPart2;
	ALsource *ALSource;
	ALuint BuffersToSkip;
	ALCcontext *ALContext;
	ALbufferlistitem *ALBufferListItem;

	ALContext = (ALCcontext*)dwUser;

	alcSuspendContext(ALContext);
	
	ALSource = ALContext->Source;

	// Process each playing source
	for (loop=0;loop < ALContext->SourceCount;loop++)
	{
		if (alIsSource((ALuint)ALSource) && (ALSource->state == AL_PLAYING))
		{
			// Valid playing source

			// Get position in DS Buffer
			IDirectSoundBuffer_GetCurrentPosition((LPDIRECTSOUNDBUFFER)ALSource->uservalue1, &PlayCursor, &WriteCursor);

			// Lock buffer from Old Write cursor to current Play cursor
			if (ALSource->OldWriteCursor > PlayCursor)
			{
				// DataToLock = (88200 - ALSource->OldWriteCursor) + PlayCursor;
				DataToLock = (44100 - ALSource->OldWriteCursor) + PlayCursor;
			}
			else
				DataToLock = PlayCursor - ALSource->OldWriteCursor;
			
			// Calculate amount of data played since last Timer event
			if (ALSource->OldPlayCursor > PlayCursor)
			{
				// ALSource->BytesPlayed += ((88200 - ALSource->OldPlayCursor) + PlayCursor);
				ALSource->BytesPlayed += ((44100 - ALSource->OldPlayCursor) + PlayCursor);
			}
			else
				ALSource->BytesPlayed += (PlayCursor - ALSource->OldPlayCursor);

			// Update current buffer variable

			// Find position in queue
			BytesPlayed = ALSource->BytesPlayed;
			if (BytesPlayed >= ALSource->TotalBufferDataSize)
			{
				if (ALSource->TotalBufferDataSize == 0)
					assert(ALSource->TotalBufferDataSize != 0);
				BytesPlayed = (BytesPlayed % ALSource->TotalBufferDataSize);
			}

			ALBufferListItem = ALSource->queue;
			DataSize = 0;
			while (ALBufferListItem != NULL)
			{
				if (ALBufferListItem->buffer)
					BufferSize = ((ALbuffer*)(ALBufferListItem->buffer))->size;
				else
					BufferSize = 0;
				DataSize += BufferSize;
				if (DataSize > BytesPlayed)
					break;
				else
					ALBufferListItem = ALBufferListItem->next;
			}

			// Record current BufferID
			BufferID = ALBufferListItem->buffer;

			// If we are not looping, decrement DataStillToPlay by the amount played since the last
			// Timer event, and check if any buffers in the queue have finished playing
			// Also check if the Source has now finished playing
			if (ALSource->param[AL_LOOPING-AL_CONE_INNER_ANGLE].data.i == AL_FALSE)
			{
				if (PlayCursor >= ALSource->OldPlayCursor)
					ALSource->DataStillToPlay -= (PlayCursor - ALSource->OldPlayCursor);
				else
				{
					//ALSource->DataStillToPlay -= ((88200 - ALSource->OldPlayCursor) + PlayCursor);
					ALSource->DataStillToPlay -= ((44100 - ALSource->OldPlayCursor) + PlayCursor);
				}

				if (ALSource->DataStillToPlay < 0)
					ALSource->DataStillToPlay = 0;

				// Check if any buffers in the queue have finished playing - if they have adjust
				// their state to PROCESSED

				DataPlayed = ALSource->TotalBufferDataSize - ALSource->DataStillToPlay;

				DataCount = 0;
				ALSource->BuffersProcessed = 0;
				ALBufferListItem = ALSource->queue;
				while (ALBufferListItem != NULL)
				{
					if (ALBufferListItem->buffer)
						DataSize = ((ALbuffer*)ALBufferListItem->buffer)->size;
					else
						DataSize = 0;

					DataCount += DataSize;
					if (DataCount <= DataPlayed)
					{
						// Buffer has been played
						ALBufferListItem->bufferstate = PROCESSED;
						ALSource->BuffersProcessed++;
						ALBufferListItem = ALBufferListItem->next;
					}
					else
						ALBufferListItem = NULL;
				}



				// Check if finished - if so stop source !
				if (ALSource->DataStillToPlay == 0)
				{
					IDirectSoundBuffer_Stop((LPDIRECTSOUNDBUFFER)ALSource->uservalue1);
					IDirectSoundBuffer_SetCurrentPosition((LPDIRECTSOUNDBUFFER)ALSource->uservalue1, 0);
					ALSource->state = AL_STOPPED;

					// Reset variables
					ALSource->BufferPosition = 0;
					ALSource->BytesPlayed = 0;
					ALSource->FinishedQueue = AL_FALSE;
					ALSource->OldPlayCursor = 0;
					ALSource->OldWriteCursor = 0;
					ALSource->SilenceAdded = 0;

					// Move on to next source
					continue;
				}


			}
			

			if (ALSource->FinishedQueue)
			{
				// Finished copying audio data into source, but data hasn't finished playing yet
				// Therefore copy silence into DS Buffer
				IDirectSoundBuffer_Lock((LPDIRECTSOUNDBUFFER)ALSource->uservalue1, ALSource->OldWriteCursor, DataToLock, &lpPart1, &Part1Size, &lpPart2, &Part2Size, 0);

				if (lpPart1)
				{
					memset(lpPart1, 0, Part1Size);
					ALSource->SilenceAdded += Part1Size;
					ALSource->OldWriteCursor += Part1Size;

					//if (ALSource->OldWriteCursor >= 88200)
					//	ALSource->OldWriteCursor -= 88200;

					if (ALSource->OldWriteCursor >= 44100)
						ALSource->OldWriteCursor -= 44100;
				}

				if (lpPart2)
				{
					memset(lpPart2, 0, Part2Size);
					ALSource->SilenceAdded += Part2Size;
					ALSource->OldWriteCursor += Part2Size;

					//if (ALSource->OldWriteCursor >= 88200)
					//	ALSource->OldWriteCursor -= 88200;

					if (ALSource->OldWriteCursor >= 44100)
						ALSource->OldWriteCursor -= 44100;
				}

				IDirectSoundBuffer_Unlock((LPDIRECTSOUNDBUFFER)ALSource->uservalue1, lpPart1, Part1Size, lpPart2, Part2Size);
				
				// Update Old Play Cursor
				ALSource->OldPlayCursor = PlayCursor;
			}
			else
			{
				IDirectSoundBuffer_Lock((LPDIRECTSOUNDBUFFER)ALSource->uservalue1, ALSource->OldWriteCursor, DataToLock, &lpPart1, &Part1Size, &lpPart2, &Part2Size, 0);

				if (lpPart1 != NULL)
				{
					// Find position in buffer queue
					BuffersToSkip = ALSource->BuffersAddedToDSBuffer;
					if (BuffersToSkip >= ALSource->BuffersInQueue)
						BuffersToSkip = BuffersToSkip % ALSource->BuffersInQueue;

					ALBufferListItem = ALSource->queue;
					for (i = 0; i < BuffersToSkip; i++)
					{
						ALBufferListItem = ALBufferListItem->next;
					}

					BytesWritten = 0;
					BufferID = ALBufferListItem->buffer;

					while (AL_TRUE)
					{
						// Copy audio data from Open AL Buffer(s) into DS buffer
									
						// Find out how much data is left in current Open AL Buffer
						if (BufferID)
						{
							Data = (ALint)(((ALbuffer*)BufferID)->data);
							DataSize = ((ALbuffer*)BufferID)->size;
						}
						else
						{
							Data = 0;
							DataSize = 0;
						}

						if (DataSize == 0)
							DataLeft = 0;
						else
							DataLeft = DataSize - ALSource->BufferPosition;

						if (DataLeft > (Part1Size - BytesWritten))
						{
							// Copy (Part1Size - BytesWritten) bytes to Direct Sound buffer
							memcpy((ALubyte*)lpPart1 + BytesWritten, (ALubyte*)Data + ALSource->BufferPosition, Part1Size - BytesWritten);
							ALSource->FinishedQueue = AL_FALSE;	// More data to follow ...
							ALSource->BufferPosition += (Part1Size - BytesWritten);		// Record position in buffer data
							BytesWritten += (Part1Size - BytesWritten);
							break;
						}
						else
						{
							// Not enough data in buffer to fill DS buffer so just copy as much data as possible
							if ((Data) && (DataLeft > 0))
								memcpy((ALubyte*)lpPart1 + BytesWritten, (ALubyte*)Data + ALSource->BufferPosition, DataLeft);

							BytesWritten += DataLeft;

							ALSource->BuffersAddedToDSBuffer++;

							ALSource->BufferPosition = 0;

							// Get next valid buffer ID
							ALBufferListItem = ALBufferListItem->next;
									
							if (ALBufferListItem == NULL)
							{
								// No more buffers - check for looping flag
								if (ALSource->param[AL_LOOPING-AL_CONE_INNER_ANGLE].data.i == AL_TRUE)
								{
									// Looping
									ALBufferListItem = ALSource->queue;
								}
								else
								{
									// Not looping and no more buffers
									ALSource->FinishedQueue = AL_TRUE;
									break;
								}
							}

							BufferID = ALBufferListItem->buffer;
						}
					}

					if (BytesWritten < Part1Size)
					{
						// Fill the rest of the buffer with silence
						memset((ALubyte*)lpPart1 + BytesWritten, 0, Part1Size - BytesWritten);
						ALSource->SilenceAdded += (Part1Size - BytesWritten);
					}

					ALSource->OldWriteCursor += Part1Size;
					//if (ALSource->OldWriteCursor >= 88200)
					//	ALSource->OldWriteCursor -= 88200;

					if (ALSource->OldWriteCursor >= 44100)
						ALSource->OldWriteCursor -= 44100;
				}


				if (lpPart2 != NULL)
				{
					if (ALSource->FinishedQueue)
					{
						// Fill Part 2 with silence
						memset(lpPart2, 0, Part2Size);
					}
					else
					{
						// Find position in buffer queue
						BuffersToSkip = ALSource->BuffersAddedToDSBuffer;
						if (BuffersToSkip >= ALSource->BuffersInQueue)
							BuffersToSkip = BuffersToSkip % ALSource->BuffersInQueue;

						ALBufferListItem = ALSource->queue;
						for (i = 0; i < BuffersToSkip; i++)
						{
							ALBufferListItem = ALBufferListItem->next;
						}

						BytesWritten = 0;
						BufferID = ALBufferListItem->buffer;

						while (AL_TRUE)
						{
							// Copy audio data from Open AL Buffer(s) into DS buffer
									
							// Find out how much data is left in current Open AL Buffer
							if (BufferID)
							{
								Data = (ALint)((ALbuffer*)BufferID)->data;
								DataSize = ((ALbuffer*)BufferID)->size;
							}
							else
							{
								Data = 0;
								DataSize = 0;
							}

							if (DataSize == 0)
								DataLeft = 0;
							else
								DataLeft = DataSize - ALSource->BufferPosition;
		
							if (DataLeft > (Part2Size - BytesWritten))
							{
								// Copy (Part1Size - BytesWritten) bytes to Direct Sound buffer
								memcpy((ALubyte*)lpPart2 + BytesWritten, (ALubyte*)Data + ALSource->BufferPosition, Part2Size - BytesWritten);
								ALSource->FinishedQueue = AL_FALSE;	// More data to follow ...
								ALSource->BufferPosition += (Part2Size - BytesWritten);		// Record position in buffer data
								BytesWritten += (Part2Size - BytesWritten);
								break;
							}
							else
							{
								// Not enough data in buffer to fill DS buffer so just copy as much data as possible
								if ((Data) && (DataLeft > 0))
									memcpy((ALubyte*)lpPart2 + BytesWritten, (ALubyte*)Data + ALSource->BufferPosition, DataLeft);

								BytesWritten += DataLeft;

								ALSource->BuffersAddedToDSBuffer++;

								ALSource->BufferPosition = 0;

								// Get next valid buffer ID
								ALBufferListItem = ALBufferListItem->next;
									
								if (ALBufferListItem == NULL)
								{
									// No more buffers - check for looping flag
									if (ALSource->param[AL_LOOPING-AL_CONE_INNER_ANGLE].data.i == AL_TRUE)
									{
										// Looping
										ALBufferListItem = ALSource->queue;
									}
									else
									{
										// Not looping and no more buffers
										ALSource->FinishedQueue = AL_TRUE;
										break;
									}
								}

								BufferID = ALBufferListItem->buffer;
							}
						}

						if (BytesWritten < Part2Size)
						{
							// Fill the rest of the buffer with silence
							memset((ALubyte*)lpPart2 + BytesWritten, 0, Part2Size - BytesWritten);
							ALSource->SilenceAdded += (Part2Size - BytesWritten);
						}

						ALSource->OldWriteCursor += Part2Size;
						//if (ALSource->OldWriteCursor >= 88200)
						//	ALSource->OldWriteCursor -= 88200;

						if (ALSource->OldWriteCursor >= 44100)
							ALSource->OldWriteCursor -= 44100;
					}
				}

				ALSource->OldPlayCursor = PlayCursor;

				IDirectSoundBuffer_Unlock((LPDIRECTSOUNDBUFFER)ALSource->uservalue1, lpPart1, Part1Size, lpPart2, Part2Size);
			} // end else

			// If we are still playing (we may have reached the end) then update current buffer
			if (ALSource->state == AL_PLAYING)
				ALSource->param[AL_BUFFER-AL_CONE_INNER_ANGLE].data.i = BufferID;
		}

		ALSource = ALSource->next;
	}

	alcProcessContext(ALContext);

	return;
}


ALCvoid alcUpdateContext(ALCcontext *context, ALuint type, ALuint name)
{
	ALCcontext *ALContext;
	ALsource *ALSource;
	
	ALContext = context;
	ALSource = (ALsource*)name;

	alcSuspendContext(ALContext);

	//Platform specific context updating
	if ((ALContext->Device->DShandle)&&(ALContext->Device->DS3dlistener))
	{
		// Check if we need to update a Source
		if ( (type == ALSOURCE) && (alIsSource(name)) && (ALSource->update1) )
		{
			// First check for any Open AL Updates (e.g Position, Velocity, Looping etc ...)
			if (ALSource->update1)
				UpdateSource(ALContext, ALSource);

			// If we need to actually start playing the sound, do it now
			if (ALSource->play)
			{	
				if (ALSource->uservalue1)
				{
					// Start playing the DS Streaming buffer (always looping)
					IDirectSoundBuffer_Play((LPDIRECTSOUNDBUFFER)ALSource->uservalue1,0,0,DSBPLAY_LOOPING);
					ALSource->play=AL_FALSE;
				}
			}
		}

		// Check for Listener related updates
		if ((type == ALLISTENER) && (ALContext->Device->DS3dlistener))
		{
			// Update any Open AL Listener Properties (e.g Position, Velocity, Orientation etc ...)
			if (ALContext->Listener.update1)
				UpdateListener(ALContext);
		}

	}

	alcProcessContext(ALContext);
}


/*
	ProcessSource(ALCcontext, ALsource)

	Obtain up-to-date status information for the given Source - e.g. Number of Buffers Processed,
	Current Buffer, and the current State.  If this function detects that the Source has finished playing
	it will stop the DS Buffer, and reset all the control variables.

	Note : This function must not update any of the global control variables of the Source (except when
	stopping the Source), otherwise the Timer callback function will perform incorrectly.

	Note 2 : Some problems seem to occur on some soundcard drivers if this function is called too
	often ( > 100 times a second).
*/
void ProcessSource(ALCcontext *ALContext, ALsource *ALSource)
{
	ALuint PlayCursor, WriteCursor;
	ALuint BufferID, DataSize;
	ALuint DataPlayed, DataCount;
	ALuint BytesPlayed, BufferSize;
	ALint  DataStillToPlay;
	ALbufferlistitem *ALBufferListItem;
	ALuint	curTime;
	static ALuint lastTime = 0;

	// Only update the state of the Source at the most 100 times a second !
	curTime = GetTickCount();
	if (curTime < (lastTime + 10))
		return;
	else
		lastTime = curTime;

	if (ALSource->state == AL_PLAYING)
	{
		// Get position in DS Buffer

		PlayCursor = ALSource->OldPlayCursor;
		if (IDirectSoundBuffer_GetCurrentPosition((LPDIRECTSOUNDBUFFER)ALSource->uservalue1, &PlayCursor, &WriteCursor) != DS_OK)
			return;
		
		// Calculate amount of data played since last update
		BytesPlayed = ALSource->BytesPlayed;

		if (ALSource->OldPlayCursor > PlayCursor)
		{
			//BytesPlayed += ((88200 - ALSource->OldPlayCursor) + PlayCursor);
			BytesPlayed += ((44100 - ALSource->OldPlayCursor) + PlayCursor);
		}
		else
			BytesPlayed += (PlayCursor - ALSource->OldPlayCursor);

		// Check for wrap-around (for looping Sources)
		if (BytesPlayed >= ALSource->TotalBufferDataSize)
		{
			if (ALSource->TotalBufferDataSize == 0)
				assert(ALSource->TotalBufferDataSize != 0);
			BytesPlayed = (BytesPlayed % ALSource->TotalBufferDataSize);
		}

		// Determine current Buffer
		DataSize = 0;
		ALBufferListItem = ALSource->queue;		
		while (ALBufferListItem != NULL)
		{
			if (ALBufferListItem->buffer)
				BufferSize = ((ALbuffer*)(ALBufferListItem->buffer))->size;
			else
				BufferSize = 0;
			DataSize += BufferSize;
			if (DataSize > BytesPlayed)
				break;
			else
				ALBufferListItem = ALBufferListItem->next;
		}

		// Record current BufferID
		BufferID = ALBufferListItem->buffer;

		// If we are not looping, decrement DataStillToPlay by the amount played since the last
		// Timer event, and check if any buffers in the queue have finished playing
		DataStillToPlay = ALSource->DataStillToPlay;
		if (ALSource->param[AL_LOOPING-AL_CONE_INNER_ANGLE].data.i == AL_FALSE)
		{
			if (PlayCursor >= ALSource->OldPlayCursor)
				DataStillToPlay -= (PlayCursor - ALSource->OldPlayCursor);
			else
			{
				//DataStillToPlay -= ((88200 - ALSource->OldPlayCursor) + PlayCursor);
				DataStillToPlay -= ((44100 - ALSource->OldPlayCursor) + PlayCursor);
			}

			if (DataStillToPlay < 0)
				DataStillToPlay = 0;

			// Check if any buffers in the queue have finished playing - if they have adjust
			// their state to PROCESSED

			DataPlayed = ALSource->TotalBufferDataSize - DataStillToPlay;

			DataCount = 0;
			ALSource->BuffersProcessed = 0;
			ALBufferListItem = ALSource->queue;
			while (ALBufferListItem != NULL)
			{
				if (ALBufferListItem->buffer)
					DataSize = ((ALbuffer*)ALBufferListItem->buffer)->size;
				else
					DataSize = 0;
				DataCount += DataSize;
				if (DataCount <= DataPlayed)
				{
					// Buffer has been played
					ALBufferListItem->bufferstate = PROCESSED;
					ALSource->BuffersProcessed++;
					ALBufferListItem = ALBufferListItem->next;
				}
				else
					ALBufferListItem = NULL;
			}

			// Check if finished - if so stop source !
			if (DataStillToPlay <= 0)
			{
				IDirectSoundBuffer_Stop((LPDIRECTSOUNDBUFFER)ALSource->uservalue1);
				IDirectSoundBuffer_SetCurrentPosition((LPDIRECTSOUNDBUFFER)ALSource->uservalue1, 0);
				ALSource->state = AL_STOPPED;

				// Reset variables
				ALSource->BufferPosition = 0;
				ALSource->BytesPlayed = 0;
				ALSource->DataStillToPlay = 0;
				ALSource->FinishedQueue = AL_FALSE;
				ALSource->OldPlayCursor = 0;
				ALSource->OldWriteCursor = 0;
				ALSource->SilenceAdded = 0;
			}
		}

		// If we are still playing (we may have reached the end) then update current buffer
		if (ALSource->state == AL_PLAYING)
			ALSource->param[AL_BUFFER-AL_CONE_INNER_ANGLE].data.i = BufferID;
	}

	return;
}


/*
	Update Source
*/
void UpdateSource(ALCcontext *ALContext, ALsource *ALSource)
{
	WAVEFORMATEX OutputType;
	DSBUFFERDESC DSBDescription;
	ALfloat Dir[3], Pos[3], Vel[3];
	ALuint	BytesWritten, DataLeft, BuffersToSkip, DataPlayed, DataCount, TotalDataSize;
	ALint	BufferSize, DataCommitted;
	ALint	Relative;
	ALuint	Data, Freq, State, Channels, outerAngle, innerAngle;
	ALfloat Pitch, outerGain, maxDist, minDist, Gain;
	ALvoid *lpPart1;
	ALuint	Part1Size, DataSize;
	ALuint PlayCursor, WriteCursor;
	ALuint BufferID, status, Loop, i;
	ALbufferlistitem *ALBufferListItem;
	ALbufferlistitem *ALBufferListTemp;
	ALint	volume;

	if (ALSource->update1 & SUPDATEBUFFERS)
	{
		// Force an update to recalculate the number of buffers processed, and the current buffer
		// (and the state of the Source)
		ProcessSource(ALContext, ALSource);

		ALSource->update1 &= ~SUPDATEBUFFERS;
		if (ALSource->update1 == 0)
				return;
	}
	
	// Check if the Source is being Destroyed
	if (ALSource->update1 == SDELETE)
	{				
		// Destroy source
		if (ALSource->uservalue1)
		{
			IDirectSoundBuffer_Stop((LPDIRECTSOUNDBUFFER)ALSource->uservalue1);
			if (ALSource->uservalue3)
			{
				IKsPropertySet_Release((LPKSPROPERTYSET)ALSource->uservalue3);
				ALSource->uservalue3 = NULL;
			}
			if (ALSource->uservalue2)
			{
				IDirectSound3DBuffer_Release((LPDIRECTSOUND3DBUFFER)ALSource->uservalue2);
				ALSource->uservalue2 = NULL;
			}
			IDirectSoundBuffer_Release((LPDIRECTSOUNDBUFFER)ALSource->uservalue1);
			ALSource->uservalue1=NULL;

			ALSource->update1 &= ~SDELETE;
			if (ALSource->update1 == 0)
				return;
		}
	}

	// Check if we need to generate a new Source
	if (ALSource->update1 & SGENERATESOURCE)
	{
		// Create a streaming DS buffer - 16bit mono 44.1KHz, 1 second in length
		memset(&DSBDescription,0,sizeof(DSBUFFERDESC));
		DSBDescription.dwSize=sizeof(DSBUFFERDESC);
		DSBDescription.dwFlags=DSBCAPS_CTRLVOLUME|DSBCAPS_CTRLFREQUENCY|DSBCAPS_CTRL3D|DSBCAPS_GLOBALFOCUS|
			DSBCAPS_GETCURRENTPOSITION2|ALContext->Device->CreationFlag;

		//DSBDescription.dwBufferBytes=88200;
		DSBDescription.dwBufferBytes=44100;

		DSBDescription.lpwfxFormat=&OutputType;
		memset(&OutputType,0,sizeof(WAVEFORMATEX));
		OutputType.wFormatTag=WAVE_FORMAT_PCM;
		OutputType.nChannels=1;
		OutputType.wBitsPerSample=16;
		OutputType.nBlockAlign=2;

		//OutputType.nSamplesPerSec=44100;
		//OutputType.nAvgBytesPerSec=88200;

		OutputType.nSamplesPerSec=22050;
		OutputType.nAvgBytesPerSec=44100;


		OutputType.cbSize=0;
		if (IDirectSound_CreateSoundBuffer(ALContext->Device->DShandle,&DSBDescription,&(LPDIRECTSOUNDBUFFER)ALSource->uservalue1,NULL)==DS_OK)
		{
			IDirectSoundBuffer_SetCurrentPosition((LPDIRECTSOUNDBUFFER)ALSource->uservalue1,0);

			// Set Volume
			Gain = ALSource->param[AL_GAIN-AL_CONE_INNER_ANGLE].data.f;
			Gain = (Gain * ALContext->Listener.Gain);
			volume = LinearGainToDB(Gain);						
			IDirectSoundBuffer_SetVolume((LPDIRECTSOUNDBUFFER)ALSource->uservalue1, volume);

			// Get 3D Interface
			if (IDirectSoundBuffer_QueryInterface((LPDIRECTSOUNDBUFFER)ALSource->uservalue1,&IID_IDirectSound3DBuffer,(LPUNKNOWN *)&ALSource->uservalue2)==DS_OK)
			{
				// Get Property Set Interface
				IDirectSound3DBuffer_QueryInterface((LPDIRECTSOUND3DBUFFER)ALSource->uservalue2,&IID_IKsPropertySet,(LPUNKNOWN *)&ALSource->uservalue3);
			}
		}

		ALSource->update1 &= ~SGENERATESOURCE;
		if (ALSource->update1 == 0)
				return;
	}

	// Check if we need to Stop, Start, Pause, or Resume a Source
	if (ALSource->update1 & STATE)
	{
		State = ALSource->state;

		switch (State)
		{
			case AL_INITIAL:
				if (ALSource->uservalue1)
					IDirectSoundBuffer_SetCurrentPosition((LPDIRECTSOUNDBUFFER)ALSource->uservalue1,0);
				break;
			case AL_PLAYING:
				if (ALSource->play)
				{							
					// Check if this Source is already playing
					IDirectSoundBuffer_GetStatus((LPDIRECTSOUNDBUFFER)ALSource->uservalue1,&status);
					
					// If already playing, stop source, set position to zero, mark all items in 
					// queue as PENDING ready to start playback
					if (status & DSBSTATUS_PLAYING)
					{
						IDirectSoundBuffer_Stop((LPDIRECTSOUNDBUFFER)ALSource->uservalue1);
						IDirectSoundBuffer_SetCurrentPosition((LPDIRECTSOUNDBUFFER)ALSource->uservalue1,0);
						
						// Mark all buffers in the queue as PENDING
						ALBufferListItem = ALSource->queue;
						while (ALBufferListItem != NULL)
						{
							ALBufferListItem->bufferstate = PENDING;
							ALBufferListItem = ALBufferListItem->next;
						}

						ALSource->BuffersProcessed = 0;
						ALSource->BuffersAddedToDSBuffer = 0;
						ALSource->BufferPosition = 0;
						ALSource->BytesPlayed = 0;
						ALSource->DataStillToPlay = 0;
						ALSource->FinishedQueue = AL_FALSE;
						ALSource->OldPlayCursor = 0;
						ALSource->OldWriteCursor = 0;
					}

					// Check that we have some data to play
					if (ALSource->BuffersInQueue == 0)
					{
						ALSource->play = AL_FALSE;

						// temp
						ALSource->state = AL_STOPPED;

						break;
					}

					if (ALSource->TotalBufferDataSize == 0)
					{
						// Nothing to play (the buffers must be of length 0) - mark them as processed
				
						// Mark all buffers in queue as PROCESSED
						ALSource->BuffersProcessed = ALSource->BuffersInQueue;

						ALBufferListItem= ALSource->queue;
						while (ALBufferListItem != NULL)
						{
							ALBufferListItem->bufferstate = PROCESSED;
							ALBufferListItem = ALBufferListItem->next;
						}

						// No need to start playing !
						ALSource->play = AL_FALSE;

						// temp
						ALSource->state = AL_STOPPED;

						break;
					}

					// If looping has been enabled, make sure that all buffers are PENDING
					Loop = ALSource->param[AL_LOOPING-AL_CONE_INNER_ANGLE].data.i;

					if (Loop == AL_TRUE)
					{
						ALBufferListItem = ALSource->queue;
						while (ALBufferListItem != NULL)
						{
							ALBufferListItem->bufferstate = PENDING;
							ALBufferListItem = ALBufferListItem->next;
						}
						ALSource->BuffersProcessed = 0;
					}

					// Find position in buffer queue
					BuffersToSkip = ALSource->BuffersAddedToDSBuffer;
					if (BuffersToSkip > ALSource->BuffersInQueue)
					{
						BuffersToSkip = BuffersToSkip % ALSource->BuffersInQueue;
					}

					ALBufferListItem = ALSource->queue;
					for (i = 0; i < BuffersToSkip; i++)
					{
						ALBufferListItem = ALBufferListItem->next;
					}

					// Mark any buffers at the start of the list as processed if they have bufferID == 0, or
					// if they have length 0 bytes
					while (ALBufferListItem)
					{
						if (ALBufferListItem->buffer)
							BufferSize = ((ALbuffer*)ALBufferListItem->buffer)->size;
						else
							BufferSize = 0;
						if (BufferSize == 0)
						{
							// Skip over this buffer (and mark as processed)
							ALBufferListItem->bufferstate = PROCESSED;
							ALSource->BuffersProcessed++;
							ALBufferListItem = ALBufferListItem->next;
							ALSource->BuffersAddedToDSBuffer++;
						}
						else
						{
							// Found a valid buffer
							break;
						}
					}

					// Check if we still have something to play !
					if (ALBufferListItem == NULL)
					{
						// No buffers to play - remove play flag
						ALSource->play = AL_FALSE;

						// temp
						ALSource->state = AL_STOPPED;

						break;
					}

					// Start multimedia timer (if not already in progress)
					if (g_nTimerID == 0)
						g_nTimerID = timeSetEvent(g_nTimerInterval, 0, &TimerCallback, (DWORD)ALContext, TIME_CALLBACK_FUNCTION | TIME_PERIODIC);

					// Update current buffer variable
					BufferID = ALBufferListItem->buffer;
					ALSource->param[AL_BUFFER-AL_CONE_INNER_ANGLE].data.i = BufferID;

					// Update variables
					ALSource->BytesPlayed = 0;
					ALSource->OldWriteCursor = 0;
					ALSource->OldPlayCursor = 0;

					// Calculate how much data still to play
					DataSize = ((ALbuffer*)BufferID)->size;
					ALSource->DataStillToPlay = DataSize - ALSource->BufferPosition;

					ALBufferListTemp = ALBufferListItem;

					while (ALBufferListTemp->next != NULL)
					{
						if (ALBufferListTemp->next->buffer)
							DataSize = ((ALbuffer*)ALBufferListTemp->next->buffer)->size;
						else
							DataSize = 0;
						ALSource->DataStillToPlay += DataSize;
						ALBufferListTemp = ALBufferListTemp->next;
					}
					
					// Check if the buffer is stereo
					Channels = (((((ALbuffer*)BufferID)->format==AL_FORMAT_MONO8)||(((ALbuffer*)BufferID)->format==AL_FORMAT_MONO16))?1:2);
					
					if ((Channels == 2) && (ALSource->SourceType == SOURCE3D))
					{
						// Playing a stereo buffer

						// Need to destroy the DS Streaming Mono 3D Buffer and create a Stereo 2D buffer
						if (ALSource->uservalue3)
						{
							IKsPropertySet_Release((LPKSPROPERTYSET)ALSource->uservalue3);
							ALSource->uservalue3 = NULL;
						}
						if (ALSource->uservalue2)
						{
							IDirectSound3DBuffer_Release((LPDIRECTSOUND3DBUFFER)ALSource->uservalue2);
							ALSource->uservalue2 = NULL;
						}
						IDirectSoundBuffer_Release((LPDIRECTSOUNDBUFFER)ALSource->uservalue1);
						ALSource->uservalue1=NULL;

						// Set Caps
						memset(&DSBDescription,0,sizeof(DSBUFFERDESC));
						DSBDescription.dwSize=sizeof(DSBUFFERDESC);
						DSBDescription.dwFlags=DSBCAPS_CTRLVOLUME|DSBCAPS_CTRLFREQUENCY|DSBCAPS_GLOBALFOCUS|
							DSBCAPS_GETCURRENTPOSITION2|ALContext->Device->CreationFlag;

						//DSBDescription.dwBufferBytes=88200;
						DSBDescription.dwBufferBytes=44100;

						DSBDescription.lpwfxFormat=&OutputType;
						memset(&OutputType,0,sizeof(WAVEFORMATEX));
						OutputType.wFormatTag=WAVE_FORMAT_PCM;
						OutputType.nChannels=2;
						OutputType.wBitsPerSample=16;
						OutputType.nBlockAlign=4;

						//OutputType.nSamplesPerSec=44100;
						//OutputType.nAvgBytesPerSec=176400;
						
						OutputType.nSamplesPerSec=22050;
						OutputType.nAvgBytesPerSec=88200;


						OutputType.cbSize=0;
						if (IDirectSound_CreateSoundBuffer(ALContext->Device->DShandle,&DSBDescription,&(LPDIRECTSOUNDBUFFER)ALSource->uservalue1,NULL)==DS_OK)
						{
							IDirectSoundBuffer_SetCurrentPosition((LPDIRECTSOUNDBUFFER)ALSource->uservalue1,0);
						}

						// Set correct volume for new DS Buffer
						if (ALSource->uservalue1)
						{
							Gain = ALSource->param[AL_GAIN-AL_CONE_INNER_ANGLE].data.f;
							Gain = (Gain * ALContext->Listener.Gain);
							volume = LinearGainToDB(Gain);
							IDirectSoundBuffer_SetVolume((LPDIRECTSOUNDBUFFER)ALSource->uservalue1, volume);
						}

						ALSource->SourceType = SOURCE2D;
					}
					else if ((Channels == 1) && (ALSource->SourceType == SOURCE2D))
					{
						// Playing a (3D) Mono buffer

						// Need to destroy the stereo streaming buffer and create a 3D mono one instead
						if (ALSource->uservalue1)
						{
							IDirectSoundBuffer_Release((LPDIRECTSOUNDBUFFER)ALSource->uservalue1);
							ALSource->uservalue1=NULL;
						}

						// Set Caps
						memset(&DSBDescription,0,sizeof(DSBUFFERDESC));
						DSBDescription.dwSize=sizeof(DSBUFFERDESC);
						DSBDescription.dwFlags=DSBCAPS_CTRLVOLUME|DSBCAPS_CTRLFREQUENCY|DSBCAPS_CTRL3D|DSBCAPS_GLOBALFOCUS|
							DSBCAPS_GETCURRENTPOSITION2|ALContext->Device->CreationFlag;

						//DSBDescription.dwBufferBytes=88200;
						DSBDescription.dwBufferBytes=44100;

						DSBDescription.lpwfxFormat=&OutputType;
						memset(&OutputType,0,sizeof(WAVEFORMATEX));
						OutputType.wFormatTag=WAVE_FORMAT_PCM;
						OutputType.nChannels=1;
						OutputType.wBitsPerSample=16;
						OutputType.nBlockAlign=2;

						//OutputType.nSamplesPerSec=44100;
						//OutputType.nAvgBytesPerSec=88200;

						OutputType.nSamplesPerSec=22050;
						OutputType.nAvgBytesPerSec=44100;

						OutputType.cbSize=0;

						if (IDirectSound_CreateSoundBuffer(ALContext->Device->DShandle,&DSBDescription,&(LPDIRECTSOUNDBUFFER)ALSource->uservalue1,NULL)==DS_OK)
						{
							IDirectSoundBuffer_SetCurrentPosition((LPDIRECTSOUNDBUFFER)ALSource->uservalue1,0);

							// Get 3D Interface
							if (IDirectSoundBuffer_QueryInterface((LPDIRECTSOUNDBUFFER)ALSource->uservalue1,&IID_IDirectSound3DBuffer,(LPUNKNOWN *)&ALSource->uservalue2)==DS_OK)
							{
								// Get Property Set Interface
								IDirectSound3DBuffer_QueryInterface((LPDIRECTSOUND3DBUFFER)ALSource->uservalue2,&IID_IKsPropertySet,(LPUNKNOWN *)&ALSource->uservalue3);
							}
						}


						// Set correct volume for new DS Buffer
						if (ALSource->uservalue1)
						{
							Gain = ALSource->param[AL_GAIN-AL_CONE_INNER_ANGLE].data.f;
							Gain = (Gain * ALContext->Listener.Gain);
							volume = LinearGainToDB(Gain);
							IDirectSoundBuffer_SetVolume((LPDIRECTSOUNDBUFFER)ALSource->uservalue1, volume);
						}

						ALSource->SourceType = SOURCE3D;
					}

					// Set Direct Sound buffer to frequency of current Open AL buffer multiplied by desired Pitch
					Freq = ((ALbuffer*)BufferID)->frequency;
					Pitch = ALSource->param[AL_PITCH-AL_CONE_INNER_ANGLE].data.f;

					IDirectSoundBuffer_SetFrequency((LPDIRECTSOUNDBUFFER)ALSource->uservalue1, (long)(Freq*Pitch));

					// Lock the whole DS buffer
					IDirectSoundBuffer_Lock((LPDIRECTSOUNDBUFFER)ALSource->uservalue1,0,0,&lpPart1,&Part1Size,NULL,NULL,DSBLOCK_ENTIREBUFFER);
						
					BytesWritten = 0;

					while (AL_TRUE)
					{
						// Copy audio data from Open AL Buffer into DS buffer
							
						// Find out how much data is left in current Open AL Buffer
						Data = (ALint)(((ALbuffer*)BufferID)->data);
						DataSize = ((ALbuffer*)BufferID)->size;
							
						if (DataSize == 0)
							DataLeft = 0;
						else
							DataLeft = DataSize - ALSource->BufferPosition;

						//if (DataLeft > (88200 - BytesWritten))
						//{
						//	// Copy (88200 - BytesWritten) bytes to Direct Sound buffer
						//	memcpy((ALubyte*)lpPart1 + BytesWritten, (ALubyte*)Data + ALSource->BufferPosition, 88200 - BytesWritten);
						//	ALSource->FinishedQueue = AL_FALSE;	// More data to follow ...
						//	ALSource->BufferPosition += (88200 - BytesWritten);		// Record position in buffer data
						//	BytesWritten += (88200 - BytesWritten);
						//	break;
						//}

						if (DataLeft > (44100 - BytesWritten))
						{
							memcpy((ALubyte*)lpPart1 + BytesWritten, (ALubyte*)Data + ALSource->BufferPosition, 44100 - BytesWritten);
							ALSource->FinishedQueue = AL_FALSE;	// More data to follow ...
							ALSource->BufferPosition += (44100 - BytesWritten);		// Record position in buffer data
							BytesWritten += (44100 - BytesWritten);
							break;
						}
						else
						{
							// Not enough data in buffer to fill DS buffer so just copy as much data as possible
							memcpy((ALubyte*)lpPart1 + BytesWritten, (ALubyte*)Data + ALSource->BufferPosition, DataLeft);

							BytesWritten += DataLeft;

							ALSource->BuffersAddedToDSBuffer++;

							ALSource->BufferPosition = 0;

							// Get next valid buffer ID
							ALBufferListItem = ALBufferListItem->next;
								
							if (ALBufferListItem == NULL)
							{
								// No more buffers - check for looping flag
								if (ALSource->param[AL_LOOPING-AL_CONE_INNER_ANGLE].data.i == AL_TRUE)
								{
									// Looping
									ALBufferListItem = ALSource->queue;
								}
								else
								{
									// Not looping and no more buffers
									break;
								}
							}

							BufferID = ALBufferListItem->buffer;
						}
					}

					//if (BytesWritten < 88200)
					//{
					//	// Fill the rest of the buffer with silence
					//	memset((ALubyte*)lpPart1 + BytesWritten, 0, 88200 - BytesWritten);
					//	ALSource->SilenceAdded = 88200 - BytesWritten;
					//	ALSource->FinishedQueue = AL_TRUE;		// Set this to true to indicate no more data needs to be copied into buffer
					//}
					
					if (BytesWritten < 44100)
					{
						// Fill the rest of the buffer with silence
						memset((ALubyte*)lpPart1 + BytesWritten, 0, 44100 - BytesWritten);
						ALSource->SilenceAdded = 44100 - BytesWritten;
						ALSource->FinishedQueue = AL_TRUE;		// Set this to true to indicate no more data needs to be copied into buffer
					}

					IDirectSoundBuffer_Unlock((LPDIRECTSOUNDBUFFER)ALSource->uservalue1,lpPart1,Part1Size,NULL,0);						
				}
				break;

			case AL_PAUSED:
				if (ALSource->uservalue1)
				{
					IDirectSoundBuffer_Stop((LPDIRECTSOUNDBUFFER)ALSource->uservalue1);
					ALSource->paused = AL_TRUE;
				}
				break;
			case AL_STOPPED:
				if (ALSource->uservalue1)
				{
					IDirectSoundBuffer_Stop((LPDIRECTSOUNDBUFFER)ALSource->uservalue1);
					IDirectSoundBuffer_SetCurrentPosition((LPDIRECTSOUNDBUFFER)ALSource->uservalue1,0);
					// Re-set variables
					ALSource->BufferPosition = 0;
					ALSource->BytesPlayed = 0;
					ALSource->DataStillToPlay = 0;
					ALSource->FinishedQueue = AL_FALSE;
					ALSource->OldPlayCursor = 0;
					ALSource->OldWriteCursor = 0;
					ALSource->SilenceAdded = 0;
				}

				// Mark all buffers in queue as PROCESSED
				ALSource->BuffersProcessed = ALSource->BuffersInQueue;

				ALBufferListItem= ALSource->queue;
				while (ALBufferListItem != NULL)
				{
					ALBufferListItem->bufferstate = PROCESSED;
					ALBufferListItem = ALBufferListItem->next;
				}

				break;
		}

		// End of STATE update
		ALSource->update1 &= ~STATE;
		if (ALSource->update1 == 0)
				return;
	}


	// Check if we need to update the 3D Position of the Source
	if (ALSource->update1 & POSITION)
	{
		if (ALSource->uservalue2)
		{
			Pos[0] = ALSource->param[AL_POSITION-AL_CONE_INNER_ANGLE].data.fv3[0];
			Pos[1] = ALSource->param[AL_POSITION-AL_CONE_INNER_ANGLE].data.fv3[1];
			Pos[2] = -ALSource->param[AL_POSITION-AL_CONE_INNER_ANGLE].data.fv3[2];
			IDirectSound3DBuffer_SetPosition((LPDIRECTSOUND3DBUFFER)ALSource->uservalue2,Pos[0],Pos[1],Pos[2],DS3D_IMMEDIATE);
			ALSource->update1 &= ~POSITION;
			if (ALSource->update1 == 0)
				return;
		}
	}


	// Check if we need to adjust the velocity of the Source
	if (ALSource->update1 & VELOCITY)
	{
		if (ALSource->uservalue2)
		{
			Vel[0] = ALSource->param[AL_VELOCITY-AL_CONE_INNER_ANGLE].data.fv3[0];
			Vel[1] = ALSource->param[AL_VELOCITY-AL_CONE_INNER_ANGLE].data.fv3[1];
			Vel[2] = -ALSource->param[AL_VELOCITY-AL_CONE_INNER_ANGLE].data.fv3[2];
			IDirectSound3DBuffer_SetVelocity((LPDIRECTSOUND3DBUFFER)ALSource->uservalue2,Vel[0],Vel[1],Vel[2],DS3D_IMMEDIATE);
			ALSource->update1 &= ~VELOCITY;
			if (ALSource->update1 == 0)
				return;
		}
	}


	// Check if we need to adjust the Orientation of the Source
	if (ALSource->update1 & ORIENTATION)
	{
		if (ALSource->uservalue2)
		{
			Dir[0] = ALSource->param[AL_DIRECTION-AL_CONE_INNER_ANGLE].data.fv3[0];
			Dir[1] = ALSource->param[AL_DIRECTION-AL_CONE_INNER_ANGLE].data.fv3[1];
			Dir[2] = -ALSource->param[AL_DIRECTION-AL_CONE_INNER_ANGLE].data.fv3[2];
			IDirectSound3DBuffer_SetConeOrientation((LPDIRECTSOUND3DBUFFER)ALSource->uservalue2,Dir[0],Dir[1],Dir[2],DS3D_IMMEDIATE);
			ALSource->update1 &= ~ORIENTATION;
			if (ALSource->update1 == 0)
				return;
		}
	}

	
	// Check if any Buffers have been added to this Source's queue
	if (ALSource->update1 & SQUEUE)
	{
		if ((ALSource->uservalue1) && (ALSource->state == AL_PLAYING))
		{
			// Some buffer(s) have been added to the queue

			// If silence has been added, then we need to overwrite the silence with new audio
			// data from the buffers in the queue
			if (ALSource->SilenceAdded > 0)
			{
				// Find position of end of valid data
				if (ALSource->OldWriteCursor < ALSource->SilenceAdded)
				{
					//ALSource->OldWriteCursor += 88200;
					ALSource->OldWriteCursor += 44100;
				}

				// Set new Write position to the end of the valid data
				ALSource->OldWriteCursor -= ALSource->SilenceAdded;

				// Read position from next buffer should be set to 0
				ALSource->BufferPosition = 0;

				// We have overwritten the silent data, so reset variable
				ALSource->SilenceAdded = 0;

				// Make sure that the we haven't finished processing the queue !
				ALSource->FinishedQueue = AL_FALSE;
			}
			// Update DataStillToPlay
			ALSource->DataStillToPlay += ALSource->SizeOfBufferDataAddedToQueue;
		}
		ALSource->TotalBufferDataSize += ALSource->SizeOfBufferDataAddedToQueue;
		ALSource->SizeOfBufferDataAddedToQueue = 0;
		ALSource->NumBuffersAddedToQueue = 0;
		ALSource->update1 &= ~SQUEUE;
		if (ALSource->update1 == 0)
				return;
	}

	// Check if any Buffers have been removed from this Source's Queue
	if (ALSource->update1 & SUNQUEUE)
	{
		// Some number of buffers have been removed from the queue

		// We need to update some variables to correctly reflect the new queue

		// The number of BuffersAddedToDSBuffers must be decreased by the number of buffers
		// removed from the queue (or else the Timer function will think we are further through
		// the list than we are)

		// The amount of DataPlayed must be decreased by the total size of the data in the buffers
		// removed from the queue (or the amount of data still to play (TotalDataSize - DataPlayed)
		// will be incorrect)
		if ((ALSource->uservalue1) && (ALSource->state == AL_PLAYING))
		{
			ALSource->BytesPlayed -= ALSource->SizeOfBufferDataRemovedFromQueue;
		}
		ALSource->TotalBufferDataSize -= ALSource->SizeOfBufferDataRemovedFromQueue;
		ALSource->NumBuffersRemovedFromQueue = 0;
		ALSource->SizeOfBufferDataRemovedFromQueue = 0;

		// If we're not playing then reset current buffer (it may have changed)
		if (ALSource->state != AL_PLAYING)
		{
			if (ALSource->queue)
				BufferID = ALSource->queue->buffer;
			else
				BufferID = 0;

			ALSource->param[AL_BUFFER-AL_CONE_INNER_ANGLE].data.i = BufferID;
		}

		ALSource->update1 &= ~SUNQUEUE;
		if (ALSource->update1 == 0)
				return;
	}

	// Check if we need to adjust the volume of the Source
	if (ALSource->update1 & VOLUME)
	{
		if (ALSource->uservalue1)
		{
			Gain = ALSource->param[AL_GAIN-AL_CONE_INNER_ANGLE].data.f;
			Gain = (Gain * ALContext->Listener.Gain);
			volume = LinearGainToDB(Gain);
			IDirectSoundBuffer_SetVolume((LPDIRECTSOUNDBUFFER)ALSource->uservalue1, volume);
			ALSource->update1 &= ~VOLUME;
			if (ALSource->update1 == 0)
				return;
		}
	}


	// Check if we need to adjust the frequency of the Source
	if (ALSource->update1 & FREQUENCY)
	{
		if (ALSource->uservalue1)
		{
			BufferID = ALSource->param[AL_BUFFER-AL_CONE_INNER_ANGLE].data.i;
			if (BufferID == 0)
				Freq = 44100;
			else
				Freq = ((ALbuffer*)BufferID)->frequency;

			Pitch = ALSource->param[AL_PITCH-AL_CONE_INNER_ANGLE].data.f;
			IDirectSoundBuffer_SetFrequency((LPDIRECTSOUNDBUFFER)ALSource->uservalue1,(long)(Freq*Pitch));
			ALSource->update1 &= ~FREQUENCY;
			if (ALSource->update1 == 0)
				return;
		}
	}


	// Check if we need to adjust the Min Distance of the Source
	if (ALSource->update1 & MINDIST)
	{
		if (ALSource->uservalue2)
		{
			minDist = ALSource->param[AL_REFERENCE_DISTANCE-AL_CONE_INNER_ANGLE].data.f;
			IDirectSound3DBuffer_SetMinDistance((LPDIRECTSOUND3DBUFFER)ALSource->uservalue2,minDist,DS3D_IMMEDIATE);
			ALSource->update1 &= ~MINDIST;
			if (ALSource->update1 == 0)
				return;
		}
	}


	// Check if we need to adjust the Max Distance of the Source
	if (ALSource->update1 & MAXDIST)
	{
		if (ALSource->uservalue2)
		{
			maxDist = ALSource->param[AL_MAX_DISTANCE-AL_CONE_INNER_ANGLE].data.f;
			IDirectSound3DBuffer_SetMaxDistance((LPDIRECTSOUND3DBUFFER)ALSource->uservalue2,maxDist,DS3D_IMMEDIATE);	
			ALSource->update1 &= ~MAXDIST;
			if (ALSource->update1 == 0)
				return;
		}
	}


	// Check if we need to adjust the Cone Outside Volume of the Source
	if (ALSource->update1 & CONEOUTSIDEVOLUME)
	{
		if (ALSource->uservalue2)
		{
			outerGain = ALSource->param[AL_CONE_OUTER_GAIN-AL_CONE_INNER_ANGLE].data.f;
			volume = LinearGainToDB(outerGain);

			IDirectSound3DBuffer_SetConeOutsideVolume((LPDIRECTSOUND3DBUFFER)ALSource->uservalue2, volume,DS3D_IMMEDIATE);

			ALSource->update1 &= ~CONEOUTSIDEVOLUME;
			if (ALSource->update1 == 0)
				return;
		}
	}

	
	// Check if we need to update the 3D Processing Mode (Head Relative)
	if (ALSource->update1 & MODE)
	{
		if (ALSource->uservalue2)
		{
			Relative = ALSource->relative ? DS3DMODE_HEADRELATIVE : DS3DMODE_NORMAL;
			IDirectSound3DBuffer_SetMode((LPDIRECTSOUND3DBUFFER)ALSource->uservalue2,Relative,DS3D_IMMEDIATE);
			ALSource->update1 &= ~MODE;
			if (ALSource->update1 == 0)
				return;
		}
	}


	// Check if we ne need to update the Cone Angles for the Source
	if (ALSource->update1 & CONEANGLES)
	{
		if (ALSource->uservalue2)
		{
			innerAngle = (ALuint)ALSource->param[AL_CONE_INNER_ANGLE-AL_CONE_INNER_ANGLE].data.f;
			outerAngle = (ALuint)ALSource->param[AL_CONE_OUTER_ANGLE-AL_CONE_INNER_ANGLE].data.f;

			IDirectSound3DBuffer_SetConeAngles((LPDIRECTSOUND3DBUFFER)ALSource->uservalue2,innerAngle,outerAngle,DS3D_IMMEDIATE);
			ALSource->update1 &= ~CONEANGLES;
			if (ALSource->update1 == 0)
				return;
		}
	}


	// Check if Looping has been enabled / disabled
	if (ALSource->update1 & LOOPED)
	{
		// Only has an effect if the Source is playing
		if ((ALSource->uservalue1) && (ALSource->state == AL_PLAYING))
		{
			// Find out whether Looping has been enabled or disabled
			Loop = ALSource->param[AL_LOOPING-AL_CONE_INNER_ANGLE].data.i;

			if (Loop == AL_TRUE)
			{
				// Looping enabled !

				// All buffers in queue will be needed again, so their state needs to be upgraded
				// to PENDING, and the number of buffers processed set to 0
				ALSource->BuffersProcessed = 0;

				// While calculating the total size of the data (by summing the datasize of each
				// buffer in the queue), set all Buffer states to PENDING
				ALBufferListTemp = ALSource->queue;
				ALSource->DataStillToPlay = 0;

				while (ALBufferListTemp != NULL)
				{
					DataSize = ((ALbuffer*)ALBufferListTemp->buffer)->size;
					ALSource->DataStillToPlay += DataSize;
					ALBufferListTemp->bufferstate = PENDING;
					ALBufferListTemp = ALBufferListTemp->next;
				}

				// If we have added silence after the valid data, then we need to set the new
				// write position back to the end of the valid data
				if (ALSource->SilenceAdded > 0)
				{
					if (ALSource->OldWriteCursor < ALSource->SilenceAdded)
					{
						//ALSource->OldWriteCursor += 88200;
						ALSource->OldWriteCursor += 44100;
					}

					ALSource->OldWriteCursor -= ALSource->SilenceAdded;

					ALSource->BufferPosition = 0;
				}

				ALSource->FinishedQueue = AL_FALSE;
			}
			else
			{
				// Looping disabled !
				
				// We need to calculate how much data is still to be played
				IDirectSoundBuffer_GetCurrentPosition((LPDIRECTSOUNDBUFFER)ALSource->uservalue1, &PlayCursor, &WriteCursor);
				
				// Calculate amount of data played
				if (ALSource->OldPlayCursor > PlayCursor)
				{
					//ALSource->BytesPlayed += ((88200 - ALSource->OldPlayCursor) + PlayCursor);
					ALSource->BytesPlayed += ((44100 - ALSource->OldPlayCursor) + PlayCursor);
				}
				else
					ALSource->BytesPlayed += (PlayCursor - ALSource->OldPlayCursor);
				
				ALSource->OldPlayCursor = PlayCursor;

				// Calculate how much data is left to play for the current iteration of the looping data

				TotalDataSize = 0;
				ALBufferListTemp = ALSource->queue;

				while (ALBufferListTemp != NULL)
				{
					DataSize = ((ALbuffer*)ALBufferListTemp->buffer)->size;
					TotalDataSize += DataSize;
					ALBufferListTemp = ALBufferListTemp->next;
				}

				ALSource->DataStillToPlay = TotalDataSize - (ALSource->BytesPlayed % TotalDataSize);

				if (WriteCursor > PlayCursor)
					DataCommitted = WriteCursor - PlayCursor;
				else
				{
					//DataCommitted = (88200 - PlayCursor) + WriteCursor;
					DataCommitted = (44100 - PlayCursor) + WriteCursor;
				}

				if (DataCommitted > ALSource->DataStillToPlay)
				{
					// Data for the next iteration of the loop has already been committed
					// Therefore increment DataStillToPlay by the total loop size
					ALSource->DataStillToPlay += TotalDataSize;
				}
				else
				{
					DataPlayed = TotalDataSize - ALSource->DataStillToPlay;
					DataCount = 0;
					ALSource->BuffersProcessed = 0;

					ALBufferListItem = ALSource->queue;
					while (ALBufferListItem != NULL)
					{
						DataSize = ((ALbuffer*)ALBufferListItem->buffer)->size;
						DataCount += DataSize;
						if (DataCount < DataPlayed)
						{
							ALBufferListItem->bufferstate = PROCESSED;
							ALBufferListItem = ALBufferListItem->next;
							ALSource->BuffersProcessed++;
						}
						else
							ALBufferListItem = NULL;
					}
				}

				//if (ALSource->DataStillToPlay < 88200)
				//{
				//	// Need to move Write Cursor to end of valid data (so silence can be added
				//	// after it)
				//	ALSource->OldWriteCursor = PlayCursor + ALSource->DataStillToPlay;

				//	if (ALSource->OldWriteCursor >= 88200)
				//		ALSource->OldWriteCursor -= 88200;
				//
				//	ALSource->FinishedQueue = AL_TRUE;
				//}

				if (ALSource->DataStillToPlay < 44100)
				{
					// Need to move Write Cursor to end of valid data (so silence can be added
					// after it)
					ALSource->OldWriteCursor = PlayCursor + ALSource->DataStillToPlay;

					if (ALSource->OldWriteCursor >= 44100)
						ALSource->OldWriteCursor -= 44100;

					ALSource->FinishedQueue = AL_TRUE;
				}
			}	
		}
		ALSource->update1 &= ~LOOPED;
		if (ALSource->update1 == 0)
			return;
	}

	return;
}

/*
	Update Open AL Listener Properties
*/
void UpdateListener(ALCcontext *ALContext)
{
	ALfloat		Pos[3],Vel[3], Ori[6];
	ALfloat		flDistanceFactor;
	ALfloat		flRollOffFactor;
	ALsource	*ALSource;
	ALfloat		Gain;
	ALuint		i;
	ALint		volume;

	if (ALContext->Listener.update1 & LVOLUME)
	{
		// Setting the volume of the Primary buffer has the effect of setting the volume
		// of the Wave / Direct Sound Mixer Line, so we can't do that

		// Instead we adjust the Gain of every Source

		ALSource = ALContext->Source;

		for (i = 0; i < ALContext->SourceCount; i++)
		{
			if (ALSource->uservalue1)
			{
				// Get current gain for source
				Gain = ALSource->param[AL_GAIN-AL_CONE_INNER_ANGLE].data.f;				
				Gain = (Gain * ALContext->Listener.Gain);
				volume = LinearGainToDB(Gain);
				IDirectSoundBuffer_SetVolume((LPDIRECTSOUNDBUFFER)ALSource->uservalue1, volume);
			}
			ALSource = ALSource->next;
		}

		ALContext->Listener.update1 &= ~LVOLUME;
		if (ALContext->Listener.update1 == 0)
			return;
	}

	if (ALContext->Listener.update1 & LPOSITION)
	{
		Pos[0] = ALContext->Listener.Position[0];
		Pos[1] = ALContext->Listener.Position[1];
		Pos[2] = -ALContext->Listener.Position[2];
		IDirectSound3DListener_SetPosition(ALContext->Device->DS3dlistener, Pos[0], Pos[1], Pos[2],DS3D_IMMEDIATE);
		ALContext->Listener.update1 &= ~LPOSITION;
		if (ALContext->Listener.update1 == 0)
			return;
	}

	if (ALContext->Listener.update1 & LVELOCITY)
	{
		Vel[0] = ALContext->Listener.Velocity[0];
		Vel[1] = ALContext->Listener.Velocity[1];
		Vel[2] = -ALContext->Listener.Velocity[2];
		IDirectSound3DListener_SetVelocity(ALContext->Device->DS3dlistener, Vel[0], Vel[1], Vel[2],DS3D_IMMEDIATE);
		ALContext->Listener.update1 &= ~LVELOCITY;
		if (ALContext->Listener.update1 == 0)
			return;
	}

	if (ALContext->Listener.update1 & LORIENTATION)
	{
		Ori[0] = ALContext->Listener.Forward[0];
		Ori[1] = ALContext->Listener.Forward[1];
		Ori[2] = -ALContext->Listener.Forward[2];
		Ori[3] = ALContext->Listener.Up[0];
		Ori[4] = ALContext->Listener.Up[1];
		Ori[5] = -ALContext->Listener.Up[2];
		IDirectSound3DListener_SetOrientation(ALContext->Device->DS3dlistener, Ori[0], Ori[1], Ori[2], Ori[3], Ori[4], Ori[5], DS3D_IMMEDIATE);
		ALContext->Listener.update1 &= ~LORIENTATION;
		if (ALContext->Listener.update1 == 0)
			return;
	}

	if (ALContext->Listener.update1 & LDOPPLERFACTOR)
	{
		IDirectSound3DListener_SetDopplerFactor(ALContext->Device->DS3dlistener,ALContext->DopplerFactor,DS3D_IMMEDIATE);
		ALContext->Listener.update1 &= ~LDOPPLERFACTOR;
		if (ALContext->Listener.update1 == 0)
			return;
	}

	if (ALContext->Listener.update1 & LDOPPLERVELOCITY)
	{
		// Doppler Velocity is used to set the speed of sound in units per second
		// DS3D uses Distance Factor to relate units to real world coordinates (metres)
		// Therefore need to convert Doppler Velocity into DS3D Distance Factor
		flDistanceFactor = SPEEDOFSOUNDMETRESPERSEC / ALContext->DopplerVelocity;
		IDirectSound3DListener_SetDistanceFactor(ALContext->Device->DS3dlistener, flDistanceFactor, DS3D_IMMEDIATE);
		ALContext->Listener.update1 &= ~LDOPPLERVELOCITY;
		if (ALContext->Listener.update1 == 0)
			return;
	}

	if (ALContext->Listener.update1 & LDISTANCEMODEL)
	{
		if (ALContext->DistanceModel == AL_NONE)
			flRollOffFactor = 0.0f;
		else
			flRollOffFactor = 1.0f;

		IDirectSound3DListener_SetRolloffFactor (ALContext->Device->DS3dlistener, flRollOffFactor, DS3D_IMMEDIATE);
		ALContext->Listener.update1 &= ~LDISTANCEMODEL;
		if (ALContext->Listener.update1 == 0)
			return;
	}

	return;
}


ALCAPI ALCdevice* ALCAPIENTRY alcOpenDevice(ALCubyte *deviceName)
{
	DSBUFFERDESC DSBDescription;
	WAVEFORMATEX OutputType;
	ALCdevice *device=NULL;
	ALint vmode=1;
	ALint i;
	DSCAPS dsCaps;
	ALvoid *lpPart1, *lpPart2;
	ALuint dwSize1, dwSize2;
	ALboolean bUseDS;
	ALboolean bUseDS3D;

	bUseDS = AL_FALSE;
	bUseDS3D = AL_FALSE;

	if (deviceName != NULL)
	{
		if (strcmp(deviceName,"DirectSound3D")==0)
			bUseDS3D = AL_TRUE;
		else if (strcmp(deviceName, "DirectSound")==0)
			bUseDS = AL_TRUE;
	}
	else
	{
		// If no device name is specified, we will attempt to use DS3D
		bUseDS3D = AL_TRUE;
	}

	device=malloc(sizeof(ALCdevice));
	if (device)
	{
		//Initialise device structure
		memset(device,0,sizeof(ALCdevice));
		//Validate device
		device->LastError=AL_NO_ERROR;
		device->InUse=AL_TRUE;
		device->Valid=AL_TRUE;
		//Set output format
		device->Frequency=22050;
		device->Channels=2;
		device->Format=AL_FORMAT_STEREO16;
		//Platform specific
		InitializeCriticalSection(&g_mutex);
		memset(&OutputType,0,sizeof(WAVEFORMATEX));
		OutputType.wFormatTag=WAVE_FORMAT_PCM;
		OutputType.nChannels=device->Channels;
		OutputType.wBitsPerSample=(((device->Format==AL_FORMAT_MONO16)||(device->Format==AL_FORMAT_STEREO16))?16:8);
		OutputType.nBlockAlign=OutputType.nChannels*OutputType.wBitsPerSample/8;
		OutputType.nSamplesPerSec=device->Frequency;
		OutputType.nAvgBytesPerSec=OutputType.nSamplesPerSec*OutputType.nBlockAlign;
		OutputType.cbSize=0;
		//Initialise requested device

		if (bUseDS3D)
		{
			//Init COM
			CoInitialize(NULL);
			//DirectSound Init code
			if (CoCreateInstance(&CLSID_DirectSound,NULL,CLSCTX_INPROC_SERVER,&IID_IDirectSound,&(device->DShandle))==S_OK)
			{
				if (IDirectSound_Initialize(device->DShandle,NULL)==DS_OK)
				{
					if (IDirectSound_SetCooperativeLevel(device->DShandle,GetForegroundWindow(),DSSCL_PRIORITY)==DS_OK)
					{
						memset(&DSBDescription,0,sizeof(DSBUFFERDESC));
						DSBDescription.dwSize=sizeof(DSBUFFERDESC);
						DSBDescription.dwFlags=DSBCAPS_PRIMARYBUFFER|DSBCAPS_CTRL3D|DSBCAPS_CTRLVOLUME;
						if (IDirectSound_CreateSoundBuffer(device->DShandle,&DSBDescription,&device->DSpbuffer,NULL)==DS_OK)
						{
							if (IDirectSoundBuffer_SetFormat(device->DSpbuffer,&OutputType)==DS_OK)
							{
								if (IDirectSoundBuffer_QueryInterface(device->DSpbuffer,&IID_IDirectSound3DListener,&device->DS3dlistener)==DS_OK)
								{
									memset(&dsCaps, 0, sizeof(DSCAPS));
									dsCaps.dwSize = sizeof(DSCAPS);
									if (IDirectSound_GetCaps(device->DShandle, &dsCaps) == DS_OK)
									{
										// Check that is an accelerated DS device
										if (!(dsCaps.dwFlags & DSCAPS_EMULDRIVER))
										{
											// Check how many Hardware 3D Streaming buffers can be created
											device->MaxNoOfSources = dsCaps.dwFreeHw3DStreamingBuffers;
											// Some soundcards incorrectly report the number of voices so we are going to
											// clamp the number of Sources to an upper limit of 31


											//(E) 2010-07-22 Editor: AFEW
											//if (device->MaxNoOfSources > 31)
											//{
											//	device->MaxNoOfSources = 31;
											//}
											//
											//if (device->MaxNoOfSources > 15)
											//{
											//	device->CreationFlag = DSBCAPS_LOCHARDWARE;
											//}
											//else
											//{
											//	device->MaxNoOfSources = 16;
											//	device->CreationFlag = DSBCAPS_LOCSOFTWARE;
											//}

											device->MaxNoOfSources = 256;
											device->CreationFlag = DSBCAPS_LOCSOFTWARE;

											strcpy(device->szDeviceName, "DirectSound3D");
											return device;
										}
									}

									IDirectSound3DListener_Release(device->DS3dlistener);
									device->DS3dlistener=NULL;
								}
							}
							IDirectSoundBuffer_Release(device->DSpbuffer);
							device->DSpbuffer=NULL;
						}
					}
					IDirectSound_Release(device->DShandle);
					device->DShandle=NULL;
				}
			}
			// Failed to initialize DirectSound3D device - so fall back to DirectSound device
			bUseDS = AL_TRUE;
		}

		if (bUseDS)
		{
			//Init COM
			CoInitialize(NULL);
			//DirectSound Init code
			if (CoCreateInstance(&CLSID_DirectSound,NULL,CLSCTX_INPROC_SERVER,&IID_IDirectSound,&device->DShandle)==S_OK)
			{
				if (IDirectSound_Initialize(device->DShandle,NULL)==DS_OK)
				{
					if (IDirectSound_SetCooperativeLevel(device->DShandle,GetForegroundWindow(),DSSCL_PRIORITY)==DS_OK)
					{
						memset(&DSBDescription,0,sizeof(DSBUFFERDESC));
						DSBDescription.dwSize=sizeof(DSBUFFERDESC);
						DSBDescription.dwFlags=DSBCAPS_PRIMARYBUFFER;
						if (IDirectSound_CreateSoundBuffer(device->DShandle,&DSBDescription,&device->DSpbuffer,NULL)==DS_OK)
						{
							if (IDirectSoundBuffer_SetFormat(device->DSpbuffer,&OutputType)==DS_OK)
							{
								memset(&DSBDescription,0,sizeof(DSBUFFERDESC));
								DSBDescription.dwSize=sizeof(DSBUFFERDESC);
								DSBDescription.dwFlags=DSBCAPS_GLOBALFOCUS|DSBCAPS_GETCURRENTPOSITION2;
								DSBDescription.dwBufferBytes=32768;
								DSBDescription.lpwfxFormat=&OutputType;
								if (IDirectSound_CreateSoundBuffer(device->DShandle,&DSBDescription,&device->DSsbuffer,NULL)==DS_OK)
								{
									// Check that is a hardware accelerated DS device
									memset(&dsCaps, 0, sizeof(DSCAPS));
									dsCaps.dwSize = sizeof(DSCAPS);
									if (IDirectSound_GetCaps(device->DShandle, &dsCaps) == DS_OK)
									{
										// Check that is an accelerated DS device
										if (!(dsCaps.dwFlags & DSCAPS_EMULDRIVER))
										{
											if (IDirectSoundBuffer_Lock(device->DSsbuffer,0,0,&lpPart1, &dwSize1, &lpPart2, &dwSize2, DSBLOCK_ENTIREBUFFER ) == DS_OK)
											{
												memset(lpPart1, 0, dwSize1);
												IDirectSoundBuffer_Unlock(device->DSsbuffer,lpPart1, dwSize1, lpPart1, dwSize2);
											}
											if (IDirectSoundBuffer_Play(device->DSsbuffer,0,0,DSBPLAY_LOOPING)==DS_OK)
											{
												device->timer=timeSetEvent(25,0,alcDirectSoundProc,(DWORD)device,TIME_CALLBACK_FUNCTION|TIME_PERIODIC);

												//(E) 2010-07-22 Editor: AFEW
												//device->MaxNoOfSources = 32;
												device->MaxNoOfSources = 256;

												strcpy(device->szDeviceName, "DirectSound");
												return device;
											}
										}
									}
									IDirectSoundBuffer_Release(device->DSsbuffer);
									device->DSsbuffer=NULL;
								}
							}
							IDirectSoundBuffer_Release(device->DSpbuffer);
							device->DSpbuffer=NULL;
						}
					}
					IDirectSound_Release(device->DShandle);
					device->DShandle=NULL;
				}
			}
		}
		
		// Fallback to WaveOut code
		if (waveOutOpen(&device->handle,WAVE_MAPPER,&OutputType,0,0,WAVE_FORMAT_DIRECT_QUERY)==MMSYSERR_NOERROR)
		{
			if (waveOutOpen(&device->handle,WAVE_MAPPER,&OutputType,(DWORD)&alcWaveOutProc,(DWORD)0,CALLBACK_FUNCTION)==MMSYSERR_NOERROR)
			{
				g_hWaveHdrEvent = CreateEvent(NULL, AL_TRUE, AL_FALSE, "WaveOutAllHeadersReturned");
				if (g_hWaveHdrEvent != NULL)
				{
					g_hWaveThreadEvent = CreateEvent(NULL, AL_TRUE, AL_FALSE, "WaveOutThreadDestroyed");
					if (g_hWaveThreadEvent != NULL)
					{
						g_hThread=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)ThreadProc,NULL,0,&g_ThreadID);
						if (g_hThread != NULL)
						{
							//(E) 2010-07-22 Editor: AFEW
							//device->MaxNoOfSources = 32;
							device->MaxNoOfSources = 256;

							// Setup Windows Multimedia driver buffers and start playing
							for (i=0;i<NUMWAVEBUFFERS;i++)
							{
								memset(&device->buffer[i],0,sizeof(WAVEHDR));
								device->buffer[i].lpData=malloc(((OutputType.nAvgBytesPerSec/16)&0xfffffff0));
								device->buffer[i].dwBufferLength=((OutputType.nAvgBytesPerSec/16)&0xfffffff0);
								device->buffer[i].dwFlags=0;
								device->buffer[i].dwLoops=0;
								waveOutPrepareHeader(device->handle,&device->buffer[i],sizeof(WAVEHDR));
								if (waveOutWrite(device->handle,&device->buffer[i],sizeof(WAVEHDR))!=MMSYSERR_NOERROR)
								{
									waveOutUnprepareHeader(device->handle,&device->buffer[i],sizeof(WAVEHDR));
									free(device->buffer[i].lpData);
								}
								else
									g_BuffersCommitted++;
							}
							strcpy(device->szDeviceName, "MMSYSTEM");
							return device;
						}
						CloseHandle(g_hWaveThreadEvent);
						g_hWaveThreadEvent = NULL;
					}
					CloseHandle(g_hWaveHdrEvent);
					g_hWaveHdrEvent = NULL;
				}
				waveOutClose(device->handle);
				device->handle = NULL;
			}
		}

		// No suitable output device found
		free(device);
		device = NULL;
	}

	return device;
}


ALCAPI ALCvoid ALCAPIENTRY alcCloseDevice(ALCdevice *device)
{
	ALint i;

	if (device)
	{
		EnterCriticalSection(&g_mutex);
		//Release timer
		if (device->timer)
			timeKillEvent(device->timer);
		//Platform specific exit
		if (device->DShandle)
		{
			if (device->DS3dlistener)
				IDirectSound3DListener_Release(device->DS3dlistener);
			if (device->DSsbuffer)
				IDirectSoundBuffer_Release(device->DSsbuffer);
			if (device->DSpbuffer)
				IDirectSoundBuffer_Release(device->DSpbuffer);
			if (device->DShandle)
				IDirectSound_Release(device->DShandle);
			//Deinit COM
			CoUninitialize();		
		}
		else
		{
			bWaveShutdown = AL_TRUE;

			// Wait for signal that all Wave Buffers have returned
			WaitForSingleObjectEx(g_hWaveHdrEvent, 5000, FALSE);

			// Wait for signal that Wave Thread has been destroyed
			WaitForSingleObjectEx(g_hWaveThreadEvent, 5000, FALSE);
			
			// Call waveOutReset to shutdown wave device
			waveOutReset(device->handle);

			// Release them all
			for (i=0;i<NUMWAVEBUFFERS;i++)
			{
				waveOutUnprepareHeader(device->handle,&device->buffer[i],sizeof(WAVEHDR));
				free(device->buffer[i].lpData);
			}

			// Close the Wave device
			waveOutClose(device->handle);
			device->handle = 0;


			CloseHandle(g_hThread);
			g_hThread = 0;

			if (g_hWaveHdrEvent)
			{
				CloseHandle(g_hWaveHdrEvent);
				g_hWaveHdrEvent = 0;
			}

			if (g_hWaveThreadEvent)
			{
				CloseHandle(g_hWaveThreadEvent);
				g_hWaveThreadEvent = 0;
			}
		}
		//Release device structure
		DeleteCriticalSection(&g_mutex);
		memset(device,0,sizeof(ALCdevice));
		free(device);
	}
	else alcSetError(ALC_INVALID_DEVICE);
}

DWORD WINAPI ThreadProc(LPVOID lpParameter)
{
	ALCcontext *ALContext;
	ALCdevice *ALDevice;
	LPWAVEHDR WaveHdr;
	MSG msg;

	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		if ((msg.message==WOM_DONE)&&(!bWaveShutdown))
		{
			if (ALContext=alcGetCurrentContext())
			{			
				WaveHdr=((LPWAVEHDR)msg.lParam);
				ALDevice=alcGetContextsDevice(ALContext);
				if (ALContext)
				{
					alcSuspendContext(ALContext);
					aluMixData(ALContext,WaveHdr->lpData,WaveHdr->dwBufferLength,ALContext->Format);
					alcProcessContext(ALContext);
				}
				else memset(WaveHdr->lpData,0,WaveHdr->dwBufferLength);
				waveOutWrite(ALDevice->handle,WaveHdr,sizeof(WAVEHDR));
				g_BuffersCommitted++;
			}
		}
	}

	// Signal Wave Thread completed event
	if (g_hWaveThreadEvent)
		SetEvent(g_hWaveThreadEvent);

	ExitThread(0);

	return 0;
}

/*
	alcIsExtensionPresent(device, extName)

	Determine if there is an extension called extName available
*/
ALCAPI ALCboolean ALCAPIENTRY alcIsExtensionPresent(ALCdevice *device,ALCubyte *extName)
{
	ALsizei i=0;

	while ((alcExtensions[i].extName)&&(strcmp((char *)alcExtensions[i].extName,(char *)extName)))
		i++;
	return (alcExtensions[i].extName!=NULL?AL_TRUE:AL_FALSE);
}


/*
	alcGetProcAddress(device, funcName)

	Get the function address for given function extension
*/
ALCAPI ALCvoid *  ALCAPIENTRY alcGetProcAddress(ALCdevice *device,ALCubyte *funcName)
{
	ALsizei i=0;

	while ((alcFunctions[i].funcName)&&(strcmp((char *)alcFunctions[i].funcName,(char *)funcName)))
		i++;
	return alcFunctions[i].address;
}


/*
	alcGetEnumValue(device, enumName)

	Get the value for a particular ALC Enumerated Value
	Calls alGetEnumValue in alExtension.c to process request
*/
ALCAPI ALCenum ALCAPIENTRY alcGetEnumValue(ALCdevice *device,ALCubyte *enumName)
{
	return alGetEnumValue(enumName);
}


/*
	LinearGainToDB

	Helper function to convert a floating point amplitude (range 0.0 to 1.0) to Decibels
*/
ALint LinearGainToDB(float flGain)
{
	if (flGain > 0)
		return (long)(2000.0*log10(flGain));
	else
		return -10000;
}
