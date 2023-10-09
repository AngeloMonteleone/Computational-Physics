#include<iostream>
#include<iomanip>
#include<fstream>
#include<cmath>
#include<string>
#include<filesystem>

using namespace std;

typedef long long ll;

template<typename T>
T sum(int option, ll limit, T initValue, ll initIndex){
    T ret=initValue;
    if(option){
        for(int i=initIndex;i<limit+1;i+=1){
            ret+=1./static_cast<T>(pow(i,2));
        }
    }else{
        for(int i=limit;i>initIndex-1;i-=1){
            ret+=1./static_cast<T>(pow(i,2));
        }
    }
    return ret;
}

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
    // double dob = sum<double>(1,step,0,1),dobinv = sum<double>(0,step,0,1);
    // float fl = sum<float>(1,step,0,1),flinv = sum<float>(0,step,0,1);

    double conf = pow(M_PI,2)/6.0;

    // for(int i=step*2;i<=lim;i+=step){
    //     file << setprecision(20) << i << " ";

    //     // dobinv = sum<double>(0,i,dobinv,i-step+1);
    //     // file << abs(dobinv-conf) << " ";
    //     // dob = sum<double>(1,i,dob,i-step+1);
    //     // file << abs(dob-conf) << endl;

    //     flinv = sum<float>(0,i,flinv,i-step+1);//+1 per far partire da indice successivo
    //     file << abs(flinv - conf) << " ";
    //     fl = sum<float>(1,i,fl,i-step+1);
    //     file << abs(fl - conf) << endl;

    //     if(filesystem::file_size(path)>1000000){
    //         cout << "size limit reached 1MB\n";
    //         break;
    //     }
    // }
    int choice=stoi(argv[4]);
    ll i=step;
    cout << "data type: " << (choice?"double":"float") << endl;
    cout << "N: " << lim << endl;
    cout << "step: " << step << endl;
    while(i<=lim){
        file << i << " ";
        if(choice){
            file << setprecision(20) << abs(conf - sum_reg<double>(0,i)) << " ";
            file << abs(conf - sum_reg<double>(1,i)) << endl;
            i+=step;
        }else{
            file << setprecision(10) << abs(conf - sum_reg<float>(0,i)) << " ";
            file << abs(conf - sum_reg<float>(1,i)) << endl;
            i+=step;
        }
        
        if(filesystem::file_size(path)>1000000){
            cout << "size limit reached 1MB\n";
            return 1;
        }
    }
    cout << "file \'" << path << "\' size: " << filesystem::file_size(path) << endl;
    // cout << "machine epsilon: " << numeric_limits<float>::epsilon() << endl;
    file.close();
    return 0;
}