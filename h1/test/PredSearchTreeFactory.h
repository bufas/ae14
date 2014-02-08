#pragma once

#include <iostream>
#include "../PredSearchTree.h"
#include "../LinearSearch.h"
#include "../InorderBinarySearch.h"
#include "../BFSBinarySearch.h"
#include "../DFSBinarySearch.h"

class PredSearchTreeFactory {
public:
    PredSearchTreeFactory(const MemoryLayout &ml) : ml(ml) {}

    PredSearchTree* createTree(const std::vector<int> &values) {
        switch (ml) {
            case MemoryLayout::LINEAR:  return new LinearSearch(values); 
            case MemoryLayout::INORDER: return new InorderBinarySearch(values); 
            case MemoryLayout::BFS:     return new BFSBinarySearch(values); 
            case MemoryLayout::DFS:     return new DFSBinarySearch(values); 
            // TODO implement vEB
            default:
                std::cout << "THIS IS VERY WRONG!" << std::endl;
                exit(-1);
        }
    }

private:
    MemoryLayout ml;
};