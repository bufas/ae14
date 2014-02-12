#!/bin/bash

rm *.png
rm *.data

clang++ -O3 -std=c++11 -stdlib=libc++ -o benchmark benchmark.cpp

#./benchmark linear > linear.bench.data
./benchmark inorder 4 21 1000000 20000 > inorder.bench.data
./benchmark bfs 4 21 1000000 20000 > bfs.bench.data
./benchmark dfs 4 21 1000000 20000 > dfs.bench.data

rm benchmark

gnuplot makeplot.plot
