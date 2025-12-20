#ifndef FONCTIONS_H
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

void remiseAZero();
void afficheLigne(const char* motifDebut, const char* motif, const char* motifFin);
void afficherCadre();
void afficherItems(int grille[LIGNES][COLONNES], Curseur curseur);

/* Affichage du jeu */
void afficherGrille(int grille[LIGNES][COLONNES], Curseur curseur);
void afficherInformations(Partie p, int tempRestant);

void afficherAnimationNiveau(int grille[LIGNES][COLONNES], Curseur curseur);
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

#endif /* FONCTIONS_H */

/*#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>

// module affichage 
void afficherMenu(); // entree : rien, sortie => int de selection
void afficherRegles(); // ni entree ni sortie 
void afficherGrille(int grille[lignes][colonnes]); // entre : dimentions de la grille, sorite : rien, lignes et colonnes a modifier peut etre 
void afficherBonbons(int ligne); // entree : cases de la matrice (avoir si il y a un bonbon ou non), sortie : rien
void afficherInformations(int niveau, int coeurs, int objVert, int objRouge, int objBleu, int objJaune, int tempsRestants, int nbrCoups);
void afficherSelection(int positionJoueur, int selection);


// module jeu 
void grilleDeJeu(int grille[][]);
int apparitionBonbons(int grille[][]);
void permutationBonbons(int grille[][], int selection);
void deplacementJoueur();
void selectionJoueur(int emplacementJoueur);
int disparitionBonbons(int grille[][]);
int detecterSuite4(int grille[][]);
int detecterSuite6(int grille[][]);
int detecterCroix(int grille[][]);
int detecterCarre([][]);


// module deroulement 
int objectifsEnJeu(int objBleu, int objVert, int objJaune, int objVert);
void nouvelleParite();
void sauvegarde();
void partieEnCours(int niveau, int coeurs);
void niveau1();
void niveaux();*/



/*#ifndef FONCTIONS_H
#define FONCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <wchar.h>

#include "affichage_console.h"

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
#define TEMPS_NIV1  90 
#define OBJECTIFS_NIV1 {5,5,5,5,5}
#define OBJECTIFS_NIV2 {10,15,5,10,15}
#define OBJECTIFS_NIV3 {20,25,10,20,5}

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

void afficherMenu();
void afficherRegles();

void afficherGrille(int grille[LIGNES][COLONNES], Curseur curseur);
void afficherInformations(Partie p, int tempRestant);

void initialiserGrille(int grille[LIGNES][COLONNES], int niveau);
int verifierGrilleInitiale(int grille[LIGNES][COLONNES]);

int permutationValide(int grille[LIGNES][COLONNES], int l1, int c1, int l2, int c2);
void initialiserObjectifs(Partie *p);

int detecterSuites4(int grille[LIGNES][COLONNES], Partie *p);
int detecterSuites6(int grille[LIGNES][COLONNES], Partie *p);
int detecterCroix(int grille[LIGNES][COLONNES], Partie *p);
int detecterCarre(int grille[LIGNES][COLONNES], Partie *p);

int appliquerSuppressions(int grille[LIGNES][COLONNES], Partie *p);

int existePermutation(int grille[LIGNES][COLONNES]);
void melangerGrille(int grille[LIGNES][COLONNES]);

void appliquerGravite(int grille[LIGNES][COLONNES], Partie *p);
void remplirCasesVides(int grille[LIGNES][COLONNES], int niveau);
int stabiliserGrille(int grille[LIGNES][COLONNES], Partie *p, int niveau);

void nouvellePartie();
void partieEnCours(Partie *p);

int jouerNiveau(Partie *p);

void sauvegarderPartie(Partie p);
int chargerPartie(Partie *p);

#endif

#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>

// module affichage 
void afficherMenu(); // entree : rien, sortie => int de selection
void afficherRegles(); // ni entree ni sortie 
void afficherGrille(int grille[lignes][colonnes]); // entre : dimentions de la grille, sorite : rien, lignes et colonnes a modifier peut etre 
void afficherBonbons(int ligne); // entree : cases de la matrice (avoir si il y a un bonbon ou non), sortie : rien
void afficherInformations(int niveau, int coeurs, int objVert, int objRouge, int objBleu, int objJaune, int tempsRestants, int nbrCoups);
void afficherSelection(int positionJoueur, int selection);


// module jeu 
void grilleDeJeu(int grille[][]);
int apparitionBonbons(int grille[][]);
void permutationBonbons(int grille[][], int selection);
void deplacementJoueur();
void selectionJoueur(int emplacementJoueur);
int disparitionBonbons(int grille[][]);
int detecterSuite4(int grille[][]);
int detecterSuite6(int grille[][]);
int detecterCroix(int grille[][]);
int detecterCarre([][]);


// module deroulement 
int objectifsEnJeu(int objBleu, int objVert, int objJaune, int objVert);
void nouvelleParite();
void sauvegarde();
void partieEnCours(int niveau, int coeurs);
void niveau1();
void niveaux();*/
