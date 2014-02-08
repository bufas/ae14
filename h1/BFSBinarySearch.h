#pragma once

#include <vector>
#include <algorithm>
#include <cmath>
#include "BinaryPredSearchTree.h"

class BFSBinarySearch : public BinaryPredSearchTree {

private:
    void build(const std::vector<int> &v) {
        bool from_above = true;
        int next_to_insert = 0;
        int idx = 0;

        while (next_to_insert < v.size()) {
            // Out of bounds
            if (idx >= tree.size()) {
                from_above = false;
                idx = parent(idx);
            }

            if (from_above) {
                if (tree[idx] == -1) idx = child_left(idx);
                else std::cout << "ERROR" << std::endl;
            }
            else {
                if (tree[idx] == -1) {
                    tree[idx] = v[next_to_insert];
                    next_to_insert++;
                    idx = child_right(idx);
                    from_above = true;
                } else {
                    idx = parent(idx);
                }
            }
        }
    }

protected:
    // We need to add a little extra because we index from 0
    int child_left(int idx) const { return idx * 2 + 1; }
    int child_right(int idx) const { return idx * 2 + 2; }
    int get_root_idx() const { return 0; }

    int parent(int idx) const { return (idx - 1) / 2; }

public:
    BFSBinarySearch(const std::vector<int> &v) : BinaryPredSearchTree(v) {
        std::vector<int> temp(v);
        std::sort(temp.begin(), temp.end());
        build(temp);
    }

};