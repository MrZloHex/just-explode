#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

const short size_field = 0xC;
const short size_pixel = 0x19;

const bool dev = true; // false - normal mode; true - dev mode


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
            if (field[x][y] == 6) continue;
            if (field[x-1][y-1] == 6) amount_bomb++;
            if (field[x-1][y] == 6) amount_bomb++;
            if (field[x-1][y+1] == 6) amount_bomb++;
            if (field[x][y+1] == 6) amount_bomb++;
            if (field[x+1][y+1] == 6) amount_bomb++;
            if (field[x+1][y] == 6) amount_bomb++;
            if (field[x+1][y-1] == 6) amount_bomb++;
            if (field[x][y-1] == 6) amount_bomb++;
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
    */
    unsigned short field[size_field][size_field];
    unsigned short show_field[size_field][size_field];

    init_field(field, true);
    init_field(show_field, false);

    generate_map(field);

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::KeyPressed)
                if (event.key.code == Keyboard::Escape)
                    window.close();
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

                }

                else if (!dev) {
                    //                                                    R     G     B
                    if (show_field[x][y] == 0) sqaure.setFillColor(Color(0x1D, 0x1D, 0x1D));
                    if (show_field[x][y] == 1) sqaure.setFillColor(Color(0x00, 0x80, 0xFF));
                    if (show_field[x][y] == 2) sqaure.setFillColor(Color(0x3A, 0xFF, 0x3A));
                    if (show_field[x][y] == 3) sqaure.setFillColor(Color(0xFF, 0xFF, 0x00));
                    if (show_field[x][y] == 4) sqaure.setFillColor(Color(0xFF, 0x3A, 0x3A));
                    if (show_field[x][y] == 5) sqaure.setFillColor(Color(0x80, 0x00, 0xFF));
                    if (show_field[x][y] == 6) sqaure.setFillColor(Color(0x00, 0x00, 0x00));
                    if (show_field[x][y] == 7) sqaure.setFillColor(Color(0xFF, 0xFF, 0xFF));
                    if (show_field[x][y] == 8) sqaure.setFillColor(Color(0xD1, 0xD1, 0xD1));
                }

                sqaure.setPosition((x*offset), (y*offset));
                window.draw(sqaure);
            }

        // window.draw(shape);
        window.display();
    }

    return 0;
}