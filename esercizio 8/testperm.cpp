#include<iostream>
#include<iomanip>
#include<fstream>
#include<cmath>
#include<string>
#include<filesystem>
#include<algorithm>
#include"integration.h"
#include"utilities.h"

using namespace std;

typedef long long ll;
typedef long double ld;

void printvec(vector<int> vec){
    for(int i = 0; i<vec.size();i++){
        cout << vec.at(i) << " ";
    }
    cout << endl;
}

int findfirst(int target,vector<int> vec){
    for(int i=0;i<vec.size();i++){
        if(vec.at(i)==target)
            return i;
    }
    return -1;
}

bool end_perm(vector<int>current_point){
    vector<int> last_point = {3,3,3,3};
    if(current_point==last_point)
        return true;
    return false;
}

// void reset(vector<int> *current_point, int val){
//     (*current_point).at((*current_point).size()-1) = val;
//     for(int i = 0; i<current_point->size()-1;i++){
//         current_point->at(i) = 1;
//     }
// }

void reset(auto start, auto end, int val){
    *(end)=val;
    for(int i = 0; i<distance(start,end-1);i++){
        *(start+i)=1;
    }
}

int main(){
    vector<int> coords = {1,1,1,1};
    int last_index = coords.size()-1;
    int last_increased = last_index;
    int last_upper_value = 1;
    do{
        do{
            printvec(coords);
        }while(next_permutation(coords.begin(),coords.end()));//la permutazione viene riportata a quella iniziale alla fine
        coords.at(last_increased)++;
        last_increased--;

        if(last_increased==-1){
            last_upper_value = coords.at(last_index);
            reset(coords.begin(),coords.begin()+last_index,last_upper_value+1);
            last_index--;

            if(last_index==-1){
                last_index = coords.size()-1;
            }
            
            last_increased=last_index;

        }
    }while(!end_perm(coords));
    // auto prova = coords.end();
    // cout << *(prova-1) << endl;
    printvec(coords);
    return 0;
}