#pragma once

#include <vector>
#include <stack>
#include <queue>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include "Globals.h"

using namespace std;

namespace PathFindingAlgorithms {
	class Algorithms {
	public:
		void findPathDFS(vector<vector<char>>& maze, pair<int, int> start, pair<int, int> end) {
			dfs.findPath(maze, start, end);
		}

		void findPathBFS(vector<vector<char>>& maze, pair<int, int> start, pair<int, int> end) {
			bfs.findPath(maze, start, end);
		}

		void findPathDijkstra(vector<vector<char>>& maze, pair<int, int> start, pair<int, int> end) {

		}

		void findPathAStar(vector<vector<char>>& maze, pair<int, int> start, pair<int, int> end) {

		}


	private:
		class DFS {
		private:
			struct Cell {
				int i, j;
				Cell(int i = 0, int j = 0) : i(i), j(j) {}
				bool operator==(const Cell& other) const {
					return i == other.i && j == other.j;
				}

				bool operator<(const Cell& other) const {
					return std::tie(i, j) < std::tie(other.i, other.j);
				}
			};
			bool initialized;
			map<Cell, Cell> parentMap;
			stack<Cell> st;
			vector<Cell> path;

			bool isValid(Cell& cell) {
				return cell.i >= 1 && cell.i < (MAZE_HEIGHT - 1)
					&& cell.j >= 1 && cell.j < (MAZE_WIDTH - 1);
			}

			vector<Cell> getAdjNodes(vector<vector<char>>& maze, Cell& cell) {
				Cell up = Cell(cell.i - 1, cell.j);
				Cell down = Cell(cell.i + 1, cell.j);
				Cell left = Cell(cell.i, cell.j - 1);
				Cell right = Cell(cell.i, cell.j + 1);

				vector<Cell> cells;
				if (isValid(up)) {
					char c = maze[up.i][up.j];
					if (c == ' ' || c == 'C' || c == 'E') {
						cells.push_back(up);
					}
				}
				if (isValid(down)) {
					char c = maze[down.i][down.j];
					if (c == ' ' || c == 'C' || c == 'E') {
						cells.push_back(down);
					}
				}
				if (isValid(left)) {
					char c = maze[left.i][left.j];
					if (c == ' ' || c == 'C' || c == 'E') {
						cells.push_back(left);
					}
				}
				if (isValid(right)) {
					char c = maze[right.i][right.j];
					if (c == ' ' || c == 'C' || c == 'E') {
						cells.push_back(right);
					}
				}
				return cells;
			}

			void reconstructPath(Cell end, Cell start) {
				path.clear();
				for (Cell at = end; !(at == start); at = parentMap[at]) {
					path.push_back(at);
				}
				std::reverse(path.begin(), path.end());
			}

			void initialize(pair<int, int> start, pair<int, int> end) {
				Cell startCell = Cell(start.first, start.second);
				st.push(startCell);
				parentMap[startCell] = startCell;
				initialized = true;
			}

		public:
			DFS() {
				initialized = false;
			}

			void findPath(vector<vector<char>>& maze, pair<int, int> start, pair<int, int> end) {
				if (!initialized) initialize(start, end);
				if (st.empty()) {
					return;
				}

				Cell current = st.top();
				st.pop();
				if (maze[current.i][current.j] != 'S' && maze[current.i][current.j] != 'E') {
					maze[current.i][current.j] = 'C';
				}
				if (maze[current.i][current.j] == 'E') {
					// then we have found the path
					reconstructPath(current, Cell(start.first, start.second));
					while (!st.empty()) {
						st.pop();
					}
					for (Cell& cell : path) {
						if (cell == current) continue;
						maze[cell.i][cell.j] = 'R';
					}
					return;
				}
				
				vector<Cell> adjCells = getAdjNodes(maze, current);
				for (Cell& next : adjCells) {
					if (parentMap.find(next) == parentMap.end()) {
						st.push(next);
						parentMap[next] = current;
					}
				}
			}
		};

		class BFS {
		private:
			struct Cell {
				int i, j;
				Cell(int i = 0, int j = 0) : i(i), j(j) {}
				bool operator==(const Cell& other) const {
					return i == other.i && j == other.j;
				}

				bool operator<(const Cell& other) const {
					return std::tie(i, j) < std::tie(other.i, other.j);
				}
			};
			bool initialized;
			queue<Cell> q;
			vector<Cell> path;
			bool visited[MAZE_HEIGHT][MAZE_WIDTH]{};
			map<Cell, Cell> parentMap;

			bool isValid(Cell& cell) {
				return cell.i >= 1 && cell.i < (MAZE_HEIGHT - 1)
					&& cell.j >= 1 && cell.j < (MAZE_WIDTH - 1);
			}

			void reconstructPath(Cell end, Cell start) {
				path.clear();
				for (Cell at = end; !(at == start); at = parentMap[at]) {
					path.push_back(at);
				}
				std::reverse(path.begin(), path.end());
			}

			vector<Cell> getAdjNodes(vector<vector<char>>& maze, Cell& cell) {
				Cell up = Cell(cell.i - 1, cell.j);
				Cell down = Cell(cell.i + 1, cell.j);
				Cell left = Cell(cell.i, cell.j - 1);
				Cell right = Cell(cell.i, cell.j + 1);

				vector<Cell> cells;
				if (isValid(up)) {
					char c = maze[up.i][up.j];
					if (c == ' ' || c == 'C' || c == 'E') {
						cells.push_back(up);
					}
				}
				if (isValid(down)) {
					char c = maze[down.i][down.j];
					if (c == ' ' || c == 'C' || c == 'E') {
						cells.push_back(down);
					}
				}
				if (isValid(left)) {
					char c = maze[left.i][left.j];
					if (c == ' ' || c == 'C' || c == 'E') {
						cells.push_back(left);
					}
				}
				if (isValid(right)) {
					char c = maze[right.i][right.j];
					if (c == ' ' || c == 'C' || c == 'E') {
						cells.push_back(right);
					}
				}
				return cells;
			}


			void initialize(pair<int, int> start, pair<int, int> end) {
				Cell startCell = Cell(start.first, start.second);
				q.push(startCell);
				initialized = true;
			}

		public:
			BFS() {
				initialized = false;
			}

			void findPath(vector<vector<char>>& maze, pair<int, int> start, pair<int, int> end) {
				if (!initialized) initialize(start, end);
				if (q.empty()) {
					return;
				}

				Cell current = q.front();
				q.pop();
				if (maze[current.i][current.j] != 'S' && maze[current.i][current.j] != 'E') {
					maze[current.i][current.j] = 'C';
				}
				if (maze[current.i][current.j] == 'E') {
					// then we have found the path
					reconstructPath(current, Cell(start.first, start.second));
					while (!q.empty()) {
						q.pop();
					}
					for (Cell& cell : path) {
						if (cell == current) continue;
						maze[cell.i][cell.j] = 'R';
					}
					return;
				}

				vector<Cell> adjCells = getAdjNodes(maze, current);
				for (Cell& next : adjCells) {
					if (visited[next.i][next.j] == false) {
						visited[next.i][next.j] = true;
						parentMap[next] = current;
						q.push(next);
					}
				}
			}
		};

		class Dijkstra {

		};

		class AStar {

		};

		DFS dfs;
		BFS bfs;
		Dijkstra dijkstra;
		AStar aStar;

	};

	
}