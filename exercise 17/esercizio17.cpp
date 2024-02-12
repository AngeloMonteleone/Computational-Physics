#include<iostream>
#include<fstream>
#include<vector>
#include<iomanip>
#include<cmath>
#include<string>
#include"eqdiff.h"

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
    //numero di parametri richiesti dal programma
    const int REQUIRED = 3;
    if(argc!=REQUIRED){
        cout<< "wrong arguments" << endl;
        return 1;
    }
    
    //il primo parametro passato è l'incremento temporale da usare, il secondo è il limite di step da usare
    ld timestep = stold(argv[1]);
    int step_limit = stoi(argv[2]);
    ld noise = 10e-7;
    //Condizione utilizzata per lo studio dell'equilibrio instabile
    vector<ld> init = {6.*sqrtl(2),6.*sqrtl(2),27+noise};
    //Condizioni iniziali inserite da line adi comando
    // vector<ld> init = {stold(argv[3]),stold(argv[4]),stold(argv[5])};

    integrator<ld>(timestep,step_limit,init,{},{&fx,&fy,&fz},"eulero.dat","eulero");
    integrator<ld>(timestep,step_limit,init,{},{&fx,&fy,&fz},"rk2.dat","rk2");
    integrator<ld>(timestep,step_limit,init,{},{&fx,&fy,&fz},"rk4.dat","rk4");

    return 0;
}
