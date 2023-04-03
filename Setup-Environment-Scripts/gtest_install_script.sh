#!/bin/bash
sudo apt-get install libgtest-dev google-mock cmake

cd /usr/src/gtest
sudo cmake CMakeLists.txt
sudo make
cd /usr/src/googletest/googletest/lib
sudo cp *.a /usr/lib

cd /usr/src/gmock
sudo cmake CMakeLists.txt
sudo make
cd /usr/src/gmock/lib
sudo cp *.a /usr/lib

sudo cp -R /usr/src/googletest/googlemock/include/gmock /usr/include
