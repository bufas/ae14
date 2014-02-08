#pragma once

#include <vector>
#include <algorithm>
#include <cmath>
#include "BinaryPredSearchTree.h"

class DFSBinarySearch : public BinaryPredSearchTree {

private:
    std::vector<int> height_of_subtree;

    void build(const std::vector<int> &v, int s, int e, int idx, int h) {
        int mid = (e + s) / 2;

        tree[idx] = mid;
        height_of_subtree[idx] = h;

        build(s, mid - 1, child_left(idx), h - 1);
        build(mid + 1, e, child_right(idx), h - 1);
    }

protected:
    // We need to add a little extra because we index from 0
    int child_left(int idx) const { return idx + 1; }
    int child_right(int idx) const { return idx + (2 << (height_of_subtree[idx] - 1)); }
    int get_root_idx() const { return 0; }

public:

    DFSBinarySearch(const std::vector<int> &v) : BinaryPredSearchTree(v) {
        std::vector<int> temp(v);
        std::sort(temp.begin(), temp.end());
        int height = ((int) std::log2(temp.size())) + 1;
        build(v, 0, elems.size(), 0, height);
    }

};