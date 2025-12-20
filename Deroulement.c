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

    while (continuer && p->vies > 0 && p->niveau <= NB_NIVEAUX) {

        // Toujours s'assurer que les objectifs sont corrects au début du niveau
        initialiserObjectifs(p);

        resultat = jouerNiveau(p);

        if (resultat == 1) { // ✅ Niveau réussi
            p->niveau++;

            if (p->niveau == 2)
                p->coupsRestants = COUPS_NIV2;
            else if (p->niveau == 3)
                p->coupsRestants = COUPS_NIV3;

            p->debutNiveau = time(NULL);
        }
        else if (resultat == 0) { // ❌ Niveau échoué
            p->vies--;

            if (p->vies > 0) {
                clrscr();
                printf("\nPerte d'une vie !\n");
                Sleep(2000);

                // 🔥 IMPORTANT : réinitialiser les objectifs du niveau
                initialiserObjectifs(p);
            }
            else {
                clrscr();
                printf("\nGAME OVER\n");
                continuer = 0;
                Sleep(2000);
            }
        }
        else { // ⏹ Quitter
            sauvegarderPartie(*p);
            continuer = 0;
        }
    }

    if (p->niveau > NB_NIVEAUX && p->vies > 0) {
        clrscr();
        printf("JEU TERMINE, BRAVO !\n");
        Sleep(2000);
    }
}


/*void partieEnCours(Partie *p) {
    int continuer = 1;
    int resultat;

    while(continuer && p->vies>0 && p->niveau<=NB_NIVEAUX) {
        resultat = jouerNiveau(p);

        if(resultat==1) { // Niveau réussi
            p->niveau++;
            if(p->niveau==2){
                 p->coupsRestants = COUPS_NIV2;
                 for(int i=1; i<=NB_ITEMS; i++) p->objectifs[i] = OBJECTIFS_NIV2[i];
            }
            else if(p->niveau==3){
                p->coupsRestants = COUPS_NIV3;
                for(int i=1; i<=NB_ITEMS; i++) p->objectifs[i]=OBJECTIFS_NIV3[i];
            } 
            p->debutNiveau = time(NULL);
        } else if(resultat==0) {
            p->vies--;
            if(p->vies>0) {
                clrscr();
                printf("\nPerte d'une vie !\n");
                objectifs[]=
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
}*/

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
    int rafraichir =1;

    if(p->niveau==1) tempsMax = TEMPS_NIV1;
    else if(p->niveau==2) tempsMax = TEMPS_NIV2;
    else tempsMax = TEMPS_NIV3;

    initialiserGrille(grille, p->niveau);
    stabiliserGrille(grille,p,p->niveau);
    clrscr();
    afficherCadre();

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
                case 'z': case 'Z': case 72:if(curseur.ligne>0) curseur.ligne--;rafraichir=1; break;
                case 's': case 'S': case 80:if(curseur.ligne<LIGNES-1) curseur.ligne++;rafraichir=1; break;
                case 'q': case 'Q': case 75:if(curseur.colonne>0) curseur.colonne--;rafraichir=1; break;
                case 'd': case 'D': case 77:if(curseur.colonne<COLONNES-1) curseur.colonne++;rafraichir=1; break;
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
                    rafraichir=1;
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
        if(rafraichir){
            afficherGrille(grille,curseur);
            afficherInformations(*p,tempsRestant);
            rafraichir = 0;
        }
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

/*#include "fonctions.h"


void nouvellePartie() {
    Partie p;
    p.niveau = 1;
    p.vies = VIES_INITIALES;
    p.coupsRestants = COUPS_NIV1;
    initialiserObjectifs(&p);
    p.debutNiveau = time(NULL);

    partieEnCours(&p);
}

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
*/