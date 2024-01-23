#include<iostream>
#include<cmath>
#include<vector>

typedef long long ll;
typedef long double ld;
typedef short int sint;

using namespace std;

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

template<typename T>
T integral_Monte_Carlo(int N, ld a, ld b, ld (*func)(ld)){
    T ret=0.;
    T point;
    for(int i=0;i<N;i++){
        point = uniform(a,b);
        ret+=func(point);
    }
    return ret*(b-a)/N;
}

template<typename T>
T integral_Monte_Carlo_repeat(int N, ld a, ld b, ld (*func)(ld),int repeat){
    T ret=0.;
    T point;
    T tot = 0;
    for(int j=0;j<repeat;j++){
        for(int i=0;i<N;i++){
            point = uniform(a,b);
            ret+=func(point);
        }
        tot+=ret*(b-a)/N;
        ret=0;
    }
    
    return tot/repeat;
}