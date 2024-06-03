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
	// add more

	Node(Tile type = Wall) : type(type) {}

	// functions here
	void draw(RenderWindow& window, int xPos, int yPos) {
		RectangleShape outer, inner;
		outer.setFillColor(Color(0x0e, 0x19, 0x1f));
		outer.setSize(Vector2f(TILE_SIZE, TILE_SIZE));
		outer.setPosition(xPos * TILE_SIZE, yPos * TILE_SIZE);

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
	MazeGenerationAlgorithms::Algorithms generators;
	PathFindingAlgorithms::Algorithms finders;

	pair<int, int> start;
	pair<int, int> end;

	int generateChoice;
	int pathChoice;
public:

	void read2DArrayFromFile(std::vector<std::vector<char>>& array, const std::string& filename) {
		std::ifstream inFile(filename);

		if (!inFile) {
			std::cerr << "Error opening file for reading: " << filename << std::endl;
			return;
		}

		std::string line;
		while (std::getline(inFile, line)) {
			std::vector<char> row;
			for (int i = 0; i < line.length(); i++) {
				if (i % 2 == 0) {
					row.push_back(line[i]);
				}
			}
			array.push_back(row);
		}

		inFile.close();
	}

	Maze() {
		//layout = vector<vector<char>>(MAZE_HEIGHT, vector<char>(MAZE_WIDTH, ' '));
		start = {1, 1};
		end = { 23, 39 };
		read2DArrayFromFile(layout, "Maze.txt");
		layout[start.first][start.second] = 'S';
		layout[end.first][end.second] = 'E';
		generateChoice = 0;
		pathChoice = 4;
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

	void generateMaze(int choice) {
		if (choice == 1) {
			generators.generateMazeDFS(layout);
		}
		else if (choice == 2) {
			generators.generateMazePrims(layout);
		}
		else if (choice == 3) {
			generators.generateMazeKruskals(layout);
		}
		else if (choice == 4) {
			generators.generateMazeWilsons(layout);
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

	void reset() {
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

	void draw(RenderWindow& window) {
		if (generateChoice != 0) generateMaze(generateChoice);
		//else reset();

		if (pathChoice != 0) findPath(pathChoice);

		maze = convertMaze();

		for (int i = 0; i < maze.size(); i++) {
			for (int j = 0; j < maze[0].size(); j++) {
				maze[i][j].draw(window, j, i);
			}
		}
	}

};