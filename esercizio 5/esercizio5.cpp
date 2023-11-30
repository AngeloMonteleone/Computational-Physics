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

#define REAL_VAL (ld)(2736.+sinl(4)+sinl(32)-4.*cosl(4)-32.*cosl(32))/16.
using namespace std;

typedef long long ll;
typedef long double ld;

ld f5(ld x){
    return (powl(x,2)+x*sinl(4*x));
}

ld f5_legendre(ld x){
    return f5(4.5*x+3.5)*4.5;
}

int main(int argc, char** argv){
    //per comodità il programma viene utilizzato inserendo da riga di comando 3 parametri:
    //  N: numero di punti da utilizzare nelle formule generalizzate del metodo del trapezio e di Simpson
    //  J,K: valori massimi a cui valutare la formula ricorsiva del metodo di Romberg. Si produce, con opportuna funzione nella libreria "integration.h"
    //      una matrice a J righe e K colonne contenente i valori della discrepanza tra valore calcolato e valor vero dell'integrale 
    //      per ogni j e k minori di questi valori massimi
    if(argc!=4)
        return 1;
    
    int N = stoi(argv[1]);
    int J = stoi(argv[2]);
    int K = stoi(argv[3]);

    ld a=-1, b=8;
    //dichiarazione vettori in cui salvare dati rilevanti da poi stampare nei file e usare nei plot
    vector<ld> trap, simpson, legend;
    vector<ld> ascisse_trap, ascisse_simpson, ascisse_legendre;
    vector<ld> times_trap, times_simpson;

    //variabile in cui salvare il tempo corrente. Viene assegnato nuovamente il valore prima di effettuare una routine di calcolo per poter
    //calcolare il tempo trascorso in secondi tramite la funzione "runtime", contenuta nella libreria "utilities.h"
    auto start = GET_TIME;
    
    for(int i = 2; i<=N; i++){
        //il metodo di Simpson viene applicato solo quando il numero dei punti è dispari
        if((i%2)!=0){
            start = GET_TIME;
            simpson.push_back(fabsl(REAL_VAL-int_simpson(i,a,b,&f5))); 
            times_simpson.push_back(runtime(start));
            
            ascisse_simpson.push_back(1./i);
        }

        start = GET_TIME;
        trap.push_back(fabsl(REAL_VAL-int_trapezoidal(i,a,b,&f5))); 
        times_trap.push_back(runtime(start));
        
        ascisse_trap.push_back(1./i);
    }

    vector<vector<ld>> matrix = romberg_matrix(J,K,a,b,&f5, REAL_VAL);

    printInFile<ld>("romberg.dat",matrix,20);
    printInFile<ld,ld,ld>("trapezio.dat",ascisse_trap,trap, times_trap,20);
    printInFile<ld,ld,ld>("simpson.dat",ascisse_simpson,simpson, times_simpson,20);
    
    vector<int> points = {2,4,8,16,48};

    for(int i = 0; i<points.size(); i++){
        // start = GET_TIME;
        legend.push_back(fabsl(REAL_VAL-legendre(points[i],&f5_legendre)));
        // laguer.push_back(REAL_VAL-laguerre(i,&f3_laguerre));
        // times_legendre.push_back(runtime(start));
        ascisse_legendre.push_back(points[i]);
        // ascisse_laguerre.push_back(i);
    }

    printInFile<ld,ld>("legendre.dat",ascisse_legendre,legend,20);
    // printInFile<ld,ld>("laguerre.dat",ascisse_laguerre,laguer,20);

    return 0;
}