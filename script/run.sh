#!/bin/bash
set -e
cd "$(dirname "$0")/.."

if [ ! -f "build/tests/training_main.exe" ]; then
    echo "training_main.exe not exists!"
    exit 1
fi

./build/tests/training_main.exe
