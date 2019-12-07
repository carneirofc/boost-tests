# boost-tests
## CMake
```
-DCMAKE_BUILD_TYPE=Release
-DCMAKE_BUILD_TYPE=Debug
```
## Setup Boost
[Get boost](https://dl.bintray.com/boostorg/release/1.71.0/source/boost_1_71_0.tar.bz2)

```
tar --bzip2 -xf /path/to/boost_1_71_0.tar.bz2
```
Compile boost modules:
```
./bootstrap.sh --prefix=../boost_1_71_0_build/ --with-libraries=log regex
./b2 install
```



## Regatron
[TCIO API](https://www.regatron.com/service/download/programming-interfaces/tcio-api.zip)
 
