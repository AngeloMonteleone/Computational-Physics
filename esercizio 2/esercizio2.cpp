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

template<typename T>
void delta(int n, string path, int precision, bool epsilon, bool simulate){
    ofstream file;
    file.open(path);
    T golden = (sqrtl(5.)-1.)/2.;
    T golden2 = -(sqrtl(5.)+1.)/2.;

    if(simulate){
        float eps = pow(10,-8);
        golden = golden + eps*golden2;
    }

    T del;
    T chi0 = 1.;
    T chi1 = golden;
    T temp;
    
    file << 0 << setprecision(precision) << " " << 0 << endl;
    file << 1 << setprecision(precision) << " " << 0 << endl;

    for(int i = 1; i < n; i++){
        temp = chi1;
        chi1 = chi0 - chi1;
        chi0 = temp;   
        del=abs((chi1-powl(golden,i+1))/(epsilon?powl(golden2,i+1):1));
        
        file << i+1 << " " << setprecision(precision) << del << endl;
        if(filesystem::file_size(path)>DATA_LIMIT){
            cout << "size limit reached: " << DATA_LIMIT << "B\n" ;
            return;
        }
    }
    file.close();
}

template<typename T>
void chi(int n, string path, int precision, bool simulate){
    T min = 1.;
    int minind;
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
    if(is_same_v<T,float>)
        cout << "n: " << log10(7.341e-9)/log10(abs(golden/golden2));
    else if(is_same_v<T,double>)
        cout << "n: " << log10(2.429e-17)/log10(abs(golden/golden2));
    else if(is_same_v<T,long double>)
        cout << "n: " << log10(1.173e-21)/log10(abs(golden/golden2));
    
}

int main(int argc, char** argv){
    if(argc!=6){
        cout << "debug\n";
        return 1;
    }
        
    int arg = stoi(argv[1]);
    string path = argv[2];
    int option = stoi(argv[3]);
    int epsilon = stoi(argv[4]);
    int simulate = stoi(argv[5]);

    cout << option << endl;
    cout << path << endl;

    if(option == 0){
        delta<float>(arg,path,10,epsilon,0);
    }else if(option == 1){
        delta<double>(arg,path,20,epsilon,0);
    }else if(option == 2){
        delta<long double>(arg,path,30,epsilon,simulate);
    }else if(option==10){
        chi<float>(arg,path,10,0); 
    }else if(option==11){
        chi<double>(arg,path,20,0);
    }else if(option==12){
        chi<long double>(arg,path,30,simulate);
    }else
        cout << "debug" << endl;
    
    return 0;
}