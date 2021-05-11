#include "Algorithm.hpp"
#include <iostream>

using namespace std;

int main() {
    auto alg = new Algorithm(10);

    alg->Set(0, 0, 4);
    alg->Set(1, 0, 5);
    alg->Set(12, 2, 7);

    //alg->PrintLength();

    cout << alg->Get(12, 2) << endl;

    delete alg;
    
    return 0;
}