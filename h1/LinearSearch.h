#include <vector>
#include <algorithm>


class LinearSearch : public PredSearchTree {

private:
    std::vector<int> elems;

public:

    LinearSearch(std::vector<int> v) : elems(v) {
        std::sort(elems.begin(), elems.begin());
    }

    virtual int pred(int x) {
        int pred = -1;
        for (auto it = elems.begin(); it != elems.end(); ++it) {
            if (*it == x) return pred;
            pred = *it;
        }
        return -1;
    }

};