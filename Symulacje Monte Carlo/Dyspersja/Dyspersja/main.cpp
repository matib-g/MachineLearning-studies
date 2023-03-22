//
//  main.cpp
//  Dyfuzja
//
//  Created by Mateusz Bulanda - Gorol on 05/03/2019.
//  Copyright © 2019 Mateusz Bulanda - Gorol. All rights reserved.
//
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <fstream>

#define L 40        // wielkość planszy

using namespace std;

int MSC = 50;
int N = 5;                 // liczba cząstek
int s;
bool pozycja [L][L];         // położenie
fstream plik, plik2;


class Czastka
{
private:
    int x, x0, xl, y, y0, yl, d;
    
public:
    Czastka()       // konstruktor rozmieszcza cząstki w przestrzeni
    {
        do
        {
            x=rand()%(L+1);
            y=rand()%(L+1);
        } while (pozycja[x][y]==1);
        pozycja[x][y]=1;
        plik<<x<<" "<<y<<"    ";  // zapisujemy położenie początkowe
        x0=x;
        xl=0;
        y0=y;
        yl=0;
    }
    void ruch() // wykonujemy ruch
    {
        for (int i=0; i<MSC; i++)
        {
            pozycja[x][y]=0;
            d=rand()%4;
        
            switch (d) {
                case 0:
                    if (x==39)
                    {
                        if (pozycja[0][y]==0)
                        {
                            x=0;
                            xl++;
                            pozycja[x][y]=1;
                        }
                        else
                        {
                            pozycja[x][y]=1;
                        }
                    }
                    else
                    {
                        if (pozycja[x+1][y]==0)
                        {
                            x=x+1;
                            xl++;
                            pozycja[x][y]=1;
                        }
                        else
                        {
                            pozycja[x][y]=1;
                        }
                    }
                    break;
                case 2:
                    if(x==0)
                    {
                        if (pozycja[39][y]==0)
                        {
                            x=39;
                            xl--;
                            pozycja[x][y]=1;
                        }
                        else
                        {
                            pozycja[x][y]=1;
                        }
                    }
                    else
                    {
                        if (pozycja[x-1][y]==0)
                        {
                            x=x-1;
                            xl--;
                            pozycja[x][y]=1;
                        }
                        else
                        {
                            pozycja[x][y]=1;
                        }
                    }
                case 1:
                    if(y==39)
                    {
                        if (pozycja[x][0]==0)
                        {
                            y=0;
                            yl++;
                            pozycja[x][y]=1;
                        }
                        else
                        {
                            pozycja[x][y]=1;
                        }
                    }
                    else
                    {
                        if (pozycja[x][y+1]==0)
                        {
                            y=y+1;
                            yl++;
                            pozycja[x][y]=1;
                        }
                        else
                        {
                            pozycja[x][y]=1;
                        }
                    }
                    break;
                case 3:
                    if(y==0)
                    {
                        if (pozycja[x][39]==0)
                        {
                            y=39;
                            yl--;
                            pozycja[x][y]=1;
                        }
                        else
                        {
                            pozycja[x][y]=1;
                        }
                    }
                    else
                    {
                        if (pozycja[x][y-1]==0)
                        {
                            y=y-1;
                            yl--;
                            pozycja[x][y]=1;
                        }
                        else
                        {
                            pozycja[x][y]=1;
                        }
                    }
            }
        
            plik<<endl<<x<<" "<<y<<"    ";    // zapisujemy kolejne położenia cząstek
            plik2<<endl<<(xl-x0)*(xl-x0)+(yl-y0)*(yl-y0)<<"  "<<s;  //zapisujemy R i MSC

        }
    }
};

int main()
{
    srand((unsigned) time(NULL));
    plik.open ("położenia.txt", ios::out);
    plik2.open ("przemieszczenia.txt", ios::out);
    
    for (int i=0; i<L; i++)
    {
        for(int j=0; j<L; j++)
        {
            pozycja[i][j]=0;
        }
    }
    
    Czastka particle[N];
    
    for (s=0; s<MSC; s++)
    {
        particle[s].ruch();
    }
    
    plik.close();
    plik2.close();
    return 0;
}
