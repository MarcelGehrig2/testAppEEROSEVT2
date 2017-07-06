#!/bin/bash

[[ $_ != $0 ]] && script_is_sourced=true || script_is_sourced=false
if [ $script_is_sourced ]; then
    SCRIPT_PATH=$BASH_SOURCE
else
    SCRIPT_PATH="$(readlink -f $0)"
fi
SCRIPT_DIR="$(dirname $SCRIPT_PATH)"
SCRIPT_NAME=$(basename $SCRIPT_PATH)

cp -pfr $SCRIPT_DIR/HalTest1Config.json $SCRIPT_DIR/buildx86/
echo $SCRIPT_DIR/HalTest1Config.json $SCRIPT_DIR/buildx86/
pushd $SCRIPT_DIR/buildx86/
sudo -E ./testappEEROSVT2 -c HalTest1Config.json

