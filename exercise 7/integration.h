#include<iostream>
#include<fstream>
#include<cmath>
#include<vector>

typedef long long ll;
typedef long double ld;

using namespace std;
//funzione che implementa il metodo del trapezio
//PARAMETRI
/*
-"N": numero di punti da utilizzare nella valutazione della formula di integrazione
-"a": estremo inferiore
-"b": estremo superiore
-"func": funzione integranda
*/
ld int_trapezoidal(int N, ld a, ld b, ld (*func)(ld)){
    ld h = (b-a)/(N-1);
    ld point = a;
    ld ret = .5*(func(a)+func(b));
    
    for(int i=2; i<=N-1;i++){
        point+=h;
        ret+=func(point);
    }

    return ret*h;
}

//funzione che implementa il metodo di Simpson
//PARAMETRI
/*
-"N": numero di punti da utilizzare nella valutazione della formula di integrazione
-"a": estremo inferiore
-"b": estremo superiore
-"func": funzione integranda
*/
ld int_simpson(int N, ld a, ld b, ld (*func)(ld)){
    ld h = (b-a)/(N-1);
    ld point = a;    
    ld ret = func(a)+func(b);
    
    for(int i=2; i<=N-1;i++){
        point+=h;
        if(i%2==0)
            ret+=4*func(point);
        else
            ret+=2*func(point);
    }

    return ret*h/3.;
}

//funzione che implementa la formula aperta con un punto con errore di ordine h^3.
//PARAMETRI:
//-fixed_low: estremo inferiore dell'intervallo di integrazione
//-fixed_up: estremo superiore dell'intervallo di integrazione
//-func: funzione integranda
ld open_h3(ld fixed_low, ld fixed_up, ld (*func)(ld)){
    ld fixed = (fixed_up-fixed_low)/2.;
    ld ret = 2*fixed*func(fixed_low+fixed);
    // cout << ret << endl;
    return ret;
}

//funzione che implementa la formula aperta con un punto con errore di ordine h^5.
//PARAMETRI:
//-fixed_low: estremo inferiore dell'intervallo di integrazione
//-fixed_up: estremo superiore dell'intervallo di integrazione
//-func: funzione integranda
ld open_h5(ld fixed_low, ld fixed_up, ld (*func)(ld)){
    ld h = (fixed_up-fixed_low)/5;
    ld ret = 11 * func(fixed_low + h) + func(fixed_low + 2 * h) + func(fixed_low + 3 * h) + 11 * func(fixed_low + 4 * h);
    return h*ret*(5./24.);
}

//funzione che implementa il metodo del trapezio ricorsivo
//PARAMETRI
/*
-"j": termine della relazione di ricorrenza a cui arrivare
-"a": estremo inferiore
-"b": estremo superiore
-"func": funzione integranda
*/
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
        T_j=.5*T_j_minus_one;
        //variabile in cui salvare il valore dei contributi dei nuovi punti
        extra_sum=0;
        //contatore con cui aumentare l'ascissa del punto da valutare
        int count = 1;
        while(count<=(pow(2,i)-1)){
            point = a+count*h;
            extra_sum+=func(point);
            //incremento il contatore di due ogni volta per evitare di ricalcolare su punti già inclusi nel termine T_j_minus_one
            count+=2;
        }
        T_j+=h*extra_sum;
        T_j_minus_one=T_j;
    }
    return T_j;
}

//funzione che implementa il metodo di Simpson ricorsivo
//PARAMETRI
/*
-"j": termine della relazione di ricorrenza a cui arrivare
-"a": estremo inferiore
-"b": estremo superiore
-"func": funzione integranda
*/
ld ric_simpson(int j, ld a, ld b, ld(*func)(ld)){
    if(j<=0)
        return -1;
    ld ret = (4.*ric_trapezoidal(j,a,b,func) - ric_trapezoidal(j-1,a,b,func))/3.;
    return ret;
}

//funzione che implementa il metodo di Simpson ricorsivo
//PARAMETRI
/*
-"j","k": si arriva al termine R_{jk} della relazione di ricorrenza
-"a": estremo inferiore
-"b": estremo superiore
-"func": funzione integranda
*/
ld romberg(int j, int k, ld a, ld b, ld(*func)(ld)){
    if(j<0 || k<0)
        return -1;
    ld R_j_0 = ric_trapezoidal(j,a,b,func);
    // ld R_j_minus_one = ric_trapezoidal(j-1,a,b,func);
    if(k==0)
        return R_j_0;
    ld ret = (powl(4,k)*romberg(j,k-1,a,b,func) - romberg(j-1,k-1,a,b,func))/(powl(4,k)-1);
    return ret;
}

//funzione che inizializza una matrice vuota
//PARAMETRI
/*
-"rows": numero di righe
-"cols": numero di colonne
*/
vector<vector<ld>> init_matrix(int rows, int cols){
    vector<vector<ld>> ret;
    vector<ld> row(cols);
    for(int i=0;i<rows;i++){
        ret.push_back(row);
    }
    return ret;
}

