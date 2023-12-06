#include<iostream>
#include<cmath>
#include<iomanip>
#include<fstream>
#include<vector>
#include"utilities.h"
#include"stat.h"
#define REAL_VAL3 (ld)(5040.-(648240./expl(5)))
#define REAL_VAL4 (ld)(-(1 - expl(5.) + expl(11.) - expl(16.))/(2 * expl(8)))
#define REAL_VAL5 (ld)(2736.+sinl(4)+sinl(32)-4.*cosl(4)-32.*cosl(32))/16.

#define LINE_LIMIT 1000000

using namespace std;

typedef long double ld;

ld f3(ld x){
    return powl(x,7)*expl(-x);
}

ld f4(ld x){
    return .5*(expl(x)+expl(-x));
}

ld f5(ld x){
    return (powl(x,2)+x*sinl(4*x));
}

ld hit_miss(int N, ld x_min, ld x_max, ld y_min, ld y_max, ld (*func)(ld)){
  ld area = fabsl((x_max-x_min)*(y_max-y_min));
  int N_hit = 0;
  ld x_rand,y_rand;
  for(int i=0;i<N;i++){
    x_rand = uniform(x_min,x_max);
    y_rand = uniform(y_min,y_max);
    if(y_rand < func(x_rand)){
      N_hit++;
    }
  }
  return (area*(ld)N_hit)/N;
}

ld hit_miss_repeat(int N, ld x_min, ld x_max, ld y_min, ld y_max, ld (*func)(ld),int repeat){
  ld area = (x_max-x_min)*(y_max-y_min);
  int N_hit = 0;
  ld x_rand,y_rand;
  ld mean=0;
  for(int j=0;j<repeat;j++){
    N_hit =0;
    for(int i=0;i<N;i++){
      x_rand = uniform(x_min,x_max);
      y_rand = uniform(y_min,y_max);
      if(y_rand < func(x_rand)){
	      N_hit++;
      }
    }
    mean+=(area*(ld)N_hit)/N;
  }
  
  return mean/repeat;
}

int main(int argc, char** argv){
  const int REQUIRED = 3;
  if(argc!= REQUIRED){
    cout << "wrong arguments" << endl;
    return 1;
  }
  int N = stoi(argv[1]);
  int step = stoi(argv[2]);
  ld val3 = REAL_VAL3;
  ld val4 = REAL_VAL4;
  ld val5 = REAL_VAL5;
  // vector<ld> data3hm, data4hm, data5hm;
  vector<ld> data3mc,data4mc,data5mc;
  vector<int> ascisse;
  for(int n= step;n<=N;n+=step){
    cout << n << endl;
    ascisse.push_back(n);
    // data3hm.push_back(fabsl(hit_miss_repeat(n,0,5,0,f3(5),&f3,50)-val3));
    // data4hm.push_back(fabsl(hit_miss_repeat(n,3,8,0,f4(8),&f4,50)-val4));
    // data5hm.push_back(fabsl(hit_miss_repeat(n,-1,8,0,80,&f5,50)-val5));

    data3mc.push_back(fabsl(integral_Monte_Carlo_repeat<ld>(n,0,5,&f3,200)-val3));
    data4mc.push_back(fabsl(integral_Monte_Carlo_repeat<ld>(n,3,8,&f4,200)-val4));
    data5mc.push_back(fabsl(integral_Monte_Carlo_repeat<ld>(n,-1,8,&f5,200)-val5));
  }

  // printInFile<int,ld>("int3hm.dat",ascisse,data3hm,15);
  // printInFile<int,ld>("int4hm.dat",ascisse,data4hm,15);
  // printInFile<int,ld>("int5hm.dat",ascisse,data5hm,15);
  printInFile<int,ld>("int3mc.dat",ascisse,data3mc,15);
  printInFile<int,ld>("int4mc.dat",ascisse,data4mc,15);
  printInFile<int,ld>("int5mc.dat",ascisse,data5mc,15);
}
