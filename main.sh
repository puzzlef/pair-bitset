#!/usr/bin/env bash
src="bitset-batched-sorted-vs-unsorted"
out="/home/resources/Documents/subhajit/$src.log"
ulimit -s unlimited
printf "" > "$out"

# Download program
rm -rf $src
git clone https://github.com/puzzlef/$src
cd $src

# Run
g++ -std=c++17 -O3 main.cxx
stdbuf --output=L ./a.out 2>&1 | tee -a "$out"
