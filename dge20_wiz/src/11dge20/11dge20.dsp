# Microsoft Developer Studio Project File - Name="11dge20" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=11dge20 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "11dge20.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "11dge20.mak" CFG="11dge20 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "11dge20 - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "11dge20 - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "11dge20 - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /Zi /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "_HOST_" /FR /YX /FD /c
# ADD BASE RSC /l 0x412 /d "NDEBUG"
# ADD RSC /l 0x412 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\..\lib\dge20.lib"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PreLink_Cmds=copy           DGE_Math.h           ..\..\include\ 
PostBuild_Cmds=copy       DGE_Type.h       ..\..\include\      	copy       DGE_System.h       ..\..\include\      	copy       DGE_Util.h       ..\..\include\      	copy       DGE_Time.h       ..\..\include\      	copy       DGE_Haptic.h       ..\..\include\      	copy       DGE_Gsensor.h       ..\..\include\      	copy       DGE_Input10.h       ..\..\include\      	copy       DGE_Input20.h       ..\..\include\      	copy       DGE_Input.h       ..\..\include\      	copy       DGE_Base.h       ..\..\include\ 
# End Special Build Tool

!ELSEIF  "$(CFG)" == "11dge20 - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "_HOST_" /FR /YX /FD /GZ /c
# ADD BASE RSC /l 0x412 /d "_DEBUG"
# ADD RSC /l 0x412 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\..\lib\dge20_.lib"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PreLink_Cmds=copy           DGE_Math.h           ..\..\include\ 
PostBuild_Cmds=copy       DGE_Type.h       ..\..\include\      	copy       DGE_System.h       ..\..\include\      	copy       DGE_Util.h       ..\..\include\      	copy       DGE_Time.h       ..\..\include\      	copy       DGE_Haptic.h       ..\..\include\      	copy       DGE_Gsensor.h       ..\..\include\      	copy       DGE_Input10.h       ..\..\include\      	copy       DGE_Input20.h       ..\..\include\      	copy       DGE_Input.h       ..\..\include\      	copy       DGE_Base.h       ..\..\include\ 
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "11dge20 - Win32 Release"
# Name "11dge20 - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\DGE10_File.cpp
# End Source File
# Begin Source File

SOURCE=.\DGE10_Log.cpp
# End Source File
# Begin Source File

SOURCE=.\DGE_Device.cpp
# End Source File
# Begin Source File

SOURCE=.\DGE_gl.cpp
# End Source File
# Begin Source File

SOURCE=.\DGE_Gsensor.c
# End Source File
# Begin Source File

SOURCE=.\DGE_Haptic.c
# End Source File
# Begin Source File

SOURCE=.\DGE_Image.cpp
# End Source File
# Begin Source File

SOURCE=.\DGE_Input10.c
# End Source File
# Begin Source File

SOURCE=.\DGE_Math.cpp
# End Source File
# Begin Source File

SOURCE=.\DGE_Sprite.cpp
# End Source File
# Begin Source File

SOURCE=.\DGE_System.cpp
# End Source File
# Begin Source File

SOURCE=.\DGE_Texture.cpp
# End Source File
# Begin Source File

SOURCE=.\DGE_Time.c
# End Source File
# Begin Source File

SOURCE=.\DGE_Util.cpp
# End Source File
# Begin Source File

SOURCE=.\DGE_vbo.cpp
# End Source File
# Begin Source File

SOURCE=.\ImgBmp.c
# End Source File
# Begin Source File

SOURCE=.\ImgGpt.c
# End Source File
# Begin Source File

SOURCE=.\ImgJpg.c
# End Source File
# Begin Source File

SOURCE=.\ImgPng.c
# End Source File
# Begin Source File

SOURCE=.\ImgTga.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\DGE_Base.h
# End Source File
# Begin Source File

SOURCE=.\DGE_Gsensor.h
# End Source File
# Begin Source File

SOURCE=.\DGE_Haptic.h
# End Source File
# Begin Source File

SOURCE=.\DGE_Input.h
# End Source File
# Begin Source File

SOURCE=.\DGE_Input10.h
# End Source File
# Begin Source File

SOURCE=.\DGE_Math.h
# End Source File
# Begin Source File

SOURCE=.\DGE_Sprite.h
# End Source File
# Begin Source File

SOURCE=.\DGE_System.h
# End Source File
# Begin Source File

SOURCE=.\DGE_Texture.h
# End Source File
# Begin Source File

SOURCE=.\DGE_Time.h
# End Source File
# Begin Source File

SOURCE=.\DGE_Type.h
# End Source File
# Begin Source File

SOURCE=.\DGE_Util.h
# End Source File
# Begin Source File

SOURCE=.\DGX_Base.h
# End Source File
# Begin Source File

SOURCE=.\ImgBmp.h
# End Source File
# Begin Source File

SOURCE=.\ImgGpt.h
# End Source File
# Begin Source File

SOURCE=.\ImgJpg.h
# End Source File
# Begin Source File

SOURCE=.\ImgPng.h
# End Source File
# Begin Source File

SOURCE=.\ImgTga.h
# End Source File
# End Group
# End Target
# End Project
