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
  return -sin(vars[0]);
}

//funzione utilizzata per l'incremento dell'angolo
ld f_theta2(ld t,vector<ld> vars,vector<ld> pars){
    return vars[1];
}

//funzione utilizzata per l'incremento della velocità
ld f_zeta2(ld t,vector<ld> vars,vector<ld> pars){
  ld gamma = pars[0];
  return -sin(vars[0])-gamma*vars[1];
}

//funzione utilizzata per l'incremento dell'angolo
ld f_theta3(ld t,vector<ld> vars,vector<ld> pars){
    return vars[1];
}

//funzione utilizzata per l'incremento della velocità
ld f_zeta3(ld t,vector<ld> vars,vector<ld> pars){
  ld gamma = pars[0];
  ld A = pars[1];
  return -sin(vars[0])-gamma*vars[1]+A*sin(2.*t/3.);
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

    //OSCILLATORE ARMONICO
    integrator<ld>(timestep,step_limit,{0,1},{},{&f_theta,&f_zeta},"semplice/eulero.dat","eulero");
    integrator<ld>(timestep,step_limit,{0,1},{},{&f_theta,&f_zeta},"semplice/rk2.dat","rk2");
    integrator<ld>(timestep,step_limit,{0,1},{},{&f_theta,&f_zeta},"semplice/rk4.dat","rk4");

    //OSCILLATORE ARMONICO SMORZATO
    integrator<ld>(timestep,step_limit,{0,1},{.5},{&f_theta2,&f_zeta2},"smorzato/eulero.dat","eulero");
    integrator<ld>(timestep,step_limit,{0,1},{.5},{&f_theta2,&f_zeta2},"smorzato/rk2.dat","rk2");
    integrator<ld>(timestep,step_limit,{0,1},{.5},{&f_theta2,&f_zeta2},"smorzato/rk4.dat","rk4");
    
    //OSCILLATORE ARMONICO FORZATO
    integrator<ld>(timestep,step_limit,{0,1},{.5,1},{&f_theta3,&f_zeta3},"forzato/eulero.dat","eulero");
    integrator<ld>(timestep,step_limit,{0,1},{.5,1},{&f_theta3,&f_zeta3},"forzato/rk2.dat","rk2");
    integrator<ld>(timestep,step_limit,{0,1},{.5,1},{&f_theta3,&f_zeta3},"forzato/rk4.dat","rk4");

    return 0;
}
