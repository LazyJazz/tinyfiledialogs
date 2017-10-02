/*_________
 /         \ hello.c v3.1.2 [Oct 2, 2017] zlib licence
 |tiny file| Hello World file created [November 9, 2014]
 | dialogs | Copyright (c) 2014 - 2017 Guillaume Vareille http://ysengrin.com
 \____  ___/ http://tinyfiledialogs.sourceforge.net
      \|
	         git://git.code.sf.net/p/tinyfiledialogs/code
		 ____________________________________________
		|                                            |
		|   email: tinyfiledialogs at ysengrin.com   |
		|____________________________________________|
	 _________________________________________________________________
    |                                                                 |
    | this file is for windows and unix (osx linux, bsd, solaris ...) |
    |_________________________________________________________________|
	  
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


/*
- Here is the Hello World:
    if a console is missing, it will use graphic dialogs
    if a graphical display is absent, it will use console dialogs
		(on windows the input box may take some time to open the first time)
*/


#include <stdio.h>
#include <string.h>
#include "tinyfiledialogs.h"
int main(void)
{
	int lIntValue;
	char const * lTmp;
	char const * lTheSaveFileName;
	char const * lTheOpenFileName;
	char const * lTheSelectFolderName;
	char const * lTheHexColor;
	char const * lWillBeGraphicMode;
	unsigned char lRgbColor[3];
	FILE * lIn;
	char lBuffer[1024];
	char lThePassword[1024];
	char const * lFilterPatterns[2] = { "*.txt", "*.text" };

#ifdef _WIN32
	tinyfd_winUtf8 = 0; /* on windows, you decide if char holds MBCS(0) or UTF8(1) */
#endif

	lWillBeGraphicMode = tinyfd_inputBox("tinyfd_query", NULL, NULL);

#ifdef _MSC_VER
#pragma warning(disable:4996) /* silences warning about strcpy strcat fopen*/
#endif

	if (lWillBeGraphicMode)
	{
		strcpy(lBuffer, "graphic mode: ");
	}
	else
	{
		strcpy(lBuffer, "console mode: ");
	}

	strcat(lBuffer, tinyfd_response);
	strcpy(lThePassword, "v");
	strcat(lThePassword, tinyfd_version);
	strcat(lThePassword, " tinyfiledialogs");
	tinyfd_messageBox(lThePassword, lBuffer, "ok", "info", 0);

	tinyfd_notifyPopup("the title", "the message\n\tfrom outer-space", "info");

	/*tinyfd_forceConsole = 1;*/
	if ( lWillBeGraphicMode && ! tinyfd_forceConsole )
	{
		lIntValue = tinyfd_messageBox("Hello World",
			"graphic dialogs [yes] / console mode [no]?",
			"yesno", "question", 1);
		tinyfd_forceConsole = ! lIntValue ;
		
		/*lIntValue = tinyfd_messageBox("Hello World",
			"graphic dialogs [yes] / console mode [no]?",
			"yesnocancel", "question", 1);
		tinyfd_forceConsole = (lIntValue == 2);*/
	}

	lTmp = tinyfd_inputBox(
		"a password box", "your password will be revealed", NULL);

	if (!lTmp) return 1 ;

	/* copy lTmp because saveDialog would overwrites
	inputBox static buffer in basicinput mode */

	strcpy(lThePassword, lTmp);

	lTheSaveFileName = tinyfd_saveFileDialog(
		"let us save this password",
		"passwordFile.txt",
		2,
		lFilterPatterns,
		NULL);

	if (! lTheSaveFileName)
	{
		tinyfd_messageBox(
			"Error",
			"Save file name is NULL",
			"ok",
			"error",
			1);
		return 1 ;
	}

	lIn = fopen(lTheSaveFileName, "w");
	if (!lIn)
	{
		tinyfd_messageBox(
			"Error",
			"Can not open this file in write mode",
			"ok",
			"error",
			1);
		return 1 ;
	}
	fputs(lThePassword, lIn);
	fclose(lIn);

	lTheOpenFileName = tinyfd_openFileDialog(
		"let us read the password back",
		"",
		2,
		lFilterPatterns,
		NULL,
		0);

	if (! lTheOpenFileName)
	{
		tinyfd_messageBox(
			"Error",
			"Open file name is NULL",
			"ok",
			"error",
			1);
		return 1 ;
	}

	lIn = fopen(lTheOpenFileName, "r");

#ifdef _MSC_VER
#pragma warning(default:4996)
#endif

	if (!lIn)
	{
		tinyfd_messageBox(
			"Error",
			"Can not open this file in read mode",
			"ok",
			"error",
			1);
		return(1);
	}
	lBuffer[0] = '\0';
	fgets(lBuffer, sizeof(lBuffer), lIn);
	fclose(lIn);

	tinyfd_messageBox("your password is",
			lBuffer, "ok", "info", 1);

	lTheSelectFolderName = tinyfd_selectFolderDialog(
		"let us just select a directory", NULL);

	if (!lTheSelectFolderName)
	{
		tinyfd_messageBox(
			"Error",
			"Select folder name is NULL",
			"ok",
			"error",
			1);
		return 1;
	}

	tinyfd_messageBox("The selected folder is",
		lTheSelectFolderName, "ok", "info", 1);

	lTheHexColor = tinyfd_colorChooser(
		"choose a nice color",
		"#FF0077",
		lRgbColor,
		lRgbColor);

	if (!lTheHexColor)
	{
		tinyfd_messageBox(
			"Error",
			"hexcolor is NULL",
			"ok",
			"error",
			1);
		return 1;
	}

	tinyfd_messageBox("The selected hexcolor is",
		lTheHexColor, "ok", "info", 1);

	return 0;
}

/*
OSX :
$ gcc -o hello.app hello.c tinyfiledialogs.c

UNIX :
$ gcc -o hello hello.c tinyfiledialogs.c
( or clang tcc cc CC )

MinGW (needs gcc >= v4.9 otherwise some headers are incomplete):
> gcc -o hello.exe hello.c tinyfiledialogs.c -LC:/mingw/lib -lcomdlg32 -lole32
(unfortunately some headers are missing with tcc)

VisualStudio :
	Create a console application project,
	it links against Comdlg32.lib & Ole32.lib.
*/
