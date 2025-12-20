#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <wchar.h>

#include "affichage.h"
#include "affichage_console.h"

int main() {
    Curseur curseur = {0,0,0,0,0};
    int grille[LIGNES][COLONNES];
    grille [0][0] = ITEM_1;
    grille [0][1] = ITEM_2;
    grille [0][2] = ITEM_3;
    grille [0][3] = ITEM_4;
    grille [0][4] = ITEM_5;
    afficherItems(grille, curseur);
    return 0;
}

