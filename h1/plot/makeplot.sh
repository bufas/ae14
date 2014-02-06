#!/bin/bash

rm *.png
rm *.data

clang++ -std=c++11 -stdlib=libc++ -o benchmark benchmark.cpp

#./benchmark linear > linear.bench.data
./benchmark inorder 10 15 1000 > inorder.bench.data
./benchmark bfs 10 15 1000 > bfs.bench.data

rm benchmark

gnuplot makeplot.plot

