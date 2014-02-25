#pragma once

#include <vector>
#include <algorithm>
#include "PredSearchTree.h"

class LinearSearch : public PredSearchTree {

private:
    std::vector<int> elems;

public:

    LinearSearch(std::vector<int> v) : elems(v) {
        std::sort(elems.begin(), elems.end());
        elems.erase(std::unique(elems.begin(), elems.end()), elems.end());
    }

    virtual int pred(int x) const {
        int pred = -1;
        for (auto it = elems.begin(); it != elems.end(); ++it) {
            if (*it > x) return pred;
            pred = *it;
        }
        return pred;
    }

};