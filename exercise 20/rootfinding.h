#ifndef rootfinding_h
#define rootfinding_h

#include<iostream>
#include<vector>
#include<cmath>
#define MAX_ITER 100
using namespace std;
typedef long double ld;

//funzione che scambia due i valori contenuti in due variabili
template<typename T>
void swap(T* a, T* b){
  T C=*a;
  *b=C;
  *a=*b;
}

//funzione che suddivide un'intervallo in sottointervalli in base agli zeri di una funzione:
//PARAMETRI
/*
-funzione di interesse
-numero massimo di zeri (e dunque, di intervalli)
-numero di intervalli iniziali da valutare per applicare il metodo. (Si calcola un dx che equivale a 1/n dell'intervallo e si utilizza
 questo per vanzare di volta in volta)
-limite minimo dell'intervallo da dividere
-limite massimo dell'intervallo da dividere
-vettore in cui salvare gli estremi inferiori
-vettore in cui salvare gli estremi superiori
*/
void multbrak(ld (*func)(ld),int* max_zeros, int n, ld lower_bound, ld upper_bound,vector<ld>* final_lower,vector<ld>* final_upper){
  int found=0;
  ld x, first_eval,second_eval, dx;

  if(upper_bound<lower_bound){
    cout << "valori invertiti" << endl;
    swap<ld>(&lower_bound,&upper_bound);
  }

  x=lower_bound;
  dx = (upper_bound-lower_bound)/n;
  first_eval=func(x);
  
  for(int i=0;i<=n;i++){
    //cout << x << endl;
    x+=dx;
    second_eval=func(x);
    if(first_eval*second_eval<=0.){
      //cout << "first: " << first_eval << " second: " << second_eval << endl;
      (*final_lower).push_back(x-dx);
      (*final_upper).push_back(x);
      found++;
      if(found==*max_zeros)  return;
    }
    first_eval=second_eval;
  }
  *max_zeros=found;
}

//funzione che implementa il metodo di bisezione:
//PARAMETRI
/*
-funzione di cui si vuole ricercare uno zero
-limite minimo dell'intervallo in cui cercare
-limite massimo dell'intervallo in cui cercare
-precisione desiderata
-variabile in cui salvare il risultato
*/ 
void bisection(ld (*func)(ld),ld lower_bound, ld upper_bound, ld precision, ld* result){
  ld midpoint, pos, neg;
  
  if(func(lower_bound)<0 && func(upper_bound)>0){
    pos = upper_bound;
    neg = lower_bound;
  }else if(func(lower_bound)>0 && func(upper_bound)<0){
    neg = upper_bound;
    pos = lower_bound;
  }else
    return;
  int iter=0;
  while(fabsl(pos-neg)>precision){
    midpoint = (pos+neg)/2;
    if(func(midpoint)>0)
      pos = midpoint;
    else
      neg = midpoint;
    iter ++;
    if(iter==MAX_ITER){ 
      *result=midpoint;
      return;
    }
  }
  
  // cout << "numero iterazioni: " << iter << endl;
  *result=midpoint;
}

//funzione che implementa il metodo di Newton-Rapson:
//PARAMETRI
/*
-funzione di cui si vogliono ricercare gli zeri
-derivata della funzione
-limite minimo dell'intervallo in cui cercare
-limite massimo dell'intervallo in cui cercare
-massimo numero di iterazioni
-vettore in cui salvare i risultati
-numero di porzioni in cui dividere la griglia
*/ 
void rapson(ld (*func)(ld),ld (*deriv)(ld), ld lower_bound, ld upper_bound, int max, vector<ld>* results, int n){
  ld dx = (upper_bound-lower_bound)/n;
  ld x = lower_bound;
  (*results).push_back(x);

  for(int i=0; i<n; i++){
    x+=dx;
    (*results).push_back(x);
  }
  
  ld delta;
  for(int i=0; i<max; i++){
    for(int j=0;j<(n+1);j++){
      delta = -func((*results).at(j))/deriv((*results).at(j));
      (*results).at(j)+=delta;
    }
  }
}

#endif