//funzione che costruisce una matrice con diversi termini della relazione di ricorrenza del metodo di Romberg
//PARAMETRI
/*
-"j_max", "k_max": dimensioni della matrice da costruire
-"a": estremo inferiore
-"b": estremo superiore
-"func": funzione integranda
-"real_value": valore vero dell'integrale
*/
vector<vector<ld>> romberg_matrix(int j_max, int k_max, ld a, ld b, ld(*func)(ld),ld real_value){
    vector<vector<ld>> ret = init_matrix(j_max,k_max);

    ld h = (b-a);
    ld T_j_minus_one = .5*h*(func(a)+func(b));
    ret.at(0).at(0) = T_j_minus_one;
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
        ret.at(J).at(0)=T_j;
    }

    for(int J=0; J<j_max; J++){
        for(int K=1; K<k_max; K++){
            if(J>=K)
                ret.at(J).at(K) = (powl(4,K)*ret.at(J).at(K-1) - ret.at(J-1).at(K-1))/(powl(4,K)-1);
            else
                ret.at(J).at(K) = 0.; 
        }
    }
    
    for(int J=0; J<j_max; J++){
        for(int K=0; K<k_max; K++){
            // cout << "ret["<< J << "][" << K << "]=" << ret[J][K] << endl;
            if(J>=K)
                ret.at(J).at(K) = fabsl(ret.at(J).at(K)-real_value);
        }
    }

    return ret;
}
//funzione che implementa le quadrature gaussiane con i polinomi di Legendre
//PARAMETRI
/*
-"N": numero dei punti da utilizzare
-"func": funzione da utilizzare nella valutazione dei punti
*/
//NOTE
/*
-gli zeri dei polinomi di Legendre sono simmetrici rispetto allo zero. Nei file sono salvati solo i valori assoluti degli zeri.
 Quando serve la funzione viene valutata sia in corrispondenza del valore positivo che di quello negativo, ovviamente con lo stesso peso.
*/
ld legendre(int N, ld (*func)(ld)){
    vector<vector<ld>> ret = init_matrix(N/2,2);//matrice all'interno della quale si salvano i punti e i pesi
    string path = "gauss/legendre" + to_string(N) + ".txt";//i file di testo contenenti i punti e i pesi sono salvati nella cartella "gauss"
    ifstream file(path,ios::in);//apertura in lettura del file
    
    int i=0;
    //lettura di punti e pesi
    while(true){
        file >> ret[i][0];
        file >> ret[i][1];
        if(file.eof())  break;
        i++;
    }
    file.close();

    ld res = 0;
    
    //valutazione dei vari termini della somma.
    for(int i=0; i<N/2;i++){
        res += ret[i][1]*func(ret[i][0]) + ret[i][1]*func(-ret[i][0]);
    }
    
    return res;
}

//funzione che implementa le quadrature gaussiane con i polinomi di Legendre
//PARAMETRI
/*
-"N": numero dei punti da utilizzare
-"func": funzione da utilizzare nella valutazione dei punti
*/
ld laguerre(int N, ld (*func)(ld)){
    vector<vector<ld>> ret = init_matrix(N,2);//matrice all'interno della quale si salvano i punti e i pesi
    string path = "gauss/laguerre" + to_string(N) + ".txt";//i file di testo contenenti i punti e i pesi sono salvati nella cartella "gauss"
    ifstream file(path,ios::in);//apertura in lettura del file
    
    int i=0;
    //lettura di punti e pesi
    while(true){
        file >> ret[i][0];
        file >> ret[i][1];
        if(file.eof())  break;
        i++;
    }
    file.close();

    ld res = 0;

    //valutazione dei vari termini della somma.
    for(int i=0; i<N;i++){
        // cout << "peso: " << ret[i][1] << ", punto: " << ret[i][0] << endl;
        res += ret[i][1]*func(ret[i][0]);
    }
    
    return res;
}

//funzione che implementa le quadrature gaussiane con i polinomi di Hermite
//PARAMETRI
/*
-"N": numero dei punti da utilizzare
-"func": funzione da utilizzare nella valutazione dei punti
*/
ld hermite(int N, ld (*func)(ld)){
    vector<vector<ld>> ret = init_matrix(N/2,2);//matrice all'interno della quale si salvano i punti e i pesi
    string path = "gauss/hermite" + to_string(N) + ".txt";//i file di testo contenenti i punti e i pesi sono salvati nella cartella "gauss"
    ifstream file(path,ios::in);//apertura in lettura del file
    
    int i=0;
    //lettura di punti e pesi
    while(true){
        file >> ret[i][0];
        file >> ret[i][1];
        if(file.eof())  break;
        i++;
    }
    file.close();

    ld res = 0;

    //valutazione dei vari termini della somma.
    for(int i=0; i<N/2;i++){
        // cout << "peso: " << ret[i][1] << ", punto: " << ret[i][0] << ",func: " << func(ret[i][0]) << endl;
        res += ret[i][1]*(func(ret[i][0]) + func(-ret[i][0]));
    }
    
    return res;
}