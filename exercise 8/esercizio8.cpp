#define _USE_MATH_DEFINES
#include<iostream>
#include<iomanip>
#include<fstream>
#include<cmath>
#include<ranges>
#include<iterator>
#include<string>
#include<filesystem>
#include<utility>
#include"sphereint.h"
#define REAL_VALUE(M) powl(M_PI,M/2.)/tgammal(M/2.+1)

using namespace std;

typedef long long ll;
typedef long double ld;

int main(int argc, char** argv){
    const int REQUIRED = 3;//numero di argomenti richiesti da linea di comando
    if(argc!=REQUIRED)
        return 1;

    int dim = stoi(argv[1]);//valore della dimensione
    int number_of_points = stoi(argv[2]);//numero di punti da utilizzare per Monte Carlo
    auto start = GET_TIME;
    //vettore per salvare il numero crescente di dimensioni
    vector<int> dims(dim-1);
    //vettori per salvare i valori e i tempi di calcolo dei due metodi
    vector<ld> values_det(dim-1),values_mc(dim-1),times_det(dim-1),times_mc(dim-1);
    //vettore con i valori esatti
    vector<ld> exact_values(dim-1);
    //vettori contenenti le deviazioni standard e i t-value nel calcolo tramite Monte Carlo
    vector<ld> dev(dim-1),t_values(dim-1);

    int current_dim;
    vector<ld> temp;
    for(int i=0; i<=(dim-2); i++){
        current_dim = i+2;
        dims.at(i)=current_dim;

        //INTEGRAZIONE DETERMINISTICA CON FORMULA MIDPOINT
        start = GET_TIME;
        values_det.at(i) = pow(2,current_dim)*integral_multidim<ld>(.1,current_dim,&M_sphere);
        times_det.at(i) = runtime(start);
        
        //INTEGRAZIONE MONTECARLO
        /*
        Per studiare l'andamento dei valori dell'integrazione stocastica si utilizza la funzione che calcola sia i valori che le deviazioni
        standard relative al calcolo effettuato. Questi dati sono prima salvati in un vettore temporaneo di due componenti e poi 
        vengono smistati nei vettori che contengono i valori o le deviazioni
        In alternativa, se si vuola calcolare solo il valore dell'integrale si può utilizzare la seguente linea di codice
        //values_mc.at(i) = pow(2,current_dim)*integral_Monte_Carlo<ld>(current_dim-1,number_of_points,&M_sphere_standard);
        */
        start = GET_TIME;
        temp = integral_Monte_Carlo_valdev<ld>(current_dim-1,number_of_points,&M_sphere_standard);
        values_mc.at(i) = pow(2,current_dim)*temp.at(0);//valore dell'integrale
        dev.at(i)= pow(2,current_dim)*temp.at(1);//deviazione
        
        times_mc.at(i) = runtime(start);//tempo di calcolo
        exact_values.at(i) = REAL_VALUE(current_dim);//valore vero dell'integrale

        t_values.at(i) = fabsl(exact_values.at(i)-values_mc.at(i))/dev.at(i);//t-value
    }

    //salvataggio dei dati
    printInFile<int,ld,ld,ld,ld,ld>("data.dat",dims,values_det,times_det,values_mc,times_mc,exact_values,13);
    printInFile<int,ld,ld>("devs.dat",dims,dev,t_values,13);
    return 0;
}