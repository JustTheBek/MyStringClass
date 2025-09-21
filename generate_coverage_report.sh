#!/bin/bash

coverage_dir=$(pwd)/coverage
output_dir=$coverage_dir/output
echo $output_dir

#create directories if they don't exist
mkdir -p $coverage_dir
mkdir -p $output_dir

# Collect coverage data
gcno_files=$(find ~+ -name '*gcno' | xargs) # ~+ helps to get the absolute path
#echo $gcno_files

gcda_files=$(find ~+ -name '*gcda' | xargs)
#echo $gcda_files

# Copy coverage data into coverage directory
cp $gcno_files $output_dir
cp $gcda_files $output_dir

# Analyze Coverage
lcov --gcov-tool /usr/bin/gcov --directory $output_dir -c --output-file $coverage_dir/lcov-out.info --ignore-errors source --ignore-errors graph

# Coverage is only interesting for MUT, exclude other files (compiler, GoogleTest, testrunner.cpp)
lcov --remove $coverage_dir/lcov-out.info '/usr/*' '/11/*' '*testrunner*' --output-file $coverage_dir/lcov-out.info

# Generate HTML report
genhtml $coverage_dir/lcov-out.info --output-directory $coverage_dir --title Coverage_MyStringClass --show-details --legend --branch-coverage