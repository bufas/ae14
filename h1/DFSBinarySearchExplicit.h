#pragma once

#include <vector>
#include <algorithm>
#include <fstream>
#include "BinaryPredSearchTree.h"

struct Node {
    int value;
    int child_right;
    int child_left;
};

class DFSBinarySearchExplicit : public BinaryPredSearchTree {

private:
    std::vector<Node> nodes;

    int build(const std::vector<int> &v, int idx, int s, int e) {
        if (s > e) return -1;

        const int split = (s + e + 1) / 2;
        const int left_child_idx  = idx + 1;
        const int right_child_idx = idx + (split - s) + 1;

        Node *n = &nodes[idx];
        n->value        = v[split];
        n->child_left   = build(v, left_child_idx , s        , split - 1);
        n->child_right  = build(v, right_child_idx, split + 1, e        );

        return idx;
    }


protected:
    int get_root_idx() const { return 0; }

    int child_right(int idx) const { exit(-1); }
    int child_left(int idx) const { exit(-1); }
    
public:
    DFSBinarySearchExplicit(const std::vector<int> &v) : BinaryPredSearchTree(v), nodes(v.size()) {
        std::vector<int> temp(v);
        std::sort(temp.begin(), temp.end());
        build(temp, 0, 0, temp.size() - 1);
    }

    int pred(int x) const {
        int pred_val = -1;
        int idx = get_root_idx();

        while (idx < nodes.size()) {
            // TODO evaluate effeciency impact on getting a pointer
            // rather than getting an object. I guess this avoids calling
            // the copy constructor and instead just creates a new pointer,
            // but I am not completely sure.
            const Node *n = &nodes[idx];

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

    void print(std::string filename) {
        std::ofstream outfile;
        outfile.open(filename);

        outfile << "digraph DFS_EXPLICIT {\n";

        for (auto it = nodes.begin(); it != nodes.end(); ++it) {
            Node n = (*it);
            outfile << "\t" << n.value << " -> " << n.child_left << "\n";
            outfile << "\t" << n.value << " -> " << n.child_right << "\n";
        }

        outfile << "}";
        outfile.close();
    }

};