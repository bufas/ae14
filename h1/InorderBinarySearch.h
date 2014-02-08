#pragma once

#include <vector>
#include <algorithm>
#include "PredSearchTree.h"

class InorderBinarySearch : public PredSearchTree {

private:
    std::vector<int> elems;

public:

    InorderBinarySearch(const std::vector<int> &v) : elems(v) {
        std::sort(elems.begin(), elems.end());
    }

    int pred(int x) const {
        int s = 0;
        int e = elems.size() - 1;

        while (s <= e) {
            int mid = (e + s) / 2;
            if (elems[mid] == x) return x;
            
            if (elems[mid] < x) s = mid + 1;
            else e = mid - 1;
        }

        // TODO clean this shit up (most of it is to handle sizes 0 and 1)
        if (e == -1) return -1;
        if (s > e) return elems[e];
        return elems[s];
    }


};