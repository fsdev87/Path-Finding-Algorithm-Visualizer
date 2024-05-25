#pragma once

#include <vector>
#include <stack>
#include <stdlib.h>
#include "Globals.h"

using namespace std;

// here add the maze generation algorithms
/*
1. DFS
2. Prim's
3. Kruskal
*/

namespace MazeGenerationAlgorithms {
	class Algorithms {
	public:
		static void generateMazeDFS(vector<vector<char>>& maze) {
			DFS::generateMaze(maze);
		}

		static void generateMazePrims(vector<vector<char>>& maze) {
			Prims::generateMaze(maze);
		}

	private:
		class DFS {
		private:
			struct Cell {
				int i, j;
				Cell(int i, int j) : i(i), j(j) {}
			};

			bool isValidCell(Cell& cell) {
				return cell.i >= 1 && cell.i < (MAZE_HEIGHT - 1)
					&& cell.j >= 1 && cell.j < (MAZE_WIDTH - 1);
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


		public:

			static void generateMaze(vector<vector<char>>& maze) {
				stack<Cell> st;
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

				bool visited[MAZE_HEIGHT][MAZE_WIDTH]{};
				

			}
		};

		class Prims {
		private:

		public:
			static void generateMaze(vector<vector<char>>& maze) {

			}
		};

		// add more algorithms and so on
	};
}

