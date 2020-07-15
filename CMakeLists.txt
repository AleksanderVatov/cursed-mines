cmake_minimum_required(VERSION 3.0)

project(mines)

add_executable(mines main.cpp)

if(BUILD_TESTING)
    enable_testing()
    find_package(Boost COMPONENTS unit_test_framework REQUIRED)
    include_directories(${Boost_INCLUDE_DIRS})
    
    add_executable(grid_test grid_test.cpp)
    add_test(grid_test grid_test)
    
    add_executable(minefield_test minefield.cpp minefield_test.cpp square.cpp)
endif()

install(TARGETS mines RUNTIME DESTINATION bin)
