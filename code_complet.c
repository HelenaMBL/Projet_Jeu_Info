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

void afficheLigne(const char* motif){
    for (int x = 0; x <= COLONNES-1; x++) {
            printf (motif);
    }
    printf ("\n");
}

void afficherCadre() {
    remiseAZero();
    printf ("+");
    afficheLigne("--+");
    for (int y = 0; y <= LIGNES-1; y++) {
        //for (int x = 0; x <= COLONNES-1; x++) {
        printf("|");
        afficheLigne("  |");
        printf ("+");
        afficheLigne("--+");
        //}
    }
}

   void afficherItems(int grille[LIGNES][COLONNES], Curseur curseur) {
    int i, j;
    int x0 = 2;
    int y0 = 3;

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
    afficherCadre();
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

    gotoxy(45, y++); printf("Objectifs :");
    for(int i=1; i<=NB_ITEMS; i++) {
        gotoxy(47, y++); printf("Item %d : %d   ", i, p.objectifs[i]); // espaces pour nettoyer
    }
}


// deroulement.c 

#include "fonctions.h"

/* =========================================================
   NOUVELLE PARTIE
   ========================================================= */
void nouvellePartie() {
    Partie p;
    p.niveau = 1;
    p.vies = VIES_INITIALES;
    p.coupsRestants = COUPS_NIV1;
    initialiserObjectifs(&p);
    p.debutNiveau = time(NULL);

    partieEnCours(&p);
}

/* =========================================================
   PARTIE EN COURS
   ========================================================= */
void partieEnCours(Partie *p) {
    int continuer = 1;
    int resultat;

    while(continuer && p->vies>0 && p->niveau<=NB_NIVEAUX) {
        resultat = jouerNiveau(p);

        if(resultat==1) { // Niveau réussi
            p->niveau++;
            if(p->niveau==2) p->coupsRestants = COUPS_NIV2;
            else if(p->niveau==3) p->coupsRestants = COUPS_NIV3;
            p->debutNiveau = time(NULL);
            for(int i=1;i<=NB_ITEMS;i++) p->objectifs[i]=10*(i+1); // Réinitialise objectifs
        } else if(resultat==0) { // Niveau échoué
            p->vies--;
            if(p->vies>0) {
                clrscr();
                printf("\nPerte d'une vie !\n");
                Sleep(2000);
            } else {
                printf("\nGAME OVER\n");
                continuer = 0;
                Sleep(2000);
            }
        } else { // Quitter
            sauvegarderPartie(*p);
            continuer = 0;
        }
    }

    if(p->niveau>NB_NIVEAUX && p->vies>0) {
        clrscr();
        printf("JEU TERMINE, BRAVO !\n");
        Sleep(2000);
    }
}

/* =========================================================
   JOUER UN NIVEAU
   ========================================================= */
int jouerNiveau(Partie *p) {
    clrscr();
    int grille[LIGNES][COLONNES];
    Curseur curseur = {0,0,0,0,0};
    int touche;
    time_t debut = time(NULL);
    int tempsMax;

    if(p->niveau==1) tempsMax = TEMPS_NIV1;
    else if(p->niveau==2) tempsMax = TEMPS_NIV2;
    else tempsMax = TEMPS_NIV3;

    initialiserGrille(grille, p->niveau);
    stabiliserGrille(grille,p,p->niveau);

    while(1) {
        int tempsEcoule = (int)difftime(time(NULL), debut);
        int tempsRestant = tempsMax - tempsEcoule; 
        afficherGrille(grille, curseur);
        afficherInformations(*p, tempsRestant);
        if(!existePermutation(grille)) {
            gotoxy(45, 20);
            printf("Plus de combinaisons possibles !");
            Sleep(1500);
            melangerGrille(grille);
            stabiliserGrille(grille, p, p->niveau);
        }

        // Gestion du temps
        if(tempsEcoule>=tempsMax) return 0; // échec niveau
        /*gotoxy(45, 8);
        printf("Temps restant : %d s  ", tempsMax - tempsEcoule);µ*/

        if(kbhit()) {
            touche = getch();
            switch(touche) {
                case 'z': case 'Z': if(curseur.ligne>0) curseur.ligne--; break;
                case 's': case 'S': if(curseur.ligne<LIGNES-1) curseur.ligne++; break;
                case 'q': case 'Q': if(curseur.colonne>0) curseur.colonne--; break;
                case 'd': case 'D': if(curseur.colonne<COLONNES-1) curseur.colonne++; break;
                case ' ': // selection / permutation
                    if(!curseur.selectionActive) {
                        curseur.selectionActive=1;
                        curseur.selLigne=curseur.ligne;
                        curseur.selColonne=curseur.colonne;
                    } else {
                        // tente permutation avec curseur actuel
                        if(permutationValide(grille,curseur.selLigne,curseur.selColonne,curseur.ligne,curseur.colonne)) {
                            p->coupsRestants--;
                            stabiliserGrille(grille,p,p->niveau);
                        }
                        curseur.selectionActive=0;
                    }
                    break;
                case 27: // ESC : quitter
                    return -1;
            }
        }

        // Vérification objectifs atteints
        int objectifsRestants=0;
        for(int i=1;i<=NB_ITEMS;i++) objectifsRestants+=p->objectifs[i];
        if(objectifsRestants<=0) return 1; // niveau réussi

        if(p->coupsRestants<=0) return 0; // niveau échoué
        Sleep(50);
    }

    return 0;
}

