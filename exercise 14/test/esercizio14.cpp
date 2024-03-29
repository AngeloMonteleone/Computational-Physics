#include<iostream>
#include<fstream>
#include<vector>
#include<iomanip>
#include<cmath>
#include<string>

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

//metodo di eulero per ODE del primo ordine
void eulero_ord1(ld timestep, int step_limit,ld x_0,ld (*func_x)(ld,ld),string path){
    if(step_limit > 1000000)
        return;
    
    ld t = 0.;
    ld x_n=x_0;
    ld x_np1;
    
    ofstream file;
    file << setprecision(10);
    file.open(path);
    
    for(int i= 0;i<step_limit;i++){
        x_np1 = x_n + timestep*func_x(t,x_n);
        file << t << " " << x_n << endl;
        x_n = x_np1;
        
        t+=timestep;
    }

    file.close();
}

//metodo di eulero per ODE del secondo ordine
void eulero_ord2(ld timestep, int step_limit,ld x_0,ld y_0,ld (*func_x)(ld,ld,ld),ld (*func_y)(ld,ld,ld),string path){
    if(step_limit > 1000000)
        return;
    
    ld t = 0.;
    ld y_n = y_0, x_n=x_0;
    ld y_np1,x_np1;
    
    ofstream file;
    file << setprecision(10);
    file.open(path);
    
    for(int i= 0;i<step_limit;i++){
        x_np1 = x_n + timestep*func_x(t,x_n,y_n);
        y_np1 = y_n + timestep*func_y(t,x_n,y_n);
        file << t << " " << x_n << " " << y_n << endl;
        
        //assegnazione valore per step successivo
        y_n = y_np1;
        x_n = x_np1;
        t+=timestep;
    }

    file.close();
}

//metodo runge_kutta2 per ODE del secondo ordine
void rk2_ord2(ld timestep, int step_limit,ld x_0,ld y_0,ld (*func_x)(ld,ld,ld),ld (*func_y)(ld,ld,ld),string path){
    if(step_limit > 1000000)
        return;
    
    ld t = 0.;
    ld y_n = y_0, x_n=x_0;
    ld y_np1,x_np1,k_x1,k_x2,k_y1,k_y2;
    
    ofstream file;
    file << setprecision(10);
    file.open(path);
    
    for(int i= 0;i<step_limit;i++){
        //calcolo step intermedi
        k_x1=timestep*func_x(t,x_n,y_n);
        k_y1=timestep*func_y(t,x_n,y_n);
        k_x2=timestep*func_x(t+timestep/2.,x_n+k_x1/2.,y_n+k_y1/2.);
        k_y2=timestep*func_y(t+timestep/2.,x_n+k_x1/2.,y_n+k_y1/2.);

        //aggiornamento delle variabili d'interesse e stampa nel file
        x_np1 = x_n + k_x2;
        y_np1 = y_n + k_y2;
        file << t << " " << x_n << " " << y_n << endl;

        //assegnazione valore per step successivo
        y_n = y_np1;
        x_n = x_np1;
        t+=timestep;
    }

    file.close();
}

//metodo runge_kutta4 per ODE del secondo ordine
void rk4_ord2(ld timestep, int step_limit,ld x_0,ld y_0,ld (*func_x)(ld,ld,ld),ld (*func_y)(ld,ld,ld),string path){
    if(step_limit > 1000000)
        return;
    
    ld t = 0.;
    ld y_n = y_0, x_n=x_0;
    ld y_np1,x_np1,k_x1,k_x2,k_y1,k_y2,k_x3,k_y3,k_x4,k_y4;
    
    ofstream file;
    file << setprecision(10);
    file.open(path);
    
    for(int i= 0;i<step_limit;i++){
        //calcolo step intermedi
        k_x1=timestep*func_x(t,x_n,y_n);
        k_y1=timestep*func_y(t,x_n,y_n);
        k_x2=timestep*func_x(t+timestep/2.,x_n+k_x1/2.,y_n+k_y1/2.);
        k_y2=timestep*func_y(t+timestep/2.,x_n+k_x1/2.,y_n+k_y1/2.);
        k_x3=timestep*func_x(t+timestep/2.,x_n+k_x2/2.,y_n+k_y2/2.);
        k_y3=timestep*func_y(t+timestep/2.,x_n+k_x2/2.,y_n+k_y2/2.);
        k_x4=timestep*func_x(t+timestep,x_n+k_x3,y_n+k_y3);
        k_y4=timestep*func_y(t+timestep,x_n+k_x3,y_n+k_y3);

        //aggiornamento delle variabili d'interesse e stampa nel file
        x_np1 = x_n + (k_x1+2*k_x2+2*k_x3+k_x4)/6.;
        y_np1 = y_n + (k_y1+2*k_y2+2*k_y3+k_y4)/6.;
        file << t << " " << x_n << " " << y_n << endl;

        //assegnazione valore per step successivo
        y_n = y_np1;
        x_n = x_np1;

        t+=timestep;
    }

    file.close();
}

//funzione utilizzata per l'incremento dell'angolo
ld f_theta2(ld t,vector<ld> vars){
    return vars[1];
}

//funzione utilizzata per l'incremento della velocità
ld f_zeta2(ld t,vector<ld> vars){
    return -vars[0];
}

ld sol_theta(ld t){
  return sin(t);
}

ld sol_zeta(ld t){
  return cos(t);
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
        }
        else
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
    
    integrator<ld>(timestep,step_limit,{0,1},{&f_theta2,&f_zeta2},"testeulero.dat","eulero",1,{&sol_theta,&sol_zeta});
    integrator<ld>(timestep,step_limit,{0,1},{&f_theta2,&f_zeta2},"eulero.dat","eulero",0,{});
    integrator<ld>(timestep,step_limit,{0,1},{&f_theta2,&f_zeta2},"testrk2.dat","rk2",1,{&sol_theta,&sol_zeta});
    integrator<ld>(timestep,step_limit,{0,1},{&f_theta2,&f_zeta2},"rk2.dat","rk2",0,{});
    integrator<ld>(timestep,step_limit,{0,1},{&f_theta2,&f_zeta2},"testrk4.dat","rk4",1,{&sol_theta,&sol_zeta});
    integrator<ld>(timestep,step_limit,{0,1},{&f_theta2,&f_zeta2},"rk4.dat","rk4",0,{});
    //integrator<ld>(timestep,step_limit,{0,1},{&f_theta2,&f_zeta2},"rk2.dat","rk2");
    //integrator<ld>(timestep,step_limit,{0,1},{&f_theta2,&f_zeta2},"rk4.dat","rk4");
    
    // eulero_ord2(timestep,step_limit,0,1,&f_theta,&f_zeta,"prova_eulero.dat");
    //rk2_ord2(timestep,step_limit,0,1,&f_theta,&f_zeta,"prova_rk2.dat");
    //rk4_ord2(timestep,step_limit,0,1,&f_theta,&f_zeta,"prova_rk4.dat");

    return 0;
}
