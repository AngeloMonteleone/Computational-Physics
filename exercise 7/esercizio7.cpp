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

#define REAL_VAL (ld)(135135.*sqrtl(M_PI)/256.)
using namespace std;

typedef long long ll;
typedef long double ld;

ld f7(ld x){
    return powl(x,14)*expl(-x*x);
}

ld f7_laguerre(ld x){
    return f7(x)*expl(x);
}

ld f7_hermite(ld x){
    return powl(x,14)*.5;
}

int main(int argc, char** argv){
    //dichiarazione vettori in cui salvare dati rilevanti da poi stampare nei file e usare nei plot
    vector<ld> laguer, hermit;
    vector<ld> ascisse_laguerre, ascisse_hermite;
    
    vector<int> data = {2,4,8,24,64};
    for(auto points : data){
        laguer.push_back(fabsl(REAL_VAL-laguerre(points,&f7_laguerre)));
        ascisse_laguerre.push_back(points);
    }

    data = {2,4,8};
    for(auto points : data){
        hermit.push_back(fabsl(REAL_VAL-hermite(points,&f7_hermite)));
        ascisse_hermite.push_back(points);
    }

    printInFile<ld,ld>("hermite.dat",ascisse_hermite,hermit,20);
    printInFile<ld,ld>("laguerre.dat",ascisse_laguerre,laguer,20);

    return 0;
}