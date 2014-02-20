#!/bin/bash

rm *.png *.data

if [ "$1" == 'skew' ]; then

    clang++ -O3 -std=c++11 -stdlib=libc++ -o benchmark_skew benchmark_skew.cpp

    ./benchmark_skew 5 95 1000000 100000 100 5 > dfs_explicit_int.skew.bench.data

    rm benchmark_skew
    gnuplot makeplot_skew.plot

elif [ "$1" == 'clean' ]; then

    rm *.png *.data

else

    clang++ -O3 -std=c++11 -stdlib=libc++ -o benchmark benchmark.cpp

    # ./benchmark linear > linear.bench.data
    # ./benchmark inorder 4 21 1000000 20000 > inorder.bench.data
    # ./benchmark bfs 4 21 1000000 20000 > bfs.bench.data
    # ./benchmark dfs 4 21 1000000 20000 > dfs.bench.data

    # ./benchmark inorder 10 21 100000 100 5 > inorder.bench.data
    ./benchmark bfs 10 21 100000 100 5 > bfs.bench.data
    # ./benchmark dfs 10 21 100000 100 5 > dfs.bench.data
    # ./benchmark dfs_explicit 10 21 100000 100 5 > dfs_explicit.bench.data
    # ./benchmark dfs_explicit_int 10 21 100000 100 5 > dfs_explicit_int.bench.data
    # ./benchmark bfs_explicit 10 21 100000 100 5 > bfs_explicit.bench.data
    # ./benchmark bfs_explicit_int 10 21 100000 100 5 > bfs_explicit_int.bench.data
    # ./benchmark veb_explicit_int 10 21 100000 100 5 > veb_explicit_int.bench.data

    rm benchmark
    gnuplot makeplot.plot

fi

