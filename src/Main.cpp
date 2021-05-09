#include "Algorithm.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;

int main() {
    // initializating algorihm all fields of data
    Algorithm algorithm(0xC, 0x19);

    algorithm.init_fields();
    algorithm.generate_map();

    // initializating sfml window
    int size_window = algorithm.get_size_field() * algorithm.get_size_cell();
    RenderWindow window(VideoMode(size_window, size_window), "Just explode this shit!");

    // life cycle
    while (window.isOpen()) {
        //event object for pooling events
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::KeyPressed)
                if (event.key.code == Keyboard::Escape)
                    window.close();
        }

        // update frame
        window.clear();
        window.display();
    }

    return 0;
}