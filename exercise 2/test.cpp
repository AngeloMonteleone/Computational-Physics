#include<iostream>
#include<iomanip>
#include<fstream>
#include<cmath>
#include<string>
#include<filesystem>

using namespace std;

typedef long long ll;

long double pot(int a, int b){
    long double ret = a;
    for(int i=1;i<abs(b);i++)
        ret*=a;
    return (b>0?ret:1.0/ret);
}

int main(int argc, char** argv){
    long double test = pot(2,stoi(argv[1]));
    long double ris = 1.0;
    cout << sizeof(__float128) << endl;
    cout<< "somma di prova: " << setprecision(30) << (ris + test) << endl;
    return 0;
}