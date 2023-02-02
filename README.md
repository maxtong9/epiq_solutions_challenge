# platform_temperature_monitor

### This is a platform temperature monitor for Epiq Solution's coding challenge


## System Requirements
* Ubuntu 22.04.1 LTS

## Dependencies
* g++ v11.3.0 ``` sudo apt-get install g++ ```
* cmake v3.22.1 ``` sudo apt-get install cmake ```
* gtest ``` sudo apt-get install libgtest-dev ```
    *   ```cd /usr/src/gtest ```\n
        ```sudo cmake CMakeLists.txt```\n
        ```sudo make ```
 
# copy or symlink libgtest.a and libgtest_main.a to your /usr/lib folder
sudo cp *.a /usr/lib

## Build Instructions
From the root directory (platform_temperature_monitor)
* ```make all``` Compiles the source code to output the executable: challenge_1