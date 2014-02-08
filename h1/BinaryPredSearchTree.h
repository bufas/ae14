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
    BinaryPredSearchTree(const std::vector<int> &v) : tree(v.size()) {}

    virtual ~BinaryPredSearchTree() {}

    /**
     * Default pred search impl for binary search trees
     */
    virtual int pred(int x) const {
        if (tree.empty()) return -1;

        int prev = -1;
        int idx = get_root_idx(); // Set index to the root
        bool only_left = true;

        while (idx < tree.size()) {
            if (tree[idx] == x) return x;
            
            prev = idx;
            if (tree[idx] < x) {
                only_left = false;
                idx = child_right(idx);
            } else {
                idx = child_left(idx);
            }
        }

        return (only_left) ? -1 : tree[prev];
    }

    virtual void print() const {
        std::cout << "[ ";
        for (auto it = tree.begin(); it != tree.end(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << "]" << std::endl;
    }


};