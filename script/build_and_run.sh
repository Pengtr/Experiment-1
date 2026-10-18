#!/bin/bash
set -e
cd "$(dirname "$0")/.."

bash script/build.sh
bash script/run.sh
