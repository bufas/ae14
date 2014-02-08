#!/bin/bash

rm *.png
rm *.data

clang++ -O3 -std=c++11 -stdlib=libc++ -o benchmark benchmark.cpp

#./benchmark linear > linear.bench.data
./benchmark inorder 10 26 1000000 > inorder.bench.data
./benchmark bfs 10 26 1000000 > bfs.bench.data
./benchmark dfs 10 26 1000000 > dfs.bench.data

rm benchmark

gnuplot makeplot.plot
