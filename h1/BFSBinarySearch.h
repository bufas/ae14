#pragma once

#include <vector>
#include <algorithm>
#include "BinaryPredSearchTree.h"

class BFSBinarySearch : public BinaryPredSearchTree {

private:
    void build(const std::vector<int> &v, int s, int e, int idx) {
        if (s > e) return;

        int mid = (e + s + 1) / 2;

        tree[idx] = v[mid];

        build(v, s,     mid-1, child_left(idx));
        build(v, mid+1, e,     child_right(idx));
    }

protected:
    // We need to add a little extra because we index from 0
    int child_left(int idx) const { return idx * 2 + 1; }
    int child_right(int idx) const { return idx * 2 + 2; }
    // int parent(int idx) const { return (idx - 1) / 2; }
    int get_root_idx() const { return 0; }

public:
    BFSBinarySearch(const std::vector<int> &v) : BinaryPredSearchTree(v) {
        std::vector<int> temp(v);
        std::sort(temp.begin(), temp.end());
        build(temp, 0, temp.size()-1, 0);
    }

};