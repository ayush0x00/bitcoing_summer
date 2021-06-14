#include <bits/stdc++.h>
#include "mempool.h"
#define MAX_WEIGHT 4000000
#define TOTAL_TXN 5214
using namespace std;

void Mempool::file_handling(string file_path){
  //Reads all transactions from file
  ifstream fin;
  fin.open(file_path);
  string line;
  int txn_no=0;
  while(getline(fin,line)){
    stringstream sstream(line);
    vector<string>data;
    txn_no++;
    while(sstream.good()){
      string temp;
      getline(sstream,temp,',');
      data.push_back(temp);
    }
    std::vector<string> p;
    int fees=stoi(data[1]);
    int weight=stoi(data[2]);
    string i=data[3];
      if(i.length()>0){
        stringstream temp(i);
        while(temp.good()){
          string t;
          getline(temp,t,';');
          p.push_back(t);
        }
      }
    Txn t(txn_no,data[0],fees,weight,p);
    AllTransactions.push_back(t);
  }
  fin.close();
  return ;
}

bool Mempool:: parentsMined(Txn t){
  auto p=t.parents;
  if(p.size()==0) return true;
  else{
    for(auto i:p){
      auto it=find(idOptTx.begin(),idOptTx.end(),i);
      if(it==idOptTx.end()) {
        return false;
      }
    }
  }
  return true;
}

vector<string> Mempool:: optimiseTransactions(){

  //Optimises the mempool transactions

  vector<int> prev(MAX_WEIGHT+1,0);
  for(int i=1;i<=TOTAL_TXN;i++){
    std::cout << "Mining tx " <<i<< '\n';
    std::cout << "-----------------" << '\n';
    Txn currTx=AllTransactions[i-1];
    vector<int> curr(MAX_WEIGHT+1,0);
    bool pMined=parentsMined(currTx);
    if(pMined){
      bool included=false;
      for(int j=1;j<=MAX_WEIGHT;j++){
        if(currTx.weight>j) curr[j]=prev[j];
        else{
              if(prev[j]>currTx.fees+prev[j-currTx.weight]) curr[j]=prev[j];
              else{
                curr[j]=currTx.fees+prev[j-currTx.weight];
                included=true;
            }
        }
      }
      if(included){
        idOptTx.push_back(currTx.id);
      }
    }
    else continue;
    prev=curr;
  }
  return idOptTx;
}
