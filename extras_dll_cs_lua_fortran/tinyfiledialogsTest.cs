/*_________
 /         \ tinyfiledialogsTest.cs v3.6.2 [May 9, 2020] zlib licence
 |tiny file| C# bindings created [2015]
 | dialogs | Copyright (c) 2014 - 2020 Guillaume Vareille http://ysengrin.com
 \____  ___/ http://tinyfiledialogs.sourceforge.net
      \|     git clone http://git.code.sf.net/p/tinyfiledialogs/code tinyfd
         ____________________________________________
	    |                                            |
	    |   email: tinyfiledialogs at ysengrin.com   |
	    |____________________________________________|

If you like tinyfiledialogs, please upvote my stackoverflow answer
https://stackoverflow.com/a/47651444
*/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

class tinyfd
{
    // cross platform UTF8
    [DllImport("C:\\Users\\frogs\\yomspace2015\\yomlibs\\tinyfd\\tinyfiledialogs32.dll",
        CallingConvention = CallingConvention.Cdecl)]
    public static extern void tinyfd_beep();
    [DllImport("C:\\Users\\frogs\\yomspace2015\\yomlibs\\tinyfd\\tinyfiledialogs32.dll",
        CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
    public static extern int tinyfd_notifyPopup(string aTitle, string aMessage, string aIconType);
    [DllImport("C:\\Users\\frogs\\yomspace2015\\yomlibs\\tinyfd\\tinyfiledialogs32.dll",
        CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
    public static extern int tinyfd_messageBox(string aTitle, string aMessage, string aDialogTyle, string aIconType, int aDefaultButton);
    [DllImport("C:\\Users\\frogs\\yomspace2015\\yomlibs\\tinyfd\\tinyfiledialogs32.dll",
        CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
    public static extern IntPtr tinyfd_inputBox(string aTitle, string aMessage, string aDefaultInput);
    [DllImport("C:\\Users\\frogs\\yomspace2015\\yomlibs\\tinyfd\\tinyfiledialogs32.dll",
        CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
    public static extern IntPtr tinyfd_saveFileDialog(string aTitle, string aDefaultPathAndFile, int aNumOfFilterPatterns, string[] aFilterPatterns, string aSingleFilterDescription);
    [DllImport("C:\\Users\\frogs\\yomspace2015\\yomlibs\\tinyfd\\tinyfiledialogs32.dll",
        CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
    public static extern IntPtr tinyfd_openFileDialog(string aTitle, string aDefaultPathAndFile, int aNumOfFilterPatterns, string[] aFilterPatterns, string aSingleFilterDescription, int aAllowMultipleSelects);
    [DllImport("C:\\Users\\frogs\\yomspace2015\\yomlibs\\tinyfd\\tinyfiledialogs32.dll",
        CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
    public static extern IntPtr tinyfd_selectFolderDialog(string aTitle, string aDefaultPathAndFile);
    [DllImport("C:\\Users\\frogs\\yomspace2015\\yomlibs\\tinyfd\\tinyfiledialogs32.dll",
        CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
    public static extern IntPtr tinyfd_colorChooser(string aTitle, string aDefaultHexRGB, byte[] aDefaultRGB, byte[] aoResultRGB);

    // windows only utf16
    [DllImport("C:\\Users\\frogs\\yomspace2015\\yomlibs\\tinyfd\\tinyfiledialogs32.dll",
        CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
    public static extern int tinyfd_notifyPopupW(string aTitle, string aMessage, string aIconType);
    [DllImport("C:\\Users\\frogs\\yomspace2015\\yomlibs\\tinyfd\\tinyfiledialogs32.dll",
        CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
    public static extern int tinyfd_messageBoxW(string aTitle, string aMessage, string aDialogTyle, string aIconType, int aDefaultButton);
    [DllImport("C:\\Users\\frogs\\yomspace2015\\yomlibs\\tinyfd\\tinyfiledialogs32.dll",
        CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
    public static extern IntPtr tinyfd_inputBoxW(string aTitle, string aMessage, string aDefaultInput);
    [DllImport("C:\\Users\\frogs\\yomspace2015\\yomlibs\\tinyfd\\tinyfiledialogs32.dll",
        CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
    public static extern IntPtr tinyfd_saveFileDialogW(string aTitle, string aDefaultPathAndFile, int aNumOfFilterPatterns, string[] aFilterPatterns, string aSingleFilterDescription);
    [DllImport("C:\\Users\\frogs\\yomspace2015\\yomlibs\\tinyfd\\tinyfiledialogs32.dll",
        CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
    public static extern IntPtr tinyfd_openFileDialogW(string aTitle, string aDefaultPathAndFile, int aNumOfFilterPatterns, string[] aFilterPatterns, string aSingleFilterDescription, int aAllowMultipleSelects);
    [DllImport("C:\\Users\\frogs\\yomspace2015\\yomlibs\\tinyfd\\tinyfiledialogs32.dll",
        CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
    public static extern IntPtr tinyfd_selectFolderDialogW(string aTitle, string aDefaultPathAndFile);
    [DllImport("C:\\Users\\frogs\\yomspace2015\\yomlibs\\tinyfd\\tinyfiledialogs32.dll",
        CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
    public static extern IntPtr tinyfd_colorChooserW(string aTitle, string aDefaultHexRGB, byte[] aDefaultRGB, byte[] aoResultRGB);
}

namespace ConsoleApplication1
{
    class tinyfiledialogsTest
    {
        private static string stringFromAnsi(IntPtr ptr) // for UTF-8/char
        {
            return System.Runtime.InteropServices.Marshal.PtrToStringAnsi(ptr);
        }

        private static string stringFromUni(IntPtr ptr) // for UTF-16/wchar_t
        {
            return System.Runtime.InteropServices.Marshal.PtrToStringUni(ptr);
        }

        static void Main(string[] args)
        {                                         
            // cross platform utf-8
            IntPtr lTheInputText = tinyfd.tinyfd_inputBox("input box", "gimme a string", "A text to input");
            string lTheInputString = stringFromAnsi(lTheInputText);
            int lala = tinyfd.tinyfd_messageBox("a message box char", lTheInputString, "ok", "warning", 1);
            tinyfd.tinyfd_notifyPopup("there is no error (even if it is an error icon)", lTheInputString, "error");

            // windows only utf-16
            IntPtr lAnotherInputTextW = tinyfd.tinyfd_inputBoxW("input box", "gimme another string", "Another text to input");
            string lAnotherInputString = stringFromUni(lAnotherInputTextW);
            int lili = tinyfd.tinyfd_messageBoxW("a message box wchar_t", lAnotherInputString, "ok", "info", 1);
            tinyfd.tinyfd_notifyPopupW("there is no error (even if it is an error icon)", lAnotherInputString, "error");

            tinyfd.tinyfd_beep();        
        }
    }
}
