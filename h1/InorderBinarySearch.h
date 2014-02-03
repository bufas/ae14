#pragma once

#include <vector>
#include <algorithm>

class SortedBinarySearch : public PredSearchTree {

private:
    std::vector<int> elems;

public:

    LinearSearch(const std::vector<int> &v) : elems(v) {
        std::sort(elems.begin(), elems.end());
    }

    /**
     * This is most likely wrong
     */
    virtual int pred(int x) {
        int s = 0;
        int e = elems.size() - 1;

        while (s < e) {
            int mid = (e + s) / 2;
            if (elems[mid] == x) return x;
            
            if (elems[mid] < x) s = mid + 1;
            else e = mid - 1;
        }

        return elems[s];
    }

};