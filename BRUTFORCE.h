#pragma once

//#include "GRAF.h"

//#include <iomanip>

class BRUTFORCE
{
	public:
		int* NajlepszaSciezka;
		int NajlepszaSuma;
		int BiezacaSuma;
		int* TablicaDrogi;

		//BRUTFORCE();

		//~BRUTFORCE();

		void rozwiazanie_silowe(int, int**);

	private:
		void permutacje(int*, int, int, int*, int&, int&, int**);

		void zamiana(int&, int&);
		
};

