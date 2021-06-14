#ifndef MEMPOOL_H
#define MEMPOOL_H
#include "txn.h"
#include <string>
#include <vector>
using namespace std;

class Mempool{
public:
  vector<Txn> AllTransactions;
  vector<string> idOptTx;

  void file_handling(string file_path);

  bool parentsMined(Txn t);

  vector<string> optimiseTransactions();

};

#endif
