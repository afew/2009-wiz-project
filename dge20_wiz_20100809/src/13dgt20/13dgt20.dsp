# Microsoft Developer Studio Project File - Name="13dgt20" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=13dgt20 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "13dgt20.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "13dgt20.mak" CFG="13dgt20 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "13dgt20 - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "13dgt20 - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "13dgt20 - Win32 Release"

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
# ADD LIB32 /nologo /out:"..\..\lib\3dgt20.lib"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy      DGT_Util.h      ..\..\include\     	copy      DGT_Lzo.h      ..\..\include\     	copy      DGT_DRM.h      ..\..\include\     	copy      DGT_SpriteMx.h      ..\..\include\   	copy      DGT_VKB.h      ..\..\include\ 
# End Special Build Tool

!ELSEIF  "$(CFG)" == "13dgt20 - Win32 Debug"

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
# ADD LIB32 /nologo /out:"..\..\lib\dgt20_.lib"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy      DGT_Util.h      ..\..\include\     	copy      DGT_Lzo.h      ..\..\include\     	copy      DGT_DRM.h      ..\..\include\     	copy      DGT_SpriteMx.h      ..\..\include\   	copy      DGT_VKB.h      ..\..\include\ 
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "13dgt20 - Win32 Release"
# Name "13dgt20 - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\DGT_DRM.cpp
# End Source File
# Begin Source File

SOURCE=.\DGT_Lzo.c
# End Source File
# Begin Source File

SOURCE=.\DGT_SpriteMx.cpp
# End Source File
# Begin Source File

SOURCE=.\DGT_Util.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\DGT_DRM.h
# End Source File
# Begin Source File

SOURCE=.\DGT_Lzo.h
# End Source File
# Begin Source File

SOURCE=.\DGT_SpriteMx.h
# End Source File
# Begin Source File

SOURCE=.\DGT_Util.h
# End Source File
# Begin Source File

SOURCE=.\DGT_VKB.h
# End Source File
# End Group
# Begin Group "lzo"

# PROP Default_Filter "c;cpp;h;"
# Begin Source File

SOURCE=.\lzo\compr1b.h
# End Source File
# Begin Source File

SOURCE=.\lzo\compr1c.h
# End Source File
# Begin Source File

SOURCE=.\lzo\config1.h
# End Source File
# Begin Source File

SOURCE=.\lzo\config1a.h
# End Source File
# Begin Source File

SOURCE=.\lzo\config1b.h
# End Source File
# Begin Source File

SOURCE=.\lzo\config1c.h
# End Source File
# Begin Source File

SOURCE=.\lzo\config1f.h
# End Source File
# Begin Source File

SOURCE=.\lzo\config1x.h
# End Source File
# Begin Source File

SOURCE=.\lzo\config1y.h
# End Source File
# Begin Source File

SOURCE=.\lzo\config1z.h
# End Source File
# Begin Source File

SOURCE=.\lzo\config2a.h
# End Source File
# Begin Source File

SOURCE=.\lzo\lzo1.c
# End Source File
# Begin Source File

SOURCE=.\lzo\lzo1_99.c
# End Source File
# Begin Source File

SOURCE=.\lzo\lzo1_cm.ch
# End Source File
# Begin Source File

SOURCE=.\lzo\lzo1_d.ch
# End Source File
# Begin Source File

SOURCE=.\lzo\lzo1a.c
# End Source File
# Begin Source File

SOURCE=.\lzo\lzo1a_99.c
# End Source File
# Begin Source File

SOURCE=.\lzo\lzo1a_cm.ch
# End Source File
# Begin Source File

SOURCE=.\lzo\lzo1a_cr.ch
# End Source File
# Begin Source File

SOURCE=.\lzo\lzo1a_de.h
# End Source File
# Begin Source File

SOURCE=.\lzo\lzo1b_1.c
# End Source File
# Begin Source File

SOURCE=.\lzo\lzo1b_2.c
# End Source File
# Begin Source File

SOURCE=.\lzo\lzo1b_3.c
# End Source File
# Begin Source File

SOURCE=.\lzo\lzo1b_4.c
# End Source File
# Begin Source File

