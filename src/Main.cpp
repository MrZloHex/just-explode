#include "Algorithm.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

int main() {
    // initializating algorihm all fields of data
    auto algorithm = new Algorithm(0xC, 0x19);

    algorithm->init_fields();
    algorithm->generate_map();

    // initializating sfml window
    int size_window = algorithm->get_size_field() * algorithm->get_size_cell();
    RenderWindow window(VideoMode(size_window, size_window), "Just explode this shit!");

    // life cycle
    while (window.isOpen()) {
        // detecting dislocation of mouse pointer
        /*Vector2i position = Mouse::getPosition(window);
        unsigned int x = position.x/algorithm.get_size_cell();
        unsigned int y = position.y/algorithm.get_size_cell();*/


        //event object for pooling events
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::KeyPressed)
                if (event.key.code == Keyboard::Escape)
                    window.close();


            /*if (event.type == Event::MouseButtonPressed)
                if (event.key.code == Mouse::Left) 
                    algorithn.bomb_handler(false, x, y, field, show_field);
                else if (event.key.code == Mouse::Right)
                    algorithm.bomb_handler(true, x, y, field, show_field);*/
        }

        // update frame
        for (short x = 0; x < algorithm->get_size_field(); x++)
            for (short y = 0; y < algorithm->get_size_field(); y++) {
                RectangleShape square(Vector2f(algorithm->get_size_cell()-2, algorithm->get_size_cell()-2));

                square.setFillColor(Color(0xFF, 0, 0));

                square.setPosition((x*algorithm->get_size_cell()), (y*algorithm->get_size_cell()));
                window.draw(square);
            }

        //illustration.test();

        window.display();
    }

    delete algorithm;
    
    return 0;
}