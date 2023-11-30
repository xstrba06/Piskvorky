#pragma once
typedef struct
{
	char meno[50];
	int skore;
} Hrac;


char** HraciePole(int velkostpola);
void vypisPola(char** pole, int velkostpola);
void suradniceXY(char** pole, int velkostpola, int vyberHraca);
void zmenHraca(int* vyberHraca);
int vyhralNiekto(char** pole, int velkostpola, int ziadnaHviezda);
void leaderBoard(char* hrac, int bod);
void ukazLeaderboard();
void zoradLeaderborad();
void bubbleSort(Hrac* hraci, int n);
void swap(Hrac* hraci, int i, int j);