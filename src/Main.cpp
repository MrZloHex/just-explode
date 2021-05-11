#include "Algorithm.hpp"
#include <iostream>

using namespace std;

int main() {
    auto algorithm = new Algorithm(12, 0x19);

    algorithm->init_fields();
    //algorithm->generate_map();

    delete algorithm;
    
    return 0;
}