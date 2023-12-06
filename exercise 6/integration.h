#include<iostream>
#include<fstream>
#include<cmath>
#include<vector>
// #include"utilities.h"

typedef long long ll;
typedef long double ld;

using namespace std;

//funzione che implementa il calcolo di un integrale con metodo del trapezio.
//PARAMETRI:
//-N: numero di punti utilizzati
//-a: estremo inferiore dell'intervallo di integrazione
//-b: estremo superiore dell'intervallo di integrazione
//-func: funzione integranda
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

//funzione che implementa la formula aperta con un punto con errore di ordine h^3.
//PARAMETRI:
//-fixed_low: estremo inferiore dell'intervallo di integrazione
//-fixed_up: estremo superiore dell'intervallo di integrazione
//-func: funzione integranda
ld open_h3(ld fixed_low, ld fixed_up, ld (*func)(ld)){
    ld fixed = (fixed_up-fixed_low)/2.;
    ld ret = 2*fixed*func(fixed/2);
    // cout << ret << endl;
    return ret;
}

//funzione che implementa il calcolo di un integrale con metodo del trapezio usando la formula aperta di ordine h^3 su un piccolo intervallo iniziale.
//PARAMETRI:
//-fixed: punto in cui dividere l'intervallo di integrazione
//-N: numero di punti utilizzati
//-a: estremo inferiore dell'intervallo di integrazione
//-b: estremo superiore dell'intervallo di integrazione
//-func: funzione integranda
ld int_trapezoidal_semiopen(int N, ld a, ld b, ld (*func)(ld),ld fixed){
    ld ret = open_h3(a,fixed,func);
    a+=fixed;
    ret=int_trapezoidal(N,a,b,func);
    return ret;
}

//funzione che implementa la formula estesa per il trapezio semi-aperta. Se il parametro sx è impostato su true, l'estremo escluso è quello
//sinistro, che verrà valutato con il peso della formula aperta, mentre se è impostato su true sarà l'estremo destro ad essere valutato con
//peso della formula aperta
// ld int_trapezoidal_semiopen(int N, ld a, ld b, ld (*func)(ld),bool sx){
//     ld h = (b-a)/(N-1);
//     // cout << "h: " <<  h << endl;
//     ld point;
//     ld ret;
//     if(sx){
//         point = a + h;
//         ret = 1.5*func(a+h)+0.5*func(b);
//     }
//     else{
//         point = a;
//         ret = 0.5*func(a)+1.5*func(b-h);
//     }
    
//     for(int i=0; i<N-3;i++){
//         point+=h;
//         // cout << "point: " << point << ", func: " << func(point) << endl;
//         ret+=func(point);
//     }
    
//     // cout << "point: " << point + h << endl;
//     return ret*h;
// }

//funzione che implementa il calcolo di un integrale con metodo di Simpson.
//PARAMETRI:
//-N: numero di punti utilizzati
//-a: estremo inferiore dell'intervallo di integrazione
//-b: estremo superiore dell'intervallo di integrazione
//-func: funzione integranda
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

ld open_h5(ld fixed_low, ld fixed_up, ld (*func)(ld)){
    float N = 6.;
    ld h = (fixed_up-fixed_low)/(N-1);
    ld ret = 11.*(func(fixed_low+h)+func(fixed_up-h)) + func(fixed_up-2*h) + func(fixed_low+2*h);
    return h*ret*5./24.;
}

//non funziona, il fit coi dati non converge
ld int_simpson_semiopen(int N, ld a, ld b, ld (*func)(ld),ld fixed){
    ld ret = open_h5(a,fixed,func);//non so se ha senso
    a+=fixed;
    ret=int_simpson(N,a,b,func);
    return ret;
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
        for(int K=0; J>=K; K++){
            ret[J][K] -= real_value;
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
        // cout << "peso: " << ret[i][1] << ", punto: " << ret[i][0] << endl;
        res += ret[i][1]*(func(ret[i][0]) + func(-ret[i][0]));
    }
    
    return res;
}

ld hermite(int N, ld (*func)(ld)){
    vector<vector<ld>> ret = init_matrix(N/2,2);
    string path = "gauss/hermite" + to_string(N) + ".txt";
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
        // cout << "peso: " << ret[i][1] << ", punto: " << ret[i][0] << ",func: " << func(ret[i][0]) << endl;
        res += ret[i][1]*(func(ret[i][0]) + func(-ret[i][0]));
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
        // cout << "peso: " << ret[i][1] << ", punto: " << ret[i][0] << endl;
        res += ret[i][1]*func(ret[i][0]);
    }
    
    return res;
}