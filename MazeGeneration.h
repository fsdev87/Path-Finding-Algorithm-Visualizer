#pragma once

#include <vector>
#include <stack>
#include <stdlib.h>
#include <iostream>
#include <unordered_set>
#include "Globals.h"

using namespace std;

// here add the maze generation algorithms
/*
1. DFS -> Done
2. Prim's
3. Kruskal
*/

namespace MazeGenerationAlgorithms {
	class Algorithms {
	public:
		void generateMazeDFS(vector<vector<char>>& maze) {
			dfs.updateMaze(maze);
		}

		void generateMazePrims(vector<vector<char>>& maze) {
			prims.updateMaze(maze);
		}

		void generateMazeKruskals(vector<vector<char>>& maze) {
			kruskals.updateMaze(maze);
		}


	private:
		class DFS {
		private:
			struct Cell {
				int i, j;
				Cell(int i, int j) : i(i), j(j) {}
				Cell(): i(0), j(0) {}
			};

			bool initialized;
			stack<Cell> st;
			Cell prevCell;
			bool visited[MAZE_HEIGHT][MAZE_WIDTH];

			bool isValidCell(Cell& cell) {
				return cell.i >= 1 && cell.i < (MAZE_HEIGHT - 1)
					&& cell.j >= 1 && cell.j < (MAZE_WIDTH - 1);
			}

			Cell generateRandomCell(vector<vector<char>>& maze) {
				srand(time(NULL));
				Cell result(-1, -1);
				result.i = 1 + rand() % (MAZE_HEIGHT - 1);
				result.j = 1 + rand() % (MAZE_WIDTH - 1);
				while (maze[result.i][result.j] == '#') {
					result.i = 1 + rand() % (MAZE_HEIGHT - 1);
					result.j = 1 + rand() % (MAZE_WIDTH - 1);
				}
				return result;
			}

			vector<Cell> getAdjCells(Cell& cell, bool visited[][MAZE_WIDTH]) {
				Cell up = Cell(cell.i - 2, cell.j);
				Cell down = Cell(cell.i + 2, cell.j);
				Cell left = Cell(cell.i, cell.j - 2);
				Cell right = Cell(cell.i, cell.j + 2);

				vector<Cell> cells;
				if (isValidCell(up) && !visited[up.i][up.j]) cells.push_back(up);
				if (isValidCell(down) && !visited[down.i][down.j]) cells.push_back(down);
				if (isValidCell(left) && !visited[left.i][left.j]) cells.push_back(left);
				if (isValidCell(right) && !visited[right.i][right.j]) cells.push_back(right);

				return cells;
			}

			void initialize(vector<vector<char>>& maze) {
				srand(time(NULL));

				for (int i = 0; i < maze.size(); i++) {
					for (int j = 0; j < maze[0].size(); j++) {
						if (i == 0 || j == 0 || i == maze.size() - 1 || j == maze[0].size() - 1) {
							maze[i][j] = '#';
						}
						if (i % 2 == 0 || j % 2 == 0) {
							maze[i][j] = '#';
						}
					}
				}
				Cell start = generateRandomCell(maze);
				visited[start.i][start.j] = true;
				st.push(start);
				initialized = true;
			}

		public:
			DFS() {
				initialized = false;
				for (int i = 0; i < MAZE_HEIGHT; i++) {
					for (int j = 0; j < MAZE_WIDTH; j++) {
						visited[i][j] = false;
					}
				}
			}

			void updateMaze(vector<vector<char>>& maze) {
				if (!initialized) initialize(maze);
				if (st.empty()) {
					//maze[prevCell.i][prevCell.j] = ' ';
					
					// the above line removes the cursor
					return;
				}

				Cell current = st.top();
				maze[current.i][current.j] = 'C';
				
				if (prevCell.i != 0 && prevCell.j != 0) maze[prevCell.i][prevCell.j] = ' ';
				
				st.pop();
				vector<Cell> adjacentCells = getAdjCells(current, visited);
				if (adjacentCells.size() > 0) { // this means valid neighbors exist
					st.push(current);
					int choice = rand() % adjacentCells.size();
					Cell selected = adjacentCells[choice];
					int dx = selected.j - current.j;
					int dy = selected.i - current.i;
					if (dy == 0 && dx > 0) { // the right cell
						maze[current.i][current.j + 1] = ' ';
					}
					else if (dy > 0 && dx == 0) { // the down cell
						maze[current.i + 1][current.j] = ' ';
					}
					else if (dy < 0 && dx == 0) { // the up cell
						maze[current.i - 1][current.j] = ' ';
					}
					else if (dy == 0 && dx < 0) { // the left cell
						maze[current.i][current.j - 1] = ' ';
					}
					visited[selected.i][selected.j] = true;
					st.push(selected);
				}
				prevCell = current;
			}
		};

