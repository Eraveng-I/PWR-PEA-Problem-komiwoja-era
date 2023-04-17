#include "Genetyka.h"
#include "Czas.h"

#include <iostream>

using namespace std;

void Genetyka::rozwiazanie_genow(int rozmiar, int** graf, int populacja, double krzyzowanie, double mutacjowanie, int LimitCzasu, long long int CzasStart)
{
	Czas CzasLokalny;
	CzasLokalny.czasPoczatkowy = CzasStart;

	GrafLokalny = graf;
	NajlepszaSciezkaG = new int[rozmiar];
	NajlepszaSumaG = 0;

	//tworzenie losowej populacji na poczatku
	CalaPopulacja = new int* [populacja];

	for (int i = 0; i < populacja; i++)
	{
		CalaPopulacja[i] = new int[rozmiar - 1];

		losowanko(CalaPopulacja[i], rozmiar - 1);
	}

	//wybranie najpierw 1 z brzegu sciezki jako domyslnej, jak znajdzie sie lepsza to sie zamieni

	for (int i = 0; i < rozmiar - 1; i++)
	{
		NajlepszaSciezkaG[i] = i + 1;
		NajlepszaSumaG = NajlepszaSumaG + GrafLokalny[i][i + 1];

		//TablicaDrogi[i] = i + 1;
	}

	NajlepszaSciezkaG[rozmiar - 1] = 0;
	NajlepszaSumaG = NajlepszaSumaG + GrafLokalny[rozmiar - 1][0];
	//

	//teesty1
	/*for (int i = 0; i < populacja; i++)
	{
		for (int j = 0; j < rozmiar - 1; j++)
		{
			cout << CalaPopulacja[i][j] << " ";
		}
		cout << endl;
	}*/

	sortowanie_drog(CalaPopulacja, populacja, rozmiar-1);

	//teesty2
	/*for (int i = 0; i < populacja; i++)
	{
		for (int j = 0; j < rozmiar - 1; j++)
		{
			cout << CalaPopulacja[i][j] << " ";
		}
		cout << endl;
	}*/

	if (obliczenie_drogi(CalaPopulacja[0], rozmiar - 1) < NajlepszaSumaG)
	{
		NajlepszaSumaG = obliczenie_drogi(CalaPopulacja[0], rozmiar - 1);

		for (int i = 0; i < rozmiar-1; i++)
		{
			NajlepszaSciezkaG[i] = CalaPopulacja[0][i];
		}

		/* - do testu
		cout << "To jest najlepsza suma, œcie¿ka to : 0 -> ";

		for (int i = 0; i < rozmiar; i++)
		{
			cout << " " << NajlepszaSciezkaG[i];
		}

		cout << endl; // nowa linia; - do testu*/
	}

	//iteracje nowych pokolen
	int RozmiarKrzyzowcow = krzyzowanie * populacja;	//0.8*populacja
	int** krzyzowcy = new int* [RozmiarKrzyzowcow];

	for (int j = 0; j < RozmiarKrzyzowcow; j++)
	{
		krzyzowcy[j] = new int[rozmiar - 1];

		for (int k = 0; k < rozmiar - 1; k++)
		{
			krzyzowcy[j][k] = CalaPopulacja[j][k];
		}
	}

	//for (int i=0;i<1000;i++)
	for (;;)
	{
		CzasLokalny.czasStop();

		if ((1000 * CzasLokalny.czasWykonania()) / CzasLokalny.czestotliwosc >= LimitCzasu * 1000)
		{
			break;
		}

		for (int j = 0; j+1 <= RozmiarKrzyzowcow; j=j+2)
		{
			int* potomek1 = new int[rozmiar - 1];
			int* potomek2 = new int[rozmiar - 1];

			int IndexPoczatek;
			int IndexKoniec;

			do
			{
				IndexPoczatek = rand() % (rozmiar - 1);
				IndexKoniec = rand() % (rozmiar - 1);

				if (IndexPoczatek > IndexKoniec)
				{
					swap(IndexPoczatek, IndexKoniec);
				}

			} while (IndexPoczatek==IndexKoniec);

			//genowanie
			for (int k = IndexPoczatek; k <= IndexKoniec; k++)
			{
				potomek1[k] = krzyzowcy[j + 1][k];
				potomek2[k] = krzyzowcy[j][k];
			}

			int IndeksPrzepisania1 = 0;
			for (int k = 0; k < rozmiar - 1; k++)
			{
				//ominiecie juz wpisanego obszaru z innego rodzica
				if (IndexPoczatek <= k && k <= IndexKoniec)
				{
					continue;
				}

				int pozwolenie1 = 1;
				
				//sprawdzenie czy liczba nie byla wczesniej juz wpisana z innego rodzica
				do
				{ 
					pozwolenie1 = 1;
					for (int l = IndexPoczatek; l <= IndexKoniec; l++)
					{
						if (krzyzowcy[j][IndeksPrzepisania1] == potomek1[l])
						{
							pozwolenie1 = 0;
							IndeksPrzepisania1 = IndeksPrzepisania1 + 1;
							break;
						}
					}
				}while (pozwolenie1==0);

				potomek1[k] = krzyzowcy[j][IndeksPrzepisania1];
				IndeksPrzepisania1 = IndeksPrzepisania1 + 1;
			}

			//testy
			/*cout << "1poczatek i koniec to: " << IndexPoczatek << " " << IndexKoniec << endl;
			for (int l = 0; l < rozmiar - 1; l++)
			{
				cout << krzyzowcy[j][l] << " ";
			}
			cout << endl;
			for (int l = 0; l < rozmiar - 1; l++)
			{
				cout << krzyzowcy[j+1][l] << " ";
			}
			cout << endl;
			for(int l = 0; l < rozmiar - 1; l++)
			{
				cout << potomek1[l] << " ";
			}
			cout << endl;*/

			int IndeksPrzepisania2 = 0;
			for (int k = 0; k < rozmiar - 1; k++)
			{
				//ominiecie juz wpisanego obszaru z innego rodzica
				if (IndexPoczatek <= k && k <= IndexKoniec)
				{
					continue;
				}

				int pozwolenie2 = 1;

				//sprawdzenie czy liczba nie byla wczesniej juz wpisana z innego rodzica
				do
				{
					pozwolenie2 = 1;
					for (int l = IndexPoczatek; l <= IndexKoniec; l++)
					{
						if (krzyzowcy[j+1][IndeksPrzepisania2] == potomek2[l])
						{
							pozwolenie2 = 0;
							IndeksPrzepisania2 = IndeksPrzepisania2 + 1;
							break;
						}
					}
				} while (pozwolenie2 == 0);

				potomek2[k] = krzyzowcy[j+1][IndeksPrzepisania2];
				IndeksPrzepisania2 = IndeksPrzepisania2 + 1;
			}

			//testy
			/*cout << "2poczatek i koniec to: " << IndexPoczatek << " " << IndexKoniec << endl;
			for (int l = 0; l < rozmiar - 1; l++)
			{
				cout << krzyzowcy[j][l] << " ";
			}
			cout << endl;
			for (int l = 0; l < rozmiar - 1; l++)
			{
				cout << krzyzowcy[j+1][l] << " ";
			}
			cout << endl;
			for(int l = 0; l < rozmiar - 1; l++)
			{
				cout << potomek2[l] << " ";
			}
			cout << endl;*/

			//szansa mutacji
			mutacje(potomek1, rozmiar - 1, mutacjowanie);
			mutacje(potomek2, rozmiar - 1, mutacjowanie);

			//zapisanie potomkow do krzyzowcow
			for (int k = 0; k < rozmiar - 1; k++)
			{
				krzyzowcy[j][k] = potomek1[k];
				krzyzowcy[j+1][k] = potomek2[k];
			}

			//usunac potomkow
			delete[] potomek1;
			delete[] potomek2;
		}

		//cout << "RozmiarKrzyzowcow to: " << RozmiarKrzyzowcow << endl;	//linia do testow

		//laczona tablica
		int** DuzaTablicaDrog = new int* [populacja + RozmiarKrzyzowcow];

		for (int j = 0; j < populacja + RozmiarKrzyzowcow; j++)
		{
			DuzaTablicaDrog[j] = new int[rozmiar - 1];
		}

		for (int j = 0; j < populacja; j++)
		{
			for (int k = 0; k < rozmiar - 1; k++)
			{
				DuzaTablicaDrog[j][k] = CalaPopulacja[j][k];
			}
		}

		for (int j = 0; j < RozmiarKrzyzowcow; j++)
		{
			for (int k = 0; k < rozmiar - 1; k++)
			{
				DuzaTablicaDrog[j+populacja][k] = krzyzowcy[j][k];
			}
		}

		sortowanie_drog(DuzaTablicaDrog, populacja + RozmiarKrzyzowcow, rozmiar - 1);

		//przepis
		for (int j = 0; j < populacja; j++)
		{
			for (int k = 0; k < rozmiar - 1; k++)
			{
				CalaPopulacja[j][k] = DuzaTablicaDrog[j][k];
			}
		}

		//usuniecie duzej tablicy
		for (int j = 0; j < populacja + RozmiarKrzyzowcow; j++)
		{
			delete[] DuzaTablicaDrog[j];
		}

		delete[] DuzaTablicaDrog;

		if (obliczenie_drogi(CalaPopulacja[0], rozmiar - 1) < NajlepszaSumaG)
		{
			NajlepszaSumaG = obliczenie_drogi(CalaPopulacja[0], rozmiar - 1);

			for (int j = 0; j < rozmiar - 1; j++)
			{
				NajlepszaSciezkaG[j] = CalaPopulacja[0][j];
			}

			// - do testu
			/*cout << "To jest nowa najlepsza suma, œcie¿ka to : 0 -> ";

			for (int i = 0; i < rozmiar; i++)
			{
				cout << " " << NajlepszaSciezkaG[i];
			}

			cout << endl; // nowa linia; - do testu
			*/
		}
	}

	//wypisanie ostatecznego wyniku
	cout << "Najkrótsza droga ma d³ugoœæ " << NajlepszaSumaG << " i idzie przez:" << endl;

	cout << "0 -> ";

	for (int i = 0; i < rozmiar; i++)
	{
		cout << " " << NajlepszaSciezkaG[i];
	}

	cout << endl;

	//usunac krzyzowcow
	for (int i = 0; i < RozmiarKrzyzowcow; i++)
	{
		delete[] krzyzowcy[i];
	}

	delete[] krzyzowcy;
	//usuwamy tablice dynamiczne
	delete[] NajlepszaSciezkaG;
	//delete[] TablicaDrogi;

	for (int i = 0; i < populacja; i++)
	{
		delete[] CalaPopulacja[i];
	}

	delete[] CalaPopulacja;
}

