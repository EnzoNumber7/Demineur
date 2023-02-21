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
int verificationMine(int* mine, int lineChoice, int columnChoice, char * tab );

int main()
{
    // Création et affichage du tableau de jeu
    int i = 0;
    char tab[sizeTab];
    for (i = 0; i < sizeTab; i++) {
        tab[i] = '_';
    }

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
        input=scanf("%d", &lineChoice);

        printf("Choisissez une colone");
        input=scanf("%d", &columnChoice);

        lose = verificationMine(mine, lineChoice, columnChoice,tab);
        printGame(tab);
        if (lose==1){
            printf("perdu !");
        }
    }

    
}

void printGame(char * tab) {
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

int verificationMine(int* mine, int lineChoice, int columnChoice, char * tab) {
    int numberLine = (int)sqrt(sizeTab);
    int i = 0;
    int placement = (lineChoice - 1) * numberLine + (columnChoice);

    for (i = 0; i < sizeMine; i++) {
        if (placement == mine[i]) {
            tab[placement-1] = 'M';
            return 1; 
        }
    }
    return 0;
}

/*
* Fonction mineProximity qui prend en paramêtre le tableau, le tableau de mine et la ligne et la colone du joueur qui renvoie
* Initialisation de numberLine qui vaut racine de sizeTab
* Initialisation de i à 0
* Initialisation de nbMine à 0
* Initialisation et calcul du placement du joueur sur le tableau
* Pour i de 0 a taille du tableau de mine
* 
*   Si placement est inferieur à 72                                                                 On verif si on est pas en bas
*       Si placement+9 est égale à mine de i On ajoute 1 à nbMine                                   On verif si la case du dessous est une mine 
*       
*       Si le reste de la division euclidienne de placement par numberLine est differente de 8      On verif si on est pas à droite 
*           Alors Si placement+10 est égale à mine de i On ajoute 1 à nbMine                        On verif si la case en bas à droite est une mine  
*           
*       Si le reste de la division euclidienne de placement par numberLine est differente de 0      On verif si on est pas à gauche
*           Alors si placement+8 est égale à mine de i On ajoute 1 à nbMine                         On verif si la case en bas à gauche est une mine
* 
*   Si placement est supérieur à 9                                                                  On verif si on est pas en haut
        Si placement-9 est égale à mine de i On ajoute 1 à nbMine                                   On verif si la case du dessus est une mine
*
*       Si le reste de la division euclidienne de placement par numberLine est differente de 8      On verif si on est pas à droite
*           Alors Si placement-10 est égale à mine de i On ajoute 1 à nbMine                        On verif si la case en haut à droite est une mine
*
*       Si le reste de la division euclidienne de placement par numberLine est differente de 0      On verif si on est pas à gauche
*           Alors si placement-8 est égale à mine de i On ajoute 1 à nbMine                         On verif si la case en haut à gauche est une mine
*/
