#!/bin/bash

[[ $_ != $0 ]] && script_is_sourced=true || script_is_sourced=false
if [ $script_is_sourced ]; then
    SCRIPT_PATH=$BASH_SOURCE
else
    SCRIPT_PATH="$(readlink -f $0)"
fi
SCRIPT_DIR="$(dirname $SCRIPT_PATH)"
SCRIPT_NAME=$(basename $SCRIPT_PATH)

CONFIG_FILE_PATH=$SCRIPT_DIR/HalTest3ConfigRos.json
CONFIG_FILE_PATH=$SCRIPT_DIR/HalMotorDemoGazeboConfig01.json
CONFIG_FILE_PATH=$SCRIPT_DIR/HalMotorDemoComediConfig01.json

CONFIG_FILE_NAME=$(basename $CONFIG_FILE_PATH)

cp -pfr $CONFIG_FILE_PATH $SCRIPT_DIR/buildx86/
echo $CONFIG_FILE_PATH $SCRIPT_DIR/buildx86/
pushd $SCRIPT_DIR/buildx86/
sudo -E ./testappEEROSVT2 -c HalMotorDemoComediConfig01.json

