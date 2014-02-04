#!/bin/bash

rm *.png
rm *.data

clang++ -std=c++11 -stdlib=libc++ -o benchmark benchmark.cpp

#./benchmark linear > linear.bench.data
./benchmark inorder > inorder.bench.data
./benchmark bfs > bfs.bench.data

rm benchmark

gnuplot makeplot.plot

