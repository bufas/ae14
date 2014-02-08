#pragma once

#include <vector>
#include <algorithm>
#include <cmath>
#include "BinaryPredSearchTree.h"

class DFSBinarySearch : public BinaryPredSearchTree {

private:
    std::vector<int> height_of_subtree;

    void build(const std::vector<int> &v, int idx, int s, int e, int h) {
        if (s > e) return;

        const int mid = (s + e + 1) / 2;
        tree[idx] = v[mid];
        height_of_subtree[idx] = h;

        build(v, child_left(idx) , s      , mid - 1, h - 1);
        build(v, child_right(idx), mid + 1, e      , h - 1);
    }


protected:
    int child_left(int idx) const { return idx + 1; }
    int child_right(int idx) const { return idx + (1 << (height_of_subtree[idx] - 1)); }
    int get_root_idx() const { return 0; }
    
    int parent(int idx) {
        if (idx == child_right(idx - (1 << height_of_subtree[idx]))) return idx - (1 << height_of_subtree[idx]);
        if (idx == child_right(idx - (1 << (height_of_subtree[idx] + 1)))) return idx - (1 << (height_of_subtree[idx] + 1));
        return idx - 1;
    }

public:

    DFSBinarySearch(const std::vector<int> &v) : BinaryPredSearchTree(v) {
        std::vector<int> temp(v);
        std::sort(temp.begin(), temp.end());

        // Add elements to tree so size becomes 2^x-1 for some x
        int height = 0;
        while ((1 << height) - 1 < tree.size()) height++;
        tree.resize((1 << height) - 1, -1);

        // Construct height_of_subtree
        height_of_subtree = tree;
        
        build(temp, 0, 0, temp.size() - 1, height);
    }

    /**
     * This is exactly the same as in BinaryPredSearchTree
     * except for the line 
     * if (tree[idx] == -1) break;
     */
    int pred(int x) const {
        if (tree.empty()) return -1;

        int pred = 0;
        int idx = get_root_idx(); // Set index to the root
        bool only_left = true;

        while (idx < tree.size()) {
            if (tree[idx] == x) return x;
            if (tree[idx] == -1) break;
            
            if (tree[idx] < x) {
                pred = idx;
                only_left = false;
                idx = child_right(idx);
            } else {
                idx = child_left(idx);
            }
        }

        return (only_left) ? -1 : tree[pred];
    }


};