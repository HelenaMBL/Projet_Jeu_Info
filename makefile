#gcc  affichage_console.o code_projet_info.o -o code_projet_info.exe
#gcc -o code_projet_info.o -c code_projet_info.c
#gcc -o affichage_console.o -c  affichage_console.c 
affichage_console.o : affichage_console.c
	gcc -c $< -o $@ 

Affichage.o : Affichage.c
	gcc -c $< -o $@ 

Deroulement.o : Deroulement.c
	gcc -c $< -o $@ 

Jeu.o : Jeu.c 
	gcc -c $< -o $@ 

main.o : main.c 
	gcc -c $< -o $@ 

CandyCrush.exe : Affichage.o Deroulement.o Jeu.o main.o affichage_console.o
	gcc  $? -o $@ 

