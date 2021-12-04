#!/bin/sh
#
# builds the loop code using different compilers

# non-threaded (gcc)
echo "building non-threaded version"
g++-8 -std=c++11 -L/usr/local/lib  loop.cpp -o loop-plain

# gcc
echo "building GNU version"
g++-8 -std=c++11 -fopenmp -L/usr/local/lib  loop.cpp -o loop-gcc

# xcode (mac osx)
echo "building xcode (LLVM) version"
g++ -std=c++11 -Xclang -fopenmp -L/usr/local/lib  loop.cpp -o loop-xcode /usr/local/lib/libomp.dylib
