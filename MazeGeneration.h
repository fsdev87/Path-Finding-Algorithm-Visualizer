#pragma once

#include <vector>
#include <stdlib.h>

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
		public:
			static void generateMaze(vector<vector<char>>& maze) {
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
			}
		};

		class Prims {
		public:
			static void generateMaze(vector<vector<char>>& maze) {

			}
		};

		// add more algorithms and so on
	};
}

