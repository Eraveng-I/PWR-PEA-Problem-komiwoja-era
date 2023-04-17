#pragma once
class Genetyka
{
public:
	int* NajlepszaSciezkaG;
	int NajlepszaSumaG;
	
	int** CalaPopulacja;

	void rozwiazanie_genow(int, int**, int, double,double, int, long long int);

private:
	int** GrafLokalny;

	void losowanko(int*,int);

	int obliczenie_drogi(int*, int);

	void sortowanie_drog(int**, int, int);

	//void iteracje(int**, int, int);

	void mutacje(int*, int, double);
};

