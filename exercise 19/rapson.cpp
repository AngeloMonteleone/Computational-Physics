#include<iostream>
#include<vector>
#include<iomanip>
#include<cmath>
#include<algorithm>
#include "rootfinding.h"
#define MAX_ITER 100

using namespace std;
typedef long double ld;

ld pol2(ld x){
  return 2*x*x-3*x+1;
}

ld pol10(ld x){
  return (46189*powl(x,10) - 109395*powl(x,8) + 90090*powl(x,6) - 30030*powl(x,4) + 3465*powl(x,2) - 63)/256.;
}

ld der2(ld x){
  return 4*x-3;
}

ld der10(ld x){
  return (46189*10*powl(x,9) - 109395*8*powl(x,7) + 90090*6*powl(x,5) - 30030*4*powl(x,3) + 3465*2*x)/256.;
}

int main(int argc, char** argv){
  const int REQUIRED = 5;
  if (argc!=REQUIRED){
    return 1;
  }

  int max = stoi(argv[1]);
  ld inf = stold(argv[2]);
  ld sup = stold(argv[3]);
  int n = stoi(argv[4]);
  
  vector<ld> lower_bounds, upper_bounds;
  cout << setprecision(19) << endl;
  
  vector<ld> grid;
  // rapson(&pol2,&der2,inf,sup,max,&grid,n);
  rapson(&pol10,&der10,inf,sup,max,&grid,n);
  
  for(auto item:grid){
    cout << item << endl;
  }

  // ld accuracy = 1e-5;
  // sort(grid.begin(),grid.begin()+grid.size());
  // ld current=grid.at(0);
  // vector<ld> final_zeros = {current};

  // for(auto item:grid){
  //   cout << item << endl;
  //   if(item<current-accuracy || item>current+accuracy){
  //     current = item;
  //     final_zeros.push_back(item);
  //   }
  // }

  // cout << endl;
  // for(auto item:final_zeros){
  //   cout << item << endl;
  // }
  
  return 0;
}
