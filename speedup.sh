#!/bin/bash

fixed_data_sizes=(10000 100000 1000000 10000000)
fixed_stats_file="fixed_data_stats"
var_speedup_file="speedup"
input=""
t1_time=0.0
count=0
speedup=1

for fixed_data_size in "${fixed_data_sizes[@]}"
do
    count=0;
    while IFS=',' read -r col1 col2 col3
    do
        if [ $count -eq 0 ]; then
            t1_time=$col3
        fi
        count=$(($count+1));
        speedup=$(echo "$t1_time / $col3" | bc)
        echo "$col1,$col2,$col3,$speedup" >> "${fixed_stats_file}/${var_speedup_file}"_"${fixed_data_size}".csv
    done < "${fixed_stats_file}/${fixed_stats_file}"_"${fixed_data_size}".csv
done
