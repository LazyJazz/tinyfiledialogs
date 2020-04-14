gcc -ansi -std=gnu89 -pedantic -Wstrict-prototypes -Wall -c tinyfiledialogs.c
dlltool --export-all-symbols -l tinyfiledialogs32.lib tinyfiledialogs.o --dllname tinyfiledialogs32.dll
gcc -shared tinyfiledialogs.o -o tinyfiledialogs32.dll -LC:/mingw/lib -lcomdlg32 -lole32
gcc -ansi -std=gnu89 -pedantic -Wstrict-prototypes -Wall -o hello.exe hello.c tinyfiledialogs32.lib

gcc -pedantic -Wstrict-prototypes -Wall -c tinyfiledialogs.c
dlltool --export-all-symbols -l tinyfiledialogs32.lib tinyfiledialogs.o --dllname tinyfiledialogs32.dll
gcc -shared tinyfiledialogs.o -o tinyfiledialogs32.dll -LC:/mingw/lib -lcomdlg32 -lole32
gcc -pedantic -Wstrict-prototypes -Wall -o hello.exe hello.c tinyfiledialogs32.lib

@REM -std=gnu89 99 11   -Ofast -std=c++11 