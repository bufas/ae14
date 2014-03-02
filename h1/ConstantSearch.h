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
    int pred_aux(const std::array<unsigned int, N> &a, int x) const;

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
        int page = pred_aux(pages, x / page_size);
        if (page == -1) return -1;
        return pred_aux(elems, std::min(x, (page + 1) * page_size - 1));
    }

};

int search_int(unsigned int c, int max) {
    if (c == 0 || max == 0) return -1;

    for (int i = max; i >= 0; --i) {
        if ((c & (1 << i)) != 0) return i;
    }

    return -1; // This should not be reached
}

template<std::size_t N>
int ConstantSearch::pred_aux(const std::array<unsigned int, N> &a, int x) const {
    const int x_div_32 = x / 32;

    // Search the rest of the int
    for (int i = x%32; i >= 0; i--) {
        if ((a[x_div_32] & (1 << i)) != 0) return x_div_32 * 32 + i;
    }

    // Linear search backwards
    int block = x_div_32 - 1;
    while (block >= 0) {
        int search_val = search_int(a[block]);
        if (search_val != -1) return block * 32 + search_val;
        block--;
    }

    return -1; // No predecessor found
}

