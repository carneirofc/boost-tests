cmake_minimum_required(VERSION 3.17)
project(boost-asio)

# General project definitions
add_compile_options(-Wall -Wextra -Wpedantic)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -fno-omit-frame-pointer -fsanitize=address")

set(CMAKE_CXX_FLAGS_RELEASE "-O2")

# Boost
set(BOOST_ROOT ${CMAKE_CURRENT_LIST_DIR}/../vendor/boost_1_71_0)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_LIBS ON)
find_package(Boost 1.71.0 COMPONENTS regex)

add_executable(main main.cpp log/Logger.cpp net/Server.cpp net/Handler.cpp)
target_include_directories(main PRIVATE  ${CMAKE_CURRENT_SOURCE_DIR})
set_property(TARGET main PROPERTY CXX_STANDARD 20)

if(Boost_FOUND)
    target_include_directories(main PRIVATE ${Boost_INCLUDE_DIRS})
    target_link_libraries(main ${Boost_LIBRARIES})
endif()

# Logging and format
find_package(fmt REQUIRED)
find_package(spdlog REQUIRED)

target_link_libraries(main fmt::fmt spdlog::spdlog_header_only)
