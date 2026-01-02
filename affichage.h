#ifndef AFFICHAGE_H
#define AFFICHAGE_H

/* =========================================================
   INCLUDES
   ========================================================= */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <wchar.h>
#include "fonctions.h"

/* =========================================================
   CONSTANTES DU JEU (MODIFIABLES POUR LA JOUABILITE)
   ========================================================= */

/* Dimensions de la grille */
#define LIGNES 8
#define COLONNES 12

/* =========================================================
   PROTOTYPES - MODULE AFFICHAGE (affichage.c)
   ========================================================= */

/* Menus */
int afficherMenu();
void afficherRegles();

void remiseAZero();
void afficheLigne(const char* motifDebut, const char* motif, const char* motifFin);
void afficherCadre();
void afficherItems(int grille[LIGNES][COLONNES], Curseur curseur);

/* Affichage du jeu */
void afficherGrille(int grille[LIGNES][COLONNES], Curseur curseur);
void afficherInformations(Partie* p, int tempRestant);

void afficherAnimationNiveau(int grille[LIGNES][COLONNES], Curseur curseur);

#endif /* AFFICHAGE_H */

