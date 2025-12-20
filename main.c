#include "affichage.h"

int main() {
    srand((unsigned int)time(NULL));
    SetConsoleOutputCP(CP_UTF8); //Si on veut utiliser des caracteres speciaux 
    system("chcp 65001");
    int choix;
    int quitter = 0;

    while(!quitter) {

        switch(afficherMenu()){
            case 1:
                afficherRegles();
                break;
            case 2:
                nouvellePartie();
                break;
            case 3: {
                Partie p;
                if(chargerPartie(&p)) {
                    printf("Partie chargee !\n");
                    Sleep(1000);
                    partieEnCours(&p);
                } else {
                    printf("Aucune sauvegarde pour ce pseudo.\n");
                    Sleep(1500);
                }
                break;
            }
            case 4:
                quitter = 1;
                clrscr();
                printf("Fin du jeu \n");
                Sleep(1500);
                break;
            default:
                gotoxy(30,14);
                printf("Choix invalide ");
                Sleep(1000);
        }
    }

    return 0;
}
