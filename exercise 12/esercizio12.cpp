//il file "gaussAR.dat" contiene i dati relativi al metodo accept & reject, mentre il file cdf.dat contiene i dati relativi al metodo
//della funzione inversa. I dati sono stati prodotti con il comando:
//./esercizio12.exe 50000
#include<iostream>
#include<cmath>
#include<vector>
#include<fstream>
#include<iomanip>
#include<limits>
#include "stat.h"
#include "utilities.h"

using namespace std;
typedef long double ld;

//funzione per la generazione di numeri distribuiti secondo una gaussiana con metodo esatto. I due parametri devono essere numeri
//distribuiti uniformemente tra 0 e 1.
ld gaussian_var(ld alpha, ld y){
  return cos(2*M_PI*alpha)*sqrtl(-log(1-y));
}

//distribuzione di probabilità maggiorante utilizzata nel metodo accept & reject. 
ld pdfAR(ld x){
  if(x>=0 && x<=1)
    return 1./sqrtl(M_PI);
  else if(x>1)
    return x*exp(1-x*x)/sqrtl(M_PI);
  
  //Se viene passato un valore che non rientra nel dominio di definizione viene restituito NaN
  return numeric_limits<double>::quiet_NaN();
}

//inversa della cumulutiva di pdfAR, utilizzata nel metodo accept & reject.
ld cdfAR(ld y){
  if(y>=0 && y<=1./sqrtl(M_PI))
    return y*sqrtl(M_PI);
  else if(y>1./sqrtl(M_PI) && y <=3./(2.*sqrtl(M_PI)))
    return sqrtl(1-log(3-2*y*sqrtl(M_PI)));
  
  //Se viene passato un valore che non rientra nel dominio di definizione viene restituito NaN
  return numeric_limits<double>::quiet_NaN();
}

//gaussiana
ld gauss(ld x){
  return exp(-x*x)/(sqrtl(M_PI));
}

int main(int argc, char** argv){
  const int REQUIRED = 2;//argomenti richiesti da linea di comando
  if(argc!=REQUIRED){
    cout<< "wrong arguments" << endl;
    return 1;
  }
  
  int N = stoi(argv[1]);//numero di valori da generare
  vector<ld> data;//vettore in cui salvare i dati
  ld y_i,a_i;

  //METODO ESATTO
  for(int i=0;i<N;i++){
    y_i = uniform(0,1);
    a_i = uniform(0,1);
    data.push_back(gaussian_var(a_i,y_i));
  }

  printInFile<ld>("cdf.dat",data,17);
  
  //METODO ACCEPT & REJECT
  vector<ld> dataAR;
  ld x_i;
  ld A = 3./(2.*sqrtl(M_PI));//area totale della funzione maggiorante utilizzata
  for(int i=0;i<N;i++){
    //PASSO 1: applicazione del metodo della funzione inversa sulla distribuzione maggiorante, per generare x_i
    y_i = uniform(0,A);
    x_i = cdfAR(y_i);
    //PASSO 2: generazione di un numero distribuito uniformemente sulla retta verticale che interseca la distribuzione maggiorante
    y_i = uniform(0,pdfAR(x_i));
    //PASSO 3: accettazione o meno del valore per confronto con la distribuzione desiderata (la gaussiana in questo caso)
    if(y_i<gauss(x_i)){
      //per scegliere se salvare il valore positivo o negativo usa la distribuzione moneta per avere uguale probabilità
      //di selezionare l'uno oppure l'altro
      if(coin()==1)
        dataAR.push_back(x_i);
      else
        dataAR.push_back(-x_i);
    }
  }

  printInFile<ld>("gaussAR.dat",dataAR,17);
  return 0;
}
