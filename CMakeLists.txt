cmake_minimum_required(VERSION 3.22)
project(platform_temperature_monitor)

# Build configurations
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-Wall -g")

# Output paths for build artifacts
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin) # executables
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib) # shared libraries


# Add library output path to link directories 
link_directories( ${CMAKE_LIBRARY_OUTPUT_DIRECTORY} )

# Platform Temperature Monitor Library
add_subdirectory(platform_temperature_monitor)

# TMP125 Software Driver Library
add_subdirectory(tmp125_driver)

include_directories(${CMAKE_SOURCE_DIR}/platform_temperature_monitor/include ${CMAKE_SOURCE_DIR}/tmp125_driver/include) # There is definitely a better way to do this

# Applications 
add_subdirectory(examples)

enable_testing()
# Unit Tests
add_subdirectory(test)