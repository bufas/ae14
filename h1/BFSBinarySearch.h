#pragma once

#include <vector>
#include <algorithm>

class BFSBinarySearch : public PredSearchTree {

private:
    std::vector<int> elems; // TODO this is just used for startup
    std::vector<int> tree;

    // We need to add a little extra because we index from 0
    int child_left(int idx) { return idx * 2 + 1; }
    int child_right(int idx) { return idx * 2 + 2; }
    int parent(int idx) { return (idx - 1) / 2; }

    void make_bfs_layout(const std::vector<int> &v, int s, int e, int idx) {
        if (s > e) return;

        int mid = (e + s) / 2;

        tree[idx] = v[mid];

        make_bfs_layout(v, s,     mid-1, child_left(idx));
        make_bfs_layout(v, mid+1, e,     child_right(idx));
    }

public:

    BFSBinarySearch(const std::vector<int> &v) : elems(v), tree(v) {
        std::sort(elems.begin(), elems.end());
        make_bfs_layout(elems, 0, elems.size()-1, 0);
    }

    int pred(int x) {
        // Print the tree
        std::cout << "Printing the tree" << std::endl;
        for (auto it = tree.begin(); it != tree.end(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;

        if (tree.empty()) return -1;

        int idx = 0; // Set index to root
        bool only_left = true;

        while (idx < tree.size()) {
            if (tree[idx] == x) return x;

            if (tree[idx] < x) {
                only_left = false;
                idx = child_right(idx);
            } else {
                idx = child_left(idx);
            }
        }

        return (only_left) ? -1 : tree[parent(idx)];
    }

};