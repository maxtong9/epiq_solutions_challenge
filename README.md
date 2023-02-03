# platform_temperature_monitor

### This is a platform temperature monitor for Epiq Solution's coding challenge


## System Requirements
* Ubuntu 22.04.1 LTS

## Dependencies
* g++ v11.3.0 ``` sudo apt-get install g++ ```
* cmake v3.22.1 ``` sudo apt-get install cmake ```
* gtest - gtest artifacts are automatically fetched through CMake. Requires active internet connection and ability to connect to https://github.com.

## Build Instructions
From the root directory (platform_temperature_monitor/)
1. Run ```cmake -B build```
    This sets up a build directory and creates a Makefile to use.
2. Run ```cmake --build build `` This compiles the source code. The artifacts that it creates are:
    * build/bin/ptm_driver - This is the main executable that satisfies the requirements for challenge #1.
    * build/lib/libptm_lib.so - This is the linux C++ Shared library for the PTM API.
    * build/bin/ptm_unit_test - This is the unit test file for the PlatformTemperatureMonitor class.