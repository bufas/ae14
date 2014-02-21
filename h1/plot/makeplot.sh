#!/bin/bash

rm -rf res
mkdir res

if [ "$1" == 'skew' ]; then

    clang++ -O3 -std=c++11 -stdlib=libc++ -o benchmark_skew benchmark_skew.cpp

    ./benchmark_skew 5 95 1000000 100000 100 5 > res/dfs_explicit_int.skew.bench.data

    rm benchmark_skew
    gnuplot makeplot_skew.plot

elif [ "$1" == 'clean' ]; then

    rm -rf res

else

    clang++ -O3 -std=c++11 -stdlib=libc++ -o benchmark benchmark.cpp

    # ./benchmark linear BRANCH 4 10 1000000 20000 > res/linear.bench.data
    # ./benchmark inorder BRANCH 4 21 1000000 20000 > res/inorder.bench.data
    # ./benchmark bfs BRANCH 4 21 1000000 20000 > res/bfs.bench.data
    # ./benchmark dfs BRANCH 4 21 1000000 20000 > res/dfs.bench.data

    # ./benchmark inorder BRANCH 10 21 100000 100 5 > inorder.bench.data
    ./benchmark bfs BRANCH 10 21 100000 100 5 > res/bfs.bench.data
    # ./benchmark dfs BRANCH 10 21 100000 100 5 > res/dfs.bench.data
    # ./benchmark dfs_explicit BRANCH 10 21 100000 100 5 > res/dfs_explicit.bench.data
    # ./benchmark dfs_explicit_int BRANCH 10 21 100000 100 5 > res/dfs_explicit_int.bench.data
    # ./benchmark bfs_explicit BRANCH 10 21 100000 100 5 > res/bfs_explicit.bench.data
    # ./benchmark bfs_explicit_int BRANCH 10 21 100000 100 5 > res/bfs_explicit_int.bench.data
    # ./benchmark veb_explicit_int BRANCH 10 21 100000 100 5 > res/veb_explicit_int.bench.data

    rm benchmark
    gnuplot makeplot.plot

fi

