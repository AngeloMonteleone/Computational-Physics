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

template<typename T>
void printInFile(string path, vector<vector<T>> matrix, int precision){
    ofstream file;
    file.open(path);
    int N_rows = matrix.size();
    int N_cols = matrix[0].size();
    // cout << "rows: " << N_rows << ", cols: " << N_cols << endl;
    
    file << setprecision(precision);

    for(int i = 0; i<N_rows; i++){
        // string line = "";
        for(int j = 0; j<N_cols; j++){
            file << matrix[i][j] << " ";
            // cout << "printing: (" << i << "," << j <<")\n";
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