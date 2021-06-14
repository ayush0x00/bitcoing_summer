## Approach
After seeing the term to maximize the fees within a given range of weight, I considered it as a variation of 0-1 knapsack. So i tried to implement the traditional DP approach.
However, the constraints were too large to make a 2-D array and maximize the fees. To tackle this problem, I used two 1-D array. This helped me in not getting my call stack blown away.

## Code structure
There are two class files in the code. One class has the structure of a single transaction and is named as `Txn`. The other class provides functionality of maintaining the mempool and is named as `Mempool`.
The `Mempool` is responsible for parsing the csv file and creating an object of Txn class for each transactions.
It then applies knapsack to the vector of Txn, and stores the result in a `idOptTx` vector.

## Steps to run the code
Compile the `main.cpp` file and then run the executable obtained.
``` Bash
g++ main.cpp mempool.cpp -o output
./output
```
This will generate `block.txt` file in the current directory.
I have added debug code that displays the progress of transactions being processed on the terminal.
