#include <bits/stdc++.h>
using namespace std;

int main(){
  ifstream in("test.csv");
  string line;
  while(getline(in,line)){
    stringstream sstream(line);
    string data;
    while(getline(sstream,data,',')){
      std::cout << data << '\n';
    }
  }
  return 0;
}
