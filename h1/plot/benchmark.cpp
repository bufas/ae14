#include <iostream>
#include <stdlib.h>
#include <sys/time.h>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <sstream>
#include <fstream>

#include "../MemoryLayout.h"
#include "../Params.h"
#include "../LinearSearch.h"
#include "../InorderBinarySearch.h"
#include "../BFSBinarySearch.h"
#include "../DFSBinarySearch.h"

/**
 * Output the minimum and maximum amount of time taken for a 
 * single query. This will allow us to add confidence bars to
 * the graphs. One possiblity could also be to remove the k 
 * fastest and slowest running times i.e. remove outliers.
 *
 * Use a better timer that can also measure cache misses and
 * branch mispredictions.
 */

void print_data_line(int elems, int searches, struct timeval before, struct timeval after) {
    // Calculate time
    long utime = ((after.tv_sec - before.tv_sec) * 1000000) + after.tv_usec - before.tv_usec;
    long stime = ((after.tv_sec - before.tv_sec) * 1000000) + after.tv_usec - before.tv_usec;

    // Print the output
    printf("%d\t%d\t%ld\n", elems, searches, (utime + stime));
}

/**
 * Does the actual timing of the searches
 */
void bench(const PredSearchTree *t, const std::vector<int> &queries, int elements) {
    struct timeval before, after;
    gettimeofday(&before, nullptr); // start timer

    // Run the predecessor search a number of times
    int dummy = 0;
    for (int q = 0; q < queries.size(); q++) {
        dummy += t->pred(queries[q]);
    }

    gettimeofday(&after, nullptr); // stop timer
    print_data_line(elements, queries.size(), before, after); // Print time elapsed

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

Params parse_arguments(int argc, char *argv[]) {
    // Check if there is enough parameters and print help message if not
    if (argc < 5) {
        std::cout << "Call this program with one of the following parameters" << std::endl;
        std::cout << "\tmemory layout [linear, inorder, bfs, dfs, veb]" << std::endl;
        std::cout << "\tminimum tree size (logarithmic)" << std::endl;
        std::cout << "\tmaximum tree size (logarithmic)" << std::endl;
        std::cout << "\tnumber of queries for each tree size" << std::endl;
        std::cout << "\thow much to increment tree size each step (optional)" << std::endl;
        std::cout << "\trandom seed (optional)" << std::endl;
        std::cout << std::endl;
        std::cout << "\tExample usage: " << argv[0] << " bfs 5 20 1000" << std::endl;
        exit(-1);
    }

    Params p;
    // Set the memory layout
    std::string layout(argv[1]);
    if (layout == "linear") p.memory_layout = MemoryLayout::LINEAR;
    else if (layout == "inorder") p.memory_layout = MemoryLayout::INORDER;
    else if (layout == "bfs") p.memory_layout = MemoryLayout::BFS;
    else if (layout == "dfs") p.memory_layout = MemoryLayout::DFS;
    else if (layout == "veb") p.memory_layout = MemoryLayout::VEB;
    else {
        std::cout << "Parameter parsing: The memory layout given is not valid." << std::endl;
        exit(-1);
    }

    // Set tree size bounds, number of queries, and random seed
    p.min_log_tree_size = intify_param(argv[2], 10);
    p.max_log_tree_size = intify_param(argv[3], 20);
    p.no_of_queries     = intify_param(argv[4], 1000);
    p.size_increment    = (argc >= 6) ? intify_param(argv[5], 0) : 0;
    p.random_seed       = (argc >= 7) ? intify_param(argv[5], 0) : time(nullptr);

    return p;
}

PredSearchTree* get_search_algorithm(const MemoryLayout &ml, const std::vector<int> &values) {
    switch (ml) {
        case MemoryLayout::LINEAR:  return new LinearSearch(values); 
        case MemoryLayout::INORDER: return new InorderBinarySearch(values); 
        case MemoryLayout::BFS:     return new BFSBinarySearch(values); 
        case MemoryLayout::DFS:     return new DFSBinarySearch(values); 
        // TODO implement DFS and vEB
        default:
            std::cout << "THIS IS VERY WRONG!" << std::endl;
            exit(-1);
    }
}

void print_output_header(const Params &p) {
    std::cout << "# Timing predecessor search with the following parameters" << std::endl;
    std::cout << "# \tmemory layout       : " << as_string(p.memory_layout) << std::endl;
    std::cout << "# \tmin tree size (log) : " << p.min_log_tree_size << std::endl;
    std::cout << "# \tmax tree size (log) : " << p.max_log_tree_size << std::endl;
    std::cout << "# \tnumber of queries   : " << p.no_of_queries << std::endl;
    std::cout << "# \tsize increment      : " << ((p.size_increment == 0) ? "*2" : std::to_string(p.size_increment)) << std::endl;
    std::cout << "# \trandom seed         : " << p.random_seed << std::endl;
    std::cout << "#" << std::endl;
    std::cout << "# Datalines: log(tree size), tree size, #searches, time in us" << std::endl;
}

/**
 * The program takes the following parameters
 *   - Memory layout (linear, bfs, dfs, or veb)
 *   - Smallest tree size (logarithmic)
 *   - Largest tree size (logarithmic)
 *   - Number of queries (pr. tree size)
 *   - Random seed (optional)
 */
int main(int argc, char *argv[]) {
    // Parse program arguments
    Params p = parse_arguments(argc, argv);

    // Seed random generator
    srand(p.random_seed);

    // Generate random numbers for the queries
    std::vector<int> queries;
    for (int q = 0; q < p.no_of_queries; q++) queries.push_back(rand());

    print_output_header(p);
    std::vector<int> values; // The tree is built from this vector
    int tree_size = 1 << p.min_log_tree_size;
    while (tree_size <= 1 << p.max_log_tree_size) {
        // Generate random numbers to search for (reuse old numbers)
        const int additional_elements = tree_size - values.size();
        for (int q = 0; q < additional_elements; q++) values.push_back(rand());

        // Build the tree from the values vector
        std::auto_ptr<PredSearchTree> t(get_search_algorithm(p.memory_layout, values));

        // Benchmark the predecessor searches
        bench(t.get(), queries, tree_size);

        // Increment tree size
        if (p.size_increment == 0) tree_size *= 2;
        else tree_size += p.size_increment;
    }
}