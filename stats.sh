#!/bin/bash

set -e

fixed_data_sizes=(10000 100000 1000000 10000000 100000000 500000000)
thread_counts=(1 2 4 6 8 10 16 20 24 28 32 36 40 48)
fixed_stats_file="fixed_data_stats"

make clean
find . -type f -name '*.csv' -delete
make -f Makefile

for data_size in "${fixed_data_sizes[@]}"
do
    echo "outer"
    for thread_count in "${thread_counts[@]}"
    do
        echo "inner"
        ./main $data_size $thread_count >> ${fixed_stats_file}"_"${data_size}".csv" 
    done
done
:
