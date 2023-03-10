// Démineurs.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define RESET "\x1B[0m"


void printGame(char* tab,int sizeTab);
int verificationMine(int* mine, int lineChoice, int columnChoice, char* tab,int sizeTab,int sizeMine);
void mineProximity(char* tab, int* mine, int lineChoice, int columnChoice, int* verified, int sizeMine, int sizeTab);
int victory(int* verified, int sizeTab, int sizeMine);
int verificationTab(int* verified, int placement, int sizeTab);
void putFlag(char* tab, int* mine, int lineChoice, int columnChoice, int* verifiedTab, int sizeTab);
void freeScanf();

int main()
{

	
	// -- INITIALISATION DES VARIABLE -- //

	// Variable pour les boucles
	int i = 0;
	int j = 0;
	int lose = 0;

	int easyTab = 81;
	int medTab = 256;
	int hardTab = 529;

	int easyMine = 10; 
	int medMine = 40;
	int hardMine = 99;


	// Autre Variable
	int lineChoice, columnChoice;
	
	
	int placement = 0;
	int win = 0;
	int sizeTab,sizeMine;

	char difficulties;
	char choice = 'c';

// -- CHOIX DIFFICULTE -- //
	printf("Choisissez la difficulte : f pour facile, m pour moyen et d pour difficile\n");
	scanf("%c", &difficulties);

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


	//stdin ""

	// -- PREMIER TOUR DE JEU -- //
	printf("Choisissez une ligne");
	scanf("%d", &lineChoice);
	freeScanf();

	//char c = getchar()


	printf("Choisissez une colone");
	scanf("%d", &columnChoice);
	freeScanf();
	

	// -- PLACEMENT DES MINES -- //
	time_t t;
	srand((unsigned)time(&t));
	
	placement = (lineChoice - 1) * numberLine + (columnChoice - 1);


	i = 0;
	for (i = 0; i < sizeMine; i++) {
		mine[i] = rand() % sizeTab - 1;
		// Une mine ne peut pas être la où le joueur à joué son premier tour
		if (mine[i] == placement || mine[i] == placement - 1 || mine[i] == placement + 1 || mine[i] == placement - numberLine || mine[i] == placement - numberLine - 1 || mine[i] == placement - numberLine + 1 || mine[i] == placement + numberLine || mine[i] == placement + numberLine - 1 || mine[i] == placement + numberLine + 1 || mine[i] <= 0 || mine[i] >= sizeTab-1) {
			
			i -= 1;
		}
		if (i >= 1) {
			for (j = 0; j < i; j++) {
				// Deux mine ne peuvent pas être au même endroit
				if (mine[i] == mine[j]) {
					mine[j] = rand() % sizeTab - 1;
					j = 0;
				}
				if (mine[j] == placement || mine[j] == placement - 1 || mine[j] == placement + 1 || mine[j] == placement - numberLine || mine[j] == placement - numberLine - 1 || mine[j] == placement - numberLine + 1 || mine[j] == placement + numberLine || mine[j] == placement + numberLine - 1 || mine[j] == placement + numberLine + 1 || mine[j] <= 0 || mine[j] >= sizeTab - 1) {
					mine[j] = rand() % sizeTab - 1;
					j -= 1;
				}
		
			}	
		}
		
		

	}


	
	mineProximity(tab, mine, lineChoice, columnChoice, verified, sizeMine, sizeTab);
	printGame(tab, sizeTab);

	// Boucle de Jeu
	while (lose == 0 && win == 0) {
		printf("d pour drapeau, c pour casser\n");
		scanf("%c", &choice);
		freeScanf();

		if (choice == 'c' || choice == 'C'){
			printf("Choisissez une ligne\n");
			scanf("%d", &lineChoice);
			freeScanf();

			printf("Choisissez une colone\n");
			scanf("%d", &columnChoice);
			freeScanf();

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
			scanf("%d", &lineChoice);
			freeScanf();

			printf("Choisissez une colone");
			scanf("%d", &columnChoice);
			freeScanf();

			putFlag(tab, mine, lineChoice, columnChoice, verified, sizeTab);
			printGame(tab, sizeTab);
		}
		else {
			printf("choix non disponible\n");
		}
		
		win = victory(verified, sizeTab, sizeMine);

		if (win == 1) {
			printf("Bravo vous avez gagne !\n");
		}

	}

	free(tab);
	free(verified);
	free(mine);

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
			// -- MISE EN COULEUR DES CHIFFRES DU DEMINEUR -- //
			if (tab[i * numberLine + j] == '1') { printf("|_" BLU "1" RESET "|"); }
			else if (tab[i * numberLine + j] == '2') { printf("|_" GRN "2" RESET "|"); }
			else if (tab[i * numberLine + j] == '3') { printf("|_" RED "3" RESET "|"); }
			else if (tab[i * numberLine + j] == '4') { printf("|_" MAG "4" RESET "|"); }
			else if (tab[i * numberLine + j] == '5') { printf("|_" YEL "5" RESET "|"); }
			else if (tab[i * numberLine + j] == '6') { printf("|_" CYN "6" RESET "|"); }
			else {printf("|_%c|", tab[i * numberLine + j]); }
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
	else {
		printf("Erreur, choix imposible");
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

int victory(int * verified, int sizeTab, int sizeMine) {
	if (verified[sizeTab - (sizeMine+1)] == -1) {
		return 0;
	}
	return 1;
}

void freeScanf() {
	char c = getchar();
	while (c != '\n'){
		c = getchar();
	}
}
