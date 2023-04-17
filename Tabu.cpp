#include "Tabu.h"

#include <iostream>

using namespace std;

void Tabu::rozwiazanie_tabu(int rozmiar, int** graf)
{
	NajlepszaSciezka = new int[rozmiar];
	NajlepszaSuma = 0;
	BiezacaSuma = 0;
	TablicaDrogi = new int[rozmiar - 1];	//wierzcholki poza tym z indeksem 0 - droga miedzy poczatkiem i koncem

	//ustawienie tablicy tabu, jesli jest 0, mozna uzyc, jesli nie to ruch zablokowany
	TablicaTabu = new int* [rozmiar-1];

	for (int i = 0; i < rozmiar-1; i++)
	{
		TablicaTabu[i] = new int[rozmiar - 1];

		for (int j = 0; j < rozmiar - 1; j++)
		{
			TablicaTabu[i][j] = 0;
		}
	}

	for (int j = 0; j < rozmiar - 1; j++)
	{
		TablicaTabu[j][j] = 1;
	}
	

	//wybranie najpierw 1 z brzegu sciezki jako domyslnej, jak znajdzie sie lepsza to sie zamieni

	for (int i = 0; i < rozmiar - 1; i++)
	{
		NajlepszaSciezka[i] = i + 1;
		NajlepszaSuma = NajlepszaSuma + graf[i][i + 1];

		TablicaDrogi[i] = i + 1;
	}

	NajlepszaSciezka[rozmiar - 1] = 0;
	NajlepszaSuma = NajlepszaSuma + graf[rozmiar - 1][0];

	//glowna petla
	for (int i = 0; i < rozmiar - 1; i++)
	{
		for (int j = 0; j < rozmiar - 1; j++)
		{
			int WierszTabu = TablicaDrogi[i]-1;
			int KolumnaTabu = TablicaDrogi[j]-1;

			if (TablicaTabu[WierszTabu][KolumnaTabu] == 0)
			{
				swap(TablicaDrogi[i], TablicaDrogi[j]);

				/*cout << "aktualna droga to: ";	do testu
				for (int i = 0; i < rozmiar - 1; i++)
				{
					cout << TablicaDrogi[i] << " ";
				}
				cout << endl;*/

				//obliczanie biezacej sumy
				BiezacaSuma = 0;

				int wierszgrafu = 0;
				int kolumnagrafu = TablicaDrogi[0];
				BiezacaSuma = BiezacaSuma + graf[wierszgrafu][kolumnagrafu];
				//cout << "BiezacaSuma = " << BiezacaSuma << endl;	do testu

				for (int i = 0; i < rozmiar - 2; i++)
				{
					wierszgrafu = TablicaDrogi[i];
					kolumnagrafu = TablicaDrogi[i + 1];

					//cout << "Wiersz grafu = " << wierszgrafu << endl;		//do testu
					//cout << "kolumna grafu = " << kolumnagrafu << endl;	//do testu

					BiezacaSuma = BiezacaSuma + graf[wierszgrafu][kolumnagrafu];
					//cout << "BiezacaSuma = " << BiezacaSuma << endl;	//do testu

					//cout << T[i]; // 1234 bez rozdzielania... - do testu
				}

				wierszgrafu = TablicaDrogi[rozmiar - 2];
				kolumnagrafu = 0;
				BiezacaSuma = BiezacaSuma + graf[wierszgrafu][kolumnagrafu];

				//cout << "Przed warunkiem BiezacaSuma = " << BiezacaSuma << endl;	//do testu

				//sprawdzenie czy mamy nowa najlepsza sume
				if (BiezacaSuma < NajlepszaSuma)
				{
					TablicaTabu[WierszTabu][KolumnaTabu] = 1;
					TablicaTabu[KolumnaTabu][WierszTabu] = 1;

					NajlepszaSuma = BiezacaSuma;

					for (int i = 0; i < rozmiar-1; i++)
					{
						NajlepszaSciezka[i] = TablicaDrogi[i];	//tu moze wyciek
						//cout << "NajlepszaSciezkaG[i] = TablicaDrogi[i] = wartossc: " << TablicaDrogi[i] << endl; do testu
					}

					/* - do testu
					cout << "		To jest najlepsza suma, œcie¿ka to : 0 -> ";

					for (int i = 0; i < R+1; i++)
					{
						cout << " " << NajSciezka[i];
					}
					*/
				}
				else
					{
						swap(TablicaDrogi[i], TablicaDrogi[j]);	//odwracamy jesli to nie pomoglo
					}
			}
			
		}
	}

	//wypisanie rezultatu
	cout << "Najkrótsza droga ma d³ugoœæ " << NajlepszaSuma << " i idzie przez:" << endl;

	cout << "0 -> ";

	for (int i = 0; i < rozmiar; i++)
	{
		cout << " " << NajlepszaSciezka[i];
	}

	cout << endl;

	//usuwamy tablice dynamiczne
	delete[] NajlepszaSciezka;
	delete[] TablicaDrogi;

	for (int i = 0; i < rozmiar-1; i++)
	{
		delete[] TablicaTabu[i];
	}

	delete[] TablicaTabu;
}
