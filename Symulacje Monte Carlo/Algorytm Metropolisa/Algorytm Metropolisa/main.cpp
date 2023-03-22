//
//  main.cpp
//  Model_Isinga
//
//  Created by Mateusz on 02/05/2019.
//  Copyright © 2019 Mateusz Bulanda - Gorol. All rights reserved.
//

#include <iostream>
#include <random>
#include <chrono>
#include <math.h>
#include <cstdlib>
#include <fstream>
#include <stdlib.h>

#define L 20

using namespace std;

int spin[L][L];

int spinS[L][L][4];



int energia(int i, int j);
void pokaz();
double namagnesowanie();
double sumaEnergii();


int main()

{
    fstream plik("namagnesowanie.txt", ios::out | ios::trunc);
    fstream plik2("podatnosc.txt", ios::out | ios::trunc);
    fstream plik3("energia.txt", ios::out | ios::trunc);
    fstream plik4("pojemnosc.txt", ios::out | ios::trunc);
    fstream plik5("t.txt", ios::out | ios::trunc);
    fstream plik6("kulminat.txt", ios::out | ios::trunc);
    fstream plik7("tempR.txt", ios::out | ios::trunc);
    
    
    
    
    double Tz = 1.5;
    //while(Tz<3.5)
    //{
        
        double Srednie_Namagnesowanie_Suma = 0;
        double Kwadrat_Namagnesowanie_Suma = 0;
        double Energia_Suma = 0;
        double Kwadrat_Energia_Suma = 0;
        double Do_Czwartej_Namagnesowanie_Kulminat_Suma = 0;
        double Kwadrat_Namagnesownie_Kulmiant_Suma = 0;
        
        double exp4 = exp(-4 / Tz);
        double exp8 = exp(-8 / Tz);
        
        
        
        mt19937 generator(chrono::high_resolution_clock::now().time_since_epoch().count());
        
        std::uniform_real_distribution<double> distribution(0.0, 1.0);
        
        //inicializacja
        
        for (int i = 0; i < L; i++)
        {
            
            for (int j = 0; j < L; j++) {
                
                int xl = i - 1;
                
                int xp = i + 1;
                
                int yl = j - 1;
                
                int yp = j + 1;
                
                if (xl < 0)
                    
                {
                    
                    xl = L + xl;
                    
                }
                
                if (xp < 0)
                    
                {
                    
                    xp = L + xp;
                    
                }
                
                if (yl < 0)
                    
                {
                    
                    yl = L + yl;
                    
                }
                
                if (yp < 0)
                    
                {
                    
                    yp = L + yp;
                    
                }
                
                
                
                
                int s = 1;
                if (distribution(generator) > 0.5)
                {
                    s = -1;
                    
                }
                spin[i][j] = s;
                
                spinS[i][j][0] = xl % L;
                
                spinS[i][j][1] = xp % L;
                
                spinS[i][j][2] = yl % L;
                
                spinS[i][j][3] = yp % L;
                
            }
            
            
            
        }
        
        int mcs = 0;
        int limit = 3000000;
        int kontrola = 100000;
        while (mcs < 3000000)
        {
            
            mcs++;
            for (int i = 0; i < L; i++)
                
            {
                
                for (int j = 0; j < L; j++) {
                    
                    int deltaE = energia(i, j);
                    
                    if (deltaE <= 0) {
                        
                        spin[i][j] *= (-1);
                        //cout<<"konfiguracja zmieniona"<<endl;
                        //showConfigurations();
                        
                        
                    }
                    else {
                        
                        
                        
                        double w;
                        
                        if (deltaE == 4) {
                            w = exp4;
                        }
                        else {
                            w = exp8;
                        }
                        
                        //cout<<w<<endl;
                        
                        float rand = distribution(generator);
                        
                        
                        
                        if (w > rand) {
                            
                            spin[i][j] *= (-1);
                            //cout<<spins[i][j]<<endl;
                            //cout<<"konfiguracja zmieniona"<<endl;
                            //showConfigurations();
                            
                        }
                        
                    }
                }
            }
            
            
            
            if (mcs % kontrola == 0)
            {
                
                //SrednieNamagnesowanie
                double Namagnesowanie = namagnesowanie();
                if (Namagnesowanie >= 0) {
                    Srednie_Namagnesowanie_Suma += Namagnesowanie;
                }
                else
                {
                    Srednie_Namagnesowanie_Suma += -Namagnesowanie;
                }
                Kwadrat_Namagnesowanie_Suma += (Namagnesowanie * Namagnesowanie);
                
                //Energia
                double Energia = sumaEnergii();
                Energia_Suma += Energia;
                Kwadrat_Energia_Suma += (Energia * Energia);
                
                //Namagnesowanie M
                double NamagnesowanieKumlinaty = namagnesowanie() * L * L;
                
                Kwadrat_Namagnesownie_Kulmiant_Suma += (NamagnesowanieKumlinaty * NamagnesowanieKumlinaty);
                Do_Czwartej_Namagnesowanie_Kulminat_Suma += NamagnesowanieKumlinaty * NamagnesowanieKumlinaty * NamagnesowanieKumlinaty * NamagnesowanieKumlinaty;
                
                
                
                
                
                /*system("clear");
                 cout<<"MCS"<<endl;
                 cout<<mcs<<endl;
                 cout<<"namagnesowanie"<<endl;*/
                //plik<<namagnesowanie()<<endl;
                /*cout<<"konfiguracja kontrolna"<<endl;
                 showConfigurations();*/
                /*float namag = namagnesowanie();
                 if (namag >= 0) {
                 sumaM += namag;
                 }
                 else {
                 sumaM += -namag;
                 }
                 sumaM2 += namag;
                 sumakwadratowM += namag * namag;
                 sumaquadM += sumakwadratowM * sumakwadratowM;
                 
                 double energia = sumaEnergii();
                 
                 sumaE += energia;
                 sumakwadratowE += energia * energia;
                 */
                
                pokaz();
                
            }
            
            
            
        }
        double liczba = limit / kontrola;
        
        double var_m = 0;
        double Kwadrat_Sredniej_m = (Srednie_Namagnesowanie_Suma / liczba) * (Srednie_Namagnesowanie_Suma / liczba);
        double Srednia_Kwadratow_m = Kwadrat_Namagnesowanie_Suma / liczba;
        
        if (Srednia_Kwadratow_m>Kwadrat_Sredniej_m) {
            var_m = Srednia_Kwadratow_m - Kwadrat_Sredniej_m;
        }
        else {
            var_m = -Srednia_Kwadratow_m + Kwadrat_Sredniej_m;
        }
        
        double var_E = 0;
        double Kwadrat_Sredniej_E = (Energia_Suma / liczba) * (Energia_Suma/ liczba);
        double Srednia_Kwadratow_E = Kwadrat_Energia_Suma / liczba;
        
        if (Srednia_Kwadratow_E > Kwadrat_Sredniej_E) {
            var_E = Srednia_Kwadratow_E - Kwadrat_Sredniej_E;
        }
        else {
            var_E = Srednia_Kwadratow_E - Kwadrat_Sredniej_E;
        }
        
        
        
        double Srednie_m = Srednie_Namagnesowanie_Suma / liczba;
        double Podatnosc_Magnetyczna = L * L * var_m/Tz;
        double SredniaEnergia = Energia_Suma / liczba;
        double Pojemnosc_Cieplna = var_E / L / L/Tz/Tz;
        double t = 1 - (Tz / 2.269);
        double Kulminat = 1 - ((Do_Czwartej_Namagnesowanie_Kulminat_Suma / liczba) / 3 / (Kwadrat_Namagnesownie_Kulmiant_Suma / liczba) / (Kwadrat_Namagnesownie_Kulmiant_Suma / liczba));
        
        
        plik << Srednie_m << endl;
        plik2 << Podatnosc_Magnetyczna << endl;
        plik3 << SredniaEnergia << endl;
        plik4 << Pojemnosc_Cieplna << endl;
        plik5 << t << endl;
        plik6 << Kulminat << endl;
        plik7 << Tz << endl;
        
        
        
        //srednia = sumaM / liczba;
        //cout <<"<m>: " <<srednia << endl;
        //
        //
        //double warM = 0;
        //double sredniasumaM = (sumaM2 / liczba)* (sumaM2 / liczba);
        //double sredniasumakwadratowM = sumakwadratowM / liczba;
        ////varM=<sumaKwadratowM> - <sumaM2>^2
        //if (sredniasumakwadratowM > sredniasumaM) {
        //    warM = sredniasumakwadratowM - sredniasumaM;
        //}
        //else {
        //    warM = -(sredniasumakwadratowM - sredniasumaM);
        //}
        //cout << "Podatnosc: " << L * L* warM/tempR << endl;
        
        //cout << sumaE / liczba << endl;
        //double warE = 0;
        //double sredniasumaE = (sumaE / liczba)* (sumaE / liczba);
        //double sredniasumakwadratowE = sumakwadratowE / liczba;
        //if (sredniasumakwadratowE > sredniasumaE) {
        //    warE = sredniasumakwadratowE - sredniasumaE;
        //}
        //else {
        //    warE = -(sredniasumakwadratowE - sredniasumaE);
        //}
        //cout << "Pojemnosc: " << warE / tempR/tempR /L/L<< endl;
        //double kumlnat = 1 - ((sumaquadM / 500.0) / 3.0 / sredniasumakwadratowM / sredniasumakwadratowM);
        //
        //
        //plik << srednia << endl;
        //plik2 << L*L* warM << endl;
        //plik3 << sumaE / 500.0 << endl;
        //plik4    << warE / tempR / tempR / L / L << endl;
        //plik5 << tempR << endl;
        //plik6 << kumlnat << endl;
        
        
        
        
        
        
        
        
        if (Tz > 1.9 && Tz < 2.6) {
            Tz += 0.02;
        }
        else
        {
            Tz += 0.1;
        }
        
        
        
        
        
        
        
    //}
    plik.close();
    plik2.close();
    plik3.close();
    plik4.close();
    plik5.close();
    plik6.close();
    plik7.close();
    
    
    
    
    
    return 0;
    
}

void pokaz() {
    
    for (int i = 0; i < L; i++)
    {
        
        for (int j = 0; j < L; j++) {
            if (spin[i][j] == 1) {
                cout << "█" << " ";
            }
            else {
                cout << " " << " ";
            }
            
        }
        cout << endl;
    }
    
}
double namagnesowanie() {
    
    float suma = 0;
    
    for (int i = 0; i < L; i++)
    {
        
        for (int j = 0; j < L; j++) {
            
            suma += spin[i][j];
        }
        
    }
    
    //cout<< suma/L/L<<endl;
    return suma / L / L;
    
}

int energia(int i, int j) {
    
    
    int topN = spinS[i][j][2];
    int bottomN = spinS[i][j][3];
    int leftN = spinS[i][j][0];
    int rightN = spinS[i][j][1];
    int energy = 2 * (spin[i][j]) * (spin[leftN][j] + spin[rightN][j] + spin[i][topN] + spin[i][bottomN]);
    
    
    return energy;
}

double sumaEnergii() {
    double sum = 0;
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < L; j++) {
            sum += -energia(i, j) / 2.0;
        }
    }
    return sum;
}
