//
//  main.cpp
//  ModelIsinga
//
//  Created by Mateusz on 06/05/2019.
//  Copyright © 2019 Mateusz Bulanda - Gorol. All rights reserved.
//

#include <iostream>
#include <random>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <math.h>
#include <fstream>

using namespace std;

double const Kb=1.38*(pow(10,(-23))); //Boltzman's Constant
int const MCS=320000; //number of MonteCarlo steps
double const Tc=2.269; //Curie temperature
double T=1.5;   //temperature
int const L=100; //size of the model 10   40   100!!!!!!!!
char field[L][L]; //graphical representation of the model
float N=0.0001; //1/(L^2)!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
int calcfield[L][L]; //spin value representation of the model
double dU; //Energy delta, energy (reduced - without J, which is irrelevant for our case)
double m, Sum, s, magnetisationSum=0., C, energySum=0.; //calc variables - magnetisation, sum of spin values, magnetic sensibility and thermal capacity
int x=0, y=0, i=0, j=0; //loop variables
double magnetisationArray[54700];
void energy();
void magnetisation();
void magneticSensibility();
void thermalCapacity();
void metropolis();
void begin();
void visualize();
void deltaU();
void confprim();

int main()
{
    ofstream dataMagnetisation,/*dataMagneticSensibility, dataThermalCapacity,*/ dataEnergy;
    dataMagnetisation.open("Magnetisation.txt");
    //dataMagneticSensibility.open("Magnetic Sensibility.txt");
    //dataThermalCapacity.open("Thermal Capacity.txt");
    dataEnergy.open("Energy.txt");
    
    srand(time(NULL));
    begin();
    
    for(T; T<=3.5; T+=0.05){
        magnetisationSum=0.;
        
        for(int k=0; k<MCS; k++){
            for (j=0; j<L; j++){
                for (i=0; i<L; i++)
                {
                    metropolis();
                    energySum=energySum+calcfield[i][j];
                }
            }
            
            if(k%1000==0 && k<30000){
                magnetisation();
                dataMagnetisation << m << "\t";
                
                dataEnergy << energySum << "\t";
                
                visualize();
            }
            energySum=0.;
        }
        
        
        //magneticSensibility();
        //dataMagneticSensibility << s << endl;
        
        //thermalCapacity();
        //dataThermalCapacity << C << endl;
        
        dataMagnetisation << endl;
        dataEnergy << endl;
    }
    
    dataMagnetisation.close();
    //dataMagneticSensibility.close();
    //dataThermalCapacity.close();
    dataEnergy.close();
}

void energy()
{
    energySum=energySum+calcfield[i][j]*(calcfield[((i+1)%L)][j]+calcfield[((i-1)%L)][j]+calcfield[i][((j+1)%L)]+calcfield[i][((j-1)%L)]);
    
}
void deltaU()
{
    dU = 2*calcfield[i][j]*(calcfield[((i+1)%L)][j]+calcfield[((i-1)%L)][j]+calcfield[i][((j+1)%L)]+calcfield[i][((j-1)%L)]);
}

void configurationprim()
{
    if (field[i][j]=='1')
    {
        field[i][j]=' ';
        calcfield[i][j]=-1;
    }
    else
    {
        field[i][j]='1';
        calcfield[i][j]=1;
    }
}

void metropolis()
{
    double R;
    R=(((double)rand())/ (RAND_MAX));
    double w;
    deltaU();
    w= exp(-dU/(T));
    if (dU<0)
        configurationprim();
    else if (w>=R)
        configurationprim();
}

void magnetisation()
{
    Sum = 0.;
    for(i=0; i<L; i++)
    {
        for(j=0; j<L; j++)
        {
            Sum=Sum+calcfield[i][j];
        }
    }
    m=N*Sum;
    magnetisationSum=magnetisationSum+m;
}

void magneticSensibility()
{
    s= N/(Kb *T) * ((((magnetisationSum*L*L)*(magnetisationSum*L*L))/MCS)-((magnetisationSum*L*L/MCS)*(magnetisationSum*L*L/MCS)));
    
}

void thermalCapacity()
{
    C=N/(Kb*T*T)*(((energySum*L*L)*(energySum*L*L))/MCS)-((energySum*L*L/MCS)*(energySum*L*L/MCS));
}

void visualize()
{
    for (y=0; y<L; y++)
    {
        for (x=0; x<L; x++)
        {
            cout << field[x][y] <<' ';
        }
        cout << endl;
    }
    system("clear");
}

void begin()
{
    for (x=0; x<L; x++)
    {
        for (y=0; y<L; y++)
        {
            int z = rand() %2;
            if(z==1){
                field[x][y]=' ';
                calcfield[x][y] = -1;
            }
            else {
                field[x][y]='1';
                calcfield[x][y]=1;
            }
        }
    }
    
}

    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    





