set(CORE_SOURCE 
    ${CMAKE_CURRENT_SOURCE_DIR}/square.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/game.cpp
    PARENT_SCOPE)

if(BUILD_TESTING)
    enable_testing()
    find_package(Boost COMPONENTS unit_test_framework REQUIRED)
    include_directories(${Boost_INCLUDE_DIRS})
    
    add_executable(grid_test grid_test.cpp)
    add_test(grid_test grid_test)
endif()
