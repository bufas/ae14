#pragma once

#include <vector>
#include <algorithm>
#include <cmath>

class DFSBinarySearch : public PredSearchTree {

private:
    std::vector<int> tree;
    std::vector<int> height_of_subtree;

    // We need to add a little extra because we index from 0
    int child_left(int idx) { return idx + 1; }
    int child_right(int idx) { return idx + (2 << (height_of_subtree[idx] - 1)); }

    void make_dfs_layout(const std::vector<int> &v, int s, int e, int idx, int h) {
        int mid = (e + s) / 2;

        tree[idx] = mid;
        height_of_subtree[idx] = h;

        make_dfs_layout(s, mid - 1, child_left(idx), h - 1);
        make_dfs_layout(mid + 1, e, child_right(idx), h - 1);
    }

public:

    DFSBinarySearch(std::vector<int> v) : elems(v) {
        std::sort(elems.begin(), elems.end());
        int height = ((int) std::log2(elems.size())) + 1;
        make_dfs_layout(v, 0, elems.size(), 0, height);
    }

    /**
     * This is most likely wrong
     */
    virtual int pred(int x) {
        int idx = 0;

        while (idx < tree.size()) {
            if (tree[idx] == x) return x;
            
            if (tree[idx] < x) idx = child_right(idx);
            else idx = child_left(idx);
        }

        return 1337; // TODO what the fuck should be here?
    }

};