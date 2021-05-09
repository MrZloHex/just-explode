#include <SFML/Graphics.hpp>
#include <iostream>
#include <unistd.h>

using namespace sf;

const short size_field = 0xC;
const short size_pixel = 0x19;

const bool dev = false; // false - normal mode; true - dev mode

void WIIIN(unsigned short show_field[size_field][size_field]) {
    for (short x = 0; x < 0xC; x++) 
        for (short y = 0; y < 0xC; y++) {
            show_field[x][y] = 10;
        }
}


void check_win(unsigned short field[size_field][size_field], unsigned short show_field[size_field][size_field]) {
    for (short x = 0; x < 0xC; x++) 
        for (short y = 0; y < 0xC; y++) {
            if (show_field[x][y] == 9) return;
        }
    WIIIN(show_field);
}

void BOOOM(unsigned short show_field[size_field][size_field]) {
    for (short x = 0; x < 0xC; x++) 
        for (short y = 0; y < 0xC; y++) {
            show_field[x][y] = 9;
        }
}


void mine_handler(bool type, unsigned int x, unsigned int y, unsigned short field[size_field][size_field], unsigned short show_field[size_field][size_field]) {
    // type::  false - Left; true - Right
    if (!type) {
        if(field[x][y] == 6) BOOOM(show_field);
        else show_field[x][y] = field[x][y];
    }
    else show_field[x][y] = 7;
}


void init_field(unsigned short field[size_field][size_field], bool type) {
    if (type) {
        for (short x = 0; x < 0xC; x++) 
            for (short y = 0; y < 0xC; y++) {
                if (rand()%0x5 == 0) field[x][y] = 0x6;
                else field[x][y] = 0;
            }
    }
    else {
        for (short x = 0; x < 0xC; x++) 
            for (short y = 0; y < 0xC; y++) {
                field[x][y] = 8;
            }
    }
}


void generate_map(unsigned short field[size_field][size_field]) {
    for (short x = 0; x < size_field; x++)
        for (short y = 0; y < size_field; y++) {
            unsigned short amount_bomb = 0;
            if (field[x][y]     == 6)   continue;
            if (field[x-1][y-1] == 6)   amount_bomb++;
            if (field[x-1][y]   == 6)   amount_bomb++;
            if (field[x-1][y+1] == 6)   amount_bomb++;
            if (field[x][y+1]   == 6)   amount_bomb++;
            if (field[x+1][y+1] == 6)   amount_bomb++;
            if (field[x+1][y]   == 6)   amount_bomb++;
            if (field[x+1][y-1] == 6)   amount_bomb++;
            if (field[x][y-1]   == 6)   amount_bomb++;
            field[x][y] = amount_bomb;
        }   
}


int main() {
    RenderWindow window(VideoMode(size_field*size_pixel, size_field*size_pixel), "Just explode this shit!");

    const short offset = size_pixel;

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
    unsigned short field[size_field][size_field];
    unsigned short show_field[size_field][size_field];

    init_field(field, true);
    init_field(show_field, false);

    generate_map(field);

    while (window.isOpen()) {
        //check_win(field, show_field);
        if (show_field[0][0] == 9) {
            usleep(1000000);
            window.close();
        }
        else if (show_field[0][0] == 10) {
            usleep(2000000);
            window.close();
        }
        Vector2i position = Mouse::getPosition(window);
        unsigned int x = position.x/size_pixel;
        unsigned int y = position.y/size_pixel;
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::KeyPressed)
                if (event.key.code == Keyboard::Escape)
                    window.close();
            if (event.type == Event::MouseButtonPressed)
                if (event.key.code == Mouse::Left) 
                    mine_handler(false, x, y, field, show_field);
                else if (event.key.code == Mouse::Right)
                    mine_handler(true, x, y, field, show_field);
        }

        // window.clear();

        for (short x = 0; x < 0xC; x++)
            for (short y = 0; y < 0xC; y++) {
                RectangleShape sqaure(Vector2f(size_pixel-2, size_pixel-2));

                if (dev) {

                    //                                               R     G     B
                    if (field[x][y] == 0) sqaure.setFillColor(Color(0x5D, 0x5D, 0x5D));
                    if (field[x][y] == 1) sqaure.setFillColor(Color(0x00, 0x80, 0xFF));
                    if (field[x][y] == 2) sqaure.setFillColor(Color(0x3A, 0xFF, 0x3A));
                    if (field[x][y] == 3) sqaure.setFillColor(Color(0xFF, 0xFF, 0x00));
                    if (field[x][y] == 4) sqaure.setFillColor(Color(0xFF, 0x3A, 0x3A));
                    if (field[x][y] == 5) sqaure.setFillColor(Color(0x80, 0x00, 0xFF));
                    if (field[x][y] == 6) sqaure.setFillColor(Color(0x00, 0x00, 0x00));
                    if (field[x][y] == 7) sqaure.setFillColor(Color(0xFF, 0xFF, 0xFF));
                    if (field[x][y] == 8) sqaure.setFillColor(Color(0xD1, 0xD1, 0xD1));
                    if (field[x][y] == 9) sqaure.setFillColor(Color(0xFF, 0x80, 0x00));
                    if (field[x][y] ==10) sqaure.setFillColor(Color(0x00, 0xFF, 0xFF));

                }

                else if (!dev) {
                    //                                                    R     G     B
                    if (show_field[x][y] == 0) sqaure.setFillColor(Color(0x5D, 0x5D, 0x5D));
                    if (show_field[x][y] == 1) sqaure.setFillColor(Color(0x00, 0x80, 0xFF));
                    if (show_field[x][y] == 2) sqaure.setFillColor(Color(0x3A, 0xFF, 0x3A));
                    if (show_field[x][y] == 3) sqaure.setFillColor(Color(0xFF, 0xFF, 0x00));
                    if (show_field[x][y] == 4) sqaure.setFillColor(Color(0xFF, 0x3A, 0x3A));
                    if (show_field[x][y] == 5) sqaure.setFillColor(Color(0x80, 0x00, 0xFF));
                    if (show_field[x][y] == 6) sqaure.setFillColor(Color(0x00, 0x00, 0x00));
                    if (show_field[x][y] == 7) sqaure.setFillColor(Color(0xFF, 0xFF, 0xFF));
                    if (show_field[x][y] == 8) sqaure.setFillColor(Color(0xD1, 0xD1, 0xD1));
                    if (show_field[x][y] == 9) sqaure.setFillColor(Color(0xFF, 0x80, 0x00));
                    if (show_field[x][y] ==10) sqaure.setFillColor(Color(0x00, 0xFF, 0xFF));
                }

                sqaure.setPosition((x*offset), (y*offset));
                window.draw(sqaure);
            }

        // window.draw(shape);
        window.display();
    }

    return 0;
}