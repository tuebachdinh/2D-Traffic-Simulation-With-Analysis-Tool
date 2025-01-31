#!/bin/bash

#Create a build directory
mkdir build

# Navigate to the build directory
cd build

# Run CMake to configure the build system
cmake ..

# Compile the project
make

# Run the TrafficSimulator executable
./TrafficSimulator
