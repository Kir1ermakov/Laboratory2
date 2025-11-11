#!/usr/bin/env bash
set -e

cmake -S . -B build
cmake --build build --target doc_doxygen