/* =========================================================
   SAUVEGARDE ET CHARGEMENT
   ========================================================= */
void sauvegarderPartie(Partie p) { 
    char pseudo[50];
    char choix;

    clrscr();
    printf("Voulez-vous sauvegarder la partie ?\n O pour Oui, N pour Non  ");
    choix = getch();  // lecture immédiate

    if(choix == 'O' || choix == 'o') {
        printf("\nEntrez votre pseudo pour sauvegarder : ");
        scanf("%49s", pseudo);

        FILE *f = fopen("sauvegarde.txt","a");
        if(f) {
            fprintf(f,"%s %d %d %d %lld %d %d %d %d %d %d\n",pseudo, p.niveau, p.vies, p.coupsRestants, p.debutNiveau,p.objectifs[1],p.objectifs[2],p.objectifs[3],p.objectifs[4],p.objectifs[5],0);
            fclose(f);
            printf("Partie sauvegardee\n");
            Sleep(1500);
        } else {
            printf("Erreur de sauvegarde.\n");
            Sleep(1500);
        }
    } else {
        printf("\nPartie non sauvegardee\n");
        Sleep(1000);
    }
}


int chargerPartie(Partie *p) {
    char pseudo[50], ligne[200];
    clrscr();
    printf("Entrez votre pseudo pour charger la partie : ");
    scanf("%49s", pseudo);

    FILE *f = fopen("sauvegarde.txt","r");
    if(!f) return 0;

    while(fgets(ligne,sizeof(ligne),f)) {
        char fichierPseudo[50];
        int n,v,c,objet1,objet2,objet3,objet4,objet5;
        long t;
        sscanf(ligne,"%s %d %d %d %ld %d %d %d %d %d %*d",fichierPseudo,&n,&v,&c,&t,&objet1,&objet2,&objet3,&objet4,&objet5);
        if(strcmp(fichierPseudo,pseudo)==0) {
            p->niveau = n;
            p->vies = v;
            p->coupsRestants = c;
            p->debutNiveau = t;
            p->objectifs[1]=objet1;
            p->objectifs[2]=objet2;
            p->objectifs[3]=objet3;
            p->objectifs[4]=objet4;
            p->objectifs[5]=objet5;
            fclose(f);
            return 1; // succès
        }
    }
    fclose(f);
    return 0; // pseudo non trouvé
}

// jeu.c

#include "fonctions.h"

// Fonnction de test pour les différentes fonctions du module jeu 
/*Modifications réalisées 
initialiserGrille => enlève le int niveau de l'initialisation */


/* =========================================================
   INITIALISATION DE LA GRILLE
   ========================================================= */
   
void initialiserGrille(int grille[LIGNES][COLONNES], int niveau) {
    int i, j;
    srand((unsigned int)time(NULL));

    do {
        for (i = 0; i < LIGNES; i++) {
            for (j = 0; j < COLONNES; j++) {
                grille[i][j] = (rand() % NB_ITEMS) + 1;
            }
        }
    } while (!verifierGrilleInitiale(grille)); // Evite figures speciales au depart
}

/* Verifie qu'il n'y a pas de figure speciale au debut */
int verifierGrilleInitiale(int grille[LIGNES][COLONNES]) {
    Partie temp = {0};
    return !(detecterSuites4(grille, &temp) ||
             detecterSuites6(grille, &temp) ||
             detecterCroix(grille, &temp) ||
             detecterCarre(grille, &temp));
}

/* =========================================================
   PERMUTATION DES ITEMS
   ========================================================= */
int permutationValide(int grille[LIGNES][COLONNES], int l1, int c1, int l2, int c2) {
    int temp = grille[l1][c1];
    grille[l1][c1] = grille[l2][c2];
    grille[l2][c2] = temp;

    Partie tempPartie = {0};
    int valide = detecterSuites4(grille, &tempPartie) ||
                 detecterSuites6(grille, &tempPartie) ||
                 detecterCroix(grille, &tempPartie) ||
                 detecterCarre(grille, &tempPartie);

    if (!valide) { // annule permutation
        temp = grille[l1][c1];
        grille[l1][c1] = grille[l2][c2];
        grille[l2][c2] = temp;
    }
    return valide;
}

