#include<iostream>
#include<vector>
#include<iomanip>
#include<cmath>
#include<algorithm>
#include "rootfinding.h"
#define MAX_ITER 100

using namespace std;
typedef long double ld;

ld pol2(ld x){
  return 2*x*x-3*x+1;
}

ld pol10(ld x){
  return (46189*powl(x,10) - 109395*powl(x,8) + 90090*powl(x,6) - 30030*powl(x,4) + 3465*powl(x,2) - 63)/256.;
}

ld der2(ld x){
  return 4*x-3;
}

ld der10(ld x){
  return (46189*10*powl(x,9) - 109395*8*powl(x,7) + 90090*6*powl(x,5) - 30030*4*powl(x,3) + 3465*2*x)/256.;
}

int main(int argc, char** argv){
  cout << "Si vogliono trovare gli intervalli contenenti zeri (1), oppure si vuole fornire l'intervallo in cui cercare (0)? ";
  int choice; cin>>choice;
  if(choice){
    vector<ld> lower_bounds, upper_bounds;

    ld left,right;
    cout << "Estremo inferiore: ";
    ld inf; cin >> inf;

    cout << "Estremo superiore: ";
    ld sup; cin >> sup;

    int n=2;
    multbrak(&pol2,&n,15,inf,sup,&lower_bounds,&upper_bounds);

    // int n=10;
    // multbrak(&pol10,&n,15,inf,sup,&lower_bounds,&upper_bounds);
    cout << setprecision(17) << endl;

    for(int i=0;i<n;i++){
      cout << "zero in (" << lower_bounds.at(i) << "," << upper_bounds.at(i) << ")\n";
    }

    ld zero;

    for(int i=0;i<n;i++){
      bisection(&pol2,lower_bounds.at(i),upper_bounds.at(i),10e-7,&zero);
      // bisection(&pol10,lower_bounds.at(i),upper_bounds.at(i),10e-7,&zero);
      cout << "zero: " << zero << endl;
    }
  }else{
    cout << "Estremo inferiore: ";
    ld inf; cin >> inf;

    cout << "Estremo superiore: ";
    ld sup; cin >> sup;

    ld zero;
    bisection(&pol2,inf,sup,10e-7,&zero);
    // bisection(&pol10,inf,sup,10e-7,&zero);
    cout << setprecision(17) << endl;
    cout << "Trovato zero in: " << zero << endl;
  }
  
  return 0;
}
