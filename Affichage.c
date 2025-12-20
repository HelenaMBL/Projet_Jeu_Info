#include "fonctions.h"

/* =========================================================
   AFFICHAGE DU MENU PRINCIPAL
   ========================================================= */
void afficherMenu() {
    clrscr();
    hide_cursor();
    set_color(WHITE, BLACK);

    gotoxy(30, 5);
    printf("==== ECE HEROES ====");

    gotoxy(30, 7);
    printf("1. Regles du jeu");

    gotoxy(30, 8);
    printf("2. Nouvelle partie");

    gotoxy(30, 9);
    printf("3. Reprendre une partie");

    gotoxy(30, 10);
    printf("4. Quitter");
}

/* =========================================================
   AFFICHAGE DES REGLES
   ========================================================= */
void afficherRegles() {
    clrscr();
    set_color(WHITE, BLACK);

    gotoxy(2, 2);
    printf("REGLES DU JEU");

    gotoxy(2, 4);
    printf("Deplacer le curseur avec Z Q S D");

    gotoxy(2, 5);
    printf("Appuyer sur la touche espace pour selectionner un item");

    gotoxy(2, 6);
    printf("Echanger en selectionnant un item voisin");

    gotoxy(2, 7);
    printf("Formez des figures pour eliminer les items");

    gotoxy(2, 9);
    printf("Figures speciales :");

    gotoxy(4, 10);
    printf("- Suite de 4 : supprime la suite");

    gotoxy(4, 11);
    printf("- Suite de 6 : supprime tous les items de la couleur");

    gotoxy(4, 12);
    printf("- Croix : supprime la ligne et la colonne");

    gotoxy(4, 13);
    printf("- Carre 4x4 : supprime le carre");

    gotoxy(2,14);
    printf("Appuyez sur esc pour quitter le jeu en cours de partie ");

    gotoxy(2, 15);
    printf("○ peut etre echange avec n'importe quel autre item");

    gotoxy(2, 16);
    printf("Lorsque ● est échangé avec n'importe quel autre item, il supprime tous les items de cette couleur ");

    gotoxy(2, 18);
    printf("Appuyez sur une touche pour revenir au menu principal");
    getch();
}

/* =========================================================
   AFFICHAGE DE LA GRILLE DE JEU
   ========================================================= */

void remiseAZero(){
    gotoxy(0,2);
    text_color(LIGHTGRAY);
}

void afficheLigne(const char* motifDebut, const char* motif, const char* motifFin){
    printf(motifDebut);
    for(int x=0; x<= COLONNES-2; x++){
        printf(motif);
    }
    printf("%s\n", motifFin);
}

void afficherCadre() {
    afficheLigne("╔", "══╦", "══╗");
    for (int y = 0; y <= LIGNES-2; y++) {
        afficheLigne("║", "  ║", "  ║");
        afficheLigne("╠", "══╬", "══╣");
    }
    afficheLigne("║", "  ║", "  ║");
    afficheLigne("╚", "══╩", "══╝");
}

void afficherItems(int grille[LIGNES][COLONNES], Curseur curseur) {
    int i, j;
    int x0=1;
    int y0 = 1;

    for (i = 0; i < LIGNES; i++) {
        for (j = 0; j < COLONNES; j++) {

            gotoxy(x0 + j * 3, y0 + i * 2);

            // Mise en évidence du curseur
            if (curseur.ligne == i && curseur.colonne == j) {
                bg_color(DARKGRAY);
            } else if (curseur.selectionActive && curseur.selLigne == i && curseur.selColonne == j) {
                bg_color(LIGHTGRAY);
            } else {
                bg_color(BLACK);
            }

            // Affichage de l’item
            switch (grille[i][j]) {
                case ITEM_1: text_color(LIGHTRED);printf("♥"); break;
                case ITEM_2: text_color(LIGHTGREEN); printf("♠"); break;
                case ITEM_3: text_color(LIGHTMAGENTA); printf("♦"); break;
                case ITEM_4: text_color(LIGHTCYAN); printf("♣"); break;
                case ITEM_5: text_color(YELLOW); printf("★"); break;
                case ITEM_BONUS: text_color(WHITE); printf("○"); break;
                case ITEM_JOKER: text_color(WHITE); printf("●"); break;
                default: printf(" ");
            }

            set_color(WHITE, BLACK);
        }
    }
}
void afficherGrille(int grille[LIGNES][COLONNES], Curseur curseur) {
    afficherItems(grille, curseur);
}

/* =========================================================
   AFFICHAGE DES INFORMATIONS DE JEU
   ========================================================= */
void afficherInformations(Partie p, int tempsRestant) {
    int y = 3;

    set_color(WHITE, BLACK);

    gotoxy(45, y++); printf("Niveau : %d", p.niveau);
    gotoxy(45, y++); printf("Vies restantes : %d", p.vies);
    gotoxy(45, y++); printf("Coups restants : %d", p.coupsRestants);
    gotoxy(45, y++); printf("Temps restant : %d s  ", tempsRestant); // espaces pour effacer reliquats
    y++;

    gotoxy(45,y++);printf("Objectifs :");
    gotoxy(47,y++);text_color(LIGHTRED);printf("♥ : %d", p.objectifs[1]);
    gotoxy(47,y++);text_color(LIGHTGREEN); printf("♠ : %d", p.objectifs[2]);
    gotoxy(47,y++);text_color(LIGHTMAGENTA); printf("♦ : %d", p.objectifs[3]);
    gotoxy(47,y++);text_color(LIGHTCYAN); printf("♣ : %d", p.objectifs[4]);
    gotoxy(47,y++);text_color(YELLOW); printf("★ : %d", p.objectifs[5]);

    set_color(WHITE,BLACK);
}

