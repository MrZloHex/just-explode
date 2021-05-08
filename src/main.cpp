#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

const short size_field = 0xC;
const short size_pixel = 0x19;


void null_field(unsigned short field[size_field][size_field]) {
    for (short i = 0; i < 0xC; i++) 
        for (short j = 0; j < 0xC; j++) {
            field[i][j] = 8;
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

    null_field(field);
    null_field(show_field);


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

                //                                               R     G     B
                if (field[x][y] == 0) sqaure.setFillColor(Color(0x1D, 0x1D, 0x1D));
                if (field[x][y] == 1) sqaure.setFillColor(Color(0x00, 0x80, 0xFF));
                if (field[x][y] == 2) sqaure.setFillColor(Color(0x3A, 0xFF, 0x3A));
                if (field[x][y] == 3) sqaure.setFillColor(Color(0xFF, 0xFF, 0x00));
                if (field[x][y] == 4) sqaure.setFillColor(Color(0xFF, 0x3A, 0x3A));
                if (field[x][y] == 5) sqaure.setFillColor(Color(0x80, 0x00, 0xFF));
                if (field[x][y] == 6) sqaure.setFillColor(Color(0x00, 0x00, 0x00));
                if (field[x][y] == 7) sqaure.setFillColor(Color(0xFF, 0xFF, 0xFF));
                if (field[x][y] == 8) sqaure.setFillColor(Color(0xD1, 0xD1, 0xD1));

                sqaure.setPosition((x*offset), (y*offset));
                window.draw(sqaure);
            }

        // window.draw(shape);
        window.display();
    }

    return 0;
}