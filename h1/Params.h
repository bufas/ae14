#pragma once

/**
 * Bundle of parameters for the build methods on some implementations
 */
struct Params {
    MemoryLayout memory_layout;
    int min_log_tree_size;
    int max_log_tree_size;
    int no_of_queries;
    int size_increment;
    int random_seed;
};
