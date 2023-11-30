#include<iostream>
#include<cmath>
#include<iomanip>
#include<fstream>
#include<vector>
#define REAL_VAL3 (ld)(5040.-(648240./expl(5)))
#define REAL_VAL4 (ld)(-(1 - expl(5.) + expl(11.) - expl(16.))/(2 * expl(8)))
#define REAL_VAL5 (ld)(2736.+sinl(4)+sinl(32)-4.*cosl(4)-32.*cosl(32))/16.

#define LINE_LIMIT 1000000

using namespace std;

typedef long double ld;

template<typename T1,typename T2>
void printInFile(string path, vector<T1> first_col, vector<T2> second_col, int precision){
    if(first_col.size()!=second_col.size()){
        cout << "ERRORE: vettori di dimensione diversa!" << endl;
        return;
    }
    ofstream file;
    file << setprecision(precision);
    file.open(path);
    unsigned int N_rows = first_col.size();
    
    for(unsigned int i = 0; i<N_rows; i++){
        file << first_col[i] << " " << second_col[i] << endl;
        if(i>LINE_LIMIT){
	  cout << "OVER LINE LIMIT" << endl;
	  return;
	}
    }
    file.close();
}

ld f3(ld x){
    return powl(x,7)*expl(-x);
}

ld f4(ld x){
    return .5*(expl(x)+expl(-x));
}

ld f5(ld x){
    return (powl(x,2)+x*sinl(4*x));
}

ld uniform(ld a, ld b){
  ld ret = a + (b-a)*(ld)rand()/RAND_MAX;
  return ret;
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
  vector<ld> data3hm, data4hm, data5hm;
  vector<int> ascisse;
  for(int n= step;n<=N;n+=step){
    cout << n << endl;
    ascisse.push_back(n);
    data3hm.push_back(fabsl(hit_miss_repeat(n,0,5,0,f3(5),&f3,50)-val3));
    data4hm.push_back(fabsl(hit_miss_repeat(n,3,8,0,f4(8),&f4,50)-val4));
    data5hm.push_back(fabsl(hit_miss_repeat(n,-1,8,0,80,&f5,50)-val5));
  }

  printInFile<int,ld>("int3hm.dat",ascisse,data3hm,15);
  printInFile<int,ld>("int4hm.dat",ascisse,data4hm,15);
  printInFile<int,ld>("int5hm.dat",ascisse,data5hm,15);
}
