#include "affichage.h"

// Fonnction de test pour les différentes fonctions du module jeu 
/*Modifications réalisées 
initialiserGrille => enlève le int niveau de l'initialisation */


/* =========================================================
   INITIALISATION DE LA GRILLE
   ========================================================= */
   
void initialiserGrille(int grille[LIGNES][COLONNES], int niveau) {
    int i, j;
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

    if (abs(l1 - l2) + abs(c1 - c2) != 1)
        return 0;

    int copie[LIGNES][COLONNES];
    for(int i=0;i<LIGNES;i++)
        for(int j=0;j<COLONNES;j++)
            copie[i][j] = grille[i][j];

    int temp = copie[l1][c1];
    copie[l1][c1] = copie[l2][c2];
    copie[l2][c2] = temp;

    Partie tempPartie = {0};

    int valide =
        detecterSuites4(copie, &tempPartie) ||
        detecterSuites6(copie, &tempPartie) ||
        detecterCroix(copie, &tempPartie) ||
        detecterCarre(copie, &tempPartie);

    if(valide) {
        temp = grille[l1][c1];
        grille[l1][c1] = grille[l2][c2];
        grille[l2][c2] = temp;
    }

    return valide;
}


void initialiserObjectifs(Partie* p) {
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
int detecterSuites4(int grille[LIGNES][COLONNES], Partie* p) {
    int i, j, count = 0;
    for (i = 0; i < LIGNES; i++) {
        for (j = 0; j < COLONNES - 3; j++) {
            int val = grille[i][j];
            if (val > 0 &&
                val == grille[i][j+1] &&
                val == grille[i][j+2] &&
                val == grille[i][j+3]) {
                grille[i][j] = grille[i][j+1] = grille[i][j+2] = grille[i][j+3] = ITEM_VIDE;
                if(p) p->objectifs[val]-=4;
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
                if(p) p->objectifs[val]-=4;
                count++;
            }
        }
    }
    return count;
}

int detecterSuites6(int grille[LIGNES][COLONNES], Partie* p) {
    for (int i = 0; i < LIGNES; i++) {
        for (int j = 0; j <= COLONNES - 6; j++) {
            int val = grille[i][j];
            if (val <= 0) continue;

            int ok = 1;
            for (int k = 1; k < 6; k++)
                if (grille[i][j+k] != val) { ok = 0; break; }

            if (ok) {
                int supprimes = 0;
                for (int ii = 0; ii < LIGNES; ii++)
                    for (int jj = 0; jj < COLONNES; jj++)
                        if (grille[ii][jj] == val) {
                            grille[ii][jj] = ITEM_VIDE;
                            supprimes++;
                        }

                if (p) p->objectifs[val] -= supprimes;

                return 1; // une seule fois
            }
        }
    }
    return 0;
}

int detecterCroix(int grille[LIGNES][COLONNES], Partie* p) {
    for (int i = 1; i < LIGNES - 1; i++) {
        for (int j = 1; j < COLONNES - 1; j++) {
            int val = grille[i][j];
            if (val > 0 &&
                val == grille[i-1][j] && val == grille[i+1][j] &&
                val == grille[i][j-1] && val == grille[i][j+1]) {

                int supprimes = 0;

                for (int x = 0; x < LIGNES; x++) {
                    if (grille[x][j] == val) {
                        grille[x][j] = ITEM_VIDE;
                        supprimes++;
                    }
                }

                for (int y = 0; y < COLONNES; y++) {
                    if (grille[i][y] == val) {
                        grille[i][y] = ITEM_VIDE;
                        supprimes++;
                    }
                }

                // centre compté deux fois → corriger
                supprimes--;

                if (p) p->objectifs[val] -= supprimes;
                return 1;
            }
        }
    }
    return 0;
}

int detecterCarre(int grille[LIGNES][COLONNES], Partie* p) {
    for (int i = 0; i <= LIGNES - 4; i++) {
        for (int j = 0; j <= COLONNES - 4; j++) {

            int val = grille[i][j];
            if (val <= 0) continue;

            // 1️⃣ Vérifier que les 16 cases du carré sont bien de type val
            int ok = 1;
            for (int ii = 0; ii < 4 && ok; ii++)
                for (int jj = 0; jj < 4; jj++)
                    if (grille[i+ii][j+jj] != val) {
                        ok = 0;
                        break;
                    }

            if (ok) {
                int supprimes = 0;

                // 2️⃣ Supprimer TOUS les items val DANS la zone du carré
                // (y compris ceux "au centre")
                for (int ii = 0; ii < 4; ii++) {
                    for (int jj = 0; jj < 4; jj++) {
                        if (grille[i+ii][j+jj] == val) {
                            grille[i+ii][j+jj] = ITEM_VIDE;
                            supprimes++;
                        }
                    }
                }

                // 3️⃣ Mise à jour des objectifs
                if (p) p->objectifs[val] -= supprimes;
                return 1; // une seule activation par stabilisation
            }
        }
    }
    return 0;
}

int existePermutation(int grille[LIGNES][COLONNES]) {
    int copie[LIGNES][COLONNES];

    for(int i=0;i<LIGNES;i++)
        for(int j=0;j<COLONNES;j++)
            copie[i][j] = grille[i][j];

    for(int i=0;i<LIGNES;i++){
        for(int j=0;j<COLONNES;j++){
            if(j+1<COLONNES && permutationValide(copie,i,j,i,j+1)) return 1;
            if(i+1<LIGNES && permutationValide(copie,i,j,i+1,j)) return 1;
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
void appliquerGravite(int grille[LIGNES][COLONNES], Partie* p) {
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
    for(int i=0;i<LIGNES;i++)
        for(int j=0;j<COLONNES;j++)
            if(grille[i][j]==ITEM_VIDE)
                grille[i][j]=(rand()%NB_ITEMS)+1;
}

int stabiliserGrille(int grille[LIGNES][COLONNES],Partie* p,int niveau){
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
    for(int i=1; i<=NB_ITEMS; i++){
        if(p&& p->objectifs[i]<0){
            p->objectifs[i]=0;
        }
    }
    return total;
}


/*#include "affichage.h"
   
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

    if (!valide) { // annule permutation
        temp = grille[l1][c1];
        grille[l1][c1] = grille[l2][c2];
        grille[l2][c2] = temp;
    }
    return valide;
}

void initialiserObjectifs(Partie* p) {
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

int detecterSuites4(int grille[LIGNES][COLONNES], Partie* p) {
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

int detecterSuites6(int grille[LIGNES][COLONNES], Partie* p) {
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

int detecterCroix(int grille[LIGNES][COLONNES], Partie* p) {
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

int detecterCarre(int grille[LIGNES][COLONNES], Partie* p) {
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

void appliquerGravite(int grille[LIGNES][COLONNES], Partie* p) {
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

int stabiliserGrille(int grille[LIGNES][COLONNES],Partie* p,int niveau){
    int total;
    do{
        total=0;
        total+=detecterSuites4(grille,p);
        total+=detecterSuites6(grille,p);
        total+=detecterCroix(grille,p);
        total+=detecterCarre(grille,p);
        remplirCasesVides(grille,niveau);
        appliquerGravite(grille, p);
        remplirCasesVides(grille,niveau);
    }while(total>0);
    return total;
}
*/

