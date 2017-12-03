#!/bin/bash

# This script is taken mainly from https://gist.github.com/joegoggins/7763637 

wget -O gcc-arm-none-eabi-6-2017-q1-update-mac.tar.bz2 https://developer.arm.com/-/media/Files/downloads/gnu-rm/6_1-2017q1/gcc-arm-none-eabi-6-2017-q1-update-mac.tar.bz2?product=GNU%20ARM%20Embedded%20Toolchain,64-bit,,Mac%20OS%20X,6-2017-q1-update

# Decompress
tar xf gcc-arm-none-eabi-6-2017-q1-update-mac.tar.bz2

# Make a place to install it to
sudo mkdir /usr/local/gcc_arm

# Move the unzipped stuff there.
sudo mv gcc-arm-none-eabi-6-2017-q1-update/ /usr/local/gcc_arm/

# Change your PATH by appending the "bin" folder of the folder
# NOTE:
# You should also add this line to ~/.bashrc or ~/.bash_profile (in your home directory)
# It needs also be set in .travis.yml
export PATH="$PATH:/usr/local/gcc_arm/gcc-arm-none-eabi-6-2017-q1-update/bin"

# Check to ensure the gcc-arm firmware compiler is available (so `make clean dependents all` will work.)
arm-none-eabi-gcc --version
