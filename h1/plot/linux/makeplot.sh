#!/bin/bash

rm -rf res
mkdir res
mkdir res/plots

# g++ -O3 -std=c++11 -o benchmark ../benchmark_skew.cpp
# ./benchmark 5 95 1000 100000 100 5 > res/dfs_explicit_int.1k.skew.bench.data
# ./benchmark 5 95 10000 100000 100 5 > res/dfs_explicit_int.10k.skew.bench.data
# ./benchmark 5 95 100000 100000 100 5 > res/dfs_explicit_int.100k.skew.bench.data
# ./benchmark 5 95 1000000 100000 100 5 > res/dfs_explicit_int.1m.skew.bench.data
# ./benchmark 5 95 10000000 100000 100 5 > res/dfs_explicit_int.10m.skew.bench.data
# ./benchmark 5 95 100000000 100000 100 5 > res/dfs_explicit_int.100m.skew.bench.data


g++ -O3 -std=c++11 -o benchmark ../benchmark.cpp

layouts="inorder bfs dfs veb_explicit_int"
perf_vars="BPU LL_CACHE L1_CACHE DATA_TLB"

for layout in ${layouts}
do
    for perf in ${perf_vars}
    do
        ./benchmark ${layout} ${perf} 26 30 100000 100 5 0 1337 > res/${layout}.${perf}.bench.data
    done
done

rm benchmark

