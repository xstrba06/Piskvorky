#include "PiskvorkyFunkcie.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** HraciePole(int velkostpola) 
{
	char** pole = (char**)malloc(velkostpola * sizeof(char*));
	for (int i = 0; i < velkostpola; i = i + 1)
	{
		pole[i] = (char*)malloc(velkostpola * sizeof(char));
	}

	for (int i = 0; i < velkostpola; i = i + 1)
	{
		printf("\n");

		for (int j = 0; j < velkostpola; j = j + 1)
		{
			pole[i][j] = '*';

			printf("%c ", pole[i][j]);
		}
	}

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

int vyhralNiekto(char** pole, int velkostpola, int ziadnaHviezda)
{
	for (int i = 0; i < velkostpola; i = i + 1) //V riadku
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
	for (int i = 0; i < velkostpola - 2; i = i + 1) //V stlpcoch
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
	for (int i = 0; i < velkostpola - 2; i = i + 1) //Diagonalne dole doprava
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
	for (int i = 2; i < velkostpola; i = i + 1) //Diagonalne hore doprava
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
	for (int i = 0; i < velkostpola; i = i + 1) //Cyklus ziadne *
	{
		for (int j = 0; j < velkostpola; j = j + 1)
		{
			if (pole[i][j] != '*')
			{
				ziadnaHviezda = ziadnaHviezda - 1;
				if (ziadnaHviezda == 0)
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
	FILE* file = fopen("D:\\leaderboard.txt", "r+");
	if (file == NULL) 
	{
		printf("Subor sa neotvoril.\n");
		return;
	}

	Hrac hraci[100];
	int pocetHracov = 0;
	while (fscanf(file, "%s %d", hraci[pocetHracov].meno, &hraci[pocetHracov].skore) != EOF)
	{
		pocetHracov = pocetHracov + 1;
	}

	int i;
	for (i = 0; i < pocetHracov; i = i + 1)
	{
		if (strcmp(hraci[i].meno, hrac) == 0)
		{
			hraci[i].skore += bod;
			break;
		}
	}

	if (i == pocetHracov)
	{
		strcpy(hraci[pocetHracov].meno, hrac);
		hraci[pocetHracov].skore = bod;
		pocetHracov = pocetHracov + 1;
	}

	rewind(file);
	for (i = 0; i < pocetHracov; i = i + 1)
	{
		fprintf(file, "%s %d\n", hraci[i].meno, hraci[i].skore);
	}

	fclose(file);
}

void ukazLeaderboard()
{
	FILE* file = fopen("D:\\leaderboard.txt", "r+");
	if (file == NULL)
	{
		printf("Subor sa neotvoril.\n");
		return;
	}

	Hrac hraci[100];
	int pocetHracov = 0;

	while (fscanf(file, "%s %d", hraci[pocetHracov].meno, &hraci[pocetHracov].skore) != EOF)
	{
		pocetHracov = pocetHracov + 1;
	}

	for (int i = 0; i < 10; i = i + 1)
	{
		printf("%s %d\n", hraci[i].meno, hraci[i].skore);
	}

	fclose(file);
}

void zoradLeaderborad()
{
	FILE* file = fopen("D:\\leaderboard.txt", "r+");
	if (file == NULL)
	{
		printf("Subor sa neotvoril.\n");
		return;
	}

	Hrac hraci[100];
	int pocetHracov = 0;

	while (fscanf(file, "%s %d", hraci[pocetHracov].meno, &hraci[pocetHracov].skore) != EOF)
	{
		pocetHracov = pocetHracov + 1;
	}

	bubbleSort(hraci, pocetHracov);

	rewind(file);
	for (int i = 0; i < pocetHracov; i = i + 1)
	{
		fprintf(file, "%s %d\n", hraci[i].meno, hraci[i].skore);
	}

	fclose(file);
}

void swap(Hrac* hraci, int i, int j)
{
	int temp = hraci[i].skore;
	hraci[i].skore = hraci[j].skore;
	hraci[j].skore = temp;

	char tempString[50];
	strcpy(tempString, hraci[i].meno);
	strcpy(hraci[i].meno, hraci[j].meno);
	strcpy(hraci[j].meno, tempString);
}

void bubbleSort(Hrac* hraci ,int n)
{
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