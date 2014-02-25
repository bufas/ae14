#pragma once

#include <vector>
#include <array>
#include <algorithm>

#include "PredSearchTree.h"

int search_char(unsigned int c);

class ConstantSearch : public PredSearchTree {
/**
 * This first version is not optimized at all.
 * It uses an array of chars to store the values, and simple
 * backwards search in the array to find predecessor if the
 * element is not present.
 */

private:
    static const int page_cover = 16384;

    std::array<unsigned int, 134217728> elems;      // One bit for every int
    std::array<unsigned int, 8192> pages;           // One page covers 2^14 (16384) ints
    // std::array<unsigned int, 134217728> elems;   // One bit for every int
    // std::array<unsigned long, 67108864> elems;   // One bit for every long
    // std::array<unsigned long, 8192> pages;       // Page size = ceil(sqrt(elems.size())) ~ 2^13 longs => 64kb

public:

    ConstantSearch(std::vector<int> v) {
        std::sort(v.begin(), v.end());
        // v.erase(std::unique(v.begin(), v.end()), v.end());

        // Insert into elems
        elems.fill(0);
        for (auto i = v.begin(); i != v.end(); ++i) elems[(*i)/32] |= 1 << (*i)%32;
        // for (auto it = elems.begin(); it != elems.end(); ++it) {
        //     for (int i = 7; i >= 0; i--) {
        //         std::cout << ((*it >> i) & 1);
        //     }
        //     std::cout << " ";
        // }
        // std::cout << std::endl;
    }

    virtual int pred(int x) const {
        // std::cout << "search for " << x << std::endl;
        // Check if the element is in the array (8 is specific for array<char>)
        const int x_div_32 = x / 32;
        const int arr_val = elems[x_div_32];
        // int mask = 1 << (x % 32);
        // std::cout << "mask = " << mask << " elems["<<x_div_8<<"]="<<((int)arr_val)<< std::endl;

        // Search the rest of the char
        // std::cout << "Searching rest of the byte" << std::endl;
        for (int i = x%32; i >= 0; i--) {
            if ((arr_val & (1 << i)) != 0) return x_div_32 * 32 + i;
        }

        // Linear search backwards
        // std::cout << "Searching backwards" << std::endl;
        int block = x_div_32 - 1;
        while (block >= 0) {
            // std::cout << "\tSearch block " << block << std::endl;
            int search_val = search_char(elems[block]);
            if (search_val != -1) return block * 32 + search_val;
            block--;
        }

        return -1; // No predecessor found
    }

};

int search_char(unsigned int c) {
    if (c == 0) return -1;

    for (int i = 31; i > 0; i--) {
        if ((c & (1 << i)) != 0) return i;
    }

    return 0;
}