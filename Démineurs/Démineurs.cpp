// Démineurs.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define easyMine 10
#define medMine 40
#define hardMine 99

#define easyTab 81  // tableau 9x9
#define medTab 256  // tableau 16x16
#define hardTab 529 // tableau 23x23

void printGame(char* tab,int sizeTab);
int verificationMine(int* mine, int lineChoice, int columnChoice, char* tab,int sizeTab,int sizeMine);
void mineProximity(char* tab, int* mine, int lineChoice, int columnChoice, int* verified, int sizeMine, int sizeTab);
int victory(int* verified, int sizeTab);
int verificationTab(int* verified, int placement, int sizeTab);
void putFlag(char* tab, int* mine, int lineChoice, int columnChoice, int* verifiedTab, int sizeTab);

int main()
{

	
	// -- INITIALISATION DES VARIABLE -- //

	// Variable pour les boucles
	int i = 0;
	int j = 0;
	int lose = 0;


	// Autre Variable
	int lineChoice, columnChoice, input;
	
	
	int placement = 0;
	int win = 0;
	int sizeTab,sizeMine;

	char difficulties;
	char choice;

// -- CHOIX DIFFICULTE -- //
	printf("Choisissez la difficulte : f pour facile, m pour moyen et d pour difficile\n");
	input = scanf("%c", &difficulties);

	if (difficulties == 'f') {
		sizeTab = easyTab;
		sizeMine = easyMine;
	}
	else if (difficulties == 'm') {
		sizeTab = medTab;
		sizeMine = medMine;
	}
	else if (difficulties == 'd') {
		sizeTab = hardTab;
		sizeMine = hardMine;
		
	}
	else {
		printf("Choix invalide, le jeu sera mis en moyen.");
		sizeTab = medTab;
		sizeMine = medMine;
	}
	printf("\n%d\n", sizeTab);

	// -- INITIALISATION DES VARIABLE -- //
	// Tableau
	char* tab = (char*)malloc(sizeof(char) * sizeTab);
	int* mine = (int*)malloc(sizeof(int) * sizeMine);
	int* verified = (int*)malloc(sizeof(int) * sizeTab);

	int numberLine = (int)sqrt(sizeTab);

	// -- TABLEAU -- //
	
	// Remplissage du tableau de jeux
	for (i = 0; i < sizeTab; i++) {
		tab[i] = '_';
	}
	// Remplissage du tableau de vérification avec des -1
	for (i = 0; i < sizeTab; i++) {
		verified[i] = -1;
	}
	printGame(tab,sizeTab);


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
	mine[0] = rand() % sizeTab - 1;
	// Une mine ne peut pas être la où le joueur à joué son premier tour
	if (mine[0] == placement) { 
		mine[0] = rand() % sizeTab - 1;
	}
	i = 1;
	for (i = 1; i < sizeMine; i++) {
		mine[i] = rand() % sizeTab - 1;
		// Une mine ne peut pas être la où le joueur à joué son premier tour
		if (mine[i] == placement) {
			mine[i] = rand() % sizeTab - 1;
		}
		for (j = 0; j < i; j++) {
			// Deux mine ne peuvent pas être au même endroit
			if (mine[i] == mine[j]) {
				mine[j] = rand() % sizeTab - 1;
				j = 0;
			}
		
		}
		

	}

	// -- AFFICHAGE DES MINE -- // ----- TEMPORAIRE ----- //
	i = 0;
	for (i = 0; i < sizeMine; i++) {
		printf("%d /", mine[i]);
	}

	
	mineProximity(tab, mine, lineChoice, columnChoice, verified, sizeMine, sizeTab);
	printGame(tab, sizeTab);

	// Boucle de Jeu

	while (lose == 0 && win == 0) {
		
		printf("d pour drapeau, c pour casser\n");
		input = scanf("%c", &choice);
		if (choice == 'c' || choice == 'C'){
			printf("Choisissez une ligne\n");
			input = scanf("%d", &lineChoice);

			printf("Choisissez une colone\n");
			input = scanf("%d", &columnChoice);

			lose = verificationMine(mine, lineChoice, columnChoice, tab, sizeTab, sizeMine);
			if (lose == 0) {
				mineProximity(tab, mine, lineChoice, columnChoice, verified, sizeMine, sizeTab);
				printGame(tab, sizeTab);
			}


			if (lose == 1) {
				printGame(tab, sizeTab);
				printf("perdu !");
			}
		
		}
		else if (choice == 'd' || choice == 'D'){
			printf("Choisissez une ligne");
			input = scanf("%d", &lineChoice);

			printf("Choisissez une colone");
			input = scanf("%d", &columnChoice);

			putFlag(tab, mine, lineChoice, columnChoice, verified, sizeTab);
			printGame(tab, sizeTab);
		}
		else{
			printf("choix non disponible");
		}
		win = victory(verified, sizeTab);

		if (win == 1) {
			printf("Bravo vous avez gagne !\n");
		}

	}


}

