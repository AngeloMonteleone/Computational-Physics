//Questo file è specifico per lo studio dei coefficienti di proporzionalità tra i momenti di ordine pari e le potenze del momento
// di ordine 2. Per lo studio dell'andamento dei momenti centrali di diverso ordine si fa riferimento 
//al file "esercizio9_valori.cpp"

//I dati sono stati salvati nella cartella "studio coefficienti" e sono stati prodotti con i comandi:
//./esercizio9_coefficienti.exe 5000 100 4
//./esercizio9_coefficienti.exe 5000 100 6

#include<iostream>
#include<cmath>
#include<vector>
#include<fstream>
#include<iomanip>
#include"utilities.h"

using namespace std;
typedef short int sint;
typedef long double ld;

//funzione che riproduce la distribuzione moneta
sint coin(){
  float num = (float)rand()/RAND_MAX;
  if(num < 0.5)
    return -1;
  return 1;
}

//funzione che, a partire dalla distribuzione moneta, costruisce una variabile casuale secondo il Teorema del limite centrale
//L'unico parametro è la grandezza del campione con cui costruire questa variabile
ld coin_to_gauss(int N){
  ld mean = 0.;
  for(int i=0; i<N;i++){
    mean+=coin();
  }
  
  return mean/N;
}

//funzione che genera numeri distribuiti uniformemente nell'intervallo (a,b)
ld uniform(ld a, ld b){
  ld ret = a + (b-a)*(ld)rand()/RAND_MAX;
  return ret;
}

//funzione che, a partire dalla distribuzione uniforme, costruisce una variabile casuale secondo il Teorema del limite centrale
//PARAMETRI
/*
-"N": grandezza del campione con cui costruire la nuova variabile
-"a" e "b": estremi dell'intervallo di definizione della distribuzione uniforme
*/
ld uniform_to_gauss(int N,ld a,ld b){
  ld mean = 0.;
  for(int i=0; i<N;i++){
    mean+=uniform(a,b);
  }
  
  return mean/N;
}

//funzione che calcola il momento centrale di un ordine arbitrario
//PARAMETRI
/*
-"data": vettore di dati con ci calcolare il momento
-"esp": ordine del momento che si vuole calcolare
*/
template<typename T>
T moment(vector<T> data,int esp){
  T ret = 0;
  T mean = 0;
  
  for(int i = 0; i<data.size();i++){
    mean+= data.at(i);
  }
  mean/=data.size();

  for(int i = 0; i<data.size();i++){
    ret+= powl(data.at(i)-mean,esp);
  }
  
  return ret/data.size();
}

int main(int argc, char** argv){
  srand(time(NULL));

  const int REQUIRED = 4;//numero di argomenti richiesti dal programma
  if(argc!=REQUIRED){
    cout << "wrong arguments" << endl;
    return 1;
  }

  int M = stoi(argv[1]);//numero di valori generati
  int N = stoi(argv[2]);//grandezza (massima) del campione con cui applicare il Teorema del limite centrale
  int esp = stoi(argv[3]);//ordine del momento centrale che si vuole studiare

  vector<ld> data_coin,data_unif,ascisse,current_moment_coin,current_moment_unif;//vettori in cui salvare i dati
  for(int j=1; j<N; j++){
    data_coin = {};
    data_unif = {};
    ascisse.push_back(j);//si salva il valore crescente del campione, incrementato ad ogni iterazione 
    for(int i=0;i<M;i++){
      data_coin.push_back(coin_to_gauss(j));//applicazione del teorema a partire dalla distribuzione moneta
      data_unif.push_back(uniform_to_gauss(j,-1,1));//applicazione del teorema a partire dalla distribuzione uniforme
    }
      //studio del coefficiente numerico di proporzionalità tra il momento analizzato e una potenza del momento di ordine 2.
      //per rendere più generale il codice si calcola il momento dell'ordine desiderato "esp" e lo si divide per la potenza
      //della deviazione con esponente "esp/2"
      ld sigma = moment<ld>(data_coin,2);
      current_moment_coin.push_back(moment<ld>(data_coin,esp)/powl(sigma,esp/2));

      sigma = moment<ld>(data_unif,2);
      current_moment_unif.push_back(moment<ld>(data_unif,esp)/powl(sigma,esp/2));
  }
  printInFile<ld,ld>("studio coefficienti/coef_unif" + to_string(esp) + ".dat",ascisse,current_moment_unif,15);
  printInFile<ld,ld>("studio coefficienti/coef_coin" + to_string(esp) + ".dat",ascisse,current_moment_coin,15);
  return 0;
}
