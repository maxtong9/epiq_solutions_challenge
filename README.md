# platform_temperature_monitor

### This is a platform temperature monitor for Epiq Solution's coding challenge


## System Requirements
* Ubuntu 22.04.1 LTS

## Dependencies
* g++ v11.3.0 ``` sudo apt-get install g++ ```
* cmake v3.22.1 ``` sudo apt-get install cmake ```
* git v2.34.2  ``` sudo apt-get install git ```
* gtest - gtest artifacts are automatically fetched through CMake. Requires active internet connection and ability to connect to https://github.com/google/googletest.git.

## Build Instructions
From inside the root directory (platform_temperature_monitor/)
1. Run ```cmake -B build```
    This sets up a build directory and creates a Makefile to use.
2. Run ```cmake --build build ``` This compiles the source code. The artifacts that it creates are:
    * build/bin/ptm_demo - This is the main executable that satisfies the requirements for challenge #1
    * build/bin/ptm_demo_multithreaded - This is a more advanced executable that demonstrates using the PTM alongside a main application
    * build/bin/tmp125_driver_demo - This is a very simple application exercising the tmp125 software driver for challenge #2
    * build/lib/libptm_lib.so - This is the linux C++ Shared library for the PTM API.
    * build/lib/libtmp125_driver.so - This is the Linux C++ shared library for the TMP Software Driver.
3. Optional (Not necessary for this challenge) Install the ptm library to linux system wide: From the build directory run: ``` sudo make install ```

## Test Instructions
From instide the build directory (platform_temperature_monitor/build)
1. Run ``` cmake --build test ``` This fetches google test and builds are two unit tests. The output is:
    * build/bin/ptm_unit_test - Unit test for our PTM library
    * build/bin/tmp125_unit_test - Unit test for our TMP125 software driver
2. Run ``` ctest ``` or ``` make test ``` to run the unit tests

## Running the code
All executable files are located in platform_temperature_monitor/build/bin
* Example of running from the root directory ``` ./build/bin/ptm_demo ```
* Executables available:
    1. ptm_demo (Challenge 1 requirements)
    2. ptm_demo_multithreaded (Challenge 1 bonus requirements)
    3. tmp125_driver_demo (Challenge 2 requirements)

    