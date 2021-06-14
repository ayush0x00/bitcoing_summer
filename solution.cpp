#include <bits/stdc++.h>
#define MAX_WEIGHT 4000000
#define TOTAL_TXN 5214
using namespace std;

class Txn{
public:
  int txn_no;
  string id;
  int weight;
  int fees;
  vector<string> parents;

  Txn(int n,string i, int f, int w, vector<string> p):txn_no{n},id{i},fees{f},weight{w},parents{p} {}
};

class Mempool{
public:
  vector<Txn> AllTransactions;
  vector<Txn> OptimalTransactions;
  vector<string> idOptTx;

  void file_handling(string file_path){
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
    return ;
  }

  bool parentsMined(Txn t){
    auto p=t.parents;
    //std::cout << "Checking for parents of " <<t.txn_no<<" transaction"<<'\n';
    if(p.size()==0) return true;
    else{
      for(auto i:p){
        //std::cout << "Parents found " << '\n';
        auto it=find(idOptTx.begin(),idOptTx.end(),i);
        if(it==idOptTx.end()) {
          //std::cout << "Parents not mined " << '\n';
          return false;
        }
      }
    }
    std::cout << "All parents mined" << '\n';
    return true;
  }

  void optimiseTransactions(){
    //Optimises the memepool transactions

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
          //std::cout << "Including transaction " <<i<<" in mined blocks"<<'\n';
          idOptTx.push_back(currTx.id);
        }
      }
      else continue;
      prev=curr;
    }
  }

  vector<string> getOptimalTransaction(){
    //Returns the ids of the transactions in a vector
    return idOptTx;
  }
};

int main(){
  Mempool mem;
  mem.file_handling("mempool.csv");
  mem.optimiseTransactions();
  return 0;
}