void printGame(char* tab, int sizeTab) {
	// Fonction qui prend en paramètre le tableau de jeu et permet de l'afficher
	int numberLine = (int)sqrt(sizeTab);
	int i = 0;
	int j = 0;

	printf("__");
	for (i = 1; i <= numberLine; i++) {
		if (i < 10) {
			printf("|0%d|", i);
		}
		else {
			printf("|%d|", i);
		}
		
	}
	printf("\n");
	for (i = 0; i < numberLine; i++) {
		if (i < 9) {
			printf("0%d", i + 1);
		}
		else {
			printf("%d", i + 1);
		}
		for (j = 0; j < numberLine; j++) {
			printf("|_%c|", tab[i * 9 + j]);
		}
		printf("\n");
	}

}

int verificationMine(int* mine, int lineChoice, int columnChoice, char* tab, int sizeTab, int sizeMine) {
	
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

void mineProximity(char* tab, int* mine, int lineChoice, int columnChoice, int* verifiedTab , int sizeMine , int sizeTab) {
	int numberLine = (int)sqrt(sizeTab);
	int i = 0;
	int nbMine = 0;
	int placement = (lineChoice - 1) * numberLine + (columnChoice - 1);
	int verified;
	int isMine = 0;
	int top = numberLine - 1;
	int bot = sizeTab - numberLine;
	int left = 0;
	int right = numberLine - 1;
	int upLeft = numberLine + 1;
	int up = numberLine;
	int upRight = numberLine - 1;
	int downLeft = numberLine - 1;
	int down = numberLine;
	int downRight = numberLine + 1;


	verified = verificationTab(verifiedTab, placement,sizeTab);
	for (i = 0; i < sizeMine; i++) {
		if (placement == mine[i]) {
			isMine = 1;
		}
	}

	i = 0;
	if (isMine == 0) {
		for (i = 0; i < sizeMine; i++) {
			if (placement > top) {
				if (placement < bot) {
					if (placement % numberLine != left) {
						if (placement % numberLine != right) {
							if (placement - upRight == mine[i]) { nbMine += 1; }
							if (placement + 1 == mine[i] ) { nbMine += 1; }
							if (placement + downRight == mine[i] ) { nbMine += 1; }
							if (placement - 1 == mine[i]) { nbMine += 1; }
							if (placement - upLeft == mine[i]) { nbMine += 1; }
							if (placement + downLeft == mine[i]) { nbMine += 1; }
							if (placement + down == mine[i]) { nbMine += 1; }
							if (placement - up == mine[i]) { nbMine += 1; }
						}
						else {
							if (placement - 1 == mine[i]) { nbMine += 1; }
							if (placement - upLeft == mine[i]) { nbMine += 1; }
							if (placement + downLeft == mine[i]) { nbMine += 1; }
							if (placement + down == mine[i]) { nbMine += 1; }
							if (placement - up == mine[i]) { nbMine += 1; }
						}
					}
					else {
						if (placement + down == mine[i]) { nbMine += 1; }
						if (placement - up == mine[i]) { nbMine += 1; }
						if (placement - upRight == mine[i]) { nbMine += 1; }
						if (placement + 1 == mine[i]) { nbMine += 1; }
						if (placement + downRight == mine[i]) { nbMine += 1; }
					}
					
				}
				else {
					if (placement % numberLine != right) {
						if (placement % numberLine != left) {
							if (placement - up == mine[i]) { nbMine += 1; }
							if (placement - upRight == mine[i]) { nbMine += 1; }
							if (placement - upLeft == mine[i]) { nbMine += 1; }
							if (placement + 1 == mine[i]) { nbMine += 1; }
							if (placement - 1 == mine[i]) { nbMine += 1; }
						}
						else {
							if (placement - up == mine[i]) { nbMine += 1; }
							if (placement - upRight == mine[i]) { nbMine += 1; }
							if (placement + 1 == mine[i]) { nbMine += 1; }
						}
					}
					else {
						if (placement - up == mine[i]) { nbMine += 1; }
						if (placement - upLeft == mine[i]) { nbMine += 1; }
					}
				}
				
			}
			else {
				if (placement % numberLine != right) {
					if (placement % numberLine != left) {
						if (placement - 1 == mine[i]) { nbMine += 1; }
						if (placement + downLeft == mine[i]) { nbMine += 1; }
						if (placement + downRight == mine[i]) { nbMine += 1; }
						if (placement + 1 == mine[i]) { nbMine += 1; }
						if (placement + down == mine[i]) { nbMine += 1; }
					}
					else {
						if (placement + downRight == mine[i]) { nbMine += 1; }
						if (placement + 1 == mine[i]) { nbMine += 1; }
						if (placement + down == mine[i]) { nbMine += 1; }
					}
					
				}
				else{
					if (placement - 1 == mine[i]) { nbMine += 1; }
					if (placement + downLeft == mine[i]) { nbMine += 1; }
					if (placement + down == mine[i]) { nbMine += 1; }
				}
			}
		
		}
		tab[placement] = nbMine + 48;
	}

	
	if (nbMine == 0 && verified == 0 && placement >= 0 && placement <= (sizeTab - 1)) {
		
		if (placement > top){
			if (placement < bot) {
				if (placement % numberLine != left) {
					if (placement % numberLine != right) {
						return (mineProximity(tab, mine, lineChoice - 1, columnChoice, verifiedTab, sizeMine, sizeTab), mineProximity(tab, mine, lineChoice - 1, columnChoice + 1, verifiedTab, sizeMine, sizeTab), mineProximity(tab, mine, lineChoice, columnChoice + 1, verifiedTab, sizeMine, sizeTab), mineProximity(tab, mine, lineChoice + 1, columnChoice + 1, verifiedTab, sizeMine, sizeTab), mineProximity(tab, mine, lineChoice + 1, columnChoice, verifiedTab, sizeMine, sizeTab), mineProximity(tab, mine, lineChoice + 1, columnChoice - 1, verifiedTab, sizeMine, sizeTab), mineProximity(tab, mine, lineChoice, columnChoice - 1, verifiedTab, sizeMine, sizeTab), mineProximity(tab, mine, lineChoice - 1, columnChoice - 1, verifiedTab, sizeMine, sizeTab));
					}
					return (mineProximity(tab, mine, lineChoice - 1, columnChoice, verifiedTab, sizeMine, sizeTab), mineProximity(tab, mine, lineChoice + 1, columnChoice, verifiedTab, sizeMine, sizeTab), mineProximity(tab, mine, lineChoice + 1, columnChoice - 1, verifiedTab, sizeMine, sizeTab), mineProximity(tab, mine, lineChoice, columnChoice - 1, verifiedTab, sizeMine, sizeTab), mineProximity(tab, mine, lineChoice - 1, columnChoice - 1, verifiedTab, sizeMine, sizeTab));
				}
				return (mineProximity(tab, mine, lineChoice - 1, columnChoice, verifiedTab, sizeMine, sizeTab), mineProximity(tab, mine, lineChoice - 1, columnChoice + 1, verifiedTab, sizeMine, sizeTab), mineProximity(tab, mine, lineChoice, columnChoice + 1, verifiedTab, sizeMine, sizeTab), mineProximity(tab, mine, lineChoice + 1, columnChoice + 1, verifiedTab, sizeMine, sizeTab), mineProximity(tab, mine, lineChoice + 1, columnChoice, verifiedTab, sizeMine, sizeTab));
			}
			if (placement % numberLine != right) {
				if (placement % numberLine != left) {
					return (mineProximity(tab, mine, lineChoice - 1, columnChoice, verifiedTab, sizeMine, sizeTab), mineProximity(tab, mine, lineChoice - 1, columnChoice + 1, verifiedTab, sizeMine, sizeTab), mineProximity(tab, mine, lineChoice, columnChoice + 1, verifiedTab, sizeMine, sizeTab), mineProximity(tab, mine, lineChoice, columnChoice - 1, verifiedTab, sizeMine, sizeTab), mineProximity(tab, mine, lineChoice - 1, columnChoice - 1, verifiedTab, sizeMine, sizeTab));
				}
				return (mineProximity(tab, mine, lineChoice - 1, columnChoice, verifiedTab, sizeMine, sizeTab), mineProximity(tab, mine, lineChoice - 1, columnChoice + 1, verifiedTab, sizeMine, sizeTab), mineProximity(tab, mine, lineChoice, columnChoice + 1, verifiedTab, sizeMine, sizeTab));
			}
			return (mineProximity(tab, mine, lineChoice - 1, columnChoice, verifiedTab, sizeMine, sizeTab),  mineProximity(tab, mine, lineChoice, columnChoice - 1, verifiedTab, sizeMine, sizeTab), mineProximity(tab, mine, lineChoice - 1, columnChoice - 1, verifiedTab, sizeMine, sizeTab));
			
		}
		if (placement % numberLine != right) {
			if (placement % numberLine != left) {
				return (mineProximity(tab, mine, lineChoice, columnChoice + 1, verifiedTab, sizeMine, sizeTab), mineProximity(tab, mine, lineChoice + 1, columnChoice + 1, verifiedTab, sizeMine, sizeTab), mineProximity(tab, mine, lineChoice + 1, columnChoice, verifiedTab, sizeMine, sizeTab), mineProximity(tab, mine, lineChoice + 1, columnChoice - 1, verifiedTab, sizeMine, sizeTab), mineProximity(tab, mine, lineChoice, columnChoice - 1, verifiedTab, sizeMine, sizeTab));
			}
			return (mineProximity(tab, mine, lineChoice, columnChoice + 1, verifiedTab, sizeMine, sizeTab), mineProximity(tab, mine, lineChoice + 1, columnChoice + 1, verifiedTab, sizeMine, sizeTab), mineProximity(tab, mine, lineChoice + 1, columnChoice, verifiedTab, sizeMine, sizeTab));
		}
		return (mineProximity(tab, mine, lineChoice + 1, columnChoice, verifiedTab, sizeMine, sizeTab), mineProximity(tab, mine, lineChoice + 1, columnChoice - 1, verifiedTab, sizeMine, sizeTab), mineProximity(tab, mine, lineChoice, columnChoice - 1, verifiedTab, sizeMine, sizeTab));
	}

}
void putFlag (char * tab, int* mine, int lineChoice, int columnChoice, int* verifiedTab, int sizeTab){
	int numberLine = (int)sqrt(sizeTab);
	int i = 0;
	int placement = (lineChoice - 1) * numberLine + (columnChoice - 1);
	int verified = 0;

	for (i=0;i<sizeTab;i++){
		if (verifiedTab[i] == placement){
			verified = 1;
		}
	}
	if (verified == 0){
		tab[placement] = '$';
	}

}

int verificationTab(int * verified, int placement, int sizeTab) {
	int i = 0;
	
	while (verified[i] != -1 && i < sizeTab) {
		if (verified[i] == placement) {
			return 1;
		}
		i++;
	}
	verified[i] = placement;
	return 0;
	
}

int victory(int * verified, int sizeTab) {
	if (verified[sizeTab-9] == -1) {
		return 0;
	}
	return 1;
}
