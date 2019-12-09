cmake_minimum_required(VERSION 3.15)
project(boost-asio)

# General project definitions
add_compile_options(-Wall -Wextra -Wpedantic)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

# Boost
set(BOOST_ROOT /home/carneirofc/boost-tests/vendor/boost_1_71_0)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_LIBS ON)
find_package(Boost 1.71.0 COMPONENTS regex)

add_executable(main main.cpp Logger.cpp)
set_property(TARGET main PROPERTY CXX_STANDARD 17)

if(Boost_FOUND)
    target_include_directories(main PRIVATE ${Boost_INCLUDE_DIRS})
    target_link_libraries(main ${Boost_LIBRARIES})
endif()

# Logging and format
find_package(fmt REQUIRED)
find_package(spdlog REQUIRED)

target_link_libraries(main fmt::fmt spdlog::spdlog_header_only)