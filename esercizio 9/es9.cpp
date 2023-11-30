#include<iostream>
#include<cmath>
#include<vector>
#include<fstream>
#include<iomanip>
#include"utilities.h"

using namespace std;
typedef short int sint;
typedef long double ld;

sint coin(){
  float num = (float)rand()/RAND_MAX;
  //cout << num << endl; 
  if(num < 0.5)
    return -1;
  return 1;
}

ld coin_to_gauss(int N){
  ld mean = 0.;
  for(int i=0; i<N;i++){
    mean+=coin();
  }
  //cout << "test: " << mean/M << endl;
  return mean/N;
}

ld uniform(ld a, ld b){
  ld ret = a + (b-a)*(ld)rand()/RAND_MAX;
  return ret;
}

ld uniform_to_gauss(int N,ld a,ld b){
  ld mean = 0.;
  for(int i=0; i<N;i++){
    mean+=uniform(a,b);
  }
  // cout << "test: " << mean/N << endl;
  return mean/N;
}

template<typename T>
T moment(vector<T> data,int esp){
  T ret = 0;
  T mean = 0;
  
  for(int i = 0; i<data.size();i++){
    mean+= data.at(i);
  }
  mean/=data.size();

  for(int i = 0; i<data.size();i++){
    ret+= powl(data.at(i)-mean,esp);
  }
  //cout << ret << endl;
  return ret/data.size();
}

int main(int argc, char** argv){
  srand(time(NULL));
  const int REQUIRED = 3;
  if(argc!=REQUIRED){
    cout << "wrong arguments" << endl;
    return 1;
  }
  int M = stoi(argv[1]);
  int N = stoi(argv[2]);
  vector<ld> data;
  vector<ld> tcl;
  vector<int> ascisse;
  ld temp = 0;
  for(int i=0;i<M;i++){
    data.push_back(uniform_to_gauss(N,-1,1));
  }

  for(int i=1;i<=N && i<M;i++){
    temp=0;
    ascisse.push_back(i);
    for(int j=0;j<i;j++){
        temp+=data.at(j);
    }
    tcl.push_back(temp/i);
  }
  printInFile<ld>("unif.dat",tcl,15);
  return 0;
}