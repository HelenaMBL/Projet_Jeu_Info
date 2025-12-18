cls
rem del *.o *.exe
rem gcc -c code_projet_info.c -o code_projet_info.o
rem gcc -c affichage_console.c -o affichage_console.o
rem gcc  code_projet_info.o affichage_console.o -o code_projet_info.exe
del *.exe
mingw32-make
gcc  code_projet_info.o affichage_console.o -o code_projet_info.exe
code_projet_info.exe

