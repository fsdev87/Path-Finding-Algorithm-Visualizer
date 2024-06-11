#pragma once

#include <vector>
#include <stack>
#include <queue>
#include <cmath>
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
			dijkstra.findPath(maze, start, end);
		}

		void findPathAStar(vector<vector<char>>& maze, pair<int, int> start, pair<int, int> end) {
			aStar.findPath(maze, start, end);
		}

		void reset() {
			dfs.reset();
			bfs.reset();
			dijkstra.reset();
			aStar.reset();
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

			void reset() {
				initialized = false;
				parentMap.clear();
				while (!st.empty()) {
					st.pop();
				}
				path.clear();
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

			void reset() {
				initialized = false;
				while (!q.empty()) q.pop();
				path.clear();
				for (int i = 0; i < MAZE_HEIGHT; i++) {
					for (int j = 0; j < MAZE_WIDTH; j++) {
						visited[i][j] = false;
					}
				}
				parentMap.clear();
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

			struct CellPriority {
				Cell cell;
				int priority;

				bool operator>(const CellPriority& other) const {
					return priority > other.priority;
				}
			};

			bool initialized;
			priority_queue<CellPriority, vector<CellPriority>, greater<CellPriority>> pq;
			vector<Cell> path;
			map<Cell, Cell> parentMap;
			map<Cell, int> distances;


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
				pq.push({ startCell, 0 });
				distances[startCell] = 0;
				parentMap[startCell] = startCell;
				initialized = true;
			}

		public:
			Dijkstra() {
				initialized = false;
			}

			void reset() {
				initialized = false;
				while (!pq.empty()) pq.pop();
				path.clear();
				parentMap.clear();
				distances.clear();
			}

			void findPath(vector<vector<char>>& maze, pair<int, int> start, pair<int, int> end) {
				if (!initialized) initialize(start, end);
				if (pq.empty()) {
					return;
				}
				CellPriority currentPriority = pq.top();
				Cell current = currentPriority.cell;
				pq.pop();
				if (maze[current.i][current.j] != 'S' && maze[current.i][current.j] != 'E') {
					maze[current.i][current.j] = 'C';
				}
				if (maze[current.i][current.j] == 'E') {
					// then we have found the path
					reconstructPath(current, Cell(start.first, start.second));
					while (!pq.empty()) {
						pq.pop();
					}
					for (Cell& cell : path) {
						if (cell == current) continue;
						maze[cell.i][cell.j] = 'R';
					}
					return;
				}

				vector<Cell> adjCells = getAdjNodes(maze, current);
				for (Cell& next : adjCells) {
					int newDist = distances[current] + 1;
					if (distances[next]) {
						if (newDist < distances[next]) {
							distances[next] = newDist;
							parentMap[next] = current;
							pq.push({ next, newDist });
						}
					}
					else {
						distances[next] = newDist;
						parentMap[next] = current;
						pq.push({ next, newDist });
					}
				}
			}
		};

		class AStar {
		private:
			struct Cell {
				int i, j;
				int f, g, h;
				Cell(int i = 0, int j = 0) : i(i), j(j) {
					f = 0; g = 0; h = 0;
				}
				bool operator==(const Cell& other) const {
					return i == other.i && j == other.j;
				}

				bool operator<(const Cell& other) const {
					return std::tie(i, j) < std::tie(other.i, other.j);
				}
			};


			bool initialized;
			vector<Cell> path;
			map<Cell, Cell> parentMap;
			vector<Cell> openList;
			vector<Cell> closedList;

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
					if (c == ' ' || c == 'E') {
						cells.push_back(up);
					}
				}
				if (isValid(down)) {
					char c = maze[down.i][down.j];
					if (c == ' ' || c == 'E') {
						cells.push_back(down);
					}
				}
				if (isValid(left)) {
					char c = maze[left.i][left.j];
					if (c == ' ' || c == 'E') {
						cells.push_back(left);
					}
				}
				if (isValid(right)) {
					char c = maze[right.i][right.j];
					if (c == ' ' || c == 'E') {
						cells.push_back(right);
					}
				}
				return cells;
			}


			void initialize(pair<int, int> start, pair<int, int> end) {
				Cell startCell = Cell(start.first, start.second);
				openList.push_back(startCell);
				parentMap[startCell] = startCell;
				initialized = true;
			}

		public:
			AStar() {
				initialized = false;
			}

			void reset() {
				initialized = false;
				path.clear();
				parentMap.clear();
				openList.clear();
				closedList.clear();
			}

			void findPath(vector<vector<char>>& maze, pair<int, int> start, pair<int, int> end) {
				if (!initialized) initialize(start, end);
				if (openList.empty()) {
					return;
				}
				Cell current = openList[0];
				int currentIndex = 0;
				for (int i = 0; i < openList.size(); i++) {
					if (openList[i].f < current.f) {
						current = openList[i];
						currentIndex = i;
					}
				}
				openList.erase(openList.begin() + currentIndex);
				closedList.push_back(current);

				if (maze[current.i][current.j] != 'S' && maze[current.i][current.j] != 'E') {
					maze[current.i][current.j] = 'C';
				}

				if (maze[current.i][current.j] == 'E') {
					// then we have found the path
					reconstructPath(current, Cell(start.first, start.second));
					openList.clear();
					for (Cell& cell : path) {
						if (cell == current) continue;
						maze[cell.i][cell.j] = 'R';
					}
					return;
				}

				vector<Cell> adjCells = getAdjNodes(maze, current);

				for (Cell& next : adjCells) {
					if (find(closedList.begin(), closedList.end(), next) != closedList.end()) {
						return;
					}

					next.g = current.g + 1;
					next.h = pow(next.i - end.first, 2) + pow(next.j - end.second, 2);
					next.f = next.g + next.h;

					for (Cell& openCell : openList) {
						if (next == openCell && next.g > openCell.g) {
							return;
						}
					}
					parentMap[next] = current;
					openList.push_back(next);
				}
			}
		};

		DFS dfs;
		BFS bfs;
		Dijkstra dijkstra;
		AStar aStar;

	};

	
}