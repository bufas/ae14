#include <boost/test/minimal.hpp>
#include <vector>
#include <iostream>
#include "../include/RSNaive.h"
#include "../include/RSIndexed.h"
#include "../include/RSIndexedCacheOpt.h"
#include "../include/RSIndexedSmall.h"

//____________________________________________________________________________//

void test_rs_naive() {
    RSNaive<10> rs("1010001101");
    BOOST_CHECK( rs.rank(3) == 2 );
    BOOST_CHECK( rs.select(5) == 10 );
    BOOST_CHECK( rs.select(6) == -1 );
}

void test_rs_indexed() {
    std::vector<unsigned long> v;
    v.push_back(7);
    v.push_back(1);
    v.push_back(63);
    RSIndexed<192> rs(v);

    BOOST_CHECK( rs.rank(40) == 3 );
    BOOST_CHECK( rs.rank(100) == 4 );
    BOOST_CHECK( rs.select(5) == 129 );
    BOOST_CHECK( rs.select(1) == 1 );
}

void test_rs_indexed_cache_opt() {
    std::vector<unsigned long> v;
    v.push_back(7);
    v.push_back(1);
    v.push_back(63);
    v.push_back(7);
    v.push_back(1);
    v.push_back(63);
    v.push_back(7);
    v.push_back(1);
    v.push_back(63);
    v.push_back(7);
    RSIndexedCacheOpt<10 * 64> rs(v);

    BOOST_CHECK( rs.rank(192 * 3 - 60) == 28 );
    BOOST_CHECK( rs.rank(40) == 3 );
    BOOST_CHECK( rs.rank(100) == 4 );
    BOOST_CHECK( rs.select(5) == 129 );
    BOOST_CHECK( rs.select(1) == 1 );
}

void test_rs_indexed_small() {
    std::vector<unsigned long> v;
    v.push_back(7);
    v.push_back(1);
    v.push_back(63);
    v.push_back(7);
    v.push_back(1);
    v.push_back(63);
    v.push_back(7);
    v.push_back(1);
    v.push_back(63);
    v.push_back(7);
    RSIndexedSmall<10 * 64> rs(v);

    BOOST_CHECK( rs.rank(192 * 3 - 60) == 28 );
    BOOST_CHECK( rs.rank(40) == 3 );
    BOOST_CHECK( rs.rank(100) == 4 );
    BOOST_CHECK( rs.select(5) == 129 );
    BOOST_CHECK( rs.select(1) == 1 );
}

void test_all_ones() {
    const int N = 50000;
    std::vector<unsigned long> v;
    for (int i = 0; i < N; ++i) {
        v.push_back(18446744073709551615ul);
    }
    RSIndexedSmall<N * 64> rs(v);

    for (int i = 1; i < N * 64; ++i) {
        BOOST_CHECK( rs.rank(i) == i);
        if ( rs.rank(i) != i ) std::cout << "rs.rank("<<i<<") = " << rs.rank(i) << std::endl;
        // BOOST_CHECK( rs.select(i) == i);
    }
}

void test_alternating_ones() {
    const int N = 50000;
    std::vector<unsigned long> v;
    for (int i = 0; i < N; ++i) {
        v.push_back(12297829382473034410ul);
    }
    RSIndexedSmall<N * 64> rs(v);

    for (int i = 1; i < N * 64; ++i) {
        BOOST_CHECK( rs.rank(i) == (i/2));
        if ( rs.rank(i) != (i/2) ) std::cout << "rs.rank("<<i<<") = " << rs.rank(i) << std::endl;
        // BOOST_CHECK( rs.select(i) == i);
    }
}

//____________________________________________________________________________//

int test_main( int, char *[] )
{
    // test_rs_naive();
    // test_rs_indexed();
    // test_rs_indexed_cache_opt();
    // test_rs_indexed_small();
    test_all_ones();
    test_alternating_ones();
    return 0;
}

//____________________________________________________________________________//
