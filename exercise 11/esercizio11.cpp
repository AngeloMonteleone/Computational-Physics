//I dati sono stati prodotti dal comando
//./esercizio11.exe 10000

#include<iostream>
#include<cmath>
#include<vector>
#include<fstream>
#include<iomanip>
#include "stat.h"
#include"utilities.h"
#define LINE_LIMIT 1000000

using namespace std;
typedef long double ld;

//inversa della prima CDF
ld cdf1(ld y){
  const ld A = powl(M_E,2)/(1-powl(M_E,2));
  return log(A/(y+A));
}

//inversa della seconda CDF
ld cdf2(ld y){
  return 1-log(1-y);
}

//inversa della terza CDF
ld cdf3(ld y){
return sqrtl(log(1/(1-y)));
}

int main(int argc, char** argv){
  const int REQUIRED = 2;//argomenti richiesti da linea di comando
  if(argc!=REQUIRED){
    cout<< "wrong arguments" << endl;
    return 1;
  }
  
  int N = stoi(argv[1]);//numero di punti da generare

  vector<ld> data1,data2,data3;//vettori in cui salvare i dati
  ld y_i;//variabile di supporto utilizzata per generare un numero con distribuzione uniforme tra 0 e 1
  for(int i=0;i<N;i++){
    y_i = uniform(0,1);
    data1.push_back(cdf1(y_i));
    y_i = uniform(0,1);
    data2.push_back(cdf2(y_i));
    y_i = uniform(0,1);
    data3.push_back(cdf3(y_i));
  }

  printInFile<ld>("cdf1.dat",data1,17);
  printInFile<ld>("cdf2.dat",data2,17);
  printInFile<ld>("cdf3.dat",data3,17);
  return 0;
}
