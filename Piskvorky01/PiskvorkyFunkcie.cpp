#include "PiskvorkyFunkcie.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** HraciePole(int velkostpola) 
{ 
	// memory allocation
	char** pole = (char**)malloc(velkostpola * sizeof(char*)); 
	for (int i = 0; i < velkostpola; i = i + 1)
	{
		pole[i] = (char*)malloc(velkostpola * sizeof(char)); 
	}

	// naplnenie pola '*'
	for (int i = 0; i < velkostpola; i = i + 1)
	{
		for (int j = 0; j < velkostpola; j = j + 1)
		{
			pole[i][j] = '*';
		}
	}

	vypisPola(pole, velkostpola);
	return pole;
}

void vypisPola(char** pole, int velkostpola)
{
	for (int i = 0; i < velkostpola; i = i + 1)
	{
		printf("\n");

		for (int j = 0; j < velkostpola; j = j + 1)
		{
			printf("%c ", pole[i][j]);
		}
	}
}

void suradniceXY(char** pole, int velkostpola, int vyberHraca)
{
	int x = 0;
	int y = 0;

	if (vyberHraca == 0)
	{
		printf("\nZadaj suradnice v tvare(x 'medzera' y) na miesto kde chces dat X: \n");
		scanf("%d %d", &x, &y);

		while ((x <= 0 || x > velkostpola || y <= 0 || y > velkostpola) || pole[x - 1][y - 1] != '*')
		{
			printf("\nZadaj spravne suradnice v rozsahu od 1 po %d: \n", velkostpola);
			scanf("%d %d", &x, &y);
		}
		pole[x - 1][y - 1] = 'X';
	}
	else
	{
		printf("\nZadaj suradnice v tvare(x 'medzera' y) na miesto kde chces dat O: \n");
		scanf("%d %d", &x, &y);

		while ((x <= 0 || x > velkostpola || y <= 0 || y > velkostpola) || pole[x - 1][y - 1] != '*')
		{
			printf("\nZadaj spravne suradnice v rozsahu od 1 po %d: \n", velkostpola);
			scanf("%d %d", &x, &y);
		}
		pole[x - 1][y - 1] = 'O';
	}
}

void zmenHraca(int* vyberHraca)
{
	if (*vyberHraca == 0)
	{
		*vyberHraca = 1;
	}
	else
	{
		*vyberHraca = 0;
	}
}

int vyhralNiekto(char** pole, int velkostpola)
{
	// V riadku
	for (int i = 0; i < velkostpola; i = i + 1)
	{
		for (int j = 0; j < velkostpola - 2; j = j + 1)
		{
			if (pole[i][j] != '*')
			{
				if (pole[i][j] == pole[i][j + 1] && pole[i][j] == pole[i][j + 2])
				{
					return 1;
				}
			}
		}
	}

	// V stlpcoch
	for (int i = 0; i < velkostpola - 2; i = i + 1)
	{
		for (int j = 0; j < velkostpola; j = j + 1)
		{
			if (pole[i][j] != '*')
			{
				if (pole[i][j] == pole[i + 1][j] && pole[i][j] == pole[i + 2][j])
				{
					return 1;
				}
			}
		}
	}

	// Diagonalne dole doprava
	for (int i = 0; i < velkostpola - 2; i = i + 1)
	{
		for (int j = 0; j < velkostpola - 2; j = j + 1)
		{
			if (pole[i][j] != '*')
			{
				if (pole[i][j] == pole[i + 1][j + 1] && pole[i][j] == pole[i + 2][j + 2])
				{
					return 1;
				}
			}
		}
	}

	// Diagonalne hore doprava
	for (int i = 2; i < velkostpola; i = i + 1)
	{
		for (int j = 0; j < velkostpola - 2; j = j + 1)
		{
			if (pole[i][j] != '*')
			{
				if (pole[i][j] == pole[i - 1][j + 1] && pole[i][j] == pole[i - 2][j + 2])
				{
					return 1;
				}
			}
		}
	}

	// Skontrolovanie nezadanych policok od uzivatela
	int pocetPolicok = velkostpola * velkostpola;
	for (int i = 0; i < velkostpola; i = i + 1) 
	{
		for (int j = 0; j < velkostpola; j = j + 1)
		{
			if (pole[i][j] != '*')
			{
				pocetPolicok = pocetPolicok - 1;
				if (pocetPolicok == 0)
				{
					return 2;
				}
			}
		}
	}
	return 0;
}

