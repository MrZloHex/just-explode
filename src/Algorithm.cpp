#include "Algorithm.hpp"
#include <time.h>
#include <stdlib.h>

/*
        0 - nothing
        1 - 1 bomb
        2 - 
        3 - 
        4 - 
        5 - 
        6 - BOMBEE
        7 - rejected mine
        8 - idk
        9 - BOOOOOOM
        10 - WIN
*/


// constructor
Algorithm::Algorithm(size_t size) : size (size) {
    /*Algorithm::size_field = sf;
    Algorithm::size_cell = sc;*/
    Algorithm::size_field = size;
    Algorithm::buff = new unsigned short[size][size];
}
// destructor
Algorithm::~Algorithm() {
    delete[] Algorithm::buff;
}



/* initing fields; field - generate bombs and nothing
                           show_field - all idk             */
void Algorithm::init_fields() {
    srand(time(NULL));
    for (short x = 0; x < Algorithm::size_field; x++)
        for (short y = 0; y < Algorithm::size_field; y++) {
            Algorithm::show_field[x][y] = 0x8;
            if (rand()%5 == 0) Algorithm::field[x][y] = 0x6;
            else Algorithm::field[x][y] = 0;
        }
}



// places all markdowns at field
void Algorithm::generate_map() {
    for (short x = 0; x < Algorithm::size_field; x++)
        for (short y = 0; y < Algorithm::size_field; y++) {
            unsigned short amount_bomb = 0;
            if (Algorithm::field[x][y]     == 6)   continue;
            if (Algorithm::field[x-1][y-1] == 6)   amount_bomb++;
            if (Algorithm::field[x-1][y]   == 6)   amount_bomb++;
            if (Algorithm::field[x-1][y+1] == 6)   amount_bomb++;
            if (Algorithm::field[x][y+1]   == 6)   amount_bomb++;
            if (Algorithm::field[x+1][y+1] == 6)   amount_bomb++;
            if (Algorithm::field[x+1][y]   == 6)   amount_bomb++;
            if (Algorithm::field[x+1][y-1] == 6)   amount_bomb++;
            if (Algorithm::field[x][y-1]   == 6)   amount_bomb++;
            Algorithm::field[x][y] = amount_bomb;
        }   
}



/* getting type of cell in field
            true - field
            false - show_field          */
unsigned short Algorithm::get_type_of_cell(bool map, short x, short y) {
    if (map) return Algorithm::field[x][y];
    else return Algorithm::show_field[x][y];
}



short Algorithm::get_size_field() {
    return Algorithm::size_field;
}

short Algorithm::get_size_cell() {
    return Algorithm::size_cell;
}