#include "Algorithm.hpp"
#include <iostream>


int main() {
    Algorithm algorithm;

    algorithm.init_fields();
    algorithm.generate_map();

    for (short x = 0; x < 0xC; x++)
        for (short y = 0; y < 0xC; y++) {
            std::cout << algorithm.get_type_of_cell(false, x, y);
        }

    return 0;
}