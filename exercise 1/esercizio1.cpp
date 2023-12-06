#include<iostream>
#include<iomanip>
#include<fstream>
#include<cmath>
#include<string>
#include<filesystem>

using namespace std;

typedef long long ll;

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
    if(argc!=5)
        return 1;

    ll lim=stoll(argv[1]);
    ll step=stoi(argv[2]);
    string path = argv[3];
    
    ofstream file;
    file.open(path);

    float conf_float = pow(M_PI,2)/6.0;
    double conf_double = pow(M_PI,2)/6.0;

    int choice=stoi(argv[4]);
    ll i=step;
    cout << "data type: " << (choice?"double":"float") << endl;
    cout << "N: " << lim << endl;
    cout << "step: " << step << endl;
    while(i<=lim){
        file << i << " ";
        if(choice){
            file << setprecision(20) << abs(conf_double - sum_reg<double>(0,i)) << " ";
            file << abs(conf_double - sum_reg<double>(1,i)) << endl;
            i*=step;
        }else{
            file << setprecision(10) << abs(conf_float - sum_reg<float>(0,i)) << " ";
            file << abs(conf_float - sum_reg<float>(1,i)) << endl;
            i+=step;
        }
        
        if(filesystem::file_size(path)>1000000){
            cout << "size limit reached 1MB\n";
            return 1;
        }
    }
    cout << "file \'" << path << "\' size: " << filesystem::file_size(path) << endl;
    file.close();
    return 0;
}