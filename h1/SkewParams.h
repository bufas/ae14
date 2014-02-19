#pragma once

/**
 * Bundle of parameters for the build methods on some implementations
 */
struct SkewParams {
    int min_skew;
    int max_skew;
    int tree_size;
    int no_of_queries;
    int random_seed;
};
