#include "Functions.hpp"

using namespace std;

string Colorize(unsigned short type) {
    string dir = "./src/img/";

    //                                R                G                B
    if      (type ==  0) {dir.append("0.png");}
    else if (type ==  1) {dir.append("1.png");}
    else if (type ==  2) {dir.append("2.png");}
    else if (type ==  3) {dir.append("3.png");}
    else if (type ==  4) {dir.append("4.png");}
    else if (type ==  5) {dir.append("5.png");}
    else if (type ==  6) {dir.append("6.png");}
    else if (type ==  7) {dir.append("7.png");}
    else if (type ==  8) {dir.append("8.png");}

    else if (type == 10) {dir.append("10.png");}
    else if (type == 11) {dir.append("11.png");}
    else if (type == 12) {dir.append("12.png");}
    else if (type == 13) {dir.append("13.png");}
    else if (type == 14) {dir.append("14.png");}

    return dir;
}

bool mine(Algorithm algorithm) {

    usleep(1000000);
    for (short x = 0; x < size_field; x++) 
        for (short y = 0; y < Algorithm::size_field; y++) {
        }
}