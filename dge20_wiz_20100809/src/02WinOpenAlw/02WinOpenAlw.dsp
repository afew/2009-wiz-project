# Microsoft Developer Studio Project File - Name="02WinOpenAlw" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=02WinOpenAlw - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "02WinOpenAlw.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "02WinOpenAlw.mak" CFG="02WinOpenAlw - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "02WinOpenAlw - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "02WinOpenAlw - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "02WinOpenAlw - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "ALwin32_EXPORTS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /O2 /I "..\\" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ALwin32LIB" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 dxguid.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /out:"release\openal11.dll"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy release\openal11.dll ..\..\..\lib\	copy debug\openal11.lib ..\..\..\lib\	copy release\openal11.dll ..\openALDemo\release
# End Special Build Tool

!ELSEIF  "$(CFG)" == "02WinOpenAlw - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "ALwin32_EXPORTS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /ZI /Od /I "..\\" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ALwin32LIB" /FR /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 dxguid.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /version:1.0 /dll /debug /machine:I386 /nodefaultlib:"LIBCD" /out:"debug\openal11_.dll" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy   debug\openal11_.dll   ..\..\lib\  	copy   debug\openal11_.lib   ..\..\lib\ 
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "02WinOpenAlw - Win32 Release"
# Name "02WinOpenAlw - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\alBuffer.c
# End Source File
# Begin Source File

SOURCE=.\alEax.c
# End Source File
# Begin Source File

SOURCE=.\alError.c
# End Source File
# Begin Source File

SOURCE=.\alExtension.c
# End Source File
# Begin Source File

SOURCE=.\alListener.c
# End Source File
# Begin Source File

SOURCE=.\alSource.c
# End Source File
# Begin Source File

SOURCE=.\alState.c
# End Source File
# Begin Source File

SOURCE=.\ALwin32.c
# End Source File
# Begin Source File

SOURCE=.\ALwin32.rc
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Include\alBuffer.h
# End Source File
# Begin Source File

SOURCE=.\Include\alEax.h
# End Source File
# Begin Source File

SOURCE=.\Include\alError.h
# End Source File
# Begin Source File

SOURCE=.\Include\alExtension.h
# End Source File
# Begin Source File

SOURCE=.\Include\alListener.h
# End Source File
# Begin Source File

SOURCE=.\Include\alMain.h
# End Source File
# Begin Source File

SOURCE=.\Include\alSource.h
# End Source File
# Begin Source File

SOURCE=.\Include\alState.h
# End Source File
# End Group
# Begin Group "AL Headers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\AL\al.h
# End Source File
# Begin Source File

SOURCE=..\AL\alc.h
# End Source File
# Begin Source File

SOURCE=..\AL\alctypes.h
# End Source File
# Begin Source File

SOURCE=..\AL\altypes.h
# End Source File
# Begin Source File

SOURCE=..\AL\alu.h
# End Source File
# Begin Source File

SOURCE=..\Al\alut.h
# End Source File
# End Group
# End Target
# End Project
