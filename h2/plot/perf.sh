#!/bin/bash

# Create the PNG folder, or remove old ones
if [ ! -d perf_png ]; then
    mkdir perf_png
else
    rm -rf perf_png/*
fi

gnuplot perf_plot.gp