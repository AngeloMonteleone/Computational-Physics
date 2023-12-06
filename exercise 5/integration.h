#include<iostream>
#include<fstream>
#include<cmath>
#include<vector>
// #include"utilities.h"

typedef long long ll;
typedef long double ld;

using namespace std;

ld int_trapezoidal(int N, ld a, ld b, ld (*func)(ld)){
    ld h = (b-a)/(N-1);
    // cout << "h: " <<  h << endl;
    ld point = a;
    ld ret = .5*(func(a)+func(b));//questo potrebbe essere un problema, perché forse andrebbe valutato alla fine
    
    for(int i=2; i<=N-1;i++){
        point+=h;
        // cout << "point: " << point << endl;
        ret+=func(point);
    }
    
    // cout << "point: " << point + h << endl;
    return ret*h;
}

ld int_simpson(int N, ld a, ld b, ld (*func)(ld)){
    ld h = (b-a)/(N-1);
    // cout << "h: " << h << endl;
    ld point = a;    
    ld ret = func(a)+func(b);
    
    for(int i=2; i<=N-1;i++){
        point+=h;
        if(i%2==0)
            ret+=4*func(point);
        else
            ret+=2*func(point);
        
        // cout << "point: " << point << endl;
    }
    // cout << "point: " << point + h << endl;
    return ret*h/3.;
}

ld ric_trapezoidal(int j, ld a, ld b, ld(*func)(ld)){
    ld h = (b-a);
    ld T_j_minus_one = .5*h*(func(a)+func(b));
    if(j==0)
        return T_j_minus_one;
    ld T_j;
    ld point;
    ld extra_sum;
    for(int i=1;i<=j;i++){
        //dimezzo la larghezza dell'intervallo ad ogni passaggio
        h/=2;
        // cout <<"h: "<< h << endl;
        T_j=.5*T_j_minus_one;
        //variabile in cui salvare il valore dei contributi dei nuovi punti
        extra_sum=0;
        //contatore con cui aumentare l'ascissa del punto da valutare
        int count = 1;
        while(count<=(pow(2,i)-1)){
            point = a+count*h;
            // cout <<"    point: " << point << endl;
            extra_sum+=func(point);
            //incremento il contatore di due ogni volta per evitare di ricalcolare su punti già inclusi nel termine T_j_minus_one
            count+=2;
        }
        T_j+=h*extra_sum;
        T_j_minus_one=T_j;
        // cout << "   check: " << point+h << endl;
    }
    return T_j;
}

ld ric_simpson(int j, ld a, ld b, ld(*func)(ld)){
    if(j<=0)
        return -1;
    ld ret = (4.*ric_trapezoidal(j,a,b,func) - ric_trapezoidal(j-1,a,b,func))/3.;
    return ret;
}

ld romberg(int j, int k, ld a, ld b, ld(*func)(ld)){
    // cout << "computing romberg: j=" << j << ", k=" << k << endl;
    if(j<0 || k<0)
        return -1;
    ld R_j_0 = ric_trapezoidal(j,a,b,func);
    // ld R_j_minus_one = ric_trapezoidal(j-1,a,b,func);
    if(k==0)
        return R_j_0;
    ld ret = (powl(4,k)*romberg(j,k-1,a,b,func) - romberg(j-1,k-1,a,b,func))/(powl(4,k)-1);
    return ret;
}

vector<vector<ld>> init_matrix(int rows, int cols){
    vector<vector<ld>> ret;
    vector<ld> row = vector<ld> (cols);
    for(int i=0;i<rows;i++){
        ret.push_back(row);
    }
    return ret;
}

vector<vector<ld>> romberg_matrix(int j_max, int k_max, ld a, ld b, ld(*func)(ld),ld real_value){
    vector<vector<ld>> ret = init_matrix(j_max,k_max);

    // cout << "size matrix: " << sizeof(ret) << endl;

    ld h = (b-a);
    ld T_j_minus_one = .5*h*(func(a)+func(b));
    ret[0][0] = T_j_minus_one;
    ld T_j, point, extra_sum;
    for(int J=1;J<j_max;J++){
        h/=2.;
        T_j=.5*T_j_minus_one;
        extra_sum=0.;
        int count = 1;

        while(count<=(pow(2,J)-1)){
            point = a+count*h;
            extra_sum+=func(point);
            count+=2;
        }
        
        T_j+=h*extra_sum;
        T_j_minus_one=T_j;
        ret[J][0]=T_j;
    }

    // for(int J=0; J<j_max; J++){
    //     cout << "test\n";
    //     ret[J][0]=ric_trapezoidal(J,a,b,func);
    // }

    for(int J=0; J<j_max; J++){
        for(int K=1; K<k_max; K++){
            if(J>=K)
                ret[J][K] = (powl(4,K)*ret[J][K-1] - ret[J-1][K-1])/(powl(4,K)-1);
            else
                ret[J][K] = 0.; 
        }
    }
    
    for(int J=0; J<j_max; J++){
        for(int K=0; K<k_max; K++){
            cout << "ret["<< J << "][" << K << "]=" << ret[J][K] << endl;
            if(J>=K)
                ret[J][K] = fabsl(ret[J][K]-real_value);
        }
    }

    return ret;
}

ld legendre(int N, ld (*func)(ld)){
    vector<vector<ld>> ret = init_matrix(N/2,2);
    string path = "gauss/legendre" + to_string(N) + ".txt";
    // cout << path << endl;
    ifstream file(path,ios::in);
    
    int i=0;
    while(true){
        file >> ret[i][0];
        file >> ret[i][1];
        if(file.eof())  break;
        i++;
    }
    file.close();

    ld res = 0;
    for(int i=0; i<N/2;i++){
        cout << "peso: " << ret[i][1] << ", punto: " << ret[i][0] << endl;
        res += ret[i][1]*func(ret[i][0]) + ret[i][1]*func(-ret[i][0]);
    }
    
    return res;
}

ld laguerre(int N, ld (*func)(ld)){
    vector<vector<ld>> ret = init_matrix(N,2);
    string path = "gauss/laguerre" + to_string(N) + ".txt";
    // cout << path << endl;
    ifstream file(path,ios::in);
    
    int i=0;
    while(true){
        file >> ret[i][0];
        file >> ret[i][1];
        if(file.eof())  break;
        i++;
    }
    file.close();

    ld res = 0;
    for(int i=0; i<N;i++){
        cout << "peso: " << ret[i][1] << ", punto: " << ret[i][0] << endl;
        res += ret[i][1]*func(ret[i][0]);
    }
    
    return res;
}