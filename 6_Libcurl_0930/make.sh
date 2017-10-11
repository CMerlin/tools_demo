#!/bin/sh
echo "clean environment!"
rm ./TCP_demo
killall -9 TCP_demo
killall -9 TCPServer_demo
killall -9 TCPClient_demo

echo "step 1. make"
rm -rf build
mkdir build
cd build
cmake ..
make
cd ..
cp ./build/bin/TCP_demo ./
