#pragma once
class DYNAMICZNOSC
{
	public:
		int n;	//Rozmiar problemu
		int n2;	//Rozmiar potrzebnych tablic (1 << n lub tez 2^n)
		int** dp;	//Tablica do zapisywania rozwiazan
		int** sciezka;	//Tablica potrzebne do wyluskiwania sciezek
		int WszystkoOdwiedzone;	//Maska oznaczajaca odwiedzenie wszystkich wierzcholkow
		int NajlepszaSuma;	//ostateczny najlepszy wynik

		void rozwiazanie_dynamiczne(int, int**);

		void inicjalizacja(int);

		int tsp(int, int, int**);

		void znajdz_rozwiazanie(int** );

		void zrob_sciezke(int, int);

		~DYNAMICZNOSC();
		
	private:
};

