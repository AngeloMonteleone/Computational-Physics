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
T integral_Monte_Carlo_repeat(int N, ld a, ld b, ld (*func)(ld),int repeat,ld real){
    T tot=0.;
    for(int j=0;j<repeat;j++){
        tot+=fabsl(integral_Monte_Carlo<T>(N,a,b,func)-real);
    }
    
    return tot/repeat;
}

template<typename T>
T hit_miss(int N, ld x_min, ld x_max, ld y_min, ld y_max, ld (*func)(ld)){
  T area = fabsl((x_max-x_min)*(y_max-y_min));
  int N_hit = 0;
  T x_rand,y_rand;
  for(int i=0;i<N;i++){
    x_rand = uniform(x_min,x_max);
    y_rand = uniform(y_min,y_max);
    if(y_rand < func(x_rand)){
      N_hit++;
    }
  }
  return (area*(ld)N_hit)/N;
}

template<typename T>
T hit_miss_repeat(int N, ld x_min, ld x_max, ld y_min, ld y_max, ld (*func)(ld),int repeat,ld real){
  T tot=0;
  for(int j=0;j<repeat;j++){
    tot+=fabsl(hit_miss<T>(N,x_min,x_max,y_min,y_max,func)-real);
  }
  return tot/repeat;
}