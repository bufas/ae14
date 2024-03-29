#pragma once

#include <iostream>
#include <vector>
#include "PredSearchTree.h"

class BinaryPredSearchTree : public PredSearchTree {

protected:
    std::vector<int> tree;
    virtual int child_right(int idx) const = 0;
    virtual int child_left(int idx) const = 0;
    virtual int get_root_idx() const = 0;

public:
    BinaryPredSearchTree(const std::vector<int> &v) : tree(v.size(), -1) {}

    virtual ~BinaryPredSearchTree() {}

    /**
     * Default pred search impl for binary search trees
     */
    virtual int pred(int x) const {
        int pred = -1;
        int idx = get_root_idx(); // Set index to the root

        while (idx < tree.size()) {
            if (tree[idx] == x) return x; // This line can be removed
            
            if (tree[idx] > x) {
                idx = child_left(idx);
            } else {
                pred = tree[idx];
                idx = child_right(idx);
            }
        }

        return pred;
    }

    virtual void print() const {
        std::cout << "[ ";
        for (auto it = tree.begin(); it != tree.end(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << "]" << std::endl;
    }


};