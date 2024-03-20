#include<iostream>
#include<cmath>
#include<vector>

typedef long long ll;
typedef long double ld;
typedef short int sint;

using namespace std;

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

//funzione che implementa il metodo Monte Carlo
//PARAMETRI
/*
-"N": numero dei punti utilizzati
-"a" e "b": estremi dell'intervallo di integrazione
-"func": funzione integranda
*/
template<typename T>
T integral_Monte_Carlo(int N, ld a, ld b, ld (*func)(ld)){
    T ret=0.;
    T point;
    for(int i=0;i<N;i++){
        point = uniform(a,b);
        ret+=func(point);
    }
    return ret*(b-a)/N;
}

//funzione che implementa il metodo Monte Carlo per lo studio dell'errore
//PARAMETRI
/*
-"N": numero dei punti utilizzati
-"a" e "b": estremi dell'intervallo di integrazione
-"func": funzione integranda
-"repeat": numero di volte in cui si ripete il conto per fare la media
-"real": valore vero dell'integrale di interesse
*/
template<typename T>
T integral_Monte_Carlo_repeat(int N, ld a, ld b, ld (*func)(ld),int repeat,ld real){
    T tot=0.;
    for(int j=0;j<repeat;j++){
        tot+=fabsl(integral_Monte_Carlo<T>(N,a,b,func)-real);
    }
    
    return tot/repeat;
}

//funzione che implementa il metodo Hit or miss
//PARAMETRI
/*
-"N": numero dei punti utilizzati
-"x_min" e "x_max": estremi del rettangolo sulle ascisse
-"y_min" e "y_max": estremi del rettangolo sulle ordinate
-"func": funzione integranda
*/
template<typename T>
T hit_miss(int N, ld x_min, ld x_max, ld y_min, ld y_max, ld (*func)(ld)){
  T area = fabsl((x_max-x_min)*(y_max-y_min));
  int N_hit = 0;
  T x_rand,y_rand;
  for(int i=0;i<N;i++){
    x_rand = uniform(x_min,x_max);
    y_rand = uniform(y_min,y_max);
    if(y_rand < func(x_rand)){
      N_hit++;
    }
  }
  return (area*(ld)N_hit)/N;
}

//funzione che implementa il metodo Hit or miss per lo studio dell'errore
//PARAMETRI
/*
-"N": numero dei punti utilizzati
-"x_min" e "x_max": estremi del rettangolo sulle ascisse
-"y_min" e "y_max": estremi del rettangolo sulle ordinate
-"func": funzione integranda
-"repeat": numero di volte in cui si ripete il conto per fare la media
-"real": valore vero dell'integrale di interesse
*/
template<typename T>
T hit_miss_repeat(int N, ld x_min, ld x_max, ld y_min, ld y_max, ld (*func)(ld),int repeat,ld real){
  T tot=0;
  for(int j=0;j<repeat;j++){
    tot+=fabsl(hit_miss<T>(N,x_min,x_max,y_min,y_max,func)-real);
  }
  return tot/repeat;
}