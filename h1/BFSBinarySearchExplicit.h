#pragma once

#include <vector>
#include <utility>
#include <algorithm>
#include "BinaryExplicitPredSearchTree.h"

class BFSBinarySearchExplicit : public BinaryExplicitPredSearchTree {

private:
    void build(const std::vector<int> &v, int idx, int s, int e, int skew) {
        using std::pair;

        // There are no elements, return
        if (v.size() == 0) return;

        // Initialize variables
        std::vector<pair<int,int>*> start_end(v.size());
        start_end[0] = new pair<int,int>(0, v.size() - 1);
        int next_free_child_idx = 1;

        // Loop over all values and insert them in tree
        for (int i = 0; i < v.size(); i++) {
            // Find the value to insert into this node
            const int this_s = start_end[i]->first;
            const int this_e = start_end[i]->second;
            const int split = (int) (this_s + ((skew/100.0f) * (this_e - this_s)));

            Node *n = &tree[i];
            n->value = v[split];

            // Prep the left child
            if (this_s < split) {
                n->child_left = &tree[next_free_child_idx];
                start_end[next_free_child_idx] = new pair<int,int>(this_s, split - 1);
                next_free_child_idx++;
            } else {
                n->child_left = nullptr;
            }

            // Prep the right child
            if (this_e > split) {
                n->child_right = &tree[next_free_child_idx];
                start_end[next_free_child_idx] = new pair<int,int>(split + 1, this_e);
                next_free_child_idx++;
            } else {
                n->child_right = nullptr;
            }
        }
    }

protected:
    int get_root_idx() const { return 0; }

public:
    BFSBinarySearchExplicit(const std::vector<int> &v, int skew = 50) : BinaryExplicitPredSearchTree(v) {
        std::vector<int> temp(v);
        std::sort(temp.begin(), temp.end());
        temp.erase(std::unique(temp.begin(), temp.end()), temp.end());
        build(temp, 0, 0, temp.size() - 1, skew);
    }

};