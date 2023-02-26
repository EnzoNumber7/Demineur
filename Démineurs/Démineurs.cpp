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
int verificationMine(int* mine, int lineChoice, int columnChoice, char* tab);
void mineProximity(char* tab, int* mine, int lineChoice, int columnChoice, int* verified);
int verificationTab(int* verified, int placement);

int main()
{
	// -- INITIALISATION DES VARIABLE -- //

	// Variable pour les boucles
	int i = 0;
	int j = 0;
	int lose = 0;

	// Tableau
	char tab[sizeTab];
	int mine[sizeMine];
	int verified[sizeTab];

	// Autre Variable
	int lineChoice, columnChoice, input;
	int numberLine = (int)sqrt(sizeTab);

	int placement = 0;

	// -- TABLEAU -- //
	
	// Remplissage du tableau de jeux
	for (i = 0; i < sizeTab; i++) {
		tab[i] = '_';
	}
	// Remplissage du tableau de vérification avec des -1
	for (i = 0; i < 81; i++) {
		verified[i] = -1;
	}
	printGame(tab);


	// -- PREMIER TOUR DE JEU -- //
	printf("Choisissez une ligne");
	input = scanf("%d", &lineChoice);

	printf("Choisissez une colone");
	input = scanf("%d", &columnChoice);
	

	// Placement des mines aléatoirement
	time_t t;
	srand((unsigned)time(&t));
	
	placement = (lineChoice - 1) * numberLine + (columnChoice - 1);

	i = 0;
	mine[0] = rand() % 80;
	// Une mine ne peut pas être la où le joueur à joué son premier tour
	if (mine[0] == placement) { 
		mine[0] = rand() % 80;
	}
	i = 1;
	for (i = 1; i < 10; i++) {
		mine[i] = rand() % 80;
		// Une mine ne peut pas être la où le joueur à joué son premier tour
		if (mine[i] == placement) {
			mine[i] = rand() % 80;
		}
		for (j = 0; j < i; j++) {
			// Deux mine ne peuvent pas être au même endroit
			if (mine[i] == mine[j]) {
				mine[j] = rand() % 80;
				j = 0;
			}
		
		}
		

	}

	// -- AFFICHAGE DES MINE -- // ----- TEMPORAIRE ----- //
	i = 0;
	for (i = 0; i < 10; i++) {
		printf("%d /", mine[i]);
	}

	
	mineProximity(tab, mine, lineChoice, columnChoice, verified);
	printGame(tab);

	// Boucle de Jeu

	while (lose == 0) {
		

		printf("Choisissez une ligne");
		input = scanf("%d", &lineChoice);

		printf("Choisissez une colone");
		input = scanf("%d", &columnChoice);

		lose = verificationMine(mine, lineChoice, columnChoice, tab);
		if (lose == 0) {
			mineProximity(tab, mine, lineChoice, columnChoice, verified);
			printGame(tab);
		}


		if (lose == 1) {
			printGame(tab);
			printf("perdu !");
		}
	}


}

