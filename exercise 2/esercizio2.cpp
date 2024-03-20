#include<iostream>
#include<iomanip>
#include<fstream>
#include<cmath>
#include<string>
#include<filesystem>
#include<vector>

#define DATA_LIMIT 1000000

using namespace std;

typedef long long ll;
//funzione che implementa il calcolo della discrepanza
//PARAMETRI
/*
-"n": numero di termini della relazione da calcolare
-"path": stringa con il nome del file in cui salvare i dati
-"precision": precisione con cui stampare i valori nel file
-"coef": se pari a 1 effettua la stima del coefficiente epsilon, altrimenti calcola solo la discrepanza
-"simulate": se pari a 1 effettua il calcolo in precisione simulata, altrimenti segue il tipo di dato T della funzione templata
*/
template<typename T>
void delta(int n, string path, int precision, bool coef, bool simulate){
    ofstream file;
    file.open(path);

    //soluzioni della relazione di ricorrenza
    T golden = (sqrtl(5.)-1.)/2.;
    T golden2 = -(sqrtl(5.)+1.)/2.;

    //implementazione della precisione simulata
    if(simulate){
        float eps = pow(10,-8);
        golden = golden + eps*golden2;
    }

    T del;//variabile in cui salvare il valore della discrepanza
    T chi0 = 1.;
    T chi1 = golden2;
    T temp;
    
    file << 0 << setprecision(precision) << " " << 0 << endl;
    file << 1 << setprecision(precision) << " " << 0 << endl;

    for(int i = 1; i < n; i++){
        temp = chi1;
        chi1 = chi0 - chi1;
        chi0 = temp;   
        del=abs((chi1-powl(golden,i+1))/(coef?powl(golden2,i+1):1));//calcolo della discrepanza, se la variabile "coef" è pari a 1 si
        //divide per la corrispondente potenza della seconda soluzione della relazione di ricorrenza, per stimare il coefficiente epsilon,
        //altrimenti si divide per 1, calcolando la semplice discrepanza
        
        file << i+1 << " " << setprecision(precision) << del << endl;
        if(filesystem::file_size(path)>DATA_LIMIT){
            cout << "size limit reached: " << DATA_LIMIT << "B\n" ;
            file.close();
            return;
        }
    }
    file.close();
}

//funzione che implementa il calcolo della relazione di ricorrenza
//PARAMETRI
/*
-"n": numero di termini della relazione da calcolare
-"path": stringa con il nome del file in cui salvare i dati
-"precision": precisione con cui stampare i valori nel file
-"simulate": se pari a 1 effettua il calcolo in precisione simulata, altrimenti segue il tipo di dato T della funzione templata
*/
template<typename T>
void chi(int n, string path, int precision, bool simulate){
    T min = 1.;//variabile per salvare il minimo
    int minind;//variabile per salvare il valore dell'indice in corrispondenza del quale si ha un minimo
    ofstream file;
    file.open(path);
    T golden = (sqrtl(5.)-1.)/2.;
    T golden2 = -(sqrtl(5.)+1.)/2.;

    if(simulate){
        float eps = pow(10,-8);
        golden = golden + eps*golden2;
    }

    T chi0 = 1.;
    T chi1 = golden;
    T temp;
    
    file << 0 << setprecision(precision) << " " << 1 << endl;
    file << 1 << setprecision(precision) << " " << golden << endl;

    for(int i = 1; i < n; i++){
        temp = chi1;
        chi1 = chi0 - chi1;
        chi0 = temp;
        
        //in questa porzione di codice si tiene traccia del valore minimo ottenuto e 
        //in corrispondenza di quale termine della relazione di ricorrenza lo si ottiene
        if(log10(abs(chi1)) < log10(abs(min))){
            min = chi1;
            minind = i;
        }

        file << i+1 << " " << setprecision(precision) << chi1 << endl;
        if(filesystem::file_size(path)>DATA_LIMIT){
            cout << "size limit reached: " << DATA_LIMIT << "B\n" ;
            return;
        }
    }
    file.close();

    cout <<"min at n: " << minind << ", exponent: " << log10(abs(min)) << endl;
    cout << "CHECK\n";

    //in queste righe si stampa il valore atteso dell'indice in corrispondenza del quale si dovrebbe 
    //avere un minimo (relazione 2.5 nella relazione). I valori al numeratore sono ottenuti da 
    //una precedente stima del parametro epsilon
    if(is_same_v<T,float>)
        cout << "n: " << log10(7.341e-9)/log10(abs(golden/golden2));
    else if(is_same_v<T,double>)
        cout << "n: " << log10(2.429e-17)/log10(abs(golden/golden2));
    else if(is_same_v<T,long double>)
        cout << "n: " << log10(1.173e-21)/log10(abs(golden/golden2));
    
}

//i dati sono stati prodotti dai seguenti comandi di esecuzione e poi spostati nelle relative cartelle:
//CALCOLO DISCREPANZA (cartella "discrepanza")
/*
./esercizio2.exe 200 float.dat 0 0 0
./esercizio2.exe 200 double.dat 1 0 0
./esercizio2.exe 200 longdouble.dat 2 0 0 
*/
//CALCOLO EPSILON (cartella "epsilon")
/*
./esercizio2.exe 200 epsilon_longdouble.dat 2 1 0
./esercizio2.exe 200 epsilon_double.dat 1 1 0
./esercizio2.exe 200 epsilon_float.dat 0 1 0 
*/
//CALCOLO DIRETTO DELLA RELAZIONE DI RICORRENZA (cartella "chi")
/*
./esercizio2.exe 200 chi_float.dat 0 0 0
./esercizio2.exe 200 chi_double.dat 1 0 0
./esercizio2.exe 200 chi_longdouble.dat 2 0 0
*/
//CALCOLO IN PRECISIONE SIMULATA (cartella "false")
/*
./esercizio2.exe 200 float.dat 0 0 0
./esercizio2.exe 200 falsefloat.dat 2 0 1
*/ 
// APPROFONDIMENTO (cartella "approfondimento")
/*
./esercizio2.exe 180 approfondimento_float.dat 0 0 0
./esercizio2.exe 180 approfondimento_double.dat 1 0 0
./esercizio2.exe 180 approfondimento_longdouble.dat 2 0 0
*/

int main(int argc, char** argv){
    const int REQUIRED = 6;//argomenti richiesti da linea di comando
    if(argc!=REQUIRED){
        cout<< "wrong arguments" << endl;
        return 1;
    }
    
    //PARAMETRI LINEA DI COMANDO
    int N = stoi(argv[1]);//termine della relazione fino a cui si prosegue il calcolo
    string path = argv[2];//nome del file in cui salvare i dati
    int option = stoi(argv[3]);//scelta di quale tipo di calcolo effettuare (spiegazione a linea ...)
    bool epsilon = stoi(argv[4]);//scelta se effettuare la stima del coefficiente epsilon nella relazione di ricorrenza
    int simulate = stoi(argv[5]);//scelta se effettuare il calcolo in precisione "simulata", ovvero forzando il valore del coefficiente epsilon

    cout << option << endl;
    cout << path << endl;

    if(option == 0){
        delta<float>(N,path,10,epsilon,0);
    }else if(option == 1){
        delta<double>(N,path,20,epsilon,0);
    }else if(option == 2){
        delta<long double>(N,path,30,epsilon,simulate);
    }else if(option==10){
        chi<float>(N,path,10,0); 
    }else if(option==11){
        chi<double>(N,path,20,0);
    }else if(option==12){
        chi<long double>(N,path,30,simulate);
    }else
        cout << "debug" << endl;
    
    return 0;
}