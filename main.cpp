#include "Simulator.h"
#include <iostream>
#include <unordered_set>



//int main() {
//    // Create an unordered_set for CELL
//    std::unordered_set<CELL, CELLHash, CELLEqual> cellSet;
//
//    // Insert elements into the set
//    cellSet.insert(CELL(1, 2));
//    cellSet.insert(CELL(3, 4));
//    cellSet.insert(CELL(23, 3));
//    cellSet.insert(CELL(3, 43));
//    cellSet.insert(CELL(43, 22));
//    cellSet.insert(CELL(43, 3));
//    cellSet.insert(CELL(3, 33));
//
//    // Check for existence
//    if (cellSet.find(CELL(3, 43)) != cellSet.end()) {
//        std::cout << "CELL(3, 43) is in the set" << std::endl;
//    }
//
//    // Erase an element
//    cellSet.erase(CELL(43, 3));
//
//    // Check for existence after erasing
//    if (cellSet.find(CELL(43, 3)) == cellSet.end()) {
//        std::cout << "CELL(43, 3) is not in the set" << std::endl;
//    }
//    
//
//
//    // to merge two cells
//    // cell.insert(cell.begin(), cell.end())
//    return 0;
//}

int main() {
	Simulator sim;
	sim.run();


	return 0;
}
