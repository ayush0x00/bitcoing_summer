#ifndef TXN_H
#define TXN_H
#include <string>
#include <vector>
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
#endif
