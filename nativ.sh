#!/bin/bash
rm -rf build-native
echo delete build-native folder
mkdir build-native
echo create build-native folder
cmake -B build-native
cmake --build build-native
echo build big-hex-transport
# run
./build-native/big-hex-transport