		class Prims {
		private:

			struct Cell {
				int i, j;
				Cell(int i, int j) : i(i), j(j) {}
				Cell() : i(0), j(0) {}
			};

			bool initialized;
			vector<Cell> frontierCells;
			Cell current;

			bool isValid(Cell& cell) {
				return cell.i >= 1 && cell.i < (MAZE_HEIGHT - 1)
					&& cell.j >= 1 && cell.j < (MAZE_WIDTH - 1);
			}


			Cell generateRandomCell(vector<vector<char>>& maze) {
				srand(time(NULL));
				Cell result(-1, -1);
				result.i = 1 + rand() % (MAZE_HEIGHT - 1);
				result.j = 1 + rand() % (MAZE_WIDTH - 1);
				while (result.i % 2 == 0 || result.j % 2 == 0) {
					result.i = 1 + rand() % (MAZE_HEIGHT - 1);
					result.j = 1 + rand() % (MAZE_WIDTH - 1);
				}
				return result;
			}

			vector<Cell> computeFrontierCells(Cell& cell, vector<vector<char>>& maze) {
				Cell up = Cell(cell.i - 2, cell.j);
				Cell down = Cell(cell.i + 2, cell.j);
				Cell left = Cell(cell.i, cell.j - 2);
				Cell right = Cell(cell.i, cell.j + 2);
				
				vector<Cell> cells;
				if (isValid(up) && maze[up.i][up.j] == '#') cells.push_back(up);
				if (isValid(down) && maze[down.i][down.j] == '#') cells.push_back(down);
				if (isValid(left) && maze[left.i][left.j] == '#') cells.push_back(left);
				if (isValid(right) && maze[right.i][right.j] == '#') cells.push_back(right);

				for (Cell& c : cells) {
					maze[c.i][c.j] = 'F'; // mark it as frontier cell
				}

				return cells;
			}

			Cell getConnectingCell(Cell& frontier, vector<vector<char>>& maze) {
				vector<Cell> connections;

				Cell up = Cell(frontier.i - 2, frontier.j);
				Cell down = Cell(frontier.i + 2, frontier.j);
				Cell left = Cell(frontier.i, frontier.j - 2);
				Cell right = Cell(frontier.i, frontier.j + 2);

				if (isValid(up) && maze[up.i][up.j] == ' ') connections.push_back(up);
				if (isValid(down) && maze[down.i][down.j] == ' ') connections.push_back(down);
				if (isValid(left) && maze[left.i][left.j] == ' ') connections.push_back(left);
				if (isValid(right) && maze[right.i][right.j] == ' ') connections.push_back(right);

				if (!connections.empty()) {
					return connections[rand() % connections.size()];
				}

				return Cell();  // Return invalid cell if no valid connections found
			}

			void initialize(vector<vector<char>>& maze) {
				srand(time(NULL));

				for (int i = 0; i < maze.size(); i++) {
					for (int j = 0; j < maze[0].size(); j++) {
						maze[i][j] = '#';
					}
				}
				Cell start = generateRandomCell(maze);
				maze[start.i][start.j] = ' ';
				vector<Cell> frontiers = computeFrontierCells(start, maze);
				frontierCells.insert(frontierCells.end(), frontiers.begin(), frontiers.end());
				initialized = true;
				current = start;
			}

		public:
			Prims() {
				initialized = false;
			}

