#pragma once

#include <bitset>
#include <string>
#include "RS.h"

template<size_t N>
class RSNaive : public RS {

private:
    std::bitset<N> values;

public:
    RSNaive(const std::string &bs) : values(bs) {}
    ~RSNaive() {}

    int rank(const int x) const {
        int count = 0;
        for (int i = 0; i < x; ++i) count += values[i];
        return count;
    }

    int select(const int x) const {
        int count = x;
        for (int i = 0; i < N; i++) {
            count -= values[i];
            if (count == 0) return i+1;
        }
        return -1;
    }
};
