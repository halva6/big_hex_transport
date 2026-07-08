#!/bin/bash
emcmake cmake -B build
cmake --build build
emrun build/big-hex-transport.html
