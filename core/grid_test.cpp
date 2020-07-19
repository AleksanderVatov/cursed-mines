#define BOOST_TEST_MODULE TEST

#include <algorithm>

#include <boost/test/included/unit_test.hpp>

#include "grid.hpp"

BOOST_AUTO_TEST_CASE(General) {
    BOOST_TEST(Grid<char>::fromString("abcdef",2,3).toString() == "abc\ndef");
    
    int array1[6] = {1, 2, 3, 4, 5, 6};
    auto g0 = Grid<int>::fromArray(array1, 2, 3);
    for(int i = 0; i < g0.width() * g0.height(); ++i) //Test flatIndex and unravelIndex
        BOOST_ASSERT(i == g0.flatIndex(g0.unravelIndex(i)));
    
    BOOST_ASSERT(Grid<int>::fromArray(array1, 2, 3) == Grid<int>::fromString("1 2 3 4 5 6", 2, 3));
    BOOST_TEST(Grid<int>::fromArray(array1, 2, 3).toString() == Grid<int>::fromString("1 2 3 4 5 6", 2, 3).toString());
    
    for(auto &i: g0) if(i % 2 == 0) i = 0;
    BOOST_TEST(g0.toString() == "103\n050");

    BOOST_CHECK_THROW(Grid<char>(3,0), std::invalid_argument);
    Grid <char> g(2,3);
    BOOST_TEST(g.width() == 3);
    BOOST_TEST(g.height() == 2);
    BOOST_CHECK_THROW(g.at(5,5), std::out_of_range);
    g.at(0,0)='a'; g.at(0,1)='b'; g.at(0,2)='c';
    g.at(1,0)='d'; g.at(1,1)='e'; g.at(1,2)='f';
    BOOST_TEST(g.toString("|","\t") == "a|b|c\td|e|f");
    BOOST_TEST(Grid<int>(1,3).toString() == "000"); //Checks correct initialization
}

BOOST_AUTO_TEST_CASE(Algorithms) {
    auto small = Grid<int>(2,2);
    BOOST_ASSERT(small.toString("","") == "0000");
    std::fill(small.begin(), small.end(), 1);
    BOOST_TEST(small.toString("", "") == "1111");
    
    auto in = Grid<char>::fromString("abcdef",2,3);
    auto out = Grid<char>(2,3);
    std::copy(in.begin(), in.end(), out.begin());
    BOOST_TEST(in.toString() == out.toString());
    
    auto nums = Grid<int>::fromString("1 2 3 4 5 6", 2, 3);
    std::for_each(nums.begin(), nums.end(), [](int &n){ n++; });
    BOOST_TEST(nums.toString(" ", " ") == "2 3 4 5 6 7");
}

BOOST_AUTO_TEST_CASE(Neighborhoods) {
    Grid<int> small (3,3);
    for(int& n: small.neighbors(1, 1)) n = 1;
    BOOST_TEST(small.toString(""," ") == "111 101 111");
    
    Grid<int> large(7, 7);
    for(int& n: large.neighbors(0,0)) n = 1;
    for(int& n: large.neighbors(0,3)) n = 2;
    for(int& n: large.neighbors(0,6)) n = 3;
    for(int& n: large.neighbors(3,0)) n = 4;
    for(int& n: large.neighbors(3,3)) n = 5;
    for(int& n: large.neighbors(3,6)) n = 6;
    for(int& n: large.neighbors(6,0)) n = 7;
    for(int& n: large.neighbors(6,3)) n = 8;
    for(int& n: large.neighbors(6,6)) n = 9;
    
    std::string target = 
        "0120230\n"
        "1122233\n"
        "4455566\n"
        "0450560\n"
        "4455566\n"
        "7788899\n"
        "0780890";
        
    BOOST_TEST(large.toString() == target);
}
