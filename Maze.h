#pragma once

#include <fstream>
#include <string>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Globals.h"
#include "MazeGeneration.h"
#include "PathFinding.h"

using namespace sf;
using namespace std;

enum Tile {
	Wall,
	Cell,
	CurrentCell,
	Start,
	End,
	Path
};

struct Node {
	Tile type;
	RectangleShape outer, inner;
	// add more

	Node(Tile type = Wall) : type(type) {}

	void setColors() {
		if (type == Wall) {
			inner.setFillColor(Color(0x00, 0x99, 0x99));
		}
		else if (type == Cell) {
			inner.setFillColor(Color(0x0e, 0x19, 0x1f));
		}
		else if (type == CurrentCell) {
			inner.setFillColor(Color::White);
		}
		else if (type == Start) {
			inner.setFillColor(Color::Green);
		}
		else if (type == End) {
			inner.setFillColor(Color::Red);
		}
		else if (type == Path) {
			inner.setFillColor(Color::Blue);
		}
	}

	void update(int xPos, int yPos) {
		outer.setFillColor(Color(0x0e, 0x19, 0x1f));
		outer.setSize(Vector2f(TILE_SIZE, TILE_SIZE));
		outer.setPosition(xPos * TILE_SIZE, yPos * TILE_SIZE);

		

		inner.setSize(Vector2f(TILE_SIZE - 2, TILE_SIZE - 2));
		inner.setPosition(outer.getPosition().x + 2, outer.getPosition().y + 2);
	}

	// functions here
	void render(RenderWindow& window) {
		window.draw(outer);
		window.draw(inner);
	}
};

class Maze {
private:
	vector<vector<char>> layout;
	vector<vector<Node>> maze;
	MazeGenerationAlgorithms::Algorithms generators;
	PathFindingAlgorithms::Algorithms finders;

	pair<int, int> start;
	pair<int, int> end;

	int generateChoice;
	int pathChoice;
public:

	Maze() {
		layout = vector<vector<char>>(MAZE_HEIGHT, vector<char>(MAZE_WIDTH, ' '));
		start = { 0, 0 };
		end = { 0, 0 };
		generateChoice = 0;
		pathChoice = 0;
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
				else if (layout[i][j] == 'C' || layout[i][j] == 'F' || layout[i][j] == 'P') {
					mapping[i][j].type = CurrentCell;
				}
				else if (layout[i][j] == 'S') {
					mapping[i][j].type = Start;
				}
				else if (layout[i][j] == 'E') {
					mapping[i][j].type = End;
				}
				else if (layout[i][j] == 'R') {
					mapping[i][j].type = Path;
				}
			}
		}
		return mapping;
	}

	bool generateMaze(int choice) {
		if (choice == 1) {
			return generators.generateMazeDFS(layout);
		}
		else if (choice == 2) {
			return generators.generateMazePrims(layout);
		}
		else if (choice == 3) {
			return generators.generateMazeKruskals(layout);
		}
		else if (choice == 4) {
			return generators.generateMazeWilsons(layout);
		}
	}

	void findPath(int choice) {
		if (choice == 1) {
			finders.findPathDFS(layout, start, end);
		}
		else if (choice == 2) {
			finders.findPathBFS(layout, start, end);
		}
		else if (choice == 3) {
			finders.findPathDijkstra(layout, start, end);
		}
		else if (choice == 4) {
			finders.findPathAStar(layout, start, end);
		}
	}

	void setChoiceGenerate (int n) {
		generateChoice = n;
	}

	void setChoicePath(int n) {
		pathChoice = n;
	}

	void resetPath() {
		pathChoice = 0;
		for (int i = 0; i < layout.size(); i++) {
			for (int j = 0; j < layout[0].size(); j++) {
				char cellVal = layout[i][j];
				string check = "CFPSER";
				for (char ch : check) {
					if (cellVal == ch) {
						layout[i][j] = ' ';
						break;
					}
				}
			}
		}
	}

	void reset() {
		start = { 0, 0 };
		end = { 0, 0 };
		generateChoice = 0;
		pathChoice = 0;
		generators.reset();
		for (int i = 0; i < layout.size(); i++) {
			for (int j = 0; j < layout[0].size(); j++) {
				if (i == 0 || j == 0 || i == layout.size() - 1 || j == layout[0].size() - 1) {
					layout[i][j] = '#';
				}
				else {
					layout[i][j] = ' ';
				}
			}
		}
	}

	void updateOnClick(RenderWindow& window, char selection) {
		for (int i = 0; i < maze.size(); i++) {
			for (int j = 0; j < maze[0].size(); j++) {
				Vector2i mousePos = Mouse::getPosition(window);
				FloatRect buttonBounds = maze[i][j].outer.getGlobalBounds();

				if (buttonBounds.contains(static_cast<Vector2f>(mousePos))) {
					if (Mouse::isButtonPressed(Mouse::Left)) {
						if (maze[i][j].type != Wall) {
							if (selection == 's') {
								
								start = { i, j };
								break;
							}
							else if (selection == 'e') {
								
								end = { i, j };
								break;
							}
						}
					}
				}
			}
		}
	}

	bool draw(RenderWindow& window, char selection) {
		bool status = true;
		if (generateChoice != 0) {
			if (generateMaze(generateChoice)) {
				status = false;
				if (start.first != 0 && start.second != 0) layout[start.first][start.second] = 'S';
				if (end.first != 0 && end.second != 0) layout[end.first][end.second] = 'E';
				if (pathChoice && start.first && start.second && end.first && end.second) findPath(pathChoice);
			}
		}
		else reset();
		
		maze = convertMaze();

		for (int i = 0; i < maze.size(); i++) {
			for (int j = 0; j < maze[0].size(); j++) {
				maze[i][j].update(j, i);
				if (maze[i][j].type == Start || maze[i][j].type == End) {
					maze[i][j].type = Cell;
				}
			}
		}

		updateOnClick(window, selection);

		maze[start.first][start.second].type = start.first == 0 ? maze[start.first][start.second].type : Start;
		maze[end.first][end.second].type = end.first == 0 ? maze[end.first][end.second].type : End;

		
		for (int i = 0; i < maze.size(); i++) {
			for (int j = 0; j < maze[0].size(); j++) {
				maze[i][j].setColors();
				maze[i][j].render(window);
			}
		}

		return status;
	}

};