#!/usr/bin/env bash
set -ev

sudo apt-get update

if [ "$1" == "assume-yes" ]; then
    sudo apt-get --yes install xorg-dev libglu1-mesa-dev libgl1-mesa-glx || true
    sudo apt-get --yes install libglew-dev || true
    sudo apt-get --yes install libglfw3-dev || true
    sudo apt-get --yes install libjsoncpp-dev || true
    sudo apt-get --yes install libeigen3-dev || true
    sudo apt-get --yes install libpng-dev || true
    sudo apt-get --yes install libpng16-dev || true
    sudo apt-get --yes install python-dev python-tk || true
    sudo apt-get --yes install python3-dev python3-tk || true
else
    sudo apt-get install xorg-dev libglu1-mesa-dev libgl1-mesa-glx || true
    sudo apt-get install libglew-dev || true
    sudo apt-get install libglfw3-dev || true
    sudo apt-get install libjsoncpp-dev || true
    sudo apt-get install libeigen3-dev || true
    sudo apt-get install libpng-dev || true
    sudo apt-get install libpng16-dev || true
    sudo apt-get install python-dev python-tk || true
    sudo apt-get install python3-dev python3-tk || true
fi
