#include "Algorithm.hpp"
#include <iostream>

using namespace std;

Algorithm::Algorithm(int size) : size (size) {
    Algorithm::size = size;
    Algorithm::array = new unsigned short*[size];
    for (short i = 0; i < size; i++)
        Algorithm::array[i] = new unsigned short[size];
}

Algorithm::~Algorithm() {
    for (short i = 0; i < Algorithm::size; i++)
        delete[] Algorithm::array[i];
    delete[] Algorithm::array;
}

void Algorithm::Set(int index1, int index2, unsigned short value) {
    Algorithm::array[index1][index2] = value;
}

unsigned short Algorithm::Get(int index1, int index2) {
    return array[index1][index2];
}

/*void Algorithm::PrintLength() {
    //cout << *(&Algorithm::array + 1) - Algorithm::array << endl;
    cout << sizeof(Algorithm::array)/sizeof(Algorithm::array[0]) << endl;
}*/