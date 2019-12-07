cmake_minimum_required(VERSION 3.15)
project(simple-program)

add_compile_options(-Wall -Wextra -Wpedantic)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

add_executable(main main.cpp)
set_property(TARGET main PROPERTY CXX_STANDARD 17)
