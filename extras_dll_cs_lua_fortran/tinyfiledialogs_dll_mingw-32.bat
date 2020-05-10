
:: cd C:\Users\frogs\yomspace2015\yomlibs\tinyfd

\MinGW\bin\gcc -ansi -std=gnu89 -pedantic -Wstrict-prototypes -Wall -c ../tinyfiledialogs.c
\MinGW\bin\dlltool --export-all-symbols -l tinyfiledialogs32.lib tinyfiledialogs.o --dllname tinyfiledialogs32.dll
\MinGW\bin\gcc -shared -static-libgcc tinyfiledialogs.o -o tinyfiledialogs32.dll -LC:/MinGW/lib -lcomdlg32 -lole32
\MinGW\bin\gcc -ansi -std=gnu89 -pedantic -Wstrict-prototypes -Wall -o hello32.exe ../hello.c tinyfiledialogs32.lib

\MinGW\bin\gcc -pedantic -Wstrict-prototypes -Wall -c ../tinyfiledialogs.c
\MinGW\bin\dlltool --export-all-symbols -l tinyfiledialogs32.lib tinyfiledialogs.o --dllname tinyfiledialogs32.dll
\MinGW\bin\gcc -shared -static-libgcc tinyfiledialogs.o -o tinyfiledialogs32.dll -LC:/MinGW/lib -lcomdlg32 -lole32
\MinGW\bin\gcc -pedantic -Wstrict-prototypes -Wall -o hello32.exe ../hello.c tinyfiledialogs32.lib

@REM -std=gnu89 -Ofast -std=c++11
