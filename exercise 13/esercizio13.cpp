#include<iostream>
#include<vector>
#include"stat.h"
#include<cmath>
#include<iomanip>
#include<fstream>

typedef long double ld;

using namespace std;

#define LINE_LIMIT 1000000

template<typename T>
void printInFile(string path, vector<T> first_col, int precision){
    ofstream file;
    file << setprecision(precision);
    file.open(path);
    unsigned int N_rows = first_col.size();
    
    for(unsigned int i = 0; i<N_rows; i++){
        file << first_col[i] << endl;
	if(i>LINE_LIMIT){
	  cout << "OVER LINE LIMIT" << endl;
	  return;
	}
	  
    }
    file.close();
}

template<typename T1,typename T2>
void printInFile(string path, vector<T1> first_col, vector<T2> second_col, int precision){
    if(first_col.size()!=second_col.size()){
        cout << "ERRORE: vettori di dimensione diversa!" << endl;
        return;
    }
    ofstream file;
    file << setprecision(precision);
    file.open(path);
    unsigned int N_rows = first_col.size();
    
    for(unsigned int i = 0; i<N_rows; i++){
        file << first_col[i] << " " << second_col[i] << endl;
        if(i>LINE_LIMIT){
	  cout << "OVER LINE LIMIT" << endl;
	  return;
	}
    }
    file.close();
}

ld f1(ld x){
  return x*cos(x);
}

ld f2(ld x){
  return x*sin(x);
}

ld fg_1(ld z){
  return asin(z);
}

ld fg_2(ld z){
  return 2*acos(1-2*z);
}

int main(int argc, char** argv){
//numero di parametri richiesti dal codice
  const int REQUIRED = 4;
  if(argc!=REQUIRED){
    cout << "wrong arguments" << endl;
    return 1;
  }
//parametri utilizzati nel programma, in ordine
//N e' il numero massimo di punti a cui arrivare nella generazione di numeri tra 0 e 1 per l'importance sampling
//step e' l'incremento del numero di punti utilizzato per calcolare un integrale 
//med e' il numero di volte su cui viene mediato il valore di ogni integrale
  int N = stoi(argv[1]);
  int step = stoi(argv[2]);
  int repeat = stoi(argv[3]);

  ld real1 = .5*(M_PI-2), real2 = M_PI; 
  vector<ld> data1,data2; 
  vector<ld> mc1,mc2;
  vector<int> ascisse;

  for(int j=step;j<N;j+=step){
    cout<<j<<endl;
    mc1.push_back(integral_Monte_Carlo_repeat<ld>(j,0,M_PI/2,&f1,repeat,real1));
    mc2.push_back(integral_Monte_Carlo_repeat<ld>(j,0,M_PI,&f2,repeat,real2));

    data1.push_back(integral_Monte_Carlo_repeat<ld>(j,0,1,&fg_1,repeat,real1));
    data2.push_back(integral_Monte_Carlo_repeat<ld>(j,0,1,&fg_2,repeat,real2));
    ascisse.push_back(j);
  }
  printInFile<int,ld>("data1.dat",ascisse,data1,15);
  printInFile<int,ld>("data2.dat",ascisse,data2,15);
  printInFile<int,ld>("mc1.dat",ascisse,mc1,15);
  printInFile<int,ld>("mc2.dat",ascisse,mc2,15);
  return 0;
}
