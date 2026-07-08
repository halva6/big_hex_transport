#!/bin/bash
cmake -B build-native
cmake --build build-native

# run
./build-native/big-hex-transport
