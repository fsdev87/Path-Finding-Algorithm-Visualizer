#pragma once
#include <SFML/Graphics.hpp>
#include "Globals.h"
#include "Maze.h"
using namespace sf;

class Simulator {
private:
    Maze maze;
public:
	Simulator() {}
	void run() {
        RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Path Finder Simulator 2D");

        while (window.isOpen())
        {
            Event event;
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                    window.close();
            }

            window.clear();
            maze.draw(window);
            window.display();
        }
	}
};