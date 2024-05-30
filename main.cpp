#include "Simulator.h"
#include <iostream>
#include <unordered_set>

// Define the CELL struct
struct CELL {
    int x, y;

    CELL(int x_val, int y_val) : x(x_val), y(y_val) {}

    // Overload the equality operator for CELL
    bool operator==(const CELL& other) const {
        return x == other.x && y == other.y;
    }
};

// Define a hash function for CELL
struct CELLHash {
    std::size_t operator()(const CELL& cell) const {
        std::size_t h1 = std::hash<int>()(cell.x);
        std::size_t h2 = std::hash<int>()(cell.y);
        // Combine the two hash values using bitwise operations
        return h1 ^ (h2 << 1); // or (h1 * 31) + h2;
    }
};

// Define an equality function for CELL
struct CELLEqual {
    bool operator()(const CELL& lhs, const CELL& rhs) const {
        return lhs.x == rhs.x && lhs.y == rhs.y;
    }
};

int main() {
    // Create an unordered_set for CELL
    std::unordered_set<CELL, CELLHash, CELLEqual> cellSet;

    // Insert elements into the set
    cellSet.insert(CELL(1, 2));
    cellSet.insert(CELL(3, 4));
    cellSet.insert(CELL(23, 3));
    cellSet.insert(CELL(3, 43));
    cellSet.insert(CELL(43, 22));
    cellSet.insert(CELL(43, 3));
    cellSet.insert(CELL(3, 33));

    // Check for existence
    if (cellSet.find(CELL(3, 43)) != cellSet.end()) {
        std::cout << "CELL(3, 43) is in the set" << std::endl;
    }

    // Erase an element
    cellSet.erase(CELL(43, 3));

    // Check for existence after erasing
    if (cellSet.find(CELL(43, 3)) == cellSet.end()) {
        std::cout << "CELL(43, 3) is not in the set" << std::endl;
    }


    // to merge two cells
    // cell.insert(cell.begin(), cell.end())
    return 0;
}

//int main() {
//	Simulator sim;
//	sim.run();
//
//
//	return 0;
//}
