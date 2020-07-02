#define BOOST_TEST_MODULE TEST
#include <boost/test/included/unit_test.hpp>

#include "grid.hpp"

BOOST_AUTO_TEST_CASE(General) {
     Grid <char> g(2,3);
     BOOST_TEST(g.width() == 3);
     BOOST_TEST(g.height() == 2);
     g(0,0)='a';
     g(0,1)='b';
     g(0,2)='c';
     g(1,0)='d';
     g(1,1)='e';
     g(1,2)='f';
    BOOST_TEST(g.toString("|") == "a|b|c\nd|e|f");
    
}
