#include "Algorithm.hpp"
#include <iostream>

using namespace std;

int main() {
    auto alg = new Algorithm(10);

    alg->Set(0, 0, 4);
    alg->Set(1, 0, 5);
    alg->Set(9, 2, 4);

    //alg->PrintLength();

    cout << alg->Get(9, 2) << endl;

    delete alg;
    
    return 0;
}