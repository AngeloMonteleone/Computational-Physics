#include<iostream>
#include<fstream>
#include<vector>
#include<iomanip>
#include<cmath>
#include<string>

using namespace std;
typedef long double ld;

//funzione utilizzata per l'incremento dell'angolo
ld f_theta(ld t,vector<ld> vars){
    return vars[1];
}

//funzione utilizzata per l'incremento della velocità
ld f_zeta(ld t,vector<ld> vars){
  return -sin(vars[0]);
}

//funzione utilizzata per l'incremento dell'angolo
ld f_theta2(ld t,vector<ld> vars){
    return vars[1];
}

//funzione utilizzata per l'incremento della velocità
ld f_zeta2(ld t,vector<ld> vars){
  ld gamma = .5;
  return -sin(vars[0])-gamma*vars[1];
}

//funzione utilizzata per l'incremento dell'angolo
ld f_theta3(ld t,vector<ld> vars){
    return vars[1];
}

//funzione utilizzata per l'incremento della velocità
ld f_zeta3(ld t,vector<ld> vars){
  ld gamma = .5;
  ld A = 1;
  return -sin(vars[0])-gamma*vars[1]+A*sin(2.*t/3.);
}

template<typename T>
void integrator(ld timestep, int step_limit,vector<T> init_data,vector<T(*)(T, vector<T>)> funcs,string path, string method,bool test_mode,vector<T(*)(T)> solutions){
  if(step_limit>1000000  ||  init_data.size()!= funcs.size())
    return;
  vector<T> vars=init_data;
  ofstream file;
  file << setprecision(10);
  file.open(path);

  ld t=0;

  for(int i=0;i<step_limit;i++){
    if(method=="eulero"){
      vector<T> k1(init_data.size(),0);
      file << t+timestep;
      for(int j=0;j<init_data.size();j++){
	      k1[j]=timestep*funcs[j](t,vars);
      }
      for(int j=0;j<init_data.size();j++){
	      vars[j]+=k1[j];
	      if(test_mode){
	        //cout << "real:" << solutions[j](t+timestep) << endl;
	        //cout << " num:" << vars[j] << endl;
	        file << " " << solutions[j](t+timestep)-vars[j];
	      }else
	        file << " " << vars[j];
      }
      file << endl;
    }else if(method=="rk2"){
      vector<T> k1(init_data.size(),0),k2(init_data.size(),0),temp(init_data.size(),0);
      file << t+timestep;
      for(int j=0;j<init_data.size();j++){
	      k1[j]=timestep*funcs[j](t,vars);
      }

      for(int j=0;j<init_data.size();j++){
	      temp[j]=vars[j]+k1[j]/2.;
      }

      for(int j=0;j<init_data.size();j++){
	      k2[j]=timestep*funcs[j](t+timestep/2.,temp);
      }

      for(int j=0;j<init_data.size();j++){
	      vars[j]+=k2[j];
	    if(test_mode)
	      file << " " << solutions[j](t+timestep)-vars[j];
	    else
	      file << " " << vars[j];
      }
      file << endl;
    }else if(method=="rk4"){
      vector<T> k1(init_data.size(),0),k2(init_data.size(),0),k3(init_data.size(),0),k4(init_data.size(),0),temp(init_data.size(),0);
      //string line=to_string(t+timestep);
      file << t+timestep;
      for(int j=0;j<init_data.size();j++){
	      k1[j]=timestep*funcs[j](t,vars);
      }

      for(int j=0;j<init_data.size();j++){
	      temp[j]=vars[j]+k1[j]/2.;
      }

      for(int j=0;j<init_data.size();j++){
	      k2[j]=timestep*funcs[j](t+timestep/2.,temp);
      }

      for(int j=0;j<init_data.size();j++){
	      temp[j]=vars[j]+k2[j]/2.;
      }

      for(int j=0;j<init_data.size();j++){
	      k3[j]=timestep*funcs[j](t+timestep/2.,temp);
      }

      for(int j=0;j<init_data.size();j++){
	      temp[j]=vars[j]+k3[j];
      }

      for(int j=0;j<init_data.size();j++){
	      k4[j]=timestep*funcs[j](t+timestep,temp);
      }

      for(int j=0;j<init_data.size();j++){
	      vars[j]+=(k1[j]+2*k2[j]+2*k3[j]+k4[j])/6.;
	    if(test_mode)
	      file << " " << solutions[j](t+timestep)-vars[j];
	      //line+=" " + to_string(solutions[j](t+timestep)-vars[j]);
	    else
	      file << " " << vars[j];
	      //line+=" " + to_string(vars[j]);
      }
      //file << line << endl;
      file<<endl;
    }else
      return;
      
    t+=timestep;
  }
  file.close();
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
    int step_limit = stoi(argv[2]);
    

    //OSCILLATORE ARMONICO
    //integrator<ld>(timestep,step_limit,{0,1},{&f_theta,&f_zeta},"testeulero.dat","eulero",1,{&sol_theta,&sol_zeta});
    integrator<ld>(timestep,step_limit,{0,1},{&f_theta,&f_zeta},"semplice/eulero.dat","eulero",0,{});
    //integrator<ld>(timestep,step_limit,{0,1},{&f_theta,&f_zeta},"testrk2.dat","rk2",1,{&sol_theta,&sol_zeta});
    integrator<ld>(timestep,step_limit,{0,1},{&f_theta,&f_zeta},"semplice/rk2.dat","rk2",0,{});
    //integrator<ld>(timestep,step_limit,{0,1},{&f_theta,&f_zeta},"testrk4.dat","rk4",1,{&sol_theta,&sol_zeta});
    integrator<ld>(timestep,step_limit,{0,1},{&f_theta,&f_zeta},"semplice/rk4.dat","rk4",0,{});

    //OSCILLATORE ARMONICO SMORZATO
    integrator<ld>(timestep,step_limit,{0,1},{&f_theta2,&f_zeta2},"smorzato/eulero.dat","eulero",0,{});
    integrator<ld>(timestep,step_limit,{0,1},{&f_theta2,&f_zeta2},"smorzato/rk2.dat","rk2",0,{});
    integrator<ld>(timestep,step_limit,{0,1},{&f_theta2,&f_zeta2},"smorzato/rk4.dat","rk4",0,{});
    
    //OSCILLATORE ARMONICO FORZATO
    integrator<ld>(timestep,step_limit,{0,1},{&f_theta3,&f_zeta3},"forzato/eulero.dat","eulero",0,{});
    integrator<ld>(timestep,step_limit,{0,1},{&f_theta3,&f_zeta3},"forzato/rk2.dat","rk2",0,{});
    integrator<ld>(timestep,step_limit,{0,1},{&f_theta3,&f_zeta3},"forzato/rk4.dat","rk4",0,{});

    return 0;
}
