#include<iostream>
#include<fstream>
#include<vector>
#include<iomanip>
#include<cmath>
#include<string>
#include<functional>

using namespace std;
typedef long double ld;

//masses {m0,m1,m2}
//vars {x0,y0,z0,x1,y1,z1,x2,y2,z2,vx0,vy0,vz0,vx1,vy1,vz1,vx2,vy2,vz2}

template<typename T>
T f_vel(int i, int axis, vector<T> masses, vector<T> vars){
  vector<T> coords0 = {vars[0],vars[1],vars[2]};
  vector<T> coords1 = {vars[3],vars[4],vars[5]};
  vector<T> coords2 = {vars[6],vars[7],vars[8]};

  vector<vector<T>> planet_coords = {coords0,coords1,coords2};

  vector<T> vels0 = {vars[9],vars[10],vars[11]};
  vector<T> vels1 = {vars[12],vars[13],vars[14]};
  vector<T> vels2 = {vars[15],vars[16],vars[17]};

  vector<vector<T>> planet_vels = {vels0,vels1,vels2};
  T ret = 0;
  T den;
  for(int j=0;j<=2;j++){
    if(j==i)
      continue;
    den = powl(planet_coords[i][0] - planet_coords[j][0],2) + powl(planet_coords[i][1] - planet_coords[j][1],2) + powl(planet_coords[i][2] - planet_coords[j][2],2);
    den = powl(den,1.5);
    ret -= masses[j]*(planet_coords[i][axis] - planet_coords[j][axis])/den;
  }
  return ret;
}

template<typename T>
T f_coord(int i, int axis, vector<T> masses, vector<T> vars){
  vector<T> coords0 = {vars[0],vars[1],vars[2]};
  vector<T> coords1 = {vars[3],vars[4],vars[5]};
  vector<T> coords2 = {vars[6],vars[7],vars[8]};

  vector<vector<T>> planet_coords = {coords0,coords1,coords2};

  vector<T> vels0 = {vars[9],vars[10],vars[11]};
  vector<T> vels1 = {vars[12],vars[13],vars[14]};
  vector<T> vels2 = {vars[15],vars[16],vars[17]};

  vector<vector<T>> planet_vels = {vels0,vels1,vels2};
  return planet_vels[i][axis];
}

template<typename T>
void integrator(ld timestep, int step_limit,vector<T> init_data,vector<T> pars,vector<function<ld(T, vector<T>, vector<T>)>> funcs,string path, string method,bool test_mode,vector<T(*)(T)> solutions){
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
      	k1[j]=timestep*funcs[j](t,vars,pars);
      }
      
      for(int j=0;j<init_data.size();j++){
	      vars[j]+=k1[j];
	      file << " " << vars[j];
      }
      
      file << endl;
    }else if(method=="rk2"){
      vector<T> k1(init_data.size(),0),k2(init_data.size(),0),temp(init_data.size(),0);
      file << t+timestep;
      for(int j=0;j<init_data.size();j++){
	      k1[j]=timestep*funcs[j](t,vars,pars);
      }

      for(int j=0;j<init_data.size();j++){
	      temp[j]=vars[j]+k1[j]/2.;
      }

      for(int j=0;j<init_data.size();j++){
	      k2[j]=timestep*funcs[j](t+timestep/2.,temp,pars);
      }

      for(int j=0;j<init_data.size();j++){
	      vars[j]+=k2[j];
	      file << " " << vars[j];
      }

      file << endl;
    }else if(method=="rk4"){
      vector<T> k1(init_data.size(),0),k2(init_data.size(),0),k3(init_data.size(),0),k4(init_data.size(),0),temp(init_data.size(),0);
      
      file << t+timestep;
      for(int j=0;j<init_data.size();j++){
	      k1[j]=timestep*funcs[j](t,vars,pars);
      }

      for(int j=0;j<init_data.size();j++){
	      temp[j]=vars[j]+k1[j]/2.;
      }

      for(int j=0;j<init_data.size();j++){
	      k2[j]=timestep*funcs[j](t+timestep/2.,temp,pars);
      }

      for(int j=0;j<init_data.size();j++){
	      temp[j]=vars[j]+k2[j]/2.;
      }

      for(int j=0;j<init_data.size();j++){
	      k3[j]=timestep*funcs[j](t+timestep/2.,temp,pars);
      }

      for(int j=0;j<init_data.size();j++){
	      temp[j]=vars[j]+k3[j];
      }

      for(int j=0;j<init_data.size();j++){
	      k4[j]=timestep*funcs[j](t+timestep,temp,pars);
      }

      for(int j=0;j<init_data.size();j++){
	      vars[j]+=(k1[j]+2*k2[j]+2*k3[j]+k4[j])/6.;
	      file << " " << vars[j];
      }
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

    vector<function<ld(ld,vector<ld>,vector<ld>)>> funcs;
    for(int i = 0;i<=2;i++){
      for(int axis = 0;axis<=2;axis++){
        auto func = [=](ld t, vector<ld> vars, vector<ld> pars){
          return f_vel<ld>(i,axis,pars,vars);
        };
        funcs.push_back(func);
      }
    }

    for(int i = 0;i<=2;i++){
      for(int axis = 0;axis<=2;axis++){
        auto func = [=](ld t, vector<ld> vars, vector<ld> pars){
          return f_coord<ld>(i,axis,pars,vars);
        };
        funcs.push_back(func);
      }
    }

    integrator<ld>(timestep,step_limit,{1,0,0,-1,0,0,0,0,0,0,.15,-.15,0,-.15,.5,0,0,0},{.3,.3,.3},funcs,"eulero.dat","eulero",0,{});
    integrator<ld>(timestep,step_limit,{1,0,0,-1,0,0,0,0,0,0,.15,-.15,0,-.15,.5,0,0,0},{.3,.3,.3},funcs,"rk2.dat","rk2",0,{});
    integrator<ld>(timestep,step_limit,{1,0,0,-1,0,0,0,0,0,0,.15,-.15,0,-.15,.5,0,0,0},{.3,.3,.3},funcs,"rk4.dat","rk4",0,{});

    return 0;
}
