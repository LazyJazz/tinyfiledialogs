/*_________
 /         \ tinyfiledialogs v3.6.5 [Sep 22, 2020] zlib licence
 |tiny file| 
 | dialogs | Copyright (c) 2014 - 2020 Guillaume Vareille http://ysengrin.com
 \____  ___/ http://tinyfiledialogs.sourceforge.net
      \|     git clone http://git.code.sf.net/p/tinyfiledialogs/code tinyfd

 - License -
 This software is provided 'as-is', without any express or implied
 warranty.  In no event will the authors be held liable for any damages
 arising from the use of this software.
 Permission is granted to anyone to use this software for any purpose,
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tinyfiledialogs.h"

#define MAX_PATH_OR_CMD 1024 /* _MAX_PATH or MAX_PATH */
void replaceSubStr( char const * aSource ,char const * aOldSubStr ,
				   char const * aNewSubStr ,char * aoDestination );
#ifndef _WIN32
int isDarwin(void);
int kdialogPresent(void);
int matedialogPresent(void);
int qarmaPresent(void);
int shellementaryPresent(void);
int zenityPresent(void);
int zenity3Present(void);
#endif /*_WIN32 */


/* not cross platform - unix zenity only */
/* contributed by Attila Dusnoki */
#ifndef _WIN32
char * tinyfd_arrayDialog(
        char const * aTitle , /* "" */
        int aNumOfColumns , /* 2 */
        char const * const * aColumns , /* {"Column 1","Column 2"} */
        int aNumOfRows , /* 2 */
        char const * const * aCells )
                /* {"Row1 Col1","Row1 Col2","Row2 Col1","Row2 Col2"} */
{
        static char lBuff [MAX_PATH_OR_CMD] ;
        char lDialogString [MAX_PATH_OR_CMD] ;
        FILE * lIn ;
        int i ;

        lBuff[0]='\0';

        if ( zenityPresent() || matedialogPresent() || shellementaryPresent() || qarmaPresent() )
        {
                if ( zenityPresent() )
                {
                        if (aTitle&&!strcmp(aTitle,"tinyfd_query")){strcpy(tinyfd_response,"zenity");return (char *)1;}
                        strcpy( lDialogString , "zenity" ) ;
                        if ( (zenity3Present() >= 4) && !getenv("SSH_TTY") )
                        {
                                strcat( lDialogString, " --attach=$(sleep .01;xprop -root 32x '\t$0' _NET_ACTIVE_WINDOW | cut -f 2)"); /* contribution: Paul Rouget */
                        }
                }
                else if ( matedialogPresent() )
                {
                        if (aTitle&&!strcmp(aTitle,"tinyfd_query")){strcpy(tinyfd_response,"matedialog");return (char *)1;}
                        strcpy( lDialogString , "matedialog" ) ;
                }
                else if ( shellementaryPresent() )
                {
                        if (aTitle&&!strcmp(aTitle,"tinyfd_query")){strcpy(tinyfd_response,"shellementary");return (char *)1;}
                        strcpy( lDialogString , "shellementary" ) ;
                }
                else
                {
                        if (aTitle&&!strcmp(aTitle,"tinyfd_query")){strcpy(tinyfd_response,"qarma");return (char *)1;}
                        strcpy( lDialogString , "qarma" ) ;
                        if ( !getenv("SSH_TTY") )
                        {
                                strcat(lDialogString, " --attach=$(xprop -root 32x '\t$0' _NET_ACTIVE_WINDOW | cut -f 2)"); /* contribution: Paul Rouget */
                        }
                }
                strcat( lDialogString , " --list --print-column=ALL" ) ;

                if ( aTitle && strlen(aTitle) )
                {
                        strcat(lDialogString, " --title=\"") ;
                        strcat(lDialogString, aTitle) ;
                        strcat(lDialogString, "\"") ;
                }

                if ( aColumns && (aNumOfColumns > 0) )
                {
                        for ( i = 0 ; i < aNumOfColumns ; i ++ )
                        {
                                strcat( lDialogString , " --column=\"" ) ;
                                strcat( lDialogString , aColumns [i] ) ;
                                strcat( lDialogString , "\"" ) ;
                        }
                }

                if ( aCells && (aNumOfRows > 0) )
                {
                        strcat( lDialogString , " " ) ;
                        for ( i = 0 ; i < aNumOfRows*aNumOfColumns ; i ++ )
                        {
                                strcat( lDialogString , "\"" ) ;
                                strcat( lDialogString , aCells [i] ) ;
                                strcat( lDialogString , "\" " ) ;
                        }
                }
        }
        else
        {
                if (aTitle&&!strcmp(aTitle,"tinyfd_query")){strcpy(tinyfd_response,"");return (char *)0;}
                return NULL ;
        }

        if (tinyfd_verbose) printf( "lDialogString: %s\n" , lDialogString ) ;
        if ( ! ( lIn = popen( lDialogString , "r" ) ) )
        {
                return NULL ;
        }
        while ( fgets( lBuff , sizeof( lBuff ) , lIn ) != NULL )
        {}
        pclose( lIn ) ;
        if ( lBuff[strlen( lBuff ) -1] == '\n' )
        {
                lBuff[strlen( lBuff ) -1] = '\0' ;
        }
        /* printf( "lBuff: %s\n" , lBuff ) ; */
        if ( ! strlen( lBuff ) )
        {
                return NULL ;
        }
        return lBuff ;
}
#endif /*_WIN32 */


