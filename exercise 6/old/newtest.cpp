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

ld f3(ld x){
    return powl(x,7)*expl(-x);
}

ld f3_laguerre(ld x){
    return powl(x,7)-powl((x+5),7)*expl(-5);
}

int main(){
    cout << laguerre(8,&f3_laguerre) << endl;
    return 0;
}