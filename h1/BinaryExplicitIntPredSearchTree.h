#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include "PredSearchTree.h"

struct IntNode {
    int value;
    int child_left;
    int child_right;
};

class BinaryExplicitIntPredSearchTree : public PredSearchTree {

protected:
    std::vector<IntNode> tree;
    virtual int get_root_idx() const = 0;

public:
    BinaryExplicitIntPredSearchTree(const std::vector<int> &v) : tree(v.size()) {}
    virtual ~BinaryExplicitIntPredSearchTree() {}

    virtual int pred(int x) const {
        int pred_val = -1;
        int idx = get_root_idx();

        while (idx < tree.size()) {
            const IntNode *n = &tree[idx];

            // Have we found it yet?
            if (n->value == x) return x;
            
            // Determine to go left or right
            if (n->value > x) {
                idx = n->child_left;
            } else {
                pred_val = n->value;
                idx = n->child_right;
            }
        }

        // The element is not present in the tree
        return pred_val;
    }

    // I think this function is incorrect
    virtual void make_dot(std::string filename) {
        std::ofstream outfile;
        outfile.open(filename);

        outfile << "digraph DFS_EXPLICIT {\n";

        //make_dot_aux(outfile, get_root_idx());

        for (int i = 0; i < tree.size(); i++) {
            IntNode n = tree[i];

            if (n.child_left != -1) {
                IntNode cl = tree[n.child_left];
                outfile << "\t\"" << n.value << ":" << i << "\" -> \"" << cl.value << ":" << n.child_left << "\"\n";
            }
            
            if (n.child_right != -1) {
                IntNode cr = tree[n.child_right];
                outfile << "\t\"" << n.value << ":" << i << "\" -> \"" << cr.value << ":" << n.child_right << "\"\n";
            }
        }

        outfile << "}";
        outfile.close();
    }

};