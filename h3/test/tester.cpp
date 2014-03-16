#include <boost/test/minimal.hpp>
#include <vector>
#include <iostream>
#include "../include/RSNaive.h"
#include "../include/RSIndexed.h"

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

//____________________________________________________________________________//

int test_main( int, char *[] )
{
    test_rs_naive();
    test_rs_indexed();
    return 0;
}

//____________________________________________________________________________//
