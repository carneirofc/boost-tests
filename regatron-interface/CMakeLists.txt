cmake_minimum_required(VERSION 3.15)

# Set the project name to your project name, my project isn't very descriptive
project(regatron-interface CXX)
include(cmake/StandardProjectSettings.cmake)

# Link this 'library' to set the c++ standard / compile-time options requested
add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_20)

# Link this 'library' to use the warnings specified in CompilerWarnings.cmake
add_library(project_warnings INTERFACE)

# standard compiler warnings
include(cmake/CompilerWarnings.cmake)
set_project_warnings(project_warnings)

# sanitizer options if supported by compiler
include(cmake/Sanitizers.cmake)
enable_sanitizers(project_options)

# enable doxygen
include(cmake/Doxygen.cmake)
enable_doxygen()

# allow for static analysis options
include(cmake/StaticAnalyzers.cmake)

option(BUILD_SHARED_LIBS "Enable compilation of shared libraries" OFF)
option(ENABLE_TESTING "Enable Test Builds" OFF)

# Very basic PCH example
option(ENABLE_PCH "Enable Precompiled Headers" OFF)
if (ENABLE_PCH)
  # This sets a global PCH parameter, each project will build its own PCH, which
  # is a good idea if any #define's change
  # 
  # 
  target_precompile_headers(project_options INTERFACE <vector> <string> <map> <utility>)
endif()


# Set up some extra Conan dependencies based on our needs
# before loading Conan
set(CONAN_EXTRA_REQUIRES "")
set(CONAN_EXTRA_OPTIONS "")

set(CONAN_EXTRA_REQUIRES ${CONAN_EXTRA_REQUIRES} boost/1.71.0@conan/stable)

include(cmake/Conan.cmake)
run_conan()

if(ENABLE_TESTING)
  enable_testing()
  message(
    "Building Tests. Be sure to check out test/constexpr_tests for constexpr testing"
  )
  add_subdirectory(test)
endif()

if(ENABLE_FUZZING)
  message(
    "Building Fuzz Tests, using fuzzing sanitizer https://www.llvm.org/docs/LibFuzzer.html"
  )
  add_subdirectory(fuzz_test)
endif()


add_subdirectory(src)


# cmake_minimum_required(VERSION 3.15)
# project(regatron-interface)

# # General project definitions
# add_compile_options(-Wall -Wextra -Wpedantic)

# if(NOT CMAKE_BUILD_TYPE)
#     set(CMAKE_BUILD_TYPE Debug)
# endif()

# set(CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
# set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -fno-omit-frame-pointer -fsanitize=address")
# set(CMAKE_CXX_STANDARD 20)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)


# set(CMAKE_CXX_FLAGS_RELEASE "-O2")


# # Boost
# set(BOOST_ROOT "${CMAKE_CURRENT_LIST_DIR}/../vendor/boost_1_71_0")
# set(Boost_USE_MULTITHREADED ON)
# set(Boost_USE_STATIC_LIBS ON)
# find_package(Boost 1.71.0 COMPONENTS regex)

# add_executable(regatron 
#     main.cpp 
#     log/Logger.cpp
#     net/Handler.cpp
#     net/Server.cpp
#     regatron/Comm.cpp
#     regatron/Handler.cpp
# )
# set_property(TARGET regatron PROPERTY CXX_STANDARD 20)
# target_include_directories(regatron PRIVATE  ${CMAKE_CURRENT_SOURCE_DIR})

# if(Boost_FOUND)
#     target_include_directories(regatron PRIVATE ${Boost_INCLUDE_DIRS})
#     target_link_libraries(regatron ${Boost_LIBRARIES})
# endif()

# target_include_directories(regatron PRIVATE "${CMAKE_CURRENT_LIST_DIR}/../vendor/regatron/V3.80.00 30072014 (Linux)/include")
# target_link_libraries(regatron "${CMAKE_CURRENT_LIST_DIR}/../vendor/regatron/V3.80.00 30072014 (Linux)/Linux/x64/libtcio.so")

# # Logging and format
# find_package(fmt REQUIRED)
# find_package(spdlog REQUIRED)

# target_link_libraries(regatron fmt::fmt spdlog::spdlog_header_only)
