#!/bin/bash


if [ "$1" == 'skew' ]; then

    rm -rf res
    mkdir res

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

elif [ "$1" == 'plot' ]; then

    rm -rf res1/plots
    mkdir res1/plots
    mkdir res1/plots/all
    mkdir res1/plots/implicit
    mkdir res1/plots/explicit
    mkdir res1/plots/big_queries
    mkdir res1/plots/small_queries
    mkdir res1/plots/same_queries
    python gen_gnuplot_input.py > makeplot1.plot
    gnuplot makeplot1.plot
    gnuplot skewplot.plot
    rm makeplot1.plot

else

    rm -rf res
    mkdir res

    clang++ -O3 -std=c++11 -stdlib=libc++ -o benchmark benchmark.cpp

    # ./benchmark bfs BPU 1 25 100000 100 5 > res/constant.BPU.bench.data
    perf_vars="BPU"
    layouts="stdset"

    for perf in ${perf_vars}
    do
        for layout in ${layouts}
        do
            ./benchmark ${layout} ${perf} 1 21 100000 100 5 0 1337 > res/${layout}.${perf}.bench.data
        done
    done

    rm benchmark

fi

