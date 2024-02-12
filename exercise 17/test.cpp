#include<iostream>
#include<vector>
#include<iomanip>
#include<cmath>

using namespace std;
typedef long double ld;

ld fx(ld t,vector<ld> vars,vector<ld> pars){
  return -10*(vars[0]-vars[1]);
}

ld fy(ld t,vector<ld> vars,vector<ld> pars){
  return -vars[0]*vars[2]+28*vars[0]-vars[1];
}

ld fz(ld t,vector<ld> vars,vector<ld> pars){
  return vars[0]*vars[1]-8.*vars[2]/3.;
}

int main(int argc, char** argv){
    vector<ld> init = {6.*sqrtl(2),6.*sqrtl(2),27};
    cout << setprecision(17) << endl;
    for(auto elem:init){
        cout << elem << endl;
    }
    cout << endl;

    cout << "f_x=" << fx(0,init,{}) << endl;
    cout << "f_y=" << fy(0,init,{}) << endl;
    cout << "f_z=" << fz(0,init,{}) << endl;

    return 0;
}
