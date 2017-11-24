// Interface for the CMain class.
//
////////////////////////////////////////////////////////////////////////////////


#if defined(_WIN32) || defined(WIN32)
	#if _MSC_VER > 1000
	#pragma once
	#endif
#endif


#ifndef __StdAfx_H_
#define __StdAfx_H_


#define GP2X_WIZ	1


#if defined(_WIN32) || defined(WIN32)
	#pragma comment(linker, "/subsystem:console")
	#pragma comment(lib, "freetype2311MT_D.lib")

	#pragma comment(lib, "dge20_.lib")
	#pragma comment(lib, "dgx20_.lib")
	#pragma comment(lib, "dgt20_.lib")

	#pragma comment(lib, "OpenGL32.lib")

	#pragma comment(lib, "winmm.lib")
	#pragma comment(lib, "openal11_.lib")
	#pragma comment(lib, "openalc11_.lib")
	#pragma comment(lib, "openalu11_.lib")
	#pragma comment(lib, "openalut11_.lib")

	#pragma comment(lib, "png124_.lib")
	#pragma comment(lib, "zImgJpg_.lib")
	#pragma comment(lib, "zlib123_.lib")

	#include <windows.h>
	#include <conio.h>

	#include <AL_win/al.h>
	#include <AL_win/alc.h>
	#include <AL_win/alut.h>

#else
	#include <AL/al.h>
	#include <AL/alc.h>
	#include <AL/alut.h>

	#include <unistd.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <gles/gl.h>

#include <DGE_Type.h>
#include <DGE_System.h>
#include <DGE_Util.h>
#include <DGE_Time.h>
#include <DGE_Math.h>
#include <DGE_Base.h>
#include <DGE_Haptic.h>
#include <DGX_Font.h>
#include <DGX_Input.h>
#include <DGX_Sound.h>
#include <DGX_Media.h>
#include <DGT_DRM.h>


#include "AppDge.h"


#include "define.h"
#include "dconv.h"
#include "util.h"
#include "blt.h"


#include "GpLogo.h"
#include "GpTitle.h"
#include "GpAct.h"
#include "GpEnding.h"
#include "GpStage.h"
#include "GpDemo.h"
#include "GpOption.h"




#include "Main.h"


#endif


