# Microsoft Developer Studio Project File - Name="ProjectRobot" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=ProjectRobot - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ProjectRobot.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ProjectRobot.mak" CFG="ProjectRobot - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ProjectRobot - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "ProjectRobot - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ProjectRobot - Win32 Release"

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
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib Msimg32.lib comctl32.lib shlwapi.lib winmm.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "ProjectRobot - Win32 Debug"

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
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib Msimg32.lib comctl32.lib shlwapi.lib winmm.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "ProjectRobot - Win32 Release"
# Name "ProjectRobot - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\_GSShared\CollisionUtils.cpp
# End Source File
# Begin Source File

SOURCE=..\_GSShared\GameButton.cpp
# End Source File
# Begin Source File

SOURCE=..\_GSShared\GameFont.cpp
# End Source File
# Begin Source File

SOURCE=..\_GSShared\GameListBox.cpp
# End Source File
# Begin Source File

SOURCE=..\_GSShared\GameObj.cpp
# End Source File
# Begin Source File

SOURCE=..\_GSShared\GameScrollBar.cpp
# End Source File
# Begin Source File

SOURCE=..\_GSShared\Img.cpp
# End Source File
# Begin Source File

SOURCE=..\_GSShared\LinkedList.cpp
# End Source File
# Begin Source File

SOURCE=.\PopupWindow.cpp
# End Source File
# Begin Source File

SOURCE=.\ProjectRobot.cpp
# End Source File
# Begin Source File

SOURCE=.\ProjectRobot.rc
# End Source File
# Begin Source File

SOURCE=.\ProjectRobot_Fonts.cpp
# End Source File
# Begin Source File

SOURCE=..\_GSShared\random.cpp
# End Source File
# Begin Source File

SOURCE=.\Score.cpp
# End Source File
# Begin Source File

SOURCE=.\Screen_Ask.cpp
# End Source File
# Begin Source File

SOURCE=.\Screen_Change_SubSystem.cpp
# End Source File
# Begin Source File

SOURCE=.\Screen_End_Turn.cpp
# End Source File
# Begin Source File

SOURCE=.\Screen_Help.cpp
# End Source File
# Begin Source File

SOURCE=.\Screen_Info.cpp
# End Source File
# Begin Source File

SOURCE=.\Screen_Intro.cpp
# End Source File
# Begin Source File

SOURCE=.\Screen_Stakeholders.cpp
# End Source File
# Begin Source File

SOURCE=.\Screen_SystemDesign.cpp
# End Source File
# Begin Source File

SOURCE=.\Screen_Title.cpp
# End Source File
# Begin Source File

SOURCE=.\ScreenExtras.cpp
# End Source File
# Begin Source File

SOURCE=..\_GSShared\Sound.cpp
# End Source File
# Begin Source File

SOURCE=..\_GSShared\Sprite.cpp
# End Source File
# Begin Source File

SOURCE=.\Stakeholder.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\System_Development.cpp
# End Source File
# Begin Source File

SOURCE=.\System_Fielded.cpp
# End Source File
# Begin Source File

SOURCE=.\System_Models.cpp
# End Source File
# Begin Source File

SOURCE=.\System_Overall.cpp
# End Source File
# Begin Source File

SOURCE=.\System_Restrictions.cpp
# End Source File
# Begin Source File

SOURCE=.\TextDefines.cpp
# End Source File
# Begin Source File

SOURCE=..\_GSShared\Utilities.cpp
# End Source File
# Begin Source File

SOURCE=..\_GSShared\winobj.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\_GSShared\CollisionUtils.h
# End Source File
# Begin Source File

SOURCE=..\_GSShared\GameButton.h
# End Source File
# Begin Source File

SOURCE=..\_GSShared\GameFont.h
# End Source File
# Begin Source File

SOURCE=..\_GSShared\GameListBox.h
# End Source File
# Begin Source File

SOURCE=..\_GSShared\GameObj.h
# End Source File
# Begin Source File

SOURCE=..\_GSShared\GameScrollBar.h
# End Source File
# Begin Source File

SOURCE=..\_GSShared\Img.h
# End Source File
# Begin Source File

SOURCE=..\_GSShared\LinkedList.h
# End Source File
# Begin Source File

SOURCE=.\PopupWindow.h
# End Source File
# Begin Source File

SOURCE=.\ProjectRobot.h
# End Source File
# Begin Source File

SOURCE=.\Records.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\Score.h
# End Source File
# Begin Source File

SOURCE=.\Screen_Ask.h
# End Source File
# Begin Source File

SOURCE=.\Screen_Change_SubSystem.h
# End Source File
# Begin Source File

SOURCE=.\Screen_End_Turn.h
# End Source File
# Begin Source File

