#pragma once

#include <iostream>
#include <vector>
#include "PredSearchTree.h"

struct Node {
    int value;
    Node *child_left;
    Node *child_right;
};

class BinaryExplicitPredSearchTree : public PredSearchTree {

protected:
    std::vector<Node> tree;
    virtual int get_root_idx() const = 0;

public:
    BinaryExplicitPredSearchTree(const std::vector<int> &v) : tree(v.size()) {}
    virtual ~BinaryExplicitPredSearchTree() {}

    virtual int pred(int x) const {
        int pred_val = -1;
        const Node *n = &tree[get_root_idx()];

        while (n != nullptr) {
            // Have we found it yet?
            if (n->value == x) return x;
            
            // Determine to go left or right
            if (n->value > x) {
                n = n->child_left;
            } else {
                pred_val = n->value;
                n = n->child_right;
            }
        }

        // The element is not present in the tree
        return pred_val;
    }

};