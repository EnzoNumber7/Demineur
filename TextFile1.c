// Démineurs.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define sizeMine 10
#define sizeTab 81

void printGame(char* tab);
int verificationMine(int* mine, int lineChoice, int columnChoice);

int main()
{
    // Création et affichage du tableau de jeu
    int i = 0;
    char * tab[sizeTab];
    tab[0] = "a";
    /*for (i = 0; i < sizeTab; i++) {
        tab[i] = ;
    }*/

    printGame(tab);


    // Placement des mines
    // Faire en sorte de ne pas perdre tour 1
    srand(time(0));

    int mine[10];
    i = 0;
    for (i = 0; i < 10; i++) {
        mine[i] = rand() % 80;
    }

    // Boucle de Jeu
    int lose = 0;

    while (lose == 0) {
        int lineChoice, columnChoice, input;
        printf("%d", mine[1]);

        printf("Choisissez une ligne");
        input = scanf("%d", &lineChoice);

        printf("Choisissez une colone");
        input = scanf("%d", &columnChoice);

        lose = verificationMine(mine, lineChoice, columnChoice);

    }


}

void printGame(char* tab) {
    int numberLine = (int)sqrt(sizeTab);
    int i = 0;
    int j = 0;
    printf(" |1||2||3||4||5||6||7||8||9|\n");
    for (i = 0; i < numberLine; i++) {
        printf("%d", i + 1);
        for (j = 0; j < numberLine; j++) {
            printf("|%c|", tab[i * 9 + j]);
        }
        printf("\n");
    }

}

int verificationMine(int* mine, int lineChoice, int columnChoice) {
    int numberLine = (int)sqrt(sizeTab);
    int i = 0;
    int placement = (lineChoice - 1) * numberLine + (columnChoice);

    for (i = 0; i < sizeMine; i++) {
        if (placement == mine[i]) { return 1; }
    }
    return 0;
}

/*
* Fonction numberMine qui prend en paramêtre le tableau, le tableau de mine et
*/


