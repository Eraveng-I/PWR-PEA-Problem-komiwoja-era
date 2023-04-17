#pragma once
class Tabu
{
	public:
		int* NajlepszaSciezka;
		int NajlepszaSuma;
		int BiezacaSuma;
		int* TablicaDrogi;
		int** TablicaTabu;

		void rozwiazanie_tabu(int, int**);

	private:

};

