#include<iostream>
#include<cmath>
#include<vector>
#include<fstream>
#include<iomanip>
#include "stat.h"
//#include "utilities.h"
#define LINE_LIMIT 1000000

using namespace std;
typedef long double ld;

template<typename T>
void printInFile(string path, vector<T> first_col, int precision){
    ofstream file;
    file << setprecision(precision);
    file.open(path);
    unsigned int N_rows = first_col.size();
    
    for(unsigned int i = 0; i<N_rows; i++){
        file << first_col[i] << endl;
	if(i>LINE_LIMIT){
	  cout << "OVER LINE LIMIT" << endl;
	  return;
	}
	  
    }
    file.close();
}

template<typename T>
void printvec(vector<T> vec){
    for(auto& elem : vec){
        cout << elem << " ";
    }
    cout << endl;
}

ld cdf1(ld y){
  const ld A = powl(M_E,2)/(1-powl(M_E,2));
  return log(A/(y+A));
}

ld cdf2(ld y){
  return 1-log(1-y);
}

ld cdf3(ld y){
return sqrtl(log(1/(1-y)));
}

int main(int argc, char** argv){
  const int REQUIRED = 2;
  if(argc!=REQUIRED){
    cout<< "wrong arguments" << endl;
    return 1;
  }
  
  int N = stoi(argv[1]);
vector<ld> data1,data2,data3;
  ld y_i;
  for(int i=0;i<N;i++){
    y_i = uniform(0,1);
    data1.push_back(cdf1(y_i));
    y_i = uniform(0,1);
    data2.push_back(cdf2(y_i));
    y_i = uniform(0,1);
    data3.push_back(cdf3(y_i));
  }

//printvec(data);
  printInFile<ld>("cdf1.dat",data1,17);
  printInFile<ld>("cdf2.dat",data2,17);
  printInFile<ld>("cdf3.dat",data3,17);
  return 0;
}
