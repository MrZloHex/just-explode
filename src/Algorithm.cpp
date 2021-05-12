#include "Algorithm.hpp"
#include <iostream>

using namespace std;


const uint8_t nothing      = 0; //        0 - nothing
const uint8_t bomb_1       = 1;  //        1 - 1 bomb around
const uint8_t bomb_2       = 2;  //        2 - 2 bombs
const uint8_t bomb_3       = 3;  //        3 - 3
const uint8_t bomb_4       = 3;  //      4 - 4 
const uint8_t bomb_5       = 3;  //      5 - 5
const uint8_t bomb_6       = 3;  //      6 - 6
const uint8_t bomb_7       = 3;  //      7 - 7
const uint8_t bomb_8       = 3;  //      8 - 8

const uint8_t BOMB         = 10;  //      10 - BOMBEE
const uint8_t labeled_bomb = 11;  //      11 - rejected mine
const uint8_t idk          = 12;  //      12 - idk
const uint8_t BOOM         = 13;  //      13 - BOOOOOOM
const uint8_t WIN          = 14;  //      14 - WIN



// constructor
Algorithm::Algorithm(short size, short cell) : size_field (size) {
    Algorithm::size_field = size;
    Algorithm::size_cell = cell;

    // taking memory for matrices
    Algorithm::field = new unsigned short *[size];
    Algorithm::show_field = new unsigned short *[size];
    for (short i = 0; i < size; i++) {
        Algorithm::field[i] = new unsigned short[size];
        Algorithm::show_field[i] = new unsigned short [size];
    }
}

// destructor
Algorithm::~Algorithm() {
    for (short i = 0; i < Algorithm::size_field; i++) {
        delete[] Algorithm::field[i];
        delete[] Algorithm::show_field[i];
    }
    delete[] Algorithm::field;
    delete[] Algorithm::show_field;
}



/* initing fields; field - generate bombs and nothing
                           show_field - all idk             */
void Algorithm::init_fields() {
    srand(time(NULL));
    for (short x = 0; x < Algorithm::size_field; x++)
        for (short y = 0; y < Algorithm::size_field; y++) {
            // idk cells for playes
            Algorithm::show_field[x][y] = idk;

            // adding bombs at main field whith chance in 20%
            if (rand()%5 == 0) Algorithm::field[x][y] = BOMB;
            else Algorithm::field[x][y] = nothing;
        }
}



// places all markdowns at field
void Algorithm::generate_map() {
    for (short x = 0; x < Algorithm::size_field; x++)
        for (short y = 0; y < Algorithm::size_field; y++) {
            // counter of bombs for each cell without bomb
            unsigned short amount_bomb = 0;

            // do not count bomb for cell with bomb )
            if (Algorithm::field[x][y] == BOMB)   continue;


            if (x != 0) {
                if (y != 0) 
                    if (Algorithm::field[x-1][y-1] == 10)   amount_bomb++;

                if (y != (Algorithm::size_field-1))
                    if (Algorithm::field[x-1][y+1] == 10)   amount_bomb++;

                if (Algorithm::field[x-1][y]   == 10)   amount_bomb++;
            }
            else if (x != (Algorithm::size_field-1)) {
                if (y != 0)
                    if (Algorithm::field[x+1][y-1] == 10)   amount_bomb++;

                if (y != (Algorithm::size_field-1))
                    if (Algorithm::field[x+1][y+1] == 10)   amount_bomb++;
                
                if (Algorithm::field[x+1][y]   == 10)   amount_bomb++;
                
            }
            else {
                if (y != 0)
                    if (Algorithm::field[x][y-1]   == 10)   amount_bomb++;

                if  (y != (Algorithm::size_field-1))
                    if (Algorithm::field[x][y+1]   == 10)   amount_bomb++;
            }

            // writing amount of bombs in cell
            Algorithm::field[x][y] = amount_bomb;
        }           
}


void Algorithm::bomb_handler(bool mouse, unsigned int x, unsigned int y){
    if (!mouse) {
        if(Algorithm::field[x][y] == 10) Algorithm::BOOOM();
        else Algorithm::show_field[x][y] = Algorithm::field[x][y];
    }
    else Algorithm::show_field[x][y] = labeled_bomb;
}

void Algorithm::BOOOM() {
    for (short x = 0; x < Algorithm::size_field; x++) 
        for (short y = 0; y < Algorithm::size_field; y++) {
            show_field[x][y] = BOOM;
        }
}


/* getting type of cell in field
            true - field
            false - show_field          */
unsigned short Algorithm::get_type_of_cell(bool map, short x, short y) {
    if (map) return Algorithm::field[x][y];
    else return Algorithm::show_field[x][y];
}


// method of getting size of game field
short Algorithm::get_size_field() {
    return Algorithm::size_field;
}


// method of getting size of cell in pixels
short Algorithm::get_size_cell() {
    return Algorithm::size_cell;
}