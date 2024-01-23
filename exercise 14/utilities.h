#include<iomanip>
#include<fstream>
#include<string>
#include<filesystem>
#include<chrono>
#include<ctime>
#include<vector>

#define GET_TIME chrono::system_clock::now()
#define DATA_LIMIT 1000000

typedef long long ll;
typedef long double ld;
// typedef vector<vector<ld>> mat_ld;

using namespace std;

template<typename T>
vector<T> random_vector(int dim){
    vector<T> ret(dim);
    for(auto& coord : ret){
        coord = (T)rand()/RAND_MAX;
    }
    return ret;
}

template<typename T>
void printvec(vector<T> vec){
    for(auto& elem : vec){
        cout << elem << " ";
    }
    cout << endl;
}

template<typename T>
T sumsqvec(vector<T> vec){
    T sum = 0.;
    for(auto& elem : vec){
        sum+=powl(elem,2);
    }
    return sum;
}

void elapsed(auto start){
    auto end = chrono::system_clock::now();
 
    chrono::duration<double> elapsed_seconds = end-start;
    time_t end_time = chrono::system_clock::to_time_t(end);
 
    cout << "   finished computation at " << ctime(&end_time)
              << "   elapsed time: " << elapsed_seconds.count() << "s"
              << endl;
}

ld runtime(auto start){
    auto end = GET_TIME;
    chrono::duration<double> elapsed_seconds = end-start;

    return elapsed_seconds.count();
}

template<typename T>
void printInFile(string path, vector<T> first_col, int precision){
    ofstream file;
    file << setprecision(precision);
    file.open(path);
    unsigned int N_rows = first_col.size();
    
    for(unsigned int i = 0; i<N_rows; i++){
        file << first_col[i] << endl;
        if(filesystem::file_size(path)>DATA_LIMIT){
            cout << "size limit reached: " << DATA_LIMIT << "B\n" ;
            file.close();
            return;
        }
    }
    file.close();
}

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
        if(filesystem::file_size(path)>DATA_LIMIT){
            cout << "size limit reached: " << DATA_LIMIT << "B\n" ;
            file.close();
            return;
        }
    }
    file.close();
}

template<typename T1,typename T2,typename T3>
void printInFile(string path, vector<T1> first_col, vector<T2> second_col, vector<T3> third_col, int precision){
    if(first_col.size()!=second_col.size()){
        cout << "ERRORE: vettori di dimensione diversa!" << endl;
        return;
    }
    ofstream file;
    file.open(path);
    file << setprecision(precision);
    unsigned int N_rows = first_col.size();
    
    for(unsigned int i = 0; i<N_rows; i++){
        file << first_col[i] << " " << second_col[i] << " " << third_col[i] << endl;
        if(filesystem::file_size(path)>DATA_LIMIT){
            cout << "size limit reached: " << DATA_LIMIT << "B\n" ;
            file.close();
            return;
        }
    }
    file.close();
}

template<typename T1,typename T2,typename T3,typename T4,typename T5, typename T6>
void printInFile(string path, vector<T1> first_col, vector<T2> second_col, vector<T3> third_col, vector<T4> fourth_col, vector<T5> fifth_col, vector<T6> sixth_col, int precision){
    if(first_col.size()!=second_col.size()){
        cout << "ERRORE: vettori di dimensione diversa!" << endl;
        return;
    }
    ofstream file;
    file.open(path);
    file << setprecision(precision);
    unsigned int N_rows = first_col.size();
    
    for(unsigned int i = 0; i<N_rows; i++){
        file << first_col[i] << " " << second_col[i] << " " << third_col[i] << " " << fourth_col[i] <<" " << fifth_col[i] <<" " << sixth_col[i] << endl;
        if(filesystem::file_size(path)>DATA_LIMIT){
            cout << "size limit reached: " << DATA_LIMIT << "B\n" ;
            file.close();
            return;
        }
    }
    file.close();
}

// string line = "";
//         for(int j=0;j<6;j++)
//             line +=

template<typename T>
void printInFile(string path, vector<vector<T>> matrix, int precision){
    ofstream file;
    file.open(path);
    int N_rows = matrix.size();
    int N_cols = matrix[0].size();
    
    file << setprecision(precision);

    for(int i = 0; i<N_rows; i++){
        // string line = "";
        for(int j = 0; j<N_cols; j++){
            file << matrix[i][j] << " ";
        }

        file << endl;

        if(filesystem::file_size(path)>DATA_LIMIT){
            cout << "size limit reached: " << DATA_LIMIT << "B\n" ;
            file.close();
            return;
        }
    }
    file.close();
}

// vector<vector<ld>> read_from_file(string path, int N){
//     vector<vector<ld>> ret = init_matrix(N,2);
//     // string path = "gauss/legendre" + to_string(N) + ".txt";
//     // cout << path << endl;
//     ifstream file(path,ios::in);
    
//     int i=0;
//     while(true){
//         file >> ret[i][0];
//         file >> ret[i][1];
//         if(file.eof())  break;
//         i++;
//     }
//     file.close();
//     return ret;
// }
