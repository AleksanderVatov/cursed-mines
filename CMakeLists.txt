cmake_minimum_required(VERSION 3.0)
project(mines)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(mines main.cpp minefield.cpp square.cpp)
target_link_libraries(mines ${CURSES_LIBRARY})

if(BUILD_TESTING)
    enable_testing()
    find_package(Boost COMPONENTS unit_test_framework REQUIRED)
    include_directories(${Boost_INCLUDE_DIRS})
    
    add_executable(grid_test grid_test.cpp)
    add_test(grid_test grid_test)
    
    add_executable(minefield_test minefield.cpp minefield_test.cpp square.cpp)
endif()

install(TARGETS mines RUNTIME DESTINATION bin)
