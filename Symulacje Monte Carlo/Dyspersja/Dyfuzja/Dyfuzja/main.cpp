//
//  main.cpp
//  Dyfuzja
//
//  Created by Mateusz on 26/03/2019.
//  Copyright © 2019 Mateusz Bulanda - Gorol. All rights reserved.
//

#include <iostream>  // for cout
#include <stdlib.h>  // for srand(), rand() and RAND_MAX
#include <math.h>  // for sqrt(), log() and sin()
#include <time.h>  // for time()
#include <fstream> // for fstream file
//niepotrzebna funkcja ale to rozk≥πd normalny dla c++ starszego niø 11
double normal(const double &mean, const double &std)
{
    static const double pii=3.1415927;
    static const double r_max=RAND_MAX+1;
    return std*sqrt(-2*log((rand()+1)/r_max))*sin(2*pii*rand()/r_max)+mean;
}

using namespace std;

int main()
{
    srand((unsigned) time(NULL));
    fstream plik;
    fstream plik2;
    
    plik.open("plik.txt", ios::out | ios::trunc);
    
    //interesuje nas tylko plik nr 2. tam wrzucana jest ilosc krokow i D
    plik2.open("srednie_przemieszczenia.txt", ios::out | ios::trunc);
    
    
    int a,b,c,e;
    a=b=c=e=0;
    
    double suma=0;
    
    //WAZNE
    int liczba=4; // liczba pkt, wybieramy liczbe punktow z przedzialu 1:399
    int rozmiar =20-1; // maksymalny indeks w tablicy (czyli jej rozmiar -1)
    int N=10; //liczba krokow
    
    
    
    
    int d; //zmienna do switcha
    int tab[liczba][5]; //punkty
    bool tab1[rozmiar+1][rozmiar+1]; //przestrzen
    double tab2[liczba]; //tablica ze srednimi przemieszczeniami po symulacji
    
    for(N=5;N<65;N+=5){ //Zapetlony caly program do sprawdzania d(N)
        for(int z=0;z<N;z++){
            
            suma=0;
            a=b=c=e=0;
            
            
            for(int i=0;i<rozmiar+1;i++){ //zerowanie tablicy boolowskiej
                
                for(int j=0;j<liczba;j++){
                    tab1[i][j]=0;
                }
                //cout<<i<<endl;
            }
            for(int i=0;i<liczba;i++){ //zerowanie tablicy pkt
                for(int j=0;j<5;j++){
                    tab[i][j]=0;
                }
                //cout<<i<<endl;
            }
            
            
            for(int i=0;i<liczba;i++){ //losowanie punktow w przestzeni
                int x=rand()%(rozmiar+1);
                int y=rand()%(rozmiar+1);
                //  cout<<x<<"   "<<y<<endl;
                if(tab1[x][y]==1){
                    // cout<<tab1[x][y]<<endl;
                    i--;
                }
                else{
                    tab[i][0]=x;
                    tab[i][1]=y;
                    tab1[x][y]=1;
                }
                
            }
            //cout<<"poczatek"<<endl;
            
            plik<<tab[0][0]<<" "<<tab[0][1]<<endl; //testowy zapis do pliku1
            
            //wedrowka punktow
            for(int i=0;i<N;i++){   // N powtorzen
                for(int j=0;j<liczba;j++){  // liczba  pkt (np20)
                    
                    d=rand()%4; //losowanie kierunku
                    
                    switch(d){
                            //-------------------------------
                            //pionowo
                        case 0:
                            a++;
                            if(tab[j][1]==rozmiar){
                                if(tab1[tab[j][0]][0]==0){
                                    tab1[tab[j][0]][0]=1;       // juz nie puste
                                    tab1[tab[j][0]][tab[j][1]]=0;
                                    tab[j][1]=0;
                                    
                                    tab[j][3]++;
                                }
                            }
                            
                            
                            else {
                                if(tab1[tab[j][0]][tab[j][1]+1]==0){ //pole wyzej jest puste
                                    tab1[tab[j][0]][tab[j][1]+1]=1;       // juz nie puste
                                    tab1[tab[j][0]][tab[j][1]]=0;         // poprzednie pole =0
                                    tab[j][1]++;                          //zwiekszenie wartosci wspolrzednej
                                    
                                    tab[j][3]++;
                                }
                            }
                            break;
                            
                            
                        case 2:
                            b++;
                            if(tab[j][1]==0){
                                if(tab1[tab[j][0]][rozmiar]==0){
                                    tab1[tab[j][0]][rozmiar]=1;       // juz nie puste
                                    tab1[tab[j][0]][tab[j][1]]=0;
                                    tab[j][1]=rozmiar;
                                    
                                    tab[j][3]--;
                                }
                            }
                            
                            else{
                                if(tab1[tab[j][0]][tab[j][1]-1]==0){ //pole wyzej jest puste
                                    tab1[tab[j][0]][tab[j][1]-1]=1;       // juz nie puste
                                    tab1[tab[j][0]][tab[j][1]]=0;        // poprzednie pole =0
                                    tab[j][1]--;                        //zmniejszenie wartosci wspolrzednej
                                    
                                    tab[j][3]--;
                                }}
                            break;
                            
                            
                            //------------------------------------------------
                            //poziomo
                            
                        case 1:
                            c++;
                            if(tab[j][0]==rozmiar){
                                if(tab1[0][tab[j][1]]==0)
                                    tab1[0][tab[j][1]]=1;       // juz nie puste
                                tab1[tab[j][0]][tab[j][1]]=0;
                                tab[j][0]=0;
                                
                                tab[j][4]++;
                            }
                            
                            else {
                                if(tab1[tab[j][0]+1][tab[j][1]]==0){ //pole wyzej jest puste
                                    tab1[tab[j][0]+1][tab[j][1]]=1;       // juz nie puste
                                    tab1[tab[j][0]][tab[j][1]]=0;
                                    tab[j][0]++;
                                    
                                    tab[j][4]++;
                                }}
                            break;
                            
                            
                        case 3:
                            e++;
                            if(tab[j][0]==0){
                                if(tab1[rozmiar][tab[j][1]]==0){
                                    tab1[rozmiar][tab[j][1]]=1;       // juz nie puste
                                    tab1[tab[j][0]][tab[j][1]]=0;
                                    tab[j][0]=rozmiar;
                                    
                                    tab[j][4]--;
                                }
                            }
                            
                            else{
                                if(tab1[tab[j][0]-1][tab[j][1]]==0){ //pole wyzej jest puste
                                    tab1[tab[j][0]-1][tab[j][1]]=1;       // juz nie puste
                                    tab1[tab[j][0]][tab[j][1]]=0;
                                    tab[j][0]--;
                                    
                                    tab[j][4]--;
                                }}
                            break;
                    } // switch bracket
                    
                } // loops brackets
                
                plik<<tab[0][0]<<" "<<tab[0][1]<<endl;
                
            }
            
            //srednia
            //cout<<a<<" "<<b<<" "<<c<<" "<<e<<" ";
            //obliczenie sredniej wedrowki punktow
            
            for(int j=0;j<liczba;j++){
                tab2[j]= (tab[j][4]*tab[j][4]+tab[j][3]*tab[j][3]);
                
                //cout<<j<<"  "<<tab2[j]<<endl;
                suma+=tab2[j];
                // cout<<tab2[j]<<endl;
            }
            //  cout<<"suma:"<<suma<<endl;
            plik2<<N<<"  "<<((double)suma/(double)liczba)/4.0/(double)N<<endl; // 4 = 2* liczba wymiarow. Zapisujemy tutaj liczbe krokow i D
        }
    }
    plik.close();
    plik2.close();
    return 0;
}

