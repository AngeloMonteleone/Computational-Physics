#include<iostream>
#include<iomanip>
#include<fstream>
#include<cmath>
#include<string>
#include<filesystem>
#include<chrono>
#include<ctime>
#include<vector>
#include "integration.h"
#include "utilities.h"

#define REAL_VAL (ld)(5040.-(648240./expl(5)))
using namespace std;

typedef long long ll;
typedef long double ld;

//funzione integranda
ld f3(ld x){
    return powl(x,7)*expl(-x);
}

//funzione da utilizzare con i polinomi di Legendre
ld f3_legendre(ld x){
    return f3(5.*(x+1)/2.)*5./2.;
}

//funzione da utilizzare con i polinomi di Laguerre
ld f3_laguerre(ld x){
    return powl(x,7)-powl((x+5),7)*expl(-5);
}

int main(int argc, char** argv){
    //per comodità il programma viene utilizzato inserendo da riga di comando 3 parametri:
    //  N: numero di punti da utilizzare nelle formule generalizzate del metodo del trapezio e di Simpson
    //  J,K: valori massimi a cui valutare la formula ricorsiva del metodo di Romberg. Si produce, con opportuna funzione nella libreria "integration.h"
    //      una matrice a J righe e K colonne contenente i valori della discrepanza tra valore calcolato e valor vero dell'integrale 
    //      per ogni j e k minori di questi valori massimi

    const int REQUIRED = 4;//argomenti richiesti da linea di comando
    if(argc!=REQUIRED){
        cout<< "wrong arguments" << endl;
        return 1;
    }
    
    int N = stoi(argv[1]);
    int J = stoi(argv[2]);
    int K = stoi(argv[3]);

    // cout << "J: " << J << ", K: " << K << endl; 

    ld a=0, b=5;
    //dichiarazione vettori in cui salvare dati rilevanti da poi stampare nei file e usare nei plot
    vector<ld> trap, simpson, legend, laguer;
    vector<ld> ascisse_trap, ascisse_simpson, ascisse_legendre, ascisse_laguerre;
    vector<ld> times_trap, times_simpson;

    //variabile in cui salvare il tempo corrente. Viene assegnato nuovamente il valore prima di effettuare una routine di calcolo per poter
    //calcolare il tempo trascorso in secondi tramite la funzione "runtime", contenuta nella libreria "utilities.h"
    auto start = GET_TIME;
    
    for(int i = 2; i<=N; i++){
        //il metodo di Simpson viene applicato solo quando il numero dei punti è dispari
        if((i%2)!=0){
            start = GET_TIME;
            simpson.push_back(fabsl(REAL_VAL-int_simpson(i,a,b,&f3))); 
            times_simpson.push_back(runtime(start));
            
            ascisse_simpson.push_back(1./i);
        }

        start = GET_TIME;
        trap.push_back(fabsl(REAL_VAL-int_trapezoidal(i,a,b,&f3))); 
        times_trap.push_back(runtime(start));
        
        ascisse_trap.push_back(1./i);
    }

    vector<vector<ld>> matrix = romberg_matrix(J,K,a,b,&f3, REAL_VAL);

    printInFile<ld>("romberg.dat",matrix,8);
    printInFile<ld,ld,ld>("trapezio.dat",ascisse_trap,trap, times_trap,16);
    printInFile<ld,ld,ld>("simpson.dat",ascisse_simpson,simpson, times_simpson,16);
    
    for(int i = 2; i<=8; i*=2){
        legend.push_back(fabsl(REAL_VAL-legendre(i,&f3_legendre)));
        laguer.push_back(fabsl(REAL_VAL-laguerre(i,&f3_laguerre)));
        ascisse_legendre.push_back(i);
        ascisse_laguerre.push_back(i);
    }

    printInFile<ld,ld>("legendre.dat",ascisse_legendre,legend,16);
    printInFile<ld,ld>("laguerre.dat",ascisse_laguerre,laguer,16);

    return 0;
}