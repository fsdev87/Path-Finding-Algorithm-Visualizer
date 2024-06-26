#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Globals.h"
using namespace sf;
using namespace std;

enum Tile {
	Wall,
	Cell
};

struct Node {
	Tile type;
	// add more

	Node(Tile type = Wall) : type(type) {}

	// functions here
	void draw(RenderWindow& window, int xPos, int yPos) {
		RectangleShape outer, inner;
		outer.setFillColor(Color::Black);
		outer.setSize(Vector2f(TILE_SIZE, TILE_SIZE));
		outer.setPosition(xPos * TILE_SIZE, yPos * TILE_SIZE);

		if (type == Wall) {
			inner.setFillColor(Color::White);
		}
		else {
			inner.setFillColor(Color::Black);
		}

		inner.setSize(Vector2f(TILE_SIZE - 2, TILE_SIZE - 2));
		inner.setPosition(outer.getPosition().x + 2, outer.getPosition().y + 2);

		window.draw(outer);
		window.draw(inner);
	}
};

class Maze {
private:
	vector<vector<char>> layout;
	vector<vector<Node>> maze;
public:
	Maze() {
		layout = generateMazeDFS();
		maze = convertMaze();
	}
	vector<vector<Node>> convertMaze() {
		vector<vector<Node>> mapping(MAZE_HEIGHT, vector<Node>(MAZE_WIDTH));
		for (int i = 0; i < layout.size(); i++) {
			for (int j = 0; j < layout[0].size(); j++) {
				if (layout[i][j] == ' ') {
					mapping[i][j].type = Cell;
				}
				else if (layout[i][j] == '#') {
					mapping[i][j].type = Wall;
				}
			}
		}
		return mapping;
	}

	vector<vector<char>> generateMazeDFS() {
		vector<vector<char>> layoutMap(MAZE_HEIGHT, vector<char>(MAZE_WIDTH, ' '));
		for (int i = 0; i < layoutMap.size(); i++) {
			for (int j = 0; j < layoutMap[0].size(); j++) {
				if (i == 0 || j == 0 || i == layoutMap.size() - 1 || j == layoutMap[0].size() - 1) {
					layoutMap[i][j] = '#';
				}
				if (i % 2 == 0 || j % 2 == 0) {
					layoutMap[i][j] = '#';
				}
			}
		}


		return layoutMap;
	}

	vector<vector<char>> generateMazeRandom() {
		srand(time(0)); // to generate random maze
		// note: random maze generation is temporary we will change it to prim's algorithm soon

		vector<vector<char>> layoutMap(MAZE_HEIGHT, vector<char>(MAZE_WIDTH, ' '));
		for (int i = 0; i < layoutMap.size(); i++) {
			for (int j = 0; j < layoutMap[0].size(); j++) {
				if (i == 0 || j == 0 || i == layoutMap.size() - 1 || j == layoutMap[0].size() - 1) {
					layoutMap[i][j] = '#';
				}
				else {
					int x = rand() % 4;
					if (x == 0) {
						layoutMap[i][j] = '#';
					}
					else {
						layoutMap[i][j] = ' ';
					}
				}
			}
		}

		return layoutMap;
	}

	void draw(RenderWindow& window) {
		for (int i = 0; i < maze.size(); i++) {
			for (int j = 0; j < maze[0].size(); j++) {
				maze[i][j].draw(window, j, i);
			}
		}
	}
};