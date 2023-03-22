//
//  main.cpp
//  pijak_smc
//
//  Created by Mateusz on 01/03/2019.
//  Copyright © 2019 Mateusz. All rights reserved.
//


#include <iostream>
#include <cstdlib>
#include <stdlib.h>  // for srand(), rand() and RAND_MAX
#include <math.h>  // for sqrt(), log() and sin()
#include <time.h>  // for time()
#include <fstream>
#include <random>

using namespace std;

double r;
int liczba_pijakow = 1000;
int liczba_krokow = 1000;
int k=0;

int main()
{
    fstream plik;
    plik.open("pijaczek.txt",ios::out);
 
 mt19937 gen{random_device{}()};    // generator liczb losowych
 
 normal_distribution<double> rand{0.0, 1.0};    // rozkład jednorodny


    for (int i=0; i<=liczba_pijakow; i++)   // badamy drogę kolejnych pijaków
    {
        for (int j=0; j<liczba_krokow; j++)    // badamy kolejne kroki pijaka
        {
            r=rand(gen);  // tu losujemy jakąś randomową liczbę
            
            if (r>=0)
            {
                k=k+1;
            }
            else
            {
                k=k-1;
            }
        }
        plik << k << endl;  // zapis do pliku
        k=0;
    }
    plik.close();
    return 0;
}

