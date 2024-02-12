#include<iostream>
#include<fstream>
#include<vector>
#include<iomanip>
#include<cmath>
#include<string>
#include<functional>
#include "eqdiff.h"

using namespace std;
typedef long double ld;

//funzione utilizzata per l'incremento dell'angolo
ld f_theta(ld t,ld theta,ld zeta){
    return zeta;
}

//funzione utilizzata per l'incremento della velocità
ld f_zeta(ld t,ld theta,ld zeta){
    return -theta;
}

//funzione utilizzata per l'incremento dell'angolo
ld f_theta2(ld t,vector<ld> vars, vector<ld> pars){
    return vars[1];
}

//funzione utilizzata per l'incremento della velocità
ld f_zeta2(ld t,vector<ld> vars, vector<ld> pars){
    return -vars[0];
}

ld sol_theta(ld t){
  return sin(t);
}

ld sol_zeta(ld t){
  return cos(t);
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
    ld time_limit = stoi(argv[2]);
    int step_limit = time_limit/timestep;
    
    // integrator<ld>(timestep,step_limit,{0,1},{},{&f_theta2,&f_zeta2},"eulero.dat","eulero");
    // integrator<ld>(timestep,step_limit,{0,1},{},{&f_theta2,&f_zeta2},"rk2.dat","rk2");
    // integrator<ld>(timestep,step_limit,{0,1},{},{&f_theta2,&f_zeta2},"rk4.dat","rk4");

    remove("testeulero.dat");
    remove("testrk2.dat");
    remove("testrk4.dat");
    for(;timestep<=0.1;timestep*=1.2){
        cout << timestep << endl;
        step_limit = time_limit/timestep;
        integrator_test<ld>(timestep,step_limit,{0,1},{},{&f_theta2,&f_zeta2},"testeulero.dat","eulero",1.57,{&sol_theta,&sol_zeta});
        integrator_test<ld>(timestep,step_limit,{0,1},{},{&f_theta2,&f_zeta2},"testrk2.dat","rk2",1.57,{&sol_theta,&sol_zeta});
        integrator_test<ld>(timestep,step_limit,{0,1},{},{&f_theta2,&f_zeta2},"testrk4.dat","rk4",1.57,{&sol_theta,&sol_zeta});
    }

    return 0;
}