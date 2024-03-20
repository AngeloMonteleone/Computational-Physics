#ifndef sphereint_h
#define sphereint_h

#include<iostream>
#include<cmath>
#include<ranges>
#include<iterator>
#include<utility>
#include"utilities.h"

#define REAL_VALUE(M) powl(M_PI,M/2.)/tgammal(M/2.+1)

using namespace std;

typedef long long ll;
typedef long double ld;

//funzione che stampa gli elementi di un vettore. L'unico parametro è il vettore d'interesse
template<typename T>
void printvec(vector<T> vec){
    for(auto& elem : vec){
        cout << elem << " ";
    }
    cout << endl;
}

//funzione che calcola la somma dei quadrati degli elementi di un vettore. L'unico parametro è il vettore d'interesse
template<typename T>
T sumsqvec(vector<T> vec){
    T sum = 0.;
    for(auto& elem : vec){
        sum+=powl(elem,2);
    }
    return sum;
}

//funzione che valuta la funzione di M-1 variabili che definisce la sfera in M dimensioni (versione per integrale deterministico)
//PARAMETRI
//-M: dimensione
//-point: numero intero che si utilizza per codificare il punto della griglia da valutare. Ogni cifra rappresenta il valore della relativa coordinata
//       Dato che interessa avere una griglia tra 0 e 1, si "estrae" da questa variabile la cifra relativa alla coordinata, la si divide per 10 e, 
//       dato che in questo caso interessa la formula midpoint si aggiunge 0.05 (metà della larghezza dell'intervallo) per andare a valutare il valore
//       centrale
ld M_sphere(int M, int point){
    ld ret = 1.;
    int coord;
    ld evaluate;

    for(int current_dim=M-1;current_dim >=1; current_dim--){
        coord = point/pow(10,current_dim-1);
        evaluate = (ld)coord/10. +.05;
        
        point-=coord*pow(10,current_dim-1);
        
        ret-=powl(evaluate,2);
    }

    if(ret<0)
        return 0;
    ret = sqrtl(ret);
    
    return ret;
}

//funzione che valuta la funzione di M-1 variabili che definisce la sfera in M dimensioni (versione per Monte Carlo)
//PARAMETRI
//-M: dimensione
//-point: vettore con le coordinate del punto in cui si vuole valutare la funzione
ld M_sphere_standard(int M, vector<ld> point){
    ld ret = 1.;
    for(auto& coord : point){
        ret-=powl(coord,2);
    }
    if(ret<0)
        return 0;
    ret = sqrtl(ret);
    return ret;
}

//funzione che realizza l'integrale multidimensionale della sfera
//PARAMETRI:
//-h: larghezza dell'intervallo
//-dim: dimensione dell'integrale
//-func: funzione da integrare
template<typename T>
T integral_multidim(T h, int dim, ld (*func)(int,int)){
    T ret = 0.;
    //con un intero si scorre attraverso tutti i punti possibili
    for(int current_point = 0; current_point < powl(10,dim-1); current_point++){
        ret+=func(dim,current_point);
    }

    return ret*powl(h,dim-1);
}

//funzione che genera un punto di R^M. Ogni coordinata è un numero casuale che si trova tra 0 e 1
//PARAMETRI
//-dim: dimensione
template<typename T>
vector<T> random_vector(int dim){
    vector<T> ret(dim);
    for(auto& coord : ret){
        coord = (T)rand()/RAND_MAX;
    }
    return ret;
}

//funzione che calcola l'integrale con metodo Monte Carlo
//PARAMETRI
//-dim: dimensione
//-N: numero di punti
//-func: funzione integranda
template<typename T>
T integral_Monte_Carlo(int dim,int N, ld (*func)(int,vector<T>)){
    //in questo caso si integra sul volume unitario in un numero "dim" di dimensioni, quindi il fattore legato al volume dello spazio è
    //uguale a 1 e non viene calcolato. Per integrali in spazi generali questa cosa deve essere invece implementata
    T ret=0.;
    vector<T> point;
    int actual = N;
    T value;
    for(int i=0;i<N;i++){
        point = random_vector<T>(dim);
        value = func(dim,point);
        ret+=value;
    }
    return ret/actual;
}

//funzione che calcola l'integrale con metodo Monte Carlo (versione con valore e deviazione standard)
//PARAMETRI
//-dim: dimensione
//-N: numero di punti
//-func: funzione integranda
template<typename T>
vector<T> integral_Monte_Carlo_valdev(int dim,int N, ld (*func)(int,vector<T>)){
    //in questo caso si integra sul volume unitario in un numero "dim" di dimensioni, quindi il fattore legato al volume dello spazio è
    //uguale a 1 e non viene calcolato. Per integrali in spazi generali questa cosa deve essere invece implementata
    T ret=0.;
    vector<T> point;
    T value,meanf=0,meanf_sq=0;
    for(int i=0;i<N;i++){
        point = random_vector<T>(dim);
        value = func(dim,point);
        meanf+=value;
        meanf_sq+=value*value;
        
        ret+=value;
    }
    meanf/=N;
    meanf_sq/=N;

    T dev = sqrtl((meanf_sq-meanf*meanf)/N);
    vector<T> couple{ret/N,dev};//il valore dell'integrale e la deviazione vengono restituite come una coppia di valori
    return couple;
}

//funzione che calcola l'integrale con metodo Monte Carlo (versione con solo deviazione standard)
//PARAMETRI
//-dim: dimensione
//-N: numero di punti
//-func: funzione integranda
template<typename T>
T integral_Monte_Carlo_dev(int dim,int N, ld (*func)(int,vector<T>)){
    //in questo caso si integra sul volume unitario in un numero "dim" di dimensioni, quindi il fattore legato al volume dello spazio è
    //uguale a 1 e non viene calcolato. Per integrali in spazi generali questa cosa deve essere invece implementata
    vector<T> point;
    T meanf=0,meanf_sq=0;
    T value;
    for(int i=0;i<N;i++){
        point = random_vector<T>(dim);
        value = func(dim,point);
        meanf+=value;
        meanf_sq+=value*value;
    }
    meanf/=N;
    meanf_sq/=N;

    T dev = sqrtl((meanf_sq-meanf*meanf)/N);
    return dev;
}

#endif