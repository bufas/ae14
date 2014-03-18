#pragma once

#include <iostream>
#include <string>
#include <array>
#include <cstdio>
#include "RS.h"

/**
 * As in Poppy
 * http://da-data.blogspot.dk/2013/04/rank-select-for-systems-folks-our-minor.html
 * We merge two cache levels into one 64 bit word. 32 bits for all previous ones,
 * and 3 * 10 bits, 10 bits for each block. And finally two bits for alignment.
 * [32 bits | 2 bits | 10 bits | 10 bits | 10 bits]
 * This means that we use 64 bits for every 2048 bits in the original set, which
 * is an overhead of 3.125%. The problem set can be up to 2^32 bits.
 * 
 * I don't know why they do not align the indexes with a cache line. They could
 * be done by using 32 bits like before, and then 53 * 9 bits (3 bits for padding). 
 * Maybe the other way is just faster, as we only have to sum 4 values (plus the 
 * popcount) instead of 49. This way we would use 512 bits index for every 27136 
 * bits, which is an overhead of 1.887%.
 */

std::vector<int> itoa(unsigned long value) {
    std::vector<int> res;
    for (int i = 63; i >= 0; --i) {
        res.push_back((value >> i) & 1);
    }
    return res;
}





template<std::size_t N>
class RSIndexedSmall : public RS {

private:
    std::array<unsigned long, (N+63)/64> values;
    std::array<unsigned long, N/2048 + 1> index;

public:
    RSIndexedSmall(const std::vector<unsigned long> &v) {
        // Build values and index
        unsigned long total_acc = 0;
        unsigned long block_acc = 0;
        int cur_block = 0;
        for (int i = 0; i < v.size(); i++) {
            // Insert into cache
            if (i % 32 == 0) {
                index[i/32] = total_acc << 32;
            }

            // Insert block
            if (i % 8 == 0 && i != 0) {
                if (cur_block < 3) {
                    index[i / 32] = index[i / 32] | block_acc << (10 * (2-cur_block));
                }
                block_acc = 0; // Reset block counter
                cur_block = (cur_block + 1) % 4;
            }

            values[i] = v[i];
            block_acc += __builtin_popcountl(v[i]);
            total_acc += __builtin_popcountl(v[i]);
        }

        // Put the rest in the next block (TODO test this for correctness)
        if (cur_block < 3) {
            index[v.size() / 32] = index[v.size() / 32] | block_acc << (10 * (2-cur_block));
        }

        // Print the index
        // std::cout << "INDEX" << std::endl;
        // for (int i = 0; i < index.size(); ++i) {
        //     auto res = itoa(index[i]);
        //     for (int x = 0; x < res.size(); x++) {
        //         if (x == 32 || x == 34 || x == 44 || x == 54) std::cout << " ";
        //         std::cout << res[x];
        //     }
        //     std::cout << std::endl;
        // }
        // std::cout << std::endl << std::endl;
    }

    ~RSIndexedSmall() {}

    /**
     * Works!
     */
    int rank(const int x) const {
        // Grab value from index
        unsigned long idx = index[(x-1)/2048];
        unsigned long idx_val = idx >> 32;
        if ((x-1) % 2048 >=  512) idx_val += (idx << 34) >> 54;
        if ((x-1) % 2048 >= 1024) idx_val += (idx << 44) >> 54;
        if ((x-1) % 2048 >= 1536) idx_val += (idx << 54) >> 54; // Nest these ifs for better branch prediction

        // Count the number of ones in the block x resides in (don't count the last word)
        int acc = 0;
        for (int i = 0; i < ((x-1) % 512) / 64; ++i) {
            acc += __builtin_popcountl(values[x/512 + i]);
        }

        // Add it all up
        return idx_val + acc + __builtin_popcountl(values[x/64] << (64 - (x%64)));
    }

    /**
     * Implement logarithmic solution by using binary search
     * on the rank index.
     */
    int select(const int x) const {
        // Binary search on the index (TODO: beware of, if x = index value)
        int min = 0;
        int max = index.size() - 1;
        while (min < max) {
            int mid = (min + max + 1) / 2;
            // if ((index[mid] >> 32) == x) { min = mid; break; } // This is wrong, as the block before could be empty in which case we should go even further back
            if ((index[mid] >> 32) < x) min = mid;
            else max = mid - 1;
        }

        // std::cout << "searcing block " << min << std::endl;

        // This is the block that contains the result
        const int block = min;
        const int newx = x - (index[block] >> 32);

        // std::cout << "newx = " << newx << std::endl;

        int subblock1 = newx - ((index[block] << 34) >> 54);
        int subblock2 = subblock1 - ((index[block] << 44) >> 54);
        int subblock3 = subblock2 - ((index[block] << 54) >> 54);

        // std::cout << "subblocks = ["<<subblock1<<", "<<subblock2<<", "<<subblock3<<"]" << std::endl;

        // Search the secondary index
        int startidx, offset;
        if (subblock1 <= 0) {
            // x is in the first block
            startidx = (block * 32);
            offset = newx;
            // std::cout << "Searching block one.";
        } else if (subblock2 <= 0) {
            // x is in the second block
            startidx = (block * 32) + 8;
            offset = subblock1;
            // std::cout << "Searching block two.";
        } else if (subblock3 <= 0) {
            // x is in the third block
            startidx = (block * 32) + 16;
            offset = subblock2;
            // std::cout << "Searching block three.";
        } else {
            // x is in the fourth block
            startidx = (block * 32) + 24;
            offset = subblock3;
            // std::cout << "Searching block four.";
        }
        // std::cout << " startidx="<<startidx<<" offset="<<offset << std::endl;

        // Search the subblock by popcounting
        for (int i = 0; i < 8; ++i) {
            int popcnt = __builtin_popcountl(values[startidx + i]);
            // std::cout << "popcnt = " << popcnt << " offset = " << offset << std::endl;
            if (popcnt >= offset) {
                // std::cout << "final stretch. Finding bit " << offset << " in " << values[startidx+i]<< std::endl;
                // The bit is in this word, search it bit by bit
                for (int q = 0; q < 64; ++q) {
                    // std::cout << "Iteration " << q << " of the inner loop" << std::endl;
                    offset -= (values[startidx + i] >> q) & 1;
                    if (offset == 0) return ((startidx + i) * 64) + q + 1;
                }
            }
            offset -= popcnt;
        }

        return -1;

    }
};
