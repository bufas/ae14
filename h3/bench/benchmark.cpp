#include <iostream> // std::cout, std::endl
#include <vector> // std::vector
#include <cstdio> // printf()
#include <fstream> // std::ofstream
#include <memory> // std::unique_ptr
#include <numeric> // std::accumulate

#include "Timer.h"
#include "Params.h"

#include "../include/RSIndexedSmall.h"

/**
 * Time queries on a specific instance size
 */
template<size_t N>
void bench(const RSIndexedSmall<N> &t, const std::vector<unsigned int> &queries, int elements, const Params &p) {
    Timer timer(p.perf_var);

    // Run the predecessor search a number of times
    int dummy = 0;
    for (int i = 0; i < p.no_of_iterations; i++) {
        timer.start();
        for (int q = 0; q < p.no_of_queries; q++) {
            dummy += t.rank(queries[q]);
        }
        timer.stop();
    }

    printf("%d\t%d\t%ld\t%ld\t%ld\t%ld\t%ld\t%ld\t%ld\t%ld\t%ld\t%.4lf\t%.4lf\t%.4lf\n", 
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


void print_output_header(const Params &p) {
    std::cout << "# Timing rank queries with the following parameters" << std::endl;
    std::cout << "# \tperformance counter  : " << as_string(p.perf_var) << std::endl;
    std::cout << "# \tnumber of queries    : " << p.no_of_queries << std::endl;
    std::cout << "# \tnumber of iterations : " << p.no_of_iterations << std::endl;
    std::cout << "# \tresults trimmed      : " << p.trim << std::endl;
    std::cout << "# \trandom seed          : " << p.random_seed << std::endl;
    std::cout << "#" << std::endl;
    std::cout << "# Datalines: tree size, #searches, TIME[avg, fast, slow] in us, MISS[avg, low, high], ACCESS[avg, low, high], RATIO[avg, low, high] in %%" << std::endl;
}

template<size_t N>
void call_bench(const Params &p) {
    const int size = 1 << (N-6);
    unsigned int no_of_ones = 0;

    // Generate the input
    std::vector<unsigned long> values;
    for (int q = 0; q < size; q++) {
        unsigned long val = rand(); val <<= 32; val |= rand();
        no_of_ones += __builtin_popcountl(val);
        values.push_back(val);
    }

    // Generate the queries
    std::vector<unsigned int> queries;
    for (int q = 0; q < p.no_of_queries; q++) queries.push_back(rand() % size); // Modulo with no_of_ones for select benchmark

    // Start the bench
    auto t = RSIndexedSmall<1 << N>(values);
    bench(t, queries, (1 << N), p);
}

int main(int argc, char *argv[]) {
    // Initialization
    Params p(argc, argv);
    srand(p.random_seed);
    print_output_header(p);


    call_bench<6>(p);
    call_bench<7>(p);
    call_bench<8>(p);
    call_bench<9>(p);

    call_bench<10>(p);
    call_bench<11>(p);
    call_bench<12>(p);
    call_bench<13>(p);
    call_bench<14>(p);
    call_bench<15>(p);
    call_bench<16>(p);
    call_bench<17>(p);
    call_bench<18>(p);
    call_bench<19>(p);

    call_bench<20>(p);
    call_bench<21>(p);
    call_bench<22>(p);
    call_bench<23>(p);
    call_bench<24>(p);
    call_bench<25>(p);
    // call_bench<26>(p);
    // call_bench<27>(p);
    // call_bench<28>(p);
    // call_bench<29>(p);

    // call_bench<30>(p);
}