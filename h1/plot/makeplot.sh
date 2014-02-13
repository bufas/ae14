#!/bin/bash

rm *.png
rm *.data

clang++ -O3 -std=c++11 -stdlib=libc++ -o benchmark benchmark.cpp

#./benchmark linear > linear.bench.data
#./benchmark inorder 4 21 1000000 20000 > inorder.bench.data
#./benchmark bfs 4 21 1000000 20000 > bfs.bench.data
#./benchmark dfs 4 21 1000000 20000 > dfs.bench.data

#./benchmark bfs 4 21 1000000 > bfs.bench.data
#./benchmark dfs 4 21 1000000 > dfs.bench.data
./benchmark dfs_explicit 4 21 1000000 > dfs_explicit.bench.data
./benchmark dfs_explicit_int 4 21 1000000 > dfs_explicit_int.bench.data
./benchmark bfs_explicit 4 21 1000000 > bfs_explicit.bench.data
./benchmark bfs_explicit_int 4 21 1000000 > bfs_explicit_int.bench.data

rm benchmark

gnuplot makeplot.plot
