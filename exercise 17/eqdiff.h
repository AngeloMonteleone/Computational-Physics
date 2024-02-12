#ifndef eqdiff_h
#define eqdiff_h

#include<iostream>
#include<fstream>
#include<vector>
#include<iomanip>
#include<cmath>
#include<string>
#include<functional>

typedef long double ld;
using namespace std;

//funzione che implementa Eulero
//PARAMETRI:
/*
-valore corrente della variabile indipendente
-intervallo h di incremento della variabile indipendente
-vettore che contiene le variabili dipendenti del problema
-vettore che contiene eventuali parametri delle funzioni
-vettore di funzioni che prendono come parametri: un valore numerico (la variabile indipendente nell'equazione differenziale),
 un vettore di variabili, un vettore di parametri.
*/
template<typename T>
void eulero(ld t, ld timestep, vector<T>* vars,vector<T> pars,vector<function<ld(T, vector<T>, vector<T>)>> funcs){
  vector<T> k1((*vars).size(),0);
  for(int j=0;j<(*vars).size();j++)
    k1[j]=timestep*funcs[j](t,*vars,pars);

  // for(auto item:k1){
  //   cout << item << " ";
  // }
  // cout << endl;
      
  for(int j=0;j<(*vars).size();j++)
    (*vars)[j]+=k1[j];
}

//funzione che implementa Runge-Kutta 2
//PARAMETRI:
/*
-valore corrente della variabile indipendente
-intervallo h di incremento della variabile indipendente
-vettore che contiene le variabili dipendenti del problema
-vettore che contiene eventuali parametri delle funzioni
-vettore di funzioni che prendono come parametri: un valore numerico (la variabile indipendente nell'equazione differenziale),
 un vettore di variabili, un vettore di parametri.
*/
template<typename T>
void rk2(ld t, ld timestep, vector<T>* vars,vector<T> pars,vector<function<ld(T, vector<T>, vector<T>)>> funcs){
  vector<T> k1((*vars).size(),0),k2((*vars).size(),0),temp((*vars).size(),0);
  for(int j=0;j<(*vars).size();j++)
    k1[j]=timestep*funcs[j](t,*vars,pars);

  for(int j=0;j<(*vars).size();j++)
    temp[j]=(*vars)[j]+k1[j]/2.;
  

  for(int j=0;j<(*vars).size();j++)
    k2[j]=timestep*funcs[j](t+timestep/2.,temp,pars);

  for(int j=0;j<(*vars).size();j++)
    (*vars)[j]+=k2[j];
}

//funzione che implementa Runge-Kutta 4
//PARAMETRI:
/*
-valore corrente della variabile indipendente
-intervallo h di incremento della variabile indipendente
-vettore che contiene le variabili dipendenti del problema
-vettore che contiene eventuali parametri delle funzioni
-vettore di funzioni che prendono come parametri: un valore numerico (la variabile indipendente nell'equazione differenziale),
 un vettore di variabili, un vettore di parametri.
*/
template<typename T>
void rk4(ld t, ld timestep, vector<T>* vars,vector<T> pars,vector<function<ld(T, vector<T>, vector<T>)>> funcs){
  vector<T> k1((*vars).size(),0),k2((*vars).size(),0),k3((*vars).size(),0),k4((*vars).size(),0),temp((*vars).size(),0);
      
  for(int j=0;j<(*vars).size();j++)
    k1[j]=timestep*funcs[j](t,*vars,pars);

  for(int j=0;j<(*vars).size();j++)
    temp[j]=(*vars)[j]+k1[j]/2.;

  for(int j=0;j<(*vars).size();j++)
    k2[j]=timestep*funcs[j](t+timestep/2.,temp,pars);
 
  for(int j=0;j<(*vars).size();j++)
    temp[j]=(*vars)[j]+k2[j]/2.;

  for(int j=0;j<(*vars).size();j++)
    k3[j]=timestep*funcs[j](t+timestep/2.,temp,pars);

  for(int j=0;j<(*vars).size();j++)
    temp[j]=(*vars)[j]+k3[j];

  for(int j=0;j<(*vars).size();j++)
    k4[j]=timestep*funcs[j](t+timestep,temp,pars);

  for(int j=0;j<(*vars).size();j++)
    (*vars)[j]+=(k1[j]+2*k2[j]+2*k3[j]+k4[j])/6.;
}

//Integratore di equazioni differenziali.
//PARAMETRI:
/*
-intervallo h di incremento della variabile indipendente
-limite massimo di passi da effettuare
-vettore che contiene i dati iniziali
-vettore che contiene eventuali parametri delle funzioni
-vettore di funzioni che prendono come parametri: un valore numerico (la variabile indipendente nell'equazione differenziale),
 un vettore di variabili, un vettore di parametri.
-stringa che indica la destinazione di salvataggio dei dati
-stringa che indica il metodo da utilizzare
*/
template<typename T>
void integrator(
    ld timestep,
    int step_limit,
    vector<T> init_data,
    vector<T> pars,
    vector<function<ld(T, vector<T>, vector<T>)>> funcs,
    string path,
    string method)
{
  if(step_limit>1000000  ||  init_data.size()!= funcs.size())
    return;
  vector<T> vars=init_data;
  void (*step)(ld t, ld timestep, vector<T>* vars,vector<T> pars,vector<function<ld(T, vector<T>, vector<T>)>> funcs);
  ofstream file;
  file << setprecision(10);
  file.open(path);
  ld t=0;

  if(method=="eulero"){
    step=eulero<T>;
  }else if(method=="rk2"){
    step=rk2<T>;
  }else if(method=="rk4"){
    step=rk4<T>;
  }else
    return;

  for(int i=0;i<step_limit;i++){
    file << t+timestep << " ";
    step(t,timestep,&vars,pars,funcs);
    for(auto var:vars){
        file << var << " ";
    }
    file << endl;
    t+=timestep;
  }
  file.close();
}

//variante della funzione integratore utilizzata per studiare l'implementazione dei vari metodi. Ha come parametri aggiuntivi
/*
-"fixed_time": ovvero l'istante fissato a cui si vuole guardare la soluzione
-"sols": un vettore di funzioni che contiene le soluzioni analitiche del problema, con le quali si vuole effettuare il confronto
*/
template<typename T>
void integrator_test(
    ld timestep,
    int step_limit,
    vector<T> init_data,
    vector<T> pars,
    vector<function<ld(T, vector<T>, vector<T>)>> funcs,
    string path,
    string method,
    ld fixed_time,
    vector<function<ld(T)>> sols){
  if(step_limit>1000000  ||  init_data.size()!= funcs.size())
    return;

  vector<T> vars=init_data;
  void (*step)(ld t, ld timestep, vector<T>* vars,vector<T> pars,vector<function<ld(T, vector<T>, vector<T>)>> funcs);

  ofstream file;
  file << setprecision(10);
  file.open(path,ios_base::app);

  ld t=0;
  int fixed_step = (fixed_time/timestep-1);

  if(method=="eulero"){
    step=eulero<T>;
  }else if(method=="rk2"){
    step=rk2<T>;
  }else if(method=="rk4"){
    step=rk4<T>;
  }else
    return;

  for(int i=0;i<step_limit;i++){
    // file << t+timestep << " ";
    step(t,timestep,&vars,pars,funcs);
    if(i==fixed_step){
      file << t+timestep << " " << timestep;
      for(int j=0; j<vars.size(); j++){
        file << " " << fabsl(vars.at(j)-sols.at(j)(t+timestep)) << " ";  
      }
      file << endl;
      file.close();
      return;
    }
    t+=timestep;
  }
  file.close();
}

#endif