/* not cross platform - UNIX and OSX only */
/* contributed by srikanth http://sourceforge.net/u/cr1vct/profile */
#ifndef _WIN32
char *tinyfd_checklistDialog(
    char const *aTitle,
    int aNumOfOptions,
    char const *const *aOptions)
{
        static char lBuff[MAX_PATH_OR_CMD];
        static char dest[MAX_PATH_OR_CMD];

        char lDialogString[MAX_PATH_OR_CMD];
        FILE *lIn;
        char *target = lDialogString;
        lBuff[0] = '\0';
        if (isDarwin())
        {
                target += sprintf(target, "osascript -e \'set Choices to {");
                for (int i = 0; i < aNumOfOptions; i++)
                {
                        if (i != aNumOfOptions - 1)
                                target += sprintf(target, "\"%s\", ", aOptions[i]);
                        else
                                target += sprintf(target, "\"%s\"", aOptions[i]);
                }
                target += sprintf(target, "}\' -e \'set Choice to choose from list Choices with prompt \"%s\" with multiple selections allowed\' -e \'Choice\'", aTitle);
        }

        else if (kdialogPresent())
        {
                target += sprintf(target, "kdialog --checklist \'%s\' ", aTitle);
                for (int i = 0; i < aNumOfOptions; i++)
                {
                        target += sprintf(target, "\'%s\' \'%s\' OFF ", aOptions[i], aOptions[i]);
                }
        }
        else if (zenityPresent())
        {
                target += sprintf(target, "zenity --list --column= --column= --checklist --title=\'%s\' ", aTitle);
                for (int i = 0; i < aNumOfOptions; i++)
                {
                        target += sprintf(target, "\'\' \'%s\' ", aOptions[i]);
                }
        }
        if (tinyfd_verbose)
                printf("lDialogString: %s\n", lDialogString);
        if (!(lIn = popen(lDialogString, "r")))
        {
                return NULL;
        }
        while (fgets(lBuff, sizeof(lBuff), lIn) != NULL)
        {
        }
        pclose(lIn);
        if (lBuff[strlen(lBuff) - 1] == '\n')
        {
                lBuff[strlen(lBuff) - 1] = '\0';
        }
        /* printf( "lBuff: %s\n" , lBuff ) ; */
        if (!strlen(lBuff))
        {
                return NULL;
        }
        if (kdialogPresent())
        {
                replaceSubStr(lBuff, "\" \"", "|", dest);
                dest[strlen(dest) - 2] = '\0';
                return dest + 1;
        }
        if (isDarwin())
        {
                replaceSubStr(lBuff, "\", \"", "|", dest);
                dest[strlen(dest) - 2] = '\0';
                dest[strlen(dest) - 3] = '\0';
                return dest + 2;
        }
        return lBuff;
}
#endif /*_WIN32 */
