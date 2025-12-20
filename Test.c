#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <wchar.h>

#include "fonctions.h"

void afficherAnimationNiveau() {
    int width = 40;
    int height = 10;
    int step, x, y;
    printf("NIVEAU REUSSI !!!\n");
    Sleep(100);
    for (step = 0; step < 6; step++) {
        for (y = 0; y < height; y++) {
            for (x = 0; x < width; x++) {
                if (x == width / 2 && y == height / 2 - step) {
                    printf("*");
                }
                else if ((rand() % (step + 2) == 0) && y >= height / 2 - step && y <= height / 2 + step) {
                    printf("*");
                } else {
                    printf(" ");
                }
            }
            printf("\n");
        }

        for (volatile long delay = 0; delay < 100000000; delay++); 
        Sleep(50);
        clrscr();
    }

    printf("\nNIVEAU SUIVANT\n");
    Sleep(150);
}

int main() {
    afficherAnimationNiveau();
    return 0;
}

