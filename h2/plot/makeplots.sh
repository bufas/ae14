#!/bin/bash

# Create the PNG folder, or remove old ones
if [ ! -d png ]; then
    mkdir png
else
    rm -rf png/*
fi

# Loop over each data file in the data folder
for data in $(ls data); do
    name=${data%%.*}
    gnuplot -e "datafile='data/$data'" plot.gp > png/$name.png
done
