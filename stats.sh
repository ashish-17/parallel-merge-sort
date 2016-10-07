#!/bin/bash

set -e

fixed_data_sizes=(10000 100000 1000000 10000000 100000000 500000000)
thread_counts=(1 2 4 6 8 10 16 20 24 28 32 36 40 48)
fixed_stats_file="fixed_data_stats"

var_data_sizes=(10 100 1000 5000 10000 20000 40000 60000 80000 100000 150000 200000 500000 700000 1000000 1200000 1500000 1700000 2000000 2300000 2500000 2750000 3000000 3500000 4000000 4500000 5000000);
var_thread_counts=(1 2 4 8 16 24 32 48 64 128 256 512)
var_stats_file="var_data_stats"

make clean
find . -type f -name '*.csv' -delete
rm -rf $fixed_stats_file
rm -rf $var_stats_file

make -f Makefile
mkdir $fixed_stats_file
mkdir $var_stats_file

for data_size in "${fixed_data_sizes[@]}"
do
    for thread_count in "${thread_counts[@]}"
    do
        ./main $data_size $thread_count >> ${fixed_stats_file}/${fixed_stats_file}"_"${data_size}".csv" 
    done
done

for var_thread_count in "${var_thread_counts[@]}"
do
    for var_data_size in "${var_data_sizes[@]}"
    do
        ./main $var_data_size $var_thread_count >> ${var_stats_file}/${var_stats_file}"_"${var_thread_count}".csv" 
    done
done
:
