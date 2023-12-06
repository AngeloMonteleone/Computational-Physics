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

#define REAL_VAL (ld)(50.5/expl(9.))
#define LIM_INF 0
#define LIM_SUP expl(-9.)
using namespace std;

typedef long long ll;
typedef long double ld;

//funzione con il cambio di varibile
ld f6(ld x){
    return .5*powl(log(x),2);
}

//funzione senza il cambio di variabile
ld f6_original(ld x){
    return powl(x,5.)*expl(-powl(x,2));
}

ld f6_laguerre(ld x){
    return f6_original(x+3)*expl(x);
}

ld f6_hermite(ld x){
    x=fabsl(x);
    return powl(x+3,5.)*expl(-9.-6*x)*.5;
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

    ld a=LIM_INF, b=LIM_SUP;
    //dichiarazione vettori in cui salvare dati rilevanti da poi stampare nei file e usare nei plot
    vector<ld> trap, simpson, legend, laguer, hermit;
    vector<ld> ascisse_trap, ascisse_simpson, ascisse_legendre, ascisse_laguerre, ascisse_hermite;
    vector<ld> times_trap, times_simpson;

    //variabile in cui salvare il tempo corrente. Viene assegnato nuovamente il valore prima di effettuare una routine di calcolo per poter
    //calcolare il tempo trascorso in secondi tramite la funzione "runtime", contenuta nella libreria "utilities.h"
    auto start = GET_TIME;
    
    for(int i = 4; i<=N; i++){
        // il metodo di Simpson viene applicato solo quando il numero dei punti è dispari
        if((i%2)!=0){
            start = GET_TIME;
            simpson.push_back(fabs(REAL_VAL-int_simpson_semiopen(i,a,b,&f6,(b-a)/100.))); 
            times_simpson.push_back(runtime(start));
            
            ascisse_simpson.push_back(i+4);
        }

        start = GET_TIME;
        trap.push_back(REAL_VAL-int_trapezoidal_semiopen(i,a,b,&f6,(b-a)/100.)); 
        times_trap.push_back(runtime(start));
        
        ascisse_trap.push_back((i+1));
    }

    // vector<vector<ld>> matrix = romberg_matrix(J,K,a,b,&f3, REAL_VAL);

    // printInFile<ld>("romberg.dat",matrix,15);
    printInFile<ld,ld,ld>("trapezio.dat",ascisse_trap,trap, times_trap,15);
    printInFile<ld,ld,ld>("simpson.dat",ascisse_simpson,simpson, times_simpson,15);
    
    for(int i = 2; i<=8; i*=2){
        // start = GET_TIME;
        
        laguer.push_back(REAL_VAL-laguerre(i,&f6_laguerre));
        // times_legendre.push_back(runtime(start));
        
        ascisse_laguerre.push_back(i);
    }

    ascisse_hermite = {2,4,8,100};
    for(int i = 0; i<ascisse_hermite.size();i++){
        hermit.push_back(fabsl(REAL_VAL-hermite(ascisse_hermite.at(i),&f6_hermite)));
    }

    // printInFile<ld,ld>("legendre.dat",ascisse_legendre,legend,15);
    printInFile<ld,ld>("laguerre.dat",ascisse_laguerre,laguer,15);
    printInFile<ld,ld>("hermite.dat",ascisse_hermite,hermit,15);

    return 0;
}