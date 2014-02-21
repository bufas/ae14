#!/bin/bash

rm -rf res
mkdir res

g++ -O3 -std=c++11 -o benchmark benchmark_linux.cpp

# ./benchmark linear > res/linear.bench.data
# ./benchmark inorder 4 21 1000000 20000 > res/inorder.bench.data
# ./benchmark bfs 4 21 1000000 20000 > res/bfs.bench.data
# ./benchmark dfs 4 21 1000000 20000 > res/dfs.bench.data

# ./benchmark inorder 10 21 100000 100 5 > res/inorder.bench.data
./benchmark bfs 10 21 100000 100 5 > res/bfs.bench.data
# ./benchmark dfs 10 21 100000 100 5 > res/dfs.bench.data
# ./benchmark dfs_explicit 10 21 100000 100 5 > res/dfs_explicit.bench.data
# ./benchmark dfs_explicit_int 10 21 100000 100 5 > res/dfs_explicit_int.bench.data
# ./benchmark bfs_explicit 10 21 100000 100 5 > res/bfs_explicit.bench.data
# ./benchmark bfs_explicit_int 10 21 100000 100 5 > res/bfs_explicit_int.bench.data
# ./benchmark veb_explicit_int 10 21 100000 100 5 > res/veb_explicit_int.bench.data

rm benchmark
gnuplot makeplot.plot

