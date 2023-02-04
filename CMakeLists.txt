cmake_minimum_required(VERSION 3.22)
project(platform_temperature_monitor)

# Build configurations
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-Wall -g")

# Output paths for build artifacts
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin) # executables
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib) # shared libraries

include_directories(include)

set(SOURCES src/platform_temperature_monitor.cpp)

add_library(ptm_lib SHARED ${SOURCES})
target_include_directories(ptm_lib PUBLIC include)


set (PROJECT_LINK_LIBS libptm_lib.so)
link_directories( ${CMAKE_LIBRARY_OUTPUT_DIRECTORY} )

add_executable(ptm_driver src/ptm_driver.cpp)
target_link_libraries(ptm_driver ${PROJECT_LINK_LIBS} )

add_executable(ptm_multi_threaded examples/background_temp_monitor.cpp)
target_link_libraries(ptm_multi_threaded ${PROJECT_LINK_LIBS})

enable_testing()

add_subdirectory(tmp125_driver)
add_subdirectory(test)
# MESSAGE("${CMAKE_BINARY_DIR}") BUILD/
# MESSAGE("${CMAKE_HOME_DIRECTORY}") - PTM DIR
# MESSAGE("${CMAKE_SOURCE_DIR}") - PTM DIR
# MESSAGE("${CMAKE_INCLUDE_PATH}") - PTM DIR