			void updateMaze(vector<vector<char>>& maze) {
				if (!initialized) initialize(maze);
				if (frontierCells.empty()) {
					return;
				}

				int choice = rand() % frontierCells.size();
				Cell currentFrontier = frontierCells[choice];

				Cell connectedCell = getConnectingCell(currentFrontier, maze);
				if (connectedCell.i == 0 && connectedCell.j == 0) {
					frontierCells.erase(frontierCells.begin() + choice);
					return;
				}

				int dx = currentFrontier.j - connectedCell.j;
				int dy = currentFrontier.i - connectedCell.i;
				if (dy == 0 && dx > 0) {  // the right cell
					maze[currentFrontier.i][currentFrontier.j - 1] = ' ';
				}
				else if (dy > 0 && dx == 0) {  // the down cell
					maze[currentFrontier.i - 1][currentFrontier.j] = ' ';
				}
				else if (dy < 0 && dx == 0) {  // the up cell
					maze[currentFrontier.i + 1][currentFrontier.j] = ' ';
				}
				else if (dy == 0 && dx < 0) {  // the left cell
					maze[currentFrontier.i][currentFrontier.j + 1] = ' ';
				}
				maze[currentFrontier.i][currentFrontier.j] = ' ';

				vector<Cell> frontiers = computeFrontierCells(currentFrontier, maze);
				frontierCells.erase(frontierCells.begin() + choice);
				frontierCells.insert(frontierCells.end(), frontiers.begin(), frontiers.end());
			}
		};

		class Kruskals {
		private:
			struct Cell {
				int x, y;
				Cell(int x_val, int y_val) : x(x_val), y(y_val) {}
				bool operator==(const Cell& other) const {
					return x == other.x && y == other.y;
				}
			};
			struct CellHash {
				std::size_t operator()(const Cell& cell) const {
					std::size_t h1 = std::hash<int>()(cell.x);
					std::size_t h2 = std::hash<int>()(cell.y);
					return h1 ^ (h2 << 1); 
				}
			};
			struct CellEqual {
				bool operator()(const Cell& lhs, const Cell& rhs) const {
					return lhs.x == rhs.x && lhs.y == rhs.y;
				}
			};

			vector<unordered_set<Cell, CellHash, CellEqual>> cellSets;
			vector<Cell> walls;
			bool initialized;
			int totalCells;
			int removedWalls;

			bool isValidCell(Cell& cell) {
				return cell.x >= 1 && cell.x < (MAZE_HEIGHT - 1)
					&& cell.y >= 1 && cell.y < (MAZE_WIDTH - 1);
			}

			bool findAndJoinSets(Cell& wall) {
				Cell up = Cell(wall.x - 1, wall.y);
				Cell down = Cell(wall.x + 1, wall.y);
				Cell left = Cell(wall.x, wall.y - 1);
				Cell right = Cell(wall.x, wall.y + 1);

				int verticalFirst = rand() % 2;
				if (verticalFirst) {
					if (isValidCell(up) && isValidCell(down)) {
						// check if these cells are in different sets. if they are then join the sets of the cells and return true

					}
					if (isValidCell(left) && isValidCell(right)) {

					}
				}
				else {
					if (isValidCell(left) && isValidCell(right)) {

					}
					if (isValidCell(down) && isValidCell(up)) {

					}
				}

				return false;
			}

			void initialize(vector<vector<char>>& maze) {
				srand(time(NULL));

				for (int i = 0; i < maze.size(); i++) {
					for (int j = 0; j < maze[0].size(); j++) {
						if (i == 0 || j == 0 || i == maze.size() - 1 || j == maze[0].size() - 1) {
							maze[i][j] = '#';
						}
						else if (i % 2 == 0 || j % 2 == 0) {
							maze[i][j] = '#';
							if (!(i % 2 == 0) || !(j % 2 == 0)) {
								walls.push_back(Cell(i, j));
							}
						}
						else {
							totalCells++;
						}
					}
				}
				initialized = true;
			}

		public:
			Kruskals() {
				initialized = false;
				removedWalls = 0;
				totalCells = 0;
			}

			void updateMaze(vector<vector<char>>& maze) {
				if (!initialized) initialize(maze);
				if (removedWalls >= (totalCells - 1)) return;

				int x = rand() % walls.size();
				Cell chosenWall = walls[x];
				if (findAndJoinSets(chosenWall)) {
					maze[chosenWall.x][chosenWall.y] = ' ';
					walls.erase(walls.begin() + x);
					removedWalls++;
				}
			}
		};

		private:
			DFS dfs;
			Prims prims;
			Kruskals kruskals;

		// add more algorithms and so on
	};
}

