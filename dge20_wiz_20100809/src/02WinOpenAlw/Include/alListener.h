#ifndef _AL_LISTENER_H_
#define _AL_LISTENER_H_

#define ALAPI __declspec(dllexport)
#define ALAPIENTRY __cdecl

#include "AL_win\altypes.h"

#ifdef __cplusplus
extern "C" {
#endif

// Flags indicating what Direct Sound parameters need to be updated in the UpdateContext call
#define LVOLUME				1
#define LPOSITION			2
#define LVELOCITY			4
#define LORIENTATION		8
#define LDOPPLERFACTOR		16
#define LDOPPLERVELOCITY	32
#define LDISTANCEMODEL		64

#pragma pack(push, 4)

typedef struct ALlistener_struct
{
	ALfloat		Position[3];
	ALfloat		Velocity[3];
	ALfloat		Forward[3];
	ALfloat		Up[3];
	ALfloat		Gain;
	ALuint		update1;			// Store changes that need to be made in UpdateContext
} ALlistener;

#pragma pack (pop)
/*
ALAPI ALvoid	ALAPIENTRY alListenerf(ALenum pname,ALfloat value);
ALAPI ALvoid	ALAPIENTRY alListener3f(ALenum pname,ALfloat v1,ALfloat v2,ALfloat v3); 
ALAPI ALvoid	ALAPIENTRY alListenerfv(ALenum pname,ALfloat *values); 
ALAPI ALvoid	ALAPIENTRY alListeneri(ALenum pname,ALint value);
ALAPI ALvoid	ALAPIENTRY alGetListenerf(ALenum pname,ALfloat *value);
ALAPI ALvoid	ALAPIENTRY alGetListener3f(ALenum pname,ALfloat *v1,ALfloat *v2,ALfloat *v3); 
ALAPI ALvoid	ALAPIENTRY alGetListenerfv(ALenum pname,ALfloat *values); 
ALAPI ALvoid	ALAPIENTRY alGetListeneri(ALenum pname,ALint *value);
*/
#ifdef __cplusplus
}
#endif

#endif