void leaderBoard(char* hrac, int bod) 
{

	// Otvorenie suboru
	FILE* file = fopen("D:\\leaderboard.txt", "r+");
	if (file == NULL) 
	{
		printf("Subor sa neotvoril.\n");
		return;
	}

	// Nacitanie zo suboru
	Hrac hraci[100];
	int pocetHracov = 0;
	while (fscanf(file, "%s %d", hraci[pocetHracov].meno, &hraci[pocetHracov].skore) != EOF)
	{
		pocetHracov = pocetHracov + 1;
	}

	// Vyhladanie hraca
	int i;
	for (i = 0; i < pocetHracov; i = i + 1)
	{
		if (strcmp(hraci[i].meno, hrac) == 0)
		{
			hraci[i].skore += bod;
			break;
		}
	}

	// Pridanie noveho hraca
	if (i == pocetHracov)
	{
		strcpy(hraci[pocetHracov].meno, hrac);
		hraci[pocetHracov].skore = bod;
		pocetHracov = pocetHracov + 1;
	}

	// Vypis leaderboardu
	rewind(file);
	for (i = 0; i < pocetHracov; i = i + 1)
	{
		fprintf(file, "%s %d\n", hraci[i].meno, hraci[i].skore);
	}

	fclose(file);
}

void ukazLeaderboard()
{

	// Otvorenie subora
	FILE* file = fopen("D:\\leaderboard.txt", "r+");
	if (file == NULL)
	{
		printf("Subor sa neotvoril.\n");
		return;
	}

	Hrac hraci[100];
	int pocetHracov = 0;

	// Nacitanie hracov do lokalnej pamati
	while (fscanf(file, "%s %d", hraci[pocetHracov].meno, &hraci[pocetHracov].skore) != EOF)
	{
		pocetHracov = pocetHracov + 1;
	}

	// Vypis top 10 hracov
	for (int i = 0; i < 10; i = i + 1)
	{
		printf("%s %d\n", hraci[i].meno, hraci[i].skore);
	}

	fclose(file);
}

void zoradLeaderborad()
{

	// Otvorenie suboru
	FILE* file = fopen("D:\\leaderboard.txt", "r+");
	if (file == NULL)
	{
		printf("Subor sa neotvoril.\n");
		return;
	}

	// Nacitanie hracov do lokalnej pamati
	Hrac hraci[100];
	int pocetHracov = 0;

	while (fscanf(file, "%s %d", hraci[pocetHracov].meno, &hraci[pocetHracov].skore) != EOF)
	{
		pocetHracov = pocetHracov + 1;
	}

	bubbleSort(hraci, pocetHracov);

	// Nacitanie hracov do suboru
	rewind(file);
	for (int i = 0; i < pocetHracov; i = i + 1)
	{
		fprintf(file, "%s %d\n", hraci[i].meno, hraci[i].skore);
	}

	fclose(file);
}

void swap(Hrac* hraci, int i, int j)
{

	// Vymena skore
	int temp = hraci[i].skore;
	hraci[i].skore = hraci[j].skore;
	hraci[j].skore = temp;

	// Vymena mena
	char tempString[50];
	strcpy(tempString, hraci[i].meno);
	strcpy(hraci[i].meno, hraci[j].meno);
	strcpy(hraci[j].meno, tempString);
}

void bubbleSort(Hrac* hraci ,int n)
{

	// Bubblesort snad jasne ne?
	int i, j;
	for (i = 0; i < n - 1; i = i + 1)
	{
		for (j = 0; j < n - i - 1; j = j + 1)
		{
			if (hraci[j].skore < hraci[j + 1].skore)
			{
				swap(hraci, j, j + 1);
			}
		}
	}
}