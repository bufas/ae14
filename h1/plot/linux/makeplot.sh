#!/bin/bash

rm -rf res
mkdir res
mkdir res/plots

g++ -O3 -std=c++11 -o benchmark ../benchmark.cpp

perf_vars="BPU LL_CACHE L1_CACHE DATA_TLB"
layouts="bfs dfs_explicit_int bfs_explicit_int veb_explicit_int"

for perf in ${perf_vars}
do
    for layout in ${layouts}
    do
        ./benchmark ${layout} ${perf} 10 21 100000 100 5 > res/${layout}.${perf}.bench.data
    done
done

rm benchmark
gnuplot ../makeplot.plot

