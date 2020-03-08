#!/bin/bash
set -e
set -x

function fmt(){
    # Fmt
    mkdir -p vendor/fmt/build
    pushd vendor/fmt/build
    cmake ..
    make -j 16
    make install
    popd
}


function spdlog(){
    mkdir -p vendor/spdlog/build
    pushd vendor/spdlog/build
    cmake ..
    make -j 16
    make install
    popd
}

function boost(){
    # Boost
    pushd vendor
    wget  https://dl.bintray.com/boostorg/release/1.71.0/source/boost_1_71_0.tar.bz2
    tar --bzip2 -xf boost_1_71_0.tar.bz2
    rm -f boost_1_71_0.tar.bz2
    popd
    pushd vendor/boost_1_71_0/
    ./bootstrap.sh --with-libraries=regex
    ./b2
    popd
}

fmt
spdlog
boost
