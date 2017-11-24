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


#if defined(_WIN32) || defined(WIN32)
	#pragma comment(linker, "/subsystem:console")
	#pragma comment(lib, "freetype2311MT_D.lib")

	#pragma comment(lib, "dge20_.lib")
	#pragma comment(lib, "dgx20_.lib")
	#pragma comment(lib, "dgt20_.lib")

	#pragma comment(lib, "zImgJpg_.lib")
	#pragma comment(lib, "png124_.lib")
	#pragma comment(lib, "zlib123_.lib")

	#pragma comment(lib, "libgles_cm.lib")

	#include <windows.h>
#endif


#include <stdio.h>

#include <gles/gl.h>

#include <DGE_Type.h>
#include <DGE_System.h>
#include <DGE_Util.h>
#include <DGE_Input10.h>
#include <DGE_Time.h>
#include <DGE_Math.h>
#include <DGE_Base.h>
#include <DGX_Font.h>
#include <DGX_Input.h>
#include <DGX_Camera.h>
#include <DGX_Entity.h>
#include <DGX_Camera.h>

#include "DGX_Mdl.h"

#include "AppDge.h"




#include "Main.h"


#endif


