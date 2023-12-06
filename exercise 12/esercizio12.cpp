#include<iostream>
#include<cmath>
#include<vector>
#include<fstream>
#include<iomanip>
#include<limits>
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

ld cdf(ld y){
  return sqrtl(-log(1-y));
}

ld gaussian_var(ld alpha, ld y){
  return cos(2*M_PI*alpha)*cdf(y);
}

ld pdfAR(ld x){
  if(x>=0 && x<=1)
    return 2./3.;
  else if(x>1)
    return x*exp(1-x*x)*2./3.;
  return numeric_limits<double>::quiet_NaN();
}

ld cdfAR(ld y){
  if(y>=0 && y<=2./3.)
    return y*3./2.;
  else if(y>2./3. && y <=1)
    return sqrtl(1-log(3-3*y));
  return numeric_limits<double>::quiet_NaN();
}

ld gauss(ld x){
  return exp(-x*x)/(sqrtl(M_PI));//CONTROLLA NORMALIZZAZIONE
}

int main(int argc, char** argv){
  const int REQUIRED = 2;
  if(argc!=REQUIRED){
    cout<< "wrong arguments" << endl;
    return 1;
  }
  
  int N = stoi(argv[1]);
  vector<ld> data;
  ld y_i,a_i;
  for(int i=0;i<N;i++){
    y_i = uniform(0,1);
    a_i = uniform(0,1);
    data.push_back(gaussian_var(a_i,y_i));
  }

//printvec(data);
  printInFile<ld>("cdf.dat",data,17);
  
  vector<ld> dataAR;
  ld x_i;
  for(int i=0;i<N;i++){
    y_i = uniform(0,1);
    // cout << "drawn y: " << y_i << endl;
    x_i = cdfAR(y_i);
    // cout << "generated x: " << x_i << endl;
    y_i = uniform(0,pdfAR(x_i));
    // cout << "drawn y: " << y_i << endl;
    // cout << "gauss: " << gauss(x_i) << endl;
    if(y_i<gauss(x_i)){
      // cout << "not reject " << i << endl;
      dataAR.push_back(x_i);
      dataAR.push_back(-x_i);
    }//else
      // cout << "reject " << i << endl;
  }

  printInFile<ld>("gaussAR.dat",dataAR,17);
  return 0;
}
