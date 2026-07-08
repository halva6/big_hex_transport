#!/bin/bash
rm -rf build
echo delete build folder
mkdir build

emcmake cmake -B build
cmake --build build
# run
emrun build/big-hex-transport.html
