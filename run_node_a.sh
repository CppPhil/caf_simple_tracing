#!/bin/bash

# Directory containing this bash script
readonly DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )

readonly PREV_DIR=$(pwd)

cd $DIR

./build/node_a/node_a_application

cd $PREV_DIR

exit 0

