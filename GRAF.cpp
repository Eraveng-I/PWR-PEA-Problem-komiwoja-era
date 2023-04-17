#include "GRAF.h"

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

//GRAF::;
void GRAF::ustawienie_grafu()
{
	graf = new int* [rozmiar];

	for (int i = 0; i < rozmiar; i++)
	{
		graf[i] = new int[rozmiar];
	}
}

void GRAF:: usuwanie_grafu()
{
	for (int i = 0; i < rozmiar; i++)
	{
		delete[] graf[i];
	}

	delete[] graf;
}

void GRAF::losowy_graf()
{
	cout << "Podaj rozmiar grafu:" << endl;
	cin >> rozmiar;

	ustawienie_grafu();

	for (int i = 0; i < rozmiar; i++)
	{
		for (int j = 0; j < rozmiar; j++)
		{
			if (i == j)
			{
				graf[i][j] = 0;
			}
			else
			{
				graf[i][j] = rand() % 9 + 1;
			}
		}
	}
}

void GRAF::testowy_losowy_graf(int r)
{
	rozmiar = r;

	ustawienie_grafu();

	for (int i = 0; i < rozmiar; i++)
	{
		for (int j = 0; j < rozmiar; j++)
		{
			if (i == j)
			{
				graf[i][j] = 0;
			}
			else
			{
				graf[i][j] = rand() % 9 + 1;
			}
		}
	}
}

void GRAF::graf_z_pliku()
{
	ifstream plik;
	string NazwaPliku;
	int poprawnosc = 1;

	//testy
	cout << "Podaj nazwê pliku z rozszerzeniem:" << endl;
	cin >> NazwaPliku;

	plik.open(NazwaPliku);

	if (plik.good())
	{
		cout << "Uda³o siê otworzyæ plik" << endl;
		sukces = 1;

		plik >> rozmiar;

		ustawienie_grafu();

		//ustalenie odleg³oœci z pliku
		for (int i = 0; i < rozmiar; i++)
		{
			for (int j = 0; j < rozmiar; j++)
			{
				plik >> graf[i][j];
			}
		}

		//sprawdzenie poprawnosci wczytania z pliku
		for (int i = 0; i < rozmiar; i++)
		{
			for (int j = 0; j < rozmiar; j++)
			{
				if (i == j)
				{
					if (graf[i][j] != 0)
					{
						poprawnosc = 0;
						break;
					}
				}
				else
					{
						if (graf[i][j] < 0)
						{
							poprawnosc = 0;
							break;
						}
					}
				
			}

			if (poprawnosc == 0)
			{
				cout << "le wczytano dane z pliku lub nieprawid³owy plik" << endl;
				usuwanie_grafu();
				sukces = 0;
				break;
			}
		}

		plik.close();
	}
	else
	{
		cout << "Nie uda³o siê otworzyæ plik" << endl;

		sukces = 0;
	}
}

void GRAF::wyswietlenie_grafu()
{
	cout << "Rozmiar grafu to " << rozmiar << endl;

	for (int i = 0; i < rozmiar; i++)
	{
		for (int j = 0; j < rozmiar; j++)
		{
			cout << graf[i][j] << "  ";
		}

		cout << endl;
	}
}

