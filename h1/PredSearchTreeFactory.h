#pragma once

#include <iostream>
#include "MemoryLayout.h"
#include "PredSearchTree.h"

#include "LinearSearch.h"

#include "InorderBinarySearch.h"
// #include "InorderBinarySearchExplicit.h"
// #include "InorderBinarySearchExplicitInt.h"

#include "BFSBinarySearch.h"
#include "BFSBinarySearchExplicit.h"
#include "BFSBinarySearchExplicitInt.h"

#include "DFSBinarySearch.h"
#include "DFSBinarySearchExplicit.h"
#include "DFSBinarySearchExplicitInt.h"

// #include "VEBBinarySearch.h"
// #include "VEBBinarySearchExplicit.h"
#include "VEBBinarySearchExplicitInt.h"

class PredSearchTreeFactory {
public:
    PredSearchTreeFactory(const MemoryLayout &ml) : ml(ml) {}

    PredSearchTree* createTree(const std::vector<int> &values) {
        switch (ml) {
            case MemoryLayout::LINEAR:  return new LinearSearch(values); 
            case MemoryLayout::INORDER: return new InorderBinarySearch(values); 
            case MemoryLayout::BFS:     return new BFSBinarySearch(values); 
            case MemoryLayout::DFS:     return new DFSBinarySearch(values); 
            // case MemoryLayout::VEB: return new VEBBinarySearch(values); 

            // case MemoryLayout::INORDER_EXPLICIT: return new InorderBinarySearchExplicit(values); 
            // case MemoryLayout::INORDER_EXPLICIT_INT: return new InorderBinarySearchExplicitInt(values); 
            case MemoryLayout::BFS_EXPLICIT: return new BFSBinarySearchExplicit(values); 
            case MemoryLayout::BFS_EXPLICIT_INT: return new BFSBinarySearchExplicitInt(values); 
            case MemoryLayout::DFS_EXPLICIT: return new DFSBinarySearchExplicit(values); 
            case MemoryLayout::DFS_EXPLICIT_INT: return new DFSBinarySearchExplicitInt(values); 
            // case MemoryLayout::VEB_EXPLICIT: return new VEBBinarySearchExplicit(values); 
            case MemoryLayout::VEB_EXPLICIT_INT: return new VEBBinarySearchExplicitInt(values); 

            default:
                std::cout << "THIS IS VERY WRONG!" << std::endl;
                exit(-1);
        }
    }

private:
    MemoryLayout ml;
};