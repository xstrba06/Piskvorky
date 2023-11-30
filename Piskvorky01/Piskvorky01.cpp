// Piskvorky.cpp : Defines the entry point for the application.
//

#include "Piskvorky01.h"
#include "PiskvorkyFunkcie.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main()
{
	printf("Hrac 1 zada meno: ");
	scanf("%s", hrac1);

	printf("Hrac 2 zada meno: ");
	scanf("%s", hrac2);

	while (novaHra == true)
	{
		printf("Vyberte velkost hracieho pole (3,4,5): ");
		scanf("%d", &velkostpola);

		while (velkostpola > 20 || velkostpola < 3)
		{
			printf("Vyber velkost hracieho pola od 3 - 20: ");
			scanf("%d", &velkostpola);
		}
		//Vytvorenie Hracieho Pola 
		char** pole = HraciePole(velkostpola);

		int vyberHraca;
		srand(time(NULL));
		vyberHraca = rand() % 2;

		if (vyberHraca == 0)
		{
			printf("\n\nZacina %s.\n", hrac1);
		}
		else
		{
			printf("\n\nZacina %s.\n", hrac2);
		}

		int gameover = 0;
		int ziadnaHviezda = velkostpola * velkostpola;
		int pocetTahov = 0;

		while (gameover == 0)
		{
			suradniceXY(pole, velkostpola, vyberHraca);
			zmenHraca(&vyberHraca);
			vypisPola(pole, velkostpola);
			pocetTahov = pocetTahov + 1; 
			gameover = vyhralNiekto(pole, velkostpola, ziadnaHviezda);
		}
		zmenHraca(&vyberHraca);

		if (gameover == 1)
		{
			if (vyberHraca == 0) 
			{
				printf("\nVyhral %s. Hra trvala %d tahov.", hrac1, pocetTahov);
				vyhraPrvy = vyhraPrvy + 1;
				leaderBoard(hrac1, 1);
			}
			if (vyberHraca == 1)
			{
				printf("\nVyhral %s. Hra trvala %d tahov.", hrac2, pocetTahov);
				vyhraDruhy = vyhraDruhy + 1;
				leaderBoard(hrac2, 1);
			}
		}
		if (gameover == 2)
		{
			printf("\nNikto nevyhral.");
		}

		int hra = 1;
		printf("\nChces zacat novu hru? (1/0) alebo chces ukazat leaderboard? (2): ");
		scanf("%d", &hra);

		if (hra == 0)
		{
			novaHra = false;
		}

		if (hra == 2)
		{
			zoradLeaderborad();
			ukazLeaderboard();
		}
	}
}
