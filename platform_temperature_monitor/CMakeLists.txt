project(platform_temperature_monitor)
MESSAGE("${CMAKE_SOURCE_DIR}")
include_directories(${CMAKE_SOURCE_DIR}/platform_temperature_monitor/include)

set(SOURCES src/platform_temperature_monitor.cpp)

add_library(ptm_lib SHARED ${SOURCES})
target_include_directories(ptm_lib PUBLIC ${CMAKE_SOURCE_DIR}/platform_temperature_monitor/include)

