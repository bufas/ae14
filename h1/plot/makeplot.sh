#!/bin/bash

rm -rf res
mkdir res
mkdir res/plots

if [ "$1" == 'skew' ]; then

    clang++ -O3 -std=c++11 -stdlib=libc++ -o benchmark_skew benchmark_skew.cpp

    ./benchmark_skew 5 95 1000 100000 100 5 > res/dfs_explicit_int.1k.skew.bench.data
    ./benchmark_skew 5 95 10000 100000 100 5 > res/dfs_explicit_int.10k.skew.bench.data
    ./benchmark_skew 5 95 100000 100000 100 5 > res/dfs_explicit_int.100k.skew.bench.data
    ./benchmark_skew 5 95 1000000 100000 100 5 > res/dfs_explicit_int.1m.skew.bench.data
    ./benchmark_skew 5 95 10000000 100000 100 5 > res/dfs_explicit_int.10m.skew.bench.data
    ./benchmark_skew 5 95 100000000 100000 100 5 > res/dfs_explicit_int.100m.skew.bench.data

    rm benchmark_skew
    gnuplot makeplot_skew.plot

elif [ "$1" == 'clean' ]; then

    rm -rf res

else

    clang++ -O3 -std=c++11 -stdlib=libc++ -o benchmark benchmark.cpp

    ./benchmark bfs BPU 10 22 100000 100 5 # > res/constant.BPU.bench.data
    # perf_vars="BPU"
    # layouts="bfs constant"

    # for perf in ${perf_vars}
    # do
    #     for layout in ${layouts}
    #     do
    #         ./benchmark ${layout} ${perf} 10 12 100000 100 5 > res/${layout}.${perf}.bench.data
    #     done
    # done

    rm benchmark
    gnuplot makeplot.plot

fi

