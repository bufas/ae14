#include <iostream>
#include <stdlib.h>
#include <sys/time.h>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <fstream>
#include <memory> // std::unique_ptr
#include <numeric> // std::accumulate

// Load a different timer for linux
#ifdef __linux__
    #include "linux/Timer.h"
#else
    #include "Timer.h"
#endif

#include "params/BenchParams.h"

#include "../PredSearchTreeFactory.h"
#include "../LinearSearch.h"
#include "../InorderBinarySearch.h"
#include "../BFSBinarySearch.h"
#include "../DFSBinarySearch.h"

/**
 * Time queries on a specific tree size
 */
void bench(const PredSearchTree *t, const std::vector<int> &queries, int elements, const BenchParams &p) {
    Timer timer(p.perf_var);

    // Run the predecessor search a number of times
    int dummy = 0;
    for (int i = 0; i < p.no_of_iterations; i++) {
        timer.start();
        for (int q = 0; q < p.no_of_queries; q++) {
            dummy += t->pred(queries[q]);
        }
        timer.stop();
    }

    printf("%d\t%d\t%ld\t%ld\t%ld\t%ld\t%ld\t%ld\t%ld\t%ld\t%ld\t%ld\t%ld\t%ld\n", 
            elements, p.no_of_queries, 
            timer.get_avg_time(p.trim), timer.get_lowest_time(p.trim), timer.get_highest_time(p.trim), 
            timer.get_avg_count_miss(p.trim), timer.get_lowest_count_miss(p.trim), timer.get_highest_count_miss(p.trim), 
            timer.get_avg_count_access(p.trim), timer.get_lowest_count_access(p.trim), timer.get_highest_count_access(p.trim), 
            timer.get_avg_count_ratio(p.trim), timer.get_lowest_count_ratio(p.trim), timer.get_highest_count_ratio(p.trim));

    // Use dummy, or the loop will be optimized away
    std::ofstream devnull;
    devnull.open("/dev/null");
    devnull << dummy;
    devnull.close();
}


void print_output_header(const BenchParams &p) {
    std::cout << "# Timing predecessor search with the following parameters" << std::endl;
    std::cout << "# \tmemory layout        : " << as_string(p.memory_layout) << std::endl;
    std::cout << "# \tperformance counter  : " << as_string(p.perf_var) << std::endl;
    std::cout << "# \tmin tree size (log)  : " << p.min_log_tree_size << std::endl;
    std::cout << "# \tmax tree size (log)  : " << p.max_log_tree_size << std::endl;
    std::cout << "# \tnumber of queries    : " << p.no_of_queries << std::endl;
    std::cout << "# \tnumber of iterations : " << p.no_of_iterations << std::endl;
    std::cout << "# \tresults trimmed      : " << p.trim << std::endl;
    std::cout << "# \tsize increment       : " << ((p.size_increment == 0) ? "*2" : std::to_string(p.size_increment)) << std::endl;
    std::cout << "# \trandom seed          : " << p.random_seed << std::endl;
    std::cout << "#" << std::endl;
    std::cout << "# Datalines: tree size, #searches, TIME[avg, fast, slow] in us, MISS[avg, low, high], ACCESS[avg, low, high], RATIO[avg, low, high]" << std::endl;
}

int main(int argc, char *argv[]) {
    // Initialization
    BenchParams p(argc, argv);
    srand(p.random_seed);
    print_output_header(p);

    int max_tree_size = 1 << p.max_log_tree_size;
    int min_tree_size = 1 << p.min_log_tree_size;
    std::vector<int> values; // The tree is built from this vector

    // Generate queries
    std::vector<int> queries;
    for (int q = 0; q < p.no_of_queries; q++) queries.push_back(rand());

    int tree_size = 1 << p.min_log_tree_size;
    PredSearchTreeFactory tree_factory(p.memory_layout);
    for (int tree_size = min_tree_size; tree_size <= max_tree_size; tree_size += (p.size_increment == 0) ? tree_size : p.size_increment) {
        // Generate random numbers to search for (reuse old numbers)
        const int additional_elements = tree_size - values.size();
        for (int q = 0; q < additional_elements; q++) values.push_back(rand());

        // Build and bench
        std::unique_ptr<PredSearchTree> t(tree_factory.createTree(values));
        bench(t.get(), queries, tree_size, p);
    }
}