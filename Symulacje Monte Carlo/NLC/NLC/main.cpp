//
//  main.cpp
//  NLC
//
//  Created by Mateusz on 07/05/2019.
//  Copyright © 2019 Mateusz Bulanda - Gorol. All rights reserved.
//

#include <iostream>
#include <random>
#include <iostream>
#include <random>
#include <chrono>
#include <math.h>
#include <cstdlib>
#include <fstream>
#include <stdlib.h>

#define L 20
#define dPhi 10

using namespace std;

int Spin[L][L];

fstream plikK("konfiguracje.txt", ios::out | ios::trunc);
fstream plikp2("p2.txt", ios::out | ios::trunc);

double tabP[361];
double tabQxx[181];
double tabQxy[181];

int SpinN[L][L][4];
int k = 0;

double dEnergy(int i, int j,int newPhi)
{
    int gornyN = SpinN[i][j][2];
    int dolnyN = SpinN[i][j][3];
    int lewyN = SpinN[i][j][0];
    int prawyN = SpinN[i][j][1];
    
    int dphiTop=-newPhi+Spin[i][gornyN];
    int dphiBottom=-newPhi+Spin[i][dolnyN];
    int dphiLeft=-newPhi+Spin[lewyN][j];
    int dphiRight=-newPhi+Spin[prawyN][j];
    
    double UK=-(tabP[180+dphiTop]+tabP[180+dphiBottom]+tabP[180+dphiLeft]+tabP[180+dphiRight]);
    
    double U0=-(tabP[-Spin[i][j]+Spin[i][gornyN]+180]+tabP[-Spin[i][j]+Spin[i][dolnyN]+180]+tabP[-Spin[i][j]+Spin[lewyN][j]+180]+tabP[-Spin[i][j]+Spin[prawyN][j]+180]);
    return UK-U0;
}

double qxx()
{
    double sum=0;
    for (int i=0; i<L; i++)
    {
        for (int j=0; j<L; j++)
        {
            sum+= tabQxx[Spin[i][j]+90];
        }
    }
    return sum/L/L;
}

double qxy()
{
    double sum=0;
    for (int i=0; i<L; i++)
    {
        for (int j=0; j<L; j++)
        {
            sum +=tabQxy[Spin[i][j]+90];
        }
    }
    return sum/L/L;
}

double p2()
{
    double sum=0;
    for (int i=0; i<L; i++)
    {
        for (int j=0; j<L; j++)
        {
            sum +=tabP[Spin[i][j]+180];
        }
    }
    return sum/L/L;
}

void pokaz()
{
    //system("cls");
    for (int i=0; i<L; i++)
    {
        for (int j=0; j<L; j++)
        {
            plikK.width(4);
            plikK<<Spin[i][j]<<" ";
            //system("cls");
            //cout << k++ << endl;
            //plikp2 << PTable[spins[i][j] + 180] << " ";
        }
        plikK<<endl;
        //plikp2 << endl;
    }
    
}
void inicializacja(int start)
{
    for (int i=-180; i<181; i++)
    {
        tabP[i+180]=(1.5*cos(i*M_PI/180.0)*cos(i*M_PI/180.0))-0.5;
        //cout<<PTable[i+180]<<endl;
    }
    for (int i=-90; i<91; i++)
    {
        tabQxx[i+90]=(2*cos(i*M_PI/180.0)*cos(i*M_PI/180.0))-1.0;
        tabQxy[i+90]=2*cos(i*M_PI/180.0)*sin(i*M_PI/180.0);
    }
    
    for (int i=0; i<L; i++)
    {
        for (int j=0; j<L; j++)
        {
            int xl =i-1, xp=i+1, yl=j-1, yp=j+1;
            if (xl<0)
            {
                xl=L+xl;
            }
            if (xp<0)
            {
                xp=L+xp;
            }
            if (yl<0)
            {
                yl=L+yl;
            }
            if (yp<0)
            {
                yp=L+yp;
            }
            mt19937 generator(chrono::high_resolution_clock::now().time_since_epoch().count());
            std::uniform_int_distribution<int> distribution(-90, 90);
            
            Spin[i][j]=distribution(generator);
            SpinN[i][j][0]=xl%L;
            SpinN[i][j][1]=xp%L;
            SpinN[i][j][2]=yl%L;
            SpinN[i][j][3]=yp%L;
        }
    }
}

double tempR =0.01;
int stop=0;

int main()
{
    int wyk=0;
    
    double n=0;
    double a=0.01;
    while (a<1.4) {
        
        a +=0.01;
        
        n++;
    }
    
    while (tempR<1.4)
    {
        cout<<wyk/n*100<<" %"<<endl;

        mt19937 generator(chrono::high_resolution_clock::now().time_since_epoch().count());
        std::uniform_real_distribution<double> distribution(0.0, 1.0);
        inicializacja(45);
        
        double Qaa=0;
        double Qab=0;
        double P2sum=0;
        double Ssum=0;
        int LIMIT=100000;
        int mcs=0;
        int CheckPeroid=1000;
        double ChecksNumber=0;
        
        while (mcs<LIMIT)
        {
            for (int i=0; i<L; i++)
            {
                for (int j=0; j<L; j++)
                {
                    int N_PI=Spin[i][j]+nearbyint((distribution(generator)-0.5)*dPhi);
                    if (N_PI>90)
                    {
                        N_PI=N_PI-180;
                    }
                    else if (N_PI<-90)
                    {
                        N_PI=N_PI+180;
                    }
                    double DeltaEnergii=dEnergy(i, j, N_PI);
                    
                    if (DeltaEnergii<0)
                    {
                        Spin[i][j]=N_PI;
                    }
                    else
                    {
                        double w=exp(-DeltaEnergii/tempR);
                        if (distribution(generator)<=w)
                        {
                            Spin[i][j]=N_PI;
                        }
                    }
                }
            }
            if (true)
            {
                //pokaz();
                /*Qaa +=qxx();
                 Qab +=qxy();*/
                Ssum +=sqrt(pow((qxx()), 2)+pow((qxy()), 2));
                //P2sum+=P2();
                ChecksNumber++;
            }
            mcs++;
        }
        fstream plik("orderparmeter.txt", ios::out | ios::trunc);
        fstream plikR("tempr.txt", ios::out | ios::trunc);
        plik<<Ssum/ChecksNumber<<endl;
        plikR<<tempR<<endl;
        tempR+=0.01;
        wyk++;
    }
}
