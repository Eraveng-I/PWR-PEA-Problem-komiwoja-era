#include "DYNAMICZNOSC.h"

#include <iostream>

using namespace std;

void DYNAMICZNOSC::rozwiazanie_dynamiczne(int rozmiar, int** graf)
{
	inicjalizacja(rozmiar);

	znajdz_rozwiazanie(graf);

	cout << "Najkrótsza droga ma d³ugoœæ " << NajlepszaSuma << " i idzie przez:" << endl;
	cout << "0 -> ";
	zrob_sciezke(0, 1);
	cout << 0 << endl;
}

//Alokacja pamieci i zdefiniowanie maski
void DYNAMICZNOSC::inicjalizacja(int rozmiar)
{
	n = rozmiar;
	n2 = (1 << rozmiar);
	sciezka = new int* [n];
	dp = new int* [n2];

	for (int i = 0; i < n2; i++)
	{
		dp[i] = new int[n];
	}
		
	for (int i = 0; i < n; i++)
	{
		sciezka[i] = new int[n2];
	}
		
	WszystkoOdwiedzone = (1 << n) - 1;	//11...1
}

//Algorytm
int DYNAMICZNOSC::tsp(int maska, int pozycja, int** dystanse)
{
	//cout << "Wywoluje tsp(" << maska << ", " << pozycja << ")" << endl;
	if (maska == WszystkoOdwiedzone) {	//Warunek zakonczenia - wszystkie miasta odwiedzone
		//cout << "Wszystkie odwiedzone, dodaje " << dystanse[pozycja][0] << endl;
		return dystanse[pozycja][0];
	}

	if (dp[maska][pozycja] != -1) {	//Warunek zakonczenia - ten przypadek zostal obliczony
		//cout << "Juz jest cos na pozycji [" << maska << "][" << pozycja << "]" << endl;
		return dp[maska][pozycja];
	}

	int odpowiedz = INT_MAX;

	for (int miasto = 0; miasto < n; miasto++)	//Powtarzamy dla kazdego miasta
	{
		//cout << "Iteracja dla " << miasto << " w tsp(" << maska << ", " << pozycja << ")" << endl;

		if ((maska & (1 << miasto)) == 0)		//Jesli miasto nie bylo odwiedzone
		{
			int tmp = dystanse[pozycja][miasto] + tsp(maska | (1 << miasto), miasto, dystanse);	//Dodajemy wage krawedzi oraz wywolujemy rekurencyjnie funkcje
			//dla mniejszych podproblemow
			if (odpowiedz > tmp)	//Jesli znajdziemy lepsze rozwiazanie, zamieniamy je
			{
				//cout << tmp << " jest mniejsze niz " << odpowiedz << ", wiec zamieniamy" << endl;
				odpowiedz = tmp;
				sciezka[pozycja][maska] = miasto;
				//cout << "sciezka[" << pozycja << "][" << maska << "] = " << miasto << endl;
			}
			/*else
				{
					//cout << tmp << " jest wieksze lub rowne " << odpowiedz << ", wiec nie zamieniamy" << endl;
				}*/
		}
	}

	//cout << "dp[" << maska << "][" << pozycja << "] = " << odpowiedz << endl;
	return dp[maska][pozycja] = odpowiedz;	//Zapisujemy rozwiazanie
}

void DYNAMICZNOSC::znajdz_rozwiazanie(int** tab)	//Przygotowanie pomocnicznych tablic oraz uruchomienie algorytmu dla odpowiednich argumentow poczatkowych
{
	for (int i = 0; i < n2; i++)
	{
		for (int j = 0; j < n; j++)
		{
			dp[i][j] = -1;
		}
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n2; j++)
		{
			sciezka[i][j] = -1;
		}
	}

	//int rezultat;
	NajlepszaSuma = tsp(1, 0, tab);		// maska = 1 oznacza odwiedzenie pierwszego wierzcholka
	//pozycja = 0 oznacza start algorytmu w wierzcholku pierwszym (ktorego indeks = 0)
	
	//return rezultat;
}

//Funkcja do odkrywania sciezki
void DYNAMICZNOSC::zrob_sciezke(int start, int set)
{
	if (sciezka[start][set] == -1)
	{
		return;
	}
	int i;
	i = sciezka[start][set];
	cout << i << " ";
	int NowySet = set | (1 << i);
	zrob_sciezke(i, NowySet);
}

DYNAMICZNOSC::~DYNAMICZNOSC()
{
	for (int i = 0; i < n2; i++)
	{
		delete[] dp[i];
	}

	for (int i = 0; i < n; i++)
	{
		delete[] sciezka[i];
	}

	delete[] dp;
	delete[] sciezka;
}