SOURCE=.\Screen_Help.h
# End Source File
# Begin Source File

SOURCE=.\Screen_Info.h
# End Source File
# Begin Source File

SOURCE=.\Screen_Intro.h
# End Source File
# Begin Source File

SOURCE=.\Screen_Stakeholders.h
# End Source File
# Begin Source File

SOURCE=.\Screen_SystemDesign.h
# End Source File
# Begin Source File

SOURCE=.\Screen_Title.h
# End Source File
# Begin Source File

SOURCE=.\ScreenExtras.h
# End Source File
# Begin Source File

SOURCE=..\_GSShared\Sound.h
# End Source File
# Begin Source File

SOURCE=..\_GSShared\Sprite.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\SubScreen.h
# End Source File
# Begin Source File

SOURCE=.\System_Development.h
# End Source File
# Begin Source File

SOURCE=.\System_Fielded.h
# End Source File
# Begin Source File

SOURCE=.\System_Models.h
# End Source File
# Begin Source File

SOURCE=.\System_Overall.h
# End Source File
# Begin Source File

SOURCE=.\System_Restrictions.h
# End Source File
# Begin Source File

SOURCE=.\TextDefines.h
# End Source File
# Begin Source File

SOURCE=..\_GSShared\Utilities.h
# End Source File
# Begin Source File

SOURCE=..\_GSShared\winobj.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\Button_Plus_Silver.bmp
# End Source File
# Begin Source File

SOURCE=.\res\button_sprite.bmp
# End Source File
# Begin Source File

SOURCE=.\res\button_sprite_3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\button_sprite_4.bmp
# End Source File
# Begin Source File

SOURCE=.\res\button_sprite_5.bmp
# End Source File
# Begin Source File

SOURCE=.\res\button_sprite_6.bmp
# End Source File
# Begin Source File

SOURCE=.\res\button_sprite_for_subscreen_text.bmp
# End Source File
# Begin Source File

SOURCE=.\res\button_sprite_for_text.bmp
# End Source File
# Begin Source File

SOURCE=.\res\button_sprite_for_text_2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\button_sprite_for_text_3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\button_sprite_for_text_4.bmp
# End Source File
# Begin Source File

SOURCE=.\res\button_sprite_long.bmp
# End Source File
# Begin Source File

SOURCE=.\res\button_sprite_overview.bmp
# End Source File
# Begin Source File

SOURCE=.\res\button_sprite_plus.bmp
# End Source File
# Begin Source File

SOURCE=.\res\button_sprite_switch.bmp
# End Source File
# Begin Source File

SOURCE=.\res\EndTurnPanel.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GiantRobot.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GridBackground.bmp
# End Source File
# Begin Source File

SOURCE=".\res\InfoPanel - Large.bmp"
# End Source File
# Begin Source File

SOURCE=.\res\InfoPanel.bmp
# End Source File
# Begin Source File

SOURCE=.\res\InfoPanel2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Popup_Window.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ProjectRobot.ico
# End Source File
# Begin Source File

SOURCE=.\res\ProjectRobotFont.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ProjectRobotFont10.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ProjectRobotFont11.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ProjectRobotFont12.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ProjectRobotFont13.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ProjectRobotFont14.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ProjectRobotFont15.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ProjectRobotFont16.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ProjectRobotFont2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ProjectRobotFont3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ProjectRobotFont4.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ProjectRobotFont5.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ProjectRobotFont6.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ProjectRobotFont7.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ProjectRobotFont8.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ProjectRobotFont9.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ProjectRobotLogo.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ResourceWindow.bmp
# End Source File
# Begin Source File

SOURCE=.\res\small.ico
# End Source File
# Begin Source File

SOURCE=.\res\Sprite_Overlay.bmp
# End Source File
# Begin Source File

SOURCE=.\res\TitleBackground.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\res\sound\BEEP1C.WAV
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\res\sound\snd_back.wav
# End Source File
# Begin Source File

SOURCE=.\res\sound\snd_click3.wav
# End Source File
# Begin Source File

SOURCE=.\res\sound\snd_info.wav
# End Source File
# Begin Source File

SOURCE=.\res\sound\snd_pick.wav
# End Source File
# Begin Source File

SOURCE=.\res\sound\snd_smallclick.wav
# End Source File
# Begin Source File

SOURCE=.\res\sound\snd_smallclick_2.wav
# End Source File
# Begin Source File

SOURCE=.\res\sound\snd_smallclick_3.wav
# End Source File
# Begin Source File

SOURCE=.\res\sound\snd_takeoff.wav
# End Source File
# Begin Source File

SOURCE=.\res\sound\snd_tick.wav
# End Source File
# End Target
# End Project
