#include <iostream>
#include <stdlib.h>
#include <sys/time.h>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <sstream>

#include "../LinearSearch.h"
#include "../InorderBinarySearch.h"
#include "../BFSBinarySearch.h"

void print_data_line(int log_elems, int searches, struct timeval before, struct timeval after) {
    // Calculate time
    long utime = ((after.tv_sec - before.tv_sec) * 1000000) + after.tv_usec - before.tv_usec;
    long stime = ((after.tv_sec - before.tv_sec) * 1000000) + after.tv_usec - before.tv_usec;

    // Print the output
    printf("%d\t%d\t%d\t%ld\n", log_elems, 1 << log_elems, searches, (utime + stime));
}

/**
 * Does the actual timing of the searches
 */
void bench(const PredSearchTree *t, const std::vector<int> &queries, const int log_tree_size) {
    struct timeval before, after;
    gettimeofday(&before, nullptr); // start timer

    // Run the predecessor search a number of times
    int dummy = 0;
    for (int q = 0; q < queries.size(); q++) {
        dummy += t->pred(queries[q]);
    }

    gettimeofday(&after, nullptr); // stop timer
    print_data_line(log_tree_size, queries.size(), before, after); // Print time elapsed

    // TODO use dummy, or the loop will be optimized away
}

enum class MemoryLayout {LINEAR, INORDER, BFS, DFS, VEB};
struct Params {
    MemoryLayout memory_layout;
    int min_log_tree_size;
    int max_log_tree_size;
    int no_of_queries;
    int random_seed;
};

Params parse_arguments(int argc, char *argv[]) {
    // Check if there is enough parameters and print help message if not
    if (argc < 5) {
        std::cout << "Call this program with one of the following parameters" << std::endl;
        std::cout << "\tmemory layout [linear, inorder, bfs, dfs, veb]" << std::endl;
        std::cout << "\tminimum tree size (logarithmic)" << std::endl;
        std::cout << "\tmaximum tree size (logarithmic)" << std::endl;
        std::cout << "\tnumber of queries for each tree size" << std::endl;
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

    // TODO I don't know how to do this properly
    // Set tree size bounds and number of queries
    std::istringstream *iss = new std::istringstream(argv[2]);
    if (!(*iss >> p.min_log_tree_size)) {
        std::cout << "minimum tree size must be an integer. " << argv[2] << " was given." << std::endl;
        exit(-1);
    }

    iss = new std::istringstream(argv[3]);
    if (!(*iss >> p.max_log_tree_size)) {
        std::cout << "maximum tree size must be an integer. " << argv[3] << " was given." << std::endl;
        exit(-1);
    }

    iss = new std::istringstream(argv[4]);
    if (!(*iss >> p.no_of_queries)) {
        std::cout << "number of queries must be an integer. " << argv[4] << " was given." << std::endl;
        exit(-1);
    }

    // Set random seed
    if (argc >= 6) {
        iss = new std::istringstream(argv[5]);
        if (!(*iss >> p.random_seed)) {
            std::cout << "random seed must be an integer. " << argv[5] << " was given." << std::endl;
            exit(-1);
        }
    }
    else p.random_seed = time(nullptr);

    return p;
}

PredSearchTree* get_search_algorithm(const MemoryLayout &ml, const std::vector<int> &values) {
    switch (ml) {
        case MemoryLayout::LINEAR:  return new LinearSearch(values); 
        case MemoryLayout::INORDER: return new InorderBinarySearch(values); 
        case MemoryLayout::BFS:     return new BFSBinarySearch(values); 
        // TODO implement DFS and vEB
        default:
            std::cout << "THIS IS VERY WRONG!" << std::endl;
            exit(-1);
    }
}

std::string memory_layout_as_string(const MemoryLayout &ml) {
    switch (ml) {
        case MemoryLayout::LINEAR: return "linear";
        case MemoryLayout::INORDER: return "inorder";
        case MemoryLayout::BFS: return "BFS";
        case MemoryLayout::DFS: return "DFS";
        case MemoryLayout::VEB: return "vEB";
        default: 
            std::cout << "Printing memory layouts is wrong" << std::endl;
            exit(-1);
    }
}

void print_output_header(const Params &p) {
    std::cout << "# Timing predecessor search with the following parameters" << std::endl;
    std::cout << "# \tmemory layout       : " << memory_layout_as_string(p.memory_layout) << std::endl;
    std::cout << "# \tmin tree size (log) : " << p.min_log_tree_size << std::endl;
    std::cout << "# \tmax tree size (log) : " << p.max_log_tree_size << std::endl;
    std::cout << "# \tnumber of queries   : " << p.no_of_queries << std::endl;
    std::cout << "# \trandom seed         : " << p.random_seed << std::endl;
    std::cout << std::endl;
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
    for (int log_tree_size = p.min_log_tree_size; log_tree_size <= p.max_log_tree_size; log_tree_size++) {
        const int tree_size = 1 << log_tree_size;

        // Generate random numbers to search for (reuse old numbers)
        const int additional_elements = tree_size - values.size();
        for (int q = 0; q < additional_elements; q++) values.push_back(rand());

        // Build the tree from the values vector
        std::auto_ptr<PredSearchTree> t(get_search_algorithm(p.memory_layout, values));

        // Benchmark the predecessor searches
        bench(t.get(), queries, log_tree_size);
    }
}