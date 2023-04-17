#pragma once
class Wyzarzenie
{
public:
	int najlepszy_koszt;

	~Wyzarzenie();

	void rozwiazanie_wyrzazone(int, int**, double, double, double);

private:
	int* sciezka;

	void zamiana(int, int );

	int LiczKoszt(int, int**);
	
	double WezPrawdopodobienstwo(int, int, double);

	double WezSzanse();

};

