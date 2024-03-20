#include<iostream>
#include<iomanip>
#include<fstream>
#include<cmath>
#include<string>
#include<filesystem>

using namespace std;

typedef long long ll;

//funzione che implementa la somma di termini 1/i^2
//PARAMETRI
/*
-"option": verso in cui effettuare la somma; se ha valore di verità 1, si somma da 1 a N, altrimenti al contrario
-"limit": intero a cui troncare la somma
*/
template<typename T>
T sum_reg(int option, ll limit){
    T ret=0;
    if(option){
        for(ll i=1;i<limit+1;i+=1){
            ret+=1./pow(i,2);
        }
    }else{
        for(ll i=limit;i>0;i-=1){
            ret+=1./pow(i,2);
        }
    }
    return ret;
}

int main(int argc, char** argv){
    const int REQUIRED = 5;//argomenti richiesti da linea di comando
    if(argc!=REQUIRED){
        cout<< "wrong arguments" << endl;
        return 1;
    }

    //il codice implementa la somma fino ad un certo intero, che viene incrementato di volta in volta 

    //PARAMETRI DA LINEA DI COMANDO
    ll lim=stoll(argv[1]);//intero N massimo a cui troncare la somma
    ll step=stoi(argv[2]);//passo da utilizzare nell'incrementare il limite della somma
    string path = argv[3];//nome del file in cui salvare i dati
    int choice=stoi(argv[4]);//scelta del tipo di dato. 1:double, 0:float

    //esempio di comando di esecuzione:
    //"./esercizio1.exe 200000000 10000000 double.dat 1"

    float conf_float = pow(M_PI,2)/6.0;// valore "esatto" della somma (float)
    double conf_double = pow(M_PI,2)/6.0;// valore "esatto" della somma (double)

    cout << "data type: " << (choice?"double":"float") << endl;
    cout << "N: " << lim << endl;
    cout << "step: " << step << endl;

    ofstream file;
    file.open(path);

    //si salva la differenza in valore assoluto tra la somma di i termini e il valore esatto
    ll i=step;
    while(i<=lim){
        file << i << " ";
        if(choice){
            file << setprecision(20) << abs(conf_double - sum_reg<double>(0,i)) << " ";//somma inversa
            file << abs(conf_double - sum_reg<double>(1,i)) << endl;//somma diretta
            i+=step;
        }else{
            file << setprecision(10) << abs(conf_float - sum_reg<float>(0,i)) << " ";//somma inversa
            file << abs(conf_float - sum_reg<float>(1,i)) << endl;//somma diretta
            i+=step;
        }
        
        if(filesystem::file_size(path)>1000000){
            cout << "size limit reached 1MB\n";
            file.close();
            return 1;
        }
    }
    cout << "file \'" << path << "\' size: " << filesystem::file_size(path) << endl;
    file.close();
    return 0;
}