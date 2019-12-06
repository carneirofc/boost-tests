cmake_minimum_required(VERSION 3.10)
project(regatron-interface)

set(CMAKE_CXX_STANDARD 17)
set(BOOST_ROOT /home/carneirofc/boost-tests/vendor/boost_1_71_0_build)

set(Boost_USE_STATIC_LIBS ON) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost 1.71.0 COMPONENTS log regex) 

if(Boost_FOUND)
    add_executable(regatron main.cpp Regatron.cpp)
    target_include_directories(regatron PRIVATE ${Boost_INCLUDE_DIRS}) 
    target_link_libraries(regatron ${Boost_LIBRARIES})
endif()
target_include_directories(regatron PRIVATE ../vendor/regatron/V3.80.00\ 30072014\ \(Linux\)/include)
target_link_libraries(regatron /home/carneirofc/boost-tests/vendor/regatron/V3.80.00\ 30072014\ \(Linux\)/Linux/x64/libtcio.so) # Full lib path

# LinuxTCIO example
add_executable(linuxTcioSample linuxTcioSample.cpp)
target_include_directories(linuxTcioSample
    PRIVATE
    ../vendor/boost_1_71_0_build/include
    ../vendor/regatron/V3.80.00\ 30072014\ \(Linux\)/include)

target_link_libraries(linuxTcioSample
    /home/carneirofc/boost-tests/vendor/regatron/V3.80.00\ 30072014\ \(Linux\)/Linux/x64/libtcio.so) # Full lib path

