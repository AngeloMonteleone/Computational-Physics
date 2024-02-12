#include<iostream>
#include<fstream>
#include<vector>
#include<iomanip>
#include<cmath>
#include<string>
#include"eqdiff.h"

using namespace std;
typedef long double ld;

//funzione utilizzata per l'incremento dell'angolo
ld f_theta(ld t,vector<ld> vars,vector<ld> pars){
    return vars[1];
}

//funzione utilizzata per l'incremento della velocità
ld f_zeta(ld t,vector<ld> vars,vector<ld> pars){
  return -pars[2]*vars[1] -(pars[0]-pars[1]*cos(t))*sin(vars[0]);
}

int main(int argc, char** argv){
    //numero di parametri richiesti dal programma
    const int REQUIRED = 6;
    if(argc!=REQUIRED){
        cout<< "wrong arguments" << endl;
        return 1;
    }
    
    //il primo parametro passato è l'incremento temporale da usare, il secondo è il limite di step da usare
    ld timestep = stold(argv[1]);
    int step_limit = stoi(argv[2]);
    vector<ld> pars = {stold(argv[3]),stold(argv[4]),stold(argv[5])};

    integrator<ld>(timestep,step_limit,{0,.1},pars,{&f_theta,&f_zeta},"eulero.dat","eulero");
    integrator<ld>(timestep,step_limit,{0,.1},pars,{&f_theta,&f_zeta},"rk2.dat","rk2");
    integrator<ld>(timestep,step_limit,{0,.1},pars,{&f_theta,&f_zeta},"rk4.dat","rk4");

    return 0;
}
