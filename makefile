
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

TestCadre.o : TestCadre.c 
	gcc -c $< -o $@ 

TestAnimation.o : TestAnimation.c 
	gcc -c $< -o $@ 

TestItems.o : TestItems.c 
	gcc -c $< -o $@ 

TestMenu.o : TestMenu.c
	gcc -c $< -o $@ 


TestCadre.exe : affichage.o Deroulement.o Jeu.o affichage_console.o TestCadre.o
	gcc  $? -o $@ 

TestAnimation.exce : affichage.o Deroulement.o Jeu.o affichage_console.o TestAnimation.o
	gcc  $? -o $@ 

TestItems.exe : affichage.o Deroulement.o Jeu.o affichage_console.o TestItems.o
	gcc  $? -o $@ 

CandyCrush.exe : affichage.o Deroulement.o Jeu.o main.o affichage_console.o
	gcc  $? -o $@ 

TestMenu.exe : affichage.o Deroulement.o Jeu.o affichage_console.o TestMenu.o
	gcc  $? -o $@

all : CandyCrush.exe TestAnimation.exe TestCadre.exe TestItems.exe TestMenu.exe

