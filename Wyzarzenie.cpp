#include "Wyzarzenie.h"
#include <iostream>
#include <stdlib.h>
#include <math.h>
using namespace std;

void Wyzarzenie::zamiana(int i, int j)
{
	int tmp = sciezka[i];
	sciezka[i] = sciezka[j];
	sciezka[j] = tmp;
}

void Wyzarzenie::rozwiazanie_wyrzazone(int rozmiar, int** graf, double temperatura_start, double temperatura_koniec, double chlodzenie)
{
	najlepszy_koszt = INT_MAX;
	sciezka = new int[rozmiar + 1];
	for (int i = 0; i < rozmiar; i++)
	{
		sciezka[i] = i;
	}
	sciezka[rozmiar] = 0;

	int koszt1, koszt2, index1, index2;
	int licznik = 0;
	double temperatura = temperatura_start;

	//losowanie zamian
	int j;
	for (int i = rozmiar - 2; i > 1; i--)
	{
		j = rand() % (i + 1) + 1;
		zamiana(i, j);
	}

	//sprawdzenie czy korzystne i zostawic
	while (temperatura > temperatura_koniec)
	{
		koszt1 = LiczKoszt(rozmiar, graf);
		index1 = rand() % (rozmiar - 1) + 1;
		index2 = rand() % (rozmiar - 1) + 1;
		zamiana(index1, index2);
		koszt2 = LiczKoszt(rozmiar, graf);
		if (koszt2 >= koszt1 && WezSzanse() >= WezPrawdopodobienstwo(koszt1, koszt2, temperatura))
		{
			zamiana(index1, index2);
		}
		temperatura = temperatura * chlodzenie;
		licznik++;
	}
	najlepszy_koszt = koszt1;

	//wypisanie rezultatu
	cout << "Ilosc potrzebnych iteracji: " << licznik << endl;	
	cout << "Najkrótsza droga ma d³ugoœæ " << najlepszy_koszt << " i idzie przez:" << endl;

	cout << "0 -> ";

	for (int i = 1; i < rozmiar+1; i++)
	{
		cout << " " << sciezka[i];
	}

	cout << endl;
}

int Wyzarzenie::LiczKoszt(int n, int** graf)
{
	int koszt = 0;
	for (int i = 0; i < n; i++)
	{
		koszt = koszt + graf[sciezka[i]][sciezka[i + 1]];
	}
	return koszt;
}

double Wyzarzenie::WezPrawdopodobienstwo(int koszt1, int koszt2, double T)
{
	int delta = koszt2 - koszt1;
	return exp(-delta / T);
}

double Wyzarzenie::WezSzanse()
{
	return rand() / (RAND_MAX);
}

Wyzarzenie:: ~Wyzarzenie()
{
	if (sciezka != NULL)
	{
		delete[] sciezka;
	}
}
