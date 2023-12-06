#include<iostream>
#include<iomanip>
#include<fstream>
#include<cmath>
#include<string>
#include<filesystem>
#include<chrono>
#include<ctime>
#include "utilities.h"
#include "integration.h"

using namespace std;

typedef long long ll;
typedef long double ld;

//dubbi: semplificare il cambio di variabili già o lasciare nell'integrale costanti moltiplicative
//se ha senso usare sempre long double

ld f3(ld x){
    return powl(x,7)*powl(M_E,-x);
}

ld f3_legendre(ld x){
    return f3(5.*(x+1)/2.)*5./2.;
}

int main(int argc, char** argv){
    if(argc!=3)
        return 1;
    // cout << "TEST trapezoidal: \n" << int_trapezoidal(stoi(argv[1]),0,5,&f3) << endl;
    // cout << "TEST simpson: \n" << int_simpson(stoi(argv[1]),0,5,&f3) << endl;
    auto start = GET_TIME;
    cout << "TEST trapezoidal recursive: \n" << ric_trapezoidal(stoi(argv[1]),0,5,&f3) << endl;
    elapsed(start);
    
    start = GET_TIME;
    cout << "TEST simpson recursive: \n" << ric_simpson(stoi(argv[1]),0,5,&f3) << endl;
    elapsed(start);
    //RESULT: trapezoid (0.00085s) simpson (0,00056)
    
    start = GET_TIME;
    cout << "TEST romberg: \n" << romberg(stoi(argv[1]),stoi(argv[2]),0,5,&f3) << endl;
    //NB: se metto come parametri in input j=6 e k=0 equivale a calcolare come la regola del trapezio ripetuta, non a caso escono valori uguali per
    //ric_trapezoidal e romberg (672.3)
    //NB: se metto come parametri in input j=6 e k=1 equivale a calcolare come la regola di simpson, non a caso escono valori uguali per
    //ric_trapezoidal e romberg (672.193)
    //NB: le precedenti note funzionano per ogni j con k=0 e k=1
    elapsed(start);

    cout << "TEST romberg matrix: \n";
    start = GET_TIME;
    int j_max = stoi(argv[1]);
    int k_max = stoi(argv[2]);
    ld a = 0. ,b = 5.;

    vector<vector<ld>> romberg_mat = romberg_matrix(j_max,k_max,a,b,&f3);
    for(int j=0; j<j_max;j++){
        for(int k=0; k<k_max;k++){
            cout << "ret[" << j << "][" << k << "] = " << romberg_mat[j][k] << endl;
        }
    }
    elapsed(start);

    start = GET_TIME;
    cout << "TEST Legendre:" << endl;
    cout << legendre(8, &f3_legendre) << endl;

    elapsed(start);
    
    return 0;
}