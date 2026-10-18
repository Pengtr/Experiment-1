#!/bin/bash
set -e
cd "$(dirname "$0")/.."

bash script/clean.sh
cmake -S . -B build -G Ninja
cmake --build build
