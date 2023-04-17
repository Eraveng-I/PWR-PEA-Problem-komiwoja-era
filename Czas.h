#include <iostream>

#ifndef Czas_H
#define Czas_H

using namespace std;

class Czas
{
    private:
        long long int read_QPC();
    public:
        long long int czestotliwosc;
        long long int czasPoczatkowy;
        long long int czasKoncowy;

        void czasStart();

        void czasStop();

        long long int czasWykonania();

        void zmierz_czas();
};

#endif //Czas_H