#ifndef AFFICHAGE_CONSOLE_H_INCLUDED
#define AFFICHAGE_CONSOLE_H_INCLUDED
#include <windows.h>
#include <conio.h>


// 16 couleurs utilisables en mode console de base
typedef enum{
    BLACK,
    BLUE,
    GREEN,
    CYAN,
    RED,
    MAGENTA,
    BROWN,
    LIGHTGRAY,
    DARKGRAY,
    LIGHTBLUE,
    LIGHTGREEN,
    LIGHTCYAN,
    LIGHTRED,
    LIGHTMAGENTA,
    YELLOW,
    WHITE
} COLORS;


//effacer la console
void clrscr ();
//d�placer le curseur � la position horizontale x, verticale y
void gotoxy(int x, int y);
//effacer la suite de la ligne
void delete_line();
//r�cup�rer la position horizontale du curseur
int wherex ();
//r�cup�rer la position verticale du curseur
int wherey ();
//changer la couleur du texte
void text_color(int color);
//changer la couleur de fond
void bg_color(int color);
//changer la couleur du texte et du fond
void set_color(int colorT,int colorBg);
//cacher le curseur
void hide_cursor();
//montrer le curseur
void show_cursor();
/*savoir si une touche a �t� press�e
retour : 1 si une touche a �t� press�e (caract�re disponible en lecture avec getch), 0 sinon*/
int kbhit();
/*Lire un caract�re du clavier imm�diatement, sans avoir besoin d'appuyer sur Entr�e.
s'utilise g�n�ralement avec kbhit :
si une touche a �t� press�e, on lit le caract�re correspondant
Retour :  entier ayant le m�me code binaire que le caract�re lu (code ASCII du caract�re)
*/
int getch();
#endif // AFFICHAGE_CONSOLE_H_INCLUDED
