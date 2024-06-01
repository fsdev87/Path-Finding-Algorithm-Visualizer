#pragma once
#include <SFML/Graphics.hpp>
#include "Maze.h"

using namespace sf;
using namespace std;

class Interface {
private:
	Maze maze;
public:
	void control(RenderWindow& window) {
		maze.draw(window);
	}
};