#pragma once

#include <sstream>

class SkewParams {

public:
    SkewParams(int argc, char **argv);

    // Data fields (public for easier access)
    int min_skew;
    int max_skew;
    int tree_size;
    int no_of_queries;
    int iterations;
    int trim;
    int random_seed;

private:
    int intify_param(const char arg[], int default_val);
    void print_usage(char *prog_name);

};

SkewParams::SkewParams(int argc, char **argv) {
    // Check if there is enough parameters and print help message if not
    if (argc < 7) {
        print_usage(argv[0]);
        exit(-1);
    }

    // Set tree size bounds, number of queries, and random seed
    min_skew       = intify_param(argv[1], 10);
    max_skew       = intify_param(argv[2], 20);
    tree_size      = intify_param(argv[3], 100000);
    no_of_queries  = intify_param(argv[4], 1000);
    iterations     = intify_param(argv[5], 100);
    trim           = intify_param(argv[6], 5);
    random_seed    = (argc >= 8) ? intify_param(argv[7], 0) : time(nullptr);
}

// TODO duplicated in BenchParams
int SkewParams::intify_param(const char *arg, int default_val) {
    std::istringstream iss(arg);
    int res;
    
    if (iss >> res) return res; // Successful conversion
    return default_val;         // Unsuccessful conversion, return default value
}

void SkewParams::print_usage(char *prog_name) {
    std::cout << "Call this program with one of the following parameters" << std::endl;
    std::cout << "\tminimum skew (percentage)" << std::endl;
    std::cout << "\tmaximum skew (percentage)" << std::endl;
    std::cout << "\ttree size" << std::endl;
    std::cout << "\tnumber of queries" << std::endl;
    std::cout << "\trandom seed (optional)" << std::endl;
    std::cout << std::endl;
    std::cout << "\tExample usage: " << prog_name << " 0 100 100000 1000000" << std::endl;
}
