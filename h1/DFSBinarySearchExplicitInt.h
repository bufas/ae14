#pragma once

#include <vector>
#include <algorithm>
#include "BinaryExplicitIntPredSearchTree.h"

class DFSBinarySearchExplicitInt : public BinaryExplicitIntPredSearchTree {

private:
    int build(const std::vector<int> &v, int idx, int s, int e, int skew) {
        if (s > e) return -1;

        const int split = (int) (s + ((skew/100.0f) * (e - s)));
        const int left_child_idx  = idx + 1;
        const int right_child_idx = idx + (split - s) + 1;

        IntNode *n = &tree[idx];
        n->value        = v[split];
        n->child_left   = build(v, left_child_idx , s        , split - 1, skew);
        n->child_right  = build(v, right_child_idx, split + 1, e        , skew);

        return idx;
    }

protected:
    int get_root_idx() const { return 0; }
    
public:
    DFSBinarySearchExplicitInt(const std::vector<int> &v, int skew = 80) : BinaryExplicitIntPredSearchTree(v) {
        std::vector<int> temp(v);
        std::sort(temp.begin(), temp.end());
        temp.erase(std::unique(temp.begin(), temp.end()), temp.end());
        build(temp, 0, 0, temp.size() - 1, skew);
    }
};