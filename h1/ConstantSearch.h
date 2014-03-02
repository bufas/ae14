#pragma once

#include <vector>
#include <array>
#include <algorithm>

#include "PredSearchTree.h"

int search_int(unsigned int c, int max = 31);

class ConstantSearch : public PredSearchTree {

private:
    static const int page_size = 65536; // in bits

    std::array<unsigned int, 134217728> elems;      // One bit for every int
    std::array<unsigned int, 2048> pages;           // One page covers 2^11 (2048) ints

    template<std::size_t N>
    int pred_aux(const std::array<unsigned int, N> &a, int s, int e) const;

    void insert(int e) {
        int page = e/page_size;
        elems[e / 32]    |= 1 << e%32;
        pages[page / 32] |= 1 << page%32;
    }

public:

    ConstantSearch(std::vector<int> v) {
        std::sort(v.begin(), v.end());

        // Insert into elems
        elems.fill(0);
        for (auto i = v.begin(); i != v.end(); ++i) insert(*i);
    }

    virtual int pred(int x) const {
        // Search the page x should reside in
        int p = pred_aux(elems, (x / page_size) * page_size, x);
        if (p != -1) return p;

        // If it is not found in that page, search in the index which page contains the predecessor
        p = pred_aux(pages, 0, (x / page_size) - 1);
        if (p == -1) return -1;

        // Search the returned page
        int start = p * page_size;
        return pred_aux(elems, start, start + page_size);
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
    int res = -1;
    for (int block = e_div_32-1; block >= s_div_32; --block) {
        int search_val = search_int(a[block]);
        if (search_val != -1) return block * 32 + search_val;
    }

    return res; // No predecessor found
}

int search_int(unsigned int c, int max) {
    if (c == 0 || max == 0) return -1;

    for (int i = max; i > 0; --i) {
        if ((c & (1 << i)) != 0) return i;
    }

    return 0;
}
