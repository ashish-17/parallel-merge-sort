#!/bin/bash

fixed_stats_file="fixed_data_stats"
var_stats_file="var_data_stats"

make clean
find . -type f -name '*.csv' -delete
rm -rf $fixed_stats_file
rm -rf $var_stats_file
