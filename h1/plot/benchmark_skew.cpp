#include <iostream>
#include <stdlib.h>
#include <sys/time.h>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <sstream>
#include <fstream>

#include "../PredSearchTreeFactory.h"
#include "../MemoryLayout.h"
#include "../SkewParams.h"
#include "../DFSBinarySearch.h"

using std::vector;

/**
 * Output the minimum and maximum amount of time taken for a 
 * single query. This will allow us to add confidence bars to
 * the graphs. One possiblity could also be to remove the k 
 * fastest and slowest running times i.e. remove outliers.
 *
 * Use a better timer that can also measure cache misses and
 * branch mispredictions.
 */

void print_data_line(int skew, int elems, int searches, struct timeval before, struct timeval after) {
    // Calculate time
    long utime = ((after.tv_sec - before.tv_sec) * 1000000) + after.tv_usec - before.tv_usec;
    long stime = ((after.tv_sec - before.tv_sec) * 1000000) + after.tv_usec - before.tv_usec;

    // Print the output
    printf("%d\t%d\t%d\t%ld\n", skew, elems, searches, (utime + stime));
}

/**
 * Does the actual timing of the searches
 */
void bench(const PredSearchTree *t, const vector<int> &queries, int skew, int elements) {
    struct timeval before, after;
    gettimeofday(&before, nullptr); // start timer

    // Run the predecessor search a number of times
    int dummy = 0;
    for (int q = 0; q < queries.size(); q++) {
        dummy += t->pred(queries[q]);
    }

    gettimeofday(&after, nullptr); // stop timer
    print_data_line(skew, elements, queries.size(), before, after); // Print time elapsed

    // TODO use dummy, or the loop will be optimized away
    std::ofstream devnull;
    devnull.open("/dev/null");
    devnull << dummy;
    devnull.close();
}

int intify_param(const char arg[], int default_val) {
    std::istringstream iss(arg);
    int res;
    
    if (iss >> res) return res; // Successful conversion
    return default_val;         // Unsuccessful conversion, return default value
}

SkewParams parse_arguments(int argc, char *argv[]) {
    // Check if there is enough parameters and print help message if not
    if (argc < 5) {
        std::cout << "Call this program with one of the following parameters" << std::endl;
        std::cout << "\tminimum skew (percentage)" << std::endl;
        std::cout << "\tmaximum skew (percentage)" << std::endl;
        std::cout << "\ttree size" << std::endl;
        std::cout << "\tnumber of queries" << std::endl;
        std::cout << "\trandom seed (optional)" << std::endl;
        std::cout << std::endl;
        std::cout << "\tExample usage: " << argv[0] << " 0 100 100000 1000000" << std::endl;
        exit(-1);
    }

    SkewParams p;

    // Set tree size bounds, number of queries, and random seed
    p.min_skew       = intify_param(argv[1], 10);
    p.max_skew       = intify_param(argv[2], 20);
    p.tree_size      = intify_param(argv[3], 100000);
    p.no_of_queries  = intify_param(argv[4], 1000);
    p.random_seed    = (argc >= 7) ? intify_param(argv[5], 0) : time(nullptr);

    return p;
}

void print_output_header(const SkewParams &p) {
    std::cout << "# Timing predecessor search with the following parameters" << std::endl;
    std::cout << "# \tminimum skew (%%)   : " << p.min_skew << std::endl;
    std::cout << "# \tmaximum skew (%%)   : " << p.max_skew << std::endl;
    std::cout << "# \ttree size           : " << p.tree_size << std::endl;
    std::cout << "# \tnumber of queries   : " << p.no_of_queries << std::endl;
    std::cout << "# \trandom seed         : " << p.random_seed << std::endl;
    std::cout << "#" << std::endl;
    std::cout << "# Datalines: skew, tree size, #searches, time in us" << std::endl;
}

/**
 * The program takes the following parameters
 *   - minimum skew (percentage)
 *   - maximum skew (percentage)
 *   - tree size (logarithmic)
 *   - Number of queries
 *   - Random seed (optional)
 */
int main(int argc, char *argv[]) {
    // Parse program arguments
    SkewParams p = parse_arguments(argc, argv);

    // Seed random generator
    srand(p.random_seed);

    // Generate random numbers for the queries
    vector<int> queries(p.no_of_queries);
    for (int q = 0; q < p.no_of_queries; q++) queries.push_back(rand());

    // Generate random numbers for the tree
    vector<int> values(p.tree_size);
    for (int q = 0; q < p.tree_size; q++) values.push_back(rand());

    print_output_header(p);
    PredSearchTreeFactory tree_factory(MemoryLayout::DFS_EXPLICIT_INT);
    for (int skew = p.min_skew; skew <= p.max_skew; skew++) {
        // Build a new tree with the same values but different skew factor
        std::auto_ptr<PredSearchTree> t(tree_factory.createTree(values, skew));

        // Benchmark the predecessor searches
        bench(t.get(), queries, skew, p.tree_size);
    }
}