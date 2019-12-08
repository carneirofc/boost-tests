cmake_minimum_required(VERSION 3.15)
project(regatron-interface)

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

add_executable(regatron main.cpp Comm.cpp Logger.cpp)
set_property(TARGET regatron PROPERTY CXX_STANDARD 17)

if(Boost_FOUND)
    target_include_directories(regatron PRIVATE ${Boost_INCLUDE_DIRS})
    target_link_libraries(regatron ${Boost_LIBRARIES})
endif()

target_include_directories(regatron PRIVATE "../vendor/regatron/V3.80.00 30072014 (Linux)/include")
target_link_libraries(regatron "/home/carneirofc/boost-tests/vendor/regatron/V3.80.00 30072014 (Linux)/Linux/x64/libtcio.so")

# Logging and format
find_package(fmt REQUIRED)
find_package(spdlog REQUIRED)

target_link_libraries(regatron fmt::fmt spdlog::spdlog_header_only)