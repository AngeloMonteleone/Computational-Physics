#include<iostream>
#include<vector>
#include<fstream>

using namespace std;
typedef long double ld;

int main(int argc, char** argv){
    string path = "testrk4.dat";
    // cout << path << endl;
    ifstream file(path,ios::in);
    
    int i=0;
    ld time;
    ld diff,dump;
    while(true){
        file >> time;
        file >> diff;
	file >> dump;
	if(time == 1)
	  cout << "time: " << time << " diff: " << diff << endl;
        if(file.eof())  break;
        i++;
    }
    file.close();
  return 0;
}