void afficherAnimationNiveau(int grille[LIGNES][COLONNES], Curseur curseur) {
    int grille[LIGNES][COLONNES];
    int i, j;
    int x0=1;
    int y0 = 1;
    for (i = 0; i < LIGNES; i++) {
        for (j = 0; j < COLONNES; j++) {
            gotoxy(x0 + j * 3, y0 + i * 2);
            switch (grille[i][j]) {
                case ITEM_1: text_color(WHITE);printf("♥"); break;
                case ITEM_2: text_color(WHITE); printf("♠"); break;
                case ITEM_3: text_color(WHITE); printf("♦"); break;
                case ITEM_4: text_color(WHITE); printf("♣"); break;
                case ITEM_5: text_color(WHITE); printf("★"); break;
                case ITEM_BONUS: text_color(WHITE); printf("○"); break;
                case ITEM_JOKER: text_color(WHITE); printf("●"); break;
                default: printf(" ");
            }

            set_color(WHITE, BLACK);
        }
    }
    gotoxy(45,17);
    printf("NIVEAU REUSSI !!!");
    Sleep(2000);
    afficherItems(grille, curseur);
}


/*void afficherMenu() {
    clrscr();
    hide_cursor();
    set_color(WHITE, BLACK);

    gotoxy(30, 5);
    printf("==== ECE HEROES ====");

    gotoxy(30, 7);
    printf("1. Regles du jeu");

    gotoxy(30, 8);
    printf("2. Nouvelle partie");

    gotoxy(30, 9);
    printf("3. Reprendre une partie");

    gotoxy(30, 10);
    printf("4. Quitter");
}

void afficherRegles() {
    clrscr();
    set_color(WHITE, BLACK);

    gotoxy(2, 2);
    printf("REGLES DU JEU");

    gotoxy(2, 4);
    printf("Deplacer le curseur avec Z Q S D");

    gotoxy(2, 5);
    printf("Appuyer sur la touche espace pour selectionner un item");

    gotoxy(2, 6);
    printf("Echanger en selectionnant un item voisin");

    gotoxy(2, 7);
    printf("Formez des figures pour eliminer les items");

    gotoxy(2, 9);
    printf("Figures speciales :");

    gotoxy(4, 10);
    printf("- Suite de 4 : supprime la suite");

    gotoxy(4, 11);
    printf("- Suite de 6 : supprime tous les items de la couleur");

    gotoxy(4, 12);
    printf("- Croix : supprime la ligne et la colonne");

    gotoxy(4, 13);
    printf("- Carre 4x4 : supprime le carre");

    gotoxy(2,14);
    printf("Appuyez sur esc pour quitter le jeu en cours de partie ");

    gotoxy(2, 15);
    printf("○ peut etre echange avec n'importe quel autre item");

    gotoxy(2, 16);
    printf("Lorsque ● est échangé avec n'importe quel autre item, il supprime tous les items de cette couleur ");

    gotoxy(2, 18);
    printf("Appuyez sur une touche pour revenir au menu principal");
    getch();
}

void afficherGrille(int grille[LIGNES][COLONNES], Curseur curseur) {
    int i, j;
    int x0 = 2;
    int y0 = 3;

    for (i = 0; i < LIGNES; i++) {
        for (j = 0; j < COLONNES; j++) {

            gotoxy(x0 + j * 2, y0 + i);

            // Mise en évidence du curseur
            if (curseur.ligne == i && curseur.colonne == j) {
                bg_color(DARKGRAY);
            } else if (curseur.selectionActive && curseur.selLigne == i && curseur.selColonne == j) {
                bg_color(LIGHTGRAY);
            } else {
                bg_color(BLACK);
            }

            // Affichage de l’item
            switch (grille[i][j]) {
                case ITEM_1: text_color(LIGHTRED);printf("♥"); break;
                case ITEM_2: text_color(LIGHTGREEN); printf("♠"); break;
                case ITEM_3: text_color(LIGHTMAGENTA); printf("♦"); break;
                case ITEM_4: text_color(LIGHTCYAN); printf("♣"); break;
                case ITEM_5: text_color(YELLOW); printf("★"); break;
                case ITEM_BONUS: text_color(WHITE); printf("○"); break;
                case ITEM_JOKER: text_color(WHITE); printf("●"); break;
                default: printf(" ");
            }

            set_color(WHITE, BLACK);
        }
    }
}

void afficherInformations(Partie p, int tempsRestant) {
    int y = 3;

    set_color(WHITE, BLACK);

    gotoxy(45, y++); printf("Niveau : %d", p.niveau);
    gotoxy(45, y++); printf("Vies restantes : %d", p.vies);
    gotoxy(45, y++); printf("Coups restants : %d", p.coupsRestants);
    gotoxy(45, y++); printf("Temps restant : %d s  ", tempsRestant); // espaces pour effacer reliquats
    y++;

    gotoxy(45, y++); printf("Objectifs :");
    for(int i=1; i<=NB_ITEMS; i++) {
        gotoxy(47, y++); printf("Item %d : %d   ", i, p.objectifs[i]); // espaces pour nettoyer
    }
}
*/