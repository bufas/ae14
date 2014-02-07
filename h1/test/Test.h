#pragma once

#include <iostream>
#include <string>

/**
 * Simple macro that expands:
 *
 *     RUN(name_of_test_function)
 *
 * to the following:
 *
 *     g_current_test = "name_of_test_function";
 *     name_of_test_function();
 *
 * The purpose of this is to allow the assertion methods to print out
 * exactly which test failed.
 */
#define RUN(TEST) \
g_current_test = #TEST; \
TEST()

/**
 * The name of the current test
 */
std::string g_current_test;

/**
 * Equality assertion
 */
void is_equal(int actual, int expected) {
    if (actual != expected) {
        std::cout << "ERROR in test: " << g_current_test << std::endl;
        std::cout << "  expected: " << expected << ", actual: " << actual << std::endl << std::flush;
        exit(-1);
    }
}

/**
 * The Test interface has but a single method for running the
 * tests it contains.
 */
class Test {
public:
    virtual ~Test() {}

    virtual void run() = 0;
};