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
2. Run ```cmake --build build