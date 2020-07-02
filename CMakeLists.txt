cmake_minimum_required(VERSION 3.0)

project(mines)

add_executable(mines main.cpp)

install(TARGETS mines RUNTIME DESTINATION bin)
