#pragma once

#include <string>
#include <array>
#include "RS.h"

template<std::size_t N>
class RSIndexed : public RS {

private:
    std::array<unsigned long, (N+63)/64> values;
    std::array<unsigned long, N/64> index;

public:
    RSIndexed(const std::vector<unsigned long> &v) {
        // Build values and index
        unsigned long count = 0;
        for (int i = 0; i < v.size(); i++) {
            values[i] = v[i];
            count += __builtin_popcount(v[i]);
            index[i] = count;
        }
    }

    ~RSIndexed() {}

    int rank(const int x) const {
        return index[x/64] + __builtin_popcount(values[x/64] >> (64 - (x%64)));
    }

    int select(const int x) const {
        // Use the index to jump
        int jump = 0;
        for (jump = 0; jump < index.size(); ++jump) {
            if (index[jump] >= x) break;
        }

        // Find the actual bit
        int bitno = x - ((jump == 0) ? 0 : index[jump - 1]);
        for (int i = 0; i < 64; ++i) {
            if ((values[jump] >> i) & 1) bitno--;
            if (bitno == 0) return 64 * jump + i + 1;
        }
        return -1;
    }
};
