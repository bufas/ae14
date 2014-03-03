#pragma once

#include <vector>
#include <array>
#include <algorithm>

#include "PredSearchTree.h"

int search_int(unsigned int c, int max = 31);

class ConstantSearch : public PredSearchTree {

private:
    static const int page_size1 = 1 << 11;
    static const int page_size2 = 1 << 22;
    static const int page_size2_for_index1 = 1 << 11;

    std::array<unsigned int, 134217728> elems;      // One bit for every int
    std::array<unsigned int, 65536> index1;         // One page covers 2^11 numbers
    std::array<unsigned int, 32> index2;            // One page covers 2^22 numbers

    template<std::size_t N>
    int pred_aux(const std::array<unsigned int, N> &a, int s, int e) const;

    void insert(int e) {
        int page1 = e/page_size1;
        int page2 = e/page_size2;
        elems[e / 32]      |= 1 << e%32;
        index1[page1 / 32] |= 1 << page1%32;
        index2[page2 / 32] |= 1 << page2%32;
    }

public:

    ConstantSearch(std::vector<int> v) {
        std::sort(v.begin(), v.end());
        elems.fill(0);
        for (auto i = v.begin(); i != v.end(); ++i) insert(*i);
    }

    virtual int pred(int x) const {
        int p;
        int idx1_page = (x / page_size1);
        int idx2_page = (x / page_size2);

        // Search the page x should reside in (partial index1 page)
        p = pred_aux(elems, idx1_page * page_size1, x);
        if (p != -1) return p;
        // Search the page in index1 x should reside in (partial index2 page)
        p = pred_aux(index1, idx2_page * page_size2_for_index1, idx1_page - 1);
        if (p != -1) {
            // If found -> search the returned page in elems and return predecessor
            int start = p * page_size1;
            return pred_aux(elems, start, start + page_size1);
        } else {
            // Else -> Search index2 for predecessor
            p = pred_aux(index2, 0, idx2_page - 1);
            if (p == -1) {
                // If -1 -> return -1
                return -1;
            } else {
                // Else -> search page in index1 that should contain pred
                p = pred_aux(index1, p * page_size2_for_index1, (p+1) * page_size2_for_index1 - 1);
                // Search the returned page in elems and return predecessor
                return pred_aux(elems, p * page_size1, (p+1) * page_size1 - 1);
            }
        }

        // // Search the page x should reside in
        // int p = pred_aux(elems, (x / page_size1) * page_size1, x);
        // if (p != -1) return p;

        // // If it is not found in that page, search in the index which page contains the predecessor
        // p = pred_aux(index1, 0, (x / page_size1) - 1);
        // if (p == -1) return -1;

        // // Search the returned page
        // int start = p * page_size1;
        // return pred_aux(elems, start, start + page_size1);
    }

};

template<std::size_t N>
int ConstantSearch::pred_aux(const std::array<unsigned int, N> &a, int s, int e) const {
    const int s_div_32 = s / 32;
    const int e_div_32 = e / 32;

    // Search the rest of the int
    for (int i = e%32; i >= 0; --i) {
        if ((a[e_div_32] & (1 << i)) != 0) return e_div_32 * 32 + i;
    }

    // Linear search backwards
    for (int block = e_div_32-1; block >= s_div_32; --block) {
        int search_val = search_int(a[block]);
        if (search_val != -1) return block * 32 + search_val;
    }

    return -1; // No predecessor found
}

int search_int(unsigned int c, int max) {
    if (c == 0 || max == 0) return -1;

    for (int i = max; i > 0; --i) {
        if ((c & (1 << i)) != 0) return i;
    }

    return 0;
}
