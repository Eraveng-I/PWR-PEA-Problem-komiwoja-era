#include "Czas.h"
#include <iostream>
#include <windows.h>
#include <iomanip>

using namespace std;

long long int Czas::read_QPC()
{
    LARGE_INTEGER count;
    QueryPerformanceCounter(&count);
    return((long long int)count.QuadPart);
}

void Czas::czasStart() 
{
    QueryPerformanceFrequency((LARGE_INTEGER*)&czestotliwosc);
    czasPoczatkowy = read_QPC();
}

void Czas::czasStop() 
{
    QueryPerformanceFrequency((LARGE_INTEGER*)&czestotliwosc);
    czasKoncowy = read_QPC();
}

long long int Czas::czasWykonania() 
{
    return czasKoncowy - czasPoczatkowy;
}

void Czas::zmierz_czas()
{
	/*long long int frequency, start, elapsed;
	QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);
	start = read_QPC();
	Sleep(1000); // kod ktorego czas wykonania mierzymy
	elapsed = read_QPC() - start;
	cout << "Time [s] = " << fixed << setprecision(3) << (float)elapsed /
		frequency << endl;
	cout << "Time [ms] = " << setprecision(0) << (1000.0 * elapsed) /
		frequency << endl;
	cout << "Time [us] = " << setprecision(0) << (1000000.0 * elapsed) /
		frequency << endl << endl;
	system("PAUSE");*/

	cout << "Czas wykonania to: " << /*setprecision(0) <<*/ (1000 * czasWykonania()) / czestotliwosc << "ms" << endl << endl;
}