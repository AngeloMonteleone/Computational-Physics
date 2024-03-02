#include<iostream>
#include<vector>
#include<fstream>
#include<iomanip>
#include<cmath>
#include<set>
#include<complex>

using namespace std;
typedef long double ld;

//funzione che applica la formula iterativa per il problema in esame
complex<ld> iter(complex<ld> z){
  return z-(pow(z,3)-complex<ld>(1,0))/(complex<ld>(3,0)*pow(z,2));
}

int main(int argc, char** argv){
  //si richiedono due parametri da linea di comando
  const int REQUIRED = 3;
  if (argc!=REQUIRED){
    return 1;
  }
  vector<complex<ld>> grid;
  //numero di intervalli in cui suddividere ogni asse, per cui ci saranno N+1 punti
  int N=stoi(argv[1]);
  //numero massimo di iterazioni
  int K=stoi(argv[2]);

  //estremi da usare per ogni asse
  ld inf=-2;
  ld sup=+2;

  //punto da cui si parte per costruire la griglia
  complex<ld> z(-2,-2);
  //incremento sull'asse reale
  complex<ld> dx((sup-inf)/N,0);
  //incremento sull'asse immaginario
  complex<ld> dy(0,(sup-inf)/N);

  //costruzione griglia
  for(int j=0;j<=N;j++){
    for(int k=0;k<=N;k++){
      grid.push_back(z+complex<ld>(j,0)*dx+complex<ld>(k,0)*dy);
    }
  }

  complex<ld> last, actual;
  //precisione entro cui fermare l'iterazione
  ld accuracy=1e-5;
  //vettore in cui salvare il numero di iterazioni effettuate per ogni punto della griglia
  vector<int> final_grid;
  for(int i=0;i<grid.size();i++){
    last = grid.at(i);
    for(int j=0;j<K;j++){
      actual=iter(last);
      if(abs(actual-last) < accuracy){
        final_grid.push_back(j);
        break;
      }
      last=actual;
      if((j+1)==K)
        final_grid.push_back(j);
    }
  }
  //NOTA: bisogna stare attenti, perché se nella griglia c'è (0,0), si ha una divisione per zero
  ofstream FILE;
  FILE.open("data.dat");
  for(int i=0;i<grid.size();i++){
    // cout << grid.at(i) << " " << final_grid.at(i) << endl;
    FILE << final_grid.at(i) << " ";
    //dato che i punti della griglia sono salvati in un vettore unico, per salvare i dati in forma matriciale
    //quando si raggiunge l'(N+1)-esimo punto si va a capo per riempire la riga successiva
    if((i+1)%(N+1)==0)
      FILE << endl;
  }
  FILE.close();
  return 0;
}
