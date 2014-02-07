#pragma once

#include <cassert>
#include <vector>
#include "../PredSearchTree.h"
#include "Test.h"
#include "PredSearchTreeFactory.h"

/**
 * A skip test is a test in which a tree is built over some of the numbers
 * in [a;b). Which numbers depends on /x/ and /y/, where /x/ is the amount
 * of numbers to skip every time /y/ numbers have been added.
 *
 * An example skip test, "Skip 1 every 3 from 1 to 10":
 *
 *   v: 1 2 3 - 5 6 7 - 9
 *   p: 1 2 3 4 5 6 7 8 9
 *
 * Here, we first add 3 numbers (1-3) and then skip 1 number (4) and then
 * go back to adding another 3 numbers (5-7), then skip 1 (8), and then
 * add the remaining number (9), because we reached the end of the range.
 *
 * The queries are made with exactly the numbers in the interval [a;b).
 */
class SkipTest : public Test {

public:
    SkipTest(const PredSearchTreeFactory &factory) : factory(factory) {}

    void run() {
        #define RUN_SKIP_TEST(x,y,a,b) \
        RUN(Skip_ ## x ## _Every_ ## y ## _From_ ## a ## _To_ ## b);

        RUN_SKIP_TEST(0,0,1,100);

        RUN_SKIP_TEST(1,2,1,100);
        RUN_SKIP_TEST(1,3,1,100);
        RUN_SKIP_TEST(1,5,1,100);
        RUN_SKIP_TEST(1,10,1,100);

        RUN_SKIP_TEST(2,2,1,100);
        RUN_SKIP_TEST(2,3,1,100);
        RUN_SKIP_TEST(2,5,1,100);
        RUN_SKIP_TEST(2,10,1,100);

        RUN_SKIP_TEST(5,2,1,100);
        RUN_SKIP_TEST(5,3,1,100);
        RUN_SKIP_TEST(5,5,1,100);
        RUN_SKIP_TEST(5,10,1,100);

        RUN_SKIP_TEST(7,2,1,100);
        RUN_SKIP_TEST(7,3,1,100);
        RUN_SKIP_TEST(7,5,1,100);
        RUN_SKIP_TEST(7,10,1,100);

        RUN_SKIP_TEST(0,0,1, 1000);

        RUN_SKIP_TEST( 1, 2,1,1000);
        RUN_SKIP_TEST(10, 2,1,1000);
        RUN_SKIP_TEST(51,10,1,1000);
        RUN_SKIP_TEST(99,99,1,1000);

        #undef RUN_SKIP_TEST
    }

private:
    PredSearchTreeFactory factory;

    /**
     * Create a skip test.
     *
     * This is a loop over [a;b) in which we switch between adding numbers
     * to both the tree values and the predecessor vector, to adding only
     * the previous number to the predecessor vector.
     *
     * At first, we add y numbers to both vectors, and then we switch over
     * to adding the previous number to only the predecessor vector, then
     * back again, and so on. The result is a value vector for the search
     * tree, and a predecessor vector for the test. The predecessor vector
     * contains the expected predecessor for every number in [a;b).
     */
    void create_skip_test(std::vector<int> &v, std::vector<int> &p, int x, int y, int a, int b) {
        // Infinite loop guard
        if (y == 0) {
            y = 1;
        }

        bool skip = false;
        for (int i = a; i < b; /* empty */) {
            if (skip) {
                for (int j = 0; j < x; ++j) {
                    p.push_back(i-1);
                }
                i += x;
                skip = false;
            } else {
                for (int j = 0; j < y; ++j) {
                    v.push_back(i+j);
                    p.push_back(i+j);
                }
                i += y;
                skip = true;
            }
        }
    }

    /**
     * Verify a skip test.
     *
     * This is a simple loop over [a;b), comparing the predecessor of a
     * given value /i/ with the expected value in /p/.
     */
    void verify_skip_test(std::vector<int> &v, std::vector<int> &p, int x, int y, int a, int b) {
        std::auto_ptr<PredSearchTree> tree(factory.createTree(v));
        std::vector<int>::iterator it = p.begin();

        // int dummy = 0;
        for (int i = a; i < b; ++i, ++it) {
            is_equal(tree->pred(i), *it);
            // dummy += tree->pred(i);
        }
        // std::cout << dummy << std::endl;
    }

    /**
     * Macro for spawning a skip test function.
     */
    #define MAKE_SKIP_TEST(x,y,a,b) \
    void Skip_ ## x ## _Every_ ## y ## _From_ ## a ## _To_ ## b() { \
        std::vector<int> v; \
        std::vector<int> p; \
        create_skip_test(v, p, x, y, a, b); \
        verify_skip_test(v, p, x, y, a, b); \
    }

    MAKE_SKIP_TEST(0,0,1, 100)

    MAKE_SKIP_TEST(1,2,1, 100)
    MAKE_SKIP_TEST(1,3,1, 100)
    MAKE_SKIP_TEST(1,5,1, 100)
    MAKE_SKIP_TEST(1,10,1,100)

    MAKE_SKIP_TEST(2,2,1, 100)
    MAKE_SKIP_TEST(2,3,1, 100)
    MAKE_SKIP_TEST(2,5,1, 100)
    MAKE_SKIP_TEST(2,10,1,100)

    MAKE_SKIP_TEST(5,2,1, 100)
    MAKE_SKIP_TEST(5,3,1, 100)
    MAKE_SKIP_TEST(5,5,1, 100)
    MAKE_SKIP_TEST(5,10,1,100)

    MAKE_SKIP_TEST(7,2,1, 100)
    MAKE_SKIP_TEST(7,3,1, 100)
    MAKE_SKIP_TEST(7,5,1, 100)
    MAKE_SKIP_TEST(7,10,1,100)

    MAKE_SKIP_TEST(0,0,1, 1000)

    MAKE_SKIP_TEST( 1, 2,1,1000)
    MAKE_SKIP_TEST(10, 2,1,1000)
    MAKE_SKIP_TEST(51,10,1,1000)
    MAKE_SKIP_TEST(99,99,1,1000)

    MAKE_SKIP_TEST(0,0,1, 100000)

    MAKE_SKIP_TEST(   1,  2,1,100000)
    MAKE_SKIP_TEST(   5, 26,1,100000)
    MAKE_SKIP_TEST(  50, 50,1,100000)
    MAKE_SKIP_TEST(1000,200,1,100000)

    #undef MAKE_SKIP_TEST
};