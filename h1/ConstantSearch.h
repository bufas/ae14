#pragma once

#include <vector>
#include <array>
#include <algorithm>

#include "PredSearchTree.h"

int search_int(unsigned int c);

class ConstantSearch : public PredSearchTree {
/**
 * This first version is not optimized at all.
 * It uses an array of chars to store the values, and simple
 * backwards search in the array to find predecessor if the
 * element is not present.
 */

private:
    static const int page_size = 16384;

    std::array<unsigned int, 134217728> elems;      // One bit for every int
    std::array<unsigned int, 8192> pages;           // One page covers 2^14 (16384) ints

    template<std::size_t N>
    int pred_aux(const std::array<unsigned int, N> &a, int x) const;

public:

    ConstantSearch(std::vector<int> v) {
        std::sort(v.begin(), v.end());

        // Insert into elems
        elems.fill(0);
        for (auto i = v.begin(); i != v.end(); ++i) {
            int e = *i;
            elems[e/32] |= 1 << e%32;

            int page_e = e/page_size;
            pages[page_e/32] |= 1 << page_e%32;
        }
    }

    virtual int pred(int x) const {
        // 
        // Find the page which contains the predecessor
        // 
        const int page = pred_aux(pages, x / page_size);
        if (page == -1) return -1; // There is no predecessor

        // 
        // Search the page
        // 
        if (page == x / page_size) {
            // The predecessor is within the page it should be, 
            // don't search the whole page, only from x's real position
            return pred_aux(elems, x);
        }
        
        return pred_aux(elems, (page + 1) * page_size - 1);
    }

};

int search_int(unsigned int c) {
    if (c == 0) return -1;

    for (int i = 31; i > 0; i--) {
        if ((c & (1 << i)) != 0) return i;
    }

    return 0;
}

template<std::size_t N>
int ConstantSearch::pred_aux(const std::array<unsigned int, N> &a, int x) const {
    const int x_div_32 = x / 32;
    const int arr_val = a[x_div_32];

    // Search the rest of the char
    for (int i = x%32; i >= 0; i--) {
        if ((arr_val & (1 << i)) != 0) return x_div_32 * 32 + i;
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