void initialiserObjectifs(Partie *p) {
    int obj1[NB_ITEMS] = OBJECTIFS_NIV1;
    int obj2[NB_ITEMS] = OBJECTIFS_NIV2;
    int obj3[NB_ITEMS] = OBJECTIFS_NIV3;

    int *src;
    if(p->niveau == 1) src = obj1;
    else if(p->niveau == 2) src = obj2;
    else src = obj3;

    for(int i = 0; i < NB_ITEMS; i++)
        p->objectifs[i+1] = src[i];
}

/* =========================================================
   DETECTION DES FIGURES
   ========================================================= */
int detecterSuites4(int grille[LIGNES][COLONNES], Partie *p) {
    int i, j, count = 0;
    for (i = 0; i < LIGNES; i++) {
        for (j = 0; j < COLONNES - 3; j++) {
            int val = grille[i][j];
            if (val > 0 &&
                val == grille[i][j+1] &&
                val == grille[i][j+2] &&
                val == grille[i][j+3]) {
                // Suppression des items
                grille[i][j] = grille[i][j+1] = grille[i][j+2] = grille[i][j+3] = ITEM_VIDE;
                if(p) p->objectifs[val]--;
                count++;
            }
        }
    }
    for (j = 0; j < COLONNES; j++) {
        for (i = 0; i < LIGNES - 3; i++) {
            int val = grille[i][j];
            if (val > 0 &&
                val == grille[i+1][j] &&
                val == grille[i+2][j] &&
                val == grille[i+3][j]) {
                grille[i][j] = grille[i+1][j] = grille[i+2][j] = grille[i+3][j] = ITEM_VIDE;
                if(p) p->objectifs[val]--;
                count++;
            }
        }
    }
    return count;
}

int detecterSuites6(int grille[LIGNES][COLONNES], Partie *p) {
    int i, j, count = 0;
    for (i = 0; i < LIGNES; i++) {
        for (j = 0; j < COLONNES - 5; j++) {
            int val = grille[i][j];
            int k, ok = 1;
            for (k = 1; k < 6; k++)
                if (grille[i][j+k] != val) { ok = 0; break; }
            if (ok && val > 0) {
                // Supprime tous les items de cette couleur
                for (i=0;i<LIGNES;i++)
                    for(j=0;j<COLONNES;j++)
                        if(grille[i][j]==val) { grille[i][j]=ITEM_VIDE; if(p) p->objectifs[val]--; }
                count++;
            }
        }
    }
    for (j = 0; j < COLONNES; j++) {
        for (i = 0; i < LIGNES - 5; i++) {
            int val = grille[i][j], k, ok=1;
            for(k=1;k<6;k++)
                if(grille[i+k][j]!=val){ok=0;break;}
            if(ok && val>0){
                for(int ii=0;ii<LIGNES;ii++)
                    for(int jj=0;jj<COLONNES;jj++)
                        if(grille[ii][jj]==val){grille[ii][jj]=ITEM_VIDE;if(p)p->objectifs[val]--;}
                count++;
            }
        }
    }
    return count;
}

int detecterCroix(int grille[LIGNES][COLONNES], Partie *p) {
    int i,j,count=0;
    for(i=1;i<LIGNES-1;i++){
        for(j=1;j<COLONNES-1;j++){
            int val = grille[i][j];
            if(val>0 &&
               val==grille[i-1][j] && val==grille[i+1][j] &&
               val==grille[i][j-1] && val==grille[i][j+1]){
                // supprimer ligne et colonne
                for(int x=0;x<LIGNES;x++) if(grille[x][j]==val){grille[x][j]=ITEM_VIDE;if(p)p->objectifs[val]--;}
                for(int y=0;y<COLONNES;y++) if(grille[i][y]==val){grille[i][y]=ITEM_VIDE;if(p)p->objectifs[val]--;}
                count++;
            }
        }
    }
    return count;
}

int detecterCarre(int grille[LIGNES][COLONNES], Partie *p) {
    int i,j,count=0;
    for(i=0;i<LIGNES-3;i++){
        for(j=0;j<COLONNES-3;j++){
            int val = grille[i][j],ok=1;
            for(int ii=0;ii<4;ii++)
                for(int jj=0;jj<4;jj++)
                    if(grille[i+ii][j+jj]!=val){ok=0;break;}
            if(ok && val>0){
                for(int ii=0;ii<4;ii++)
                    for(int jj=0;jj<4;jj++){
                        grille[i+ii][j+jj]=ITEM_VIDE;
                        if(p) p->objectifs[val]--;
                    }
                count++;
            }
        }
    }
    return count;
}

