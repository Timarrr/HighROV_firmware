#!/bin/bash
CMAKE=$(which cmake)

if [[ -z "${1}" ]]; then
    echo "Provide the arduino device's serial port"
    exit -1
fi


if [ ! -e "${1}" ]; then
    echo "File \"${1}\" doesn't exist, exiting"
    exit -2
fi

cd $(dirname "${BASH_SOURCE[0]}") 

mkdir -p build && cd build

$CMAKE -D CMAKE_TOOLCHAIN_FILE=/home/mango/Arduino-CMake-Toolchain/Arduino-toolchain.cmake -D CMAKE_EXPORT_COMPILE_COMMANDS=1 ..

cmake --build . -j$(nproc)

make SERIAL_PORT=${1} upload-main
