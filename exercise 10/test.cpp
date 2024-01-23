#include<iostream>
#include<cmath>
#include<iomanip>
#include<fstream>
#include<vector>
#define REAL_VAL3 (ld)(5040.-(648240./expl(5)))
#define REAL_VAL4 (ld)(-(1 - expl(5.) + expl(11.) - expl(16.))/(2 * expl(8)))
#define REAL_VAL5 (ld)(2736.+sinl(4)+sinl(32)-4.*cosl(4)-32.*cosl(32))/16.

using namespace std;

typedef long double ld;

ld uniform(ld a, ld b){
  ld ret = a + (b-a)*(ld)rand()/RAND_MAX;
  return ret;
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
        ret=0.;
        for(int i=0;i<N;i++){
            point = uniform(a,b);
            ret+=func(point);
            cout << setprecision(15)<<"point: " << point << ", ret: " << ret << endl;
        }
        tot+=ret*(b-a)/N;
    }
    
    return tot/repeat;
}

int main(int argc, char** argv){
    cout << "TEST: " << endl;
    cout << integral_Monte_Carlo_repeat<ld>(1000,0,5,&f3,10) - REAL_VAL3 << endl;
    return 0;
}