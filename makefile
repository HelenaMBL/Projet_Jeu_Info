#gcc  affichage_console.o code_projet_info.o -o code_projet_info.exe
#gcc -o code_projet_info.o -c code_projet_info.c
#gcc -o affichage_console.o -c  affichage_console.c 

code_projet_info.o : code_projet_info.c 
	gcc -c $< -o $@ 

affichage_console.o : affichage_console.c 
	gcc -c $< -o $@ 

code_projet_info.exe : code_projet_info.o affichage_console.o
	gcc  $? -o $@ 

