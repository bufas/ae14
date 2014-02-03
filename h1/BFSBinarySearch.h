#pragma once

#include <vector>
#include <algorithm>

class BFSBinarySearch : public PredSearchTree {

private:
    std::vector<int> elems; // TODO this should be deleted
    std::vector<int> tree; // TODO this should be std::array pointer instead

    // We need to add a little extra because we index from 0
    int child_left(int idx) { return idx * 2 + 1; }
    int child_right(int idx) { return idx * 2 + 2; }
    int parent(int idx) { return (idx + 1) / 2; }

    void make_bfs_layout(const std::vector<int> &v, int s, int e, int idx) {
        int mid = (e + s) / 2;

        tree[idx] = mid;

        make_bfs_layout(s, mid - 1, child_left(idx));
        make_bfs_layout(mid + 1, e, child_right(idx));
    }

public:

    BFSBinarySearch(std::vector<int> v) : elems(v) {
        std::sort(elems.begin(), elems.end());
        make_bfs_layout(v, 0, elems.size(), 0);
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

        return tree[parent(idx)];
    }

};