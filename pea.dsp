# Microsoft Developer Studio Project File - Name="pea" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=pea - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "pea.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "pea.mak" CFG="pea - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "pea - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "pea - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "pea - Win32 Release"

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
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE RSC /l 0x41d /d "NDEBUG"
# ADD RSC /l 0x41d /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "pea - Win32 Debug"

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
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "." /I "C:\cvs_is\infrasec\sdk\mysql\mysql-4.1.18\include" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FD /GZ /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE RSC /l 0x41d /d "_DEBUG"
# ADD RSC /l 0x41d /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wsock32.lib libmysql.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept /libpath:"C:\cvs_is\infrasec\sdk\mysql\mysql-3.23.53\lib\opt"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Desc=Copy
PostBuild_Cmds=copy debug\pea.exe \pea
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "pea - Win32 Release"
# Name "pea - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\pea_array.c
# End Source File
# Begin Source File

SOURCE=.\pea_atom.c
# End Source File
# Begin Source File

SOURCE=.\pea_class.c
# End Source File
# Begin Source File

SOURCE=.\pea_exec.c
# End Source File
# Begin Source File

SOURCE=.\pea_function.c
# End Source File
# Begin Source File

SOURCE=.\pea_hash.c
# End Source File
# Begin Source File

SOURCE=.\pea_lex.c
# End Source File
# Begin Source File

SOURCE=.\pea_lex.l

!IF  "$(CFG)" == "pea - Win32 Release"

!ELSEIF  "$(CFG)" == "pea - Win32 Debug"

# Begin Custom Build - Running flex
InputPath=.\pea_lex.l

"pea_lex.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	flex -8 -opea_lex.c $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\pea_main.c
# End Source File
# Begin Source File

SOURCE=.\pea_map.c
# End Source File
# Begin Source File

SOURCE=.\pea_mem.c
# End Source File
# Begin Source File

SOURCE=.\pea_object.c
# End Source File
# Begin Source File

SOURCE=.\pea_parse.c
# End Source File
# Begin Source File

SOURCE=.\pea_parse.y

!IF  "$(CFG)" == "pea - Win32 Release"

!ELSEIF  "$(CFG)" == "pea - Win32 Debug"

# Begin Custom Build - Running bison
InputPath=.\pea_parse.y

BuildCmds= \
	bison --verbose -d -t -opea_parse.c pea_parse.y

"pea_parse.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"pea_parse.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\pea_rtl_cgi.c
# End Source File
# Begin Source File

SOURCE=.\pea_rtl_db.c
# End Source File
# Begin Source File

SOURCE=.\pea_rtl_io.c
# End Source File
# Begin Source File

SOURCE=.\pea_rtl_lang.c
# End Source File
# Begin Source File

SOURCE=.\pea_rtl_socket.c
# End Source File
# Begin Source File

SOURCE=.\pea_segment.c
# End Source File
# Begin Source File

SOURCE=.\pea_stack.c
# End Source File
# Begin Source File

SOURCE=.\pea_stream.c
# End Source File
# Begin Source File

SOURCE=.\pea_string.c
# End Source File
# Begin Source File

SOURCE=.\pea_type.c
# End Source File
# Begin Source File

SOURCE=.\pea_util.c
# End Source File
# Begin Source File

SOURCE=.\pea_variable.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\pea.h
# End Source File
# Begin Source File

SOURCE=.\pea_array.h
# End Source File
# Begin Source File

SOURCE=.\pea_atom.h
# End Source File
# Begin Source File

SOURCE=.\pea_class.h
# End Source File
# Begin Source File

SOURCE=.\pea_function.h
# End Source File
# Begin Source File

SOURCE=.\pea_hash.h
# End Source File
# Begin Source File

SOURCE=.\pea_map.h
# End Source File
# Begin Source File

SOURCE=.\pea_mem.h
# End Source File
# Begin Source File

SOURCE=.\pea_object.h
# End Source File
# Begin Source File

SOURCE=.\pea_op.h
# End Source File
# Begin Source File

SOURCE=.\pea_parse.h
# End Source File
# Begin Source File

SOURCE=.\pea_rtl.h
# End Source File
# Begin Source File

SOURCE=.\pea_segment.h
# End Source File
# Begin Source File

SOURCE=.\pea_stack.h
# End Source File
# Begin Source File

SOURCE=.\pea_stream.h
# End Source File
# Begin Source File

SOURCE=.\pea_string.h
# End Source File
# Begin Source File

SOURCE=.\pea_variable.h
# End Source File
# Begin Source File

SOURCE=.\unistd.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Source File

SOURCE=.\2do.txt
# End Source File
# Begin Source File

SOURCE=.\index.pea
# End Source File
# Begin Source File

SOURCE=.\makefile
# End Source File
# Begin Source File

SOURCE=.\notepad.txt
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\test.pea
# End Source File
# End Target
# End Project
