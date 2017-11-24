# Microsoft Developer Studio Project File - Name="01dgeinc" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=01dgeinc - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "01dgeinc.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "01dgeinc.mak" CFG="01dgeinc - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "01dgeinc - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "01dgeinc - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "01dgeinc - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ""
# PROP Intermediate_Dir ""
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
# ADD LIB32 /nologo
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=mkdir  ..\..\include	mkdir  ..\..\lib	mkdir ..\..\include\AL	mkdir ..\..\include\AL_win	xcopy include\*.* ..\..\include\  /k/y/e/c/h/r	xcopy lib\*.* ..\..\lib\  /k/y/e/c/h/r	copy ..\11dge20\DGE_Type.h ..\..\include\	copy ..\11dge20\DGE_Math.h ..\..\include\	copy ..\11dge20\DGE_System.h ..\..\include\	copy ..\11dge20\DGE_Util.h ..\..\include\	xcopy ..\02openal\AL\*.* ..\..\include\AL  /k/y/e/c/h/r	xcopy ..\02WinOpenAl\ALwin\*.* ..\..\include\AL_win  /k/y/e/c/h/r
# End Special Build Tool

!ELSEIF  "$(CFG)" == "01dgeinc - Win32 Debug"

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
# ADD LIB32 /nologo /out:"debug\dummy_.lib"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=mkdir  ..\..\include	mkdir  ..\..\lib	mkdir ..\..\include\AL	mkdir ..\..\include\AL_win	xcopy include\*.* ..\..\include\  /k/y/e/c/h/r	xcopy lib\*.* ..\..\lib\  /k/y/e/c/h/r	copy ..\11dge20\DGE_Type.h ..\..\include\	copy ..\11dge20\DGE_Math.h ..\..\include\	copy ..\11dge20\DGE_System.h ..\..\include\	copy ..\11dge20\DGE_Util.h ..\..\include\	xcopy ..\02openal\AL\*.* ..\..\include\AL  /k/y/e/c/h/r	xcopy ..\02WinOpenAlw\ALwin\*.* ..\..\include\AL_win  /k/y/e/c/h/r
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "01dgeinc - Win32 Release"
# Name "01dgeinc - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\dumy.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# End Group
# End Target
# End Project
