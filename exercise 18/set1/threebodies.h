#ifndef threebodies_h
#define threebodies_h

#include<iostream>
#include<fstream>
#include<vector>
#include<iomanip>
#include<cmath>
#include<string>
#include<functional>
#include"eqdiff.h"

using namespace std;
typedef long double ld;

//masses {m0,m1,m2}
//vars {x0,y0,z0,x1,y1,z1,x2,y2,z2,vx0,vy0,vz0,vx1,vy1,vz1,vx2,vy2,vz2}

template<typename T>
T modulo(vector<T> v){
  T ret = 0;
  for(auto v_i:v)
    ret+=(v_i*v_i);
  return sqrtl(ret);
}

template<typename T>
T potential_energy(T m_i, T m_j, vector<T> r_i, vector<T> r_j){
  T ret;
  vector<T> diff;
  for(int coord=0;coord<r_i.size();coord++){
    diff.push_back(r_i[coord]-r_j[coord]);
  }
  ret = -m_i*m_j/modulo(diff);
  return ret;
}

template<typename T>
T kinetic_energy(T m_i, vector<T> v_i){
  return .5*m_i*powl(modulo(v_i),2); 
}

template<typename T>
T total_energy(vector<T> masses, vector<T> vars){
  vector<T> coords0 = {vars[0],vars[1],vars[2]};
  vector<T> coords1 = {vars[3],vars[4],vars[5]};
  vector<T> coords2 = {vars[6],vars[7],vars[8]};

  vector<vector<T>> planet_coords = {coords0,coords1,coords2};

  vector<T> vels0 = {vars[9],vars[10],vars[11]};
  vector<T> vels1 = {vars[12],vars[13],vars[14]};
  vector<T> vels2 = {vars[15],vars[16],vars[17]};

  vector<vector<T>> planet_vels = {vels0,vels1,vels2};
  T tot_kinetic = 0;
  for(int i = 0; i<=2; i++){
    tot_kinetic += kinetic_energy<T>(masses[i],planet_vels[i]);
  }
  T tot_potential = 0;
  for(int i = 0; i<=2; i++){
    for(int j = 0; j<=2; j++){
      if(j==i)
	continue;
      tot_potential+=potential_energy<T>(masses[i],masses[j],planet_coords[i],planet_coords[j]);
    }
  }
  return (tot_kinetic+tot_potential);
}

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
void integrator3b(ld timestep, int step_limit,vector<T> init_data,vector<T> pars,vector<function<ld(T, vector<T>, vector<T>)>> funcs,string path, string method){
  if(step_limit>1000000  ||  init_data.size()!= funcs.size())
    return;
  vector<T> vars=init_data;
  void (*step)(ld t, ld timestep, vector<T>* vars,vector<T> pars,vector<function<ld(T, vector<T>, vector<T>)>> funcs);
  ofstream file;
  file << setprecision(10);
  file.open(path);
  ld t=0;

  if(method=="eulero"){
    step=eulero<T>;
  }else if(method=="rk2"){
    step=rk2<T>;
  }else if(method=="rk4"){
    step=rk4<T>;
  }else
    return;
  ofstream ener;
  ener << setprecision(10);
  ener.open("ener_"+path);
  for(int i=0;i<step_limit;i++){
    file << t+timestep << " ";
    step(t,timestep,&vars,pars,funcs);
    for(auto var:vars){
        file << var << " ";
    }
    file << endl;
    ener << t << " " << total_energy<T>(pars,vars) << endl;
    t+=timestep;
  }
  ener.close();
  file.close();
}

#endif