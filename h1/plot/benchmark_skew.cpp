#include <iostream>
#include <stdlib.h>
#include <sys/time.h>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <fstream>
#include <numeric> // std::accumulate

#include "Timer.h"
#include "params/SkewParams.h"
#include "../MemoryLayout.h"

#include "../PredSearchTreeFactory.h"

using std::vector;

/**
 * Use a better timer that can also measure cache misses and
 * branch mispredictions.
 */

void bench(const PredSearchTree *t, const vector<int> &queries, int skew, int elements, int iterations, int trim) {
    Timer timer;
    std::vector<long> times; // Vector to hold time of all iterations

    // Run the predecessor search a number of times
    int dummy = 0;
    for (int i = 0; i < iterations; i++) {
        timer.start();
        for (int q = 0; q < queries.size(); q++) {
            dummy += t->pred(queries[q]);
        }
        timer.stop();
        times.push_back(timer.get_microseconds());
    }

    std::sort(times.begin(), times.end());

    // Calculate average time
    long sum = std::accumulate(times.begin() + trim, times.end() - trim, 0l);
    long avg = sum / (iterations - (trim * 2));

    printf("%d\t%d\t%lu\t%ld\t%ld\t%ld\n", skew, elements, queries.size(), avg, times[trim], times[times.size()-(trim + 1)]);

    // TODO use dummy, or the loop will be optimized away
    std::ofstream devnull;
    devnull.open("/dev/null");
    devnull << dummy;
    devnull.close();
}

void print_output_header(const SkewParams &p) {
    std::cout << "# Timing predecessor search with the following parameters" << std::endl;
    std::cout << "# \tminimum skew (%%) : " << p.min_skew << std::endl;
    std::cout << "# \tmaximum skew (%%) : " << p.max_skew << std::endl;
    std::cout << "# \ttree size         : " << p.tree_size << std::endl;
    std::cout << "# \tnumber of queries : " << p.no_of_queries << std::endl;
    std::cout << "# \titerations        : " << p.iterations << std::endl;
    std::cout << "# \ttrim              : " << p.trim << std::endl;
    std::cout << "# \trandom seed       : " << p.random_seed << std::endl;
    std::cout << "#" << std::endl;
    std::cout << "# Datalines: skew, tree size, #searches, avg. time in us, fastest time in us, slowest time in us" << std::endl;
}

/**
 * The program takes the following parameters
 *   - minimum skew (percentage)
 *   - maximum skew (percentage)
 *   - tree size (logarithmic)
 *   - Number of queries
 *   - Iterations
 *   - Trim
 *   - Random seed (optional)
 */
int main(int argc, char *argv[]) {
    // Parse program arguments
    SkewParams p(argc, argv);
    srand(p.random_seed);
    print_output_header(p);

    // Generate random numbers for the queries
    vector<int> queries(p.no_of_queries);
    for (int q = 0; q < p.no_of_queries; q++) queries.push_back(rand());

    // Generate random numbers for the tree
    vector<int> values(p.tree_size);
    for (int q = 0; q < p.tree_size; q++) values.push_back(rand());

    PredSearchTreeFactory tree_factory(MemoryLayout::DFS_EXPLICIT_INT);
    for (int skew = p.min_skew; skew <= p.max_skew; skew++) {
        // Build a new tree with the same values but different skew factor
        std::auto_ptr<PredSearchTree> t(tree_factory.createTree(values, skew));

        // Benchmark the predecessor searches
        bench(t.get(), queries, skew, p.tree_size, p.iterations, p.trim);
    }
}