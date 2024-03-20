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
    
    const int REQUIRED = 3;//argomenti richiesti da linea di comando
    if(argc!=REQUIRED){
        cout<< "wrong arguments" << endl;
        return 1;
    }
    
    int N = stoi(argv[1]);
    ld den = stold(argv[2]);

    ld a=LIM_INF, b=LIM_SUP;
    //dichiarazione vettori in cui salvare dati rilevanti da poi stampare nei file e usare nei plot
    vector<ld> trap, simpson, romb3, romb4, legend, laguer, hermit;
    vector<ld> ascisse, ascisse_legendre, ascisse_laguerre, ascisse_hermite;
        
    for(int j = 3; j<=N; j++){
        int i = pow(2,j)+1;
        ascisse.push_back(j);
        simpson.push_back(REAL_VAL-(open_h5(a,(b-a)/den,&f6)+int_simpson(i,a+(b-a)/den,b,&f6)));
        trap.push_back(REAL_VAL-(open_h5(a,(b-a)/den,&f6)+int_trapezoidal(i,a+(b-a)/den,b,&f6)));
        romb3.push_back(REAL_VAL-(open_h5(a,(b-a)/den,&f6)+romberg(j,3,a+(b-a)/den,b,&f6)));
        romb4.push_back(REAL_VAL-(open_h5(a,(b-a)/den,&f6)+romberg(j,4,a+(b-a)/den,b,&f6)));
    }

    printInFile<ld,ld>("romberg3.dat",ascisse,romb3,15);
    printInFile<ld,ld>("romberg4.dat",ascisse,romb4,15);
    printInFile<ld,ld>("trapezio.dat",ascisse,trap,15);
    printInFile<ld,ld>("simpson.dat",ascisse,simpson,15);
    
    for(int i = 2; i<=8; i*=2){
        laguer.push_back(REAL_VAL-laguerre(i,&f6_laguerre));
        ascisse_laguerre.push_back(i);
    }

    ascisse_hermite = {2,4,8,100};
    for(int i = 0; i<ascisse_hermite.size();i++){
        hermit.push_back(fabsl(REAL_VAL-hermite(ascisse_hermite.at(i),&f6_hermite)));
    }

    printInFile<ld,ld>("laguerre.dat",ascisse_laguerre,laguer,15);
    printInFile<ld,ld>("hermite.dat",ascisse_hermite,hermit,15);

    return 0;
}