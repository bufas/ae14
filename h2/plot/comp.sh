#!/bin/bash

# Create the PNG folder, or remove old ones
if [ ! -d comp_png ]; then
    mkdir comp_png
else
    rm -rf comp_png/*
fi

# Loop over each data file in the data folder
for data in $(ls comp_data); do
    name=${data%%.*}
    gnuplot -e "datafile='comp_data/$data'" comp_plot.gp > comp_png/$name.png
done
