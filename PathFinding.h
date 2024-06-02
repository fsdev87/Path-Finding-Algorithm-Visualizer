#pragma once

#include <vector>
#include <stack>
#include <queue>
#include <unordered_map>
#include <unordered_set>

using namespace std;

namespace PathFindingAlgorithms {
	class Algorithms {
	public:
		void findPathDFS(vector<vector<char>>& maze, pair<int, int> start, pair<int, int> end) {

		}

		void findPathBFS(vector<vector<char>>& maze, pair<int, int> start, pair<int, int> end) {

		}

		void findPathDijkstra(vector<vector<char>>& maze, pair<int, int> start, pair<int, int> end) {

		}

		void findPathAStar(vector<vector<char>>& maze, pair<int, int> start, pair<int, int> end) {

		}


	private:
		class DFS {
		private:

		public:
			DFS() {

			}
		};

		class BFS {

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