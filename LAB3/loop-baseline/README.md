Loop collisions
===============

This is the same-ish code from the binding lab. Here we want to look at why we 
were seeing collisions in the three lines of code that exchange values.

# Build

Use the script build.sh to build a non-threaded, gnu and xcode (clang - LLVM)
implementations. Note the xcode requires libomp to be installed (use 
brew install libomp).

If you are using Linux, comment out the xcode implementation

# Run

Run multiple times. Note the varying of collisions; why? 
