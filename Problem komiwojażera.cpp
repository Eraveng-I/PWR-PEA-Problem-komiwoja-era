// Problem komiwojażera.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <fstream>
#include <iostream>
using namespace std;

#include "GRAF.h"
#include "BRUTFORCE.h"
#include "DYNAMICZNOSC.h"
//#include "BandB.h"
#include "Czas.h"

#include "Tabu.h"
#include "Wyzarzenie.h"

#include "Genetyka.h"


int main()
{
	int wybor = -1;
	int wybor2 = -1;
	int wybor3 = -1;

	int p = 100;
	int c = 60;
	double m = 0.01;
	double k = 0.08;

	//obiektowka
	GRAF miasta;
	BRUTFORCE brutal;
	Czas czas;
	DYNAMICZNOSC dynamik;
	//BandB galaz;
	Tabu lamacz;
	Wyzarzenie zar;
	Genetyka geny;

	srand(time(NULL));

	setlocale(LC_ALL, "Polish");

	while (wybor != 0)
	{
		wybor2 = -1;

		cout << "Problem komiwojażera!" << endl << "wybierz co chcesz zrobić:\n";
		cout << "1 - wygeneruj graf" << endl;
		cout << "2 - załaduj graf z pliku" << endl;
		cout << "0 - wyjście\n";

		cin >> wybor;

		if (wybor == 0)
		{
			break;
		}
		else
		{
			switch (wybor)
			{
				//graf losowy
			case 1:
			{
				miasta.losowy_graf();

				break;
			}
			//graf z pliku
			case 2:
			{
				miasta.graf_z_pliku();

				if (miasta.sukces == 0)
				{
					wybor2 = 0;
				}

				break;
			}
			default:
				break;
			}
		}

		while (wybor2 != 0)
		{
			cout << "Wybierz metodę rozwiązania problemu:" << endl;
			cout << "1 - Wyświetl graf" << endl;
			cout << "2 - brutforce" << endl;
			cout << "3 - metoda B&B - dziel i ograniczaj" << endl;
			cout << "4 - programowanie dynamiczne" << endl;
			cout << "5 - tabu search" << endl;
			cout << "6 - wyżarzanie" << endl;
			cout << "7 - genetyka" << endl;
			cout << "8 - testy" << endl;
			cout << "9 - zmiana parametrów genetyki" << endl;
			cout << "0 - wróć do poprzedniego punktu" << endl;

			cin >> wybor2;

			if (wybor2 == 0)
			{
				miasta.usuwanie_grafu();
				break;
			}
			else
			{
				switch (wybor2)
				{
					//wyswietlenie grafu
				case 1:
				{
					miasta.wyswietlenie_grafu();

					break;
				}

				//brutforce
				case 2:
				{
					//miasta.
					czas.czasStart();

					brutal.rozwiazanie_silowe(miasta.rozmiar, miasta.graf);

					czas.czasStop();
					czas.zmierz_czas();
					break;
				}

				//B&B - dziel i ograniczaj
				case 3:
				{
					czas.czasStart();

					//galaz.rozwiazanie_dzielonej_galezi(miasta.rozmiar, miasta.graf);

					czas.czasStop();
					czas.zmierz_czas();
					break;
				}

				case 4:
				{
					czas.czasStart();

					dynamik.rozwiazanie_dynamiczne(miasta.rozmiar, miasta.graf);

					czas.czasStop();
					czas.zmierz_czas();

					//
					break;
				}

				case 5:
				{
					czas.czasStart();

					lamacz.rozwiazanie_tabu(miasta.rozmiar, miasta.graf);

					czas.czasStop();
					czas.zmierz_czas();

					//
					break;
				}

				case 6:
				{
					double temperatura_start, temperatura_koniec, chlodzenie;
					cout << "Podaj temperature poczatkowa: ";
					cin >> temperatura_start;
					cout << "Podaj temperature koncowa: ";
					cin >> temperatura_koniec;
					cout << "Podaj wspolczynnik chlodzenia: ";
					cin >> chlodzenie;

					czas.czasStart();

					zar.rozwiazanie_wyrzazone(miasta.rozmiar, miasta.graf, temperatura_start, temperatura_koniec, chlodzenie);

					czas.czasStop();
					czas.zmierz_czas();

					//
					break;
				}

				case 7:
				{
					////int p, c;
					///*cout << "Podaj rozmiar popilacji:" << endl;
					//cin >> p;*/
					//cout << "Podaj limit czasu w sekundach:" << endl;
					//cin >> c;
					//p = 100;

					czas.czasStart();

					geny.rozwiazanie_genow(miasta.rozmiar, miasta.graf, p, k, m, c, czas.czasPoczatkowy);

					czas.czasStop();
					czas.zmierz_czas();

					//
					break;
				}

				case 8:
				{
					int IleRazy;
					int JakaFunkcja;
					int RozmiarGrafu;

					miasta.usuwanie_grafu();

					cout << "Jaką funkcję chcesz testowac: " << endl;
					cin >> JakaFunkcja;
					cout << "Ile testow?" << endl;
					cin >> IleRazy;
					cout << "Na jakim rozmiarze?" << endl;
					cin >> RozmiarGrafu;

					switch (JakaFunkcja)
					{
					case 2:
					{
						for (int i = 0; i < IleRazy; i++)
						{
							miasta.testowy_losowy_graf(RozmiarGrafu);

							miasta.wyswietlenie_grafu();

							czas.czasStart();

							brutal.rozwiazanie_silowe(miasta.rozmiar, miasta.graf);

							czas.czasStop();
							czas.zmierz_czas();

							miasta.usuwanie_grafu();
						}

						break;
					}

					case 4:
					{
						for (int i = 0; i < IleRazy; i++)
						{
							miasta.testowy_losowy_graf(RozmiarGrafu);

							miasta.wyswietlenie_grafu();

							czas.czasStart();

							dynamik.rozwiazanie_dynamiczne(miasta.rozmiar, miasta.graf);

							czas.czasStop();
							czas.zmierz_czas();

							//miasta.usuwanie_grafu();
						}

						break;
					}

					case 5:
					{
						for (int i = 0; i < IleRazy; i++)
						{
							miasta.testowy_losowy_graf(RozmiarGrafu);

							miasta.wyswietlenie_grafu();

							czas.czasStart();

							lamacz.rozwiazanie_tabu(miasta.rozmiar, miasta.graf);

							czas.czasStop();
							czas.zmierz_czas();

							//miasta.usuwanie_grafu();
						}

						break;
					}

					case 6:
					{
						double temperatura_start, temperatura_koniec, chlodzenie;
						cout << "Podaj temperature poczatkowa: ";
						cin >> temperatura_start;
						cout << "Podaj temperature koncowa: ";
						cin >> temperatura_koniec;
						cout << "Podaj wspolczynnik chlodzenia: ";
						cin >> chlodzenie;

						for (int i = 0; i < IleRazy; i++)
						{
							miasta.testowy_losowy_graf(RozmiarGrafu);

							miasta.wyswietlenie_grafu();

							czas.czasStart();

							zar.rozwiazanie_wyrzazone(miasta.rozmiar, miasta.graf, temperatura_start, temperatura_koniec, chlodzenie);

							czas.czasStop();
							czas.zmierz_czas();
						}

						break;
					}

					case 7:
					{
						for (int i = 0; i < IleRazy; i++)
						{
							miasta.testowy_losowy_graf(RozmiarGrafu);

							//miasta.graf_z_pliku();

							miasta.wyswietlenie_grafu();

							//do testow1
							/*cout << "Tabu:" << endl;
							czas.czasStart();

							lamacz.rozwiazanie_tabu(miasta.rozmiar, miasta.graf);

							czas.czasStop();
							czas.zmierz_czas();

							p = 500;
							cout << "Geny z pop=500" << endl;
							czas.czasStart();

							geny.rozwiazanie_genow(miasta.rozmiar, miasta.graf, p, k, m, c, czas.czasPoczatkowy);

							czas.czasStop();
							czas.zmierz_czas();

							p = 200;
							cout << "Geny z pop=200" << endl;
							czas.czasStart();

							geny.rozwiazanie_genow(miasta.rozmiar, miasta.graf, p, k, m, c, czas.czasPoczatkowy);

							czas.czasStop();
							czas.zmierz_czas();
							p = 100;
							cout << "Geny z pop=100" << endl;*/
							//do testow2

							czas.czasStart();

							geny.rozwiazanie_genow(miasta.rozmiar, miasta.graf, p, k, m, c, czas.czasPoczatkowy);

							czas.czasStop();
							czas.zmierz_czas();
						}

						break;
					}

					default:
						break;
					}

					break;
				}

				case 9:
				{
					cout << "Wybierz co chcesz zmienić:" << endl;
					cout << "1 - popuulacja - domyślnie 100" << endl;
					cout << "2 - czas w sekundach - domyślnie 60" << endl;
					cout << "3 - współczynnik mutacji - domyślnie 0.01" << endl;
					cout << "4 - współczynnik krzyżowania - domyślnie 0.8" << endl;

					cin >> wybor3;

					switch (wybor3)
					{
					case 1:
					{
						cout << "Na ile chcesz zmienic?" << endl;
						cin >> p;
						cout << "Zmieniono na: " << p << endl;
						break;
					}

					case 2:
					{
						cout << "Na ile chcesz zmienic?" << endl;
						cin >> c;
						cout << "Zmieniono na: " << c << endl;
						break;
					}

					case 3:
					{
						cout << "Na ile chcesz zmienic?" << endl;
						cin >> m;
						cout << "Zmieniono na: " << m << endl;
						break;
					}

					case 4:
					{
						cout << "Na ile chcesz zmienic?" << endl;
						cin >> k;
						cout << "Zmieniono na: " << k << endl;
						break;
					}

					default:
					{
						break;
					}
					}


					//
					break;
				}

				default:
				{
					break;
				}

				}
			}
		}

		if (miasta.sukces == 8)
		{
			miasta.usuwanie_grafu();
		}

		wybor2 = -1;

		/*if (miasta.sukces != 0)
		{
			miasta.usuwanie_grafu();
		}*/
	}

}

