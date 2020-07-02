#define BOOST_TEST_MODULE TEST
#include <boost/test/included/unit_test.hpp>

#include "grid.hpp"

BOOST_AUTO_TEST_CASE(General) {
     BOOST_CHECK_THROW(Grid<char>(3,0), std::invalid_argument);
     Grid <char> g(2,3);
     BOOST_TEST(g.width() == 3);
     BOOST_TEST(g.height() == 2);
     BOOST_CHECK_THROW(g(5,5), std::out_of_range);
     g(0,0)='a';
     g(0,1)='b';
     g(0,2)='c';
     g(1,0)='d';
     g(1,1)='e';
     g(1,2)='f';
     BOOST_TEST(g.toString("|") == "a|b|c\nd|e|f");
     BOOST_TEST(Grid<int>(1,3).toString() == "000"); //Checks correct initialization
}
