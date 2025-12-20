
affichage_console.o : affichage_console.c
	gcc -c $< -o $@ 

affichage.o : affichage.c
	gcc -c $< -o $@ 

Deroulement.o : Deroulement.c
	gcc -c $< -o $@ 

Jeu.o : Jeu.c 
	gcc -c $< -o $@ 

main.o : main.c 
	gcc -c $< -o $@ 

Test.o : Test.c 
	gcc -c $< -o $@ 


Test.exe : affichage.o Deroulement.o Jeu.o affichage_console.o Test.o
	gcc  $? -o $@ 



CandyCrush.exe : affichage.o Deroulement.o Jeu.o main.o affichage_console.o
	gcc  $? -o $@ 

