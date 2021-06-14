#include <bits/stdc++.h>
using namespace std;
#include "mempool.h"

int main(){
  Mempool mem;
  mem.file_handling("mempool.csv");
  ofstream out;
  out.open("block.txt");
  if(!out){
    std::cout << "Error while opening the file" << '\n';
    exit(1);
  }

  vector<string> result=mem.optimiseTransactions();
  for (auto i:result) out<<i<<"\n";
  return 0;
}