void Genetyka::losowanko(int* GenerowanaDroga, int rozmiar_osobnika)
{
	for (int i = 0; i < rozmiar_osobnika; i++)
	{
		GenerowanaDroga[i] = rand() % rozmiar_osobnika + 1;

		for (int j = 0; j < i; j++)
		{
			if (GenerowanaDroga[j] == GenerowanaDroga[i])
			{
				i = i - 1;
				break;
			}
		}
	}

	//testy
	/*for (int i = 0; i < rozmiar_osobnika; i++)
	{
		cout << GenerowanaDroga[i] << " ";
	}

	cout << endl;*/
}

int Genetyka::obliczenie_drogi(int* LiczonaDroga, int RozmiarDrogi)
{	
	//obliczanie biezacej sumy
	int suma = 0;

	int wierszgrafu = 0;
	int kolumnagrafu = LiczonaDroga[0];
	suma = suma + GrafLokalny[wierszgrafu][kolumnagrafu];

	for (int i = 0; i < RozmiarDrogi-1; i++)
	{
		wierszgrafu = LiczonaDroga[i];
		kolumnagrafu = LiczonaDroga[i + 1];

		suma = suma + GrafLokalny[wierszgrafu][kolumnagrafu];

		//cout << T[i]; // 1234 bez rozdzielania... - do testu
	}

	wierszgrafu = LiczonaDroga[RozmiarDrogi - 1];
	kolumnagrafu = 0;
	suma = suma + GrafLokalny[wierszgrafu][kolumnagrafu];

	return suma;
}

