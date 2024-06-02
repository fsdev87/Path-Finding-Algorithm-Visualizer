#pragma once
#include <SFML/Graphics.hpp>
#include "Globals.h"
#include "Interface.h"
using namespace sf;

class Simulator {
private:
    RenderWindow window;
    //Interface interface;

    Maze maze;
public:
	Simulator():window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Path Finder Simulator 2D") {
        window.setFramerateLimit(30);
    }
	void run() {

        while (window.isOpen())
        {
            Event event;
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                    window.close();
            }

            window.clear(Color(0x0e, 0x19, 0x1f));
            //interface.control(window);
            maze.draw(window);
            window.display();
        }
	}
};