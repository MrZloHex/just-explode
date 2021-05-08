#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

const short size_field = 0xC;
const short size_pixel = 0x19;


void null_field(unsigned short field[0xC][0xC]) {
    for (short i = 0; i < 0xD; i++) 
        for (short j = 0; j < 0xD; j++) {
            field[i][j] = 0;
        }
}


int main() {
    RenderWindow window(VideoMode((size_field*size_pixel) + (2*size_pixel), (size_field*size_pixel) + (2*size_pixel)), "Just explode this shit!");

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

        window.clear();
        // window.draw(shape);
        window.display();
    }

    return 0;
}