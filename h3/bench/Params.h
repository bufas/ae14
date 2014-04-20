#pragma once

#include <sstream>
#include "PerfVar.h"

class Params {

public:
    Params(int argc, char **argv);

    // Data fields (public for easier access)
    PerfVar perf_var;               // The performance variable to count
    int no_of_queries;              // Number of queries to run each iteration
    int no_of_iterations;           // We time queries this number of times, and take the average running time
    int trim;                       // Remove the trim best and worst running times from the output
    int random_seed;                // The seed for the random generator

private:
    int intify_param(const char arg[], int default_val);
    void print_usage(char *prog_name);

};

Params::Params(int argc, char **argv) {
    // Check if there is enough parameters and print help message if not
    if (argc < 5) {
        print_usage(argv[0]);
        exit(-1);
    }

    // Set the performance variable
    std::string pvar(argv[1]);
    if (pvar == "BRANCH") perf_var = PerfVar::BRANCH;
    else if (pvar == "BPU") perf_var = PerfVar::BPU;
    else if (pvar == "HW_CACHE") perf_var = PerfVar::HW_CACHE;
    else if (pvar == "LL_CACHE") perf_var = PerfVar::LL_CACHE;
    else if (pvar == "L1_CACHE") perf_var = PerfVar::L1_CACHE;
    else if (pvar == "DATA_TLB") perf_var = PerfVar::DATA_TLB;
    else {
        std::cout << "Parameter parsing: The performance variable given is not valid." << std::endl;
        exit(-1);
    }

    // Set tree size bounds, number of queries, and random seed
    no_of_queries     = intify_param(argv[2], 10000);
    no_of_iterations  = intify_param(argv[3], 100);
    trim              = intify_param(argv[4], 5);
    random_seed       = (argc >= 6) ? intify_param(argv[5], 0) : time(nullptr);
}

int Params::intify_param(const char *arg, int default_val) {
    std::istringstream iss(arg);
    int res;
    
    if (iss >> res) return res; // Successful conversion
    return default_val;         // Unsuccessful conversion, return default value
}

void Params::print_usage(char *prog_name) {
    std::cout << "Call this program with the following parameters:" << std::endl;
    std::cout << "\tperformance variable [BPU, LL_CACHE, L1_CACHE, DATA_TLB]" << std::endl;
    std::cout << "\tnumber of queries for each tree size" << std::endl;
    std::cout << "\tnumber of iterations of the queries" << std::endl;
    std::cout << "\tnumber of (best and worst) results to chop away" << std::endl;
    std::cout << "\trandom seed (optional)" << std::endl;
    std::cout << std::endl;
    std::cout << "\tExample usage: " << prog_name << " LL_CACHE 10000 100 5" << std::endl;
}