#include <iostream>
#include <stdlib.h>
#include <sys/time.h>
#include <vector>
#include <algorithm>
#include <cstdio>

#include "../LinearSearch.h"
#include "../InorderBinarySearch.h"
#include "../BFSBinarySearch.h"

void print_time(int elems, int searches, struct timeval before, struct timeval after) {
    long utime = ((after.tv_sec - before.tv_sec) * 1000000) + after.tv_usec - before.tv_usec;
    long stime = ((after.tv_sec - before.tv_sec) * 1000000) + after.tv_usec - before.tv_usec;
    printf("%d\t%d\t%ld\n", elems, searches, (utime + stime));
}

/**
 * Does the actual timing of the searches
 */
void bench(PredSearchTree *t, const std::vector<int> &queries, int tree_size) {
    struct timeval before, after;
    gettimeofday(&before, nullptr); // start timer

    // do the predecessor search
    int dummy = 0;
    for (int q = 0; q < queries.size(); q++) {
        dummy += t->pred(queries[q]);
    }

    gettimeofday(&after, nullptr); // stop timer
    print_time(tree_size, queries.size(), before, after); // Print time elapsed

    // TODO use dummy, or the loop will be optimized away
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cout << "Call this program with one of the following parameters" << std::endl;
        std::cout << "\tlinear" << std::endl;
        std::cout << "\tinorder" << std::endl;
        std::cout << "\tbfs" << std::endl;
        exit(-1);
    }

    srand(time(nullptr));

    const int no_of_queries    = 1000;
    const int iterations       = 25;
    const int inc_pr_iteration = 1000;

    // Generate query numbers
    std::vector<int> queries;
    for (int q = 0; q < no_of_queries; q++) queries.push_back(rand());

    std::cout << "# Timing inorder-tree predecessor search" << std::endl;
    std::cout << "# elements, searches, time in us" << std::endl;
    for (int i = 1; i <= iterations; i++) {

        const int tree_size = i * inc_pr_iteration;

        // generate random numbers to search for
        std::vector<int> values;
        for (int q = 0; q < tree_size; q++) values.push_back(rand());

        // create the tree (Yep, this is ugly, but it's also 2 o'clock)
        PredSearchTree *t;
        if (strcmp(argv[1], "linear") == 0) t = new LinearSearch(values);
        else if (strcmp(argv[1], "bfs") == 0) t = new BFSBinarySearch(values);
        else if (strcmp(argv[1], "inorder") == 0) t = new InorderBinarySearch(values);
        else {
            std::cout << "invalid argument: " << argv[1] << std::endl;
            exit(-1);
        }

        // Time the predecessor searches
        bench(t, queries, tree_size);
    }
}