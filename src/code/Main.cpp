#include "Algorithm.hpp"
#include "Functions.hpp"
#include <iostream>
/*#include <tuple>
#include <utility>*/
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

const bool dev = false; // false - normal mode, true - dev mode 

int main() {

    // initializating algorihm all fields of data
    auto algorithm = new Algorithm(12, 25);

    algorithm->init_fields();
    algorithm->generate_map();

    // initializating sfml window
    int size_window = algorithm->get_size_field() * algorithm->get_size_cell();
    RenderWindow window(VideoMode(size_window, size_window), "Just explode this shit!");

    // life cycle
    while (window.isOpen()) {
        // detecting dislocation of mouse pointer
        Vector2i position = Mouse::getPosition(window);
        unsigned int x = position.x/algorithm->get_size_cell();
        unsigned int y = position.y/algorithm->get_size_cell();


        //event object for pooling events
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::KeyPressed)
                if (event.key.code == Keyboard::Escape)
                    window.close();


            if (event.type == Event::MouseButtonPressed) {
                if (event.key.code == Mouse::Left) 
                    algorithm->bomb_handler(false, x, y);
                else if (event.key.code == Mouse::Right)
                    algorithm->bomb_handler(true, x, y);
            }
        }

        // update frame
        window.clear();

        for (short x = 0; x < algorithm->get_size_field(); x++)
            for (short y = 0; y < algorithm->get_size_field(); y++) {
                
                /*RectangleShape square(Vector2f(algorithm->get_size_cell(), algorithm->get_size_cell()));

                int *Colour = Colorize(algorithm->get_type_of_cell(dev, x, y));*/

                /*auto t = make_tuple(Colour[0], Colour[1], Colour[2], 0);
                square.setFillColor(std::apply(Color::Color, t));*/

                /*square.setFillColor(Color(Colour[0], Colour[1], Colour[2]));
          
                square.setPosition((x*algorithm->get_size_cell()), (y*algorithm->get_size_cell()));*/
                Texture texture;
                texture.loadFromFile("./src/img/1.png");
                Sprite square;
                square.setTexture(texture);
                square.setPosition((x*algorithm->get_size_cell()), (y*algorithm->get_size_cell()));
                window.draw(square);
            }   
        window.display();
    }

    delete algorithm;
    return 0;
}