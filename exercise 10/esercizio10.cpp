//I dati sono stati prodotti dal comando
//./esercizio10.exe 10000 100

#include<iostream>
#include<cmath>
#include<iomanip>
#include<fstream>
#include<vector>
#include"utilities.h"
#include"stat.h"
#define REAL_VAL3 (ld)(5040.-(648240./expl(5)))
#define REAL_VAL4 (ld)(-(1 - expl(5.) + expl(11.) - expl(16.))/(2 * expl(8)))
#define REAL_VAL5 (ld)(2736.+sinl(4)+sinl(32)-4.*cosl(4)-32.*cosl(32))/16.

#define LINE_LIMIT 1000000

using namespace std;

typedef long double ld;

//funzione integranda esercizio 3
ld f3(ld x){
  return powl(x,7)*expl(-x);
}

//funzione integranda esercizio 4
ld f4(ld x){
  return .5*(expl(x)+expl(-x));
}

//funzione integranda esercizio 5
ld f5(ld x){
  return (powl(x,2)+x*sinl(4*x));
}

int main(int argc, char** argv){
  const int REQUIRED = 3;
  if(argc!= REQUIRED){
    cout << "wrong arguments" << endl;
    return 1;
  }
  
  int N = stoi(argv[1]);
  int step = stoi(argv[2]);
  int repeat = 100;

  //valori veri degli integrali
  ld val3 = REAL_VAL3;
  ld val4 = REAL_VAL4;
  ld val5 = REAL_VAL5;
  
  //vettori in cui salvare i dati
  vector<ld> data3hm, data4hm, data5hm;
  vector<ld> data3mc,data4mc,data5mc;
  vector<ld> ascisse;
  
  for(int n= step;n<=N;n+=step){
    cout << n << endl;
    ascisse.push_back(1./n);
    //calcolo con metodo hit or miss
    data3hm.push_back(hit_miss_repeat<ld>(n,0,5,0,f3(5),&f3,repeat,val3));
    data4hm.push_back(hit_miss_repeat<ld>(n,3,8,0,f4(8),&f4,repeat,val4));
    data5hm.push_back(hit_miss_repeat<ld>(n,-1,8,0,80,&f5,repeat,val5));

    //calcolo con metodo Monte Carlo
    data3mc.push_back(integral_Monte_Carlo_repeat<ld>(n,0,5,&f3,repeat,val3));
    data4mc.push_back(integral_Monte_Carlo_repeat<ld>(n,3,8,&f4,repeat,val4));
    data5mc.push_back(integral_Monte_Carlo_repeat<ld>(n,-1,8,&f5,repeat,val5));
  }

  //salvataggio dati
  printInFile<ld,ld>("int3hm.dat",ascisse,data3hm,15);
  printInFile<ld,ld>("int4hm.dat",ascisse,data4hm,15);
  printInFile<ld,ld>("int5hm.dat",ascisse,data5hm,15);
  printInFile<ld,ld>("int3mc.dat",ascisse,data3mc,15);
  printInFile<ld,ld>("int4mc.dat",ascisse,data4mc,15);
  printInFile<ld,ld>("int5mc.dat",ascisse,data5mc,15);
}
