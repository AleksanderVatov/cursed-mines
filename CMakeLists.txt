cmake_minimum_required(VERSION 3.0)

project(mines)
enable_testing()

add_executable(mines main.cpp)

if(BUILD_TESTING)
    enable_testing()
    add_executable(grid_test grid_test.cpp)
    add_test(grid_test grid_test)
endif()

install(TARGETS mines RUNTIME DESTINATION bin)
