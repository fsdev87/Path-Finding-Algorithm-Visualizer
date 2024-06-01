#pragma once

#include <vector>
#include <stack>
#include <stdlib.h>
#include <iostream>
#include <iterator>
#include <unordered_set>
#include <algorithm>
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

		void generateMazeWilsons(vector<vector<char>>& maze) {
			wilsons.updateMaze(maze);
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

			vector<unordered_set<Cell, CellHash, CellEqual>> CellSets;
			vector<Cell> walls;
			bool initialized;
			int totalCells;
			int removedWalls;

			bool isValidCell(Cell& cell) {
				return cell.x >= 1 && cell.x < (MAZE_HEIGHT - 1)
					&& cell.y >= 1 && cell.y < (MAZE_WIDTH - 1);
			}

			bool findAndJoinSets(Cell& cell1, Cell& cell2) {
				// Find the sets containing cell1 and cell2
				auto set1Iter = CellSets.end();
				auto set2Iter = CellSets.end();

				for (auto it = CellSets.begin(); it != CellSets.end(); ++it) {
					if (it->find(cell1) != it->end()) {
						set1Iter = it;
					}
					if (it->find(cell2) != it->end()) {
						set2Iter = it;
					}
					if (set1Iter != CellSets.end() && set2Iter != CellSets.end()) {
						break;  // Both sets found
					}
				}

				// Check if they are in different sets
				if (set1Iter != set2Iter) {
					// Join the sets
					if (set1Iter != CellSets.end() && set2Iter != CellSets.end()) {
						set1Iter->insert(set2Iter->begin(), set2Iter->end());
						CellSets.erase(set2Iter);
					}
					return true;
				}

				// Both cells are in the same set
				return false;
			}

			bool relaxation(Cell& wall) {
				Cell up = Cell(wall.x - 1, wall.y);
				Cell down = Cell(wall.x + 1, wall.y);
				Cell left = Cell(wall.x, wall.y - 1);
				Cell right = Cell(wall.x, wall.y + 1);

				int verticalFirst = rand() % 2;
				if (verticalFirst) {
					if (isValidCell(up) && isValidCell(down)) {
						if (findAndJoinSets(up, down)) {
							return true;
						}
					}
					if (isValidCell(left) && isValidCell(right)) {
						if (findAndJoinSets(left, right)) {
							return true;
						}
					}
				}
				else {
					if (isValidCell(left) && isValidCell(right)) {
						if (findAndJoinSets(left, right)) {
							return true;
						}
					}
					if (isValidCell(down) && isValidCell(up)) {
						if (findAndJoinSets(up, down)) {
							return true;
						}
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
							unordered_set<Cell, CellHash, CellEqual> newSet = { Cell(i, j) };
							CellSets.push_back(newSet);
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
				if (relaxation(chosenWall)) {
					maze[chosenWall.x][chosenWall.y] = ' ';
					walls.erase(walls.begin() + x);
					removedWalls++;
				}
			}
		};

		class Wilsons {
		private:
			struct Cell {
				int x, y;
				Cell(int x_val, int y_val) : x(x_val), y(y_val) {}
				Cell() {}
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

			bool initialized;
			unordered_set<Cell, CellHash, CellEqual> visited;
			unordered_set<Cell, CellHash, CellEqual> unvisited;
			vector<Cell> path;

			bool isValidCell(Cell cell) {
				return cell.x >= 1 && cell.x < (MAZE_HEIGHT - 1)
					&& cell.y >= 1 && cell.y < (MAZE_WIDTH - 1);
			}

			Cell generateRandomCell() {
				srand(time(NULL));
				Cell result(-1, -1);
				result.x = 1 + rand() % (MAZE_HEIGHT - 1);
				result.y = 1 + rand() % (MAZE_WIDTH - 1);
				while (result.x % 2 == 0 || result.y % 2 == 0) {
					result.x = 1 + rand() % (MAZE_HEIGHT - 1);
					result.y = 1 + rand() % (MAZE_WIDTH - 1);
				}
				return result;
			}

			vector<Cell> possibleMoves(Cell& cell) {
				Cell up = Cell(cell.x - 2, cell.y);
				Cell down = Cell(cell.x + 2, cell.y);
				Cell left = Cell(cell.x, cell.y - 2);
				Cell right = Cell(cell.x, cell.y + 2);

				vector<Cell> cells;
				if (isValidCell(up)) cells.push_back(up);
				if (isValidCell(down)) cells.push_back(down);
				if (isValidCell(left)) cells.push_back(left);
				if (isValidCell(right)) cells.push_back(right);

				return cells;
			}

			char checkCellDir(Cell& current, Cell& next) { // check where the next cell is relative to current
				int dx = current.y - next.y;
				int dy = current.x - next.x;
				if (dy == 0 && dx > 0) {  // the right cell
					return 'r';
				}
				else if (dy > 0 && dx == 0) {  // the down cell
					return 'd';
				}
				else if (dy < 0 && dx == 0) {  // the up cell
					return 'u';
				}
				else if (dy == 0 && dx < 0) {  // the left cell
					return 'l';
				}
			}

			void eraseLoop(vector<vector<char>>& maze, Cell& intersectingCell) {
				if (intersectingCell == path.back()) return;
				Cell prev;
				while (!(path.back() == intersectingCell)) {
					maze[path.back().x][path.back().y] = '#';
					prev = path.back();
					path.pop_back();
					int dir = checkCellDir(path.back(), prev);
					switch (dir)
					{
					case 'r': maze[prev.x][prev.y + 1] = '#'; break;
					case 'd': maze[prev.x + 1][prev.y] = '#'; break;
					case 'u': maze[prev.x - 1][prev.y] = '#'; break;
					case 'l': maze[prev.x][prev.y - 1] = '#'; break;
					default: break;
					}
				}
			}

			void randomWalk(vector<vector<char>>& maze, Cell& start) {
				if (start == Cell(0, 0)) { // path is already being made
					vector<Cell> moves = possibleMoves(path.back());
					Cell nextCell = moves[rand() % moves.size()];
					if (find(path.begin(), path.end(), nextCell) == path.end()) {
						char dir = checkCellDir(path.back(), nextCell);
						path.push_back(nextCell);
						maze[nextCell.x][nextCell.y] = 'P';
						cout << dir << endl;
						switch (dir)
						{
							case 'r': maze[nextCell.x][nextCell.y + 1] = 'P'; break;
							case 'd': maze[nextCell.x + 1][nextCell.y] = 'P'; break;
							case 'u': maze[nextCell.x - 1][nextCell.y] = 'P'; break;
							case 'l': maze[nextCell.x][nextCell.y - 1] = 'P'; break;
							default: break;
						}
					}
					else {
						eraseLoop(maze, nextCell);
					}
				}
				else {
					path.push_back(start);
					maze[start.x][start.y] = 'P';
				}
			}

			void addPathToMaze(vector<vector<char>>& maze) {
				Cell prev;
				while (!path.empty()) {
					maze[path.back().x][path.back().y] = ' ';
					unvisited.erase(path.back());
					visited.insert(path.back());
					prev = path.back();
					path.pop_back();
					if (!path.empty()) {
						int dir = checkCellDir(path.back(), prev);
						switch (dir)
						{
						case 'r': maze[prev.x][prev.y + 1] = ' '; break;
						case 'd': maze[prev.x + 1][prev.y] = ' '; break;
						case 'u': maze[prev.x - 1][prev.y] = ' '; break;
						case 'l': maze[prev.x][prev.y - 1] = ' '; break;
						default: break;
						}
					}
				}
			}
			
			void initialize(vector<vector<char>>& maze) {
				srand(time(NULL));
				for (int i = 0; i < maze.size(); i++) {
					for (int j = 0; j < maze[0].size(); j++) {
						maze[i][j] = '#';
						if (i % 2 != 0 && j % 2 != 0 && isValidCell(Cell(i, j))) {
							unvisited.insert(Cell(i, j));
						}
					}
				}
				Cell first = generateRandomCell();
				maze[first.x][first.y] = ' ';
				unvisited.erase(first);
				visited.insert(first);
				initialized = true;
			}

		public:
			Wilsons() {
				initialized = false;
			}

			void updateMaze(vector<vector<char>>& maze) {
				if (!initialized) initialize(maze);
				if (unvisited.size() == 0) return;
				Cell pathStart(0, 0);
				if (path.size() == 0) { // then get a random cell from the unvisited set
					int randomIndex = rand() % unvisited.size();
					auto it = unvisited.begin();
					advance(it, randomIndex);
					pathStart = *it;
				}
				randomWalk(maze, pathStart);
				if (visited.find(path.back()) != visited.end()) {
					addPathToMaze(maze);
				}
			}
		};

		private:
			DFS dfs;
			Prims prims;
			Kruskals kruskals;
			Wilsons wilsons;

		// add more algorithms and so on
	};
}

