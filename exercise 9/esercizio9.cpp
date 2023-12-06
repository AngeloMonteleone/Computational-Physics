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
  const int REQUIRED = 4;
  if(argc!=REQUIRED){
    cout << "wrong arguments" << endl;
    return 1;
  }
  int M = stoi(argv[1]);
  int N = stoi(argv[2]);
  int esp = stoi(argv[3]);

  vector<ld> data_coin,data_unif,ascisse,current_moment_coin,current_moment_unif;
  for(int j=1; j<N; j++){
    data_coin = {};
    data_unif = {};
    for(int i=0;i<M;i++){
      data_coin.push_back(coin_to_gauss(j));
      data_unif.push_back(uniform_to_gauss(j,-1,1));
    }
      ascisse.push_back(j);
      // current_moment_coin.push_back(moment<ld>(data_coin,esp)/moment<ld>(data_coin,esp-2));
      // current_moment_unif.push_back(moment<ld>(data_unif,esp)/moment<ld>(data_unif,esp-2));
      current_moment_coin.push_back(moment<ld>(data_coin,esp));
      current_moment_unif.push_back(moment<ld>(data_unif,esp));
  }
  
  // printInFile<ld>("coin.dat",data_coin,15);
  // printInFile<ld>("unif.dat",data_unif,15);
  printInFile<ld,ld>("mom_unif" + to_string(esp) + ".dat",ascisse,current_moment_unif,15);
  printInFile<ld,ld>("mom_coin" + to_string(esp) + ".dat",ascisse,current_moment_coin,15);
  return 0;
}
