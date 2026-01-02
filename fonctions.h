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

////////////////////////////////////////// Constantes 

//Dimentions de la grille et nombre d'items 
#define LIGNES 8
#define COLONNES 12

// Definitions des items 
#define NB_ITEMS 5
#define ITEM_VIDE   0
#define ITEM_1      1
#define ITEM_2      2
#define ITEM_3      3
#define ITEM_4      4
#define ITEM_5      5
#define ITEM_BONUS  6 
#define ITEM_JOKER  7  

// Definition des parametres des niveaux 
#define NB_NIVEAUX  3
#define VIES_INITIALES 3

#define COUPS_NIV1  15
#define TEMPS_NIV1  120
#define OBJECTIFS_NIV1 {5,5,5,5,5}

#define COUPS_NIV2  25
#define TEMPS_NIV2  150
#define OBJECTIFS_NIV2 {10,15,5,10,15}

#define COUPS_NIV3  30
#define TEMPS_NIV3  200
#define OBJECTIFS_NIV3 {20,25,10,20,5}

//////////////////////////////////////////// Structures 

// Données d'un niveau 
typedef struct {
    int niveau;
    int vies;
    int coupsRestants;
    int objectifs[NB_ITEMS+1];
    time_t debutNiveau;
} Partie;

// Données de la grille en jeu
typedef struct {
    int ligne;
    int colonne;
    int selectionActive;
    int selLigne;
    int selColonne;
} Curseur;

// Prototypes du module affichage 


void afficherMenu();
void afficherRegles();
void remiseAZero(); // Fonction qui remet le curseur en haut de la page quand il arrive en bas 
void afficheLigne(const char* motifDebut, const char* motif, const char* motifFin); // Fonction qui affiche la grille
void afficherCadre();
void afficherItems(int grille[LIGNES][COLONNES], Curseur curseur);
void afficherGrille(int grille[LIGNES][COLONNES], Curseur curseur);
void afficherInformations(Partie p, int tempRestant);

// Animations de niveau
void animationNiveauGagne(int niveau);
void animationNiveauPerdu(int viesRestantes);
void animationJeuGagne();
void animationGameOver();


// Prototypes du module jeu 


void initialiserGrille(int grille[LIGNES][COLONNES], int niveau);
int verifierGrilleInitiale(int grille[LIGNES][COLONNES]); // Verification qu'il n'y a pas de suites dans la grille initiale 

int permutationValide(int grille[LIGNES][COLONNES], int l1, int c1, int l2, int c2); // Test de validité de la permutation
void initialiserObjectifs(Partie *p); // Gestion des objectifs de niveau 

int detecterSuites4(int grille[LIGNES][COLONNES], Partie *p);
int detecterSuites6(int grille[LIGNES][COLONNES], Partie *p);
int detecterCroix(int grille[LIGNES][COLONNES], Partie *p);
int detecterCarre(int grille[LIGNES][COLONNES], Partie *p);

int existePermutation(int grille[LIGNES][COLONNES]); // Verification qu'il existe des permutations dans la grille 
void melangerGrille(int grille[LIGNES][COLONNES]); // Mélange de la grille 

// Gestion de la grille et des cases vides 
void appliquerGravite(int grille[LIGNES][COLONNES], Partie *p); 
void remplirCasesVides(int grille[LIGNES][COLONNES], int niveau);
int stabiliserGrille(int grille[LIGNES][COLONNES], Partie *p, int niveau);

// Prototypes du module deroulement 

void nouvellePartie();
void partieEnCours(Partie *p); // Gestion de la partie 

int jouerNiveau(Partie *p);// gestion du niveau en cours 

// Gestions des sauvegardes 
void sauvegarderPartie(Partie p);
int chargerPartie(Partie *p);

#endif