void Genetyka::sortowanie_drog(int** TablicaDrog, int RozmiarTablicy, int RozmiarDrogi)
{
	for (int i = 0; i < RozmiarTablicy - 1; i++)
	{
		for (int j = 0; j < RozmiarTablicy - 1 - i; j++)
		{
			if (obliczenie_drogi(TablicaDrog[j], RozmiarDrogi) > obliczenie_drogi(TablicaDrog[j + 1], RozmiarDrogi))
			{
				int* zamiennik = TablicaDrog[j];
				TablicaDrog[j] = TablicaDrog[j + 1];
				TablicaDrog[j + 1] = zamiennik;
			}
		}
	}
}

void Genetyka::mutacje(int* TablicaDrogi, int RozmiarDrogi, double szansa)
{
	int mnoznik = 1000;
	int los = rand() % mnoznik;

	if (los <= szansa * mnoznik)
	{
		//testy1
		/*cout << "robimy mutacje" << endl;
		for (int i = 0; i < RozmiarDrogi; i++)
		{
			cout << TablicaDrogi[i];
		}
		cout << endl;*/

		int index1, index2;

		do
		{
			index1 = rand() % (RozmiarDrogi);
			index2 = rand() % (RozmiarDrogi);
		} while (index1 == index2);

		swap(TablicaDrogi[index1], TablicaDrogi[index2]);

		//testy2
		/*cout << "zamiana indeksow: " <<index1<<" "<<index2<< endl;
		for (int i = 0; i < RozmiarDrogi; i++)
		{
			cout << TablicaDrogi[i];
		}
		cout << endl;*/
	}
}