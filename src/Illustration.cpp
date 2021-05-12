#include "Illustration.hpp"

int *Colorize(unsigned short type) {
    static int color[3];

    //                                R                G                B
    if      (type ==  0) {color[0] = 0x5D; color[1] = 0x5D; color[2] = 0x5D;}
    else if (type ==  1) {color[0] = 0x00; color[1] = 0x80; color[2] = 0xFF;}
    else if (type ==  2) {color[0] = 0x3A; color[1] = 0xFF; color[2] = 0x3A;}
    else if (type ==  3) {color[0] = 0xFF; color[1] = 0xFF; color[2] = 0x00;}
    else if (type ==  4) {color[0] = 0xFF; color[1] = 0x3A; color[2] = 0x3A;}
    else if (type ==  5) {color[0] = 0x80; color[1] = 0x00; color[2] = 0xFF;}

    else if (type ==  6) {color[0] = 0x5D; color[1] = 0x5D; color[2] = 0x5D;}
    else if (type ==  7) {color[0] = 0x5D; color[1] = 0x5D; color[2] = 0x5D;}
    else if (type ==  8) {color[0] = 0x5D; color[1] = 0x5D; color[2] = 0x5D;}

    else if (type == 10) {color[0] = 0x00; color[1] = 0x00; color[2] = 0x00;}
    else if (type == 11) {color[0] = 0xFF; color[1] = 0xFF; color[2] = 0xFF;}
    else if (type == 12) {color[0] = 0xD1; color[1] = 0xD1; color[2] = 0xD1;}
    else if (type == 13) {color[0] = 0xFF; color[1] = 0x80; color[2] = 0x00;}
    else if (type == 14) {color[0] = 0x00; color[1] = 0xFF; color[2] = 0xFF;}

    return color;
}