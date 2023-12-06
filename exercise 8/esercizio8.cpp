#define _USE_MATH_DEFINES
#include<iostream>
#include<iomanip>
#include<fstream>
#include<cmath>
#include<ranges>
#include<iterator>
#include<string>
#include<filesystem>
#include<utility>
#include"integration.h"
#include"utilities.h"

#define REAL_VALUE(M) powl(M_PI,M/2.)/tgammal(M/2.+1)

using namespace std;

typedef long long ll;
typedef long double ld;

template<typename T>
void printvec(vector<T> vec){
    for(auto& elem : vec){
        cout << elem << " ";
    }
    cout << endl;
}

template<typename T>
T sumsqvec(vector<T> vec){
    T sum = 0.;
    for(auto& elem : vec){
        sum+=powl(elem,2);
    }
    return sum;
}

template<typename T>
void printgrid(vector<vector<T>> grid){
    for(auto& point : grid)
        printvec<T>(point);
}

//funzione che valuta la funzione di M-1 variabili che definisce la sfera in M dimensioni
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
        // cout << "EVALUATE: " << evaluate << endl;
        point-=coord*pow(10,current_dim-1);
        // cout << "POINT: " << point << endl;
        ret-=powl(evaluate,2);
    }

    if(ret<0)
        return 0;
    ret = sqrtl(ret);
    
    return ret;
}

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

//funzione che realizza il prodotto cartesiano un numero arbitrario di volte. Poco utile
template<typename T>
vector<vector<T>> cart_prod(vector<T> set_of_coords, int dim){
    vector<vector<T>> newset;
    vector<vector<T>> current_set;
    for(auto& coord: set_of_coords)
        current_set.push_back({coord});
    do{
        newset = {};
        for(auto& first_set_elem : current_set){
            for(auto& second_set_elem : set_of_coords){
                vector<T> newelem = first_set_elem;
                newelem.push_back(second_set_elem);
                newset.push_back(newelem);
            }
        }
        dim--;
        current_set=newset;
    }while(dim>1);
    
    return newset;
}
//funzione che realizza l'integrale multidimensionale della sfera
//PARAMETRI:
//-h: larghezza dell'intervallo
//-dim: dimensione dell'integrale
//-func: funzione da integrare
template<typename T>
T integral_multidim(T h, int dim, ld (*func)(int,int)){
    // cout << "\nSELECTED DIM: " << dim << endl;
    // cout << "SELECTED SPACING: " << h << endl;
    T ret = 0.;
    //con un intero si scorre attraverso tutti i punti possibili
    for(int current_point = 0; current_point < powl(10,dim-1); current_point++){
        // cout << "CURRENT POINT: " << current_point << endl;
        ret+=func(dim,current_point);
    }

    return ret*powl(h,dim-1);
}

template<typename T>
vector<T> random_vector(int dim){
    // srand(time(nullptr));//bisogna stare attenti ad aggiornare in questo modo il seed di generazione, perché se i punti vengono generati molto velocemente
                            //in un ciclo verranno generati sempre gli stessi valori
    vector<T> ret(dim);
    for(auto& coord : ret){
        coord = (T)rand()/RAND_MAX;
    }
    return ret;
}

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
        // if(value == 0)
        //     actual--;
        ret+=value;
    }
    return ret/actual;
}

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
    vector<T> couple{ret/N,dev};
    // return ret/N;
    return couple;
}

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
    // return ret/N;
    return dev;
}

int main(int argc, char** argv){
    const int REQUIRED = 3;
    if(argc!=REQUIRED)
        return 1;

    int dim = stoi(argv[1]);
    int number_of_points = stoi(argv[2]);
    auto start = GET_TIME;
    // int point = 4111111;
    //TEST FUNZIONE SFERA
    // cout << "TEST, M_SPHERE: " << M_sphere(dim,point) << endl;

    //TEST INTEGRALE DETERMINISTICO
    // cout << "INTEGRAL: " << pow(2,dim)*integral_multidim<ld>(.1,dim,&M_sphere) << endl;
    // elapsed(start);
    //TEST GENERAZIONE PUNTO
    // for(int i=1;i<10;i++){
    //     vector<ld> point=random_vector<ld>(dim);
    //     printvec(point);
    //     // cout << sqrtl(1-sumsqvec(point)) << endl;
    //     cout << "TEST, M_SPHERE: " << M_sphere_standard(dim,point) << endl;
    // }
    //TEST INTEGRALE MONTECARLO
    // start = GET_TIME;
    // cout << "INTEGRAL: " << pow(2,dim)*integral_Monte_Carlo(dim-1,number_of_points,&M_sphere_standard) << endl;
    // elapsed(start);
    //TEST VALORE ANALITICO
    // cout << "REAL VALUE: " << REAL_VALUE(dim) << endl;
    // cout << tgammal(dim/2.+1) << endl;
    
    vector<int> dims(dim-1);
    vector<ld> values_det(dim-1),values_mc(dim-1),times_det(dim-1),times_mc(dim-1);
    vector<ld> exact_values(dim-1);

    vector<ld> dev(dim-1),t_values(dim-1);

    int current_dim;
    vector<ld> temp;
    for(int i=0; i<=(dim-2); i++){
        current_dim = i+2;
        dims.at(i)=current_dim;
        start = GET_TIME;
        values_det.at(i) = pow(2,current_dim)*integral_multidim<ld>(.1,current_dim,&M_sphere);
        times_det.at(i) = runtime(start);
        start = GET_TIME;
        //TEST DEVIAZIONE STANDARD
        temp = integral_Monte_Carlo_valdev<ld>(current_dim-1,number_of_points,&M_sphere_standard);
        values_mc.at(i) = pow(2,current_dim)*temp.at(0);
        dev.at(i)= pow(2,current_dim)*temp.at(1);//TODO: da vedere se influenza sensibilmente il tempo di calcolo
        //TEST
        // values_mc.at(i) = pow(2,current_dim)*integral_Monte_Carlo<ld>(current_dim-1,number_of_points,&M_sphere_standard);
        times_mc.at(i) = runtime(start);
        exact_values.at(i) = REAL_VALUE(current_dim);

        t_values.at(i) = fabsl(exact_values.at(i)-values_mc.at(i))/dev.at(i);
    }

    printInFile<int,ld,ld,ld,ld,ld>("data.dat",dims,values_det,times_det,values_mc,times_mc,exact_values,13);
    printInFile<int,ld,ld>("devs.dat",dims,dev,t_values,13);
    printvec(dev);
    return 0;
}