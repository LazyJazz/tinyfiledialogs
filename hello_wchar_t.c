/*_________
 /         \ hello_wchar_t.c v3.1.2 [Oct 2, 2017] zlib licence
 |tiny file| Hello WCHAR_T file created [November 9, 2014]
 | dialogs | Copyright (c) 2014 - 2017 Guillaume Vareille http://ysengrin.com
 \____  ___/ http://tinyfiledialogs.sourceforge.net
      \|
	         git://git.code.sf.net/p/tinyfiledialogs/code
         ____________________________________________
	    |                                            |
	    |   email: tinyfiledialogs at ysengrin.com   |
	    |____________________________________________|
                _______________________________
               |                               |
               | this file is for windows only |
               |_______________________________|
	  
Please 1) Let me know If you are using it on exotic hardware / OS / compiler
       2) If yo have a sourceforge account, leave a 3-word review on Sourceforge.
          It helps the ranking on google.

tiny file dialogs (cross-platform C C++)
InputBox PasswordBox MessageBox ColorPicker
OpenFileDialog SaveFileDialog SelectFolderDialog
Native dialog library for WINDOWS MAC OSX GTK+ QT CONSOLE & more
SSH supported via automatic switch to console mode or X11 forwarding

One C file (add it to your C or C++ project) with 7 functions:
- message & question
- notify
- input & password
- save file
- open file(s)
- select folder
- color picker

Complements OpenGL GLFW GLUT GLUI VTK SFML TGUI SDL Ogre Unity3d ION OpenCV
CEGUI MathGL GLM CPW GLOW IMGUI MyGUI GLT NGL STB & GUI less programs

NO INIT
NO MAIN LOOP
NO LINKING
NO INCLUDE

The dialogs can be forced into console mode

Windows (XP to 10) ASCII MBCS UTF-8 UTF-16
- native code & vbs create the graphic dialogs
- enhanced console mode can use dialog.exe from
http://andrear.altervista.org/home/cdialog.php
- basic console input

Unix (command line calls) ASCII UTF-8
- applescript
- zenity / matedialog / qarma (zenity for qt)
- kdialog
- Xdialog
- python2 tkinter
- dialog (opens a console if needed)
- basic console input
The same executable can run across desktops & distributions

tested with C & C++ compilers
on VisualStudio MinGW Mac Linux Bsd Solaris Minix Raspbian
using Gnome Kde Enlightenment Mate Cinnamon Unity
Lxde Lxqt Xfce WindowMaker IceWm Cde Jds OpenBox Awesome Jwm

bindings for LUA and C# dll, Haskell
included in LWJGL(java), Rust, Allegrobasic

- License -

This software is provided 'as-is', without any express or implied
warranty.  In no event will the authors be held liable for any damages
arising from the use of this software.

including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
claim that you wrote the original software.  If you use this software
in a product, an acknowledgment in the product documentation would be
appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tinyfiledialogs.h"
int main(void)
{
	int lIntValue;
	wchar_t const * lTmp;
	wchar_t const * lTheSaveFileName;
	wchar_t const * lTheOpenFileName;
	wchar_t const * lTheSelectFolderName;
	wchar_t const * lTheHexColor;
	wchar_t const * lWillBeGraphicMode;
	unsigned char lRgbColor[3];
	FILE * lIn;
	wchar_t lWcharBuff[1024];
	wchar_t lBuffer[1024];
	wchar_t lThePassword[1024];
	wchar_t const * lFilterPatterns[2] = { L"*.txt", L"*.text" };

	lWillBeGraphicMode = tinyfd_inputBoxW(L"tinyfd_query", NULL, NULL);

#ifdef _MSC_VER
#pragma warning(disable:4996) /* silences warning about strcpy strcat fopen wcscpy*/
#endif

	if (lWillBeGraphicMode)
	{
		wcscpy(lBuffer, L"graphic mode: ");
	}
	else
	{
		wcscpy(lBuffer, L"console mode: ");
	}

	mbstowcs(lWcharBuff, tinyfd_response, strlen(tinyfd_response)+1);
	wcscat(lBuffer, lWcharBuff);
	wcscpy(lThePassword, L"tinyfiledialogs v");
	mbstowcs(lWcharBuff, tinyfd_version, strlen(tinyfd_version) + 1);
	wcscat(lThePassword, lWcharBuff);
	tinyfd_messageBoxW(lThePassword, lBuffer, L"ok", L"info", 0);

	tinyfd_notifyPopupW(L"le titre", L"le message\n\tde la mort qui tue", L"info");

	/*tinyfd_forceConsole = 1;*/
	if ( lWillBeGraphicMode && ! tinyfd_forceConsole )
	{
		lIntValue = tinyfd_messageBoxW(L"Hello World",
			L"Console mode is not implemented for wchar_T UTF-16",
			L"ok", L"info", 1);
		tinyfd_forceConsole = ! lIntValue ;		
	}

	lTmp = tinyfd_inputBoxW(
		L"a password box", L"your password will be revealed", NULL);

	if (!lTmp) return 1 ;

	/* copy lTmp because saveDialog would overwrites
	inputBox static buffer in basicinput mode */

	wcscpy(lThePassword, lTmp);

	lTheSaveFileName = tinyfd_saveFileDialogW(
		L"let us save this password",
		L"passwordFile.txt",
		2,
		lFilterPatterns,
		NULL);

	if (! lTheSaveFileName)
	{
		tinyfd_messageBoxW(
			L"Error",
			L"Save file name is NULL",
			L"ok",
			L"error",
			1);
		return 1 ;
	}

	lIn = _wfopen(lTheSaveFileName, L"wt, ccs=UNICODE");
	if (!lIn)
	{
		tinyfd_messageBoxW(
			L"Error",
			L"Can not open this file in write mode",
			L"ok",
			L"error",
			1);
		return 1 ;
	}
	fputws(lThePassword, lIn);
	fclose(lIn);

	lTheOpenFileName = tinyfd_openFileDialogW(
		L"let us read the password back",
		L"",
		2,
		lFilterPatterns,
		NULL,
		0);

	if (! lTheOpenFileName)
	{
		tinyfd_messageBoxW(
			L"Error",
			L"Open file name is NULL",
			L"ok",
			L"error",
			1);
		return 1 ;
	}

	lIn = _wfopen(lTheOpenFileName, L"rt, ccs=UNICODE");

