#pragma once

#include <iostream>
#include <string>
#include <array>
#include <cstdio>
#include "RS.h"

template<std::size_t N>
class RSIndexedCacheOpt : public RS {

private:
    std::array<unsigned long, (N+63)/64> values;
    std::array<unsigned long, N/512 + 1> index; // Every block is one cache line (64 bytes)

public:
    RSIndexedCacheOpt(const std::vector<unsigned long> &v) {
        // Build values and index
        unsigned long count = 0;
        for (int i = 0; i < v.size(); i++) {
            if (i % 8 == 0) index[i/8] = count;
            values[i] = v[i];
            count += __builtin_popcount(v[i]);
        }
    }

    ~RSIndexedCacheOpt() {}

    int rank(const int x) const {
        int acc = 0;
        for (int i = 0; i < (x % 512) / 64; ++i) {
            acc += __builtin_popcountl(values[x/512 + i]);
        }

        return index[x/512] + acc + __builtin_popcountl(values[x/64] << (64 - (x%64)));
    }

    int select(const int x) const {
        // Use the index to jump
        int jump = 0;
        for (; jump < index.size(); ++jump) {
            if (index[jump] >= x) break;
        }

        // Find the actual bit
        int bitno = x - index[jump - 1];
        for (int val = (jump - 1) * 8; val < jump * 8; ++val) {
            for (int i = 0; i < 64; ++i) {
                if ((values[val] >> i) & 1) bitno--;
                if (bitno == 0) return 64 * val + i + 1;
            }
        }

        // Index is not found
        return -1;
    }
};
