#include<iostream>
#include<fstream>
#include<vector>
#include<iomanip>
#include<cmath>
#include<string>

using namespace std;
typedef long double ld;

ld fx(ld t,vector<ld> vars){
  return -10*(vars[0]-vars[1]);
}

ld fy(ld t,vector<ld> vars){
  return -vars[0]*vars[2]+28*vars[0]-vars[1];
}

ld fz(ld t,vector<ld> vars){
  return vars[0]*vars[1]-8.*vars[2]/3.;
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
    vector<ld> init = {stold(argv[3]),stold(argv[4]),stold(argv[5])};
    integrator<ld>(timestep,step_limit,init,{&fx,&fy,&fz},"eulero.dat","eulero",0,{});
    integrator<ld>(timestep,step_limit,init,{&fx,&fy,&fz},"rk2.dat","rk2",0,{});
    integrator<ld>(timestep,step_limit,init,{&fx,&fy,&fz},"rk4.dat","rk4",0,{});

    return 0;
}