int existePermutation(int grille[LIGNES][COLONNES]) {
    for(int i=0;i<LIGNES;i++){
        for(int j=0;j<COLONNES;j++){
            if(j+1<COLONNES && permutationValide(grille,i,j,i,j+1)) return 1;
            if(i+1<LIGNES && permutationValide(grille,i,j,i+1,j)) return 1;
        }
    }
    return 0;
}

void melangerGrille(int grille[LIGNES][COLONNES]) {
    for(int i=0;i<LIGNES;i++){
        for(int j=0;j<COLONNES;j++){
            grille[i][j] = (rand()%NB_ITEMS)+1;
        }
    }
}

/* =========================================================
   GRAVITE ET REMPLISSAGE
   ========================================================= */
void appliquerGravite(int grille[LIGNES][COLONNES], Partie *p) {
    for(int j=0;j<COLONNES;j++){
        for(int i=LIGNES-2;i>=0;i--){
            if(grille[i][j]!=ITEM_VIDE){
                int ligne=i;
                while(ligne+1<LIGNES && grille[ligne+1][j]==ITEM_VIDE){
                    grille[ligne+1][j]=grille[ligne][j];
                    grille[ligne][j]=ITEM_VIDE;
                    ligne++;
                }
            }
        }
    }
    for(int j=0;j<COLONNES;j++){
    if(grille[LIGNES-1][j] == ITEM_JOKER) {
        int cible = (rand() % NB_ITEMS) + 1;
        p->objectifs[cible] = 0;
        grille[LIGNES-1][j] = ITEM_VIDE;
    }
}

}

void remplirCasesVides(int grille[LIGNES][COLONNES], int niveau) {
    srand((unsigned int)time(NULL));
    for(int i=0;i<LIGNES;i++)
        for(int j=0;j<COLONNES;j++)
            if(grille[i][j]==ITEM_VIDE)
                grille[i][j]=(rand()%NB_ITEMS)+1;
}

int stabiliserGrille(int grille[LIGNES][COLONNES],Partie *p,int niveau){
    int total;
    do{
        total=0;
        total+=detecterSuites4(grille,p);
        total+=detecterSuites6(grille,p);
        total+=detecterCroix(grille,p);
        total+=detecterCarre(grille,p);
        appliquerGravite(grille, p);
        remplirCasesVides(grille,niveau);
    }while(total>0);
    return total;
}


/* =========================================================
   EXTENSIONS BONUS
   ========================================================= */

// main.c

#include "fonctions.h"

