#include "BRUTFORCE.h"

#include <iostream>

using namespace std;

//#include <windows.h>
//#include <iomanip>

//#include "GRAF.h"

void BRUTFORCE::rozwiazanie_silowe(int rozmiar, int** graf)
{
	NajlepszaSciezka = new int[rozmiar];
	NajlepszaSuma = 0;
	BiezacaSuma = 0;
	TablicaDrogi = new int[rozmiar - 1];	//wierzcholki poza tym z indeksem 0 - droga miedzy poczatkiem i koncem

	//wybranie najpierw 1 z brzegu sciezki jako domyslnej, jak znajdzie sie lepsza to sie zamieni

	for (int i = 0; i < rozmiar - 1; i++)
	{
		NajlepszaSciezka[i] = i + 1;
		NajlepszaSuma = NajlepszaSuma + graf[i][i + 1];

		TablicaDrogi[i] = i + 1;
	}

	NajlepszaSciezka[rozmiar - 1] = 0;
	NajlepszaSuma = NajlepszaSuma + graf[rozmiar - 1][0];

	permutacje(TablicaDrogi, 0, rozmiar - 1, NajlepszaSciezka, NajlepszaSuma, BiezacaSuma, graf);

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
}

void BRUTFORCE::permutacje(int T[], int ix, int R, int* NajSciezka, int& NajSuma, int& BiezSuma, int** NaszGraf) // ix = 0..N-1
{
	if (ix < R - 1)
	{
		for (int i = ix; i < R; i++)
		{
			zamiana(T[ix], T[i]); // zamienia dwa elementy miejscami
			permutacje(T, ix + 1, R, NajSciezka, NajSuma, BiezSuma, NaszGraf);
			zamiana(T[ix], T[i]); // przywracamy
		}
	}
	else
		{
			//obliczanie biezacej sumy
			BiezSuma = 0;

			int wierszgrafu = 0;
			int kolumnagrafu = T[0];
			BiezSuma = BiezSuma + NaszGraf[wierszgrafu][kolumnagrafu];

			for (int i = 0; i < R - 1; i++)
			{
				wierszgrafu = T[i];
				kolumnagrafu = T[i + 1];

				BiezSuma = BiezSuma + NaszGraf[wierszgrafu][kolumnagrafu];

				//cout << T[i]; // 1234 bez rozdzielania... - do testu
			}

			wierszgrafu = T[R - 1];
			kolumnagrafu = 0;
			BiezSuma = BiezSuma + NaszGraf[wierszgrafu][kolumnagrafu];

			//cout << T[R - 1]; //- do testu
			//cout << "		Suma przejœcia to " << BiezSuma;

			//sprawdzenie czy mamy nowa najlepsza sume
			if (BiezSuma < NajSuma)
			{
				NajSuma = BiezSuma;

				for (int i = 0; i < R; i++)
				{
					NajSciezka[i] = T[i];
				}

				/* - do testu
				cout << "		To jest najlepsza suma, œcie¿ka to : 0 -> ";

				for (int i = 0; i < R+1; i++)
				{
					cout << " " << NajSciezka[i];
				}
				*/
			}

			//cout << endl; // nowa linia; - do testu
		}
}

void BRUTFORCE::zamiana(int& a, int& b)
{
	int c = a;
	a = b;
	b = c;
}



