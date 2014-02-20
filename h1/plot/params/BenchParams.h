#pragma once

#include <sstream>
#include "../../MemoryLayout.h"

class BenchParams {

public:
    BenchParams(int argc, char **argv);

    // Data fields (public for easier access)
    MemoryLayout memory_layout;     // The memory layout of the tree
    int min_log_tree_size;          // Minimum tree size (logarithmic)
    int max_log_tree_size;          // Maximum tree size (logarithmic)
    int no_of_queries;              // Number of queries to run each iteration
    int no_of_iterations;           // We time queries this number of times, and take the average running time
    int trim;                       // Remove the trim best and worst running times from the output
    int size_increment;             // How much to increment the tree size each time (0 means double every time)
    int random_seed;                // The seed for the random generator

private:
    int intify_param(const char arg[], int default_val);
    void print_usage(char *prog_name);

};

BenchParams::BenchParams(int argc, char **argv) {
    // Check if there is enough parameters and print help message if not
    if (argc < 7) {
        print_usage(argv[0]);
        exit(-1);
    }

    // Set the memory layout
    std::string layout(argv[1]);
    if (layout == "linear") memory_layout = MemoryLayout::LINEAR;
    else if (layout == "inorder") memory_layout = MemoryLayout::INORDER;
    else if (layout == "bfs") memory_layout = MemoryLayout::BFS;
    else if (layout == "dfs") memory_layout = MemoryLayout::DFS;
    else if (layout == "veb") memory_layout = MemoryLayout::VEB;
    // else if (layout == "inorder_explicit") memory_layout = MemoryLayout::INORDER_EXPLICIT;
    // else if (layout == "inorder_explicit_int") memory_layout = MemoryLayout::INORDER_EXPLICIT_INT;
    else if (layout == "bfs_explicit") memory_layout = MemoryLayout::BFS_EXPLICIT;
    else if (layout == "bfs_explicit_int") memory_layout = MemoryLayout::BFS_EXPLICIT_INT;
    else if (layout == "dfs_explicit") memory_layout = MemoryLayout::DFS_EXPLICIT;
    else if (layout == "dfs_explicit_int") memory_layout = MemoryLayout::DFS_EXPLICIT_INT;
    // else if (layout == "veb_explicit") memory_layout = MemoryLayout::VEB_EXPLICIT;
    else if (layout == "veb_explicit_int") memory_layout = MemoryLayout::VEB_EXPLICIT_INT;
    else {
        std::cout << "Parameter parsing: The memory layout given is not valid." << std::endl;
        exit(-1);
    }

    // Set tree size bounds, number of queries, and random seed
    min_log_tree_size = intify_param(argv[2], 5);
    max_log_tree_size = intify_param(argv[3], 20);
    no_of_queries     = intify_param(argv[4], 10000);
    no_of_iterations  = intify_param(argv[5], 100);
    trim              = intify_param(argv[6], 5);
    size_increment    = (argc >= 8) ? intify_param(argv[7], 0) : 0;
    random_seed       = (argc >= 9) ? intify_param(argv[8], 0) : time(nullptr);
}

// TODO duplicated in SkewParams
int BenchParams::intify_param(const char *arg, int default_val) {
    std::istringstream iss(arg);
    int res;
    
    if (iss >> res) return res; // Successful conversion
    return default_val;         // Unsuccessful conversion, return default value
}

void BenchParams::print_usage(char *prog_name) {
    std::cout << "Call this program with the following parameters:" << std::endl;
    std::cout << "\tmemory layout [linear, inorder, bfs, dfs, veb]" << std::endl;
    std::cout << "\tminimum tree size (logarithmic)" << std::endl;
    std::cout << "\tmaximum tree size (logarithmic)" << std::endl;
    std::cout << "\tnumber of queries for each tree size" << std::endl;
    std::cout << "\tnumber of iterations of the queries" << std::endl;
    std::cout << "\tnumber of (best and worst) results to chop away" << std::endl;
    std::cout << "\thow much to increment tree size each step (optional)" << std::endl;
    std::cout << "\trandom seed (optional)" << std::endl;
    std::cout << std::endl;
    std::cout << "\tExample usage: " << prog_name << " bfs 5 20 10000 100 5" << std::endl;
}