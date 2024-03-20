#include<iostream>
#include<fstream>
#include<vector>
#include<iomanip>
#include<cmath>
#include<string>
#include<functional>
#include"threebodies.h"

using namespace std;
typedef long double ld;

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

    vector<function<ld(ld,vector<ld>,vector<ld>)>> funcs;
    for(int i = 0;i<=2;i++){
      for(int axis = 0;axis<=2;axis++){
        auto func = [=](ld t, vector<ld> vars, vector<ld> pars){
          return f_coord<ld>(i,axis,pars,vars);
        };
        funcs.push_back(func);
      }
    }

    for(int i = 0;i<=2;i++){
      for(int axis = 0;axis<=2;axis++){
        auto func = [=](ld t, vector<ld> vars, vector<ld> pars){
          return f_vel<ld>(i,axis,pars,vars);
        };
        funcs.push_back(func);
      }
    }

    integrator3b<ld>(timestep,step_limit,{1,0,0,-1,0,0,0,0,0,0,.4,0,0,-0.8,0.7,0,-0.8,-0.7},{1.6,0.4,0.4},funcs,"eulero.dat","eulero");
    integrator3b<ld>(timestep,step_limit,{1,0,0,-1,0,0,0,0,0,0,.4,0,0,-0.8,0.7,0,-0.8,-0.7},{1.6,0.4,0.4},funcs,"rk2.dat","rk2");
    integrator3b<ld>(timestep,step_limit,{1,0,0,-1,0,0,0,0,0,0,.4,0,0,-0.8,0.7,0,-0.8,-0.7},{1.6,0.4,0.4},funcs,"rk4.dat","rk4");

    return 0;
}
