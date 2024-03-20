//i dati sono stati prodotti dal comando
//./esercizio13.exe 1000 10 25

//la sigla "is" sta per importance sampling, mentre "mc" per Monte Carlo

#include<iostream>
#include<vector>
#include<cmath>
#include<iomanip>
#include<fstream>
#include"stat.h"
#include"utilities.h"

typedef long double ld;

using namespace std;

//prima integranda
ld f1(ld x){
  return x*cos(x);
}

//seconda integranda
ld f2(ld x){
  return x*sin(x);
}

//prima integranda dopo il cambio di variabile
ld fg_1(ld z){
  return asin(z);
}

//seconda integranda dopo il cambio di variabile
ld fg_2(ld z){
  return 2*acos(1-2*z);
}

int main(int argc, char** argv){
  const int REQUIRED = 4;//numero argomenti richiesti da linea di comando
  if(argc!=REQUIRED){
    cout << "wrong arguments" << endl;
    return 1;
  }
  
  
  int N = stoi(argv[1]);//numero massimo di punti a cui arrivare nella generazione di numeri tra 0 e 1 per l'importance sampling
  int step = stoi(argv[2]);//incremento del numero di punti utilizzato per calcolare un integrale 
  int repeat = stoi(argv[3]);//numero di volte su cui viene mediato il valore di ogni integrale

  ld real1 = .5*(M_PI-2), real2 = M_PI;//valori veri dei due integrali
  vector<ld> is1,is2;//vettori per salvare i dati dell'importance sampling
  vector<ld> mc1,mc2;//vettori per salvare i dati di Monte Carlo
  vector<int> ascisse;

  for(int j=step;j<N;j+=step){
    //APPLICAZIONE DI MONTE CARLO SEMPLICE
    mc1.push_back(integral_Monte_Carlo_repeat<ld>(j,0,M_PI/2,&f1,repeat,real1));
    mc2.push_back(integral_Monte_Carlo_repeat<ld>(j,0,M_PI,&f2,repeat,real2));

    //APPLICAZIONE DI IMPORTANCE SAMPLING
    is1.push_back(integral_Monte_Carlo_repeat<ld>(j,0,1,&fg_1,repeat,real1));
    is2.push_back(integral_Monte_Carlo_repeat<ld>(j,0,1,&fg_2,repeat,real2));
    ascisse.push_back(j);
  }

  //salvataggio dati
  printInFile<int,ld>("is1.dat",ascisse,is1,15);
  printInFile<int,ld>("is2.dat",ascisse,is2,15);
  printInFile<int,ld>("mc1.dat",ascisse,mc1,15);
  printInFile<int,ld>("mc2.dat",ascisse,mc2,15);
  return 0;
}
