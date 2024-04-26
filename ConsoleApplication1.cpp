#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

class Vyjimka
{
	int n_error;
	string s_error;
public:
	Vyjimka(int error)
	{
		n_error = error;
	}

	string Message(void)
	{
		switch (n_error)
		{
		case -1: return string("Velkost hraceho pola nesmie byt cislo mensie ako 3 alebo pismeno");
		default: return string("Ina chyba!");
		}
	}
};

class Hrac
{
private:
	string hrac;
	int h;

public:
	Hrac()
	{

	}

	Hrac(int h)
	{
		cout << "\nHrac " << h << ". zada meno: ";
		cin >> hrac;

		this->h = h;
	}

	Hrac(Hrac& h)
	{
		cout << "\nHrac " << h.h << ". zada meno: ";
		cin >> hrac;

		this->h = h.h;
	}

	friend ostream& operator<<(ostream& out, const Hrac& h);
};

ostream& operator<<(ostream& out, const Hrac& h)
{
	out << h.hrac;
	return out;
}

class Hraciepole
{
private:
	vector<vector<char>> hraciePole;
	int velkostPola;

public:
	Hraciepole()
	{

	}

	void vytvoreniePola()
	{
		cout << "\nVelkost hracieho pola:";

		cin >> velkostPola;
		if (velkostPola < 3)
		{
			throw(Vyjimka(-1));
		}

		hraciePole = vector<vector<char>>(velkostPola, vector<char>(velkostPola, '*'));
	}

	void vypisPola()
	{
		cout << "\n\n";

		for (const auto& row : hraciePole)
		{
			for (const auto& cell : row)
			{
				cout << cell << ' ';
			}
			cout << "\n";
		}
	}

	void spravTah(int aktualnyHrac)
	{
		int x, y;
		cout << "\nZadaj suradnice (x y) na miesto kde chces dat " << (aktualnyHrac == 0 ? 'X' : 'O') << ": \n";
		cin >> x >> y;

		while (x <= 0 || x > velkostPola || y <= 0 || y > velkostPola || hraciePole[x - 1][y - 1] != '*')
		{
			cout << "\nZadaj spravne suradnice od 1 do " << velkostPola << ": \n";
			cin >> x >> y;
		}

		// X alebo O
		hraciePole[x - 1][y - 1] = (aktualnyHrac == 0 ? 'X' : 'O');
	}

	int vyhralNiekto()
	{
		// Skontrolovanie riadkov
		for (int i = 0; i < velkostPola; i++)
		{
			for (int j = 0; j < velkostPola - 2; j++)
			{
				if (hraciePole[i][j] != '*' && hraciePole[i][j] == hraciePole[i][j + 1] && hraciePole[i][j] == hraciePole[i][j + 2])
				{
					return 1;
				}
			}
		}
		// Skontrolovanie stlpcov
		for (int j = 0; j < velkostPola; j++)
		{
			for (int i = 0; i < velkostPola - 2; i++)
			{
				if (hraciePole[i][j] != '*' && hraciePole[i][j] == hraciePole[i + 1][j] && hraciePole[i][j] == hraciePole[i + 2][j])
				{
					return 1;
				}
			}
		}
		// Skontrolovanie diagonalne
		for (int i = 0; i < velkostPola - 2; i++)
		{
			for (int j = 0; j < velkostPola - 2; j++)
			{
				if (hraciePole[i][j] != '*' && hraciePole[i][j] == hraciePole[i + 1][j + 1] && hraciePole[i][j] == hraciePole[i + 2][j + 2])
				{
					return 1;
				}
			}
		}
		// Su nejake * este?
		for (const auto& row : hraciePole)
		{
			for (const auto& cell : row)
			{
				if (cell == '*')
				{
					return 0;
				}
			}
		}
		// Remiza
		return 2;
	}
};

class Hra
{
private:
	Hraciepole hraciePole;

public:
	Hra()
	{

	}

	void novaHra()
	{
		bool koniecHry = true;

		while (koniecHry)
		{
			Hrac hracA(1);
			Hrac hracB(2);

			hraciePole.vytvoreniePola();
			hraciePole.vypisPola();


			int vyberHraca = rand() % 2;
			if (vyberHraca == 0)
			{
				cout << "\n\nZacina hrac menom " << hracA << ".\n";
			}
			else
			{
				cout << "\n\nZacina hrac menom " << hracB << ".\n";
			}

			int koniecKola = 0;
			int pocetTahov = 0;

			while (koniecKola == 0)
			{
				hraciePole.spravTah(vyberHraca);
				vyberHraca = 1 - vyberHraca;
				hraciePole.vypisPola();
				pocetTahov++;
				koniecKola = hraciePole.vyhralNiekto();
			}

			vyberHraca = 1 - vyberHraca;
			if (koniecKola == 1)
			{
				if (vyberHraca == 0)
				{
					cout << "\n" << hracA << " vyhral. Hra trvala " << pocetTahov << " tahov.\n";
				}
				else
				{
					cout << "\n" << hracB << " vyhral. Hra trvala " << pocetTahov << " tahov.\n";
				}
			}
			else if (koniecKola == 2) {
				cout << "\nHra skoncila remizou.\n";
			}

			int hra;
			cout << "\nChces zacat novu hru? (1/0): ";
			cin >> hra;

			if (hra == 0)
			{
				koniecHry = false;
			}
		}
	}
};

int main()
{
	cout << "\nVITAJ V HRE PISKVORKY\n\n";

	Hra piskvorky;

	try
	{
		piskvorky.novaHra();
	}
	catch (Vyjimka& v)
	{
		cout << "Vyjimka: " << v.Message();
	}

}