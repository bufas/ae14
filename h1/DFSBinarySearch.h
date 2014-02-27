#pragma once

#include <vector>
#include <algorithm>
#include "BinaryPredSearchTree.h"

class DFSBinarySearch : public PredSearchTree {

private:
    std::vector<int> tree;
    int height;

    void build(const std::vector<int> &v, int idx, int s, int e, int h) {
        if (s > e) return;

        const int mid = (s + e + 1) / 2;
        tree[idx] = v[mid];

        build(v, child_left(idx)    , s      , mid - 1, h - 1);
        build(v, child_right(idx, h), mid + 1, e      , h - 1);
    }

    void switch_minus_ones(int idx, int h) {
        // If children is -1, set it to the same value as their parent. 
        // This will not change the outcome of predecessor search
        if (h > 1) {
            if (tree[child_left(idx)] == -1) tree[child_left(idx)] = tree[idx];
            if (tree[child_right(idx, h)] == -1) tree[child_right(idx, h)] = tree[idx];

            switch_minus_ones(child_left(idx), h-1);
            switch_minus_ones(child_right(idx, h), h-1);
        }
    }

protected:
    int child_left(int idx) const { return idx + 1; }
    int child_right(int idx, int h) const { return idx + (1 << (h - 1)); }
    int get_root_idx() const { return 0; }
    
public:

    DFSBinarySearch(const std::vector<int> &v) : tree(v.size(), -1) {
        std::vector<int> temp(v);
        std::sort(temp.begin(), temp.end());
        temp.erase(std::unique(temp.begin(), temp.end()), temp.end());

        // Add elements to tree so size becomes 2^x-1 for some x
        height = 0;
        while ((1 << height) - 1 < tree.size()) height++;
        tree.resize((1 << height) - 1, -1);

        build(temp, 0, 0, temp.size() - 1, height);
        switch_minus_ones(get_root_idx(), height);
    }

    /**
     * This is exactly the same as in BinaryPredSearchTree
     * except for the height variable
     */
    virtual int pred(int x) const {
        int pred = -1;
        int idx  = get_root_idx(); // Set index to the root

        for (int h = height; h > 0; h--) {
            if (tree[idx] == x) return x; // This line can be removed
            
            if (tree[idx] > x) {
                idx = child_left(idx);
            } else {
                pred = tree[idx];
                idx = child_right(idx, h);
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