SOURCE=.\lzo\lzo1b_5.c
# End Source File
# Begin Source File

SOURCE=.\lzo\lzo1b_6.c
# End Source File
# Begin Source File

SOURCE=.\lzo\lzo1b_7.c
# End Source File
# Begin Source File

SOURCE=.\lzo\lzo1b_8.c
# End Source File
# Begin Source File

SOURCE=.\lzo\lzo1b_9.c
# End Source File
# Begin Source File

SOURCE=.\lzo\lzo1b_99.c
# End Source File
# Begin Source File

SOURCE=.\lzo\lzo1b_9x.c
# End Source File
# Begin Source File

SOURCE=.\lzo\lzo1b_c.ch
# End Source File
# Begin Source File

SOURCE=.\lzo\lzo1b_cc.c
# End Source File
# Begin Source File

SOURCE=.\lzo\lzo1b_cc.h
# End Source File
# Begin Source File

SOURCE=.\lzo\lzo1b_cm.ch
# End Source File
# Begin Source File

SOURCE=.\lzo\lzo1b_cr.ch
# End Source File
# Begin Source File

SOURCE=.\lzo\lzo1b_d.ch
# End Source File
# Begin Source File

SOURCE=.\lzo\lzo1b_d1.c
# End Source File
# Begin Source File

SOURCE=.\lzo\lzo1b_d2.c
# End Source File
# Begin Source File

SOURCE=.\lzo\lzo1b_de.h
# End Source File
# Begin Source File

SOURCE=.\lzo\lzo1b_r.ch
# End Source File
# Begin Source File

SOURCE=.\lzo\lzo1b_rr.c
# End Source File
# Begin Source File

SOURCE=.\lzo\lzo1b_sm.ch
# End Source File
# Begin Source File

SOURCE=.\lzo\lzo1b_tm.ch
# End Source File
# Begin Source File

SOURCE=.\lzo\lzo1b_xx.c
# End Source File
# Begin Source File

SOURCE=.\lzo\lzo1c_1.c
# End Source File
# Begin Source File

SOURCE=.\lzo\lzo1c_2.c
# End Source File
# Begin Source File

SOURCE=.\lzo\lzo1c_3.c
# End Source File
# Begin Source File

SOURCE=.\lzo\lzo1c_4.c
# End Source File
# Begin Source File

SOURCE=.\lzo\lzo1c_5.c
# End Source File
# Begin Source File

SOURCE=.\lzo\lzo1c_6.c
# End Source File
# Begin Source File

SOURCE=.\lzo\lzo1c_7.c
# End Source File
# Begin Source File

SOURCE=.\lzo\lzo1c_8.c
# End Source File
# Begin Source File

SOURCE=.\lzo\lzo1c_9.c
# End Source File
# Begin Source File

SOURCE=.\lzo\lzo1c_99.c
# End Source File
# Begin Source File

SOURCE=.\lzo\lzo1c_9x.c
# End Source File
# Begin Source File

SOURCE=.\lzo\lzo1c_cc.c
# End Source File
# Begin Source File

SOURCE=.\lzo\lzo1c_cc.h
# End Source File
# Begin Source File

SOURCE=.\lzo\lzo1c_d1.c
# End Source File
# Begin Source File

SOURCE=.\lzo\lzo1c_d2.c
# End Source File
# Begin Source File

SOURCE=.\lzo\lzo1c_rr.c
# End Source File
# Begin Source File

SOURCE=.\lzo\lzo1c_xx.c
# End Source File
# Begin Source File

SOURCE=.\lzo\lzo1f_1.c
# End Source File
# Begin Source File

SOURCE=.\lzo\lzo1f_9x.c
# End Source File
# Begin Source File

SOURCE=.\lzo\lzo1f_d.ch
# End Source File
# Begin Source File

SOURCE=.\lzo\lzo1f_d1.c
# End Source File
# Begin Source File

SOURCE=.\lzo\lzo1f_d2.c
# End Source File
# Begin Source File

SOURCE=.\lzo\lzo1x_1.c
# End Source File
# Begin Source File

