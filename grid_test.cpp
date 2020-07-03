#define BOOST_TEST_MODULE TEST
#include <boost/test/included/unit_test.hpp>

#include "grid.hpp"

BOOST_AUTO_TEST_CASE(General) {
    BOOST_TEST(Grid<char>::fromString("abcdef",2,3).toString() == "abc\ndef");
    
    int array1[6] = {1, 2, 3, 4, 5, 6};
    auto g0 = Grid<int>::fromArray(array1, 2, 3);
    BOOST_ASSERT(Grid<int>::fromArray(array1, 2, 3) == Grid<int>::fromString("1 2 3 4 5 6", 2, 3));
    BOOST_TEST(Grid<int>::fromArray(array1, 2, 3).toString() == Grid<int>::fromString("1 2 3 4 5 6", 2, 3).toString());

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
    BOOST_TEST(g.toString("|","\t") == "a|b|c\td|e|f");
    BOOST_TEST(Grid<int>(1,3).toString() == "000"); //Checks correct initialization
}
