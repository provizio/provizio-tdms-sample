#!/bin/bash

# Usage:
# sudo ./install_dependencies.sh

set -eu

# Update apt cache
apt update

# Install lsb-release for checking Ubuntu version
apt install -y --no-install-recommends lsb-release

# Check if running in Ubuntu 18
UBUNTU_18=false
if lsb_release -a | grep -q 18; then
    UBUNTU_18=true
fi

# Install GCC
apt install -y --no-install-recommends gcc g++

# Install Make
apt install -y --no-install-recommends make

# Install CMake
if [ "${UBUNTU_18}" = true ]; then
    apt install -y software-properties-common lsb-release wget
    wget -O - https://apt.kitware.com/keys/kitware-archive-latest.asc 2>/dev/null | gpg --dearmor - | tee /etc/apt/trusted.gpg.d/kitware.gpg >/dev/null
    apt-add-repository "deb https://apt.kitware.com/ubuntu/ $(lsb_release -cs) main"
    apt update && apt install -y --no-install-recommends kitware-archive-keyring
    apt update && apt install -y --no-install-recommends cmake
else
    apt install -y --no-install-recommends cmake
fi
