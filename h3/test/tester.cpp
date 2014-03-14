#include <boost/test/minimal.hpp>
#include "../include/RSNaive.h"

//____________________________________________________________________________//

int test_main( int, char *[] )
{
    RSNaive<10> rs("1010001101");
    BOOST_CHECK( rs.rank(3) == 2 );
    BOOST_CHECK( rs.select(5) == 10 );
    BOOST_CHECK( rs.select(6) == -1 );
    return 0;
}

//____________________________________________________________________________//