#ifdef _MSC_VER
#pragma warning(default:4996)
#endif

	if (!lIn)
	{
		tinyfd_messageBoxW(
			L"Error",
			L"Can not open this file in read mode",
			L"ok",
			L"error",
			1);
		return(1);
	}
	lBuffer[0] = '\0';
	fgetws(lBuffer, sizeof(lBuffer), lIn);
	fclose(lIn);

	tinyfd_messageBoxW(L"your password is",
			lBuffer, L"ok", L"info", 1);

	lTheSelectFolderName = tinyfd_selectFolderDialogW(
		L"let us just select a directory", NULL);

	if (!lTheSelectFolderName)
	{
		tinyfd_messageBoxW(
			L"Error",
			L"Select folder name is NULL",
			L"ok",
			L"error",
			1);
		return 1;
	}

	tinyfd_messageBoxW(L"The selected folder is",
		lTheSelectFolderName, L"ok", L"info", 1);

	lTheHexColor = tinyfd_colorChooserW(
		L"choose a nice color",
		L"#FF0077",
		lRgbColor,
		lRgbColor);

	if (!lTheHexColor)
	{
		tinyfd_messageBoxW(
			L"Error",
			L"hexcolor is NULL",
			L"ok",
			L"error",
			1);
		return 1;
	}

	tinyfd_messageBoxW(L"The selected hexcolor is",
		lTheHexColor, L"ok", L"info", 1);

	return 0;
}

/*
MinGW (needs gcc >= v4.9 otherwise some headers are incomplete):
> gcc -o hello.exe hello_wchar_t.c tinyfiledialogs.c -LC:/mingw/lib -lcomdlg32 -lole32
(unfortunately some headers are missing with tcc)

VisualStudio :
	Create a console application project,
	it links against Comdlg32.lib & Ole32.lib.
*/
