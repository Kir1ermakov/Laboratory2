#!/usr/bin/env bash
set -e

cmake -S . -B build -DBUILD_TESTING=ON
cmake --build build --target game_tests
ctest --test-dir build --output-on-failure


