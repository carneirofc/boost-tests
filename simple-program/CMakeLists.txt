cmake_minimum_required(VERSION 3.15)
project(simple-program)

set(CMAKE_CXX_STANDARD 14)

add_executable(untitled main.cpp main.cpp)
#target_include_directories(untitled PRIVATE ../vendor/boost_1_71_0_build/include) # include path
#target_link_libraries(untitled /home/carneirofc/boost-tests/simple-program/vendor/) # Full lib path

