cmake_minimum_required(VERSION 3.0)
project(mines)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(core)
add_subdirectory(ui)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

if(APPLE)
  # This is where Homebrew installs ncurses
  set(CMAKE_PREFIX_PATH /usr/local/opt/ncurses)
endif()

set(CURSES_NEED_WIDE TRUE) # Unicode support required
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(mines main.cpp ${CORE_SOURCE} ${UI_SOURCE})
target_link_libraries(mines ${CURSES_LIBRARY})

install(TARGETS mines RUNTIME DESTINATION bin)