void printGame(char* tab) {
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

int verificationMine(int* mine, int lineChoice, int columnChoice, char* tab) {
	
	// Fonction qui prend en paramètre le tableau contenant le placement des mines, le tableau de jeu, la ligne et la colone séléctionner par le joueur
	int numberLine = (int)sqrt(sizeTab);
	int i = 0;
	int j = 0;
	int placement = (lineChoice - 1) * numberLine + (columnChoice - 1);

	for (i = 0; i < sizeMine; i++) {
		if (placement == mine[i]) {
			for (j = 0;j<sizeMine;j++){tab[mine[j]] = 'M';}
				
			return 1;
		}
	}
	return 0;
}

void mineProximity(char* tab, int* mine, int lineChoice, int columnChoice, int* verifiedTab) {
	int numberLine = (int)sqrt(sizeTab);
	int i = 0;
	int nbMine = 0;
	int placement = (lineChoice - 1) * numberLine + (columnChoice - 1);
	int verified;
	int isMine = 0;

	verified = verificationTab(verifiedTab, placement);
	for (i = 0; i < sizeMine; i++) {
		if (placement == mine[i]) {
			isMine = 1;
		}
	}

	i = 0;
	if (isMine == 0) {
		for (i = 0; i < sizeMine; i++) {
			if (placement > 8) {
				if (placement < 72) {
					if (placement % numberLine != 0) {
						if (placement % numberLine != 8) {
							if (placement - 8 == mine[i]) { nbMine += 1; }
							if (placement +1 == mine[i] ) { nbMine += 1; }
							if (placement +10 == mine[i] ) { nbMine += 1; }
							if (placement - 1 == mine[i]) { nbMine += 1; }
							if (placement - 10 == mine[i]) { nbMine += 1; }
							if (placement + 8 == mine[i]) { nbMine += 1; }
							if (placement + 9 == mine[i]) { nbMine += 1; }
							if (placement - 9 == mine[i]) { nbMine += 1; }
						}
						else {
							if (placement - 1 == mine[i]) { nbMine += 1; }
							if (placement - 10 == mine[i]) { nbMine += 1; }
							if (placement + 8 == mine[i]) { nbMine += 1; }
							if (placement + 9 == mine[i]) { nbMine += 1; }
							if (placement - 9 == mine[i]) { nbMine += 1; }
						}
					}
					else {
						if (placement + 9 == mine[i]) { nbMine += 1; }
						if (placement - 9 == mine[i]) { nbMine += 1; }
					}
					
				}
				else {
					if (placement - 9 == mine[i]) { nbMine += 1; }
				}
				
			}
			else {
				if (placement % numberLine != 8) {
					if (placement % numberLine != 0) {
						if (placement - 1 == mine[i]) { nbMine += 1; }
						if (placement + 8 == mine[i]) { nbMine += 1; }
						if (placement + 10 == mine[i]) { nbMine += 1; }
						if (placement + 1 == mine[i]) { nbMine += 1; }
						if (placement + 9 == mine[i]) { nbMine += 1; }
					}
					else {
						if (placement + 10 == mine[i]) { nbMine += 1; }
						if (placement + 1 == mine[i]) { nbMine += 1; }
						if (placement + 9 == mine[i]) { nbMine += 1; }
					}
					
				}
			}
		
		}
		tab[placement] = nbMine + 48;
	}

	
	if (nbMine == 0 && verified == 0 && placement >= 0 && placement <= 80) {
		
		if (placement > 8){
			if (placement < 72) {
				if (placement % numberLine != 0) {
					if (placement % numberLine != 8) {
						return (mineProximity(tab, mine, lineChoice - 1, columnChoice, verifiedTab), mineProximity(tab, mine, lineChoice - 1, columnChoice + 1, verifiedTab), mineProximity(tab, mine, lineChoice, columnChoice + 1, verifiedTab), mineProximity(tab, mine, lineChoice + 1, columnChoice + 1, verifiedTab), mineProximity(tab, mine, lineChoice + 1, columnChoice, verifiedTab), mineProximity(tab, mine, lineChoice + 1, columnChoice - 1, verifiedTab), mineProximity(tab, mine, lineChoice, columnChoice - 1, verifiedTab), mineProximity(tab, mine, lineChoice - 1, columnChoice - 1, verifiedTab));
					}
					return (mineProximity(tab, mine, lineChoice - 1, columnChoice, verifiedTab), mineProximity(tab, mine, lineChoice + 1, columnChoice, verifiedTab), mineProximity(tab, mine, lineChoice + 1, columnChoice - 1, verifiedTab), mineProximity(tab, mine, lineChoice, columnChoice - 1, verifiedTab), mineProximity(tab, mine, lineChoice - 1, columnChoice - 1, verifiedTab));
				}
				return (mineProximity(tab, mine, lineChoice - 1, columnChoice, verifiedTab), mineProximity(tab, mine, lineChoice - 1, columnChoice + 1, verifiedTab), mineProximity(tab, mine, lineChoice, columnChoice + 1, verifiedTab), mineProximity(tab, mine, lineChoice + 1, columnChoice + 1, verifiedTab), mineProximity(tab, mine, lineChoice + 1, columnChoice, verifiedTab));
			}
			if (placement % numberLine != 8) {
				if (placement % numberLine != 0) {
					return (mineProximity(tab, mine, lineChoice - 1, columnChoice, verifiedTab), mineProximity(tab, mine, lineChoice - 1, columnChoice + 1, verifiedTab), mineProximity(tab, mine, lineChoice, columnChoice + 1, verifiedTab), mineProximity(tab, mine, lineChoice, columnChoice - 1, verifiedTab), mineProximity(tab, mine, lineChoice - 1, columnChoice - 1, verifiedTab));
				}
				return (mineProximity(tab, mine, lineChoice - 1, columnChoice, verifiedTab), mineProximity(tab, mine, lineChoice - 1, columnChoice + 1, verifiedTab), mineProximity(tab, mine, lineChoice, columnChoice + 1, verifiedTab));
			}
			return (mineProximity(tab, mine, lineChoice - 1, columnChoice, verifiedTab),  mineProximity(tab, mine, lineChoice, columnChoice - 1, verifiedTab), mineProximity(tab, mine, lineChoice - 1, columnChoice - 1, verifiedTab));
			
		}
		if (placement % numberLine != 8) {
			if (placement % numberLine != 0) {
				return (mineProximity(tab, mine, lineChoice, columnChoice + 1, verifiedTab), mineProximity(tab, mine, lineChoice + 1, columnChoice + 1, verifiedTab), mineProximity(tab, mine, lineChoice + 1, columnChoice, verifiedTab), mineProximity(tab, mine, lineChoice + 1, columnChoice - 1, verifiedTab), mineProximity(tab, mine, lineChoice, columnChoice - 1, verifiedTab));
			}
			return (mineProximity(tab, mine, lineChoice, columnChoice + 1, verifiedTab), mineProximity(tab, mine, lineChoice + 1, columnChoice + 1, verifiedTab), mineProximity(tab, mine, lineChoice + 1, columnChoice, verifiedTab));
		}
		return (mineProximity(tab, mine, lineChoice + 1, columnChoice, verifiedTab), mineProximity(tab, mine, lineChoice + 1, columnChoice - 1, verifiedTab), mineProximity(tab, mine, lineChoice, columnChoice - 1, verifiedTab));
	}

}

int verificationTab(int * verified, int placement) {
	int i = 0;
	/*int j = 0;
	for (j = 0; j < 81; j++) {
		printf("%d", verified[i]);
	}*/
	
	while (verified[i] != -1 && i < 81) {
		if (verified[i] == placement) {
			return 1;
		}
		i++;
	}
	verified[i] = placement;
	return 0;
	
}