int main() {
    SetConsoleOutputCP(CP_UTF8); //Si on veut utiliser des caracteres speciaux 
    system("chcp 65001");
    int choix;
    int quitter = 0;

    while(!quitter) {
        afficherMenu();
        choix = getch() - '0'; // lecture du chiffre

        switch(choix) {
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


// fonctions.h

//#ifndef FONCTIONS_H
#define FONCTIONS_H

/* =========================================================
   INCLUDES
   ========================================================= */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <wchar.h>

#include "affichage_console.h"

/* =========================================================
   CONSTANTES DU JEU (MODIFIABLES POUR LA JOUABILITE)
   ========================================================= */

/* Dimensions de la grille */
#define LIGNES 8
#define COLONNES 12

/* Types d'items */
#define NB_ITEMS 5

#define ITEM_VIDE   0
#define ITEM_1      1
#define ITEM_2      2
#define ITEM_3      3
#define ITEM_4      4
#define ITEM_5      5

/* Extensions */
#define ITEM_BONUS  6   /* Supprime tous les items d'une couleur */
#define ITEM_JOKER  7   /* Peut s'aligner avec n'importe quel item */

/* Jeu */
#define NB_NIVEAUX  3
#define VIES_INITIALES 3

/* Niveau 1 (sans extensions) */
#define COUPS_NIV1  30
#define TEMPS_NIV1  90   /* en secondes */
#define OBJECTIFS_NIV1 {5,5,5,5,5}
#define OBJECTIFS_NIV2 {10,15,5,10,15}
#define OBJECTIFS_NIV3 {20,25,10,20,5}

/* Niveau 2 */
#define COUPS_NIV2  35
#define TEMPS_NIV2  75

/* Niveau 3 */
#define COUPS_NIV3  40
#define TEMPS_NIV3  90

/* =========================================================
   STRUCTURES
   ========================================================= */

/* Informations sur la partie */
typedef struct {
    int niveau;
    int vies;
    int coupsRestants;
    int objectifs[NB_ITEMS + 1]; /* index 1 a 5 */
    time_t debutNiveau;
} Partie;

/* Curseur du joueur */
typedef struct {
    int ligne;
    int colonne;
    int selectionActive;   /* 0 = non, 1 = oui */
    int selLigne;
    int selColonne;
} Curseur;

/* =========================================================
   PROTOTYPES - MODULE AFFICHAGE (affichage.c)
   ========================================================= */

/* Menus */
void afficherMenu();
void afficherRegles();

/* Affichage du jeu */
void afficherGrille(int grille[LIGNES][COLONNES], Curseur curseur);
void afficherInformations(Partie p, int tempRestant);

/* =========================================================
   PROTOTYPES - MODULE JEU (jeu.c)
   ========================================================= */

/* Grille */
void initialiserGrille(int grille[LIGNES][COLONNES], int niveau);
int verifierGrilleInitiale(int grille[LIGNES][COLONNES]);

/* Deplacements */
int permutationValide(int grille[LIGNES][COLONNES], int l1, int c1, int l2, int c2);
void initialiserObjectifs(Partie *p);

/* Detection et suppression */
int detecterSuites4(int grille[LIGNES][COLONNES], Partie *p);
int detecterSuites6(int grille[LIGNES][COLONNES], Partie *p);
int detecterCroix(int grille[LIGNES][COLONNES], Partie *p);
int detecterCarre(int grille[LIGNES][COLONNES], Partie *p);

int appliquerSuppressions(int grille[LIGNES][COLONNES], Partie *p);

int existePermutation(int grille[LIGNES][COLONNES]);
void melangerGrille(int grille[LIGNES][COLONNES]);

/* Gravite */
void appliquerGravite(int grille[LIGNES][COLONNES], Partie *p);
void remplirCasesVides(int grille[LIGNES][COLONNES], int niveau);
int stabiliserGrille(int grille[LIGNES][COLONNES], Partie *p, int niveau);

/* Extensions */



/* =========================================================
   PROTOTYPES - MODULE DEROULEMENT (deroulement.c)
   ========================================================= */

/* Partie */
void nouvellePartie();
void partieEnCours(Partie *p);

/* Niveaux */
int jouerNiveau(Partie *p);

/* Sauvegarde */
void sauvegarderPartie(Partie p);
int chargerPartie(Partie *p);

//#endif 











/*//////// CODE COMPLET DU JEU //////////

////////////////////////////////////////////////////////// Fonctions.h

#ifndef FONCTIONS_H
#define FONCTIONS_H

// Bibliothèques 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <wchar.h>

#include "affichage_console.h"

// Constantes 
#define LIGNES 8
#define COLONNES 12

#define NB_ITEMS 5

#define ITEM_VIDE   0
#define ITEM_1      1
#define ITEM_2      2
#define ITEM_3      3
#define ITEM_4      4
#define ITEM_5      5

#define ITEM_BONUS  6
#define ITEM_JOKER  7

#define NB_NIVEAUX  3
#define VIES_INITIALES 3

#define COUPS_NIV1  30
#define TEMPS_NIV1  60

#define COUPS_NIV2  35
#define TEMPS_NIV2  75

#define COUPS_NIV3  40
#define TEMPS_NIV3  90

typedef struct {
    int niveau;
    int vies;
    int coupsRestants;
    int objectifs[NB_ITEMS + 1];
    time_t debutNiveau;
} Partie;

typedef struct {
    int ligne;
    int colonne;
    int selectionActive;
    int selLigne;
    int selColonne;
} Curseur;

//Module affichage 
void afficherMenu();
void afficherRegles();

void afficherGrille(int grille[LIGNES][COLONNES], Curseur curseur);
void afficherInformations(Partie p, int tempRestant);

// Module jeu 
void initialiserGrille(int grille[LIGNES][COLONNES], int niveau);
int verifierGrilleInitiale(int grille[LIGNES][COLONNES]);

int permutationValide(int grille[LIGNES][COLONNES], int l1, int c1, int l2, int c2);

int detecterSuites4(int grille[LIGNES][COLONNES], Partie *p);
int detecterSuites6(int grille[LIGNES][COLONNES], Partie *p);
int detecterCroix(int grille[LIGNES][COLONNES], Partie *p);
int detecterCarre(int grille[LIGNES][COLONNES], Partie *p);

int appliquerSuppressions(int grille[LIGNES][COLONNES], Partie *p);

void appliquerGravite(int grille[LIGNES][COLONNES]);
void remplirCasesVides(int grille[LIGNES][COLONNES], int niveau);
int stabiliserGrille(int grille[LIGNES][COLONNES], Partie *p, int niveau);

void activerBonusCouleur(int grille[LIGNES][COLONNES], int type, Partie *p);

/// Module deroulement 
void nouvellePartie();
void partieEnCours(Partie *p);

int jouerNiveau(Partie *p);

void sauvegarderPartie(Partie p);
int chargerPartie(Partie *p);

#endif

////////////////////////////////////////////////////////// Deroulement.c

#include "fonctions.h"

void nouvellePartie() {
    Partie p;
    p.niveau = 1;
    p.vies = VIES_INITIALES;
    p.coupsRestants = COUPS_NIV1;
    for(int i=1;i<=NB_ITEMS;i++) p.objectifs[i]=10*(i+1);
    p.debutNiveau = time(NULL);

    partieEnCours(&p);
}

void partieEnCours(Partie *p) {
    int continuer = 1;
    int resultat;

    while(continuer && p->vies>0 && p->niveau<=NB_NIVEAUX) {
        resultat = jouerNiveau(p);

        if(resultat==1) {
            p->niveau++;
            if(p->niveau==2) p->coupsRestants = COUPS_NIV2;
            else if(p->niveau==3) p->coupsRestants = COUPS_NIV3;
            p->debutNiveau = time(NULL);
            for(int i=1;i<=NB_ITEMS;i++) p->objectifs[i]=10*(i+1);
        } else if(resultat==0) {
            p->vies--;
            if(p->vies>0) {
                clrscr();
                printf("\nPerte d'une vie !\n");
                Sleep(2000);
            } else {
                printf("\nGAME OVER\n");
                continuer = 0;
                Sleep(2000);
            }
        } else {
            sauvegarderPartie(*p);
            continuer = 0;
        }
    }

    if(p->niveau>NB_NIVEAUX && p->vies>0) {
        clrscr();
        printf("JEU TERMINE, BRAVO !\n");
        Sleep(2000);
    }
}

int jouerNiveau(Partie *p) {
    clrscr();
    int grille[LIGNES][COLONNES];
    Curseur curseur = {0,0,0,0,0};
    int touche;
    time_t debut = time(NULL);
    int tempsMax;

    if(p->niveau==1) tempsMax = TEMPS_NIV1;
    else if(p->niveau==2) tempsMax = TEMPS_NIV2;
    else tempsMax = TEMPS_NIV3;

    initialiserGrille(grille, p->niveau);
    stabiliserGrille(grille,p,p->niveau);

    while(1) {
        int tempsEcoule = (int)difftime(time(NULL), debut);
        int tempsRestant = tempsMax - tempsEcoule; 
        afficherGrille(grille, curseur);
        afficherInformations(*p, tempsRestant);
        if(tempsEcoule>=tempsMax) return 0;
        if(kbhit()) {
            touche = getch();
            switch(touche) {
                case 'z': case 'Z': if(curseur.ligne>0) curseur.ligne--; break;
                case 's': case 'S': if(curseur.ligne<LIGNES-1) curseur.ligne++; break;
                case 'q': case 'Q': if(curseur.colonne>0) curseur.colonne--; break;
                case 'd': case 'D': if(curseur.colonne<COLONNES-1) curseur.colonne++; break;
                case ' ':
                    if(!curseur.selectionActive) {
                        curseur.selectionActive=1;
                        curseur.selLigne=curseur.ligne;
                        curseur.selColonne=curseur.colonne;
                    } else {
                        if(permutationValide(grille,curseur.selLigne,curseur.selColonne,curseur.ligne,curseur.colonne)) {
                            p->coupsRestants--;
                            stabiliserGrille(grille,p,p->niveau);
                        }
                        curseur.selectionActive=0;
                    }
                    break;
                case 27:
                    return -1;
            }
        }
        int objectifsRestants=0;
        for(int i=1;i<=NB_ITEMS;i++) objectifsRestants+=p->objectifs[i];
        if(objectifsRestants<=0) return 1;
        if(p->coupsRestants<=0) return 0;
        Sleep(50);
    }

    return 0;
}

void sauvegarderPartie(Partie p) { 
    char pseudo[50];
    char choix;

    clrscr();
    printf("Voulez-vous sauvegarder la partie ?\n O pour Oui, N pour Non  ");
    choix = getch();

    if(choix == 'O' || choix == 'o') {
        printf("\nEntrez votre pseudo pour sauvegarder : ");
        scanf("%49s", pseudo);

        FILE *f = fopen("sauvegarde.txt","a");
        if(f) {
            fprintf(f,"%s %d %d %d %lld %d %d %d %d %d %d\n",pseudo, p.niveau, p.vies, p.coupsRestants, p.debutNiveau,p.objectifs[1],p.objectifs[2],p.objectifs[3],p.objectifs[4],p.objectifs[5],0);
            fclose(f);
            printf("Partie sauvegardee\n");
            Sleep(1500);
        } else {
            printf("Erreur de sauvegarde.\n");
            Sleep(1500);
        }
    } else {
        printf("\nPartie non sauvegardee\n");
        Sleep(1000);
    }
}


int chargerPartie(Partie *p) {
    char pseudo[50], ligne[200];
    clrscr();
    printf("Entrez votre pseudo pour charger la partie : ");
    scanf("%49s", pseudo);

    FILE *f = fopen("sauvegarde.txt","r");
    if(!f) return 0;

    while(fgets(ligne,sizeof(ligne),f)) {
        char fichierPseudo[50];
        int n,v,c,objet1,objet2,objet3,objet4,objet5;
        long t;
        sscanf(ligne,"%s %d %d %d %ld %d %d %d %d %d %*d",fichierPseudo,&n,&v,&c,&t,&objet1,&objet2,&objet3,&objet4,&objet5);
        if(strcmp(fichierPseudo,pseudo)==0) {
            p->niveau = n;
            p->vies = v;
            p->coupsRestants = c;
            p->debutNiveau = t;
            p->objectifs[1]=objet1;
            p->objectifs[2]=objet2;
            p->objectifs[3]=objet3;
            p->objectifs[4]=objet4;
            p->objectifs[5]=objet5;
            fclose(f);
            return 1;
        }
    }
    fclose(f);
    return 0;
}

////////////////////////////////////////////////////////// Affichage.c
#include "fonctions.h"

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
            if (curseur.ligne == i && curseur.colonne == j) {
                bg_color(DARKGRAY);
            } else if (curseur.selectionActive && curseur.selLigne == i && curseur.selColonne == j) {
                bg_color(LIGHTGRAY);
            } else {
                bg_color(BLACK);
            }
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
    gotoxy(45, y++); printf("Temps restant : %d s  ", tempsRestant);
    y++;

    gotoxy(45, y++); printf("Objectifs :");
    for(int i=1; i<=NB_ITEMS; i++) {
        gotoxy(47, y++); printf("Item %d : %d   ", i, p.objectifs[i]);
    }
}

////////////////////////////////////////////////////////// Jeu.c
#include "fonctions.h"
   
void initialiserGrille(int grille[LIGNES][COLONNES], int niveau) {
    int i, j;
    srand((unsigned int)time(NULL));

    do {
        for (i = 0; i < LIGNES; i++) {
            for (j = 0; j < COLONNES; j++) {
                grille[i][j] = (rand() % NB_ITEMS) + 1;
            }
        }
    } while (!verifierGrilleInitiale(grille));
}

int verifierGrilleInitiale(int grille[LIGNES][COLONNES]) {
    Partie temp = {0};
    return !(detecterSuites4(grille, &temp) ||
             detecterSuites6(grille, &temp) ||
             detecterCroix(grille, &temp) ||
             detecterCarre(grille, &temp));
}

int permutationValide(int grille[LIGNES][COLONNES], int l1, int c1, int l2, int c2) {
    int temp = grille[l1][c1];
    grille[l1][c1] = grille[l2][c2];
    grille[l2][c2] = temp;

    Partie tempPartie = {0};
    int valide = detecterSuites4(grille, &tempPartie) ||
                 detecterSuites6(grille, &tempPartie) ||
                 detecterCroix(grille, &tempPartie) ||
                 detecterCarre(grille, &tempPartie);

    if (!valide) {
        temp = grille[l1][c1];
        grille[l1][c1] = grille[l2][c2];
        grille[l2][c2] = temp;
    }
    return valide;
}

int detecterSuites4(int grille[LIGNES][COLONNES], Partie *p) {
    int i, j, count = 0;
    for (i = 0; i < LIGNES; i++) {
        for (j = 0; j < COLONNES - 3; j++) {
            int val = grille[i][j];
            if (val > 0 &&
                val == grille[i][j+1] &&
                val == grille[i][j+2] &&
                val == grille[i][j+3]) {
                // Suppression des items
                grille[i][j] = grille[i][j+1] = grille[i][j+2] = grille[i][j+3] = ITEM_VIDE;
                if(p) p->objectifs[val]--;
                count++;
            }
        }
    }
    for (j = 0; j < COLONNES; j++) {
        for (i = 0; i < LIGNES - 3; i++) {
            int val = grille[i][j];
            if (val > 0 &&
                val == grille[i+1][j] &&
                val == grille[i+2][j] &&
                val == grille[i+3][j]) {
                grille[i][j] = grille[i+1][j] = grille[i+2][j] = grille[i+3][j] = ITEM_VIDE;
                if(p) p->objectifs[val]--;
                count++;
            }
        }
    }
    return count;
}

int detecterSuites6(int grille[LIGNES][COLONNES], Partie *p) {
    int i, j, count = 0;
    for (i = 0; i < LIGNES; i++) {
        for (j = 0; j < COLONNES - 5; j++) {
            int val = grille[i][j];
            int k, ok = 1;
            for (k = 1; k < 6; k++)
                if (grille[i][j+k] != val) { ok = 0; break; }
            if (ok && val > 0) {
                for (i=0;i<LIGNES;i++)
                    for(j=0;j<COLONNES;j++)
                        if(grille[i][j]==val) { grille[i][j]=ITEM_VIDE; if(p) p->objectifs[val]--; }
                count++;
            }
        }
    }
    for (j = 0; j < COLONNES; j++) {
        for (i = 0; i < LIGNES - 5; i++) {
            int val = grille[i][j], k, ok=1;
            for(k=1;k<6;k++)
                if(grille[i+k][j]!=val){ok=0;break;}
            if(ok && val>0){
                for(int ii=0;ii<LIGNES;ii++)
                    for(int jj=0;jj<COLONNES;jj++)
                        if(grille[ii][jj]==val){grille[ii][jj]=ITEM_VIDE;if(p)p->objectifs[val]--;}
                count++;
            }
        }
    }
    return count;
}

int detecterCroix(int grille[LIGNES][COLONNES], Partie *p) {
    int i,j,count=0;
    for(i=1;i<LIGNES-1;i++){
        for(j=1;j<COLONNES-1;j++){
            int val = grille[i][j];
            if(val>0 &&
               val==grille[i-1][j] && val==grille[i+1][j] &&
               val==grille[i][j-1] && val==grille[i][j+1]){
                // supprimer ligne et colonne
                for(int x=0;x<LIGNES;x++) if(grille[x][j]==val){grille[x][j]=ITEM_VIDE;if(p)p->objectifs[val]--;}
                for(int y=0;y<COLONNES;y++) if(grille[i][y]==val){grille[i][y]=ITEM_VIDE;if(p)p->objectifs[val]--;}
                count++;
            }
        }
    }
    return count;
}

int detecterCarre(int grille[LIGNES][COLONNES], Partie *p) {
    int i,j,count=0;
    for(i=0;i<LIGNES-3;i++){
        for(j=0;j<COLONNES-3;j++){
            int val = grille[i][j],ok=1;
            for(int ii=0;ii<4;ii++)
                for(int jj=0;jj<4;jj++)
                    if(grille[i+ii][j+jj]!=val){ok=0;break;}
            if(ok && val>0){
                for(int ii=0;ii<4;ii++)
                    for(int jj=0;jj<4;jj++){
                        grille[i+ii][j+jj]=ITEM_VIDE;
                        if(p) p->objectifs[val]--;
                    }
                count++;
            }
        }
    }
    return count;
}

void appliquerGravite(int grille[LIGNES][COLONNES]) {
    for(int j=0;j<COLONNES;j++){
        for(int i=LIGNES-2;i>=0;i--){
            if(grille[i][j]!=ITEM_VIDE){
                int ligne=i;
                while(ligne+1<LIGNES && grille[ligne+1][j]==ITEM_VIDE){
                    grille[ligne+1][j]=grille[ligne][j];
                    grille[ligne][j]=ITEM_VIDE;
                    ligne++;
                }
            }
        }
    }
}

void remplirCasesVides(int grille[LIGNES][COLONNES], int niveau) {
    srand((unsigned int)time(NULL));
    for(int i=0;i<LIGNES;i++)
        for(int j=0;j<COLONNES;j++)
            if(grille[i][j]==ITEM_VIDE)
                grille[i][j]=(rand()%NB_ITEMS)+1;
}

int stabiliserGrille(int grille[LIGNES][COLONNES],Partie *p,int niveau){
    int total;
    do{
        total=0;
        total+=detecterSuites4(grille,p);
        total+=detecterSuites6(grille,p);
        total+=detecterCroix(grille,p);
        total+=detecterCarre(grille,p);
        appliquerGravite(grille);
        remplirCasesVides(grille,niveau);
    }while(total>0);
    return total;
}

void activerBonusCouleur(int grille[LIGNES][COLONNES], int type, Partie *p){
    for(int i=0;i<LIGNES;i++)
        for(int j=0;j<COLONNES;j++)
            if(grille[i][j]==type){grille[i][j]=ITEM_VIDE;if(p)p->objectifs[type]--;}
    appliquerGravite(grille);
    remplirCasesVides(grille,p->niveau);
}
////////////////////////////////////////////////////////// Main.c
#include "fonctions.h"

int main() {
    SetConsoleOutputCP(CP_UTF8); //Si on veut utiliser des caracteres speciaux 
    system("chcp 65001");
    int choix;
    int quitter = 0;

    while(!quitter) {
        afficherMenu();
        choix = getch() - '0'; // lecture du chiffre

        switch(choix) {
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
}*/