#pragma once
class GRAF
{
	public:
		int rozmiar;
		int** graf;
		int sukces;

		//GRAF();

		//~GRAF();

		
		void usuwanie_grafu();

		void losowy_graf();

		void graf_z_pliku();

		void wyswietlenie_grafu();

		void testowy_losowy_graf(int);

	private:
		void ustawienie_grafu();
};

