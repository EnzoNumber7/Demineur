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
void mineProximity(char* tab, int* mine, int lineChoice, int columnChoice);

int main()
{
    // Création et affichage du tableau de jeu et initialisation du tableau de mines
    int mine[10];
    int i = 0;
    char tab[sizeTab];
    for (i = 0; i < sizeTab; i++) {
        tab[i] = '_';
    }

    printGame(tab);

    // Premier tour de jeu, le joueur ne peut pas perdre donc on place les mines sur la tableau après le premier coup du joueur
    int lineChoice, columnChoice, input;

    printf("Choisissez une ligne");
    input = scanf("%d", &lineChoice);

    printf("Choisissez une colone");
    input = scanf("%d", &columnChoice);


    // Placement des mines
    time_t t;
    srand((unsigned)time(&t));
	int numberLine = (int)sqrt(sizeTab);
	int placement = (lineChoice - 1) * numberLine + (columnChoice - 1);
    mine[0] = rand() % 80;
    if (mine[0] == placement) {
        mine[0] = rand() % 80;
    }
    i = 1;
    int j = 0;
    for (i = 1; i < 10; i++) {
        mine[i] = rand() % 80;
        if (mine[i]==placement){
			mine[i] = rand() % 80;
        }
            
        for (j = 0; j < i; j++) {
            if (mine[i] == mine[j] ) {
                j = 0;
                mine[j] = rand() % 80;
            }
        }
        
    }

    i = 0;
    for (i = 0; i < 10; i++) {
        printf("%d /", mine[i]);
    }

    int lose = 0;
    mineProximity(tab, mine, lineChoice, columnChoice);
    printGame(tab);

    // Boucle de Jeu

    while (lose == 0) {
        printf("%d", mine[1]);

        printf("Choisissez une ligne");
        input=scanf("%d", &lineChoice);

        printf("Choisissez une colone");
        input=scanf("%d", &columnChoice);

        lose = verificationMine(mine, lineChoice, columnChoice,tab);
        if (lose == 0) {
            mineProximity(tab, mine, lineChoice, columnChoice);
            printGame(tab);
        }
        
        
        if (lose==1){
            printGame(tab);
            printf("perdu !");
        }
    }

    
}

void printGame(char * tab) {
    // Fonction qui prend en paramètre le tableau de jeu et permet de l'afficher
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
    // Fonction qui prend en paramètre le tableau contenant le placement des mines, le tableau de jeu, la ligne et la colone séléctionner par le joueur
    int numberLine = (int)sqrt(sizeTab);
    int i = 0;
    int placement = (lineChoice -1) * numberLine + (columnChoice -1);

    for (i = 0; i < sizeMine; i++) {
        if (placement == mine[i]) {
            tab[placement] = 'M';
            return 1; 
        }
    }
    return 0;
}


/*
* Fonction mineProximity qui prend en paramêtre le tableau, le tableau de mine et la ligne et la colone du joueur, ne renvoie rien et permet de compter les 
mines autour de la case séléctionner
* 
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
*
* Si nbMine est égale à 0 
*   Faire en sorte de casser toute les case autours, et toutes le case egale à 0 relié à elle (recursif??????)
* 
* tab[placement] = nbMine + '0'
*/

void mineProximity (char * tab, int * mine, int lineChoice, int columnChoice){
    int numberLine = (int)sqrt(sizeTab);
    int i = 0;
    int nbMine = 0;
    int placement = (lineChoice -1) * numberLine + (columnChoice -1);

    for (i = 0; i < sizeMine; i++) {
         if (placement < 72){
            if (placement + 9 == mine[i]){nbMine+=1;}

            if (placement%numberLine != 8){
                if (placement + 10 == mine[i]){nbMine+=1;}
                if (placement + 1 == mine[i]){nbMine+=1;}

            }
			if (placement%numberLine != 0){
				if (placement + 8 == mine[i]){nbMine+=1;}
                if (placement - 1 == mine[i]){nbMine+=1;}
			}
            if (placement > 8){
                if (placement - 9 == mine[i]) { nbMine += 1; }

                else if (placement%numberLine != 8){
                    if (placement - 10 == mine[i]){nbMine+=1;}
                }
                else if (placement%numberLine != 0){
                    if (placement - 8 == mine[i]){nbMine+=1;}
            }
         }
         }
		 if (placement > 8){
             if (placement - 9 == mine[i]) { nbMine += 1; }

			if (placement%numberLine != 8){
				if (placement - 10 == mine[i]){nbMine+=1;}
                if (placement + 1 == mine[i]){nbMine+=1;}
			}
			if (placement%numberLine != 0){
				if (placement - 8 == mine[i]){nbMine+=1;}
                if (placement - 1 == mine[i]){nbMine+=1;}
			}
		 }
    }
    tab[placement] = nbMine + 48;
    if (nbMine == 0) {
        
        if (placement > 8) {
            if (placement % numberLine != 0) {
                return mineProximity(tab, mine, lineChoice - 1, columnChoice - 1), mineProximity(tab, mine, lineChoice, columnChoice - 1), mineProximity(tab, mine, lineChoice - 1, columnChoice);
            }
            if (placement % numberLine != 8) {
                return mineProximity(tab, mine, lineChoice - 1, columnChoice + 1), mineProximity(tab, mine, lineChoice, columnChoice + 1), mineProximity(tab, mine, lineChoice - 1, columnChoice);
            }

            if (placement < 72) {
                if (placement % numberLine != 0) {
                    return mineProximity(tab, mine, lineChoice + 1, columnChoice - 1), mineProximity(tab, mine, lineChoice + 1, columnChoice), mineProximity(tab, mine, lineChoice - 1, columnChoice);
                }
                if (placement % numberLine != 8) {
                    return mineProximity(tab, mine, lineChoice + 1, columnChoice + 1), mineProximity(tab, mine, lineChoice + 1, columnChoice), mineProximity(tab, mine, lineChoice - 1, columnChoice);
                }
                return mineProximity(tab, mine, lineChoice + 1, columnChoice), mineProximity(tab, mine, lineChoice - 1, columnChoice);
                
            }
        }

        if (placement < 72) {
            if (placement % numberLine != 0) {
                return mineProximity(tab, mine, lineChoice + 1, columnChoice - 1), mineProximity(tab, mine, lineChoice, columnChoice - 1), mineProximity(tab, mine, lineChoice + 1, columnChoice);
            }
            if (placement % numberLine != 8) {
                return mineProximity(tab, mine, lineChoice + 1, columnChoice + 1), mineProximity(tab, mine, lineChoice, columnChoice + 1), mineProximity(tab, mine, lineChoice + 1, columnChoice);
            }

            if (placement > 0) {
                if (placement % numberLine != 0) {
                    return mineProximity(tab, mine, lineChoice - 1, columnChoice - 1), mineProximity(tab, mine, lineChoice - 1, columnChoice), mineProximity(tab, mine, lineChoice - 1, columnChoice);
                }
                if (placement % numberLine != 8) {
                    return mineProximity(tab, mine, lineChoice - 1, columnChoice + 1), mineProximity(tab, mine, lineChoice - 1, columnChoice), mineProximity(tab, mine, lineChoice - 1, columnChoice);
                }
                return mineProximity(tab, mine, lineChoice - 1, columnChoice), mineProximity(tab, mine, lineChoice - 1, columnChoice);

            }
        }


            
    }
}