SOURCE=.\lzo\lzo1x_1k.c
# End Source File
# Begin Source File

SOURCE=.\lzo\lzo1x_1l.c
# End Source File
# Begin Source File

SOURCE=.\lzo\lzo1x_1o.c
# End Source File
# Begin Source File

SOURCE=.\lzo\lzo1x_9x.c
# End Source File
# Begin Source File

SOURCE=.\lzo\lzo1x_c.ch
# End Source File
# Begin Source File

SOURCE=.\lzo\lzo1x_d.ch
# End Source File
# Begin Source File

SOURCE=.\lzo\lzo1x_d1.c
# End Source File
# Begin Source File

SOURCE=.\lzo\lzo1x_d2.c
# End Source File
# Begin Source File

SOURCE=.\lzo\lzo1x_d3.c
# End Source File
# Begin Source File

SOURCE=.\lzo\lzo1x_o.c
# End Source File
# Begin Source File

SOURCE=.\lzo\lzo1x_oo.ch
# End Source File
# Begin Source File

SOURCE=.\lzo\lzo1y_1.c
# End Source File
# Begin Source File

SOURCE=.\lzo\lzo1y_9x.c
# End Source File
# Begin Source File

SOURCE=.\lzo\lzo1y_d1.c
# End Source File
# Begin Source File

SOURCE=.\lzo\lzo1y_d2.c
# End Source File
# Begin Source File

SOURCE=.\lzo\lzo1y_d3.c
# End Source File
# Begin Source File

SOURCE=.\lzo\lzo1y_o.c
# End Source File
# Begin Source File

SOURCE=.\lzo\lzo1z_9x.c
# End Source File
# Begin Source File

SOURCE=.\lzo\lzo1z_d1.c
# End Source File
# Begin Source File

SOURCE=.\lzo\lzo1z_d2.c
# End Source File
# Begin Source File

SOURCE=.\lzo\lzo1z_d3.c
# End Source File
# Begin Source File

SOURCE=.\lzo\lzo2a_9x.c
# End Source File
# Begin Source File

SOURCE=.\lzo\lzo2a_d.ch
# End Source File
# Begin Source File

SOURCE=.\lzo\lzo2a_d1.c
# End Source File
# Begin Source File

SOURCE=.\lzo\lzo2a_d2.c
# End Source File
# Begin Source File

SOURCE=.\lzo\lzo_conf.h
# End Source File
# Begin Source File

SOURCE=.\lzo\lzo_crc.c
# End Source File
# Begin Source File

SOURCE=.\lzo\lzo_dict.h
# End Source File
# Begin Source File

SOURCE=.\lzo\lzo_dll.ch
# End Source File
# Begin Source File

SOURCE=.\lzo\lzo_init.c
# End Source File
# Begin Source File

SOURCE=.\lzo\lzo_mchw.ch
# End Source File
# Begin Source File

SOURCE=.\lzo\lzo_ptr.c
# End Source File
# Begin Source File

SOURCE=.\lzo\lzo_ptr.h
# End Source File
# Begin Source File

SOURCE=.\lzo\lzo_str.c
# End Source File
# Begin Source File

SOURCE=.\lzo\lzo_swd.ch
# End Source File
# Begin Source File

SOURCE=.\lzo\lzo_util.c
# End Source File
# Begin Source File

SOURCE=.\lzo\miniacc.h
# End Source File
# Begin Source File

SOURCE=.\lzo\stats1a.h
# End Source File
# Begin Source File

SOURCE=.\lzo\stats1b.h
# End Source File
# Begin Source File

SOURCE=.\lzo\stats1c.h
# End Source File
# End Group
# Begin Group "vkb"

# PROP Default_Filter "cpp;h;"
# Begin Source File

SOURCE=.\vkb\Automata.cpp
# End Source File
# Begin Source File

SOURCE=.\vkb\Automata.h
# End Source File
# Begin Source File

SOURCE=.\vkb\VirtualKeyboard.cpp
# End Source File
# Begin Source File

SOURCE=.\vkb\VirtualKeyboard.h
# End Source File
# End Group
# End Target
# End Project
