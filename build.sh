#!/bin/bash

build_dir=$(pwd)/build
#echo $build_dir

#create build dir if it doesn't exist
mkdir -p $build_dir

cd $build_dir

#call CMake to generate makefiles
cmake ..

#build
make all