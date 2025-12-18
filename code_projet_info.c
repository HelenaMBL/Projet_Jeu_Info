#include <stdio.h>
#include <conio.h> 
#include "affichage_console.h"
#include <time.h>

//Afficher le menu
int menu() {
    int choix;
    printf("\n1. Jouer");
    printf("\n2. Regles du jeu");
    printf("\n3. Quitter\n");
    scanf("%d",&choix);
    return choix;
}

// Afficher des règles du jeu
void afficherRegles(){
    printf("\nUtilisez z/q/s/w pour séléctionner les cases pour éliminer un maximum d'items et passer au niveau suivant\n");
}

void remiseAZero(){
    gotoxy(0,0);
    text_color(LIGHTGRAY);
}

void afficheTemps(clock_t temps_debut){
    //variables pour la gestion du temps
    double temps_ecoule;
    //initialisation du temps
    clock_t temps_courant = clock();
    double tempsecoule = (double)(temps_courant - temps_debut) / CLOCKS_PER_SEC;
    printf ("Temps restant : [%.2f] restantes" ,tempsecoule );
}

void afficheNiveau(int niveau){
    printf ("/////////NIVEAU[%d]/////////\n\n" ,niveau);
}
void afficheLigne(const char* motif){
    for (int x = 0; x <= LARGEUR-1; x++) {
            printf (motif);
    }
    printf ("\n");
}
// Afficher le cadre de la zone de jeu"
void afficherCadre() {
    printf ("+");
    afficheLigne("--+");
    for (int y = 0; y <= HAUTEUR-1; y++) {
        //for (int x = 0; x <= LARGEUR-1; x++) {
        printf("|");
        afficheLigne("  |");
        printf ("+");
        afficheLigne("--+");
        //}
    }
    /* for (int x = 0; x <= LARGEUR+1; x++) {
            printf ("-");
            for (int y = 0; y <= HAUTEUR+1; y++) {
            printf ("|");
            if (y == 0 || y == HAUTEUR+1) printf("#");
            else if (x == 0 || x == LARGEUR+1) printf("#");
            else printf(" ");
        } */
        printf("\n");
        //getchar();
    }


// Afficher un caractère à une position dans la console avec une couleur
void afficherObjet(char c, int x, int y, int couleur) {
    /* A COMPLETER */
}

// Déplacer le chasseur selon la touche appuyée
void deplacerChasseur(char touche, int *x, int *y) {
    /* A COMPLETER */
}

// Génèrer des coordonnées aléatoires pour le trésor
void genererTresor(int *x, int *y) {
    /* A COMPLETER */
}

//Vérifier si le chasseur a attrapé un tresor//
void attrapperTresor(/* A COMPLETER */) {
    /* A COMPLETER */
}

//Jouer une partie
void jouer(){
    //déclarations et initialisations des variables pour le joueur
    int xJoueur = LARGEUR / 2;
    int yJoueur = HAUTEUR / 2;
    int temps=15;
    int niveau=1;
    //variables pour le trésor
    int xTresor, yTresor;
    //variables pour la gestion du temps
    clock_t temps_debut;
    double temps_ecoule;
    //variables pour la saise utilisateur (choix de direction de déplacement)
    char touche='a';
    //génération d'un trésor
    genererTresor(&xTresor,&yTresor);
    //initialisation du temps
    temps_debut = clock();
    //Affichage du cadre
    //boucle de jeu
    do {
        remiseAZero();
        afficheNiveau(niveau);
        afficherCadre();
        afficheTemps(temps_debut);

    } while (TRUE);
    return; 
    do{
        /* partie autonome : ce que fait le programme quoi qu'il arrive */
        //calcul du temps écoulé
        /*ACOMPLETER*/
        //affichages
        //affichage du temps écoulé et du score
        gotoxy(0, HAUTEUR+4);
        printf("Temps : %.1f s  ", temps_ecoule);
        gotoxy(0, HAUTEUR+3);
        //printf("Score : %d  ", temps_ecoule);
        //Affichage du chasseur
        /*ACOMPLETER*/
        //Affichage du trésor
        /*ACOMPLETER*/

        /* partie évènementielle : ce que fait le programme si l'utilisateur appuie sur une touche */
        /*ACOMPLETER*/

        //Petite pause pour que ça n'aille pas trop vite
        Sleep(50);
        scanf("");
        
    }while (TRUE);
    clrscr();//efface la console
    //printf("\nFin du jeu. Score final = %d\n", score);
}

// ==== SOUS-PROGRAMME PRINCIPAL ====
int main() {
    int choix;
    // initialisation du générateur pseudo-aléatoire
    srand(time(NULL));
    //boucle de retour au menu à la fin d'une partie
    do{
        //gestion du menu
        choix=menu();
        switch(choix){
            case 1 : /*lancement d'une partie*/
                    hide_cursor();
                    clrscr();
                    jouer();
                    show_cursor();
                    break;
            case 2 : afficherRegles(); break;
        }
    }while(choix!=3);

    return 0;
}